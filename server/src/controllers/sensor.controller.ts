import { NextFunction, Request, Response } from "express"
import { SensorSchema, transformSensorData } from "../schemas/sensor.shema"

const create = async (req: Request<{}, {}, SensorSchema>, res: Response, next: NextFunction) => {
  try {
    const rawSensorData = req.body
    const sensorData = transformSensorData(rawSensorData)

    const response = await fetch(process.env.GOOGLE_SHEET_URL!, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(rawSensorData),
    })

    if (!response.ok) {
      const errorText = await response.text()
      throw new Error(`Google Sheet error: ${response.status} - ${errorText}`)
    }

    res.status(201).json({ message: 'sensor data added', data: sensorData })
  } catch (error) {
    next(error)
  }
}

export { create }