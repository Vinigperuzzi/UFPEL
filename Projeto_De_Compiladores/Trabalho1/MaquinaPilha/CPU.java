public class CPU {

    public CPU() {
    }

    public void executaComando(Memoria memoria, String op) throws Exception{

        float arg1, arg2, resultado;

        arg1 = memoria.popStack();
        arg2 = memoria.popStack();
        
        switch(op){
            case "SUM":
            resultado = arg2 + arg1;
            break;
            case "SUB":
            resultado = arg2 - arg1;
            break;
            case "MULT":
            resultado = arg2 * arg1;
            break;
            case "DIV":
            resultado = arg2 / arg1;
            break;
            default: throw (new Exception("Algum erro no código fonte, operador não definido: " + op));
        }
        
        memoria.stackPush(Float.toString(resultado));
    }
}
