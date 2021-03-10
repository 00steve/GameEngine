#pragma once

#include <windows.h>
#include <d3d11.h>       // D3D interface
#include <dxgi.h>        // DirectX driver interface
#include <d3dcompiler.h> // shader compiler
#include <string>
#include <assert.h>

#pragma comment( lib, "user32" )          // link against the win32 library
#pragma comment( lib, "d3d11.lib" )       // direct3D library
#pragma comment( lib, "dxgi.lib" )        // directx graphics interface
#pragma comment( lib, "d3dcompiler.lib" ) // shader compiler

#include "Graphics.h"



class DirectX11 : public Graphics {
private:
	ID3D11Device* device_ptr = NULL;
	ID3D11DeviceContext* device_context_ptr = NULL;
	IDXGISwapChain* swap_chain_ptr = NULL;
	ID3D11RenderTargetView* render_target_view_ptr = NULL;
	HRESULT hr = NULL;
	ID3D11VertexShader* vertex_shader_ptr = NULL;
	ID3D11PixelShader* pixel_shader_ptr = NULL;

	ID3D11InputLayout* input_layout_ptr = NULL;
	//D3D11_INPUT_ELEMENT_DESC* inputElementDesc = NULL;

	D3D11_RASTERIZER_DESC* rasterizer = NULL;

	ID3D11Texture2D* framebuffer;
	ID3D11Buffer* vertex_buffer_ptr = NULL;
	HWND hWnd = NULL;

	float* vertex_data_array = NULL;
	UINT vertex_stride = 3 * sizeof(float);
	UINT vertex_offset = 0;
	UINT vertex_count = 3;

	float background_color[4] = { .5,.5,.5,1 };

public:

	DirectX11(HWND windowsHandle);

	~DirectX11();

	bool ReadMessage(Message message);

	void Redraw();

};