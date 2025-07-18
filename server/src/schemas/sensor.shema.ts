import z from "zod"

export const sensorSchema = z.object({
  time: z.string().trim().min(1, "Time is required"),
  dhtTemp: z.number(),
  humidity: z.number(),
  bmpTemp: z.number(),
  pressure: z.number(),
  altitude: z.number(),
  dhtStatus: z.boolean().optional(),
  bmpStatus: z.boolean().optional(),
})

export type SensorSchema = z.infer<typeof sensorSchema>;