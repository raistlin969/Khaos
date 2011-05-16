#include "KhaosEngine/stdafx.h"
#include "KhaosEngine/KhaosApp.h"
#include "KhaosEngine/MainLoop/Initialization.h"
#include "KhaosEngine/Utility/KhaosError.h"

KhaosApp* g_app = NULL;

KhaosApp::KhaosApp()
{
}

HWND KhaosApp::GetHwnd()
{
  return DXUTGetHWND();
}

bool KhaosApp::InitInstance(HINSTANCE hinstance, LPWSTR command_line, HWND hwnd, int screen_width, int screen_height)
{
  //check for adequate machine resources
  bool resource_check = false;
  while(!resource_check)
  {
    try
    {
      const DWORDLONG pr = 32 * MEGABYTE;
      const DWORDLONG vr = 64 * MEGABYTE;
      CheckMemory(pr, vr);

      const DWORDLONG disk_space = 10 * MEGABYTE;
      CheckHardDisk(disk_space);

      //TODO: CPU spped test
    }
    catch(KhaosError err)
    {
      if(err.Handle() == ERROR_RETRY)
        continue;
      else if(err.Handle() == ERR_INIT_NOT_ENOUGH_VIRT_RAM)
      {
        OutputDebugString(L"WARNING: INSUFFICIENT VIRTUAL RAM REPORTED.  CONTINUING...");
      }
      else
        return false;
    }
    resource_check = true;
  }

  _hinstance = hinstance;

  //TODO: game options
  //TODO: ParseCommand line

  //TODO: Resource Cache

  //TODO: Lua State Manager

  //TODO: Event Manager

  //TODO: Lua init script

  //DXUT init
  DXUTInit(true, true, command_line, true);
  if(hwnd == NULL)
  {
    DXUTCreateWindow(GetGameTitle(), hinstance, GetIcon());
  }
  else
  {
    DXUTSetWindow(hwnd, hwnd, hwnd);
  }

  if(!GetHwnd())
  {
    return FALSE;
  }

  SetWindowText(GetHwnd(), GetGameTitle());

  //TODO: init user settable options

  //CreateDevice
  DXUTCreateDevice(D3D_FEATURE_LEVEL_11_0, true, screen_width, screen_height);

  //TODO: init game views
  //TODO: font system

  _running = true;

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