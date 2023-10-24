/* eslint-disable */
import { useState, useEffect } from 'react';
import { Link, useNavigate } from 'react-router-dom';
import Header from '../components/Header';
import styles from './EventForm.module.css';
import pinpoint_icon from '../assets/pinpoint_icon.png';
import calendar_icon from '../assets/calendar_icon.png';
import clock_icon from '../assets/clock_icon.png';
import person_icon from '../assets/person_icon.png';
import PlusSymbol from '../assets/plusSymbol.png';
import Map from '../components/Places';
import { createEvent, getOneEvent, deleteEvent } from '../services/event';
import { useParams } from 'react-router-dom';

function EditEvent() {

  const params = useParams();
  const id = params.index;
  const navigate = useNavigate();

  const [eventLocal, setEventLocal] = useState({
    address: '',
    lat: '',
    lng: '',
  });
  const [backgroundImage, setBackgroundImage] = useState('none');
  const [formImage, setFormImage] = useState('');
  const [eventTime, setEventTime] = useState('');
  const [eventDate, setEventDate] = useState('');

  useEffect(() => {
    async function fetchData() {
      try {
        const response = await getOneEvent(id);
        console.log(response);
  
        setEventTime(response.horario);
        setEventDate(response.inicio);
        setEventLocal({
          address: response.endereco,
          lat: parseFloat(response.latitude),
          lng: parseFloat(response.longitude),
        });
      } catch (error) {
        console.error('Erro ao buscar dados do evento:', error);
      }
    }
  
    fetchData();
  }, [id]);

  const [eventName, setEventName] = useState('');

  const handleFileChange = (e: any) => {
    const file = e.target.files[0];
    if (file) {
      setFormImage(file);
      const imageUrl = URL.createObjectURL(file);
      setBackgroundImage(`url(${imageUrl})`);
    } else {
      setBackgroundImage('none');
      setFormImage(null)
    }
  };

  const handleSelect = (data: any) => {
    setEventLocal(data);
  };

  useEffect(() => {
    if (eventLocal.address !== '') {
      console.log('Dados do Local:', eventLocal);
    }
  }, [eventLocal]);

  /*useEffect(() => {
      console.log('Dados do Tempo', eventTime, typeof(eventTime));
  }, [eventTime]);*/

  const handleDelete = async (event: any) => {
    event.preventDefault();
    try {
      const response = await deleteEvent(id);
        if (response) {
            console.log(response);
            navigate('/events');
        }
    } catch (error) {
        console.error("Erro ao deletar evento: ", error);
    }
  }


  const handleSubmit = async (event: any) => {
    event.preventDefault();

    const formData = new FormData();

    const timeFormat = eventTime.concat(":00");
    const horarioFormat = eventDate.concat(" " + timeFormat);
    console.log(horarioFormat);
    
    formData.append('nome', eventName);
    formData.append('horario', horarioFormat);
    formData.append('inicio', eventDate);
    formData.append('latitude', eventLocal.lat); // Truncar para 10 caracteres
    formData.append('longitude', eventLocal.lng);
    formData.append('endereco', eventLocal.address)
    formData.append('foto', formImage)
    formData.append('fim', 'null')
    formData.append('codEvento_fk', 'null')
    formData.append('estabelecimento', 'null')
    

    console.log(formData);
    
    for (const [key, value] of formData.entries()) {
      console.log(`${key}: ${value}`);
    }

    try {
      const response = await createEvent(formData);
        if (response) {
            console.log(response);
            navigate('/events');
        }
    } catch (error) {
        console.error("Erro ao criar evento: ", error);
    }
  }
    
  return (
    <>
      <Header toMap={false} />
      <div className={styles.formContainer}>
        <div className={styles.photoForm}>
          <span>Banner do Evento</span>
          <label
            className={styles.customFileInput}
            style={{
              backgroundImage: backgroundImage,
              backgroundColor: 'rgba(0, 0, 0, 0.5)',
              backgroundPosition: 'center center',
              backgroundSize: 'cover',
            }}
          >
            <input
              type="file"
              className={styles.inputPhoto}
              onChange={handleFileChange}
            />
            <span className={styles.plusSymbol}>
              <img src={PlusSymbol} alt="+" />
            </span>
          </label>
        </div>

        <div className={styles.textForm}>
          <div className={styles.leftColumn}>
            <div className={styles.inputContainer}>
              <label className={styles.inputLabel} htmlFor="eventname">
                Nome do evento
              </label>
              <div className={styles.inputOuterStyle}>
                <img className={styles.inputIcon} src={person_icon} alt="" />
                <input
                  className={styles.input}
                  placeholder="Adicione o nome do evento"
                  type="text"
                  id="eventname"
                  value={eventName}
                  onChange={(e) => setEventName(e.target.value)}
                />
              </div>
            </div>
            <div className={styles.inputContainer}>
              <label className={styles.inputLabel} htmlFor="eventLocal">
                Local do Evento
              </label>
              <div className={styles.inputOuterStyle}>
                <img className={styles.inputIcon} src={pinpoint_icon} alt="Localização" />
                <Map
                  setSelect={handleSelect}
                  value = { eventLocal.address }
                />
              </div>
            </div>
          </div>

          <div className={styles.rightColumn}>
            <div className={styles.inputContainer}>
              <label className={styles.inputLabel} htmlFor="eventTime">
                Hora do Evento
              </label>
              <div className={styles.inputOuterStyle}>
                <img className={styles.inputIcon} src={clock_icon} alt="" />
                <input
                  className={styles.input}
                  type="time"
                  id="eventTime"
                  value={eventTime}
                  onChange={(e) => setEventTime(e.target.value)}
                />
              </div>
            </div>

            <div className={styles.inputContainer}>
              <label className={styles.inputLabel} htmlFor="date">
                Data do Evento
              </label>
              <div className={styles.inputOuterStyle}>
                <img className={styles.inputIcon} src={calendar_icon} alt="" />
                <input
                  className={styles.input}
                  type="date"
                  value={eventDate}
                  onChange={(e) => setEventDate(e.target.value)}
                />
              </div>
            </div>
          </div>
        </div>
        <div className = {styles.buttonContainer}>
          <button type="submit" onClick = {handleSubmit} className={styles.submitButton}>Adicionar Evento</button>
          <button type="submit" onClick = {handleDelete} className={styles.deleteButton}>Excluir Evento</button>
        </div>
      </div>
    </>
  );
}

export default EditEvent;
