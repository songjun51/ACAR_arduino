#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); 
#include <DHT11.h>
int THpin = 4;
float temp, humi;
DHT11 dht11(THpin);
int t1 = 10; int e1 = 9;
int t2 = 8; int e2 = 7;
int t3 = 6; int e3 = 5;
int er3,er2,er1;
int statusCode1=0, statusCode2=0, statusCode3=0, statusCode4=0;
//int B=11,G=13,R=12;
//int btn1=3,btnstatus;
//boolean toggle=false;
void setup(){
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(t3, OUTPUT); pinMode(t2, OUTPUT); pinMode(t1, OUTPUT);
  pinMode(e3, INPUT); pinMode(e2, INPUT); pinMode(e1, INPUT);
//  pinMode(R,OUTPUT);pinMode(G,OUTPUT);pinMode(B,OUTPUT);
//  pinMode(btn1,INPUT);
  pinMode(13, OUTPUT);
}

void loop(){
  dht11.read(humi, temp);

//  btnstatus=digitalRead(btn1);
//  if(btnstatus==LOW){
//    if(toggle==true){
//      Serial.println("bbbbbbbb");
//      toggle=!toggle;
//    //시동 켜져있을때
//    
//    }
    
//  }
  
  
  digitalWrite(t3, HIGH);
  delay(10);
  digitalWrite(t3, LOW);
  er3 = pulseIn(e3, HIGH)/58.2;
  
  digitalWrite(t2, HIGH);
  delay(10);
  digitalWrite(t2, LOW);
  er2 = pulseIn(e2, HIGH)/58.2;

  digitalWrite(t1, HIGH);
  delay(10);
  digitalWrite(t1, LOW);
  er1 = pulseIn(e1, HIGH)/58.2;
  Serial.print("1  : ");
  Serial.println(er1);
  Serial.print("2  : ");
  Serial.println(er2);
  Serial.print("3  : ");
  Serial.println(er3);
//  distance = ((float)(340 * duration) / 10000) / 2;
delay(1000);


if(er1<20)//뒤에 애가 타고있음
  statusCode1=1;
else
  statusCode1=0;

  
if(er2<8)//앞자리
//어른 1
  statusCode2=1;
else if (er2>=8&&er2<13)
  statusCode2=2;
//어린이 2
else if (er2>=13&&er2<15)
  statusCode2=3;
//애기 3
else
  statusCode2=0;
// 자리에없음 0 


if (er3>10){
//문에 누구있음
statusCode3=1;
//analogWrite(R,HIGH);
//analogWrite(G,LOW);
//analogWrite(B,LOW);
//Serial.println("door o");
}
else{ 
statusCode3=0;
////문에 누가없음
//analogWrite(R,LOW);
//analogWrite(G,HIGH);
//analogWrite(B,LOW);
//Serial.println("door x");
}
if('a'==BTSerial.read()){
digitalWrite(13, HIGH);

}
//if(temp<=35){
//analogWrite(R,255);
//analogWrite(G,0);
//analogWrite(B,0);
//}

  BTSerial.print(statusCode1);
  BTSerial.print(",");

  BTSerial.print(statusCode2);
  BTSerial.print(",");

  BTSerial.print(statusCode3);
  BTSerial.print(",");

  BTSerial.println((int) temp);
  
  
}
