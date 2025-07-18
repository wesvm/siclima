import type { Socket } from "socket.io"

export function socketHandlers(socket: Socket) {
  socket.on("ping", () => {
    console.log("Received ping")
    socket.emit("pong")
  })

  socket.on("disconnect", () => {
    console.log(`Socket disconnected: ${socket.id}`)
  })
}
