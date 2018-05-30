# sender.py 
import packet
import socket
import sys
import thread
import time

from timer import Timer

# UDP socket 
SERVER_ADDRESS = '172.111.0.14'
CLIENT_ADDRESS = '198.13.0.14'
PORT = 10000
PACKET_SIZE = 4096
RECEIVER_ADDR = (SERVER_ADDRESS, PORT)  	# client - rt1
SENDER_ADDR = (CLIENT_ADDRESS, PORT)		# server - rt3
SLEEP_INTERVAL = 0.05
TIMEOUT_INTERVAL = 1
WINDOW_SIZE = 4

# Shared resources across threads
base = 0
mutex = thread.allocate_lock()
send_timer = Timer(TIMEOUT_INTERVAL)

# Sets the window size
def set_window_size(num_packets):
    global base
    return min(WINDOW_SIZE, num_packets - base)

# Send thread
def send(sock,numbers):
    #global mutex
    global base
    global send_timer

   
    # Add all the packets to the buffer
    packets = []
    seq_num = 0
    while True:
        if seq_num >= len(numbers):
        	break
        data = numbers[seq_num]
        packets.append(packet.make(seq_num, data))
        seq_num += 1


    num_packets = len(packets)
    print('I got', num_packets,' to send')
    window_size = set_window_size(num_packets)
    next_to_send = 0
    base = 0

    # Start the receiver thread
    thread.start_new_thread(receive, (sock,))

    while base < num_packets:
        mutex.acquire()
        # Send all the packets in the window
        while next_to_send < base + window_size:
            print('Sending packet', next_to_send)
            sock.sendto(packets[next_to_send], RECEIVER_ADDR)
            next_to_send += 1

        # Start the timer
        if not send_timer.running():
            print('Starting timer')
            send_timer.start()

        # Wait until a timer goes off or we get an ACK
        while send_timer.running() and not send_timer.timeout():
            mutex.release()
            print('Sleeping')
            time.sleep(SLEEP_INTERVAL)
            mutex.acquire()

        if send_timer.timeout():
            # Looks like we timed out
            print('Timeout')
            send_timer.stop();
            next_to_send = base
        else:
            print('Shifting window')
            window_size = set_window_size(num_packets)
        mutex.release()

    # Send empty packet as sentinel
    sock.sendto(packet.make_empty(), RECEIVER_ADDR)

# Receive thread
def receive(sock):
    global mutex
    global base
    global send_timer

    while True:
        pkt, _ = sock.recvfrom(PACKET_SIZE);
        ack, _ = packet.extract(pkt);

        # If we get an ACK for the first in-flight packet
        print('Got ACK', ack, '  expected  ',base)
        if (int(ack) >= base):
            mutex.acquire()
            base = int(ack) + 1
            print('Base updated', base)
            send_timer.stop()
            mutex.release()

    # Main function
if __name__ == '__main__':

    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(SENDER_ADDR)
    numbers = list(range(1,21,1))
    send(sock, numbers)
    sock.close()

