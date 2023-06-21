#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;
int trig=2;
int echo=3;
int tiemp;
float dis;

int agua=7;
String inputString="";
bool stringComplete=false;

void setup() {
  Serial.begin(115200);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  
  pinMode(agua,OUTPUT);
  

  if (! aht.begin()) {
    //Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  //Serial.println("AHT10 or AHT20 found");
}

void loop() {

 digitalWrite(trig,HIGH);
 //delay(1);
  digitalWrite(trig,LOW);
  tiemp= pulseIn(echo,HIGH);
  dis=tiemp/58.2;
  
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("x:"); 
  Serial.print(temp.temperature);
  //Serial.println(" degrees C");
  Serial.print("y:");
  Serial.print(humidity.relative_humidity); //Serial.println("% rH");
  Serial.print("z:");
  Serial.println(dis);
    
  if (stringComplete){
    Serial.println(inputString);
    if (inputString=="on\n"){
      digitalWrite(agua,HIGH);}
    if (inputString=="off\n"){
      digitalWrite(agua,HIGH);}
    inputString="";
    stringComplete=false;
  }
  delay(500);
}
void serialEvent(){
  while (Serial.available()){
    char inChar=(char)Serial.read();
    inputString += inChar;
    if (inChar=='\n'){
      stringComplete=true;
      }
     }
  }
