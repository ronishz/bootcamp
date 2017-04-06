import java.io.*;
import java.net.*;
import java.util.*;
public class Server extends Thread{
	public static ServerSocket svr=null;
	public static Socket s=null;

	public Server(){
		try{
		this.svr=new ServerSocket(1234);
		this.s = svr.accept();
		}catch(IOException e){};
	}

	public static void main(String[] args) throws Exception{
		//svr=new ServerSocket(1234);
		//s = svr.accept();
	Server server=new Server();
		server.start();
		
		
	}
		

	public void run(){
		try{
	
			DataInputStream din=new DataInputStream(s.getInputStream());
			int a1=din.read();
			int a2=din.read();
		
			DataOutputStream dout=new DataOutputStream(s.getOutputStream());
	
		while(true){
		int op=din.read();
		if(op==1){
			int sum=a1+a2;
			dout.write(sum);
			dout.flush();	
		}
		else if(op==2){
			int sub=a1-a2;
			dout.write(sub);
			dout.flush();
		}
		else if(op==3){
			int mul=a1*a2;
			dout.write(mul);
			dout.flush();
		}
		else if(op==4){
			int div=a1/a2;
			dout.write(div);
			dout.flush();
		}
		else if(op==5){
			break;
		}
		
		}
		
		
		
		}
		catch(IOException e){
			System.out.println("Exception found");
		}
		
		
		
		
		
		
		//String str=(String)din.readUTF();
		//s.close();
			

		}						
	
}
