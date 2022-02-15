#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2);

unsigned int HighByte = 0;
unsigned int LowByte  = 0;
unsigned int Len  = 0;

int spd=180;             //設定速度值 0-255
int turnspd = spd-60;    //當車子轉彎時，有一個輪子速度較慢
  
const int IN1 = 10;      // L298N IN1 連接 Arduino pin 10
const int IN2 = 11;      // L298N IN2 連接 Arduino pin 11
const int IN3 = 5;       // L298N IN3 連接 Arduino pin 5
const int IN4 = 6;       // L298N IN4 連接 Arduino pin 6
int models = 0;


void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(5,OUTPUT);    // Arduino 輸出電壓控制車子
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
}

void loop() {
    char c;
    if (Serial.available()){
        c = Serial.read();     //讀入手機App藉由藍牙輸入的字元, 字元存入 c
        Serial.println(c);          //在序列埠監視器中印出所讀入的字元 c
        if(c=='2'){
            models = 0;
        }else if(c=='4'){
            models =1;
            
        }  
    }
    if(models==0){
        //Serial.println(models);          //在序列埠監視器中印出所讀入的字元 c
        switch(c){
            case '5':                //當接收到的字元為5，車子前進
            Forward();
            break;
            
            case '7':               //當接收到的字元為7，車子後退
            Back();
            break;
            
            case '1':               //當接收到的字元為1，車子左轉
            Left();
            break;
            
            case '3':              //當接收到的字元為3，車子右轉
            Right();
            break;

            case '0':
            Stop();
            
            default:               //當所接收到的字元非以上所述，車子停止
            Stop();
            break;
        }
 
    }else if(models==1){
        Forward();
        mySerial.flush();
        mySerial.write(0X55);                           // trig US-100 begin to measure the distance
        delay(500);                                  
        if (mySerial.available() >= 200)                  // check receive 2 bytes correctly
        {
            HighByte = mySerial.read();
            LowByte  = mySerial.read();
            Len  = HighByte * 256 + LowByte;          // Calculate the distance
            Serial.println(Len); 
            if ((Len > 1) && (Len < 10000))
            {
                if (Len >200){
                    // 先倒退
                    for(int i=0;i<5000; i++){
                        Back();
                    }
                    // 再右轉
                    for(int i=0;i<5000; i++){
                        Right();
                    }
                }               
            }
        }

    }
 // delay(300);                                    
} 

void Forward(void)        //車子前進子程式
{
  analogWrite(IN1, spd);
  analogWrite(IN2, 0);
  analogWrite(IN3, spd);
  analogWrite(IN4, 0);
} 
void Back(void)           //車子後退子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, spd);
  analogWrite(IN3, 0);
  analogWrite(IN4, spd);
} 

void Stop(void)           //車子停止子程式
{
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void Left(void)            //車子左轉子程式
{
  analogWrite(IN1, spd);
  analogWrite(IN2, 0);
  analogWrite(IN3, turnspd);
  analogWrite(IN4, 0);
} 

void Right(void)             //車子右轉子程式
{
  analogWrite(IN1, turnspd);
  analogWrite(IN2, 0);
  analogWrite(IN3, spd);
  analogWrite(IN4, 0);
}
