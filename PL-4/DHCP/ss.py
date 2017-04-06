#!/usr/bin
import os
print "\nCopying .deb file from our computer to remote computer \n"
os.system("scp ~/cowsay_3.03+dfsg1-3_all.deb student@192.168.1.25:~")
print "\nCopy completed \n"
os.system("ssh -t student@192.168.1.25 sudo dpkg -i ~/cowsay_3.03+dfsg1-3_all.deb \n")
print "\n************** Installation completed..!! *********************\n" 
