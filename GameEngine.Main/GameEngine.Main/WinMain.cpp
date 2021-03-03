#include "Window.h"




int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	Window w = Window(hInstance);


	w.Title("My game!");
	MSG msg = { 0 };

	while (msg.message != WM_QUIT && w.IsOpen()) {
		if (PeekMessage(&msg, 0, 0, 0,PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}


	return 0;

}