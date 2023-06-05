import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Interface extends Remote {
    String calculaCategoriaNadador(int idade) throws RemoteException;
}