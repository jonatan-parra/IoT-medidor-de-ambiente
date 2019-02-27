/*** Librerías  ***/
#include <DHT.h> // Librería sensor de temperatura
#include <LiquidCrystal_I2C.h> // Librería del display LCD


/*** DHT11 ***/
#define DHTPIN 2      // Definimos el pin digital donde se conecta el sensor
#define DHTTYPE DHT11 // Dependiendo del tipo de sensor
DHT dht(DHTPIN, DHTTYPE); // Inicializamos el sensor DHT11

/*** Display LCD ***/
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

/*** Wifi ***/


/*** Sensor de ruido ***/
int soundPin = A0;


/*** Sensor de luminosidad ***/



void setup(){

  /*** Se inicializa el display LCD  ***/
  lcd.init();  
  lcd.backlight();

  /*** Se inicializa el sensor de temperatura y humedad  ***/
  Serial.begin(9600);  // inicializa comunicación serie con el DHT11 y el sensor de ruido
  dht.begin();        // Comienza el sensor DHT

  /*** Se inicializa el módulo WIFI  ***/


  /*** Se inicializa el sensor de ruido ***/

  
  /*** Se inicializa el sensor de luminosidad ***/

  
}


void loop(){
  delay(1000); // Se esperan 1 segundo entre medidas
  
  /*** Medición de temperatura, humedad y sensación termica ***/
  medir_temperatura_humedad();

  /*** Medición de ruido ***/
  medir_ruido();

  /*** Medición de luminosidad ***/
  medir_luminosidad();

  /** Wifi ***/
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
    return;
  }
   
  float hif = dht.computeHeatIndex(f, h); // Calcular el índice de calor/sensación termica en Fahreheit
  float hic = dht.computeHeatIndex(t, h, false); // Calcular el índice de calor/sensación termica en grados centígrados
  /*
  Serial.print("Humedad: ");  Serial.print(h);
  Serial.print(" %\t"); Serial.print("Temperatura: ");
  Serial.print(t);  Serial.print(" *C ");
  Serial.print(f);  Serial.print(" *F\t");
  Serial.print("Índice de calor: ");  
  Serial.print(hic);  Serial.print(" *C ");
  Serial.print(hif);  Serial.println(" *F"); */

  /*** Mostrar en Display ***/
  lcd.setCursor(0,1); // Humedad  // Segundo reglón
  lcd.print("H:");  
  lcd.print(h);

  lcd.setCursor(8,1); // Temperatura, centigrados
  lcd.print("T:"); 
  lcd.print(t);

  return 0;
}


double medir_ruido(){
  int value = analogRead(soundPin);
  if (value > 340){
    Serial.println("Está hablando muy alto ");
    Serial.println(value);
  } else {
    Serial.println(value);
  }

  /*** Mostrar en Display ***/
  lcd.setCursor(0,0);  // Primer reglón
  lcd.print("Ruido:");
  lcd.print(value);
  return value;
}
