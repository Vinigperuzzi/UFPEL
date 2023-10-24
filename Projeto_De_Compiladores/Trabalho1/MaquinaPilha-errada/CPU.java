public class CPU {

    public CPU() {
    }

    public float executaCodigo(Memoria memoria) throws Exception{

        float arg1, arg2, parcial, resultado;
        String op;

        do {
            if(memoria.testaInstVazio()){
                resultado = memoria.popStack();
                return resultado;
            }
            op = memoria.popInstruction();
            arg1 = memoria.popStack();
            arg2 = memoria.popStack();

            switch(op){
                case "SUM":
                    parcial = arg2 + arg1;
                    break;
                case "SUB":
                    parcial = arg2 - arg1;
                    break;
                case "MULT":
                    parcial = arg2 * arg1;
                    break;
                case "DIV":
                    parcial = arg2 / arg1;
                    break;
                default: throw (new Exception("Algum erro no código fonte, operador não definido: " + op));
            }

            memoria.stackPush(Float.toString(parcial));
        } while (!memoria.testaInstVazio());

        return parcial;
    }
}
