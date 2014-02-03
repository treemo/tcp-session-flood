/*
 * File:   main.cpp
 * Author: Treemo
 *
 * Created on 19 décembre 2012, 16:43
 */

void addConnexion();

#if defined (WIN32)
    #include <winsock2.h>
#elif defined (linux)
    #include <unistd.h>
#endif

#include "Flood.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    printf("Usage :\n%s <host> <port> <thread>\n\n", argv[0]);

    if (argc < 1)
    {
        printf("host requis !\n");
		return 1;
    }

    if (argc < 2)
    {
        printf("port requis !\n");
		return 1;
    }

	std::string host = argv[1];
	unsigned short int port = atoi(argv[2]);
	unsigned short int nbThread = 1;

    if (argc < 3)
    {
        nbThread = atoi(argv[3]);
    }

    if (nbThread <= 0)
		nbThread = 1;

    printf("host: %s\nport: %d\nnombre de thread: %d\n\n", host.c_str(), port, nbThread);

	for (int i = 0; i <= nbThread; i++)
		new Flood(host, port);

	while(true)
        #if defined (WIN32)
            Sleep(100000000);
        #elif defined (linux)
	        usleep(10000000);
        #endif

	return 0;
}

int bnConnexion = 0;
void addConnexion()
{
	bnConnexion++;
	printf("connexion: %d\n", bnConnexion);
}
