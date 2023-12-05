#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if ( argc < 2 ){
	 printf("Input : %s port number\n", argv[0]);
	 return 1;
	}

	int SERVER_PORT = atoi(argv[1]);

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(SERVER_PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	int listen_sock;
	if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Could not create listen socket\n");
		return 1;
	}

	if ((bind(listen_sock, (struct sockaddr *)&server_address,
	          sizeof(server_address))) < 0) {
		printf("Could not bind socket\n");
		return 1;
	}

	int wait_size = 16;
	if (listen(listen_sock, wait_size) < 0) {
		printf("Could not open socket for listening\n");
		return 1;
	}
	struct sockaddr_in client_address;
	int client_address_len = 0;

	int sock;
	int  maxlen = 1024;
	int n = 0;
	char buffer[maxlen];

	while (1) {
		if ((sock = accept(listen_sock, (struct sockaddr *)&client_address, &client_address_len)) < 0) {
			printf("Could not open a socket to accept data\n");
			return 1;
		}

		printf("Client connected with ip address: %s\n", inet_ntoa(client_address.sin_addr));

		// Insert code Here! /////
		//1.클라이언트가 보낸 메시지 수신

		//2. 수신한 메시지를 출력

		//3. 수신한 메시지를 클라이언트에게 송신

		while ((n = recv(sock, buffer, maxlen, 0)) > 0) {
			buffer[n] = '\0'; // Null
			printf("%s", buffer);
			send(sock, buffer, maxlen, 0);
		}	
	}
	close(sock);
	close(listen_sock);
	return 0;
}
