/* 
 * File:   ModelClient.h
 * Author: khoai
 *
 * Created on October 10, 2014, 10:53 AM
 */

#ifndef MODELCLIENT_H
#define	MODELCLIENT_H

#include "ISocket.h"
#include "Util.h"

using namespace std;

template <class T>
class ModelClient {
public:

	ModelClient(string& host, int port) : _host(host), _port(port) {
		_socket = new T(_host, _port);
	}

	void init() {
		_socket->open();
	}

	void close() {
		_socket->close();
	}

	void run(uint32_t n = 1000) {
		cout << "[] begin(" << n << ")" << endl;
		for (int i = 0; i < n; i++) {
			_socket->write((uint8_t*) "hello", 5);
			uint8_t buff[128] = {0};
			int res = _socket->read(buff, 128);
			//cout << "[" << i << "] res(" << res << ") : " << buff << endl;
			int percent = 0;
			if (percent = Util::isPercentProcStep(n, i, 10)) {
				cout << "process: " << percent << "%" << endl;
			}
		}
		cout << "[] finish" << endl;
	}

private:
	string _host;
	int _port;
	T* _socket;
};

#endif	/* MODELCLIENT_H */

