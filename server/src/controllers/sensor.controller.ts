import { NextFunction, Request, Response } from "express"
import { SensorSchema } from "../schemas/sensor.shema"

const create = async (req: Request<{}, {}, SensorSchema>, res: Response, next: NextFunction) => {
  try {
    const sensorData = req.body

    res.status(201).json({ message: 'sensor data added', data: sensorData })
  } catch (error) {
    next(error)
  }
}

export { create }