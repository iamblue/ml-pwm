#include <string.h>
#include "jerry.h"
#include "pinmux.h"
#include "hal_pwm.h"
#include "microlattice.h"

DELCARE_HANDLER(pwmRegister) {
  uint8_t pin = (int)args_p[0].v_float32;
  uint8_t mode = (int)args_p[1].v_float32;
  uint8_t frequency = (int)args_p[2].v_float32;
  uint32_t total_count = 0;

  if (HAL_PWM_STATUS_OK != hal_pwm_init(HAL_PWM_CLOCK_40MHZ)) {
      printf("hal_pwm_init fail");
      return true;
  }
  if (HAL_PWM_STATUS_OK != hal_pwm_set_frequency(32, 400000, &total_count)) {
      printf("hal_pwm_set_frequency fail");
      return true;
  }
  if (HAL_PWM_STATUS_OK != hal_pwm_set_duty_cycle(32, 0)) {
      printf("hal_pwm_set_duty_cycle fail");
      return true;
  }
  if (HAL_PWM_STATUS_OK != hal_pwm_start(32)) {
      printf("hal_pwm_start fail");
      return true;
  }

  ret_val_p->type = JERRY_API_DATA_TYPE_BOOLEAN;
  ret_val_p->v_bool = true;
  return true;
}

DELCARE_HANDLER(pwmWrite) {
  uint8_t pin = (int)args_p[0].v_float32;
  uint8_t value = (int)args_p[1].v_float32;

  hal_pwm_set_duty_cycle(pin, value);

  ret_val_p->type = JERRY_API_DATA_TYPE_BOOLEAN;
  ret_val_p->v_bool = true;
  return true;
}

DELCARE_HANDLER(pwmRead) {

  uint8_t pin = (int)args_p[0].v_float32;
  uint8_t mode = (int)args_p[1].v_float32;
  uint32_t frequency = 0;
  uint32_t value = 0;

  if (1 == mode) {
    hal_pwm_get_frequency(pin, &frequency);
    ret_val_p->type = JERRY_API_DATA_TYPE_FLOAT64;
    ret_val_p->v_float64 = frequency;
  } else {
    hal_pwm_get_duty_cycle(pin, &value);
    ret_val_p->type = JERRY_API_DATA_TYPE_FLOAT64;
    ret_val_p->v_float64 = value;
  }

  return true;
}

void ml_pwm_init(void) {
  REGISTER_HANDLER(pwmWrite);
  REGISTER_HANDLER(pwmRead);
  REGISTER_HANDLER(pwmRegister);
}