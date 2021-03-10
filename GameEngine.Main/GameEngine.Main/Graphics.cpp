#include "Graphics.h"



//bool Graphics::AddToWindow(Entity* window) {
	//this->window = window;
	//Message m;
	//m.Code = ADD_GRAPHICS;
	//m.Sender = this;
	//return SendMsg(m, window);
	//return true;
//}



void Graphics::Update() {
	Entity::Update();
	Redraw();
}