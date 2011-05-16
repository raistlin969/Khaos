#pragma once

#define ERR_INIT_NOT_ENOUGH_DISK_SPACE  1
#define ERR_INIT_CPU_TOO_SLOW           2
#define ERR_INIT_NOT_ENOUGH_PHYS_RAM    3
#define ERR_INIT_NOT_ENOUGH_VIRT_RAM    4
#define ERR_INIT_NOT_ENOUGH_CONTIG_RAM  5

#define ERR_ABORT     1
#define ERR_RETRY     2
#define ERR_IGNORE    3

class KhaosError
{
protected:
  const int _code;

public:
  KhaosError(const int code) : _code(code) {}

  int Handle()  { return _code; }

  KhaosError& operator=(KhaosError& o)
  {
    if(this != &o)
    {
      int& ref = const_cast<int&>(_code);
      ref = o._code;
    }
    return *this;
  }
};