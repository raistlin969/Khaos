#include "KhaosEngine\stdafx.h"
#include "MainLoop/Initialization.h"
#include "Utility/KhaosError.h"
#include <direct.h>

bool IsOnlyInstance(LPCTSTR title)
{
  //find the window. if active, set and return false
  //only one game instance may have this mutex at a time

  HANDLE handle = CreateMutex(NULL, TRUE, title);
  if(GetLastError() != ERROR_SUCCESS)
  {
    HWND hwnd = FindWindow(title, NULL);
    if(hwnd)
    {
      //an instance is already running
      ShowWindow(hwnd, SW_SHOWNORMAL);
      SetFocus(hwnd);
      SetForegroundWindow(hwnd);
      SetActiveWindow(hwnd);
      return false;
    }
  }
  return true;
}

void CheckHardDisk(const DWORDLONG space_needed)
{
  //check for enough free space on currect disk
  const int drive = _getdrive();
  struct _diskfree_t diskfree;

  _getdiskfree(drive, &diskfree);
  unsigned __int64 const need_clusters = space_needed / (diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
  if(diskfree.avail_clusters < need_clusters)
  {
    //if you get here you do not have enough disk space
    throw KhaosError(ERR_INIT_NOT_ENOUGH_DISK_SPACE);
  }
}

void CheckMemory(const DWORDLONG physical_ram_needed, const DWORDLONG virtual_ram_needed)
{
  MEMORYSTATUSEX status;
  status.dwLength = sizeof(MEMORYSTATUSEX);
  GlobalMemoryStatusEx(&status);
  if(status.ullTotalPhys < physical_ram_needed)
  {
    //not enough
    throw KhaosError(ERR_INIT_NOT_ENOUGH_PHYS_RAM);
  }

  //check free mem
  if(status.ullAvailVirtual < virtual_ram_needed)
  {
    throw KhaosError(ERR_INIT_NOT_ENOUGH_VIRT_RAM);
  }

  char* buff = KHAOS_NEW char[virtual_ram_needed];
  if(buff)
    delete[] buff;
  else
    throw KhaosError(ERR_INIT_NOT_ENOUGH_CONTIG_RAM);
}