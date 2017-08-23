//----------SLS Team 8----------
//---Alhassan Khaled---Mohamed Wael---Youssef Amr---Suhil Elkholy---
//Coach :---Ahmed Tarek Fahmy---
//RoboCup2017 code



//QTR-8RC SENSOR Line Follwing
#include <QTRSensors.h>     //QTR-8RC Library
#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2
// sensors 0 through 7 are connected to digital pins 2 through 9, respectively
QTRSensorsRC qtrrc((unsigned char[]) {2, 3, 4, 5, 6, 7, 8, 9},
 NUM_SENSORS, TIMEOUT, EMITTER_PIN); 
unsigned int sensorValues[NUM_SENSORS];
unsigned int sensorValues2[NUM_SENSORS];
unsigned int position;      //It Is The Position Of Black Or White line In The Track




//QTR-8RC SENSOR Inverted Line Follwing
int Black;                  //inverted signal 




//Motors

int PWM1 = 11;              //left
int DIR1 = 10;              //left
int PWM2 = 13;              //right
int DIR2 = 12;              //right
int maxspeed=50;           //Maximum Speed for the motor 
int medspeed=30;           //Medium Speed for the motor 
int minspeed=10;           //Minimum Speed for the motor 
int stopp=0;               //Stop the motor 



//Green

int io;               //
int mex = 0;          //
int max_num = 0;      //
int max_num2 = 0;     // 
int green_right = 0;  //
int green_left = 0;   //
int i = 0;            //




void setup() 
{
  pinMode(DIR1,OUTPUT);
  pinMode(DIR2,OUTPUT);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);
 
  delay(500);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
    
    for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
   {
      qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
    }
    digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration
  
    // print the calibration minimum values measured when emitters were on
    Serial.begin(9600);
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    
    // print the calibration maximum values measured when emitters were on
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(1000);
}








void loop() 
{

  sensor_read();

  printt();
   if((sensorValues[0]>800 && sensorValues[1]>800 && sensorValues[6]>800 && sensorValues[7]>800)&&( sensorValues[2]<200 || sensorValues[3]<200 || sensorValues[4]<200 || sensorValues[5]<200 ) )  
 {
     Black=1;
     Serial.println("black=1");
}     
   if(Black=1)
     inverted();

   else
   line_following();
}







 void green()//When The Sensor Read An Intersection(All Black) The Robot Go Backward ,When The Sensor See The Last Sensors From Left And Right Are White The Robot Stops And Then  
{            //Read The Max Sensor Value And The 2nd Max Sensor Value And See The 2 Sensors Beside The Max And The 2nd Max Then The Robot Turn To The Direction Of The Bigger Sensor Value    
  Stop ();
  Serial.print("stop");
  while (1)
{
   Backward(minspeed);
   sensor_read();
  if(sensorValues[7]<200 || sensorValues[0]<200)
  break;
}
  Stop();
  sensor_read();
  printt();
  
  for(i=0 ;i<8;i++)
  {
     if(mex<sensorValues2[i])
     {
        mex=sensorValues2[i];
        max_num =i;
     }
  }
  Serial.print("MAX: ");
  Serial.print(mex);
  Serial.print('\t');
  Serial.print("Max_num");
  Serial.print(max_num);
  Serial.print('\t');
  
  if (sensorValues2[max_num+1]>sensorValues2[max_num-1])
  {
    max_num2 = max_num+1;
    green_right = max_num+2;
    green_left = max_num-1;
  }
  else
  {
   max_num2 = max_num-1;
   green_right = max_num+1;
   green_left = max_num-2; 
  }
  Serial.print("Green Right: ");
  Serial.print(green_right);
  Serial.print('\t');
  Serial.print("Green Left: ");
  Serial.print(green_left);
  Serial.print('\t');
  
  if(sensorValues2[green_right]>sensorValues2[green_left])
  {
    Forward(stopp,medspeed);
    Serial.print("RIGHT");
    Serial.print("\n\n\n");
    delay(800);  
  }
  if(sensorValues2[green_right]<sensorValues2[green_left])
  {
    Forward(medspeed, stopp); 
    Serial.print("LEFT");
    Serial.print("\n\n\n");
    delay(800);   
  }
  if(((sensorValues2[green_right]=sensorValues2[green_left]))&&((sensorValues2[green_right]>200)&&(sensorValues2[green_left]>200)))
  {
    Right(medspeed, medspeed);
    delay(2000);
  }
  else
  {
    Forward(medspeed, medspeed);
    delay(700);

  }
  
}








