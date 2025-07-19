import type { Socket } from "socket.io"
import { sensorSchema, transformSensorData } from "../schemas/sensor.shema"

export function socketHandlers(socket: Socket) {
  socket.on("sensor:data", (payload) => {
    const parsed = sensorSchema.safeParse(payload)
    if (!parsed.success) return console.error("Invalid sensor data")

    const raw = parsed.data
    const sensorData = transformSensorData(raw)

    console.log("Received sensor data:", sensorData)
    socket.broadcast.emit("sensor:data", sensorData)
  })
}
