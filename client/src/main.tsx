import { StrictMode } from 'react'
import { createRoot } from 'react-dom/client'
import './index.css'

import DashboardLayout from '@/app/layout'
import SensorDashboard from './app/page'

createRoot(document.getElementById('root')!).render(
  <StrictMode>
    <DashboardLayout>
      <SensorDashboard />
    </DashboardLayout>
  </StrictMode>,
)
