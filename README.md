# 🚰 Water Level Control Module

## 📊 Project Status
| Component | Status |
|------------|---------|
| Ultrasonic Sensor (HC-SR04) Integration | ✅ Completed |
| PID Control Loop Implementation | ✅ Completed |
| Power Console PCB (AOD4184 MOSFETs) | ✅ Completed |
| Manual / Automatic Mode Switch | ✅ Completed |
| Processing GUI for Monitoring | ⚙️ In Progress |
| Data Logging Functionality | ⚙️ In Progress |
| Final System Validation | ⚠️ Not Started |

---

## 📖 Overview
This project focuses on developing a **low-cost educational system** for automatic **water level control**.  
The setup allows experiments related to **PID control**, **signal conditioning**, and **embedded systems** using Arduino.  

The system regulates the **tank water level** through a **PWM-controlled pump** driven by MOSFETs, while a **manual/automatic switch** enables user interaction and comparison between open-loop and closed-loop operation.

---

## ⚙️ System Description
- **Controller:** Arduino Uno  
- **Sensor:** HC-SR04 ultrasonic distance sensor  
- **Actuator:** DC water pump  
- **Power Stage:** Custom PCB with two AOD4184 MOSFETs for PWM control  
- **Modes:**  
  - 🧭 *Manual mode:* Level controlled via potentiometer  
  - 🔁 *Automatic mode:* PID-based level regulation  
- **Sampling period:** 0.1 seconds  
- **Data transmission:** Serial output for GUI visualization and logging  

---

## 🧠 Control Strategy
The closed-loop system implements a **digital PID controller** regulating the tank level based on ultrasonic sensor feedback.

\[
u[k] = u[k-1] + K_p(e[k] - e[k-1]) + K_i T_s e[k] + \frac{K_d}{T_s}(e[k] - 2e[k-1] + e[k-2])
\]

Where:  
- \( e[k] = r[k] - y[k] \) → level error  
- \( T_s = 0.1\,s \) → sampling time  
- \( u[k] \) → control signal (PWM duty cycle)  

---

## 💻 Processing Interface
A **Processing 4 GUI** is under development to provide:  
- Real-time monitoring of water level and control signal  
- Visualization of reference tracking performance  
- Data logging for later analysis  

📸 The interface is currently used for **monitoring and data storage only**.

---

## ⚡ Power Console PCB
The **custom PCB** integrates:  
- Dual **AOD4184 MOSFETs** for high-efficiency PWM control  
- Manual/automatic mode switch  
- Potentiometer for manual reference adjustment  
- Connector headers for Arduino and sensor interface  

---

## 🔬 Educational Focus
This project is part of a set of **control system laboratory modules**, including:  
- 🔥 Temperature Control  
- 🚗 Mobile Robot (PI Control)  
- ✈️ UAV Attitude Control  

Each module is designed for teaching **digital control**, **signal acquisition**, and **embedded systems design**.

---

## 🔧 Future Work
- 🧰 Complete the Processing 4 GUI for data logging  
- 📈 Implement real-time plot scaling and CSV export  
- ⚙️ Tune PID parameters for nonlinear dynamics of the tank  
- 📡 Add wireless telemetry (ESP32-based extension)  

---

## 📜 License
MIT License © 2025  
Developed for educational and laboratory purposes.
