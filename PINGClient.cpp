#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <netdb.h>

// function declarations
void error(const char *);
void randomize_str(std::string &);
void print_packet(std::string &);

int main(int argc, char **argv)
{
	// if not correct number of arguments
	if(argc != 6)
		error("incorrect number of arguments.");
	
	// store all the arguments given
	std::string serv_ip = argv[1];
	unsigned short serv_port = (unsigned short) std::stoi(argv[2]);
	std::string client_id = argv[3];
	int num_packets = std::stoi(argv[4]);
	int wait = std::stoi(argv[5]);
	
	// check valid arguments
//	if(num_packets > 300 || num_packets < 150)
//		error("not valid number of packets.");
//	if(wait < 1 || wait > 10)
//		error("not valid wait period.");

	// print out startup client info
	std::cout << "PINGClient started with server IP: " << serv_ip <<
		", port: " << serv_port << ", client ID: " << client_id << 
		", packets: " << num_packets << ", wait: " << wait << "\n";
	
	// set seed for rand()
	srand(time(0));

	std::string payload;
	int sockfd;
	struct sockaddr_in serv_addr;
	struct hostent *hp;	
	// create socket description <IPV4, UDP>
	if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
		error("socket creation failed");

	memset(&serv_addr,0,sizeof(serv_addr));

	// set serveraddr
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(serv_port);
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	
	//int n;
	//socklen_t len;
	
	for(int i=0; i<num_packets;i++)
	{
		// get random payload
		randomize_str(payload);

		// add header to payload
		// create_ping_packet();

		// send the packet
		sendto(sockfd, payload.c_str(), payload.length(), MSG_CONFIRM, 
			(const struct sockaddr *)&serv_addr, sizeof(serv_addr));
	}


	return 0;
}

// print error message and exit program
void error(const char *err_msg)
{
	std::cout << "ERROR: " << err_msg << "\n";
	exit(1);
}


// fills string with random lowercase characters
void randomize_str(std::string &str)
{
	// empty arr
	str.clear();

	// size is 150 - 300
	int size = (rand() % 150) + 150;
	
	// get size bytes and add them to arr
	for(int i=0;i<size;i++)
		str += (char) ((rand() % 26) + 97);
}
