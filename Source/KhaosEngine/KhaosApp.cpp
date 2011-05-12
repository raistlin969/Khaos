#include "KhaosEngine/stdafx.h"
#include "KhaosEngine/KhaosApp.h"

KhaosApp* g_app = NULL;

KhaosApp::KhaosApp()
{
}

bool KhaosApp::InitInstance(HINSTANCE hinstance, LPWSTR command_line, HWND hwnd, int screen_width, int screen_height)
{
  return true;
}

//directx dxut callbacks
HRESULT CALLBACK KhaosApp::OnCreateDevice( ID3D11Device* pd3dDevice, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
  return S_OK;
}

bool CALLBACK KhaosApp::IsDeviceAcceptable( const CD3D11EnumAdapterInfo *AdapterInfo, UINT Output, const CD3D11EnumDeviceInfo *DeviceInfo, DXGI_FORMAT BackBufferFormat, bool bWindowed, void* pUserContext )
{
  return true;
}

HRESULT CALLBACK KhaosApp::SwapChainResized( ID3D11Device* pd3dDevice, IDXGISwapChain *pSwapChain, const DXGI_SURFACE_DESC* pBackBufferSurfaceDesc, void* pUserContext )
{
  return S_OK;
}

void CALLBACK KhaosApp::FrameRender( ID3D11Device* pd3dDevice, ID3D11DeviceContext* pd3dImmediateContext, double fTime, float fElapsedTime, void* pUserContext )
{
}

void CALLBACK KhaosApp::SwapChainRelease( void* pUserContext )
{
}

void CALLBACK KhaosApp::OnDestroyDevice( void* pUserContext )
{
}

void CALLBACK KhaosApp::OnUpdateGame(double fTime, float fElapsedTime, void* pUserContext)
{
}

bool CALLBACK KhaosApp::ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
  return true;
}

LRESULT CALLBACK KhaosApp::MsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam, bool* no_further_processing, void* user_context)
{
  return 0;
}