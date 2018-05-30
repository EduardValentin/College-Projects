# inainte de toate trebuie adaugata o regula de ignorare 
# a pachetelor RST pe care ni le livreaza kernelul automat
# iptables -A OUTPUT -p tcp --tcp-flags RST RST -j DROP
from scapy.all import *
import struct

ip = IP()
ip.src = '198.13.0.15' # ip ul nostru
ip.dst = '198.13.0.14' # ip ul serverului


tcp = TCP()
tcp.sport = 54321
tcp.dport = 10000


optiune = 'MSS'
op_index = TCPOptions[1][optiune]
op_format = TCPOptions[0][op_index]
print op_format
valoare = struct.pack(op_format[1], 2)

tcp.options = [(optiune, valoare)]


## SYN ##
tcp.seq = 100
tcp.flags = 'S' # flag de SYN
raspuns_syn_ack = sr1(ip/tcp)

tcp.seq += 1
tcp.ack = raspuns_syn_ack.seq + 1
tcp.flags = 'A'
ACK = ip / tcp

send(ACK)


for ch in "edi":
    tcp.flags = 'PACE'
    ip.tos = int('011100' + '11', 2)
    tcp.ack = raspuns_syn_ack.seq + 1
    rcv = sr1(ip/tcp/ch)
    rcv
    tcp.seq += 1

#3 bytes
ch = 'nio'
tcp.ack = raspuns_syn_ack.seq + 1
rcv = sr1(ip/tcp/ch)
rcv
tcp.seq += 1

#trimitem rst
tcp.flags = 'RA'
rcv = sr1(ip/tcp)