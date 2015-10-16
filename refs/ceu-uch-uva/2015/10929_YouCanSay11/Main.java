// EL FICHERO DEBE LLAMARSE Main Y LA CLASE TAMBIEN, EL JUEZ LO PIDE ASI
import java.math.BigInteger;
import java.io.*;

public class Main {
  public static void main(String args[]) {
    String line;
    BigInteger eleven = new BigInteger("11");
    // El InputStreamReader es necesario para poder leer desde teclado cuando se
    // redirige la entrada
    InputStreamReader isr = new InputStreamReader(System.in);
    BufferedReader br = new BufferedReader (isr);
    try {
      do {
        line = br.readLine();
        // NOTA: viajeros de C++, en Java no hay sobrecarga de operadores, hay
        // que utilizar los metodos de la clase String
        if (!line.equals("0")) {
          BigInteger number = new BigInteger(line);
          BigInteger rest = number.mod(eleven);
          if (rest.equals(BigInteger.ZERO)) {
            System.out.println(line + " is a multiple of 11.");
          }
          else {
            System.out.println(line + " is not a multiple of 11.");
          }
        }
      } while(!line.equals("0"));
    }
    catch(Exception e) {
    }
  }
}
