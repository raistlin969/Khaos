#pragma once
#include "stdafx.h"
#include "Utility/Optional.h"

class KhaosApp
{
protected:
  HINSTANCE _hinstance;
  bool _windowed_mode;  //true if windowed, false if fullscreen
  bool _running;  //true if everything is init and game is in main loop
  bool _quit_requested; //true if app should run exit sequence
  bool _quitting; //true if exit sequence is running
  CRect _window_size; //current client window size
  CRect _desktop_size;  //desktop size
  int _color_depth; //current color depth (16 or 32)
  int _has_modal_dialog;  //determines if modal dialog is up

protected:
//  int PumpUntilMessage(UINT msg_end, WPARAM* wp, LPARAM* lp);
//  int EatSpecificMessage(UINT msg_type, Optional<LPARAM> lp, Optional<WPARAM> wp);
//  void FlashWhileMinimized();

public:
  KhaosApp();

  //virtuals
  virtual bool InitInstance(HINSTANCE hinstance, LPWSTR command_line, HWND hwnd = NULL, 
                            int screen_width = SCREEN_WIDTH, int screen_height = SCREEN_HEIGHT);

  //main loop processing
  void AbortGame() { _quitting = true; }
  int GetExitCode() { return DXUTGetExitCode(); }
  bool IsRunning() { return _running; }
  void SetQuitting(bool quitting) { _quitting = quitting; }
};


extern KhaosApp* g_app;