import Header from '../components/Header';
import styles from './Date.module.css';

interface Props {
    title: string
}

function Date(props:Props) {
    return (
        <>
            <Header/>
            <article className={styles.sidebar}>
                <h1 className={styles.title}>{props.title}</h1>
                <form className={styles.form} action="submit">
                    <input type="time" className={styles.timeInput} />
                    <div className={styles.inputContainer}>
                        <button formAction="submit" className={styles.confirmButton}>Confirmar</button>
                        <button formAction="submit" className={styles.cancelButton}>Cancelar</button>
                    </div>
                </form>
            </article>
        </>
    );
}

export default Date;
