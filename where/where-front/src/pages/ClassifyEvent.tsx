/* eslint-disable */
import Header from '../components/Header';
import styles from './ClassifyEvent.module.css';
import { Rating } from '@mui/material';
import StarIcon from '@mui/icons-material/Star';
import { useParams, useNavigate } from 'react-router-dom';
import { useState, useEffect } from 'react';
import { getOneEvent, postAvaliacao } from '../services/event';

function ClassifyEvent() {

    const navigate = useNavigate();

    const [userRating, setUserRating] = useState(0);
    const [event, setEvent] = useState(0);
    const [imgUrl, setUrl] = useState('');
    const [inputContent, setInputContent] = useState(''); // Adicione um estado para o conteúdo do campo de entrada

    const params = useParams();
    const id = params.id;

    const handleRatingChange = (newValue: any) => {
        setUserRating(newValue);
    };

    const handleInputChange = (e: any) => {
        // Atualize o estado do campo de entrada com o valor digitado
        setInputContent(e.target.value);
    };

    const handleFormSubmit = async (e: any) => {
        e.preventDefault();
        
        console.log('Rating:', userRating);
        console.log('Input Content:', inputContent);

        try {
            const response = await postAvaliacao(id, inputContent, userRating);
            console.log(response);
            if(response){
                navigate('/events')
            }
        } catch (error) {
            console.error('Erro ao enviar avaliação:', error);
        }
    };

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = await getOneEvent(id);
                console.log(response);
                setEvent(response);

                // Gere a URL somente quando a resposta estiver pronta
                const uint8Array = new Uint8Array(response.foto.buffer.data);
                const blob = new Blob([uint8Array], { type: "application/octet-stream" });
                const url = URL.createObjectURL(blob);
                setUrl(url);
            } catch (error) {
                console.error('Erro ao buscar evento:', error);
            }
        };

        if (id !== undefined) {
            fetchData();
        }
    }, [id]);

    return (
        <>
            <Header toMap={false} />
            <div className={styles.eventVisionContainer}>

                <div className={styles.eventBannerContainer}>
                    <img className={styles.eventBanner} src={imgUrl} alt="Banner do evento" />
                </div>

                <div className={styles.userEvaluationContainer}>
                    <div className={styles.evaluation}>
                        <Rating
                            name="rating"
                            value={userRating}
                            precision={0.1}
                            size="large"
                            onChange={(event, newValue) => handleRatingChange(newValue)}
                            icon={<StarIcon style={{ color: '#2ECA45', fontSize: '4rem' }} />}
                            emptyIcon={<StarIcon style={{ color: 'grey', fontSize: '4rem' }} />}
                        />
                    </div>
                </div>

                <form onSubmit={handleFormSubmit} className = { styles.bottomForm }>
                    <input
                        type="text"
                        className={styles.inputUser}
                        placeholder="Digite algo..."
                        value={inputContent} // Defina o valor do campo de entrada com base no estado
                        onChange={handleInputChange} // Adicione um manipulador de evento para atualizar o estado
                    />
                    <button type='submit' className={styles.confirmButton}>Confirmar</button>
                </form>

            </div>
        </>
    )
}

export default ClassifyEvent;
