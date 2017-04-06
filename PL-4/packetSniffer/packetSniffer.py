from __future__ import print_function
from scapy.all import sniff
import threading

# Function used for expanding the packet layers
def expand(packet):
    yield packet # yield works like return
    while packet.payload:
        packet = packet.payload
        yield packet

# Print important fields of each layer
def print_details(packet):

    for layer in expand(packet):
        if layer.name == 'Ether':
            print('Ethernet: dst = {}, src = {}'.format(layer.dst, layer.src))
            print('----------')
        if layer.name == 'IP':
            print('IP: version = {}, len = {}, src = {}, dst = {}'.format(layer.version, layer.len, layer.src, layer.dst))
            print('----------')
        if layer.name == 'TCP':
            print('TCP: sport = {}, dport = {}, seq = {}, ack = {}'.format(layer.sport, layer.dport, layer.seq, layer.ack))
            print('----------')
        if layer.name == 'Raw':
            print('Raw: payload = {}'.format(layer.load[:100]))
            print('----------')
        if layer.name == 'UDP':
            print('UDP: sport = {}, dport = {}, len = {}'.format(layer.sport, layer.dport, layer.len))
            print('----------')
        if layer.name == 'ICMP':
            print('ICMP: type = {}, code = {}, seq = {}'.format(layer.type, layer.code, layer.seq))
            print('----------')
        if layer.name == 'ARP':
            print('ARP: hwsrc = {}, psrc = {}'.format(layer.hwsrc, layer.psrc))
            print('----------')

class SnifferThread(threading.Thread):
    """
    A class that extends threading.Thread which encapsulates the code required for threading and sniffing packets.

    """
    # Constructor
    def __init__(self, fil, thread_no=0):
        threading.Thread.__init__(self)
        self.filter = fil
        self.thread_no = thread_no
        self.packets = []

    # Callback function for sniff
    def _store_packet(self, packet):
        self.packets.append(packet)

    # Print packets
    def print_packets(self):
        print('--- Thread {:d}, Filter: {:s} ---'.format(self.thread_no, self.filter.upper()))
        for i, packet in enumerate(self.packets):
            print('Packet: {}'.format(i))
            print_details(packet)
            #print(repr(packet))	

    # Internal function that calls sniff with correct parameters
    def _sniff(self):
        sniff(prn=self._store_packet, filter=self.filter, count=3)

    # Thread interface method
    def run(self):
        self._sniff() # Call the _sniff method


def main():
    # Protocols to sniff
    protocols = ['tcp', 'udp', 'icmp', 'tcp port 80', 'arp'] # Required protocols are added to this list
    # List of threads
    threads = []    
    # Create a thread for each protocol and append it to 'threads'
    for index, protocol in enumerate(protocols):
        threads.append(SnifferThread(protocol, index))

    # Start all the threads
    for th in threads:
        th.start()

    # Wait for execution to be complete
    for th in threads:
        th.join()

    # Print all the info
    for th in threads:
        th.print_packets()


if __name__ == '__main__':
    main()
