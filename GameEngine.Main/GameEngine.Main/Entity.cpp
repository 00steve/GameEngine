#include "Entity.h"



bool Entity::AddChild(Entity* child) {
	return false;
}


Entity::Entity() {

}


bool Entity::ReadMessage(Message message) {
	return false;
}

bool Entity::ReadMessageQueue() {
	while (messages.Count() > 0) {
		ReadMessage(messages.Pop());
	}
	return true;
}


bool Entity::ReceiveMessage(Message message) {
	messages.Push(message);
	return true;
}

bool Entity::SendMsg(Message message, Entity* receiver) {
	if (!receiver) return false;
	receiver->ReceiveMessage(message);
	return true;
}


void Entity::Update() {
	ReadMessageQueue();
}