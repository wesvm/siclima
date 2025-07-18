import { io, Socket } from "socket.io-client"

const URL = import.meta.env.VITE_PUBLIC_SERVER_URL

export const socket: Socket = io(URL, {
  autoConnect: false,
})
