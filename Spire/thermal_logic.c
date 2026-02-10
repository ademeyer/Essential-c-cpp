#include <stdint.h>
#include <stdio.h>
#include <stddef.h>

#define PMS_BIT_READY (0)
#define PMS_BIT_HEATER (5)

typedef struct
{
  uint32_t status_reg;
} pms_status_t;

void update_thermal_control(pms_status_t *pms, int cur_temp)
{
  if (pms == NULL)
    return;

  if (!(pms->status_reg & (1 << PMS_BIT_READY)))
    return;

  if (cur_temp < 2)
    pms->status_reg |= (1 << PMS_BIT_HEATER);
  else if (cur_temp > 10)
    pms->status_reg &= ~(1 << PMS_BIT_HEATER);
}

int main()
{
  return 0;
}