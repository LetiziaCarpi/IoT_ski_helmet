# IoT_ski_helmet
An IoT-based smart ski helmet developed as a university project for the IoT course at UNIMORE. The system collects environmental and skier data to improve safety and manage ski resort facilities in real time.

## Extended README Description

### Project Overview

This project was developed as part of the **Internet of Things (IoT) course at the University of Modena and Reggio Emilia (UNIMORE)**.
The goal of the project is to design and prototype a **realistic and innovative IoT product** with a concrete application in the real world.

The proposed solution is an **IoT-enabled ski helmet** designed to collect data from skiers and ski slopes in order to **monitor the safety conditions of a ski resort** and enhance the overall skier experience.

---

### Concept and Use Case

The core idea is to promote safety in ski resorts by providing a **temporary and free smart helmet** for each ski pass sold.
By equipping skiers with IoT helmets, the resort can gather distributed data across the entire area and obtain a **real-time understanding of slope conditions, skier behavior, and potential hazards**.

Using data collected from multiple helmets, the system evaluates the **state of the ski slopes** and dynamically regulates skier flow through the resort’s turnstiles.

---

### Smart Helmet Hardware

Each helmet is based on an **Arduino R4** microcontroller and includes the following components:

* 3-axis accelerometer
* 3-axis gyroscope
* GPS module
* Red LED (helmet warning indicator)
* DHT11 temperature and humidity sensor
* Light sensor (photoresistor)
* Acoustic actuator (buzzer)

These sensors allow the system to monitor:

* Skier movement and speed
* Environmental conditions (fog, light, temperature, humidity)
* Potential falls or dangerous situations

---

### Safety Logic and Use Cases

The collected data is processed to determine safety conditions and trigger specific actions:

* **Fog + high number of people** → Turnstile closed
* **Heavy fog** → Turnstile closed
* **Fog detected** → Helmet LED turns on
* **Fog + crowd density + high speed (on slope)** → Warning: dangerous condition
* **Fog + high speed** → Warning: slow down and pay attention
* **GPS off slope + no accelerometer movement + high heart rate (ski proximity)** → Skier fall detected

---

### Turnstile System

The ski resort turnstile is represented in the project by an **Arduino R3** microcontroller equipped with:

* Bluetooth module
* Display for user feedback
* Three LEDs acting as a traffic light (red, yellow, green)
* A blue LED simulating the turnstile opening frequency

This system acts as the **user interface of the ski lift access control**, dynamically adjusting skier flow based on real-time safety conditions.

---

### Architecture and Implementation

The following sections of this repository describe:

* The system architecture
* Communication between devices
* Data processing logic
* Implementation details of both the helmet and turnstile prototypes

This project demonstrates how IoT technologies can be applied to **enhance safety, optimize infrastructure management, and improve user experience in ski resorts**.


