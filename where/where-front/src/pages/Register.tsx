import React, { useState } from 'react';
import styles from './Register.module.css';
import padlock from '../assets/padlock_icon.png';
import email from '../assets/email_icon.png';
import invisibleEye from '../assets/eye.png';
import { Link, useNavigate } from 'react-router-dom';
import { signup } from '../services/signup';

function Register() {
    const navigate = useNavigate();

    const [emailValue, setEmailValue] = useState('');
    const [usernameValue, setUsernameValue] = useState('');
    const [passwordValue, setPasswordValue] = useState('');
    const [confirmPasswordValue, setConfirmPasswordValue] = useState('');

    const [showPassword, setShowPassword] = useState(false);

    const toggleShowPassword = () => {
        setShowPassword(!showPassword);
    };

    const [showPassword2, setShowPassword2] = useState(false);

    const toggleShowPassword2 = () => {
        setShowPassword2(!showPassword2);
    };

    const handleSubmit = async (event: React.FormEvent) => {
        event.preventDefault();

        if (passwordValue !== confirmPasswordValue) {
            alert('As senhas não coincidem. Por favor, verifique suas senhas.');
            return;
        }

        try {
            const response = await signup(usernameValue, emailValue, passwordValue);
            if (response && response.isCreated) {
                navigate('/');
            }
        // eslint-disable-next-line @typescript-eslint/no-explicit-any
        } catch (error: any) {
            console.log(error);
            alert("Erro ao registrar: " + error.response.data.error)
        }
    };

    return (
        <>
            <article className={styles.sidebar}>
                <div>
                    <h1 className={styles.title}>Criar Conta</h1>
                    <span className={styles.titleSpan}>
                        Se você já tiver uma conta,{' '}
                        <Link to="/" className={styles.signUpLink}>
                            entre aqui!
                        </Link>
                    </span>
                </div>

                <form className={styles.form} onSubmit={handleSubmit}>
                    <div className={styles.inputContainer}>
                        <label className={styles.inputLabel} htmlFor="email">
                            E-mail
                        </label>
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
                        <label className={styles.inputLabel} htmlFor="username">
                            Nome de Usuário
                        </label>
                        <div className={styles.inputOuterStyle}>
                            <img className={styles.inputIcon} src={email} alt="" />
                            <input
                                className={styles.input}
                                placeholder="Digite seu nome de usuário"
                                type="text"
                                id="username"
                                value={usernameValue}
                                onChange={(e) => setUsernameValue(e.target.value)}
                            />
                        </div>
                    </div>

                    <div className={styles.inputContainer}>
                        <label className={styles.inputLabel} htmlFor="password">
                            Senha
                        </label>
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
                            <button
                                className={styles.inputIconButton}
                                onClick={toggleShowPassword}
                                type="button"
                            >
                                <img src={invisibleEye} alt="Mostrar Senha" />
                            </button>
                        </div>
                    </div>

                    <div className={styles.inputContainer}>
                        <label className={styles.inputLabel} htmlFor="confirmPassword">
                            Confirmar Senha
                        </label>
                        <div className={styles.inputOuterStyle}>
                            <img className={styles.inputIcon} src={padlock} alt="" />
                            <input
                                type={showPassword2 ? 'text' : 'password'}
                                id="confirmPassword"
                                className={styles.input}
                                placeholder="Confirmar sua senha"
                                value={confirmPasswordValue}
                                onChange={(e) => setConfirmPasswordValue(e.target.value)}
                            />
                            <button
                                className={styles.inputIconButton}
                                onClick={toggleShowPassword2}
                                type="button"
                            >
                                <img src={invisibleEye} alt="Mostrar Senha" />
                            </button>
                        </div>
                    </div>

                    <button type="submit" className={styles.loginButton}>
                        Registrar
                    </button>
                </form>
            </article>
        </>
    );
}

export default Register;
