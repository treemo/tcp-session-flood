#pragma once

#include "thread/Thread.h"

class Flood : public Thread<Flood>
{
	public:
		Flood(std::string host, unsigned short int port);
		~Flood(void);
		void update();

	private:
		bool m_start;
		std::string m_host;
		unsigned short int m_port;
};
