#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <dirent.h>
#include <math.h>

#define MAX_CORES 64
#define MAX_LINE 256
#define SAMPLE_INTERVAL 1 // seconds

typedef unsigned long long ULL;

typedef struct
{
  int core_id;
  double cpu_utilization;
  double waiting_time;
  double turnaround_time;
  double throughput;
  double response_time;
  ULL cycles;
  ULL instructions;
  ULL cache_misses;
  ULL context_switches;

} CoreMetrics;

typedef struct
{
  int total_cores;
  CoreMetrics cores[MAX_CORES];
  double total_throughput;
  double avg_response_time;
} CPUMetrics;

int get_cpu_core_count()
{
  FILE *f;
  char line[MAX_LINE];
  int cores = 0;

  f = fopen("/proc/cpuinfo", "r");
  if (f == NULL)
  {
    perror("Error opening /proc/cpuinfo");
    return EXIT_FAILURE;
  }

  while (fgets(line, sizeof(line), f))
  {
    if (strstr(line, "processor"))
      ++cores;
  }

  fclose(f);
  return cores;
}

// Read perf counters for a specific core
int read_perf_counters(int core, ULL *cycles, ULL *instructions,
                       ULL *cache_misses, ULL *context_switches)
{
  char cmd[MAX_LINE];
  FILE *f;
  char line[MAX_LINE];

  // Use perf stat to measure various metrics for specific core
  snprintf(cmd, sizeof(cmd),
           "perf stat -e cycles,instructions,cache-misses,context-switches "
           "-C %d sleep %d 2>&1",
           core, SAMPLE_INTERVAL);

  // Run command in shell
  f = popen(cmd, "r");
  if (f == NULL)
  {
    perror("failed to run cmd");
    return EXIT_FAILURE;
  }

  *cycles = 0;
  *instructions = 0;
  *cache_misses = 0;
  *context_switches = 0;

  while (fgets(line, sizeof(line), f))
  {
    // Parse lines with counter values - they contain commas and spaces
    if (strstr(line, "cycles") && !strstr(line, "ref-cycles") && !strstr(line, "cycle"))
    {
      // Remove commas and parse the number
      char *ptr = line;
      while (*ptr && (*ptr < '0' || *ptr > '9'))
        ptr++;
      char *endptr;
      *cycles = strtoull(ptr, &endptr, 10);
    }
    else if (strstr(line, "instructions"))
    {
      char *ptr = line;
      while (*ptr && (*ptr < '0' || *ptr > '9'))
        ptr++;
      char *endptr;
      *instructions = strtoull(ptr, &endptr, 10);
    }
    else if (strstr(line, "cache-misses"))
    {
      char *ptr = line;
      while (*ptr && (*ptr < '0' || *ptr > '9'))
        ptr++;
      char *endptr;
      *cache_misses = strtoull(ptr, &endptr, 10);
    }
    else if (strstr(line, "context-switches"))
    {
      char *ptr = line;
      while (*ptr && (*ptr < '0' || *ptr > '9'))
        ptr++;
      char *endptr;
      *context_switches = strtoull(ptr, &endptr, 10);
    }
  }

  fclose(f);
  return 0;
}

double calculate_cpu_utilization(int core)
{
  FILE *f;
  char line[MAX_LINE];
  static ULL prev_idle[MAX_CORES] = {0};
  static ULL prev_total[MAX_CORES] = {0};

  ULL user, nice, system, idle, iowait, irq, softirq;
  ULL total, idle_time, total_delta, idle_delta;
  double utilization;

  f = fopen("/proc/stat", "r");
  if (f == NULL)
  {
    perror("failed to open /proc/stat");
    return -1.0;
  }

  // Find the line for specific core
  char core_str[16];
  memset(core_str, 0, sizeof(core_str));
  snprintf(core_str, sizeof(core_str), "cpu%d", core);

  while (fgets(line, sizeof(line), f))
  {
    if (strstr(line, core_str))
    {
      sscanf(line + strlen(core_str), "%llu %llu %llu %llu %llu %llu %llu",
             &user, &nice, &system, &idle, &iowait, &irq, &softirq);
      break;
    }
  }
  fclose(f);

  idle_time = idle + iowait;
  total = user + nice + system + idle + iowait + irq + softirq;

  if (prev_total[core] != 0)
  {
    total_delta = total - prev_total[core];
    idle_delta = idle_time - prev_idle[core];

    if (total_delta > 0)
      utilization = 100.0 * (1.0 - ((double)idle_delta / total_delta));
    else
      utilization = 0.0;
  }
  else
  {
    utilization = 0.0;
  }

  prev_idle[core] = idle_time;
  prev_total[core] = total;

  return utilization;
}

void simulate_workload()
{
  volatile double result = 0.0;
  for (int i = 0; i < 1000000; ++i)
    result += sin(i) * cos(i);
}

