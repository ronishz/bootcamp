import java.io.*;
import java.net.*;
public class Server{
	public static void main(String[] args) throws Exception{
		ServerSocket svr=new ServerSocket(1234);
		Socket s = svr.accept();
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
		
		
		
		
		
		
		
		
		
		
		//String str=(String)din.readUTF();
		//s.close();
			

								
	}
}
