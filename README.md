# 🚰 Water Level Control Module

## 📖 Overview
This project focuses on developing a **educational system** for automatic **water level control**.  
The setup allows experiments related to **PID control**, **signal conditioning**, and **embedded systems** using Arduino.  

The system regulates the **tank water level** through a **PWM-controlled pump** driven by MOSFETs, while a **manual/automatic switch** enables user interaction and comparison between open-loop and closed-loop operation.

## 📂 Contents
- `/control_lvl` → C code for Arduino.

## 📊 Project Status
| Component | Status |
|------------|---------|
| Ultrasonic Sensor (HC-SR04) Integration | ✅ Completed |
| PID Control Loop Implementation | ✅ Completed |
| Power Console PCB (AOD4184 MOSFETs) | ✅ Completed |
| Manual / Automatic Mode Switch | ✅ Completed |
| Processing GUI for Monitoring | ✅ Completed |
| Data Logging Functionality | ✅ Completed |
| Final System Validation | ✅ Completed |


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

## ⚠️ Serial Communication Issue on Arduino UNO

### 🧩 Overview
The **Arduino UNO** can freeze when the serial connection is interrupted — for example, if you close the Serial Monitor or stop the Processing app while data is being transmitted.  
This issue **does not affect** the **Arduino Leonardo**.

### ⚙️ Technical Cause
- **UNO:** uses a separate USB–Serial chip (**ATmega16U2**).  
  → When the PC closes the port, the main MCU (**ATmega328P**) keeps sending data to a disconnected USB bridge, blocking the serial buffer.  
- **Leonardo:** uses an integrated USB controller (**ATmega32u4**) that detects disconnections and avoids blocking.

🧠 **Additional factor:**  
UNO’s transmit buffer is only **64 bytes**. If `Serial.print()` is used too often or the port is closed, the buffer fills and freezes the loop

### 💡 Recommendation
- Prefer **Arduino Leonardo** or **Teensy** for real-time communication.  
- If using UNO, add checks before sending data:
  
```cpp
if (Serial && Serial.availableForWrite() > 16) {
  Serial.println(sensorValue);
}
```
or
```cpp
if (Serial) {
  Serial.println(sensorValue);
}
```

## 🔄 Control Loop

<p align="center">
<img src="https://github.com/user-attachments/assets/957fee3b-aad1-4faf-adfd-1462c229e427" alt="Diagrama sistema" width="550">
</p>

### Controlled Variables

- **Level** → Level value control (stabilization)

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
y(k) =(1 - \alpha)  \cdot x(k) +  \alpha \cdot y(k-1)
$$  

Where:  
- $$x(k)$$: raw sensor measurement at time step $$k$$  
- $$y(k)$$: filtered output  
- $$\alpha$$: smoothing factor, $$(0<\alpha<1)$$ 

## :triangular_ruler: Connection Diagram

<p align="center">
<img src="https://github.com/user-attachments/assets/f60ea8f1-6d69-460d-ae31-d151c5ba9422" alt="Esquema de conexiones" width="500">
</p>

## 📊 PI Control Test and First-Order Model Identification

A closed-loop experiment was conducted using a PI controller applied to the water level control system.  
From the acquired input–output data, a **First-Order** model was identified using a non-parametric step-response method.

### 🔹 Identified  Model

The identified model follows the general first-order transfer function:

$$G(s)=\frac{K}{\tau s + 1}$$

Where:

| Symbol | Meaning |
|--------|---------|
| $$K$$ | Steady-state gain |
| $$\tau$$ | Time constant of the process |

This model structure was obtained from the experimental step response without assuming a parametric structure beforehand (non-parametric identification).

### 🔎 Results Overview

- ✅ The PI controller achieved stable regulation of water level  
- 🌊 The system dynamics were dominated by a single time constant, consistent with first-order behavior  
- 🧩 The absence of transport delay simplifies control tuning  
- 🎯 The identified model accurately reproduced the experimental response  
- 🧾 This model serves as the basis for controller tuning and validation 


### 📈 Experimental Plots

<p align="center">
<img src="https://github.com/user-attachments/assets/c461f447-2a95-4bae-a6e5-aa46dd87229c" alt="First-Order Model vs Experimental Comparison (Level)" width="500">
</p>

## 🖥️ GUI — Monitoring and Data Logging

The graphical user interface (GUI) shown in the photograph is developed using **Processing 4**.  
It is designed **only for monitoring** the level module in real time and for **recording experimental data**.  

<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/f1f75f42-ce8a-465c-a9fb-ea1d8dbad870" alt="GUI preview" width="400"><br>
      <sub>GUI preview closed loop</sub>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/62fbed8f-c7f3-4e76-85d8-725b13706de6" alt="GUI preview" width="400"><br>
      <sub>GUI preview open loop</sub>
    </td>
  </tr>
</table>

Key features:
- Real-time plot of level and setpoint.
- Display of control output (PWM or equivalent).
- Logging of measurements to files for offline analysis.
- Simple visualization of system behavior during experiments.

> ⚠️ **Note:** The GUI is for observation and data recording only; it does **not** modify the control system or send commands to the hardware.

## ⚡ Power Console PCB
The **custom PCB** integrates:  
- Dual **AOD4184 MOSFETs** for high-efficiency PWM control  
- Manual/automatic mode switch  
- Potentiometer for manual reference adjustment  
- Connector headers for Arduino and sensor interface  

## 🖼️ Render 3D PCB 

<p align="center">
<img src="https://github.com/user-attachments/assets/1dfb69ca-ce82-4780-a2aa-99e8c4d943e8" alt="PCB render" width="500">
</p>

## ⚡Physical  Prototype

<table>
  <tr>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/0b8b2f6e-41c6-48fb-917a-0f376eb87b35" alt="Prototype PCB assembled" width="500"><br>
      <sub>PCB assembled</sub>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/dc4f8d14-0b17-4afd-836e-77b98d723287" alt="Prototype PCB assembled" width="400"><br>
      <sub>PCB assembled in process</sub>
    </td>
    <td align="center">
      <img src="https://github.com/user-attachments/assets/0d722579-5256-4bd1-b425-c781d6621171" alt="Complete Setup" width="600"><br>
      <sub>Setup overview</sub>
    </td>
  </tr>
</table>


## 📜 License
MIT License
