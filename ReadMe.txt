Name of the Model: Landmine Finder

READ THE USER MANUAL 



USES:

Find Anti-tank Mines during war time and during movement of troops in vulnerable areas.  Anti-tank Mines usually require 100-500 kg of force to detonate. This remotely operated robot can safely go over these as it is very light.


Find Antipersonnel Mines during war time and anti terror operations. Antipersonnel Mines usually require 5-50 kg of force to detonate. This remotely operated robot can safely go over these as it is very light.

It can be used to clean up bombed areas after wartime and find unexploded explosives.




ADVANTAGES:

Custom Developed Software and Algorithm
Very lightweight
Simple to use
Cheap
Easy to operate
Can be operated using a hand held remote, Smartphone or a Computer.
Used highly secure and simple WiFi to communicate. 
Uses a widely used and secure HTTPS protocol to transfer data.



FEATURES & TECHNOLOGIES:

Custom Developed Software and Algorithm
ESP32 & ESP8266 microcontroller 
WiFi 802.11 b/g/n.      // b- high rate Wifi // g- short distance 54Mbps in 2.4 GHz // n- multiple input multiple output 
Land Mine Detection
Hazard light
Long range (50 ft and extendable)
Variable speed
RISC V chipset
Low power consumption





WORKING PRINCIPAL:


Controller Input: The user operates a joystick on the ESP32-based controller, which generates signals indicating the direction the user wants the RC car to move.

Communication: The ESP32 on the controller side communicates with the ESP8266 on the LandMine Finder (car) using Wi-Fi and HTTPS protocol to transmit the user's directional commands securely.

Motor Control: The ESP8266 on the LandMine Finder (car) side receives the directional commands from the controller and processes them. It then drives the four motors using the L298 motor driver to move the car in the desired direction (forward, backward, left, or right).

Metal Detector Sensor: The ESP8266 on the LandMine Finder (car) side is also connected to a metal detector sensor. It detects changes in the magnetic field caused by the presence of metal objects nearby. It is an induction-based metal detector and has two coils. A transmitter coil that creates a magnetic field, and a receiver coil that senses changes when metal is close. When metal comes near, it makes eddy currents, creating a magnetic field that opposes the transmitter's field. The receiver coil detects this change and alerts us about the metal nearby.

Metal Detector Output Transmission: When the metal detector sensor detects Land Mine or metal, it sends a signal (high) to the ESP8266. The ESP8266 then transmits this state (high or low) back to the controller using Wi-Fi and HTTPS, notifying the user about the presence of Land Mine or metal near the LandMine Finder (car).

In summary, the ESP32-based controller sends directional commands to the LandMine Finder (car), which is equipped with an ESP8266, motor driver, and metal detector sensor. The ESP8266 processes the commands, drives the motors, and detects Land Mine or other metal objects, communicating back to the controller about the metal detection status.
