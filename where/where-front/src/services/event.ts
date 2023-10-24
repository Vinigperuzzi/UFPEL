/* eslint-disable */
import axios from 'axios';
import Cookies from 'js-cookie';

export const baseUrl = axios.create({
  baseURL: 'http://localhost:3000'
});

export async function createEvent(formdata: FormData) {
  try {

    const token = Cookies.get('where-access-token');

    const response = await baseUrl.post('/events', formdata, {
      headers: {
        'where-access-token': token,
      },
    });

    console.log("Res (EventCreate): ", response);
    
    return response.data;
  } catch (error) {
    console.error("Erro ao criar evento: ", error);
    throw error;
  }
}

export async function getEvents() {
  try {

    const token = Cookies.get('where-access-token');

    const response = await baseUrl.get('/events/all', {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao Pegar eventos ", error);
    throw error;
  }
}

export async function getOneEvent(id: string) {
  try {
    const token = Cookies.get('where-access-token');

    const response = await baseUrl.get(`/events/${id}`, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao Pegar eventos ", error);
    throw error;
  }
}

export async function confirmarParticipacao(codEvento: number, confirmed: boolean) {
  try {
    const token = Cookies.get('where-access-token');

    const json = {
      codEvento_fk: codEvento,
      confirmado: confirmed
    }

    let response;

    if (!json.confirmado) {
      response = await baseUrl.delete(`/participate`, {
        headers: {
          'where-access-token': token,
        },
        data: json, // Use a propriedade 'data' para enviar o JSON no corpo da solicitação DELETE
      });
    } else {
      response = await baseUrl.post(`/participate`, json, {
        headers: {
          'where-access-token': token,
        },
      });
    }
    
    return response.data;
  } catch (error) {
    console.error("Erro ao confirmar participação ", error);
    throw error;
  }
}

export async function verificarConfirmacao(id: number) {
  try {
    const token = Cookies.get('where-access-token');

    console.log("ID enviado:", id);
    

    const response = await baseUrl.get(`/participate/${id}`, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao verificar participação ", error);
    throw error;
  }
}

export async function numeroParticipantes(id: any) {
  try {
    const token = Cookies.get('where-access-token');

    const response = await baseUrl.get(`events/${id}/participating`, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao verificar participantes", error);
    throw error;
  }
}

export async function postAvaliacao(id: any, comentario: string, userRating: number) {
  try {
    const token = Cookies.get('where-access-token');

    const req = {
      codEvento_fk: id,
      comentario: comentario,
      rating: userRating
    }

    const response = await baseUrl.post(`ratings`, req, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao verificar participantes", error);
    throw error;
  }
}

export async function mediaRatings(id: number) {
  try {
    const token = Cookies.get('where-access-token');

    const response = await baseUrl.get(`ratings/average/${id}/`, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao consultar média", error);
    throw error;
  }
}

export async function ratingsAll(id: number) {
  try {
    const token = Cookies.get('where-access-token');

    const response = await baseUrl.get(`ratings/all/${id}/`, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao consultar avaliações", error);
    throw error;
  }
}

export async function eventFilter1(id: number) {
  try {
    const token = Cookies.get('where-access-token');

    const response = await baseUrl.get(`ratings/all/${id}/`, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao consultar avaliações", error);
    throw error;
  }
}

export async function deleteEvent(id: number) {
  try {
    const token = Cookies.get('where-access-token');

    const response = await baseUrl.delete(`events/${id}/`, {
      headers: {
        'where-access-token': token,
      },
    });
    
    return response.data;
  } catch (error) {
    console.error("Erro ao consultar avaliações", error);
    throw error;
  }
}


