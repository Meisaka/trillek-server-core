
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include "net/network.h"
#include "filesystem.hpp"
#include "server.hpp"

int main(int argc, char* argv[], char** env) {
	network::TCPConnection lhost;
	std::vector<std::shared_ptr<network::TCPConnection>> rhosts;
	std::vector<std::weak_ptr<network::TCPConnection>> uahosts;
	network::TCPConnection* rhost;
	network::UDPSocket uhost;
	std::string txtrh;
	int i, rcc;
	network::NetworkAddress la;
	network::NetworkAddress ra;
	char * dbf = 0;
	std::string inbuf;
	rapidjson::GenericStringBuffer<rapidjson::UTF8<char>> outst;

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
	std::cout <<
	"Trillek Server (Dev Version)\n";

	network::Initialize();

	la.IP4(0ul); // All IP
	la.Port(0x102C); // aka 4140
	lhost.Init(network::NETA_IPv4);
	lhost.Bind(la);
	lhost.Listen(30);
	if(lhost.IsListening()) {
		std::cout <<
			"Listening on all interfaces port 4140\n"
			"-----------------\n";
		std::cout.flush();
	} else {
		std::cout <<
			"Can not open network!\n"
			"Exiting.\n";
		return 1;
	}
	uhost.Init(network::NETA_IPv4);
	uhost.Bind(la);
	uhost.SetNonBlocking();
	i = 0;
	while(lhost.IsListening()) {
		if(lhost.Select(true,false,false,0,0)) { // Handle new connections
			rhost = new network::TCPConnection;
			rhost->Accept(&lhost);
			rhost->Send(txt.c_str(), txt.length()); // send welcome
			std::cout << "Connection from " << rhost->GetRemote().ToString() << std::endl;
			rhosts.push_back(std::shared_ptr<network::TCPConnection>(rhost));
			uahosts.push_back(std::weak_ptr<network::TCPConnection>(rhosts[rhosts.size()-1]));
			rhost = NULL;
		}
		// handle messages from the Virtual CPU process/thread here

		// TODO Send any sync messages here
		//
		if((rcc = uhost.RecvFrom(ra, dbf, 1500)) > 0) {
			std::cout << "M-Recv: " << rcc << " from " << ra.ToString() << std::endl;
			inbuf.assign(dbf, rcc);
			inbuf += "!";
			uhost.SendTo(ra, inbuf);
		}
		//for(auto itrt = rhosts.begin(); itrt != rhosts.end(); itrt++) {
		//	if((*itrt)->IsConnected() && (*itrt)->Select(false,true,false,0,0)) {
		//		(*itrt)->Send("X", 1);
		//	}
		//}

		for(auto itrc = uahosts.begin(); itrc != uahosts.end(); itrc++) {
			if((*itrc).expired()) {
				uahosts.erase(itrc);
				break;
			}
		}

		// Handle receives
		if(rhosts.size() > 0) {
			for(auto itrc = rhosts.begin(); itrc != rhosts.end(); itrc++) {
				if((*itrc)->IsConnected()) {
					while((*itrc)->Select(true,false,false,0,0)) {
						if((rcc=(*itrc)->Recv(dbf, 1500)) > 0) {
							// Very simple recive function
							// TODO make it do something
							inbuf.assign(dbf, rcc);
							std::cout << "Recv: " << inbuf.length() << std::endl;
							for(auto itrt = rhosts.begin(); itrt != rhosts.end(); itrt++) {
								if(itrt != itrc && (*itrt)->IsConnected() && (*itrt)->Select(false,true,false,0,0)) {
									(*itrt)->Send(inbuf.data(), inbuf.length());
								}
							}
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
	uhost.Close();
	return 0;
}

