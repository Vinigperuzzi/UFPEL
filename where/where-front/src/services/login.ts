import axios from 'axios';

export const baseUrl = axios.create({
  baseURL: 'http://localhost:3000'
});

export async function login(email: string, password: string) { // Tipando os parâmetros como string
  const credentials = {
    email,
    password
  };

  try {
    const response = await baseUrl.post('/login', credentials);
    console.log("Resposta do servidor:", response);
    
    return response.data;
  } catch (error) {
    console.error("Erro ao fazer login:", error);
    throw error;
  }
}
