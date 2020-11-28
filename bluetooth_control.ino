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

void setup() {
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
 
}
 
void loop(){
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
    else {   
        stoooop();
      
    }      
  }
}



void forward(){
      analogWrite(ENA, value);
      analogWrite(ENB, value);      
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
}

void backward(){
      analogWrite(ENA, value);
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
      delay(300);
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
      delay(300);
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
