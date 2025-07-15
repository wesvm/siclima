import { Card, CardContent, CardHeader, CardTitle } from "@/components/ui/card";
import { AlertTriangle, CheckCircle, Wifi } from "lucide-react";

export function Warning() {
  return (
    <Card>
      <CardHeader>
        <CardTitle className="flex items-center gap-2">
          <AlertTriangle className="h-5 w-5 text-yellow-500" />
          Alertas y Notificaciones
        </CardTitle>
      </CardHeader>
      <CardContent>
        <div className="space-y-3">
          <div className="flex items-center gap-3 p-3 bg-green-50 rounded-lg">
            <CheckCircle className="h-5 w-5 text-green-500" />
            <div>
              <p className="text-sm font-medium">Sistema funcionando correctamente</p>
              <p className="text-xs text-gray-500">Todos los sensores reportan valores normales</p>
            </div>
          </div>
          <div className="flex items-center gap-3 p-3 bg-blue-50 rounded-lg">
            <Wifi className="h-5 w-5 text-blue-500" />
            <div>
              <p className="text-sm font-medium">Conectividad estable</p>
              <p className="text-xs text-gray-500">Señal WiFi fuerte detectada</p>
            </div>
          </div>
        </div>
      </CardContent>
    </Card>
  );
}
