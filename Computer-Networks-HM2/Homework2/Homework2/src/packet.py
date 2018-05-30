
# packet.py - Packet-related functions

# Creates a packet from a sequence number and byte data
def make(seq_num, data=0):
    seq_str = str(seq_num)
    data_str = str(data)
    return seq_str + "|" + data_str

# Creates an empty packet
def make_empty():
    return b''

# Extracts sequence number and data from a non-empty packet
def extract(packet):
	nr = 0
	rseq = ""
	for char in packet:
		if char != '|':
		    rseq = rseq + char
		    nr = nr + 1
		else:
		    nr = nr+1
		    break

	rdata = ""
	str2 = packet[nr:]

	for char in str2:
		rdata = rdata + char

	return rseq,rdata