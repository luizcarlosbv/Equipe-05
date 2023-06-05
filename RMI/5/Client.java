import java.rmi.Naming;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws Exception {
        String objName = "rmi://localhost:1099/Calc";
        Interface calc = (Interface) Naming.lookup(objName);
        Scanner keyboard = new Scanner(System.in);
        System.out.println("Digite a idade do nadador!");
        System.out.println("A categoria do nadador é: " + calc.calculaCategoriaNadador(keyboard.nextInt()));
        keyboard.close();
    }
}
