import { useEffect } from "react"
import { socket } from "@/app/socket"

export function useSocket() {
  useEffect(() => {
    socket.connect()

    return () => {
      socket.disconnect()
    }
  }, [])
}
