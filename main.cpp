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
	struct sockaddr_in address;
	//char* hello = "hello from server"
	//char buffer[1024] = { 0 };
	int server_fd; //, new_socket, valread
	//int addrlen = sizeof(address);
	int opt = 1;

	//AF_INET = adress familly (ipv4)
	//SOCK_STREAM = type de flux
	//---------Creation du fd du server--------------
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
	//----------Gestion des options de la socket---------------
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR/* | SO_REUSEPORT*/, &opt, sizeof(opt)))
	{
		perror("Setsockopt");
		exit(EXIT_FAILURE);
	}

	//remplir info de la communication
	address.sin_family = AF_INET;
	//permet d'affecter la socket a tous les adresses locales
	address.sin_addr.s_addr = INADDR_ANY;
	//affectation du port
	address.sin_port = htons(PORT);
	
	std::cout << "Valeur af_inet : " << AF_INET << std::endl;
	std::cout << "Valeur sock_stream : " << SOCK_STREAM << std::endl;
	std::cout << "Valeur PORT : " << PORT << std::endl;
	std::cout << "Valeur INADDR_ANY : " << INADDR_ANY << std::endl;

	//associe une socket a une adress et un port 
	if(bind(server_fd, (struct sockaddr*)&address))
	{
		perror("Bind fail");
		exit(EXIT_FAILURE);
	}


	return 0;
}
