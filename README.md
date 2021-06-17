# Project-on-COVID-19-Screening-Machine-
Aim:To automate Temperature based Screening Task for COVID’19 Screening

Brief description of the Working procedure

*At first monitor will show “lets start”. After some times letter it will show the count of the     person  currently inside.
*Then master Arduino(Arduino-1) will activate Slave Arduino(Arduino-2) via Serial communication .Now the Slave Arduino is ready to work. 
*Then the LCD (that is connected to Slave Arduino(Arduino-2)) will show “Enter one person”.   Now a person can enter .
*When a person will come at the range of 13 to 20 cm in front of the machine ,the distance measurement sensor will  catch this .
*His/her temperature will be measured by the sensor and displayed on LCD both in Farenheit and Celcius.
*If his temperature is normal Green led will be turned on.
*If his temperature is high red led and buzzer will be activated.
*At the same time Surveillance monitor will display this to alert and notify the Gatekeeper.
*After the person moving to the sanitizer section The LCD will show “STOP!!”. It is just a message   for the next person standing on queue that check up of the previous person is not completed yet.So don’t enter.
* At the same time Master Arduino will disable the temperature measurement section of the Slave Arduino. That means if anyone will  enter, violating this message his/her temperature will not be measured.
*When the  person will place his hands below a knob ,PIR sensor will catch this movement  and     Servo motor will be rotated by 90 degree and LED will glow. It is just to represent that sanitizer knob is open and sanitizer is sprayed.
*It will be also displayed on Surveillance monitor and serial monitor also.
*Next the surveillance monitor will display “ check up is complete”. It will also so how many person were checked up till that moment.
*After that it will tell next person to enter and at that moment Master Arduino(Arduino-1) will activate the Slave Arduino (Arduino-2) via Serial communication and the whole process will repeat.
*All the events are printed on Serial Monitor also.




![image](https://user-images.githubusercontent.com/81832778/122360152-ce0bca80-cf73-11eb-8479-7357b00a6b62.png)


![image](https://user-images.githubusercontent.com/81832778/122360569-1aefa100-cf74-11eb-84e6-ca8a4fdd6333.png)

![image](https://user-images.githubusercontent.com/81832778/122360633-280c9000-cf74-11eb-877b-88078af71f3e.png)

https://drive.google.com/file/d/1fuPl4JK54FskE1PyEB8o2uY89dyDXq84/view?usp=sharing

video link




