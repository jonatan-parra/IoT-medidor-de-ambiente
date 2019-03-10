/*** Librerías  ***/
#include <DHT.h> // Librería sensor de temperatura
#include <LiquidCrystal_I2C.h> // Librería del display LCD
#include <SoftwareSerial.h>


/*** DHT11 ***/
#define DHTPIN 2      // Definimos el pin digital donde se conecta el sensor
#define DHTTYPE DHT11 // Dependiendo del tipo de sensor
DHT dht(DHTPIN, DHTTYPE); // Inicializamos el sensor DHT11

/*** Display LCD ***/
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

SoftwareSerial mySerial(3, 4); // RX TX

const char CR = 13;

/*** Wifi ***/


/*** Sensor de ruido ***/
int soundPin = A0;
const int inputWindow = 100;
unsigned int inputSample;
int ruido = 0;

/*** Sensor de luminosidad ***/

/*** Sensor de temperatura y humedad ***/
float temperatura = 0;
float humedad = 0;


void setup(){

  /*** Se inicializa el display LCD  ***/
  lcd.begin();  
  lcd.backlight();

  pinMode(soundPin, INPUT);

  /*** Se inicializa el sensor de temperatura y humedad  ***/
  Serial.begin(115200);  // inicializa comunicación serie con el DHT11 y el sensor de ruido
  mySerial.begin(115200);
  dht.begin();        // Comienza el sensor DHT

  /*** Se inicializa el módulo WIFI  ***/


  /*** Se inicializa el sensor de ruido ***/

  
  /*** Se inicializa el sensor de luminosidad ***/

  
}


void loop(){
//  delay(50); // Se esperan 1 segundo entre medidas
  
  /*** Medición de temperatura, humedad y sensación termica ***/
  medir_temperatura_humedad();

  /*** Medición de ruido ***/
  medir_ruido();

  /*** Medición de luminosidad ***/
  medir_luminosidad();

  /** Wifi ***/

  if(temperatura >= 0 && ruido >= 0 && humedad >= 0){
    String hum = String(humedad);
    String temp = String(temperatura);
    String ru = String(ruido);
    String JSON = String("<{\"noise\": \"" + ru + "\",\"humidity\": \"" + hum + "\",\"temperature\": \"" + temp + "\"}>");

    for (int i = 0; i < JSON.length(); i++){
      mySerial.write(JSON[i]);   // Push each char 1 by 1 on each loop pass
    }
    mySerial.write("\n");
    Serial.println(JSON);
  }
}

double medir_luminosidad(){
  
}

double medir_temperatura_humedad(){
  float h = dht.readHumidity(); // Se lee la humedad relativa  
  float t = dht.readTemperature(); // Se lee la temperatura en grados centígrados (por defecto)
  float f = dht.readTemperature(true); // Se lee la temperatura en grados Fahreheit
 
  // Comprobamos si ha habido algún error en la lectura
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return -1;
  }
   
  float hif = dht.computeHeatIndex(f, h); // Calcular el índice de calor/sensación termica en Fahreheit
  float hic = dht.computeHeatIndex(t, h, false); // Calcular el índice de calor/sensación termica en grados centígrados

  /*** Mostrar en Display ***/
  lcd.setCursor(0,1); // Humedad  // Segundo reglón
  lcd.print("H:");  
  lcd.print(h);

  lcd.setCursor(8,1); // Temperatura, centigrados
  lcd.print("T:"); 
  lcd.print(t);

  temperatura = t;
  humedad = h;

  return 0;
}

double medir_ruido(){

  unsigned int inputMax = 0;
  unsigned int inputMin = 1024;

  // loop for the window
  for (unsigned int i = 0; i < inputWindow; i++) {
    // read in a single value
    inputSample = analogRead(soundPin);
    // get the minimum and maximum value
    inputMin = min(inputMin, inputSample);
    inputMax = max(inputMax, inputSample);
  }
  
  int value = analogRead(soundPin);
  ruido = inputMax-inputMin;

  if(ruido > 50){
    lcd.setCursor(0,0);  // Primer reglón
    lcd.print("SILENCIO  ");
    delay(3000);
  }
  else{
    lcd.setCursor(9,0);
    lcd.print("  ");
    lcd.setCursor(0,0);  // Primer reglón
    lcd.print("Ruido:");
    lcd.print(ruido);
  }
  return value;
}
