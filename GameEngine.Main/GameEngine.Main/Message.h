#pragma once

#define ADD_GRAPHICS 100
#define ADD_WINDOW_HANDLE 101




class Entity;



struct Message {
	unsigned int Code;
	Entity* Sender;
	void* Data;
};