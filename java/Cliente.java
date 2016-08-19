import java.io.*;
import java.util.Scanner;
import java.net.*;

class Cliente
{
	public static void main(String arg[]) throws IOException
	{
		Socket cliente = new Socket("192.168.4.12",20000);

		Scanner entrada = new Scanner(System.in);
		PrintStream saida = new PrintStream(cliente.getOutputStream());
		{
			while(entrada.hasNextLine())
			{
				saida.println(entrada.nextLine());
			}

			saida.close();
     		entrada.close();
     		cliente.close();
		}
	}
}