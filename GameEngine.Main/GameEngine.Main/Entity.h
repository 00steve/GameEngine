#pragma once


#include <cstddef>

#include "UnorderedList.h"
#include "Message.h"


class Entity {
private:

	UnorderedList<Message> messages;

protected:

	bool ReadMessage(Message message);

public:

	bool AddChild(Entity* child);

	Entity();

	bool ReadMessageQueue();
	bool ReceiveMessage(Message message);
	bool SendMsg(Message message, Entity* receiver);

	void Update();

};