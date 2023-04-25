#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h>

#define MAXLINE 1024

void error(const char *);
void print_packet(std::string &);


int main(int argc, char **argv)
{
	if(argc != 3)
		error("incorrect number of arguments");
	int sockfd;

	unsigned short serv_port = (unsigned short)std::stoi(argv[1]);
	int loss = std::stoi(argv[2]);

	struct sockaddr_in serv_addr, cli_addr;
        char buffer[MAXLINE];
	if((sockfd = socket(AF_INET, SOCK_DGRAM, 0))<0)
		error("failed to create socket");

	memset(&serv_addr, 0, sizeof(serv_addr));
	memset(&cli_addr, 0, sizeof(cli_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(8080);

	if(bind(sockfd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
		error("bind failed");

	socklen_t len;
	int n;

	len = sizeof(cli_addr);

	n = recvfrom(sockfd,(char*)buffer,MAXLINE, MSG_WAITALL, (struct sockaddr *)&cli_addr, &len);
	buffer[n] = '\0';
	std::string b(buffer);
	std::cout << b << " :END\n";
	//sendto(sockfd, (const char*)hello, strlen(hello));
	std::cout  << "hello message sent\n";

	return 0;
}



// print error message and exit program
void error(const char *err_msg)
{
	std::cout << "ERROR: " << err_msg << "\n";
	exit(1);
}
