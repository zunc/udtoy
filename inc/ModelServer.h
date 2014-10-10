/* 
 * File:   ServerModel.h
 * Author: khoai
 *
 * Created on October 10, 2014, 11:29 AM
 */

#ifndef SERVERMODEL_H
#define	SERVERMODEL_H

// simple server, one thread working on blocking socket

#include "ISocket.h"

using namespace std;

template <class T>
class ModelServer {
public:

	ModelServer(string& host, int port) : _host(host), _port(port) {
		_socket = new T(_host, _port);
	}

	void init() {
		_socket->doListen();
	}

	void close() {
		_socket->close();
	}

	void run() {
		while (true) {
			int fd = _socket->doAccept();
			if (fd <= 0) {
				cout << "ModelServer::run.doAccept " << fd << endl;
				continue;
			}
			
			cout << "onConnect" << endl;
			//--- client process: echo
			T conn(fd);
			while (true) {
				uint8_t buff[128] = {0};
				int res = conn.read(buff, sizeof (buff));
				if (res <= 0) {
					cout << "ModelServer::run.recv " << res << endl;
					conn.close();
					cout << "onDisconnect" << endl;
					break;
				} else {
					conn.write(buff, res);
				}
			}
		}

		cout << "break: RUN" << endl;
	}

private:
	string _host;
	int _port;
	T* _socket;
};


#endif	/* SERVERMODEL_H */

