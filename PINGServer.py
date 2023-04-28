from socket import *
import sys

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

def packet_capitalize(pkt):
    info = pkt.split('|')
    for i in range(5,8):
        info[i] = info[i].capitalize()
    return '|'.join(info)
    

def main():
    args = sys.argv

    if len(args) != 3:
        print("Not right number of args")
        exit(1)
    port = int(args[1])
    serverSocket = socket(AF_INET, SOCK_DGRAM)
    serverSocket.bind(('',port))


    while 1:
        pkt, cliAddr = serverSocket.recvfrom(2048)
        pkt = pkt.decode()
        print_packet(pkt)
        serverSocket.sendto(pkt.upper().encode(),cliAddr)
        print ("ack sent")




main()
