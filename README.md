# AI-Smart-Sight
# SmartSight 🚶‍♂️🔔 + AI Scene Narrator 👁️‍🗨️🎙️  

A combined hardware + AI software solution designed for **blind and visually impaired individuals**.  
This project integrates:  

1. **SmartSight (Smart Stick)** – an ESP32-powered obstacle detection stick with GPS and buzzer alerts.  
2. **AI Scene Narrator** – an AI-driven system that uses a camera and Google’s Gemini AI to describe scenes in natural language and narrate them via speech.  

---

## ✨ Features

### 🦯 SmartSight (Hardware Stick)
- 🚧 **Obstacle Detection:** Ultrasonic + IR sensors detect objects in the path.  
- 🔊 **Audio Feedback:** Alerts via buzzer (extendable to voice/vibration).  
- 📍 **GPS Tracking:** Provides live location data for safety/navigation.  
- 🔌 **ESP32 Powered:** Wi-Fi + Bluetooth for future mobile integration.  
- ⚡ **Low Cost & Portable:** Affordable, easy-to-carry design.  

### 👁️‍🗨️ AI Scene Narrator (Software App)
- 🎥 **Live Camera Feed** using OpenCV  
- 📸 **Capture Images** via button or voice command ("capture")  
- 🧠 **Scene Description** with Google Gemini AI  
- 🔊 **Text-to-Speech (TTS)** narration of AI responses  
- 🌐 **Multilingual Support:** English, Bangla, Spanish, French, German, Hindi  
- 🎤 **Voice Command Mode** for hands-free use  
- 💾 **Auto-save** images + AI responses  

---

## 🛠️ Hardware Used (SmartSight)
- **ESP32-S3-WROOM-1**  
- **HC-SR04 Ultrasonic Sensor**  
- **IR Sensor**  
- **GPS Module (NEO-6M or similar)**  
- **Buzzer**  
- *(Optional)* ESP32-CAM for AI-based object detection  

---

## 🛠️ Tech Stack (AI Scene Narrator)
- **Python 3.11+**  
- **OpenCV** → Camera input  
- **Google Gemini API** → Scene understanding  
- **pyttsx3 / gTTS** → Text-to-Speech narration  
- **SpeechRecognition** → Voice commands  

---

## 📂 Project Structure
