# Smart Greenhouse Monitoring & Automation System

An IoT-based Smart Greenhouse Monitoring and Automation System developed as a **1st Year, 1st Semester university project at the Sri Lanka Institute of Information Technology (SLIIT)**.

The system is designed to monitor important greenhouse environmental conditions and automate plant watering with minimal manual intervention.

## Project Overview

The Smart Greenhouse system uses a **NodeMCU ESP8266** as the main controller. Environmental sensors collect real-time information from inside the greenhouse, while the controller processes the sensor readings and controls the watering system according to predefined conditions.

The system also uses the **Blynk IoT platform** to provide remote monitoring of greenhouse conditions.

## Key Features

* Real-time temperature monitoring
* Real-time humidity monitoring
* Soil moisture monitoring
* Automated watering system
* Water pump control
* LCD-based local monitoring
* Wi-Fi connectivity
* Blynk IoT remote monitoring
* Automatic control based on predefined thresholds
* Reduced manual intervention

## System Architecture

The main components of the system include:

* **NodeMCU ESP8266** – Main microcontroller and Wi-Fi connectivity
* **DHT11 Sensor** – Temperature and humidity monitoring
* **Soil Moisture Sensor** – Soil moisture measurement
* **Water Pump** – Automated irrigation
* **Relay Module** – Controls the water pump
* **16×2 LCD** – Displays sensor information locally
* **Blynk IoT** – Remote monitoring and control interface

## How It Works

```text
DHT11 Sensor
     │
     ├──────────────┐
     │              │
Soil Moisture ──► NodeMCU ESP8266 ──► LCD Display
     │              │
     │              └────────► Blynk IoT
     │
     └──────────────► Relay ──► Water Pump
```

The sensors continuously provide environmental readings to the NodeMCU. The controller processes these values and determines whether watering is required. When the soil moisture reaches the predefined condition, the relay controls the water pump to irrigate the plants.

At the same time, sensor information can be monitored remotely through the Blynk IoT interface.

## Technologies

### Software

* Arduino IDE
* C/C++
* Blynk IoT

### Hardware

* NodeMCU ESP8266
* DHT11
* Soil Moisture Sensor
* 16×2 LCD
* Relay Module
* Water Pump
* Wi-Fi

## Project Images

### Smart Greenhouse Prototype

Add your greenhouse prototype image here.

```text
images/greenhouse-front.jpg
```

### Blynk IoT Dashboard

Add your Blynk dashboard screenshot here.

```text
images/blynk-dashboard.jpg
```

## Project Objectives

* Monitor greenhouse environmental conditions in real time
* Automate plant watering
* Reduce manual intervention
* Enable remote monitoring through IoT
* Improve efficient use of water
* Gain practical experience with embedded systems and IoT

## Learning Outcomes

Through this project, I gained practical experience in:

* IoT system development
* Microcontroller programming
* Sensor integration
* Embedded systems
* Automation
* Relay and actuator control
* LCD interfacing
* Wi-Fi communication
* Blynk IoT
* Hardware prototyping

## Academic Information

**Institution:** Sri Lanka Institute of Information Technology (SLIIT)

**Project:** Smart Greenhouse Monitoring & Automation System

**Academic Year:** 1st Year – 1st Semester

**Project Group:** PWE 09

## Future Improvements

Possible future improvements include:

* Additional environmental sensors
* CO₂ monitoring
* Automatic light control
* Enhanced security features
* More advanced environmental automation
* Improved cloud-based analytics
* Mobile notifications and alerts

## License

This project is created for academic and educational purposes.
