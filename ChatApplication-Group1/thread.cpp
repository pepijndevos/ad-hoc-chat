#include <thread>
#include <cstring>
#include <unistd.h>
#include <iostream>
#include "AdHoc.h"
#include "Transciever.h"
#include "Packet.h"
#include "Routing.h"
#include "RaftNode.h"
#include "UI.h"
#include "Security.h"
#include "BlockingQueue.h"
#include "Datta.h"

#define PORT 14000 //The port you want to use
#define IP "192.168.5.1" //The IP address of this computer
#define GROUP "228.1.2.3" //The multicast group you want to use

using namespace std;
BlockingQueue<std::string> q;

int main() {
	//thread t1(&Transciever::sendPacket, IP, PORT, GROUP); //start networking sending thread
	//std::thread Transciever(receivePacket, IP, PORT, GROUP, std::ref(q)); //start network receiving thread

	while(1)
	{
		std::string message = q.pop();
		std::cout << "Packet of size " << message.size() << " received, message: " << message << std::endl;;
	}
}
