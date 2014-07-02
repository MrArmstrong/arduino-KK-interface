#include <Servo.h>
Servo bldc_Aileron;
Servo bldc_Elevator;
Servo bldc_Throttle;
Servo bldc_Rudder;
Servo bldc_Aux;

String string= "";

//To send a command use this format : e.g. TH_1850
//for Aileron AI
//for Elevator EL
//for Throttle TH
//for Throttle RD
//for Auxiliary use AUX_ON or AUX_OFF

int defAileron = 1500;//Max value is 1900 and Min value is 1100
int defElevator = 1500;//Max value is 1900 and Min value is 1100
int defThrottle = 1100;//Max value is 2400 and Min value is 1100
int defRudder = 1500;//Max value is 1900 and Min value is 1100

int AuxOn = 2018;
int AuxOff = 1015;


void setup(){
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  bldc_Aileron.attach(5);
  bldc_Elevator.attach(6);
  bldc_Throttle.attach(9);
  bldc_Rudder.attach(10);
  bldc_Aux.attach(11);

  Serial.begin(9600);
  delay(100);
  initializePulse();
  
  Serial.println("System Ready");
}


void loop(){
  
  string = "";

    while(Serial.available() > 0)
    {
        string += (char) Serial.read();
        Serial.flush();
        delay(10);
    }

    if(string != "")
    {
      String word1 = getValue(string, '_', 0);
      String word2 = getValue(string, '_', 1);
      
      Serial.println(word1);
      
//      if(word1 == "+"){
//        fullThrottle();
//      }
//      
//      if(word1 == "-"){
//        IdleThrottle();
//      }
      
      if(word1=="TH"){
        int th = word2.toInt();
        bldc_Throttle.writeMicroseconds(th); //actually write the value to the motor
        Serial.print("Throttle speed :");Serial.println(bldc_Throttle.read());
      }
      
      if(word1=="RD"){
        int th = word2.toInt();
        bldc_Rudder.writeMicroseconds(th); //actually write the value to the motor
        Serial.print("Rudder :");Serial.println(word2);
      }
      
      if(word1=="AI"){
        int th = word2.toInt();
        bldc_Aileron.writeMicroseconds(th); //actually write the value to the motor
        Serial.print("Aileron :");Serial.println(word2);
      }
      
      if(word1=="EL"){
        int th = word2.toInt();
        bldc_Elevator.writeMicroseconds(th); //actually write the value to the motor
        Serial.print("Elevator :");Serial.println(word2);
      }
      
      if(word1=="AUX"){
        if(word2=="ON"){
          Auxiliary(true);
          Serial.println("Self-Level is ON");
        }
        else if(word2=="OFF"){
          Auxiliary(false);
          Serial.println("Self-Level is OFF");
        }
      }
      
      if(word1=="ARM"){
        ArmModel();
      }
      
      if(word1=="DARM"){
        DisArmModel();
      }
    }
  delay(10);
}


void fullThrottle(){
  bldc_Throttle.writeMicroseconds(2390);
}

void IdleThrottle(){
  bldc_Throttle.writeMicroseconds(defThrottle);
}

void ArmModel(){
  bldc_Rudder.writeMicroseconds(1100);
  delay(2000);
  bldc_Rudder.writeMicroseconds(defRudder);
  
  Serial.println("Model Armed and Ready to Fly");
  delay(1000);
}

void DisArmModel(){
  bldc_Rudder.writeMicroseconds(1900);
  delay(2000);
  bldc_Rudder.writeMicroseconds(defRudder);
  
  Serial.println("Model Disarmed");
  delay(1000);
}


void initializePulse(){
  
  bldc_Aileron.writeMicroseconds(defAileron);
  delay(10);
  bldc_Elevator.writeMicroseconds(defElevator);
  delay(10);
  bldc_Throttle.writeMicroseconds(defThrottle);
  delay(10);
  bldc_Rudder.writeMicroseconds(defRudder);
  delay(10);
  Auxiliary("ON");
  delay(10);
  Serial.println("Pulse Initialized");
}

void Auxiliary(bool SW){
  if(SW){
    bldc_Aux.writeMicroseconds(AuxOn);
  }
  else{
    bldc_Aux.writeMicroseconds(AuxOff);
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}

