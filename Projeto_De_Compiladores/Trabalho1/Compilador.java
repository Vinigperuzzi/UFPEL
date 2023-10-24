class Compilador{

	public static void main(String[]args)
	{	
		ArvoreSintatica arv=null;
	
		try{

			AnaliseLexica al = new AnaliseLexica(args[0]);
			//AnaliseLexica al = new AnaliseLexica("teste");
			Parser as = new Parser(al);
		
			arv = as.parseProg();
		
			
			CodeGen backend = new CodeGen();
			String codigo = backend.geraCodigo(arv);
			System.out.println(codigo);

			if (args.length > 1 && args[1] != null){
				Output out = new Output(codigo);
				out.geraOutput();
			}
			if (args.length > 2 && args[2] != null){
				Interpretador interpretador = new Interpretador();
				Float resultadoInterpretado = interpretador.interpreta(arv);
				System.out.println("A saída do interpretador é: " + resultadoInterpretado);
			}

		}catch(Exception e)
		{			
			System.out.println("Erro de compilação:\n" + e);
		}



	}
}
