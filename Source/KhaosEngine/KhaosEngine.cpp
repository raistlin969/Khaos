#include "KhaosEngine/stdafx.h"
#include "KhaosEngine/KhaosApp.h"

INT WINAPI KhaosEngine(HINSTANCE instance, HINSTANCE prev, LPWSTR cmd_line, int cmd_show)
{
  //setup checks for memory leaks
  int tmp_dbg_flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

  //perfrom leak check just before exit
  tmp_dbg_flag |= _CRTDBG_LEAK_CHECK_DF;
  _CrtSetDbgFlag(tmp_dbg_flag);

  //set DX callbacks
  DXUTSetCallbackD3D11DeviceCreated(KhaosApp::OnCreateDevice);
  DXUTSetCallbackD3D11DeviceAcceptable(KhaosApp::IsDeviceAcceptable);
  DXUTSetCallbackD3D11SwapChainResized(KhaosApp::SwapChainResized);
  DXUTSetCallbackD3D11FrameRender(KhaosApp::FrameRender);
  DXUTSetCallbackD3D11SwapChainReleasing(KhaosApp::SwapChainRelease);
  DXUTSetCallbackD3D11DeviceDestroyed(KhaosApp::OnDestroyDevice);
  
  DXUTSetCallbackFrameMove(KhaosApp::OnUpdateGame);
  DXUTSetCallbackMsgProc(KhaosApp::MsgProc);
  DXUTSetCallbackDeviceChanging(KhaosApp::ModifyDeviceSettings);

  DXUTSetCursorSettings(true, true);

  //perfrom app init
  if(!g_app->InitInstance(instance, cmd_line))
  {
    return FALSE;
  }

  DXUTMainLoop();
  DXUTShutdown();

  _CrtDumpMemoryLeaks();
  return g_app->GetExitCode();
}