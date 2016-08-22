#include <string.h>
#include "jerry-api.h"
#include "pinmux.h"
#include "hal_pwm.h"
#include "microlattice.h"

DELCARE_HANDLER(__pwmRegister) {
  uint8_t pin = jerry_get_number_value(args_p[0]);
  uint8_t mode = jerry_get_number_value(args_p[1]);
  uint8_t frequency = jerry_get_number_value(args_p[2]);
  uint32_t total_count = 0;

  if (HAL_PWM_STATUS_OK != hal_pwm_init(HAL_PWM_CLOCK_40MHZ)) {
      printf("hal_pwm_init fail");
      return true;
  }
  if (HAL_PWM_STATUS_OK != hal_pwm_set_frequency(pin, frequency, &total_count)) {
      printf("hal_pwm_set_frequency fail");
      return true;
  }
  if (HAL_PWM_STATUS_OK != hal_pwm_set_duty_cycle(pin, 0)) {
      printf("hal_pwm_set_duty_cycle fail");
      return true;
  }
  if (HAL_PWM_STATUS_OK != hal_pwm_start(pin)) {
      printf("hal_pwm_start fail");
      return true;
  }

  return jerry_create_boolean(true);
}

DELCARE_HANDLER(__pwmWrite) {
  uint8_t pin = jerry_get_number_value(args_p[0]);
  uint8_t value = jerry_get_number_value(args_p[1]);

  printf("pin: %d\n", pin);
  printf("value: %d\n", value);
  hal_pwm_set_duty_cycle(pin, value);

  return jerry_create_boolean(true);
}

DELCARE_HANDLER(__pwmRead) {

  uint8_t pin = jerry_get_number_value(args_p[0]);
  uint8_t mode = jerry_get_number_value(args_p[1]);
  uint32_t frequency = 0;
  uint32_t value = 0;

  if (1 == mode) {
    hal_pwm_get_frequency(pin, &frequency);
    return jerry_create_number(frequency);

  } else {
    hal_pwm_get_duty_cycle(pin, &value);
    return jerry_create_number(value);
  }
}

void ml_pwm_init(void) {
  REGISTER_HANDLER(__pwmWrite);
  REGISTER_HANDLER(__pwmRead);
  REGISTER_HANDLER(__pwmRegister);
}