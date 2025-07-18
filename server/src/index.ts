import express from 'express'
import cors from "cors"
import router from './routes'
import errorHandler from "./middlewares/error"

import { createServer } from 'node:http'
import { setupSocket } from './sockets'

const PORT = process.env.PORT ?? 3000
const app = express()
app.disable("x-powered-by")
app.use(express.json())
app.use(cors())
app.use("/api", router)
app.use(errorHandler)

const server = createServer(app)
setupSocket(server)

server.listen(PORT, () => {
  console.log(`server is running on port ${PORT}`)
})