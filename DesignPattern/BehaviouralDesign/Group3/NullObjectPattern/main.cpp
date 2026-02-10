#include <iostream>
#include <vector>

class Logger
{
public:
  virtual ~Logger() {}
  virtual void log(const std::string &message) = 0;
};

class ConsoleLogger : public Logger
{
public:
  void log(const std::string &message) override { std::cout << message << "\n"; }
};

class FileLogger : public Logger
{
  std::string filePath;

public:
  FileLogger(const std::string &path) : filePath(path) {}
  void log(const std::string &message) override
  {
    std::cout << "Writing message: " << message << "to filepath: " << filePath << "\n";
  }
};

class APILogger : public Logger
{
  std::string url;

public:
  APILogger(const std::string &url) : url(url) {}
  void log(const std::string &message) override
  {
    std::cout << "Writing message: " << message << "to api: " << url << "\n";
  }
};

class NullLogger : public Logger
{
public:
  void log(const std::string &message) override {}
};

class SomeTask
{
  Logger *logger = nullptr;

public:
  SomeTask() { logger = new NullLogger; }
  SomeTask(Logger *logger) : logger(logger) {}
  ~SomeTask() { delete logger; }
  void execute()
  {
    // No need to check for a nulllogger
    logger->log("did some stuff");
    logger->log("did some other stuff");
    logger->log("Task complete!");
  }
};

int main()
{
  SomeTask task1(new ConsoleLogger);
  SomeTask task2(new FileLogger("logs.txt"));
  SomeTask task3(new APILogger("loggingsite.com/api/log"));
  SomeTask task4;

  task1.execute();
  task2.execute();
  task3.execute();
  task4.execute();

  return 0;
}