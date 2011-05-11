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

  //perfrom app init
  if(!g_app->InitInstance(instance, cmd_line))
  {
    return FALSE;
  }
  return g_app->GetExitCode();
}