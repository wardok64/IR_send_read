/*
 * Programa final arduino nano old bootloader
 * decodificador de control remoto con OLED
 * sep 18 22
 */
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <IRremote.h> 

// Definir constantes
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 32 // alto pantalla OLED
 
// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

int RECV_PIN = 2;// pin donde se conecta la entrada del IR reader
int LED_PIN = 4; // led para indicar cuando entra un dato

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
  pinMode(LED_PIN, OUTPUT);// Led para indicar datos entrada

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) 
  {
     while (true);
  }
  
  //*--------------Mensaje inicio a la OLED ----------------------- *//
  display.clearDisplay();
  // Tamaño del texto
  display.setTextSize(2);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  display.setCursor(0, 0);
  // Escribir texto
  display.println("  Decoder ");
  display.setCursor(0, 17);
  // Escribir texto
  display.println(" Martinez ");
  // Enviar a pantalla
  display.display();
  
  delay(5000);

  display.clearDisplay();
  // Tamaño del texto
  display.setTextSize(1);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  display.setCursor(0, 0);
  // Escribir texto
  display.println("Coloca control frente");
  display.setCursor(0, 10);
  // Escribir texto
  display.println("a IR.");
  display.setCursor(0, 25);
  // Escribir texto
  display.println("  Presiona una tecla.");
  // Enviar a pantalla
  display.display();
  //*--------------Fin mensaje inicio OLED ----------------------- *//

   irrecv.enableIRIn(); // Empezamos la recepción  por IR
}


void dump(decode_results *results) 
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.println(" Wait...");
  display.setTextSize(1);
  display.setCursor(0, 20);
  display.println("   Decoding");
  display.display();
  
  for(uint8_t i = 0; i < 6; i++)
  {
    digitalWrite(LED_PIN, HIGH);
    delay(30);
    digitalWrite(LED_PIN, LOW);
    delay(30);
  }
  
  delay(700);
  /* Proceso de decodificacion   */
  if (results->decode_type == UNKNOWN) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Unknown enc: ");
  }
  else if (results->decode_type == NEC) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("NEC: ");
  }
  else if (results->decode_type == SONY) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Decoded SONY: ");
  }
  else if (results->decode_type == RC5) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("RC5: ");
  }
  else if (results->decode_type == RC6) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("RC6: ");
  }
  else if (results->decode_type == PANASONIC) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Panasonic: ");
    display.setCursor(0, 8);
    display.println(results->address, HEX);
  }
  else if (results->decode_type == LG) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("LG: ");
  }
  else if (results->decode_type == JVC) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("JVC: ");
  }
//  else if (results->decode_type == AIWA_RC_T501) 
//  {
//    display.clearDisplay();
//    display.setTextSize(1);
//    display.setCursor(0, 0);
//    display.println("AIWA RC T501: ");
//  }
  else if (results->decode_type == WHYNTER) 
  {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("WHYNTER: ");
  }
  
  display.setTextSize(2);
  display.setCursor(0, 18);
  display.println(results->value, HEX);
  display.display();
}

void loop() {
  if (irrecv.decode(&results)) 
  {
    dump(&results);
    irrecv.resume(); // empezamos una nueva recepción
  }
  delay(300);
}
