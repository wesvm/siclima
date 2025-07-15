const sensorData = {
  dht22: {
    temperature: { value: 24.5, unit: "°C", status: "normal" },
    humidity: { value: 68.2, unit: "%", status: "normal" },
  },
  bmp280: {
    temperature: { value: 24.1, unit: "°C", status: "normal" },
    pressure: { value: 1013.25, unit: "hPa", status: "normal" },
    altitude: { value: 145.8, unit: "m", status: "normal" },
  },
  system: {
    battery: { value: 87, unit: "%", status: "good" },
    signal: { value: -45, unit: "dBm", status: "excellent" },
  },
}

const historicalData = [
  {
    time: "14:30",
    dhtTemp: "24.5°C",
    humidity: "68.2%",
    bmpTemp: "24.1°C",
    pressure: "1013.25 hPa",
    altitude: "145.8 m",
  },
  {
    time: "14:25",
    dhtTemp: "24.2°C",
    humidity: "67.8%",
    bmpTemp: "23.9°C",
    pressure: "1013.20 hPa",
    altitude: "145.9 m",
  },
  {
    time: "14:20",
    dhtTemp: "23.8°C",
    humidity: "69.1%",
    bmpTemp: "23.6°C",
    pressure: "1013.15 hPa",
    altitude: "146.0 m",
  },
  {
    time: "14:15",
    dhtTemp: "23.5°C",
    humidity: "70.3%",
    bmpTemp: "23.2°C",
    pressure: "1013.10 hPa",
    altitude: "146.2 m",
  },
  {
    time: "14:10",
    dhtTemp: "23.2°C",
    humidity: "71.5%",
    bmpTemp: "22.9°C",
    pressure: "1013.05 hPa",
    altitude: "146.3 m",
  },
]

export { sensorData, historicalData };