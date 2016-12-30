import java.net.*;
import java.io.*;
import java.util.*;
public class client
{
    public static void main(String args[])throws Exception{
	 Socket client_socket;
	 DataOutputStream data_output_stream;
	 DataInputStream data_input_stream;
	 client_socket = new Socket("172.16.132.130",6665);
	 data_output_stream = new DataOutputStream(client_socket.getOutputStream());
	 data_input_stream = new DataInputStream(client_socket.getInputStream());
	 Scanner sc = new Scanner(System.in);
	 String a;
	 while(true){
	     a = sc.next();
	     data_output_stream.writeUTF(a);
	 }
    }
} 
