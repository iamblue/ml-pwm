# ml-pwm

## Required

* ml-pinmux

## API

* pwmRegister

``` js

pwmRegister(
  pin,      // number
  mode,     // number
  frequency // number
)

/*

mode:
  * HAL_PWM_CLOCK_32KHZ = 0
  * HAL_PWM_CLOCK_2MHZ  = 1
  * HAL_PWM_CLOCK_20MHZ = 2
  * HAL_PWM_CLOCK_26MHZ = 3
  * HAL_PWM_CLOCK_40MHZ = 4
  * HAL_PWM_CLOCK_52MHZ = 5

*/

```

* pwmWrite

``` js
pwmWrite(
  pin,   // number
  value  // number
)

```

* pwmRead

``` js
pwmRead(
  pin,   // number
  mode   // 0: value, 1: frequency
)

```


## Example

``` js

/* Write example */

pinmux(31, 9);  // set pinmux
pwmRegister(32, 4, 400000);  // registe pwm

var t = 0;
timer(function() {
  pwmWrite(32, t);  // write signal
  t++;
  if (t === 10) {
    t = 0;
  }
}, 10);

```
