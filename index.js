function pwm(config) {
  this.pin = config.pin;
  this.mode = config.mode;
  this.frequency = config.frequency;
};

pwm.prototype.register = function() {
  return __pwmRegister(this.pin, this.mode, this.frequency);
}

pwm.prototype.write = function(status) {
  return __pwmWrite(this.pin, status);
}

pwm.prototype.read = function(mode) {
  return {
    value: __pwmRead(this.pin, 0);
    frequency: __pwmRead(this.pin, 1);
  }
}

module.exports = pwm
