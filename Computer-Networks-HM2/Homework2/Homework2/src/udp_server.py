# receiver.py - The receiver in the reliable data transer protocol
import packet
import socket
import sys

PORT = 10000
PACKET_SIZE = 4096
RECEIVER_ADDR = ('172.111.0.14', PORT)

recieved = []

# Receive packets from the sender
def receive(sock):
    expected_num = 0
    while True:
        # Get the next packet from the sender
        pkt, addr = sock.recvfrom(PACKET_SIZE)
        
        if not pkt:
            break
        seq_num, data = packet.extract(pkt)
        print('Got packet', seq_num,' expected ', expected_num)
        
        # Send back an ACK
        if int(seq_num) == expected_num:
            print('Got expected packet')
            recieved.append(data)
            print('Sending ACK', expected_num)
            pkt = packet.make(expected_num)
            sock.sendto(pkt,addr)
            expected_num += 1
        else:
            print('Sending ACK', expected_num - 1)
            pkt = packet.make(expected_num - 1)
            sock.sendto(pkt,addr)

# Main function
print('Server is up and running at address: ',RECEIVER_ADDR)

if __name__ == '__main__':
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(RECEIVER_ADDR) 
    receive(sock)
    print 'I recieved from client following numbers:' , ', '.join(recieved)
    sock.close()