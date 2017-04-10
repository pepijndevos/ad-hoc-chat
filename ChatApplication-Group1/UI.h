/*
 * UI.h
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef UI_H_
#define UI_H_
#include <vector>
#include <string>

class UI {
public:
	UI();
	virtual ~UI();
	void sendMessage();
	void sendFile();
	void newChat();
	void addUser();
	void setPassword();

private:
	int chats;
	std::vector<int> chat_users;
	std::vector<std::string> chat_messages;
	void updateMessages();

};

#endif /* UI_H_ */
