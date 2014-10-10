#include <udt.h>
#include <iostream>
#include <cstring>
#include <cstdlib>

#include "inc/TCP_Socket.h"
#include "inc/ModelClient.h"
#include "inc/ModelServer.h"
#include "inc/UDT_Socket.h"

using namespace std;

#define HOST "127.0.0.1"
#define PORT 1234

template <class T>
void doClient(uint32_t n) {
	string host = HOST;
	ModelClient<T> cli(host, PORT);
	cli.init();
	cli.run(n);
	cli.close();
}

template <class T>
void doServer() {
	string host = HOST;
	ModelServer<T> serv(host, PORT);
	serv.init();
	serv.run();
	serv.close();
}

int main(int argc, char** argv) {
	if (argc < 2) {
		cout << "Wrong arg" << endl;
		return 1;
	}

	uint32_t n = 1000;
	if (argc > 2) {
		n = atoi(argv[2]);
	}
	
	if (!strcmp(argv[1], "tcpclient")) {
		doClient<TCP_Socket>(n);
	} else if (!strcmp(argv[1], "tcpserver")) {
		doServer<TCP_Socket>();
	} else if (!strcmp(argv[1], "udtclient")) {
		doClient<UDT_Socket>(n);
	} else if (!strcmp(argv[1], "udtserver")) {
		doServer<UDT_Socket>();
	} else {
		cout << "what do you want ?" << endl;
		return 1;
	}

	return 1;
}