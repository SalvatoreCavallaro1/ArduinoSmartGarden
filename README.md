# Smart Garden with Arduino Mega

This project demonstrates the creation of a small “Smart Garden” using an **Arduino Mega** (or a compatible board), various sensors (DHT11 for temperature/humidity, LDR for light, PIR for motion, soil moisture sensor), and several actuators (servo for irrigation, status LEDs, a cooling fan, and an internal light). It also includes a **16x2 LCD** display to show real-time data.

---

## 1. Overview

The “Smart Garden” monitors:

- **Air temperature and humidity** using the DHT11 sensor.
- **Soil moisture** using an analog sensor.
- **Ambient light** using an LDR (photoresistor).
- **Motion** using a PIR sensor.

Based on the readings:

- It turns a **fan** on or off depending on temperature thresholds.
- Activates a **servo motor** to simulate opening a valve for irrigation when the soil moisture is too low.
- Switches on an **internal light** if motion is detected.
- Displays temperature and humidity on the **LCD**.
- Uses three **LEDs** (green, yellow, red) to indicate temperature ranges.

---

## 2. Components Used

1. **Arduino Mega 2560** (or compatible)
2. **DHT11** sensor for air temperature and humidity
3. **Photoresistor (LDR)** for ambient light measurement
4. **PIR sensor** for motion detection
5. **Soil moisture sensor** (analog)
6. **Servo motor** (e.g., SG90) to simulate irrigation valve
7. **Fan** (or DC motor) controlled via PWM
8. **16x2 LCD** (HD44780-compatible) + 10k potentiometer for contrast
9. **Three LEDs** (green, yellow, red) with appropriate resistors
10. **Photoresistor** with voltage divider
11. **Jumper wires** and **breadboard**
12. **5V power supply** (from Arduino or external)

---

## 3. Wiring (Key Pins)

Below are the main pin connections as defined in the sketch:

- **DHT11**  
  - Data → **Digital Pin 4**  
  - VCC → **5V**  
  - GND → **GND**

- **PIR Sensor**  
  - Output → **Digital Pin 2** (interrupt)  
  - VCC → **5V**  
  - GND → **GND**

- **Soil Moisture Sensor**  
  - Analog Output → **A11**  
  - VCC → **5V**  
  - GND → **GND**

- **Photoresistor (LDR)**  
  - Used in a voltage divider; the midpoint of the divider goes to **A14**  
  - VCC → **5V**  
  - GND → **GND**

- **Internal Light (LUCEINTERNA)**  
  - Controlled by **A8** (using `analogWrite`)

- **External Light (LUCE)**  
  - Controlled by **A7** (using `analogWrite`)

- **LEDs**  
  - Green LED → **A0** (with series resistor)  
  - Yellow LED → **A1** (with series resistor)  
  - Red LED → **A3** (with series resistor)

- **Fan (ENABLE_FAN)**  
  - Controlled by **Digital Pin 6** (PWM)  
  - A transistor or driver module may be needed if the fan requires more current.

- **Servo**  
  - Signal → **Digital Pin 25**  
  - VCC → **5V**  
  - GND → **GND**

- **16x2 LCD**  
  - RS → **Digital Pin 7**  
  - Enable → **Digital Pin 8**  
  - D4 → **Digital Pin 9**  
  - D5 → **Digital Pin 10**  
  - D6 → **Digital Pin 11**  
  - D7 → **Digital Pin 12**  
  - R/W → **GND**  
  - VSS → **GND**  
  - VCC → **5V**  
  - VO (pin 3) → middle pin of the 10k potentiometer (ends to 5V and GND)

*(Refer to the attached schematic or Fritzing diagram for more details.)*

---

## 4. Required Libraries

The sketch uses:

- **Servo.h** (included with the Arduino IDE)
- **LiquidCrystal.h** (included with the Arduino IDE)
- **dht11.h** (you may need to install a dedicated library for the DHT11 if your IDE doesn’t have it)

Make sure these libraries are correctly installed before compiling.

---

## 5. Code Explanation

1. **Initialization**  
   - Sets up serial communication (`Serial.begin(9600)`), pin modes, and initializes the LCD.  
   - Calibrates the photoresistor by reading its values over a 4-second interval to determine minimum (`low`) and maximum (`high`) values.

2. **LCD Display**  
   - Displays a welcome message, then regularly shows the DHT11 humidity and temperature readings.  
   - Loads custom characters (thermometer and water drop) into the LCD’s memory.

3. **Sensor Reading**  
   - **DHT11**: Reads temperature and humidity; prints them on the LCD.  
   - **Photoresistor**: Determines whether to switch on the **external light** (pin A7) based on a threshold.  
   - **PIR**: If motion is detected, it switches on the **internal light** (pin A8). When no motion, it turns the internal light off.  
   - **Soil Moisture**: Mapped to 100 (wet) to 0 (dry). Compared against 50% threshold.

4. **Actions**  
   - **Temperature LEDs & Fan**  
     - Temp ≤ 30 °C → Green LED on, fan off  
     - 30 °C < Temp < 50 °C → Yellow LED on, fan at medium speed (PWM ~180)  
     - Temp ≥ 50 °C → Red LED on, fan at full speed (PWM ~255)  
   - **Irrigation Servo**  
     - If soil moisture < 50%, servo rotates to 90° (valve open).  
     - Otherwise, it rotates back to 180° (valve closed).

5. **Main Loop**  
   - Continuously reads sensors, updates the LCD, and controls the actuators accordingly.

---

## 6. Getting Started

1. **Upload** the code (`SmartGarden.ino`) to your Arduino Mega.  
2. **Power** the board and components (sensors, servo, fan, etc.).  
3. **Check the LCD** for temperature and humidity values.  
4. **Observe the LEDs** for temperature status (green, yellow, red).  
5. **Watch the servo** move when soil moisture drops below the threshold.  
6. **Observe the internal light** turning on/off in response to the PIR motion sensor.

---

## 7. Future Improvements

- **Adjust thresholds** for temperature and soil moisture as needed.  
- **Remote control**: Add a Wi-Fi module (ESP8266 or similar) to send data to an app or web server.  
- **Water level sensor**: Monitor the water reservoir to ensure enough supply for irrigation.  
- **Code optimization**: Add power-saving features, data logging to an SD card, or more advanced functionalities.

---
## 8. Schema

![SmartGardenVersione1](https://github.com/user-attachments/assets/ca89a47b-dd99-4ae5-8bb5-9d091fd43a4a)

---

## 9. Conclusion

This project provides a starting point for an automated gardening system that responds to environmental factors. With Arduino’s flexibility, you can expand it with additional sensors and features to suit more complex needs.

For further details, refer to:
- [Arduino Official Documentation](http://www.arduino.cc)


**Happy gardening with your Smart Garden!**

