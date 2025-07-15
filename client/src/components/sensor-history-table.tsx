// components/SensorHistoryTable.tsx
import {
  Card,
  CardHeader,
  CardTitle,
  CardContent,
} from "@/components/ui/card"
import {
  Table,
  TableHeader,
  TableRow,
  TableHead,
  TableBody,
  TableCell,
} from "@/components/ui/table"
import type { RawSensorReading } from "@/lib/types"

type SensorHistoryTableProps = {
  data: RawSensorReading[]
}

export function SensorHistoryTable({ data }: SensorHistoryTableProps) {
  return (
    <Card>
      <CardHeader>
        <CardTitle>Datos Históricos</CardTitle>
        <p className="text-sm text-gray-600">Últimas lecturas de los sensores</p>
      </CardHeader>
      <CardContent>
        <Table>
          <TableHeader>
            <TableRow>
              <TableHead>Hora</TableHead>
              <TableHead>DHT22 Temp</TableHead>
              <TableHead>Humedad</TableHead>
              <TableHead>BMP280 Temp</TableHead>
              <TableHead>Presión</TableHead>
              <TableHead>Altitud</TableHead>
            </TableRow>
          </TableHeader>
          <TableBody>
            {data.map((reading, i) => (
              <TableRow key={i}>
                <TableCell className="font-medium">{reading.time}</TableCell>
                <TableCell>{reading.dhtTemp} °C</TableCell>
                <TableCell>{reading.humidity} %</TableCell>
                <TableCell>{reading.bmpTemp} °C</TableCell>
                <TableCell>{reading.pressure} hPa</TableCell>
                <TableCell>{reading.altitude} m</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </CardContent>
    </Card>
  )
}
