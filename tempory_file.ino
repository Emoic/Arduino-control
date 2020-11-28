#include "DHT.h"

#define DHTPIN  33
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


//motor A
int IN1 = 4;  
int IN2 = 5;   
int ENA = A1;  

//motor B
int IN3 = 6;  
int IN4 = 7;   
int ENB = A0;  

 
unsigned long time = 1200;  //delay time
int value = 128;   // the duty cycle
int value1 = 143;

#define Trig 35 //引脚Tring 连接 IO D2
#define Echo 37 //引脚Echo 连接 IO D3 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> 
float cm; //距离变量
float temp; // 
LiquidCrystal_I2C lcd(0x27, 16, 2); 


void motorcontrol();
void forward();
void backward();
void turn_left();
void turn_right();
void forward_left();
void forward_right();
void backward_left();
void backward_right();
void stoooop();

void choose();
void ultrasonic();
void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  lcd.begin();
  lcd.backlight();
  dht.begin();
  pinMode(51, INPUT_PULLUP);
  pinMode(49, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  int h = dht.readHumidity();//读湿度
  int t = dht.readTemperature();//读温度(摄氏度)
  lcd.print(" Humidity:");
  lcd.print(h);
  lcd.print("%");
lcd.setCursor (0,1); // go to start of 2nd line
lcd.print(" Temperature:");
  lcd.print(t); 
}
 
void loop() {

 motorcontrol();
}




void motorcontrol(){
    char serialData;
    if( Serial.available()>0 ){ 
    
    serialData =  Serial.read();   
    
    if (serialData == '1' ) {  //前进
        forward();

    } 
    else if(serialData == '2' ){//后退
        backward();
    }
    else if(serialData == '3' ){//左转
        turn_left();
    }
    else if(serialData == '4' ){//右转
        turn_right();
    }
     else if (serialData == '5' ) {  //左前进
        forward_left();

    } 
     else if (serialData == '6' ) {  //右前进
        forward_right();

    } 
     else if (serialData == '7' ) {  //右后退
        backward_right();

    }     
     else if (serialData == '8' ) {  //左后退
        backward_left();

    }    
     else if (serialData == '9' ) {  //随机避障
        ultrasonic();

    }    
        
    else{   
        stoooop();
  lcd.clear();
  int h = dht.readHumidity();//读湿度
  int t = dht.readTemperature();//读温度(摄氏度)
  lcd.print(" Humidity:");
  lcd.print(h);
  lcd.print("%");
lcd.setCursor (0,1); // go to start of 2nd line
lcd.print(" Temperature:");
  lcd.print(t); 
      
    }      
  }
}





void ultrasonic(){
      char serialData1;
  
while(true){
  //给Trig发送一个低高低的短时间脉冲,触发测距
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  delayMicroseconds(2);    //等待 2微妙
  digitalWrite(Trig,HIGH); //给Trig发送一个高电平
  delayMicroseconds(10);    //等待 10微妙
  digitalWrite(Trig, LOW); //给Trig发送一个低电平
  
  temp = float(pulseIn(Echo, HIGH)); //存储回波等待时间,

  cm = (temp * 17 )/1000; //把回波时间换算成cm

  if(cm<40){
  
  lcd.clear();
  lcd.print("  Distance<40 ");
  lcd.setCursor (0,1); // go to start of 2nd line
  lcd.print("    WARNING"); 
  choose();
  forward();
  }

  if(cm<30){
  lcd.clear();
  lcd.print("  Distance<30 ");
  lcd.setCursor (0,1); // go to start of 2nd line
  lcd.print("    WARNING"); 
  backward();
  delay(1000);
  choose();
  forward();
  }

  if(digitalRead(47)==0){
  backward();
  delay(1000);
  choose();
  forward();    
  }
  if(digitalRead(51)==0){
turn_right();
  forward();    
  }
  if(digitalRead(49)==0){
turn_left();
  forward();    
  }
  
  if(cm> 40){
  forward();
  lcd.clear();
  lcd.print("  Distance:");
  lcd.print(cm); 
lcd.setCursor (0,1); // go to start of 2nd line
lcd.print(" Create by Xuhe"); 
  }
      if( Serial.available()>0 ){ 
    
    serialData1 =  Serial.read();   
          if(serialData1 =='10'){
            stoooop();

          }
           break;     
          }
}
}

void choose(){
 int x = random(1,3);
 if (x==1){
turn_left();
 }
 else if (x==2){
turn_right();
 }
 
  
}



void forward(){
      analogWrite(ENA, value1);
      analogWrite(ENB, value);      
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
}

void backward(){
      analogWrite(ENA, value1);
      analogWrite(ENB, value);      
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);  
}

void turn_left(){
      analogWrite(ENA, value);
      analogWrite(ENB, value);      
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(200);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);  
}
  
void turn_right(){
      analogWrite(ENA, value);
      analogWrite(ENB, value);      
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(200);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);  
}
 
void forward_left(){
      analogWrite(ENA, value/2);
      analogWrite(ENB, value);      
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);  
}

void forward_right(){
      analogWrite(ENA, value);
      analogWrite(ENB, value/2);      
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
}

void backward_left(){
      analogWrite(ENA, value/2);
      analogWrite(ENB, value);      
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
}

void backward_right(){
      analogWrite(ENA, value);
      analogWrite(ENB, value/2);      
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
}

void stoooop(){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW); 
}
