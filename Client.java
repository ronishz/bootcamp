import java.io.*;
import java.net.*;
import java.util.*;
public class Client{
	public static void main(String[] args)throws Exception{
		Socket s = new Socket("localhost",1234) ;
		DataOutputStream dout=new DataOutputStream(s.getOutputStream());

		Scanner sc=new Scanner(System.in);
		System.out.println("Enter number 1:	");
		int a1=sc.nextInt();
		dout.write(a1);
		dout.flush();
		System.out.println("Enter number 2:	");
		int a2=sc.nextInt();
		//String s1=sc.nextLine();
		dout.write(a2);
		dout.flush();
		while(true){
		System.out.println("Operations:\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit");
		int op=sc.nextInt();
		if(op==5){
			break;
		}
		dout.write(op);
		DataInputStream din=new DataInputStream(s.getInputStream());
		int sum=din.read();
		System.out.println("Result:	"+sum);
		}
		
		s.close();

					
	}
}
