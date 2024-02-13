#include <Wire.h>
#include <ServoDriver.h>

ServoDriver servo(NO_R_REMOVED);//this value affects the I2C address, which can be changed by
                                //removing resistors R1-R3. Then the corresponding R1_REMOVED,
                                //R2_REMOVED, R1_R2_REMOVED, R1_R4_REMOVED and so on can be set.
                                //Default is NO_R_REMOVED


#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

void setRelay(uint8_t relay, uint16_t val){
if (val == 0) {
  servo.setServo(relay, 2000); 
} else {
  servo.setServo(relay, 10000);
  }
}

void setup(){
  SerialMonitorInterface.begin(9600);
  Wire.begin();

  servo.useResetPin();         //This tells the library to use the reset line attached to Pin 9
  if(servo.begin(20000)){      //Set the period to 20000us or 20ms, correct for driving most servos
    SerialMonitorInterface.println("Relay not detected!");
    while(1);
  }
  //The failsafe turns off the PWM output if a command is not sent in a certain amount of time.
  //Failsafe is set in milliseconds- comment or set to 0 to disable
  servo.setFailsafe(1000);
  setRelay(1, 1);
  setRelay(2, 1);
  setRelay(3, 1);
  setRelay(4, 1);
}

void loop()
{
  
}