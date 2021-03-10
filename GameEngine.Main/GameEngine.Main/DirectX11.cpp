/*
Resources:
https://antongerdelan.net/opengl/d3d11.html


*/


#include "DirectX11.h"

//#define ARRAYSIZE(a) \
//  ((sizeof(a) / sizeof(*(a))) / \
//  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))


DirectX11::DirectX11(HWND windowsHandle) {
	hWnd = windowsHandle;

	DXGI_SWAP_CHAIN_DESC swap_chain_descr = { 0 };
	swap_chain_descr.BufferDesc.RefreshRate.Numerator = 0;
	swap_chain_descr.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_descr.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swap_chain_descr.SampleDesc.Count = 1;
	swap_chain_descr.SampleDesc.Quality = 0;
	swap_chain_descr.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_descr.BufferCount = 1;
	
	//only needed if putting in window (I wonder if I can do this 
	//later when I add the graphics to a window or go fullscreen, etc.
	swap_chain_descr.OutputWindow = hWnd;

	//if not windowed, set to false, can I update this later to switch
	//between fullscreen and windowed?
	swap_chain_descr.Windowed = true;


	D3D_FEATURE_LEVEL feature_level;

	UINT flags = D3D11_CREATE_DEVICE_SINGLETHREADED;
	#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif
	hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flags,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swap_chain_descr,
		&swap_chain_ptr,
		&device_ptr,
		&feature_level,
		&device_context_ptr);
	assert(S_OK == hr && swap_chain_ptr && device_ptr && device_context_ptr);



	
	hr = swap_chain_ptr->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),
		(void**)&framebuffer);
	assert(SUCCEEDED(hr));

	hr = device_ptr->CreateRenderTargetView(
		framebuffer, 0, &render_target_view_ptr);
	assert(SUCCEEDED(hr));
	framebuffer->Release();





	//compile shader
	 flags = D3DCOMPILE_ENABLE_STRICTNESS;
	#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3DCOMPILE_DEBUG; // add more debug output
	#endif
	ID3DBlob* vs_blob_ptr = NULL, * ps_blob_ptr = NULL, * error_blob = NULL;


	// COMPILE VERTEX SHADER
	HRESULT hr = D3DCompileFromFile(
		L"Default.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"vs_main",
		"vs_5_0",
		flags,
		0,
		&vs_blob_ptr,
		&error_blob);
	if (FAILED(hr)) {
		if (error_blob) {
			OutputDebugStringA((char*)error_blob->GetBufferPointer());
			error_blob->Release();
		}
		if (vs_blob_ptr) { vs_blob_ptr->Release(); }
		assert(false);
	}

	// COMPILE PIXEL SHADER
	hr = D3DCompileFromFile(
		L"Default.hlsl",
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"ps_main",
		"ps_5_0",
		flags,
		0,
		&ps_blob_ptr,
		&error_blob);
	if (FAILED(hr)) {
		if (error_blob) {
			OutputDebugStringA((char*)error_blob->GetBufferPointer());
			error_blob->Release();
		}
		if (ps_blob_ptr) { ps_blob_ptr->Release(); }
		assert(false);
	}




	hr = device_ptr->CreateVertexShader(
		vs_blob_ptr->GetBufferPointer(),
		vs_blob_ptr->GetBufferSize(),
		NULL,
		&vertex_shader_ptr);
	assert(SUCCEEDED(hr));

	hr = device_ptr->CreatePixelShader(
		ps_blob_ptr->GetBufferPointer(),
		ps_blob_ptr->GetBufferSize(),
		NULL,
		&pixel_shader_ptr);
	assert(SUCCEEDED(hr));




	input_layout_ptr = NULL;
	D3D11_INPUT_ELEMENT_DESC inputElementDesc[]{
	  { "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	  /*
	  { "COL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  { "NOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  { "TEX", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	  */
	};
	hr = device_ptr->CreateInputLayout(
		inputElementDesc,
		ARRAYSIZE(inputElementDesc),
		vs_blob_ptr->GetBufferPointer(),
		vs_blob_ptr->GetBufferSize(),
		&input_layout_ptr);
	assert(SUCCEEDED(hr));


	vertex_data_array = new float[9]{
	0.0f,  0.5f,  0.0f, // point at top
	0.5f, -0.5f,  0.0f, // point at bottom-right
	-0.5f, -0.5f,  0.0f, // point at bottom-left
	};



	
	/*** load mesh data into vertex buffer **/
	D3D11_BUFFER_DESC vertex_buff_descr = {};
	vertex_buff_descr.ByteWidth = sizeof(vertex_data_array);
	vertex_buff_descr.Usage = D3D11_USAGE_DEFAULT;
	vertex_buff_descr.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sr_data = { 0 };
	sr_data.pSysMem = vertex_data_array;

	//create a test buffer and test that the input parameters are correct
	hr = device_ptr->CreateBuffer(
		&vertex_buff_descr,
		&sr_data,
		NULL);
	assert(hr == S_FALSE);

	hr = device_ptr->CreateBuffer(
		&vertex_buff_descr,
		&sr_data,
		&vertex_buffer_ptr);
	assert(SUCCEEDED(hr));
	


}

DirectX11::~DirectX11() {

}


bool DirectX11::ReadMessage(Message message) {
	switch (message.Code) {
	//case ADD_WINDOW_HANDLE:

	default:
		return Entity::ReadMessage(message);
	}
	return false;
}


void DirectX11::Redraw() {
	device_context_ptr->ClearRenderTargetView( render_target_view_ptr, background_color);

	//**set all of this to only happen when the window is resized
	RECT winRect;
	GetClientRect(hWnd, &winRect);
	D3D11_VIEWPORT viewport = {
	  0.0f,
	  0.0f,
	  (FLOAT)(winRect.right - winRect.left),
	  (FLOAT)(winRect.bottom - winRect.top),
	  0.0f,
	  1.0f };
	device_context_ptr->RSSetViewports(1, &viewport);


	device_context_ptr->OMSetRenderTargets(1, &render_target_view_ptr, NULL);

	device_context_ptr->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	device_context_ptr->IASetInputLayout(input_layout_ptr);
	device_context_ptr->IASetVertexBuffers(
		0,
		1,
		&vertex_buffer_ptr,
		&vertex_stride,
		&vertex_offset);


	device_context_ptr->VSSetShader(vertex_shader_ptr, NULL, 0);
	device_context_ptr->PSSetShader(pixel_shader_ptr, NULL, 0);


	device_context_ptr->Draw(3, 0);


	swap_chain_ptr->Present(1, 0);

}