CPUMetrics collect_metrics()
{
  CPUMetrics cpucores;
  int num_cores = get_cpu_core_count();

  if (num_cores <= 0)
  {
    perror("Failed to get number of CPU cores");
    exit(EXIT_FAILURE);
  }

  cpucores.total_cores = num_cores;
  cpucores.total_throughput = 0.0;
  cpucores.avg_response_time = 0.0;

  printf("Monitoring %d CPU cores for %d seconds... \n", num_cores, SAMPLE_INTERVAL);

  // Create multiple process to generate load
  pid_t pids[num_cores];
  struct timeval start_time, end_time;

  gettimeofday(&start_time, NULL);

  for (int i = 0; i < num_cores; ++i)
  {
    pids[i] = fork();

    if (pids[i] == 0)
    {
      // Child process - pin to specific core and do work
      char cmd[MAX_LINE];
      snprintf(cmd, sizeof(cmd), "taskset -c %d ./dummy_workload", i);
      system(cmd);
      exit(0);
    }
  }

  // Parent process - collect metrics
  for (int core = 0; core < num_cores; ++core)
  {
    CoreMetrics *cm = &cpucores.cores[core];
    cm->core_id = core;

    // Get CPU core utilization
    cm->cpu_utilization = calculate_cpu_utilization(core);
    ULL cycles, instructions, cache_misses, context_switches;
    // Get perf counters
    if (read_perf_counters(core, &cycles, &instructions, &cache_misses, &context_switches) == 0)
    {
      cm->cycles = cycles;
      cm->instructions = instructions;
      cm->cache_misses = cache_misses;
      cm->cache_misses = cache_misses;

      // Calculate derived metrics (simplified models)
      if (instructions > 0)
      {
        cm->throughput = (double)instructions / SAMPLE_INTERVAL / 1000000.0; // MIPS
        cm->waiting_time = (double)context_switches * 0.1;                   // usec per context switch
        cm->turnaround_time = (double)cycles / 2000000000.0 * 1000.0;        // ms (assuming 2GHz)
        cm->response_time = cm->waiting_time + (cm->turnaround_time * 0.3);
      }
      cpucores.total_throughput += cm->throughput;
      cpucores.avg_response_time += cm->response_time;
    }
  }

  // Wait for all child processess
  for (int i = 0; i < num_cores; ++i)
    waitpid(pids[i], NULL, 0);

  gettimeofday(&end_time, NULL);

  // Calculate average response time
  if (num_cores > 0)
    cpucores.avg_response_time /= num_cores;

  return cpucores;
}

// Dummy workload code is compile separately
void dummy_workload()
{
  printf("Starting dummy workload... \n");
  for (int i = 0; i < 5; i++)
  {
    simulate_workload();
    sleep(1);
  }
  printf("Dummy workload completed.\n");
}

// Display metrics in a formatted way
void display_metrics(const CPUMetrics *system)
{
  printf("\n=== SYSTEM PERFORMANCE METRICS ===\n");
  printf("Total Cores: %d\n", system->total_cores);
  printf("Total Throughput: %.2f MIPS\n", system->total_throughput);
  printf("Average Response Time: %.2f ms\n", system->avg_response_time);
  printf("\n");

  printf("Core\tCPU%%\tWait(ms)\tTurn(ms)\tResp(ms)\tThru(MIPS)\tIPC\n");
  printf("----\t----\t--------\t--------\t--------\t----------\t---\n");

  for (int i = 0; i < system->total_cores; i++)
  {
    const CoreMetrics *cm = &system->cores[i];
    double ipc = (cm->instructions > 0) ? (double)cm->instructions / cm->cycles : 0.0;

    printf("%d\t%.1f\t%.2f\t\t%.2f\t\t%.2f\t\t%.2f\t\t%.3f\n",
           cm->core_id,
           cm->cpu_utilization,
           cm->waiting_time,
           cm->turnaround_time,
           cm->response_time,
           cm->throughput,
           ipc);
  }
}

int main(int argc, char *argv[])
{
  if (argc > 1 && strcmp(argv[1], "workload") == 0)
  {
    dummy_workload();
    return 0;
  }

  printf("CPU Performance Metrics Collector using perf tools\n");
  printf("==================================================\n");

  // Check if perf is available
  if (system("which perf > /dev/null 2>&1") != 0)
  {
    fprintf(stderr, "Error: perf tools not found. Please install linux-tools package.\n");
    return 1;
  }

  // Compile dummy workload if needed
  if (system("gcc -o dummy_workload -xc - -lm << 'EOF'\n"
             "#include <stdio.h>\n"
             "#include <unistd.h>\n"
             "#include <math.h>\n"
             "void simulate_workload() {\n"
             "    volatile double result = 0.0;\n"
             "    for (int i = 0; i < 1000000; i++) {\n"
             "        result += sin(i) * cos(i);\n"
             "    }\n"
             "}\n"
             "int main() {\n"
             "    printf(\"Starting workload...\\n\");\n"
             "    for (int i = 0; i < 3; i++) {\n"
             "        simulate_workload();\n"
             "        sleep(1);\n"
             "    }\n"
             "    return 0;\n"
             "}\n"
             "EOF") != 0)
  {
    perror("Failed to compile dummy workload\n");
  }

  // Collect metrics multiple times for better accuracy
  CPUMetrics metrics;
  const int samples = 3;

  for (int i = 0; i < samples; i++)
  {
    printf("Sample %d/%d:\n", i + 1, samples);
    metrics = collect_metrics();
    sleep(1);
  }

  display_metrics(&metrics);

  // Cleanup
  system("rm -f dummy_workload");

  return 0;
}