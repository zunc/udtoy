/* 
 * File:   UDT_Socket.h
 * Author: khoai
 *
 * Created on October 10, 2014, 2:35 PM
 */

#ifndef UDT_SOCKET_H
#define	UDT_SOCKET_H

#include <errno.h>
#include "ISocket.h"

#include <udt.h>

using namespace UDT;

class UDT_Socket : public ISocket {
protected:
	string host_;
	int port_;
	UDTSOCKET fd_;
public:

	UDT_Socket(string& host, int port) : host_(host), port_(port) {

	}

	UDT_Socket(int fd) : fd_(fd) {

	}

	void open() {
		UDTSOCKET client = UDT::socket(AF_INET, SOCK_STREAM, 0);

		sockaddr_in serv_addr;
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_port = htons(this->port_);
		inet_pton(AF_INET, this->host_.c_str(), &serv_addr.sin_addr);

		memset(&(serv_addr.sin_zero), '\0', 8);

		if (UDT::ERROR == UDT::connect(client, (sockaddr*) & serv_addr, sizeof (serv_addr))) {
			cout << "connect: " << UDT::getlasterror().getErrorMessage();
			this->fd_ = 0;
			return;
		}
		
		this->fd_ = client;
	}

	void close() {
		UDT::close(this->fd_);
		this->fd_ = 0;
	}

	uint32_t read(uint8_t* buf, uint32_t len) {
		return UDT::recv(this->fd_, (char*) buf, len, 0);
	}

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
		return UDT::send(this->fd_, (char*) buf, len, 0);
	}

	void doListen() {
		fd_ = UDT::socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in my_addr;
		my_addr.sin_family = AF_INET;
		my_addr.sin_port = htons(this->port_);
		my_addr.sin_addr.s_addr = INADDR_ANY;
		memset(&(my_addr.sin_zero), '\0', 8);

		if (UDT::ERROR == UDT::bind(fd_, (sockaddr*) & my_addr, sizeof (my_addr))) {
			cout << "bind: " << UDT::getlasterror().getErrorMessage();
			return;
		}

		if (UDT::ERROR == UDT::listen(fd_, 10)) {
			cout << "listen: " << UDT::getlasterror().getErrorMessage();
			return;
		}
	}

	uint32_t doAccept() {
		int namelen = 0;
		sockaddr_in their_addr;
		UDTSOCKET recver = UDT::accept(fd_, (sockaddr*) & their_addr, &namelen);
		if (UDT::ERROR == recver) {
			cout << "accept: " << UDT::getlasterror().getErrorMessage() << endl;
		}
		return recver;
	}

};

#endif	/* UDT_SOCKET_H */

