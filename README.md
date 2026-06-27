# 📡 **Morse Caster using Arduino**  

The **Morse Caster** is an **Arduino-based Morse Code Transmitter** that converts text into **Morse code** and transmits it using an **LED** and a **buzzer**. The transmission is also shown in real-time on a **16x2 LCD display** — a fun, educational project for learning Morse code and embedded systems.  

---

## 🛠️ **Components Used**  
- 🔹 **Arduino Uno** – Processes input and controls output.  
- 🔹 **16x2 LCD Display** – Shows the current message and status.  
- 🔹 **Buzzer (active)** – Beeps in time with the Morse code.  
- 🔹 **LED (+ ~220–330 Ω resistor)** – Blinks the Morse signal.  

> ✍️ **Text is entered over USB via the Serial Monitor** (9600 baud) — type a message and press Enter. Until then it transmits the default **"HELLO"**.

---

## 🔌 **Wiring**  
| Arduino Pin | Connects to |
|-------------|-------------|
| D12, D11 | LCD **RS**, **E** |
| D5, D4, D3, D6 | LCD data **D4, D5, D6, D7** |
| D7 | LED **+** via a ~220–330 Ω resistor (LED − → GND) |
| D8 | Buzzer **+** (buzzer − → GND) |

> Plus the usual LCD pins: VSS→GND, VDD→5V, V0→contrast pot, RW→GND, and the A/K backlight. The sketch assumes an **active** buzzer; for a passive piezo, drive it with `tone()`.

---

## ⚙️ **How It Works**  
1️⃣ **Type text in the Serial Monitor** (or it uses the default "HELLO"); it's converted to Morse code.  
2️⃣ The **LED blinks** and the **buzzer beeps** with standard Morse timing (dot : dash : element/letter/word gaps = 1 : 3 : 1/3/7 units).  
3️⃣ The current **message and status** are shown on the **16x2 LCD**.  
4️⃣ The system pauses between words and loops, ready for the next message.  

---

## 📝 **Features**  
✅ **Converts text to Morse code** with correct standard timing  
✅ **Outputs Morse via LED and buzzer**  
✅ **Displays the message and status on the LCD**  
✅ **Live text input over the Serial Monitor**  
✅ **Great for learning and practising Morse code**  

---

## 🌍 **Applications**  
🔹 **Learning Morse Code** – Useful for students and radio enthusiasts.  
🔹 **Emergency Communication** – Can be adapted for distress signalling.  
🔹 **Secret Messaging** – A fun way to encode messages.  
🔹 **Historical Exploration** – Experience old-school telecommunication.  

---

🚀 **This Morse Caster makes learning and using Morse code fun and interactive!**
