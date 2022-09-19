

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#define EXCLUDE_EXOTIC_PROTOCOLS  // Saves around 240 bytes program memory if IrSender.write is used
//#define SEND_PWM_BY_TIMER         // Disable carrier PWM generation in software and use (restricted) hardware PWM.
//#define USE_NO_SEND_PWM           // Use no carrier PWM, just simulate an active low receiver signal. Overrides SEND_PWM_BY_TIMER definition
//#define NO_LED_FEEDBACK_CODE      // Saves 566 bytes program memory
//#define USE_OPEN_DRAIN_OUTPUT_FOR_SEND_PIN // Use or simulate open drain output mode at send pin. Attention, active state of open drain is LOW, so connect the send LED between positive supply and send pin!

#include "PinDefinitionsAndMore.h"  // Define macros for input and output pin etc.
#include <IRremote.hpp>

// Definir constantes
#define ANCHO_PANTALLA 128 // ancho pantalla OLED
#define ALTO_PANTALLA 32 // alto pantalla OLED

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

int LED_PIN = 4;

void setup() {
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(LED_PIN, OUTPUT);// Led para indicar
    Serial.begin(115200);

#if defined(__AVR_ATmega32U4__) || defined(SERIAL_PORT_USBVIRTUAL) || defined(SERIAL_USB) /*stm32duino*/|| defined(USBCON) /*STM32_stm32*/|| defined(SERIALUSB_PID) || defined(ARDUINO_attiny3217)
    delay(4000); // To be able to connect Serial monitor after reset or power up and before first print out. Do not wait for an attached Serial Monitor!
#endif
    // Just to know which program is running on my Arduino
    //Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

#if defined(IR_SEND_PIN)
    IrSender.begin(); // Start with IR_SEND_PIN as send pin and enable feedback LED at default feedback LED pin
#else
    IrSender.begin(3, ENABLE_LED_FEEDBACK); // Specify send pin and enable feedback LED at default feedback LED pin
#endif

//#if defined(IR_SEND_PIN)
//    Serial.println(F("Ready to send IR signals at pin " STR(IR_SEND_PIN)));
//#else
//    Serial.println(F("Ready to send IR signals at pin 3"));
//#endif

//#if !defined(SEND_PWM_BY_TIMER)
    /*
     * Print internal signal generation info
     */
//    IrSender.enableIROut(38); // Call it with 38 kHz to initialize the values printed below
//    Serial.print(F("Send signal mark duration is "));
//    Serial.print(IrSender.periodOnTimeMicros);
//    Serial.print(F(" us, pulse correction is "));
//    Serial.print(IrSender.getPulseCorrectionNanos());
//    Serial.print(F(" ns, total period is "));
//    Serial.print(IrSender.periodTimeMicros);
//    Serial.println(F(" us"));
//#endif

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
  display.println("Controller");
  display.setCursor(0, 17);
  // Escribir texto
  display.println(" Martinez");
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
  display.println("Apunta al dispocitivo");
  display.setCursor(0, 10);
  // Escribir texto
  display.println("      TV o AIRE");
  display.setCursor(0, 25);
  // Escribir texto
  display.println("  Presiona una tecla.");
  // Enviar a pantalla
  display.display();
  //*--------------Fin mensaje inicio OLED ----------------------- *//

}

/*
 * Set up the data to be sent.
 * For most protocols, the data is build up with a constant 8 (or 16 byte) address
 * and a variable 8 bit command.
 * There are exceptions like Sony and Denon, which have 5 bit address.
 */

void loop() {
  
  if(digitalRead(5)){ // ON 
    
    IrSender.sendNEC(284158740, 32);  //just remove my remote code and add your                                          //remote hex value
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("SENDING: ");
    display.setTextSize(2);
    display.setCursor(0, 18);
    display.println("ON/OFF");
    display.display();
    for(uint8_t i = 0; i < 6; i++)
    {
      digitalWrite(LED_PIN, HIGH);
      delay(30);
      digitalWrite(LED_PIN, LOW);
      delay(30);
    }
    delay(500);
  }
  else if(digitalRead(6)){ // UP 
    
    IrSender.sendNEC(284099070, 32);  //just remove my remote code and add your                                          //remote hex value
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("SENDING: ");
    display.setTextSize(2);
    display.setCursor(0, 18);
    display.println("UP");
    display.display();
    for(uint8_t i = 0; i < 6; i++)
    {
      digitalWrite(LED_PIN, HIGH);
      delay(30);
      digitalWrite(LED_PIN, LOW);
      delay(30);
    }
    delay(500);
  }
  else if(digitalRead(7)){ // DOWN 
    
    IrSender.sendNEC(284127630, 32);  //just remove my remote code and add your                                          //remote hex value
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("SENDING: ");
    display.setTextSize(2);
    display.setCursor(0, 18);
    display.println("DOWN");
    display.display();
    for(uint8_t i = 0; i < 6; i++)
    {
      digitalWrite(LED_PIN, HIGH);
      delay(30);
      digitalWrite(LED_PIN, LOW);
      delay(30);
    }
    delay(500);
  }

}
// aire mirage
// ON/OFF(32 bits)Decoded NEC: 80FF48B7 (HEX) , 10000000111111110100100010110111 (BIN)
// Subir (32 bits)Decoded NEC: 80FF58A7 (HEX) , 10000000111111110101100010100111 (BIN)
// Bajar (32 bits)Decoded NEC: 80FFC837 (HEX) , 10000000111111111100100000110111 (BIN)

// TV Mitsui
//(32 bits)Decoded NEC: 10EFEB14 (HEX) , 10000111011111110101100010100 (BIN) 
