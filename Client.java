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
		System.out.println("Operations:\n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division");
		int op=sc.nextInt();
		dout.write(op);
		DataInputStream din=new DataInputStream(s.getInputStream());
		int sum=din.read();
		System.out.println("Result:	"+sum);
		//int sub=din.read();
		//System.out.println("Subtraction:	"+sub);
		//int mul=din.read();
		//System.out.println("Multiplication:	"+mul);
		//int div=din.read();
		//System.out.println("Division:	"+div);
		s.close();		
		

					
	}
}
