#include <SoftwareSerial.h>               //This library is for Serial communication between two arduino
#include <LiquidCrystal.h>               //for lcd screen
SoftwareSerial Slave(10,9);     //RX and TX

#define R 19     //for red led
#define G 18  //for green led
#define buzzer 13                         
#define rl 17
#define gl 16
long duration;
int distance;
double temp;
double far;
double cel;
char m='0';
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);    // initialize the library with the numbers of the interface pins
                                                                 //LCD RS pin to digital pin 12
                                                                 //Enable pin to digital pin 11
                                                                   //LCD D4 to D7 data pins to digital pins(5,4,3,2)respectively
void setup() {
  
  lcd.begin(16, 2);    
                                                       //initialization different pins
  pinMode(7,INPUT);                   //echo pin for HCSr04
  pinMode(8,OUTPUT);                //trig for the HcSr04
  pinMode(R,OUTPUT);                  // pin for red led
  pinMode(G,OUTPUT);                 //pin for green led
  pinMode(rl,OUTPUT);                   // pin for red marker led
  pinMode(gl,OUTPUT);                 //pin for green marker led
  pinMode(buzzer,OUTPUT);            // pin for buzzer
  Slave.begin(9600);                    // baud rate for slave
  Serial.begin(9600);                  //baud rate for Serial monitor
                
  
}

void loop() {
if(Slave.available())               // If  data is  available to receive from master
 {   
  m=Slave.read();                   //Read that data
 }
  delay(400);                           // wait for 400 millisecond
 while(m=='1')                        // When sent data is “1”( by master)
  {  
    m=checkUp(m);                //call that function to start checkup
  }
  delay(400);                             // wait for 400 millisecond
  // M_distance();
  if(m=='4')                             //if sent data is “4” show the message on lcd
   {
     lcd.clear();                        //to clear the screen
     lcd.print("Enter one");
     lcd.setCursor(0,1);             // to set the cursor of LCD
     lcd.print("person");
     m=’0’;
   }
  delay(400);                     // wait for 400 millisecond
  if(m=='5')                      // if sent data is “5”  show the message on lcd and turn off the components
  {
    lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("STOP!!");                //print this message on lcd
    
    digitalWrite(gl,LOW);                     // turn off the marker red LED
    digitalWrite(rl,LOW);                      //turn off the marker green led
    digitalWrite(R,LOW);                      //turn off the RED led
    digitalWrite(G,LOW);                      //turn off the GREEN led
    digitalWrite(buzzer,LOW);             // turn off the buzzer
    m='0';                                                  //set the delimiter value
  }  
  delay(400);        // wait for 400 millisecond
}

int checkUp(int m)      //check up  function  
{
   M_distance();               //call this function to measure distance
    
    if(distance>10 and distance<20)     // if the distance lie between(10-20) do that 
    {   
      temperature();                                 //call temperature function to measure temperature
      printTemp(temp);                          //call this function to print the temperature on LCD and Serial Monitor
      if(temp>98)                                      // if the temperature is above 98 degree farenheit
      {
        digitalWrite(R,HIGH);                     // red led high
        digitalWrite(buzzer,HIGH);             // buzzer on
        Slave.println("2");                           // Send the data to master Arduino that this if statement executed success fully
      }
    
      else                                                              // if the temperature is below 98 degree farenheit
      {
        digitalWrite(G,HIGH);                           // green led on
       
        Slave.println("3");                              // Send the data to master Arduino that this ’else’ statement executed success fully

        delay(1000);
      }
     m='7';                                  //set the delimiter value
    }
  return m;                          // return this value to the calling function
}

  
void M_distance()                 // function to measure distance
{
  digitalWrite(8,LOW);               // trig pin low    
  delayMicroseconds(2);             //wait two microsecond
  digitalWrite(8,HIGH);                 //trig pin High
  delayMicroseconds(10);            //wait for ten microsecond
  digitalWrite(8,LOW);                  // trig pin set to low

  duration=pulseIn(7,HIGH);                       // Pulse in function to reads the reflected pulse from an object
  distance=duration*0.034/2;                       //compute distance in centimeter
  if(distance<20 and distance>10)               // if the distance is in between this range green led turn on 
  {
    digitalWrite(gl,HIGH);                               //green led on to indicate the person he is in proper range
  }
  if(distance<10)                                         //if the the person will come to close to the sensor Alert him by red led
  {
    digitalWrite(rl,HIGH);                           // to indicate the person he  is in wrong position
  }
     
 
}
void temperature()                                  //function for measuring temperature
{
  int a=analogRead(0);                                //read analog voltage in analog pin ‘0’
  temp=(double)a/1024;                             // find the percentage of input reading
  temp=temp*5;                                           //multiply by 5V to get the voltage

  temp=temp-0.5;                                         //Subtract the offset
  temp=temp*100;                                        //convert to degree
  far=(9*temp/5)+32;                                  //convert it into farenheit
  cel=temp;                                                    // temperature in celcius
  
  temp=far;                                                   // convert temp to farenheit
 
}
void printTemp(double temp)            //function to print the temperature in lcd and serial monitor
{
   far=temp;
  
  lcd.clear();                                                //clear the screen
  lcd.setCursor(0,0);                                  //set the cursor of LCD  (columb,row) (0,0)                           
  lcd.print("temp is ");                                 

  lcd.print(far);                                           //print the temperature on LCD in farenheit
  lcd.print(" ");
  lcd.print("*F");                                          //print this message on lcd             
  
  lcd.setCursor(2,1);
  lcd.print("or");                                        //print this message on lcd      
  lcd.setCursor(6,1);
  lcd.print("  ");                                            //print this message on lcd   
  lcd.print(cel);                                            //print the temperature on LCD in celcius
  lcd.print(" ");
  lcd.print("*C");                                       //print this message on lcd   
  
  Serial.print("temperature is->");                
  Serial.print(far);                                             // print the temperature on Serial Monitor in farenheit
  Serial.println(" degree F");
  
  Serial.print("temperature is->");
  Serial.print(cel);                                                    //  print the temperature on Serial Monitor in celcius                    
  Serial.println(" degree C");
 
}


 
