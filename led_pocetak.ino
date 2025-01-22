#include <FastLED.h>      // Biblioteka koju koristimo za kontrolu ledovki
#define LED_PIN     7      // Pin na kome su ledovke
#define NUM_LEDS    52      // Broj ledovki
CRGB leds[NUM_LEDS];

int i;      // Koristimo za crvene ledovke
int f;      // Koristimo za plave ledovke
int g = 1;      // Koristimo da bi znali kada tajmer treba da pocne da odbrojava, takodje
int k = 1;      // kao da bi znali kada treba resetovati pozicuju ledovki
const int Button = 3;      // Deklarisanje pin-a tastera
const int Button1 = 2;      // Deklarisanje pin-a tastera
byte ButtonState;
byte lastState = LOW;
byte ButtonState1;
byte lastState1 = LOW;
int period = 10000;      // Period je vremenski maksimalno trajanje jedne partije
unsigned long time_now = 0;      // Koristimo za racunanje proteklog vremena

int n = 26;      // Broj koji ce se povecavati ili smanjivati u odnosu na to koja strana vodi
                 // 26 je neutralna pozicija posto postoje 52 diode

void setup() {
  Serial.begin(9600);
  Serial.println(n);      // Bilo je korisceno da se vidi da li sve radi kako treba
  pinMode(Button, INPUT);
  pinMode(Button1, INPUT);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  for(i = 0; i < 25; i++)
  {
  leds[i] = CRGB(255, 0, 0);
  FastLED.show();
  Serial.println("Loop still going..");      // Bilo je korisceno da se vidi da li sve radi kako treba
  }
  Serial.println(n);      // Bilo je korisceno da se vidi da li sve radi kako treba
}
void loop() {

/////////////////////////////////////////// Deo koda koji osigurava da ce se svaki pritisak tastera vrednovati jednom
                                         // i da ne mozete jednostavno drzati taster
  ButtonState = digitalRead(Button);
  ButtonState1 = digitalRead(Button1);
  
  if(ButtonState && ButtonState != lastState)
  {
     n += 4;
     delay(15);
     Serial.println(n);
     k = 2;
  } 
  lastState = ButtonState;

  if(ButtonState1 && ButtonState1 != lastState1)
  {
     n -= 4;
     delay(15);
     Serial.println(n);
     k = 2;
  } 
  lastState1 = ButtonState1;
  
/////////////////////////////////////////// Kraj dela koda koji osigurava da ce se svaki pritisak tastera vrednovati jednom
                                         // i da ne mozete jednostavno drzati taster

  if(n < 0)      // Uspostavljanje granica za n
  {
    n = 0;
  }

  if(n > 52)
  {
    n = 52;
  }

  
/////////////////////////////////////////// Deo koda koji se bavi tajmerom
  if(k != 1)
  {
    if(g == 1)
    {
     time_now = millis();
     g = 2; 
    }
  
    if (millis() > time_now + period)
    {

  if(n >= 27)
  {
     for(i = 0; i < 3; i++)
     {
        fill_solid(leds, NUM_LEDS, CRGB::Red);
        FastLED.show();
        delay(200);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(200);
        
    }
        delay(1000);
        n = 26;
        g = 1;
        k = 1;
  }

  if(n <= 25)
  {
     for(i = 0; i < 3; i++)
     {
        fill_solid(leds, NUM_LEDS, CRGB::Blue);
        FastLED.show();
        delay(200);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(200);
        
    }
        delay(1000);
        n = 26;
        g = 1;
        k = 1;
  }
    }
  }
 /////////////////////////////////////////// Zavrsetak dela koda koji se bavi tajmerom

  for(i = 0; i < n; i++)      // Ovo su komande koje pale odredjen broj ledovki u ondnosu na broj n, tojest
    {                         //proporcijalno sa tim ko trenutno vodi
       leds[i] = CRGB::Red;
       FastLED.show();
    
    }


  for(f = n; f < 52; f++)      // Ovo su komande koje pale odredjen broj ledovki u ondnosu na broj n, tojest
    {                         //proporcijalno sa tim ko trenutno vodi
       leds[f] = CRGB::Blue;
       FastLED.show();
    
    }
  

  if(n >= 52)      // Prva strana je pobedila       
  {
     for(i = 0; i < 3; i++)
     {
        fill_solid(leds, NUM_LEDS, CRGB::Red);
        FastLED.show();
        delay(200);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(200);
        
    }
        delay(1000);
        n = 26;
        g = 1;
        k = 1;
  }

  if(n <= 0)      // Druga strana je pobedila
  {
     for(i = 0; i < 3; i++)
     {
        fill_solid(leds, NUM_LEDS, CRGB::Blue);
        FastLED.show();
        delay(200);
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        delay(200);
        
    }
        delay(1000);
        n = 26;
        g = 1;
        k = 1;
  }
  
  
}
