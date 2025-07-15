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

type HistoryItem = {
  time: string
  dhtTemp: string
  humidity: string
  bmpTemp: string
  pressure: string
  altitude: string
}

type SensorHistoryTableProps = {
  data: HistoryItem[]
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
                <TableCell>{reading.dhtTemp}</TableCell>
                <TableCell>{reading.humidity}</TableCell>
                <TableCell>{reading.bmpTemp}</TableCell>
                <TableCell>{reading.pressure}</TableCell>
                <TableCell>{reading.altitude}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </CardContent>
    </Card>
  )
}
