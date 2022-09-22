#include <netinet/in.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

int main(int argc, char** argv)
{
	int server_fd;
	int opt = 1;

	//AF_INET = adress familly (ipv4)
	//SOCK_STREAM = type de flux
	//creation du fd du server
	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	std::cout << "Valeur serveur_fd : " << server_fd << std::endl;

	//SOL_SOCKET = niveau ou s'appliquent les modifications (socket)
	//SO_REUSEADDR = option pour setsockopt() (valide les adresses envoyees a bind, autorise la reutilisation des adresses locals)
	//SO_REUSEPORT = pareil pour le port
	//opt = booleen utiliser pour valider ou pas une option
	//Gestion des options de la socket
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR/* | SO_REUSEPORT*/, &opt, sizeof(opt)))
	{
		perror("Setsockopt");
		exit(EXIT_FAILURE);
	}

	std::cout << "Valeur serveur_fd : " << server_fd << std::endl;

	return 0;
}
