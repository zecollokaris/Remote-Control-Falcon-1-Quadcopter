#include <Servo.h>
#include <stdbool.h>
#include <string.h>


#define MAX_THROTTLE 2000; 

void slowmotion(int rpms);
void writeThrottle(int rpms);
void writeRpmsCumulative(int rpms); // Prototyping methods

void initializeDirections();
int toFullThrottle();
int remainThrottle(int strength);

int init_rpms=1160;  // Minimum operational rpms of rotors
typedef struct Falcon{
  Servo fr;
  Servo fl;
  Servo br;
  Servo bl;
}Falcon;


typedef struct Direction{;
  char *name;
  int high;
  int low;
  Servo motor1;
  Servo motor2;
  Servo helper;
}Direction;

   Direction right;
   Direction front;
   Direction left;
   Direction back;


typedef struct Rpms{
   int fr;
   int fl;
   int br;
   int bl;
 }Rpms;

  Rpms rpms;

  Falcon falcon;
void initial(){
  //Initializes servos to pins
  falcon.fr.attach(14);
  falcon.fl.attach(12);
  falcon.br.attach(16);
  falcon.bl.attach(2);
  initializeDirections();  
}

void detachPins(){
  falcon.fr.detach();
  falcon.fl.detach();
  falcon.br.detach();
  falcon.fl.detach();
}
void writeThrottle(int rpms){
   int diff_rpms=rpms -init_rpms;
   if(diff_rpms>20 || diff_rpms<-20){
    slowmotion(diff_rpms);
  }
  else{
    writeRpmsCumulative(rpms);
  }
}

void writeRpmsCumulative(int rpm){
  rpms.fr=rpm;
  rpms.fl=rpm;
  rpms.br=rpm;
  rpms.bl=rpm;
  falcon.fr.writeMicroseconds(rpm);
  falcon.fl.writeMicroseconds(rpm);
  falcon.br.writeMicroseconds(rpm);
  falcon.bl.writeMicroseconds(rpm);
  init_rpms=rpm;
}

void slowmotion(int rpms){
  Serial.println("rpms");
  Serial.println(rpms);

  int iterate,mod;
  if(rpms<0){
       // If difference in rpms is less than 0;
    rpms=rpms * -1;
    if(rpms % 20 ==0){
        iterate=rpms/ 20;
        while(iterate>0){
          init_rpms-=20;
          writeRpmsCumulative(init_rpms);
          Serial.println(init_rpms);
          delay(100);
          iterate--;
        }
    }
    else{
      iterate=rpms / 20;
      mod=rpms % 20;
         while(iterate>0){
          init_rpms-=20;
          writeRpmsCumulative(init_rpms);
          Serial.println(init_rpms);
          delay(100);
          iterate--;
        }
      init_rpms-=mod; 
      writeRpmsCumulative(init_rpms) ; 
    }
  }
  else{
    // If difference in rpms is more than 0;
      if(rpms % 20 ==0){
        iterate=rpms / 20;
        while(iterate>0){
          init_rpms+=20;
          writeRpmsCumulative(init_rpms);
          Serial.println(init_rpms);
          delay(100);
          iterate--;
        }
    }
    else{
      iterate=rpms / 20;
      mod=rpms % 20;
         while(iterate>0){
          init_rpms+=20;
          writeRpmsCumulative(init_rpms);
          Serial.println(init_rpms);
          delay(100);
          iterate--;
        }
      init_rpms+=mod; 
      writeRpmsCumulative(init_rpms) ; 
    }
  }
}

int toFullThrottle(){
   Serial.println("Init");
  Serial.println(init_rpms);
  return (2000- init_rpms);
}

int remainThrottle(int strength){
   float rmt=((float) strength/ (float)100);
 
    int rem=toFullThrottle();
    Serial.println("Remaining");
    Serial.println("\t");
    Serial.println(rem);

   return rmt * rem;
}

void initializeDirections(){


   right.motor1=falcon.fl;
   right.motor2=falcon.bl;
   right.high=315;
   right.low=44;



   front.motor1=falcon.bl;
   front.motor2=falcon.br;
   front.high=135;
   front.low=45;

   
   left.motor1=falcon.fr;
   left.motor2=falcon.br;
   left.high=224;
   left.low=135;


   back.motor1=falcon.fl;
   back.motor2=falcon.fr;
   back.high=314;
   back.low=225;

}

void getRpms(){
  Serial.print("fr :");
  Serial.print('\t');
  Serial.println(rpms.fr);

  Serial.print("fl :");
  Serial.print('\t');
  Serial.println(rpms.fl);

  Serial.print("br :");
  Serial.print('\t');
  Serial.println(rpms.br);

  Serial.print("bl :");
  Serial.print('\t');
  Serial.println(rpms.bl);

  Serial.print("init rpms :");
  Serial.print('\t');
  Serial.println(init_rpms);
}

void  setPath(int angle,int strength){
  int rem= remainThrottle(strength);
  Serial.println("rem\n");
  Serial.println(rem);
 if((angle>=315  &&  angle<=360) || (angle>=0  && angle<44)){
      rpms.bl=rem+init_rpms;
      rpms.fl=rem+init_rpms;
      right.motor1.writeMicroseconds(rem+init_rpms);
      right.motor2.writeMicroseconds(rem+init_rpms);
      Serial.println("Right");
      
 }
 else if(angle>=45 && angle <135){
    rpms.br=rem+init_rpms;
    rpms.bl=rem+init_rpms;
    front.motor1.writeMicroseconds(rem+init_rpms);
    front.motor2.writeMicroseconds(rem+init_rpms);  
    Serial.println("Front");
 }
 else if(angle>=135 && angle<225){
     rpms.fr=rem+init_rpms;
     rpms.br=rem+init_rpms;
    left.motor1.writeMicroseconds(rem+init_rpms);
    left.motor2.writeMicroseconds(rem+init_rpms);  
    Serial.println("Left");
 }
 else if(angle>=225 && angle<=314){
     rpms.fl=rem+init_rpms;
     rpms.fr=rem+init_rpms;
     back.motor1.writeMicroseconds(rem+init_rpms);
     back.motor2.writeMicroseconds(rem+init_rpms);  
     Serial.println("Back");
 }
 getRpms();
}
