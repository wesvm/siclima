import { NextFunction, Request, Response } from "express"
import { SensorSchema, transformSensorData } from "../schemas/sensor.shema"

const create = async (req: Request<{}, {}, SensorSchema>, res: Response, next: NextFunction) => {
  try {
    const rawSensorData = req.body
    const sensorData = transformSensorData(rawSensorData)

    res.status(201).json({ message: 'sensor data added', data: sensorData })
  } catch (error) {
    next(error)
  }
}

export { create }