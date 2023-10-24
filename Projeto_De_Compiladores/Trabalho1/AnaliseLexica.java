import java.io.*;

enum TokenType{ NUM,SOMA,SUB,MULT,DIV,APar,FPar, EOF}

class Token{
  String lexema;
  TokenType token;

 Token (String l, TokenType t)
 	{ lexema=l;token = t;}	

}

class AnaliseLexica {

	BufferedReader arquivo;

	AnaliseLexica(String a) throws Exception
	{
		
	 	this.arquivo = new BufferedReader(new FileReader(a));
		
	}

	Token getNextToken() throws Exception
	{	
		Token token;
		int eof = -1;
		char currchar;
		int currchar1;
		String currStr = new String();
		
		do{
				currStr = "";
				currchar1 =  arquivo.read();
				currchar = (char) currchar1;
				if (currchar >= '0' && currchar <= '9'){
					do{
						arquivo.mark(0);
						currStr += currchar;
						currchar1 =  arquivo.read();
						currchar = (char) currchar1;
					} while(currchar >= '0' && currchar <= '9');
					arquivo.reset();
					if (currchar1 == 10 || currchar == '\n' || currchar == ' ' || currchar == '\t' || currchar == '\r'){
						currchar1 =  (int) currStr.charAt(0);
						currchar = (char) currchar1;
					}
				} else {
					currStr += currchar;
				}
			} while (currchar == '\n' || currchar == ' ' || currchar == '\t' || currchar == '\r');
			
			if(currchar1 != eof && currchar1 !=10)
			{
								
	
				if (currStr.compareTo("00") > 0 && currStr.compareTo("99") < 0)
					return (new Token (currStr, TokenType.NUM));
				else
					switch (currStr){
						case "(":
							return (new Token (currStr,TokenType.APar));
						case ")":
							return (new Token (currStr,TokenType.FPar));
						case "+":
							return (new Token (currStr,TokenType.SOMA));
						case "*":
							return (new Token (currStr,TokenType.MULT));
						case "-":
							return (new Token (currStr,TokenType.SUB));
						case "/":
							return (new Token (currStr,TokenType.DIV));
						
						default: throw (new Exception("Caractere inválido: " + ((int) currchar)));
					}
			}

			arquivo.close();
			
		return (new Token(currStr,TokenType.EOF));
		
	}
}
