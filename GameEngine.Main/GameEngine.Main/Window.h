#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <string>

#include "Entity.h"



#define MAX_CLASS_NAME_LENGTH 256
#define HInstance() GetModuleHandle(NULL)




class Window : protected Entity {
private:
	HWND			hWnd;
	std::string		title;
	WNDCLASSEX		wcex;

	static LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMSG, WPARAM wParam, LPARAM lPARAM);

public:

	bool Close();

	HWND Handle();

	bool IsOpen();

	bool ReadMessage(Message message);

	bool Title(std::string newTitle);

	void Update();

	Window(HINSTANCE hInstance);



};