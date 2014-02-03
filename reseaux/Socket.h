/* 
 * File:   Socket.h
 * Author: Treemo
 * revision: 2
 *
 * Created on 25 décembre 2012, 13:28
 */

#pragma once

#if defined (WIN32)
	#include <winsock2.h>
	typedef int socklen_t;
	#ifdef _MSC_VER
		#pragma comment(lib, "ws2_32.lib")
	#endif
#elif defined (linux)
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket(s) close(s)
	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#endif

#include <iostream>

class Socket
{
	public:
		Socket();
		virtual ~Socket();
		bool connexion(std::string host, unsigned short int port);
		bool ecoute(unsigned short int port);
		bool envoi(const char* envoi);
		char* reception();
	
	private:
		void init();

	private:
		SOCKET m_socket;
};