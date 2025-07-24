# 🚗🌦 Carrito Autónomo para Monitoreo Meteorológico en Movimiento

Este proyecto integra robótica, sensorización e Internet de las Cosas (IoT) para desarrollar un carrito autónomo capaz de registrar en tiempo real variables ambientales como temperatura, humedad y presión, además de detección de gases (CO, CO2, NH4, alcohol, acetona) mientras se desplaza por distintos espacios de la universidad.
Tambien, se implementa una aplicación web con React para visualizar los datos, y un servidor en Express que expone una API REST y una conexión WebSocket para la transmisión en tiempo real de los datos. 

---

## 📡 Características del Proyecto

- Medición de variables ambientales con sensores **BMP280**, **DHT22** y **MQ135**
- Microcontrolador **ESP32** con conectividad WiFi
- Transmisión de datos en tiempo real via **WebSocket**
- Sitio web para visualización de datos
- Carrito autónomo con motores DC y controladores lógicos

---

## 🖥️ Tecnologías Utilizadas

### 🔧 Backend
- **Node js** con **Express**
- **API REST** y **WebSockets** para comunicación en tiempo real

### 🎨 Frontend
- **React** con componentes personalizados
- **Tailwind CSS** para una interfaz moderna y responsiva

### 🔗 Otros
- Arduino IDE (para cargar código en ESP32)
- Twitter API (envío automático de publicaciones)

## 👥 Equipo del Proyecto

| Avatar | Nombre | Rol | GitHub |
|--------|--------|-----|--------|
| <img src="https://github.com/wesvm.png" width="80" height="80" /> | **Walter Vilca** | Desarrollo Web (React, Express, despliegue) | [@wesvm](https://github.com/wesvm) |
| <img src="https://github.com/Esquema.png" width="80" height="80" /> | **Ever Quispe** | Sistema Meteorológico (sensores, IoT, Twitter,ThingSpeak ) | [@Esquema](https://github.com/Esquema) |
| <img src="https://github.com/Valera-2321.png" width="80" height="80" /> | **Jeremy Valera** | Carrito Autónomo (motores, diseño físico, navegación) | [@Valera-2321](https://github.com/Valera-2321) |

