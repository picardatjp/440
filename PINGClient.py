from ctypes import sizeof
from socket import *
import sys
import random
import string
from datetime import datetime





def create_packet(client_id, seq_no):
    size = random.randint(150,300)
    payload = create_payload(size)
    header = create_header(client_id, seq_no, size)
    packet = header + payload
    return packet

def create_header(client_id, seq_no, size):
    header = ''
    header += '1|'
    header += client_id + '|'
    header += str(seq_no) + '|'
    now = datetime.now().timestamp()
    header += str(now) + '|'
    header += str(size) + '|'
    return header

def create_payload(size):
    payload = ''
    payload += 'hostname|'
    payload += 'VCU-CMSC440-SPRING-2023|'
    payload += 'Picardat, Jacob|'
    payload += ''.join(random.choice(string.ascii_lowercase + string.digits) for _ in range(size - len(payload)))
    return payload



def print_packet(pkt):
    info = pkt.split("|")
    print("-----------Ping Request Packet Header------------")
    print("Version:", info[0])
    print("ClientID:", info[1])
    print("SequenceNo:",info[2])
    print("Timestamp:",info[3])
    print("Size:",info[4])
    print("-----------Ping Request Packet Header-----------")
    print("Host:",info[5])
    print("Class-name:",info[6])
    print("User-name:",info[7])
    print("Rest:",info[8])
    print("-------------------------------------------")



def main():
    args = sys.argv

    if len(args) != 6:
        print("not right number of args")
        exit(1)

    hostname = args[1]
    port = int(args[2])
    client_id = args[3]
    num_packets = int(args[4])
    timeout_time = int(args[5])

    clientSocket = socket(AF_INET, SOCK_DGRAM)
    clientSocket.settimeout(timeout_time)
    for i in range(0,num_packets):
        p = create_packet(client_id, i)
        clientSocket.sendto(p.encode(), (hostname, port))
        print_packet(p)
        try:
            servS, servA = clientSocket.recvfrom(1024)
            print('\n\nrecieved ack!\n')
            servS = servS.decode()
            print_packet(servS)
        except timeout:
            print('packet lost')
            
    clientSocket.close()

main()
