import type { RawSensorReading } from "@/lib/types"

const api = {
  sensors: {
    list: async (): Promise<RawSensorReading[]> => {
      const csv = await fetch(import.meta.env.VITE_PUBLIC_SENSOR_SHEET_URL!).then((res) => res.text())

      return csv
        .split("\n")
        .slice(1)
        .map((row) => {
          const [time, dhtTemp, humidity, bmpTemp, pressure, altitude] = row.trim().split(",")

          return {
            time,
            dhtTemp: parseFloat(dhtTemp),
            humidity: parseFloat(humidity),
            bmpTemp: parseFloat(bmpTemp),
            pressure: parseFloat(pressure),
            altitude: parseFloat(altitude),
          }
        })
    },
  },
}

export default api
