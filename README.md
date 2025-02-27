## Weather Monitoring System 🌦️  

This **Weather Monitoring System** is built using **NodeMCU ESP8266** and IoT sensors to measure environmental parameters such as **temperature, humidity, pressure, rainfall, and light intensity**. The system displays real-time sensor readings on an **LCD screen** and transmits the data to the **Blynk IoT platform**, enabling remote monitoring through a mobile app.  

### 📌 Features  
✔️ **Real-time Weather Data** – Monitors **temperature, humidity, pressure, rainfall**, and **light intensity**.  
✔️ **IoT Integration** – Sends sensor data to **Blynk Cloud**, allowing remote access via the **Blynk app**.  
✔️ **LCD Display** – Shows live readings directly on a **16x2 I2C LCD**.  
✔️ **Automatic Updates** – Continuously reads and updates sensor values using timers.  
✔️ **Alerts & Visualization** – Uses **Blynk virtual pins** and widgets for **LED indicators** and remote alerts.  

### 🛠️ Hardware Components  
- **NodeMCU ESP8266** (WiFi-enabled microcontroller)  
- **DHT11** (Temperature & Humidity Sensor)  
- **BMP180/BMP085** (Barometric Pressure Sensor)  
- **Rain Sensor** (Analog input for rainfall detection)  
- **LDR Sensor** (Light intensity detection)  
- **16x2 I2C LCD** (For real-time display)  

### 📡 How It Works  
1. The **ESP8266** connects to WiFi and communicates with **Blynk Cloud**.  
2. Sensors collect environmental data and display it on the **LCD screen**.  
3. The system updates **Blynk** with real-time values for remote monitoring.  
4. If the **light sensor** detects darkness, an LED indicator is turned on in the **Blynk app**.  

### 🔧 Setup & Installation  
1. Install the **Blynk app** and create a project with virtual pins **V0-V4** for different sensors.  
2. Flash the **Arduino code** onto **NodeMCU ESP8266** using the **Arduino IDE**.  
3. Enter your **WiFi credentials** and **Blynk authentication token** in the code.  
4. Power up the system, and monitor data on the **LCD screen** and the **Blynk app**.  

### 🚀 Future Improvements  
- Add **weather forecasting** using machine learning.  
- Implement **alerts & notifications** for extreme weather conditions.  
- Expand with **additional sensors** like **air quality (MQ135)** for pollution monitoring.  

#### 📌 *A smart way to track your local weather conditions in real-time!* 🌍⛅
