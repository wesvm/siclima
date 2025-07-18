import { Request, Response, NextFunction } from "express"
import { type z } from "zod"

export default (schema: z.Schema) => {
  return (req: Request, res: Response, next: NextFunction) => {
    const result = schema.safeParse(req.body)

    if (!result.success) {
      const errors = result.error.flatten()
      res.status(422).json({
        error: "Validation error",
        errors: errors.fieldErrors,
      })
      return
    }

    next()
  }
}