import { useState, useEffect } from 'react';
import Header from '../components/Header';
import styles from './Events.module.css';
import { Link, useNavigate } from 'react-router-dom';
import PlusSymbol from '../assets/plusSymbol.png';
import { promoterChecker } from '../services/promoter';
import { getEvents } from '../services/event';
import gear from '../assets/gear.png'

function Events() {
  const navigate = useNavigate();
  const [isPromoter, setIsPromoter] = useState(false);
  const [events, setEvents] = useState([]);
  const [showEventsStartingWithB, setShowEventsStartingWithB] = useState(false); // Estado para alternar entre mostrar todos e mostrar eventos com nomes começando com "B"

  useEffect(() => {
    // Função para buscar eventos
    async function fetchEvents() {
      try {
        const response = await getEvents();
        setEvents(response); // Define o estado com os eventos obtidos
      } catch (error) {
        console.error('Erro ao buscar eventos:', error);
      }
    }

    fetchEvents(); // Chama a função de busca de eventos ao montar o componente
  }, []);

  useEffect(() => {
    promoterChecker().then((result) => {
      setIsPromoter(result);
    });
  }, []);

  // Função para filtrar eventos com base em uma condição
  const filterEvents = (condition) => {
    const filtered = events.filter((event) => condition(event));
    return filtered;
  };

  // Renderização condicional com base no estado de showEventsStartingWithB
  const filteredEvents = showEventsStartingWithB
    ? filterEvents((event) => event.nome && event.isCreator)
    : events;

  const toggleShowEventsStartingWithB = () => {
    setShowEventsStartingWithB((prevState) => !prevState);
  };

  // Renderização condicional com base no estado de isPromoter
  const renderAddEventLink = () => {
    if (isPromoter) {
      return (
        <Link to="/eventoForm/" className={styles.gridItemAdd}>
          <img src={PlusSymbol} alt="Adicionar Evento" />
        </Link>
      );
    }
    return null; // Não renderiza o link se não for um promotor
  };

  return (
    <>
      <Header toMap={true} />

      {isPromoter && (
        <label className={styles.label}>
          Meus Eventos
          <input
            type="checkbox"
            checked={showEventsStartingWithB}
            onChange={toggleShowEventsStartingWithB}
            className={styles.checkbox}
          />
        </label>
      )}

      <div className={styles.gridContainer}>
        <div className={styles.grid}>

            {filteredEvents.map((event) => {
              const uint8Array = new Uint8Array(event.foto.buffer.data);
              const blob = new Blob([uint8Array], { type: 'application/octet-stream' });
              const url = URL.createObjectURL(blob);

              if (event.isCreator) {
                return (
                  <Link key={event.codEvento} to={`/evento/${event.codEvento}`} className={styles.gridItem}>
                    {event.foto && event.foto.buffer && <img src={url} alt={`Evento ${event.codEvento}`} />}
                    <span className={styles.eventTitle}>{event.nome}</span>

                    <button
                      className={styles.editButton}
                      onClick={(e) => {
                        e.preventDefault();
                        e.stopPropagation();
                        navigate(`/editEvento/${event.codEvento}`);
                      }}
                    >
                      <img src={gear} />
                    </button>
                  </Link>
                );
              }

              return (
                <Link key={event.codEvento} to={`/evento/${event.codEvento}`} className={styles.gridItem}>
                  {event.foto && event.foto.buffer && <img src={url} alt={`Evento ${event.codEvento}`} />}
                  <span className={styles.eventTitle}>{event.nome}</span>
                </Link>
              );
            })}

          {renderAddEventLink()}
        </div>
      </div>
    </>
  );
}

export default Events;
