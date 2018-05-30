# TCP Server
import socket
import logging
import time

logging.basicConfig(format = u'[LINE:%(lineno)d]# %(levelname)-8s [%(asctime)s]  %(message)s', level = logging.NOTSET)

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

port = 10000
adresa = '198.13.0.14'
server_address = (adresa, port)
sock.bind(server_address)
logging.info("Serverul a pornit pe %s si portnul portul %d", adresa, port)
sock.listen(1)
logging.info('Asteptam conexiunea...')
conexiune, address = sock.accept()
logging.info("Handshake cu %s", address)

while True:
    data = conexiune.recv(1024)
    logging.info('Content primit: "%s"', data)
    conexiune.send("X")

conexiune.close()
sock.close()