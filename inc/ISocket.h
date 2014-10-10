/* 
 * File:   ISocket.h
 * Author: khoai
 *
 * Created on October 10, 2014, 10:09 AM
 */

#ifndef ISOCKET_H
#define	ISOCKET_H

#include <netdb.h>
#include <arpa/inet.h>

using namespace std;

class ISocket {
public:
	
	// client side
	virtual void open() = 0;
	
	// general
	virtual void close() = 0;
	virtual uint32_t read(uint8_t* buf, uint32_t len) = 0;
	virtual void write(const uint8_t* buf, uint32_t len) = 0;
	virtual uint32_t write_partial(const uint8_t* buf, uint32_t len) = 0;
	
	// server side
	virtual void doListen() = 0;
	virtual uint32_t doAccept() = 0;
};

#endif	/* ISOCKET_H */

