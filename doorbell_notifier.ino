// Listens for a signal from a 433MHz receiver unit (like the cheap chinese ones for example).
// Can be setup to display found codes on serial, and/or activate an LED (WS2812B//Adafruit Neopixel in this example) when a known signal is found

// *** IMPORTANT NOTE: Receiver data pin should go to "interrupt 0" => that is pin #2 for Uno; #3 for Leonardo *** //
// Darren Gibbard -- 03/03/2016

// Requires the Neopixel Library to drive WS2812B LEDs - not needed if you just want a normal LED; but some code changes required.
#include <Adafruit_NeoPixel.h>

// RCSwitch library required for managing 433MHz signals from the doorbell.
#include <RCSwitch.h>

// Optional part of the Neopixel stuff. Probably not needed :)
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN            0  // Neopixel is on Digital Pin 0
#define NUMPIXELS      1  // We only have the one pixel (they're power hungry - best go easy driving them direct off an arduino!)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // Setup the pixel
int onboard = 13;  // Onboard LED pin

RCSwitch mySwitch = RCSwitch();
void setup() {
  Serial.begin(9600); // Initialize the Serial port
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setPixelColor(0, pixels.Color(0,0,0)); // Set the pixel to off
  pixels.show(); // Apply pixel settings
  pinMode(onboard, OUTPUT); // Enable the onboard LED
  // Give time for serial monitor to connect!
  delay(5000);
  digitalWrite(onboard, HIGH); // Set onboard LED on.
  Serial.println("Listening for 433MHz signals...");
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2 for Uno; #3 for Leonardo
}
void loop() {
  if (mySwitch.available()) {

    // Set the Indicator LED off, so people know we've stopped listening for a second:
    digitalWrite(onboard, LOW);
    
    // Print to Serial information about the signal we found (Use the first value for checking received codes)
    // -- Feel free to comment this section out once you know what codes you're interested in!
    Serial.print("Signal Received:  ");
    Serial.print("Value: "); Serial.print(mySwitch.getReceivedValue() );
    Serial.print(" / "); Serial.print(mySwitch.getReceivedValue(), BIN);
    Serial.print(" Length: "); Serial.print(mySwitch.getReceivedBitlength() );
    Serial.print(" Delay: "); Serial.print(mySwitch.getReceivedDelay() );
    Serial.print(" Protocol: "); Serial.println(mySwitch.getReceivedProtocol());
    
    // Check the received code against our known doorbell codes :)
    if ((mySwitch.getReceivedValue() == 1454736851)||(mySwitch.getReceivedValue() == 1745540499 )){
      // If it's one of the codes we're after, light up our Pixel (WS2812B)
      Serial.print("Doorbell Identified! Lighting up.");
      pixels.setPixelColor(0, pixels.Color(10,180,10)); // Moderately bright green color.
      pixels.show();
      delay(10000); // Leave it on for 10s
      pixels.setPixelColor(0, pixels.Color(0,0,0)); // Turn it off.
      pixels.show();
    }
    mySwitch.resetAvailable(); // Start the listening again.
    digitalWrite(onboard, HIGH); // Turn the onboard LED back on to show we're listening.
  }
}
