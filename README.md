# IoT-Air-Pollution-Monitoring-System
Project Description:
This project aims to create a gas detection system with MQ2 gas sensor, buzzer, 3 LEDs and an LCD display using a NodeMCU. The system turns on LEDs, buzzer and displays the gas level on an LCD display according to certain gas levels. It also establishes WiFi connection to display gas levels in real time through a web server and presents it on an HTML page.
																																																				![image (2)](https://github.com/user-attachments/assets/25bf6a01-00ba-4494-9904-72d6cbf9de57)
																																																	
*Software Components:*
1. *Arduino IDE:* Used to write codes and upload them to NodeMCU.

2. *LiquidCrystal Library:* To control the LCD screen.

3. *ESP8266WiFi and ESP8266WebServer Libraries:* To establish WiFi connection and create a web server.

*Project Steps:*

1.Hardware Setup:
- MQ2 gas sensor is connected to the analog pin of NodeMCU.
- Green, yellow and red LEDs are connected to digital pins.
- Buzzer is connected to a digital pin.
- 1602 LCD screen is connected to the digital pins of NodeMCU and the potentiometer.

2.Software Development:
- Code is written to read the gas level in NodeMCU.
- LEDs and buzzer are controlled according to the gas level.
- Gas level is printed on the LCD screen.
- Code is written to connect NodeMCU to WiFi.
- A web server is created to display gas levels on an HTML page.

3.Gas Level Display:
- When the gas level is low (less than 650), the green LED lights up and the text "Clean Air" is displayed.

- When the gas level is medium (between 650-1000), the yellow LED lights up and the text "Dirty Air" is displayed.

- When the gas level is high (more than 1000), the red LED lights up, the buzzer sounds and the text "Very Dirty Air" is displayed.

4.Web Interface:
- The gas level and air quality are displayed via the web server.

-The HTML page is refreshed every 2 seconds to provide real-time data.

-The background of the page is designed to be dark blue, the text is white, and the air quality colors (green, yellow, red) are displayed.

This project demonstrates how a gas detection and warning system can be created and how it can be monitored with a web interface. The system is a practical example for security applications and environmental monitoring.
