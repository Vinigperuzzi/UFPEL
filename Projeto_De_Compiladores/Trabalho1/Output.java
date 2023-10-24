import java.io.FileWriter;

public class Output {
    
    String codigo;

    public Output(String codigo) {
        this.codigo = codigo;
    }

    public void geraOutput(){
        try{
            FileWriter fr = new FileWriter("MaquinaPilha/Output.txt");
            fr.write(this.codigo);
            fr.close();
        }
        catch(Exception erro){
            System.out.println("Não foi possível criar o arquivo no diretório de saída");
        }
    }
}
