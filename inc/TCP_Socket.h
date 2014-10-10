/* 
 * File:   TCP_Socket.h
 * Author: khoai
 *
 * Created on October 10, 2014, 10:17 AM
 */

#ifndef TCP_SOCKET_H
#define	TCP_SOCKET_H

#include <errno.h>
#include "ISocket.h"

class TCP_Socket : public ISocket {
protected:
	string host_;
	int port_;
	int fd_;
public:

	TCP_Socket(string& host, int port) : host_(host), port_(port) {

	}

	TCP_Socket(int fd) : fd_(fd) {

	}

	void open() {
		int client = socket(AF_INET, SOCK_STREAM, 0);

		sockaddr_in serv_addr;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(this->port_);
		inet_pton(AF_INET, this->host_.c_str(), &serv_addr.sin_addr);

		memset(&(serv_addr.sin_zero), '\0', 8);

		if (0 < connect(client, (sockaddr*) & serv_addr, sizeof (serv_addr))) {
			cout << "connect: " << strerror(errno) << endl;
			this->fd_ = 0;
			return;
		}
		this->fd_ = client;
	}

	void close() {
		shutdown(this->fd_, SHUT_RDWR);
		this->fd_ = 0;
	}

	uint32_t read(uint8_t* buf, uint32_t len) {
		return recv(this->fd_, buf, len, 0);
	}

	//	uint32_t read(uint8_t* buf, uint32_t len) {
	//		int remain = len;
	//		while (remain > 0) {
	//			int pos = len - remain;
	//			int res = recv(buf + pos, remain);
	//			if (res <= 0) {
	//				cout << "read: " << strerror(errno) << endl;
	//			} else {
	//				remain -= res;
	//			}
	//		}
	//		return 0;
	//	}

	void write(const uint8_t* buf, uint32_t len) {
		int remain = len;
		while (remain > 0) {
			int pos = len - remain;
			int res = write_partial(buf + pos, remain);
			if (res <= 0) {
				cout << "write: " << strerror(errno) << endl;
			} else {
				remain -= res;
			}
		}
		return;
	}

	uint32_t write_partial(const uint8_t* buf, uint32_t len) {
		return send(this->fd_, buf, len, 0);
	}

	void doListen() {
		fd_ = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in my_addr;
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(this->port_);
		my_addr.sin_addr.s_addr = INADDR_ANY;
		memset(&(my_addr.sin_zero), '\0', 8);

		int yes = 1;
		if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof (int)) == -1) {
			cout << "setsockopt: " << strerror(errno) << endl;
			return;
		}

		if (0 < bind(fd_, (sockaddr*) & my_addr, sizeof (my_addr))) {
			cout << "bind: " << strerror(errno) << endl;
			return;
		}

		if (0 < listen(fd_, 10)) {
			cout << "listen: " << strerror(errno) << endl;
			return;
		}
	}

	uint32_t doAccept() {
		unsigned int namelen = 0;
		sockaddr_in their_addr;
		int recver = accept(fd_, (sockaddr*) & their_addr, &namelen);
		if (0 >= recver) {
			cout << "accept: " << strerror(errno) << endl;
		}
		return recver;
	}

};

#endif	/* TCP_SOCKET_H */

