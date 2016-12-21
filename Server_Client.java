import java.io.*;
import java.net.Socket;


public class Server_Client {
	public static void main(String args[]) throws Exception {
		Server server = new Server();
		server.start();//after this run method will be executed
		Socket client_socket = new Socket("localhost",12345);
		DataOutputStream data_output_stream = new DataOutputStream(client_socket.getOutputStream());
		char a = 'a';
		data_output_stream.write(a);
		
	}
}
