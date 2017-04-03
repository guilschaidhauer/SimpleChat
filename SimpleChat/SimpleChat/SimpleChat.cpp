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

	sf::TcpSocket socket1;
	sf::TcpSocket socket2;
	
	char buffer1[2000];
	char buffer2[2000];

	size_t received1;
	size_t received2;

	char connectionType, mode;

	string text1 = "Connected to ";
	string text2 = "Connected to ";

	cout << "Enter (s) for Server, Enter for (c) for client" << endl;
	cin >> connectionType;

	if (connectionType == 's')
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket1);

		sf::TcpListener listener1;
		listener1.listen(2001);
		listener1.accept(socket2);

		text1 += "Server";
		text2 += "Server";
		mode = 's';

		socket1.send(text1.c_str(), text1.size() + 1);
		socket1.receive(buffer1, sizeof(buffer1), received1);

		socket2.send(text2.c_str(), text2.size() + 1);
		socket2.receive(buffer2, sizeof(buffer2), received2);

		cout << buffer1 << endl;
		cout << buffer2 << endl;
	}
	else if (connectionType == '1')
	{
		socket1.connect(ip, 2000);
		text1 += "Client1";
		mode = 'r';

		socket1.send(text1.c_str(), text1.size() + 1);
		socket1.receive(buffer1, sizeof(buffer1), received1);

		cout << buffer1 << endl;
	}
	else if (connectionType == '2')
	{
		socket2.connect(ip, 2001);
		text1 += "Client2";
		mode = 'r';

		socket2.send(text1.c_str(), text1.size() + 1);
		socket2.receive(buffer2, sizeof(buffer2), received2);

		cout << buffer2 << endl;
	}

	/*bool done = false;

	while (!done)
	{
		if (mode == 's')
		{
			getline(cin, text);
			socket.send(text.c_str(), text.size() + 1);
			mode = 'r';
		}
		else if (mode == 'r')
		{
			socket.receive(buffer, sizeof(buffer), received);
			if (received > 0)
			{
				cout << "Received: " << buffer << endl;
				mode = 's';
			}
		}
	}*/

	system("pause");
	return 0;
}