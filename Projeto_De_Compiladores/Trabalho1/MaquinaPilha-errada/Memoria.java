import java.util.ArrayList;
import java.util.List;

public class Memoria {
    
    private List<String> stack = new ArrayList<>();
    private List<String> instructions = new ArrayList<>();

    public Memoria() {
    }

    public void carregaStack(String valor){
        stack.add(valor);
    }

    public void carregaInstructions(String valor){
        instructions.add(valor);
    }

    public float popStack(){
        float arg = Float.parseFloat(stack.get(stack.size()-1));
        stack.remove(stack.size()-1);
        return arg;
    }

    public void stackPush(String valor){
        stack.add(stack.size(), valor);
    }

    public String popInstruction(){
        String op = instructions.get(0);
        instructions.remove(0);
        return op;
    }

    public boolean testaInstVazio(){
        if(instructions.size() == 0){
            return true;
        }
        return false;
    }

    @Override
    public String toString() {
        return "Memoria [stack=" + stack + ", instructions=" + instructions + "]";
    }

    
}
