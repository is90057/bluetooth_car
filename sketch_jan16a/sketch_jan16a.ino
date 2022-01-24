// 藍牙控制 L298N Arduino 小車
// 藍牙使用 HC-05 or HC-06 for Android 安卓手機
// 安卓手機 APP 請至 Play Store 下載 “ Arduino Bluetooth” by CircuitMagic
// 如您使用 iPhone手機 藍牙請用HM-10; 手機 APP 請至 APP Store 下載任何可藉由藍牙發送字元的應用程式
int spd=180;             //設定速度值 0-255
int turnspd = spd-60;    //當車子轉彎時，有一個輪子速度較慢
  
const int IN1 = 10;      // L298N IN1 連接 Arduino pin 10
const int IN2 = 11;      // L298N IN2 連接 Arduino pin 11
const int IN3 = 5;       // L298N IN3 連接 Arduino pin 5
const int IN4 = 6;       // L298N IN4 連接 Arduino pin 6

void setup() 
{
  Serial.begin(57600);   //確認藍牙傳輸速率 9600 bits/second
  pinMode(5,OUTPUT);    // Arduino 輸出電壓控制車子
  pinMode(6,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
}
 
void loop() 
{
  if (Serial.available()) {
  char c = Serial.read();     //讀入手機App藉由藍牙輸入的字元, 字元存入 c
  Serial.println(c);          //在序列埠監視器中印出所讀入的字元 c
 
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
}
  delay(100);
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
