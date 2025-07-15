import { historicalData, sensorData } from "@/lib/placeholder-data";
import { Warning } from "@/components/warning";
import { SensorCard } from "@/components/sensor-card";
import { SensorHistoryTable } from "@/components/sensor-history-table";

export default function SensorDashboard() {
  return (
    <div className="max-w-7xl mx-auto space-y-6">
      <div className="flex items-center justify-between">
        <div>
          <h1 className="text-3xl font-bold text-gray-900">Dashboard de Sensores</h1>
          <p className="text-gray-600">Monitoreo en tiempo real del carrito móvil</p>
        </div>
        <div className="flex items-center gap-4">
          <div className="flex items-center gap-2">
            <div className="w-3 h-3 bg-green-500 rounded-full animate-pulse"></div>
            <span className="text-sm text-gray-600">En línea</span>
          </div>
        </div>
      </div>

      <div className="grid grid-cols-1 lg:grid-cols-2 gap-6">
        <SensorCard name="DHT22" icon="thermometer" data={sensorData.dht22} />
        <SensorCard name="BMP280" icon="gauge" data={sensorData.bmp280} />
      </div>
      <SensorHistoryTable data={historicalData} />
      <Warning />
    </div>
  )
}
