class MaquinaPilha{


    public static void main(String[]args){

        try
        {
            float resultado;
            Carregador carregador = new Carregador(args[0]);
            //Carregador carregador = new Carregador("Output.txt");
            Memoria memoria = new Memoria();

            carregador.carregar(memoria);
            System.out.println("\n\n\t\t\t" + memoria + "\n\n");        //Memória impressa

            CPU cpu = new CPU();
            resultado = cpu.executaCodigo(memoria);

            System.out.println("\n\n\n\t\t\t" + resultado + "\n\n\n");

        }catch(Exception e)
        {
            System.out.println("Erro de execução:\n" + e);
        }
    }
}