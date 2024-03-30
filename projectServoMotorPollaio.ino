#include <Servo.h>
#include <BH1750.h>

Servo servo_9;
BH1750 GY30; // instantiate a sensor event object

int salita,discesa;
int direzione;
int analogValue;
bool aperto = false, chiuso = false, manualBool = false;
float lux;
 
void setup()
{
  Wire.begin(); // Initialize the I2C bus for use by the BH1750 library  
  GY30.begin(); // Initialize the sensor object
  servo_9.attach(9);
  Serial.begin(9600);
  
}

void loop()
{ 

 //Serial.println(servo_9.read());
//Serial.println((String)"Light: " + lux + " lx"); // print the data to the serial monitor
  
 servoMotorApri();
 servoMotorChiudi();
 manualBottom();
  
  Serial.println( " dir: "+String(direzione)+ " bool: "+ String(manualBool)+ " lux: " + String(lux));
}
 
void manualBottom()
{
  direzione = servo_9.read();
   
  if(analogRead(analogValue) > 100 && direzione >= 0)
  {
    manualBool = true;
    while(direzione != 0)
    {
      direzione--;
      servo_9.write(direzione);
      delay(100);
    }
    
  } 
  
  if(analogRead(analogValue) > 100 && direzione <= 93)
  {
    manualBool = true;
     while(direzione != 93)
     {
      direzione++;
      servo_9.write(direzione);
      delay(100);
     }    
      
      manualBool = false;  
  }
}
 

void servoMotorApri()
{
  lux = GY30.readLightLevel();
  if(lux > 50)
  {
    if(!aperto && !manualBool)
    {
      for(int i = servo_9.read(); i >= 0; i--)
      {
        servo_9.write(i);
        delay(125);
      }
      chiuso = false;
      aperto = true;
    }
  } 
}

void servoMotorChiudi()
{
  lux = GY30.readLightLevel();
  if(lux < 50)
  {
    if(!chiuso && !manualBool)
    {
      for(int i = servo_9.read(); i <= 90;i++)
      {
        servo_9.write(i);
        delay(125);
      }
      chiuso = true;
      aperto = false;
    }
  } 
  
}
