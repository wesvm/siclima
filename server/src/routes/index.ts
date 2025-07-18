import { Router } from "express"
import { create } from "../controllers/sensor.controller"
import validation from "../middlewares/validation"
import { sensorSchema } from "../schemas/sensor.shema"
const router = Router()

router.post('/sensors', validation(sensorSchema), create)

export default router