#include <SparkFunESP8266WiFi_KMU.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <PMS.h>
#include <Adafruit_BME280_KMU.h>
#include "MutichannelGasSensor.h"

#define WAIT (30000) //30second
#define DEBUG // 주석시 시리얼출력 없음.

//define dust
SoftwareSerial Serial_dust(10, 11);
PMS Pms(Serial_dust);
PMS::DATA Data;


unsigned int _pm1_0 = 0; //pm1.0
unsigned int _pm2_5 = 0; //pm2.5
unsigned int _pm10 = 0;  //pm10

//define temp
Adafruit_BME280 Bme; // I2C

float _temperature = 0.00f;
float _humidity = 0.00f;
float _pressure = 0.00f;

//define co2
int co2_sig = A2; int co2_analog=0; 
float co2_volt = 0; float co2_conc=0;

float analog2mV (float volt, int analog);


void setup() {
  // put your setup code here, to run once:
    pinMode(LED_BUILTIN, OUTPUT);

#ifdef DEBUG
    Serial.begin(9600);
#endif

    dust_init();
    bme_init();
    //gas_init();
    gas_in();


#ifdef DEBUG
  Serial.println("ssssstarttttt");
  
#endif

    delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  read_co2();
  read_bme();
  read_dust();
  read_gas();
  

#ifdef DEBUG
    Serial.println(F("---------------------"));
#endif

    delay(WAIT);
  
}
//gas sensor
void gas_in(){
      Serial.begin(9600);  // start serial for output
    gas.begin();//the default I2C address of the slave is 0x04
    gas.powerOn();
}
void gas_init(){
    Serial.begin(9600);  // start serial for output
    gas.begin(0x04);//the default I2C address of the slave is 0x04
    gas.powerOn();

}
void read_gas(){
    float c;
    float nh3;
    float co;
    float no2;
    float ch4;
    float h2;

    float c3h8;
    float c4h10;
    float c2h5oh;
    

    nh3 = gas.measure_NH3();
    Serial.print("NH3 : ");
    if(nh3>=0) Serial.print(nh3);
    else Serial.print("invalid");
    Serial.println(" ppm");

    co = gas.measure_CO();
    Serial.print("CO : ");
    if(co>=0) Serial.print(co);
    else Serial.print("invalid");
    Serial.println(" ppm");

    no2 = gas.measure_NO2();
    Serial.print("NO2 : ");
    if(no2>=0) Serial.print(no2);
    else Serial.print("invalid");
    Serial.println(" ppm");

    h2 = gas.measure_H2();
    Serial.print("H2 : ");
    if(h2>=0) Serial.print(h2);
    else Serial.print("invalid");
    Serial.println(" ppm");


    c2h5oh = gas.measure_C2H5OH();
    Serial.print("C2H5OH : ");
    if(c2h5oh>=0) Serial.print(c2h5oh);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c3h8 = gas.measure_C3H8();
    Serial.print("C3H8 : ");
    if(c3h8>=0) Serial.print(c3h8);
    else Serial.print("invalid");
    Serial.println(" ppm");

    c4h10 = gas.measure_C4H10();
    Serial.print("C4H10 : ");
    if(c4h10>=0) Serial.print(c4h10);
    else Serial.print("invalid");
    Serial.println(" ppm");

    ch4 = gas.measure_CH4();
    Serial.print("CH4 : ");
    if(ch4>=0) Serial.print(ch4);
    else Serial.print("invalid");
    Serial.println(" ppm");
}

//co2
void read_co2(){
  co2_analog = 0;
  int test_analog=0;
  for(int i =0; i< 32; i++){
    co2_analog += analogRead(co2_sig);
  }
  co2_volt = analog2mV(5.0, co2_analog>>5);
  co2_conc = co2_volt * 0.4;
  Serial.print("CO2 : ");
  Serial.print(co2_volt);
  Serial.print("  mV    ");
  Serial.print(co2_conc);
  Serial.println("    ppm");
  
}
float analog2mV(float volt, int analog) {
  return analog*volt*1000/1023.0;
}

//dust
void dust_init()
{
    Serial_dust.begin(9600);
    Serial_dust.listen();
    Pms.passiveMode(); // Switch to passive mode
    Pms.wakeUp();
}
void read_dust()
{
    Serial_dust.listen();
    Pms.requestRead();
    if (Pms.readUntil(Data))
    {
        _pm1_0 = Data.PM_SP_UG_1_0;
        _pm2_5 = Data.PM_SP_UG_2_5;
        _pm10 = Data.PM_SP_UG_10_0;
#ifdef DEBUG
        Serial.print(F("PM 1.0 (ug/m3)SP: "));
        Serial.println(Data.PM_SP_UG_1_0);

        Serial.print(F("PM 2.5 (ug/m3)SP: "));
        Serial.println(Data.PM_SP_UG_2_5);

        Serial.print(F("PM 10.0 (ug/m3)SP: "));
        Serial.println(Data.PM_SP_UG_10_0);

#endif
    }
    else
    {
        _pm1_0 = 0;
        _pm2_5 = 0;
        _pm10 = 0;
#ifdef DEBUG
        Serial.println(F("PMS No data."));
#endif
    }
}


//void bms
void bme_init()
{
  Bme.begin();
}

void read_bme()
{
  _temperature = Bme.readTemperature();
  _humidity = Bme.readHumidity();
  _pressure = (Bme.readPressure() / 100.0F);

#ifdef DEBUG
    Serial.print(F("Temperature: "));
    Serial.print(Bme.readTemperature());
    Serial.println(" *C");
    Serial.print(F("Pressure: "));
    Serial.print(Bme.readPressure() / 100.0F);
    Serial.println(F(" hPa"));
    Serial.print(F("Humidity: "));
    Serial.print(Bme.readHumidity());
    Serial.println(F(" %"));
#endif

}
