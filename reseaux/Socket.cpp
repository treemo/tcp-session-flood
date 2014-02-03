/* 
 * File:   Socket.cpp
 * Author: Treemo
 * revision: 2
 * 
 * Created on 25 décembre 2012, 13:28
 */

#include <string>
#include "string.h"

#include "Socket.h"

Socket::Socket()
{
	init();
}

Socket::~Socket()
{
	closesocket(m_socket);

#if defined (WIN32)
	WSACleanup();
#endif
}

void Socket::init()
{
#if defined (WIN32)
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err < 0)
    {
		std::cout << "Erreur " << __FILE__ << ":" << __LINE__ << " WSAStartup" << std::endl;
        exit(EXIT_FAILURE);
    }
#endif
}

bool Socket::connexion(std::string host, unsigned short int port)
{
	m_socket = socket(AF_INET, SOCK_STREAM, 0);
	
	if(m_socket == INVALID_SOCKET)
	{
		std::cout << "Erreur " << __FILE__ << ":" << __LINE__ << " INVALID_SOCKET" << std::endl;
		return false;
	}

	SOCKADDR_IN sin = { 0 };

	sin.sin_port = htons(port);
	sin.sin_family = AF_INET;
	
	struct hostent *hostinfo = NULL;

	hostinfo = gethostbyname( host.c_str() );
	if (hostinfo != NULL)
		sin.sin_addr = *(in_addr *) hostinfo->h_addr;
	else
		sin.sin_addr.s_addr = inet_addr( host.c_str() );

	if(connect(m_socket, (SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		std::cout << "Erreur " << __FILE__ << ":" << __LINE__ << " connect" << std::endl;
		return false;
	}

	return true;
}

bool Socket::ecoute(unsigned short int port)
{
	return false;
}

bool Socket::envoi(const char* envoi)
{
	if(send(m_socket, envoi, strlen(envoi), 0) < 0)
	{
		std::cout << "Erreur " << __FILE__ << ":" << __LINE__ << " envoi:'" << envoi << "'" <<  std::endl;
		return false;
	}
	
	return true;
}

char* Socket::reception()
{
	char buffer[65025];
	int n = 0;

	if((n = recv(m_socket, buffer, sizeof buffer - 1, 0)) < 0)
	{
		std::cout << "Erreur " << __FILE__ << ":" << __LINE__ << " reception" << std::endl;
		return "";
	}

	buffer[n] = '\0';

	return buffer;
}