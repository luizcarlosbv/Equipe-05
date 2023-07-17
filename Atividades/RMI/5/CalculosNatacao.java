import java.rmi.server.UnicastRemoteObject;
import java.rmi.RemoteException;

public class CalculosNatacao extends UnicastRemoteObject implements Interface {
    public CalculosNatacao() throws RemoteException {

    }

    public String calculaCategoriaNadador(int idade) throws RemoteException {
        if(idade < 5) {
            return "Sem categoria";
        } else if(idade <= 7) {
            return "Infantil A";
        } else if(idade <= 10) {
            return "Infantil B";
        } else if(idade <= 13) {
            return "Juvenil A";
        } else if(idade <= 17) {
            return "Juvenil B";
        } else {
            return "Adulto";
        }
    }
    
}
