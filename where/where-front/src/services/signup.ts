import axios from 'axios';

export const baseUrl = axios.create({
    baseURL: 'http://localhost:3000'
});

export async function signup(name: string, email: string, password: string) {
  const credentials = {
    email,
    password,
    name,
    date: '2000-01-01',
  };

  try {
    const response = await baseUrl.post('/user/create', credentials);
    console.log("Resposta do servidor (Registro):", response);
    return response.data;
  } catch (error) {
    console.error("Erro ao Registrar", error);
    throw error;
  }
}
