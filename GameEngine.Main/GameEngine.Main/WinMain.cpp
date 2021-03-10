#include <iostream>
#include <sstream>

#include "Window.h"
#include "DirectX11.h"

#define DBOUT( s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {



	
	Window w = Window(hInstance);
	w.Title("My game!");

	DirectX11 dx = DirectX11(w.Handle());
	//dx.AddToWindow((Entity*)&w);

	MSG msg = { 0 };

	while (msg.message != WM_QUIT && w.IsOpen()) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		w.Update();
		dx.Update();
	}
	

	return 0;

}