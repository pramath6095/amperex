# ❄️ Portable Chemical Cooling System (PCCS) 🧪🌍

A **non-electric, sustainable cooling system** designed for **cold-chain logistics of temperature-sensitive medical supplies** in **resource-constrained environments**.  
Developed under the **Experiential Learning Scheme (Semester 2)** at **RV College of Engineering**.

---

## 🎯 Project Focus

- Electricity-free cooling
- Sustainable and reusable cooling chemistry
- Rapid temperature pull-down for medical cold chain (≈ 8 °C)
- Field-deployable, low-infrastructure design

---

## 🧠 Project Summary

The **Portable Chemical Cooling System (PCCS)** leverages the **endothermic dissolution reaction (EDR)** of **ammonium chloride (NH₄Cl) in water** to produce rapid cooling without ice, compressors, or grid power.

The system integrates **embedded control** to automate fluid cycling, temperature monitoring, and multi-cycle reuse of the chemical cooling agent.

---

## 🔬 Key Technical Concepts

### 🌡 Smart Thermal Control
- ESP32-based closed-loop control
- DS18B20 temperature sensing unit (TSU)
- Maintains critical medical cold-chain temperature (~8 °C)

### 🔁 Automated Fluid Cycling
- DC water pumps for solution refill and drainage
- Geared DC motor for salt agitation and uniform dissolution
- Enables multiple cooling cycles using the same salt batch

### ⚡ Validated Performance
- Temperature drop of **19 °C → 8 °C in ~30 seconds**
- Maintained **≤10 °C for up to 120 minutes**

### ♻️ Sustainability
- >90% regeneration efficiency of NH₄Cl
- Regeneration via **solar or low-grade waste heat**
- Eliminates ice dependency and refrigerants

### 🔋 Energy Efficiency
- Optimized duty-cycle logic
- ~14 hours of continuous operation on a single rechargeable battery pack

---

## 🧩 System Architecture

- **ESP32 MCU** – control logic and state management
- **DS18B20** – real-time temperature sensing
- **DC Pumps** – fluid refill/drain control
- **Geared DC Motor** – salt agitation
- **I2C LCD** – live temperature and system status display
- **Finite State Machine (FSM)** for safe and repeatable operation

---

## ⚙️ Control Logic (Firmware Highlights)

- Threshold-based activation at >12 °C
- Sequential motor actuation with safety delays
- Cooldown lockout to prevent overuse
- LCD feedback for:
  - Temperature
  - Motor states
  - Cooldown timer

---

## 🧪 Applications

- Vaccine transport
- Insulin and biologics storage
- Emergency medical logistics
- Rural healthcare cold-chain support
- Disaster relief operations

---

## 🔮 Future Work

- Automated salt refill and drying mechanism
- Fully integrated solar charging for battery packs
- Improved insulation and thermal retention
- Field trials with real medical payloads

---

## 👨‍💻 Team

- **Pramath J**
- Anika U Bhat
- Samaraditya P H  

**Role:** Embedded Systems Developer / Hardware–Software Integration

---

## 🏫 Academic Context

- **Institution:** RV College of Engineering  
- **Program:** Experiential Learning Scheme  
- **Semester:** 2  
- **Deliverables:** Working prototype, demonstration video, draft research paper

---
