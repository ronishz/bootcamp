from brotherprint import BrotherPrint
import socket
f_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
f_socket.connect(("172.016.133.145",9100))
printjob = BrotherPrint(f_socket)

printjob.command_mode()
printjob.initialize()
printjob.bold('on')

printjob.send("     It is my Remote Printer assignment")
printjob.print_page("full")

#to print from file

#fn = raw_input("Enter file name to be printed")
#f1 = open(fn,'r')
#text = f1.read()
#printjob.send(text)
#printjob.print_page("full")
