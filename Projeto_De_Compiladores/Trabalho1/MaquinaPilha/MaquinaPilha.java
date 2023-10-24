class MaquinaPilha{


    public static void main(String[]args){

        try
        {
            float resultado;
            Carregador carregador = new Carregador(args[0]);
            //Carregador carregador = new Carregador("Output.txt");
            Memoria memoria = new Memoria();
            CPU cpu = new CPU();

            carregador.carregar(memoria, cpu);

            resultado = memoria.popStack();

            System.out.println("\n\n\n\t\t\t" + resultado + "\n\n\n");

        }catch(Exception e)
        {
            System.out.println("Erro de execução:\n" + e);
        }
    }
}