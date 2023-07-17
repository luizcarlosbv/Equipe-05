import java.rmi.Naming;
import java.rmi.registry.LocateRegistry;

public class Server {
    public static void main(String[] args) {
        try {
            Interface calc = new CalculosNatacao();
            String objName = "rmi://localhost/Calc";

            System.out.println("Registrando o objeto no RMIRegistry...");
            LocateRegistry.createRegistry(1099);
            Naming.rebind(objName, calc);

            System.out.println("Aguardando clientes");
        } catch(Exception e) {
            e.printStackTrace();
        }
    }
}
