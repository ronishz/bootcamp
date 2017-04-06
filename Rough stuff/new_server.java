import java.net.*;
import java.io.*;
import java.io.PrintStream;
public class new_server{
    ServerSocket serverSocket;
     public new_server(){
	 try{
	serverSocket = new ServerSocket(6665);
	System.out.println("Server starting \n");
	 }catch(Exception e){}
    }
    public static void main(String args[])throws Exception{
	new_server server = new new_server();
	while(true){
	    Socket clientSocket = server.serverSocket.accept();
	    ClientHelper clientHelper = new ClientHelper(clientSocket);
	    clientHelper.start();
	}
    }
}
class ClientHelper extends Thread{
    Socket clientSocket;
     public ClientHelper(Socket c){
	clientSocket = c;
	System.out.println("Client connected is \t" + clientSocket.getInetAddress().toString() + "\n");
	System.out.println(clientSocket);
    }
    public void run(){
	try{
	    BufferedReader input;
	    DataInputStream d;
	    while(true){
		d = new DataInputStream(clientSocket.getInputStream());
		System.out.println(d.readUTF());
	    }
	}catch(Exception e){}
    }
}


