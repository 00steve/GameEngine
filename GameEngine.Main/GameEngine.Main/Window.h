#pragma once

#include <string>
#include <windows.h>

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

	bool IsOpen();

	bool Title(std::string newTitle);


	void Update();


	Window(HINSTANCE hInstance);



};