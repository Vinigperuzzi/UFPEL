import React, { useState } from 'react';
import styles from './Login.module.css';
import padlock from '../assets/padlock_icon.png';
import email from '../assets/email_icon.png';
import invisibleEye from '../assets/eye.png';
import { Link, useNavigate } from 'react-router-dom';
import { login } from '../services/login.ts';
import Cookies from 'js-cookie';

function Login() {

    const navigate = useNavigate()

    const [emailValue, setEmailValue] = useState('');
    const [passwordValue, setPasswordValue] = useState('');
    const [showPassword, setShowPassword] = useState(false);

    const toggleShowPassword = () => {
        setShowPassword(!showPassword);
    };

    const handleSubmit = async (event: React.FormEvent) => {
        event.preventDefault();
        try {
            const response = await login(emailValue, passwordValue);
            if (response && response.isLogged) {
                Cookies.set(response.cookieName, response.cookieInfo)
                console.log(Cookies.get(response.cookieName));
                
                navigate('/map');
            }
        } catch (error) {
            console.error("Erro ao fazer login:", error);
        }
    };

    return (
        <>
            <article className={styles.sidebar}>
                <div>
                    <h1 className={styles.title}>Entrar</h1>
                    <span className={styles.titleSpan}>Se você não tiver uma conta, <Link to="/register" className={styles.signUpLink}>registre-se</Link></span>
                </div>

                <form className={styles.form} onSubmit={handleSubmit}>
                    <div className={styles.inputContainer}>
                        <label className={styles.inputLabel} htmlFor="email">E-mail</label>
                        <div className={styles.inputOuterStyle}>
                            <img className={styles.inputIcon} src={email} alt="" />
                            <input
                                className={styles.input}
                                placeholder="Entre com seu endereço de email"
                                type="text"
                                id="email"
                                value={emailValue}
                                onChange={(e) => setEmailValue(e.target.value)}
                            />
                        </div>
                    </div>

                    <div className={styles.inputContainer}>
                        <label className={styles.inputLabel} htmlFor="password">Senha</label>
                        <div className={styles.inputOuterStyle}>
                            <img className={styles.inputIcon} src={padlock} alt="" />
                            <input
                                type={showPassword ? 'text' : 'password'}
                                id="password"
                                className={styles.input}
                                placeholder="Entre com sua senha"
                                value={passwordValue}
                                onChange={(e) => setPasswordValue(e.target.value)}
                            />
                            <button className={styles.inputIconButton} onClick={toggleShowPassword} type="button">
                                <img src={invisibleEye} alt="Mostrar Senha" />
                            </button>
                        </div>
                    </div>

                    <button type="submit" className={styles.loginButton}>Entrar</button>
                    <Link to="/map" className={styles.signUpLink}>Ir para Mapa (Dev Only)</Link>
                </form>
            </article>
        </>
    )
}

export default Login;
