import { Server as IOServer } from "socket.io"
import type { Server } from "http"
import { socketHandlers } from "./handlers"

export function setupSocket(server: Server) {
  const io = new IOServer(server, {
    cors: {
      origin: "*",
    },
  })

  io.on("connection", (socket) => {
    console.log(`socket connected`)
    socketHandlers(socket)
  })
}
