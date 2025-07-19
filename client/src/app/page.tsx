import { useEffect, useState } from "react";
import api from "@/lib/api";
import type { RawSensorReading, SensorData } from "@/lib/types";
import { socket } from "@/app/socket";
import { Warning } from "@/components/warning";
import { SensorDataCard } from "@/components/sensor-data-card";
import { SensorHistoryTable } from "@/components/sensor-history-table";

export default function SensorDashboard() {
  const [historicalData, setHistoricalData] = useState<RawSensorReading[]>([])
  const [sensorData, setSensorData] = useState<SensorData | null>(null)
  const [isConnected, setIsConnected] = useState<boolean>(false)

  useEffect(() => {
    api.sensors.list().then(setHistoricalData)

    if (!socket.connected) socket.connect()
    socket.on("connect", () => setIsConnected(true))
    socket.on("disconnect", () => setIsConnected(false))
    socket.on("sensor:data", (payload: SensorData) => {
      setSensorData(payload)
    })

    return () => {
      socket.off("connect")
      socket.off("disconnect")
      socket.off("sensor:data")
      socket.disconnect()
    }
  }, [])

  return (
    <div className="max-w-7xl mx-auto space-y-6">
      <div className="flex items-center justify-between">
        <div>
          <h1 className="text-3xl font-bold text-gray-900">Dashboard de Sensores</h1>
          <p className="text-gray-600">Monitoreo en tiempo real del carrito móvil</p>
        </div>
        <div className="flex items-center gap-4">
          <div className="flex items-center gap-2">
            <div className={`w-3 h-3 rounded-full ${isConnected ? "bg-green-500" : "bg-red-500"} animate-pulse`} />
            <span className="text-sm text-gray-600">{isConnected ? "En línea" : "Desconectado"}</span>
          </div>
        </div>
      </div>

      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
        <SensorDataCard
          name="DHT22"
          icon="thermometer"
          data={{
            temperatura: {
              value: sensorData?.dht22.temperature,
              unit: "°C",
            },
            humedad: {
              value: sensorData?.dht22.humidity,
              unit: "%",
            },
          }}
          status={sensorData?.dht22.status}
        />

        <SensorDataCard
          name="BMP280"
          icon="gauge"
          data={{
            temperatura: {
              value: sensorData?.bmp280.temperature,
              unit: "°C",
            },
            presion: {
              value: sensorData?.bmp280.pressure,
              unit: "hPa",
            },
            altitud: {
              value: sensorData?.bmp280.altitude,
              unit: "m",
            },
          }}
          status={sensorData?.bmp280.status}
        />

      </div>
      <SensorHistoryTable historicalData={historicalData} />
      <Warning />
    </div>
  )
}
