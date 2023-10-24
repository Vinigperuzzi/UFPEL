import java.io.BufferedReader;
import java.io.FileReader;

public class Carregador{
    private BufferedReader source;
    private String sourceName;

    public Carregador(String sourceName) {
        this.sourceName = sourceName;
    }
    
    public void carregar(Memoria memoria) throws Exception{
        this.source = new BufferedReader(new FileReader(this.sourceName));
        String vect[];

        do {
            String line = source.readLine();
            vect = line.split(" ");
            if (vect[0].equals("PUSH")){
                memoria.carregaStack(vect[1]);
            } else if (!vect[0].equals("PRINT")){
                memoria.carregaInstructions(vect[0]);
            }
        } while (!vect[0].equals("PRINT"));

        source.close();
    }
}
