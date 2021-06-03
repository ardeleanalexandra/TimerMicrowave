#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int minutes;
int seconds=59;
char timeline[16];
 
int button1=0;
int button2=0;
int stop=0;
int start=0;
int verifSec=0;
int sensorValue=0;


void setup() {

  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.print("Cronometru :");
  pinMode(8,INPUT);
  pinMode(9,INPUT);
  pinMode(13,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,INPUT);
  pinMode(7,INPUT);
  //minutes=analogRead(A0);
  
}

void loop() {
  
 
  button1=digitalRead(8);
  button2=digitalRead(9);
  stop=digitalRead(10);
  start=digitalRead(7);
  sensorValue=analogRead(A0);
  
  
  if(button1==HIGH  && seconds > 10 ) {
    seconds=seconds-9;
  }
  
  if(button2==HIGH  ) {
    
    if(seconds<50)
        seconds=seconds+11;
    
    else { 
      		seconds=(seconds+11)%10;
           	minutes++;
         }

  }
 
  lcd.setCursor(0, 1);
  sprintf(timeline,"%0.2d min %0.2dseconds", minutes, seconds);
  lcd.print(timeline);
 
  if( start==HIGH ){

     if(seconds>=0)
     {
    	seconds--;
     }
   
  } else minutes=map(sensorValue, 0, 1023, 0, 60);

  delay(1000);
 
  if((minutes>0 )&&( seconds == -1))
  {	//delay(1000);
    minutes--;
  	seconds = 59;
   }
  
  if(stop==HIGH)
    {minutes=0;
     seconds=0;
      }
 
 
  if((seconds==-1) &&(minutes!=0))
{
lcd.print(minutes);
lcd.print(seconds);
lcd.clear();
}
 
   
  if(seconds==-1) {
     if(minutes!=0)
		{
        lcd.print(minutes);
		lcd.print(seconds);
		lcd.clear();
	}else
     seconds=0;}
 


  
 if((seconds==0) && (minutes==0))
   { tone(13,220,10000);
    digitalWrite(6,HIGH);
    
   }

}
