from scapy.all import *
from threading import Thread

def call(p):
	p.show()

def sniffing(f):
	sniff(prn=call,count=2,filter=f)

t1=Thread(target=sniffing("icmp"))
t1.start()
t2=Thread(target=sniffing("udp"))
t2.start()
