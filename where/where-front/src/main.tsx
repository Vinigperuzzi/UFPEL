import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import { createBrowserRouter, RouterProvider } from "react-router-dom";
import Login from './pages/Login.tsx';
import Register from './pages/Register.tsx';
import Map from './pages/Map.tsx';
import Events from './pages/Events.tsx';
import EventVision from './pages/EventVision.tsx';
import EventForm from './pages/EventForm.tsx';
import ClassifyEvent from './pages/ClassifyEvent.tsx';
import EditEvent from './pages/EditEvent.tsx';

const router = createBrowserRouter([
  {
    path: "/",
    element: <Login />
  },
  {
    path: "/register",
    element: <Register />
  },
  {
    path: "/map",
    element: <Map />
  },
  {
    path: "/events",
    element: <Events />
  },
  {
    path: "/eventoForm/",
    element: <EventForm />
  },
  {
    path: "/evento/:id/classify", // Adicione uma barra inicial aqui
    element: <ClassifyEvent />
  },
  {
    path: "/evento/:index",
    element: <EventVision />
  },
  {
    path: "/editevento/:index",
    element: <EditEvent/>
  }
]);

ReactDOM.createRoot(document.getElementById('root')!).render(
  <React.StrictMode>
    <RouterProvider router = {router}/> 
  </React.StrictMode>,
)