void line_following() //Makes Regular Line Following 
{
    sensor_read();

  printt();
     if(sensorValues[0]>800 && sensorValues[1]>800 && sensorValues[2]>800&& sensorValues[3]>800)
{
   Right(medspeed, medspeed);
  delay(200);
  }
   if((sensorValues[4]>800) && (sensorValues[5]>800) && (sensorValues[6]>800)&& (sensorValues[7]>800))
   {
   Left(medspeed, medspeed);
  delay(200);
  }
   if (((sensorValues[1]>800 && sensorValues[2]>800) && ( sensorValues[0]>800 || sensorValues[3]>800 )) || ( sensorValues[0]>800 || sensorValues[1]>800 )  ) 
  {
  
   Right(medspeed, medspeed);
  delay(100);
  }

   if (((sensorValues[5]>800 && sensorValues[6]>800) && ( sensorValues[4]>800 || sensorValues[7]>800 )) || ( sensorValues[6]>800 || sensorValues[7]>800 )  )  
   
   {
    Left(medspeed, medspeed);
    delay(100);
    }
  if(position>=0&&position<=1000)
   {
    Right(medspeed, medspeed);
    Serial.print("R H");
   }
  if(position>1000&&position<=2000)
   {
    Forward(medspeed, minspeed);
    Serial.print("R M");
   }
  if(position>2000&&position<=3000)
  {
    Forward(maxspeed, medspeed);
    Serial.print("R L");
  }
  if(position>3000&&position<=4000)
   {
    Forward(maxspeed , maxspeed);
    Serial.print("F");
   }
  if(position>4000&&position<=5000)
    {
    Forward(medspeed, maxspeed);
    Serial.print("L L");
    }
  if(position>5000&&position<=6000)
    {
      Forward(minspeed, medspeed);
      Serial.print("L M");
    }
  if(position>6000&&position<=7000)
    { 
      Left(medspeed, medspeed);
      Serial.print("L H");
    }

  if(sensorValues[0]<100 && sensorValues[1]<100 && sensorValues[2]<100 && sensorValues[3]<100 && sensorValues[4]<100 && sensorValues[5]<100 && sensorValues[6]<100 && sensorValues[7]<100 ) 
  Forward(maxspeed , maxspeed);

  if(sensorValues[0]>800 && sensorValues[1]>800 && sensorValues[2]>800 && sensorValues[3]>800 && sensorValues[4]>800 && sensorValues[5]>800 && sensorValues[6]>800 && sensorValues[7]>800 ) 
  {
  Backward(maxspeed);
  delay(100);
  }  
}




void Right(int sped1, int sped2)   //Turn The Robot Right
{
  analogWrite(PWM1,sped1);
  digitalWrite(DIR1,1);
  analogWrite(PWM2,sped2);
  digitalWrite(DIR2,0);
}

void Left(int sped1, int sped2)    //Turn The Robot Left
{
  analogWrite(PWM1,sped1);
  digitalWrite(DIR1,0);
  analogWrite(PWM2,sped2);
  digitalWrite(DIR2,1);
}

void Forward (int sped1, int sped2)//Move The Robot Forward
{
  analogWrite(PWM1,sped1);
  digitalWrite(DIR1,1);
  analogWrite(PWM2,sped2);
  digitalWrite(DIR2,1);
}

void Backward(int sped)           //Move The Robot Backward
{
  analogWrite(PWM1,sped);
  digitalWrite(DIR1,0);
  analogWrite(PWM2,sped);
  digitalWrite(DIR2,0);
}

void Stop ()                      //Stop The Robot
{
  analogWrite(PWM1,0);
  digitalWrite(DIR1,0);
  analogWrite(PWM2,0);
  digitalWrite(DIR2,0);
}




void printt() //Print Sensors Values
{
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
       Serial.print("Pos: ");
       Serial.print(position); 
    Serial.println("");

   for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues2[i]);
    Serial.print('\t');
    
  }
    Serial.println("");
   
}

void inverted_sensor_read() 
{
  position = qtrrc.readLine(sensorValues, QTR_EMITTERS_ON,1);        // To get Inverted Calibarted sensor values
}
void sensor_read()
{
  position = qtrrc.readLine(sensorValues);        // To get Calibarted sensor values
 qtrrc.read(sensorValues2);                      // To get Uncalibrated (raw) sensor values
}






void inverted()//Makes Inverted Line Following 
{
    inverted_sensor_read();
      printt();
    
 if(sensorValues[0]<200 && sensorValues[1]<200 && sensorValues[2]<200&& sensorValues[3]<200)
{
   Right(medspeed, medspeed);
  delay(200);
  }
   if((sensorValues[4]<200) && (sensorValues[5]<200) && (sensorValues[6]<200)&& (sensorValues[7]<200))
   {
   Left(medspeed, medspeed);
  delay(200);
  }
   if (((sensorValues[1]<200 && sensorValues[2]<200) && ( sensorValues[0]<200 || sensorValues[3]<200 )) || ( sensorValues[0]<200 || sensorValues[1]<200 )  ) 
  {
  
   Right(medspeed, medspeed);
  delay(100);
  }

   if (((sensorValues[5]<200 && sensorValues[6]<200) && ( sensorValues[4]<200 || sensorValues[7]<200 )) || ( sensorValues[6]<200 || sensorValues[7]<200 )  )  
    {
    Left(medspeed, medspeed);
    delay(100);
    }
    else
    {
if(position>=0&&position<=1000)
   {
    Right(medspeed, medspeed);
    Serial.print("R H");
   }
  if(position>1000&&position<=2000)
   {
    Forward(medspeed, minspeed);
    Serial.print("R M");
   }
  if(position>2000&&position<=3000)
  {
    Forward(maxspeed, medspeed);
    Serial.print("R L");
  }
  if(position>3000&&position<=4000)
   {
    Forward(maxspeed , maxspeed);
    Serial.print("F");
   }
  if(position>4000&&position<=5000)
    {
    Forward(medspeed, maxspeed);
    Serial.print("L L");
    }
  if(position>5000&&position<=6000)
    {
      Forward(minspeed, medspeed);
      Serial.print("L M");
    }
  if(position>6000&&position<=7000)
    { 
      Left(medspeed, medspeed);
      Serial.print("L H");
    }


Serial.println("inverted");
   if((sensorValues[0]<200 && sensorValues[1]<200 && sensorValues[6]<200 && sensorValues[7]<200)&&( sensorValues[2]>800 || sensorValues[3]>800 || sensorValues[4]>800 || sensorValues[5]>800 ) )  
  {  
   Black=0;
   Serial.println("black=0");
  }
   
}
Forward(medspeed, medspeed);
delay(300);
}




void Ultrasonic()//still working on it
{
}




void Evacuation_Zone()//still working on it
{
}
