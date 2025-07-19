import { Card, CardHeader, CardTitle, CardContent } from "@/components/ui/card"
import { Badge } from "@/components/ui/badge"
import { Thermometer, Gauge } from "lucide-react"

type SensorDataSection = {
  [key: string]: {
    value: number | undefined
    unit: string
  }
}

type SensorCardProps = {
  name: string
  icon: keyof typeof iconMap
  data: SensorDataSection
  status?: boolean
}

const iconMap = {
  thermometer: <Thermometer className="h-5 w-5 text-red-500" />,
  gauge: <Gauge className="h-5 w-5 text-purple-500" />,
}

export function SensorDataCard({ name, icon, data, status }: SensorCardProps) {

  return (
    <Card>
      <CardHeader>
        <CardTitle className="flex items-center gap-2">
          {iconMap[icon]} Sensor {name.toUpperCase()}
        </CardTitle>
      </CardHeader>
      <CardContent>
        <div className="space-y-3">
          {Object.entries(data).map(([label, { value, unit }]) => (
            <div key={label} className="flex justify-between items-center">
              <span className="text-sm text-gray-600 capitalize">{label}:</span>
              <span className="font-medium">{value == undefined ? "--" : `${value} ${unit}`}</span>
            </div>
          ))}

          <div className="flex justify-between items-center">
            <span className="text-sm text-gray-600">Estado:</span>
            <Badge className={status ? "bg-green-100 text-green-800" : "bg-red-100 text-red-800"}>
              {status ? "Activo" : "Inactivo"}
            </Badge>
          </div>
        </div>
      </CardContent>
    </Card>
  )
}
