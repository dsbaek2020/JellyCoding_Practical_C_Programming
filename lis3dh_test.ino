/**
 *
 * @brief 아두이노에서 LIS3DH 가속도 센서를 인터페이스
 * @details 센서 설정, 가속도 데이터 획득
 * @author syl
 * @date 2020-06-06
 * @version 0.0.1
 *
 */


#include <Wire.h>

//LIS3DH REGISTER ADDRESS MAP
#define LIS3DH_REG_WHO_AM_I   0xF
#define LIS3DH_REG_ACCX_L     0x2A
#define LIS3DH_REG_CTRL1      0x20

int LIS3DH_001_address = 25; 


void setup() {
  
  //시리얼 통신 초기화, 통신속도: 9600bps
  Serial.begin(9600);

  //MCU 내부의 I2C 통신장치를 I2C 마스터 모드로 초기화.
  Wire.begin();
}


int i2c_readOneByte(int address, int sub_address)
{
 // put your main code here, to run repeatedly:
  Wire.beginTransmission(address);
  
  Wire.write(sub_address);
  
  Wire.endTransmission(0); //0은 Sr를 하기위함이다
  
  int returned_bytes = Wire.requestFrom(address,1);

    if (returned_bytes == 0)
  {
    Serial.println("I2C Error"); //Print an error
    while(1);                    //Halt the program
  }

  // Get the temp and read it into a variable  // from buffer
  int rData = Wire.read(); 

  return rData;
}


void loop() {

  int device_name;
  int acc_x;
  
  device_name = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_WHO_AM_I);

  if(device_name=51)
  { 
    Serial.print("good\n\r");
  }
  else 
  {
    Serial.print("bad\n\r");
  }

  //acc_x = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_ACCX_L); 
  //Serial.print("accel X:  ")
  //Serial.print(acc_x) 
  //Serial.println("mg");
  
}
