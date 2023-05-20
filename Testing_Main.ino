
#include <WiFi.h>
#include "ThingSpeak.h"
#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <BH1750.h>
#define ONE_WIRE_BUS_1 32
#define ANALOG_V_IN_PIN 34
#define switch_1 33
#define switch_2 25
#define switch_3 26
#define led 2
#define cu_senor_in 35

// switch 
int  switch_1_status=3;
int  switch_2_status=3;
int  switch_3_status=3;


//voltage
float adc_voltage=0;
float adc_value=0;
float R1=0;
float R2=0; 
float ref_voltage=0;
float adc_value_err=0;
float adc_value_err_sq=0;
float adc_value_err_cube=0;
float adc_value_err_d4=0;
float in_voltage=0;

//current
float cur_sen_vout = 0;
float cur_sen = 0;
float cur_sen1 = 0;
float Current=0;
float actualvoltage=0; 
float Current1=0;
float cur_sen_vout_er =0;
float cur_sen_vout_er_1 =0; 
float cur_sen_vout_er_sq=0; 
float cur_sen_vout_er_cube=0;
float cur_sen_vout_er_d4=0;
float ref_volt_for_current=0; 

//temp 
float temperature=0;

//irrad
float lux_err=0;
float lux=0;
float irrad=0;
float irrad_err=0;
float irrad_err_sqr=0;
float irrad_err_cube=0;
float irrad_err_1=0;

//wifi
const char ssid[] = "Redmi note 8 pro";  //  network SSID
const char pass[] = "Anigoku18";   // network password   

//thingspeak channel id
unsigned long ChannelNumber1 =1564083;            // voltage Channel ID
unsigned long ChannelNumber2 =1572100;            // current Channel ID
unsigned long ChannelNumber3 =1742629;            // tempture Channel ID
unsigned long ChannelNumber4 =1742630;            // irradition Channel ID

//write api key
const char * myWriteAPIKey1 ="MKDC8O6DCCJW7JOW";// voltage
const char * myWriteAPIKey2 ="CAECGM5KEQCNQH7L";// current
const char * myWriteAPIKey3 ="YQKV5NFTZ2IECTJ4";// tempeture
const char * myWriteAPIKey4 ="3GPMLWA6A52D0UDT";// irradition

 




OneWire oneWire_in(ONE_WIRE_BUS_1);
DallasTemperature temp_sensor(&oneWire_in);
BH1750 lightMeter;   //pin connection of lux meter - sda=21 ,scl=22.
WiFiClient  client;
unsigned long timerDelay = 10000;


void setup() 
{
  
 //initializaion
  
  Serial.begin(115200);     //Initialize serial
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
  Wire.begin();
  temp_sensor.begin();
  lightMeter.begin();
  pinMode(switch_1,INPUT);
  pinMode(switch_2,INPUT);
  pinMode(switch_3,INPUT);
  pinMode(led,OUTPUT);
  delay(1000);
   
 } 
      

void loop()
{

if (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(led,LOW);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
    digitalWrite(led,HIGH);
  }

// voltage


 for(int i = 0; i < 1000; i++) 
  {
    adc_value_err=analogRead(ANALOG_V_IN_PIN);  
    delay(10);
  }
  adc_value_err=adc_value_err/1000;
  adc_value_err_sq=adc_value_err*adc_value_err;
  adc_value_err_cube=adc_value_err_sq*adc_value_err;
  adc_value_err_d4=adc_value_err_sq*adc_value_err_sq;
  adc_value=(55.85*adc_value_err_d4-321.4*adc_value_err_cube+622.2*adc_value_err_sq+759.5*adc_value_err-27.49);
  
  if(adc_value<0)
  {
    adc_value=0;
  }
  
  adc_voltage=(adc_value*3.3) / 4095.0; 
  

switch_1_status=digitalRead(switch_1);
switch_2_status=digitalRead(switch_2);
switch_3_status=digitalRead(switch_3);
 
 
 if((switch_1_status==0) && (switch_2_status==0))
 {
  R1=46600 ;
  R2=12000 ;
 }
 if((switch_1_status==1) && (switch_2_status==0))
 {
  R1=26800 ;
  R2=3200 ;
 }
 if((switch_1_status==0) && (switch_2_status==1))
 {
  R1=120000 ;
  R2=12000 ;
 }
in_voltage=adc_voltage/(R2/(R1+R2)); 
Serial.print(switch_1_status);
Serial.println( "-----1w");
Serial.print(switch_2_status);
Serial.println("------2w");
Serial.print(R1);
Serial.println("------r1");
Serial.print(R2);
Serial.println("------r2");  
 
Serial.print("Voltage=");
Serial.println(in_voltage);
Serial.println("-----------------------");
   
   //temp  
   
   
   
   temp_sensor.requestTemperatures();
   temperature=temp_sensor.getTempCByIndex(0);
   if(temperature<=0)
   {
    temperature=0;
   }
   Serial.print("temperature= ");
   Serial.print(temperature);
   Serial.println("°c");
   Serial.println("-----------------------");
  
    
    
    //current
 
 for(int i = 0; i < 1000; i++) 
  {
  cur_sen_vout=analogRead(cu_senor_in); 
  delay(10);
  }
  cur_sen=(cur_sen_vout*3.3)/1023.0;
  actualvoltage= (cur_sen-1.65);
  Current=actualvoltage/0.185;
  
 if(Current <0)
 {
  Serial.println("-------------");
  Serial.println("Inter change the terminals of current sensor"); 
  Serial.println("-------------"); 
 }
 if(Current <=0)
 {
  Current=0;
 }

Serial.print(cur_sen);
Serial.println("-----volts"); 
Serial.print(cur_sen_vout );
Serial.println("----adc cal" );
Serial.print(Current);
Serial.println("----amp");
Serial.println("-------------------------");

 
//irradition
  
lux_err =lightMeter.readLightLevel();
lux=lux_err*1.725;
irrad_err=lux*0.0079;
irrad_err_sqr=irrad_err*irrad_err;
irrad_err_cube=irrad_err_sqr*irrad_err;
//irrad=1.277E-6*irrad_err_cube-0.001496*irrad_err_sqr+1.695*irrad_err+27.68;

irrad=1.207E-6*irrad_err_cube-0.001402*irrad_err_sqr+1.66*irrad_err+30.54; //
if(irrad_err<0)
{
  irrad=0;
}
Serial.print(irrad);
Serial.println("----W/m^2");
Serial.println("**************************");    
    
// upload the data  
   
 ThingSpeak.writeField(ChannelNumber1,1,in_voltage,myWriteAPIKey1);

 ThingSpeak.writeField(ChannelNumber2,1,Current,myWriteAPIKey2);
   
 ThingSpeak.writeField(ChannelNumber3,1,temperature,myWriteAPIKey3);
 
 ThingSpeak.writeField(ChannelNumber4,1,irrad,myWriteAPIKey4);
 //delay(15000);
  }
