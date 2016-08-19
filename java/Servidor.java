import java.*;
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Servidor
{
	public static void main(String argv[]) throws IOException
	{
		ServerSocket Servidor = new ServerSocket(20000);
		System.out.println(Servidor);

		Socket cliente = Servidor.accept();
		System.out.println("Nova conexão com o cliente " + cliente.getInetAddress().getHostAddress());

		/*Recebe tudo que o cliente enviar*/
		Scanner scanner = new Scanner(cliente.getInputStream());

		while (scanner.hasNextLine()) 
		{
  				System.out.println(scanner.nextLine());
		}

		scanner.close();
     	Servidor.close();
     	cliente.close();
	}
}

