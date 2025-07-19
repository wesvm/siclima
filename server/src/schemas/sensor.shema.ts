import z from "zod"

export const sensorSchema = z.object({
  time: z.string().trim().min(1, "Time is required"),
  dhtTemp: z.number(),
  humidity: z.number(),
  dhtStatus: z.boolean().optional(),
  bmpTemp: z.number(),
  pressure: z.number(),
  altitude: z.number(),
  status: z.boolean().optional(),
  bmpStatus: z.boolean().optional(),
})

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

export function transformSensorData(raw: z.infer<typeof sensorSchema>): SensorData {
  return {
    time: raw.time,
    dht22: {
      temperature: raw.dhtTemp,
      humidity: raw.humidity,
      status: raw.dhtStatus ?? false,
    },
    bmp280: {
      temperature: raw.bmpTemp,
      pressure: raw.pressure,
      altitude: raw.altitude,
      status: raw.bmpStatus ?? false,
    },
  }
}

export type SensorSchema = z.infer<typeof sensorSchema>;