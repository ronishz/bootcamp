import os

print("Options..\n1. Same subnet.\n2. Different subnet.\n")
op=int(raw_input("\nEnter your choice : "))

while op!=3:

	if op==1:
		same=raw_input("\nEnter the ip address of machine from same subnet : ")
		os.system("ping -c 4 %s" %same)

	if op==2:
		diff=raw_input("\nEnter the ip address of machine from different subnet : ")
		os.system("ping -c 4 %s" %diff)
		
	op=int(raw_input("\nEnter your choice : "))
		
print("\nExiting..")
