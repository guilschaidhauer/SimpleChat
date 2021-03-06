#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>

using namespace std;

int main()
{
	sf::IpAddress ip = sf::IpAddress::getLocalAddress();

	sf::TcpSocket socket1;
	//socket1.setBlocking(false);
	sf::TcpSocket socket2;
	//socket2.setBlocking(false);
	
	char buffer1[2000];
	char buffer2[2000];

	size_t received1;
	size_t received2;

	string connectionType, mode;

	string text1 = "Connected to ";
	string text2 = "Connected to ";

	cout << "Enter 's' to connect as a server, Enter for '1' for client 1 and '2' for client 2" << endl;
	getline(cin, connectionType);

	if (connectionType == "s")
	{
		sf::TcpListener listener;
		listener.listen(2000);
		listener.accept(socket1);

		sf::TcpListener listener1;
		listener1.listen(2001);
		listener1.accept(socket2);

		text1 += "Server";
		text2 += "Server";

		mode = 'r';

		socket1.send(text1.c_str(), text1.size() + 1);
		socket1.receive(buffer1, sizeof(buffer1), received1);

		socket2.send(text2.c_str(), text2.size() + 1);
		socket2.receive(buffer2, sizeof(buffer2), received2);

		cout << buffer1 << endl;
		cout << buffer2 << endl;
	}
	else if (connectionType == "1")
	{
		socket1.connect(ip, 2000);
		text1 += "Client1";
		mode = 's';

		socket1.send(text1.c_str(), text1.size() + 1);
		socket1.receive(buffer1, sizeof(buffer1), received1);

		cout << buffer1 << endl;
	}
	else if (connectionType == "2")
	{
		socket2.connect(ip, 2001);
		text1 += "Client2";
		mode = 'r';

		socket2.send(text1.c_str(), text1.size() + 1);
		socket2.receive(buffer2, sizeof(buffer2), received2);

		cout << buffer2 << endl;
	}

	cout << endl;

	system("cls");
	Sleep(1000);

	bool done = false;

	while (!done)
	{
		if (connectionType == "s")
		{
			if (mode == "r")
			{
				socket1.receive(buffer1, sizeof(buffer1), received1);
				if (received1 > 0)
				{
					cout << "Received: " << buffer1 << endl;
					socket2.send(buffer1, sizeof(buffer1));
					mode = "s";
				}
			}
			else if (mode == "s")
			{
				socket2.receive(buffer2, sizeof(buffer2), received2);
				if (received2 > 0)
				{
					cout << "Received: " << buffer2 << endl;
					socket1.send(buffer2, sizeof(buffer2));
					mode = 'r';
				}
			}
		}
		else if (connectionType == "1")
		{
			if (mode == "s") 
			{
				cout << "Type in your message: ";
				getline(cin, text1);

				if (text1.size() <= 0)
					continue;

				socket1.send(text1.c_str(), text1.size() + 1);
				mode = "r";
			}
			else if (mode == "r")
			{
				socket1.receive(buffer1, sizeof(buffer1), received1);
				if (received1 > 0)
				{
					cout << "Received from client 2: " << buffer1 << endl;
					mode = "s";
				}
			}
		}
		else if (connectionType == "2")
		{
			if (mode == "s")
			{
				cout << "Type in your message: ";
				getline(cin, text2);

				if (text2.size() <= 0)
					continue;

				socket2.send(text2.c_str(), text2.size() + 1);
				mode = "r";
			}
			else if (mode == "r")
			{
				socket2.receive(buffer2, sizeof(buffer2), received2);
				if (received2 > 0)
				{
					cout << "Received from client 1: " << buffer2 << endl;
					mode = "s";
				}
			}
		}

	}

	system("pause");
	return 0;
}