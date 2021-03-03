#include "Window.h"



bool Window::Close() {
	if (!hWnd) { 
		return false;
	}
	return CloseWindow(hWnd);
}


bool Window::IsOpen() {
	return IsWindowVisible(hWnd);
}


bool Window::Title(std::string newTitle) {
	if (!hWnd) {
		return false;
	}
	title = newTitle;
	return SetWindowTextA(hWnd, title.c_str());
}


void Window::Update() {
}


Window::Window(HINSTANCE hInstance) {
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);
	//wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wcex.lpszMenuName = nullptr;
	wcex.lpfnWndProc = Window::WindowCallback;

	title = "New Window";
	wchar_t* title_w = new wchar_t[title.length() + 1];
	std::copy(title.begin(), title.end(), title_w);
	title_w[title.length()] = 0;
	wcex.lpszClassName = title_w;

	wcex.hInstance = hInstance;
	wcex.lpfnWndProc = DefWindowProc;
	RegisterClassEx(&wcex);

	hWnd = CreateWindow(wcex.lpszClassName, title_w, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		CW_USEDEFAULT,CW_USEDEFAULT, 640, 480, 0, 0 , hInstance, 0);
	if (!hWnd) {
		MessageBox(0, L"Failed to create window!.", 0, 0);
		return;
	}
	SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)this);



	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}


LRESULT CALLBACK Window::WindowCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	
	LRESULT result = 0;
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		window->Close();
	} break;
	case WM_SIZE: {
		window->Close();
	} break;
	default: {
		result = DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	}
	return result;
}