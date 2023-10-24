import { GoogleMap, LoadScript, Marker } from '@react-google-maps/api';
import icon from '../assets/map_pin2.png';
import { useEffect, useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { getEvents } from '../services/event';

const MapComponent = () => {

  const navigate = useNavigate();

  const containerStyle = {
    width: '1200px',
    height: '500px'
  };

  const apiKey = import.meta.env.VITE_GOOGLE_MAPS_API_KEY;

  const initialCenter = {
    lat:  -31.0332,
    lng:  -42.098632
  };

  const initialZoom = 5;

  const mapOptions = {
    disableDefaultUI: true,
    clickableIcons: false,
  };

  const [map, setMap] = useState<google.maps.Map | null>(null);
  const [markersVisible, setMarkersVisible] = useState(false);
  const [data, setData] = useState([{lat: 1.23, lng: 1.23, name: "alo"}]);

  const handleMarkerClick = (location: any) => {
    navigate(`/evento/${location.id}`);
  };

  useEffect(() => {
    // Verificar se o mapa foi carregado
    if (map) {
      // Agora que o mapa está carregado, podemos exibir os marcadores
      setMarkersVisible(true);
    }
  }, [map]);

  useEffect(() => {
    // Função assíncrona para buscar os eventos
    async function fetchEvents() {
      try {
        const response = await getEvents(); // Aguarde a resolução da promessa
        console.log(response);

        // Popule data com os dados da resposta
        const newData = response.map((event) => ({
          lat: parseFloat(event.latitude),
          lng: parseFloat(event.longitude),
          name: event.nome,
          id: event.codEvento
        }));

        console.log(newData);
        

        setData(newData); // Atualize o estado data com os dados

      } catch (error) {
        console.error('Erro ao buscar eventos:', error);
      }
    }

    // Chame a função para buscar os eventos
    fetchEvents();
  }, []); // Certifique-se de fornecer uma dependência vazia para executar isso apenas uma vez

  return (
    <LoadScript googleMapsApiKey={apiKey}>
      <GoogleMap
        mapContainerStyle={containerStyle}
        center={initialCenter}
        zoom={initialZoom}
        options={mapOptions}
        onLoad={(map) => setMap(map)}
      >
        <Marker position={initialCenter} title="Marcador Inicial" />
        {markersVisible && data.map((location, index) => (
          <Marker
            key={index}
            position={{ lat: location.lat, lng: location.lng }}
            title={location.name}
            onClick={() => handleMarkerClick(location)}
            icon={{ url: icon, scaledSize: new window.google.maps.Size(30,45) }}
          />
        ))}
      </GoogleMap>
    </LoadScript>
  );
};

export default MapComponent;
