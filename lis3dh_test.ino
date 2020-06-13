/**
 *
 * @brief 아두이노에서 LIS3DH 가속도 센서를 인터페이스
 * @details 센서 설정, 가속도 데이터 획득
 * @author kyl
 * @date 2020-06-06
 * @version 0.0.1
 *
 */


#include <Wire.h>

//LIS3DH REGISTER ADDRESS MAP
#define LIS3DH_REG_WHO_AM_I   0xF
#define LIS3DH_REG_ACCX_L     0x2A
#define LIS3DH_REG_CTRL1      0x20
#define LIS3DH_REG_OUT_X_L    0x28
#define LIS3DH_REG_OUT_X_H    0x29
#define LIS3DH_REG_OUT_Y_L    0x2A
#define LIS3DH_REG_OUT_Y_H    0x2B
#define LIS3DH_REG_OUT_Z_L    0x2C
#define LIS3DH_REG_OUT_Z_H    0x2D

#define LIS3DH_10HZ           (2<<4)

const int LIS3DH_001_address = 25; 

//함수 정의
void i2c_writeOneByte(int address, int sub_address, char *wdata, int len);
int i2c_readOneByte(int address, int sub_address);



void setup() {

  int ctrl1_value;
  char wdata[2];
  
  //MCU 내부의 I2C 통신장치를 I2C 마스터 모드로 초기화.
  Wire.begin();
  
  
  ctrl1_value = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_CTRL1);
  wdata[0]= LIS3DH_10HZ|ctrl1_value;
  i2c_writeOneByte(LIS3DH_001_address,  LIS3DH_REG_CTRL1,  &wdata[0], 1);

  ctrl1_value = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_CTRL1);

  
  
  //시리얼 통신 초기화, 통신속도: 2000000
  Serial.begin(2000000);

  Serial.print("ctrl1_value = "); 
  Serial.print(ctrl1_value);

}



void i2c_writeOneByte(int address, int sub_address, char *wdata, int len)
{
 // put your main code here, to run repeatedly:
  Wire.beginTransmission(address);
  
  Wire.write(sub_address);
  Wire.write(wdata, len);
  
  Wire.endTransmission(); 
  
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
  char wdata[2];
  int device_name;
  int acc_x;
  int acc_y;
  int acc_z;
  int acc_x_l;
  int acc_x_h;
  int acc_y_l;
  int acc_y_h;
  int acc_z_l;
  int acc_z_h;
  
  
  
  //device_name = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_WHO_AM_I);
 
  acc_x_h = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_OUT_X_H);
  acc_x_l = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_OUT_X_L);
  acc_y_h = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_OUT_Y_H);
  acc_y_l = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_OUT_Y_L);
  acc_z_h = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_OUT_Z_H);
  acc_z_l = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_OUT_Z_L);

  //Serial.print("ctrl1_value: ");
  //Serial.println(ctrl1_value);


/*
  if(device_name=51)
  { 
    Serial.print("good\n\r");
  }
  else 
  {
    Serial.print("bad\n\r");
  }
*/
  //acc_x = i2c_readOneByte(LIS3DH_001_address, LIS3DH_REG_ACCX_L); 
  //Serial.print("accel X:  ")
  //Serial.print(acc_x) 
  //Serial.println("mg");
  /*delay (500);
  Serial.print("가속도 센서 x축 데이터(LOW 1Byte)는 =  ");
  Serial.println(acc_x_l);
  Serial.print("가속도 센서 x축 데이터(High 1Byte)는 =  ");
  Serial.println(acc_x_h);*/

  acc_x = acc_x_h<<8;
  acc_y = acc_y_h<<8;
  acc_z = acc_z_h<<8;
  acc_x = acc_x|acc_x_l;
  acc_y = acc_y|acc_y_l;
  acc_z = acc_z|acc_z_l;

  
  //Serial.print("가속도 센서 x축 데이터는 =  ");
  //Serial.println(acc_x);
  Serial.print("가속도 센서 y축 데이터는 =  ");
  Serial.println(acc_y);
  //Serial.print("가속도 센서 z축 데이터는 =  ");
  //Serial.println(acc_z);
  

  delay(200);

}
