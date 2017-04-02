// Anything after // is a comment not actual C++ code
// Comments are important and I use them to explain things
// Why not read the comments in this code

// These "include" code from the C++ library and SFML too
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using namespace std;

// This is the main C++ program- Duh!
// It is where our game starts from
int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();
	sf::TcpSocket socket;
	char connectionType, mode; 
	char buffer[2000];
	size_t received;
	string text = "Connected to ";

	cout << "Enter (s) for Server, Enter for (c) for client" << endl;
	cin >> connectionType;

	if (connectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		text += "Server";
	}
	else if (connectionType == 'c')
	{
		socket.connect(ip, 2000);
		text += "Client";
	}

	socket.send(text.c_str(), text.size() + 1);
	socket.receive(buffer, sizeof(buffer), received);

	cout << buffer << endl;

	system("pause");
	return 0;
}