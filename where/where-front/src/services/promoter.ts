import axios from 'axios';
import Cookies from 'js-cookie';

export const baseUrl = axios.create({
  baseURL: 'http://localhost:3000'
});

export async function turnOnPromoter() {

  try {

    const token = Cookies.get('where-access-token');

    const response = await baseUrl.post('/user/upgrade', null, {
        headers: {
            'where-access-token': token,
        },
    });

    console.log("Resposta (TurnOnPromoter):", response.data);
    
    return response.data.isPromoter;
  } catch (error) {
    console.error("Resposta (TurnOnPromoter):", error);
    throw error;
  }
}

export async function turnOffPromoter() {

    try {
  
      const token = Cookies.get('where-access-token');
  
      const response = await baseUrl.post('/user/downgrade', null, {
          headers: {
              'where-access-token': token,
          },
      });

      return response.data;
    } catch (error) {
      console.error("Resposta (TurnOffPromoter):", error);
      throw error;
    }
}

export async function promoterChecker() {

    try {
  
      const token = Cookies.get('where-access-token');
  
      const response = await baseUrl.get('/user/promoter', {
          headers: {
              'where-access-token': token,
          },
      });
      
      return response.data.isPromoter;
    } catch (error) {
      console.error("Erro ao checar se o user é promoter.", error);
      throw error;
    }
}
