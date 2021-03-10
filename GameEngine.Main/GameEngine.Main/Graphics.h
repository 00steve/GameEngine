#pragma once

#include <Windows.h>
#include "Entity.h"


class Graphics : public Entity {
private:

	//Entity* window = NULL;


public:

	//bool AddToWindow(Entity* window);
	//void AddWindowHandle(HWND hWnd);


	virtual void Redraw() = 0;

	void Update();
};