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
	char buffer[1024] = { 0 };
	int server_fd, new_socket, valread;
	int addrlen = sizeof(address);
	int opt = 1;
	std::string hello("hello from server");

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
	
	std::cout << "Valeur AF_INET : " << AF_INET << std::endl;
	std::cout << "Valeur SOCK_STREAM : " << SOCK_STREAM << std::endl;
	std::cout << "Valeur PORT : " << PORT << std::endl;
	std::cout << "Valeur INADDR_ANY : " << INADDR_ANY << std::endl;

	//associe une socket a une adress et un port 
	if(bind(server_fd, (struct sockaddr*)&address, addrlen))
	{
		perror("Bind fail");
		exit(EXIT_FAILURE);
	}

	// met le serveur en mode passif et attend la connection de clients
	// 3 = longuer max de le queue
	if(listen(server_fd, 3) < 0)
	{
		perror("Listen fail");
		exit(EXIT_FAILURE);
	}

	//creation d'une connection entre le serveur et le client 
	if((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
	{
		std::cout << "Valeur socket : " << new_socket << std::endl;
		perror("Not accepted");
		exit(EXIT_FAILURE);
	}
	
	std::cout << "Valeur socket : " << new_socket << std::endl;
	
	valread = read(new_socket, buffer, 1024);
	std::cout<< buffer << std::endl;
	send(new_socket, hello.c_str(), hello.size(), 0);
	
	close(new_socket);
	shutdown(server_fd, SHUT_RDWR);

	return 0;
}
