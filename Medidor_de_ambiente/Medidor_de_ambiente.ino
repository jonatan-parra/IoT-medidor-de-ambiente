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



/*** Sensor de luminosidad ***/



void setup(){

  /*** Se inicializa el display LCD  ***/
  lcd.init();  
  lcd.backlight();

  /*** Se inicializa el sensor de temperatura y humedad  ***/
  Serial.begin(9600);  // inicializa comunicación serie con el DHT11
  dht.begin();        // Comienza el sensor DHT

  /*** Se inicializa el módulo WIFI  ***/


  /*** Se inicializa el sensor de ruido ***/

  
  /*** Se inicializa el sensor de luminosidad ***/

  
}


void loop(){

  // Se esperan 2 segundos entre medidas
  delay(2000);

  /*** Medición del DHT11 ***/
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


  /*** Medición de ruido ***/


  /*** Medición de luminosidad ***/


  /*** Mostrar en Display ***/
  // Primer reglón
  lcd.setCursor(0,0); 
  lcd.print("Ruido:");
  lcd.print("xx");

  // Segundo reglón
  lcd.setCursor(0,1); // Humedad
  lcd.print("H:");  
  lcd.setCursor(2,1);
  lcd.print(h);

  lcd.setCursor(8,1); // Temperatura, centigrados
  lcd.print("T:"); 
  lcd.setCursor(10,1);
  lcd.print(t);

  
}
