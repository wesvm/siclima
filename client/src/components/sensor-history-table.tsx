import { useState } from "react"
import type { RawSensorReading } from "@/lib/types"
import { Button } from "@/components/ui/button"
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
import { ArrowLeft, ArrowRight } from "lucide-react"

type SensorHistoryTableProps = {
  historicalData: RawSensorReading[]
}

export function SensorHistoryTable({ historicalData }: SensorHistoryTableProps) {
  const [currentPage, setCurrentPage] = useState(1)
  const itemsPerPage = 5
  const totalPages = Math.ceil(historicalData.length / itemsPerPage)
  const startIndex = (currentPage - 1) * itemsPerPage
  const endIndex = startIndex + itemsPerPage
  const currentData = historicalData.slice(startIndex, endIndex)

  return (
    <Card>
      <CardHeader>
        <CardTitle>Datos Históricos</CardTitle>
        <p className="text-sm text-gray-600">Últimas lecturas de los sensores</p>
      </CardHeader>
      <CardContent>
        <HistoricalTable historicalData={currentData} />

        {historicalData.length > 0 && (
          <PaginationControls
            currentPage={currentPage}
            totalPages={totalPages}
            totalItems={historicalData.length}
            startIndex={startIndex}
            endIndex={endIndex}
            onPageChange={setCurrentPage}
          />
        )}
      </CardContent>
    </Card>
  )
}

function HistoricalTable({ historicalData: data }: SensorHistoryTableProps) {
  return (
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
        {data.length ? (
          data.map((reading, i) => (
            <TableRow key={i}>
              <TableCell className="font-medium">{reading.time}</TableCell>
              <TableCell>{reading.dhtTemp} °C</TableCell>
              <TableCell>{reading.humidity} %</TableCell>
              <TableCell>{reading.bmpTemp} °C</TableCell>
              <TableCell>{reading.pressure} hPa</TableCell>
              <TableCell>{reading.altitude} m</TableCell>
            </TableRow>
          ))
        ) : (
          <TableRow>
            <TableCell colSpan={6} className="text-gray-500 h-24 text-center">
              No hay datos históricos disponibles
            </TableCell>
          </TableRow>
        )}
      </TableBody>
    </Table>
  )
}

type PaginationControlsProps = {
  currentPage: number
  totalPages: number
  totalItems: number
  startIndex: number
  endIndex: number
  onPageChange: (page: number) => void
}

export function PaginationControls({
  currentPage,
  totalPages,
  onPageChange
}: PaginationControlsProps) {
  return (
    <div className="flex items-center justify-end space-x-2 py-4">
      <div className="flex items-center space-x-2">
        <Button
          variant="ghost"
          size="sm"
          onClick={() => onPageChange(currentPage - 1)}
          disabled={currentPage === 1}
        >
          <ArrowLeft className="size-4" />
        </Button>

        <div className="flex items-center space-x-1">
          {Array.from({ length: totalPages }, (_, i) => i + 1).map((page) => (
            <Button
              key={page}
              variant={currentPage === page ? "default" : "outline"}
              size="sm"
              onClick={() => onPageChange(page)}
              className="w-8 h-8 p-0"
            >
              {page}
            </Button>
          ))}
        </div>

        <Button
          variant="ghost"
          size="sm"
          onClick={() => onPageChange(currentPage + 1)}
          disabled={currentPage === totalPages}
        >
          <ArrowRight className="size-4" />
        </Button>
      </div>
    </div>
  )
}
