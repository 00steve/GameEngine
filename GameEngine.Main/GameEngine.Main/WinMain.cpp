

#include "DevUtils.h"
#include "Window.h"
#include "DirectX11.h"



int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {



	
	Window w = Window(hInstance);
	w.Title("My game!");

	DirectX11 dx = DirectX11(w.Handle());
	//dx.AddToWindow((Entity*)&w);

	MSG msg = { 0 };

	while (w.IsOpen()) { //msg.message != WM_QUIT && more shit to keep the program going
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		w.Update();
		dx.Update();
	}
	

	return 0;

}