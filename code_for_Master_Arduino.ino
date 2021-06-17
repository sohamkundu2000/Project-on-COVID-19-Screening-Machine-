#include <Servo.h>                            //Library for Servo motor
#include <SoftwareSerial.h>                //Library  for Serial communication between master and slave
#include <LiquidCrystal.h>                   //Library for LCD
#define pir 8                                               // define PIR pin
#define Y 13

Servo myservo;                                      //create object under Servo
SoftwareSerial Master(10,9);                //define Rx and Tx pin

char t='0';                          //initialize those variables
int a;
int b=1;
int count=0;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);              //Initialize the library with the numbers of the 
                                                                                    Interface pins
                                                                    //LCD RS pin to digital    pin 12
                                                                 //Enable pin to digital pin 11
                                                                   //LCD D4 to D7 data pins to digital pins(5,4,3,2)respectively 


void setup() {
  lcd.begin(16, 2);                                //16 column and 2 rows
  myservo.attach(6);                         // define signal pin of Servo motor
  pinMode(pir,INPUT);                       // define pir pin as INPUT pin
  pinMode(Y,OUTPUT);                     //Define Led pin as OUTPUT
   
  myservo.write(0);                           // set the angle of servo at 0 degree
  Serial.begin(9600);                         //set the baud rate of Serial monitor
  Master.begin(9600);                        //set the baud rate  
  
  lcd.print("lets start");                        // print this message
  Serial.println("lets start");
 
}

void loop() {
  if(b==1)                                         // If delimiter b=1 call star()  function 
  {
    start();                               //to start the protocol
  }
  temp();                                          // call temp() function to accept the data sent by Slave(aeduiono-2) 
  delay(1000);                                
  while(t=='3' or t=='2')                // when received character is “3” or “2” call Sanitizer function to
                                                           activate it//                    
  {
    Sanitizer();    
  }
                                  //call this function to activate sanitizer part
  if(a==1)                                          // if delimiter is set to “1” call this function to end the protocol
  {
    end();                                       //call At the end of check of one person
  }
}



void temp()                                 // to check the status of Slave after measuring temperature
{
   if(Master.available())            //If data is Available to receive
  {
    
    t=Master.read();                      // read the data send by Slave
    
    delay(500);                                //wait for 500 millisecond
    if(t=='3')                                       //if data sent by the slave is “3” show this  message on Surveillance monitor
    {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("temp is normal");                 // show this message on Surveillance monitor
      lcd.setCursor(0,1);
      lcd.print("GL-on");                            // show that Green light is on
      
      Serial.println("temp is normal");          // print this message on serial monitor
      Serial.println("Blue Led is on");
    }
    
    if(t=='2')                                      // if data sent by the slave is “2” show this  message on Surveillance monitor
    {
      lcd.clear();
      lcd.setCursor(0,0);                      //to set the column and row of lcd
      lcd.print("temp is High");      
      lcd.setCursor(0,1);                      //to set the column and row
      lcd.print("RL-on");                  // show that red light is on
      lcd.setCursor(6,1);
      lcd.print("BZ-on");                      // show buzzer is on
      
      Serial.println("temp is High");                  //print on Serial monitor also
      Serial.println("Red Led is on");
      Serial.println("Buzzer is on");
    }
    delay(500);
  }
  
}
void start()                 // this function is for initializing the protocol
{  
  delay(2000);
  delay(500);
  Master.println("4");                         //sent the data to Slave to  print the Message
  delay(400);
  Master.println("1");                       // to activate the temperature measurement capability of Slave part
  lcd.clear();
  lcd.print("no.of person-");   
  lcd.print(count);                               // show the no. of person recently inside on Surveillance monitor
  
  Serial.print("no.of person-");       
  Serial.println(count);                     // show the same on Serial monitor
  
  b=0;
}

void Sanitizer()                     // to activate the sanitizer part 
    {
      a=digitalRead(pir);                // read the value in pir pin
      if(a==1)                                    // if the pin status is HIGH do this following
      {
        Master.write("5");           //to deactivate the temperature measurement capability on slave and print a message on LCD
        myservo.write(90);             //  rotate the servo motor by 90 degree
        digitalWrite(Y,HIGH);           // glow the yellow led
        lcd.clear();
        lcd.setCursor(0,0);
        delay(800);
        lcd.print("Sanitizer has");             // show this message on  Surveillance monitor
        lcd.setCursor(0,1);
        lcd.print("been taken");
        
        Serial.println("Sanitizer has been taken");   // show the message on Serial monitor also
        
        t=’0’;
        delay(2000);
        myservo.write(0);                   // rotate the servo by 0 degree
        digitalWrite(Y,LOW);                  // turn of the led
      }
    }

void end()                                  //  at the end of the check up
{
  lcd.clear();                          //clear the lcd screen
  lcd.setCursor(0,0); 
  lcd.print("checkup complete");        // to show this message on Surveillance monitor
  Serial.println("checkup complete");     // show that on serial monitor also
  delay(2000);
  lcd.setCursor(0,1);
   
  count=count+1;
  lcd.print("no.of person-");        //  to show the number of person currently inside
   lcd.print(count);

  Serial.print("no. of person checked up-");   // show this also in Serial monitor
  Serial.println(count);          

  delay(2000);

  lcd.clear();
  lcd.print("Next person can");       //  to show that next person can enter now
  Serial.println("Next Person can enter");
  
  lcd.setCursor(0,1);
  lcd.print("enter");
  a=0;                                           //set the delimiter value as it in beginning
  b=1;
 
}
