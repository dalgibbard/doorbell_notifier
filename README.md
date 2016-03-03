# doorbell_notifier
Arduino Based Receiver and visual indicator for a 433MHz Wireless Doorbell

Essentially; when i'm working with my headphones on, I can't hear the doorbell. It's a generic, cheap, UK wireless doorbell; which has a 433.92MHz Transmitter module inside.
So; this project is to setup an Arduino (Uno, Leonardo or whatever), a 433MHz receiver and a WS2182B (Similar to Adafruit Neopixel LED) to notify me when someone presses on the doorbell, by:
* Identifying the Doorbell's (somewhat) unique transmission
* Checking if it matches one of the codes we know the doorbell to transmit
* Turn on the LED

You could replace the WS2812B LED with a regular LED, but i wanted to be able to have it cycle rainbow colours rather than just 'on' ;D

* The *.fzz file is a Fritzing wiring diagram to get you started (the PNG is an image version of it for simplicity!)
* The *.ino file is the Arduino sketch (requires the RCSwitch and Adafruit_Neopixel Libraries)

NOTE: I had serious range issues with the cheaper chinese receiver modules. Try finding one that has a crystal on it (pill-shaped metal plate thingy)

Example Wiring:
![Example Wiring Diagram](/doorbell_notifier_bb.png?raw=true "Example Wiring")
