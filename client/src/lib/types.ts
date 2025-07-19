export type RawSensorReading = {
  time: string
  dhtTemp: number
  humidity: number
  bmpTemp: number
  pressure: number
  altitude: number
  dhtStatus?: boolean
  bmpStatus?: boolean
}

export type SensorData = {
  time: string
  dht22: {
    temperature: number
    humidity: number
    status?: boolean
  }
  bmp280: {
    temperature: number
    pressure: number
    altitude: number
    status?: boolean
  }
}