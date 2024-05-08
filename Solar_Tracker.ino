
#include <Servo.h> // include Servo library 

// 180 horizontal max value
Servo horizontal; // horizontal servo
int servoh = 180;   // 90;     // stand horizontal servo

int servohLimitHigh = 180;
int servohLimitLow = 65;

// 65 vertical max value
Servo vertical;   // vertical servo 
int servov =50;    //   90;     // stand vertical servo

int servovLimitHigh = 100;
int servovLimitLow = 0;


// LDR pin connections
int ldrld = 2; //LDR down left 
int ldrlt = 3; //LDR top left
int ldrrt = 1; //LDR top right 
int ldrrd = 0; //LDR down right

void setup()
{
  Serial.begin(9600);
// name.attacht(pin);
  horizontal.attach(4); 
  vertical.attach(3);
  horizontal.write(45);
  vertical.write(45);
  delay(3000);
}

void loop() 
{
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  int tol = 50;

  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the difference of up and down
  int dhoriz = avl - avr;// check the difference og left and rigt
  
  
  Serial.println(ld);
  Serial.println();

  
    
  if (-1*tol > dvert || dvert > tol) // check if the difference is in the tolerance else change vertical angle
  {
  if (avt > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avt < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the difference is in the tolerance else change horizontal angle
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
}




