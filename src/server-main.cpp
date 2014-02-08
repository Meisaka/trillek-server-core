
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "net/network.h"
#include "filesystem.hpp"
#include "server.hpp"

int main(int argc, char* argv[], char** env) {
	network::TCPConnection lhost;
	std::vector<std::unique_ptr<network::TCPConnection>> rhosts;
	network::TCPConnection* rhost;
	std::string txtrh;
	int i, rcc;
	network::NetworkAddress la;
	char * dbf = 0;
	Server::Configuration serverconfig;

	{
		Server::LocalFile sconf("config.json");
		if(sconf.isOpen()) {
			serverconfig.Load(sconf);
		}
	}
	// Welcome message
	std::string txt = "\xe3\x81\x8a\xe3\x81\xaf\xe3\x82\x88\xe3\x81\x86\xef\xbc\x81";

	dbf = new char[1500];

	network::Initialize();

	la.IP4(0ul); // All IP
	la.Port(0x102C); // aka 4140
	lhost.Init(network::NETA_IPv4);
	lhost.Bind(la);
	lhost.Listen(30);
	if(lhost.IsListening()) {
		std::cout << "Trillek Server (Dev Version)\n"
			"Listening on all interfaces port 4140\n"
			"-----------------\n";
		std::cout.flush();
	} else {
		std::cout << "Trillek Server (Dev Version)\n"
			"Can not open network!\n"
			"Exiting.\n";
		return 1;
	}
	i = 0;
	while(lhost.IsListening()) {
		if(lhost.Select(true,false,false,0,0)) { // Handle new connections
			rhost = new network::TCPConnection;
			rhost->Accept(&lhost);
			rhost->Send(txt.c_str(), txt.length()); // send welcome
			std::cout << "Connection from " << rhost->GetRemote().ToString() << std::endl;
			rhosts.push_back(std::unique_ptr<network::TCPConnection>(rhost));
			rhost = NULL;
		}
		// handle messages from the Virtual CPU process/thread here

		// TODO Send any sync messages here
		//

		// Handle receives
		if(rhosts.size() > 0) {
			for(auto itrc = rhosts.begin(); itrc != rhosts.end(); itrc++) {
				if((*itrc)->IsConnected()) {
					while((*itrc)->Select(true,false,false,0,0)) {
						if((rcc=(*itrc)->Recv(dbf, 400)) > 0) {
							// Very simple recive function
							// TODO make it do something
							std::cout << "Recv: " << rcc << std::endl;
						}
					}
				} else {
					std::cout << "Connection with " << (*itrc)->GetRemote().ToString() << " closed\n";
					(*itrc)->Close();
					rhosts.erase(itrc);
					break;
				}
			}
		}
		// TODO Update server side here
		network::sleep(1);
	}
	lhost.Close();
	return 0;
}

