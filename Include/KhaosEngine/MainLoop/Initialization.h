#pragma once

extern void CheckHardDisk(const DWORDLONG disk_space_needed);
extern void CheckMemory(const DWORDLONG physical_ram_needed, const DWORDLONG virtual_ram_needed);
extern bool IsOnlyInstance(LPCTSTR game_title);
extern const TCHAR* GetSavedGameDirectory(HWND hwnd, const TCHAR* game_app_dir);