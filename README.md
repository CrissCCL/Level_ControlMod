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
### Controlled Variables
- **Temperature** → Level value control (stabilization)

## 📐 Digital PID Control

The Module uses a discrete PI controller implemented on a Arduino microcontroller.  
The control law in the digital domain is expressed as:

$$
u(n) = u(n-1) + K_0 e(n) + K_1 e(n-1)
$$

Digital PI controller implemented for level measured,

$$
V_{PWM}(n) = V_{PWM}(n-1) + K_0 e(n) + K_1 e(n-1)
$$

### Parameters:
The parameters are adjusted for temperature measured,

$$
K_0 = K_p + \frac{K_p}{2T_i} T_s
$$

$$
K_1 = -K_p + \frac{K_p}{2T_i} T_s
$$

## 🔉 Signal Processing: Low-Pass IIR Filter (1st Order)

To reduce measurement noise, a **first-order IIR low-pass filter** was applied to the level signal before feeding it to the controller and the model.  

### 🔹 Filter Equation  

$$
y(k) = \alpha \cdot x(k) + (1 - \alpha) \cdot y(k-1)
$$  

Where:  
- $$x(k)$$: raw sensor measurement at time step $$k$$  
- $$y(k)$$: filtered output  
- $$\alpha$$: smoothing factor, $$(0<\alpha<1)$$ 



## 💻 Processing Interface
A **Processing 4 GUI** is under development to provide:  
- Real-time monitoring of water level and control signal  
- Visualization of reference tracking performance  
- Data logging for later analysis  

📸 The interface is currently used for **monitoring and data storage only**.

## ⚡ Power Console PCB
The **custom PCB** integrates:  
- Dual **AOD4184 MOSFETs** for high-efficiency PWM control  
- Manual/automatic mode switch  
- Potentiometer for manual reference adjustment  
- Connector headers for Arduino and sensor interface  



---

## 📜 License
MIT License © 2025  
Developed for educational and laboratory purposes.
