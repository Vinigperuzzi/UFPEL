import java.util.ArrayList;
import java.util.List;

public class Memoria {
    
    private List<String> stack = new ArrayList<>();

    public Memoria() {
    }

    public void carregaStack(String valor){
        stack.add(valor);
    }

    public float popStack(){
        float arg = Float.parseFloat(stack.get(stack.size()-1));
        stack.remove(stack.size()-1);
        return arg;
    }

    public void stackPush(String valor){
        stack.add(stack.size(), valor);
    }

    @Override
    public String toString() {
        return "Memoria [stack=" + stack + "]";
    }
    
}
