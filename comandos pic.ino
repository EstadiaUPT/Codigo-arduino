#include "BluetoothSerial.h"
#include "ELMduino.h"

BluetoothSerial SerialBT;
#define ELM_PORT   SerialBT
#define DEBUG_PORT Serial

//String MACadd = "DC:0D:30:48:8D:60";          //enter the ELM327 MAC address
uint8_t address[6]  = {0xDC, 0x0D, 0x30, 0x48, 0x8D, 0x60}; 

ELM327 myELM327;

/*
1. reset 
2. leer la bateria
3. leer las rpm sin parar 
4. temperatura del refrigerante
5. leer km/h
6. averias
7. tipo de averia
8. borrar averia
*/

/*
1. RPM uint32_t rpm = 0;
2. Bateria uint32_t engineLoad = 0;
3. Temperatura del refigerante uint32_t engineCoolantTemp = 0;
4. Velocidad kp/h uint32_t kph = 0;
5. Estado del sistema del combustible
6. Tipo de averias
7. borrado de averiarias
*/

uint32_t rpm = 0;
uint32_t engineLoad = 0;
uint32_t engineCoolantTemp = 0;
uint32_t kph = 0;
uint16_t fuelSystemStatus = 0;
uint32_t monitorStatus = 0;
uint32_t throttle = 0;
uint32_t obd = 0;
uint32_t fuelLevel = 0;
uint32_t oilTemp = 0;

void setup() {
  
 #if LED_BUILTIN
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
#endif

DEBUG_PORT.begin(115200);
  //SerialBT.setPin("1234");
  ELM_PORT.begin("ArduHUD", true);
  
if (!ELM_PORT.connect(address))            //"OBDII" replaced by "address"
  {
    DEBUG_PORT.println("No se puede conectar al escaner OBC - Fase 1");
    while (1);
  }

  if (!myELM327.begin(ELM_PORT))
  {
    Serial.println("No se puede conectar al escaner OBD - Fase 2");
    while (1);
  }

  Serial.println("Connected to ELM327");  
}

void loop() {
  while(false){
    Serial.println("");
    delay(2000);     
  }   
//lectura de sensores
  float TempRPM = myELM327.rpm();
  if(myELM327.status == ELM_SUCCESS){
    rpm = (uint32_t)TempRPM;
    Serial.print("RPM: "); Serial.println(rpm);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }
  float TempEngineLoad = myELM327.engineLoad();
  if(myELM327.status == ELM_SUCCESS){
    engineLoad = (uint32_t)TempEngineLoad;
    Serial.print("Carga del motor: "); Serial.println(engineLoad);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }
  float TempCoolant = myELM327.engineCoolantTemp();
  if(myELM327.status == ELM_SUCCESS){
    tempCoolant = (uint32_t)TempCoolant;
    Serial.print("Temperatura del refigerante: "); Serial.println(tempCoolant);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }  
  float Speed = myELM327.kph();
  if(myELM327.status == ELM_SUCCESS){
    Kph = (uint32_t)Speed;
    Serial.print("KP/H: "); Serial.println(Kph);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }   
  float FuelSystem = myELM327.fuelSystemStatus();
  if(myELM327.status == ELM_SUCCESS){
    fuelSystem = (uint32_t)FuelSystem;
    Serial.print("Estado del sistema de combustible: "); Serial.println(fuelSystem);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }
  float Monitor = myELM327.monitorStatus();
  if(myELM327.status == ELM_SUCCESS){
    monitor = (uint32_t)Monitor;
    Serial.print("monitorear el estado: "); Serial.println(monitor);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }
  float Throttlee = myELM327.throttle();
  if(myELM327.status == ELM_SUCCESS){
    throttlee = (uint32_t)Throttlee;
    Serial.print("Acelerador: "); Serial.println(throttlee);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }  
  float OBD = myELM327.obd();
  if(myELM327.status == ELM_SUCCESS){
    Obd = (uint32_t)OBD;
    Serial.print("Estándares obd:"); Serial.println(Obd);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }
  float Level = myELM327.fuelLevel();
  if(myELM327.status == ELM_SUCCESS){
    level = (uint32_t)Level;
    Serial.print("Nivel de combustible:"); Serial.println(level);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }
  float Oil = myELM327.oilTemp();
  if(myELM327.status == ELM_SUCCESS){
    oil = (uint32_t)Oil;
    Serial.print("Temperatura del aceite:"); Serial.println(oil);    
  }else{
    Serial.print(F("\tERROR: "));
    Serial.println(myELM327.status);
    myELM327.printError();
    delay(100); 
  }
}
