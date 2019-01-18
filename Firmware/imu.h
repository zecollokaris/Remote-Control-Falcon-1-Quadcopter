#include <Wire.h>
#include <stdbool.h>
byte check_I2c(int address);
void getMPUReadings();
void initSetup();
void stabilizeX();
void stabilizeY();
void stabilizeZ(); 

const int MPU_addr=0x69; // Register address of mpu

int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

double AX,AY,AZ,T,GX,GY,GZ;

float gyro_angle=0;
float initial_angle=0;
bool reached=false;
const float deg_second=0.0159154943 ;



const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

void initSetup() {
  Wire.begin();
  // put your setup code here, to run once:
  check_I2c(0x69);
  Wire.beginTransmission(0x69);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

}

void getMPUReadings() {
Wire.beginTransmission(MPU_addr);
Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H)
Wire.endTransmission(false);
Wire.requestFrom(MPU_addr,14,true); // request a total of 14 registers
AcX=Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
AcY=Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
AcZ=Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
Tmp=Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
GyX=Wire.read()<<8|Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
GyY=Wire.read()<<8|Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
GyZ=Wire.read()<<8|Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)



T=(double) Tmp/340+36.53;
AX=((double) AcX/AccelScaleFactor) - 0.02;
AY=((double) AcY/AccelScaleFactor) - 0.02;
AZ=((double) AcZ/AccelScaleFactor) - 0.02;


GX=((double) GyX/GyroScaleFactor)- 0.02;
GY=((double) GyY/GyroScaleFactor) - 0.02;
GZ=((double) GyZ/GyroScaleFactor) - 0.02;

Serial.print("AcX = "); Serial.print(AX);
Serial.print(" | AcY = "); Serial.print(AY);
Serial.print(" | AcZ = "); Serial.print(AZ);
Serial.print(" | Tmp = "); Serial.print(T);
Serial.print(" | GyX = "); Serial.print(GX);
Serial.print(" | GyY = "); Serial.print(GY);
Serial.print("| GyZ = "); Serial.println(GZ);





//
  if(AX>0.2 || AX< -0.2){
    stabilizeX();
    getRpms();
  }
  
  if(AY>0.2 || AY< - 0.2){
    stabilizeY();
    getRpms(); }
//
//



delay(100); // Wait 100 ms and scan again
}


void stabilizeX(){
  if(AX>-0.09 && AX<0.04){
        Serial.println("Done Pitch Front");
     writeThrottle(init_rpms);
  }
  else{
    if(AX<0.0){
     if(AX<-0.09){
      if(rpms.fr>=1165){
      rpms.fr-=5;
      falcon.fr.writeMicroseconds(rpms.fr);
      }
 
      if(rpms.fl>=1165){
      rpms.fl-=5;
      falcon.br.writeMicroseconds(rpms.fl);
      }
 

      if(rpms.bl<=1995){
      rpms.bl+=5;
      falcon.br.writeMicroseconds(rpms.bl);
      }

      if(rpms.br<=1995){
         rpms.br+=5;
      falcon.br.writeMicroseconds(rpms.br);
      }
     
      delay(1000);
      Serial.println("Done Pitch Front");
    }
 
  }
  else{
    if(AX>0.04){
      if(rpms.fr<=1995){
      rpms.fr+=5;
      falcon.fr.writeMicroseconds(rpms.fr);
      }
 
      
      if(rpms.fl<=1995){
      rpms.fl+=5;
      falcon.br.writeMicroseconds(rpms.fl);
      }
 

      if(rpms.bl>=1165){
      rpms.bl-=5;
      falcon.br.writeMicroseconds(rpms.bl);
      }
     

      if(rpms.br>=1165){
         rpms.br-=5;
      falcon.br.writeMicroseconds(rpms.br);
      }
      delay(1000);
      Serial.println("Done Pitch Back");
     }  
   }
  }
}

void stabilizeY(){
  if(AY<0.0){
    if(AY<-0.04){
   if(rpms.fr<=1995){
      rpms.fr+=5;
      falcon.fr.writeMicroseconds(rpms.fr);
      }
 
      
      if(rpms.fl>=1165){
      rpms.fl-=5;
      falcon.br.writeMicroseconds(rpms.fl);
      }
 

      if(rpms.bl>=1165){
      rpms.bl-=5;
      falcon.br.writeMicroseconds(rpms.bl);
      }
     

      if(rpms.br<=1995){
         rpms.br+=5;
      falcon.br.writeMicroseconds(rpms.br);
      }
      delay(1000);
      Serial.println("Done Roll Left");
    }
  
  }
  else{
    if(AY>0.04){
      if(rpms.fr>=1165){
      rpms.fr-=5;
      falcon.fr.writeMicroseconds(rpms.fr);
      }
 
      
      if(rpms.fl<=1995){
      rpms.fl+=5;
      falcon.br.writeMicroseconds(rpms.fl);
      }
 

      if(rpms.bl<=1995){
      rpms.bl+=5;
      falcon.br.writeMicroseconds(rpms.bl);
      }
     

      if(rpms.br>=1165){
         rpms.br-=5;
      falcon.br.writeMicroseconds(rpms.br);
      }
      delay(1000);
      Serial.println("Done Roll Right");
    }
     
  }
}





byte check_I2c(int address){
   byte error;

  Wire.beginTransmission(MPU_addr);
  error=Wire.endTransmission();

  if(error==0){
    Serial.println("Device Found");
  }
  else{
       Serial.println("Device NotFound");
  } 
  delay(4000);
  return error;
}
