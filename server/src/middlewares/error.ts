import { Request, Response, NextFunction } from "express"

export default (err: any, _req: Request, res: Response, _next: NextFunction) => {
  console.error("Error:", err)

  res.status(500).json({
    error: err.message || "Something went wrong",
  })
}