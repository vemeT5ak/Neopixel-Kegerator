#include <Adafruit_NeoPixel.h>
float temp;
int tempPin = A7; // pin that the lm35 temp probe is attached to
int relay = 2; // pin that the relay is attached to
#define PIN 3 //pin that the LED strip is hooked to.
// Edit the delay to make it faster or slower
// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(1,PIN, NEO_GRB + NEO_KHZ800);


  void setup() {
   Serial.begin(9600);
  strip.begin(); // Initalize the strip
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(255); // set total brightness, from 1 to 255.
  pinMode (relay, OUTPUT);
  digitalWrite (relay, LOW); // Make sure the relay is off when we startup
  delay(50);
  
  }

void loop() {
  //temp = analogRead(tempPin);
 // temp = temp * 0.48828125; // c no conversion
 temp = ( 5.0 * analogRead(tempPin) * 100.0) / 1024.0; // read temp
  Serial.print("CELSIUS: ");
 Serial.print(temp);
 Serial.println("*C ");
 temp = (temp * 9)/ 5 + 32; // convert c to fahrenheit
 Serial.print("         ");
 Serial.print(temp);
 Serial.println("*F ");
  
  if (temp > 38){
  digitalWrite (relay, HIGH);
  colorAll(strip.Color(255,0,0), 1); //red
  delay (3000); // wait 3 seconds
  }
  
  if (temp < 38 && temp > 34){ //3.33c=38f 1.11c=34f
    //digitalWrite (relay, LOW);
    colorAll(strip.Color(0,255,0), 1); //green
    delay (3000);// wait 3 seconds
    
  }
  
  if (temp < 34){
    digitalWrite (relay, LOW);
    colorAll(strip.Color(0,0,255), 1); //blue
    delay (3000);// wait 3 seconds
  }
  
  if (temp < 32){
    digitalWrite (relay, LOW);
    colorAll(strip.Color(255,0,255), 1); //blue
        delay (3000);// wait 3 seconds

  }    
}
// Set all pixels in the strip to a solid color, then wait (ms)
void colorAll(uint32_t c, uint8_t wait) {
  uint16_t i;
  
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  delay(wait);
}
