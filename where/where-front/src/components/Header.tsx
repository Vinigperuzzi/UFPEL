import { useState, useEffect } from 'react';
import { Link } from 'react-router-dom';
import { createTheme, ThemeProvider } from '@mui/material/styles';
import FormControlLabel from '@mui/material/FormControlLabel';
import { styled } from '@mui/material/styles';
import Switch, { SwitchProps } from '@mui/material/Switch';
import styles from './Header.module.css';
import { promoterChecker, turnOffPromoter, turnOnPromoter } from '../services/promoter';

const theme = createTheme({
  palette: {
    primary: {
      main: '#ff5722',
    },
    secondary: {
      main: '#9c27b0',
    },
  },
});

const IOSSwitch = styled((props: SwitchProps) => (
  <Switch focusVisibleClassName=".Mui-focusVisible" disableRipple {...props} />
))(({ theme }) => ({
  width: 42,
  height: 26,
  padding: 0,
  '& .MuiSwitch-switchBase': {
    padding: 0,
    margin: 2,
    transitionDuration: '300ms',
    '&.Mui-checked': {
      transform: 'translateX(16px)',
      color: '#fff',
      '& + .MuiSwitch-track': {
        backgroundColor: theme.palette.mode === 'dark' ? '#2ECA45' : '#EB4335',
        opacity: 1,
        border: 0,
      },
      '&.Mui-disabled + .MuiSwitch-track': {
        opacity: 0.5,
      },
    },
    '&.Mui-focusVisible .MuiSwitch-thumb': {
      color: '#33cf4d',
      border: '6px solid #fff',
    },
    '&.Mui-disabled .MuiSwitch-thumb': {
      color:
        theme.palette.mode === 'light'
          ? theme.palette.grey[100]
          : theme.palette.grey[600],
    },
    '&.Mui-disabled + .MuiSwitch-track': {
      opacity: theme.palette.mode === 'light' ? 0.7 : 0.3,
    },
  },
  '& .MuiSwitch-thumb': {
    boxSizing: 'border-box',
    width: 22,
    height: 22,
  },
  '& .MuiSwitch-track': {
    borderRadius: 26 / 2,
    backgroundColor: theme.palette.mode === 'light' ? '#E9E9EA' : '#39393D',
    opacity: 1,
    transition: theme.transitions.create(['background-color'], {
      duration: 500,
    }),
  },
}));

interface HeaderProps {
  toMap: boolean;
}

function Header(props: HeaderProps) {
  const [isPromoter, setIsPromoter] = useState(false);

  useEffect(() => {
    promoterChecker().then((result) => {
      setIsPromoter(result);
    });
  }, []);

  const handleChange = () => {
    const newPromoterState = !isPromoter;
    setIsPromoter(newPromoterState);

    if (newPromoterState) {
      turnOnPromoter().then((response) => {
        alert("Você virou promoter com sucesso!");
        window.location.reload();
        console.log(response);
      });
    } else {
      turnOffPromoter().then((response) => {
        alert("Você desvirou promoter com sucesso!");
        window.location.reload();
        console.log(response);
      });
    }
  };

  return (
    <ThemeProvider theme={theme}>
      <div className={styles.backgroundHeader}>
        <FormControlLabel
          control={
            <IOSSwitch sx={{ m: 1 }} checked={isPromoter} onChange={handleChange} />
          }
          label=""
        />

        {props.toMap ? (
          <Link to="/map" className={styles.linkToEvents}>
            Mapa
          </Link>
        ) : (
          <Link to="/events" className={styles.linkToEvents}>
            Eventos
          </Link>
        )}
      </div>
    </ThemeProvider>
  );
}

export default Header;
