//from GCC3 book

#include "KhaosEngine/stdafx.h"

#define SLEEPTIME 0

static int s_milliseconds;
static __int64 s_ticks;

static int s_milliseconds0;
static __int64 s_ticks0;

//fabs
#if 0
#pragma message("Disabled local fabs() to prevent collision w/ VS2K3")
float inline fabs(float a)
{
  if(a < 0.0f)
    return -a;
  else
    return a;
}
#endif

//StartTimingCPU
//call this to start timing the CPU. It takes the CPU tick count and the current time and stores it.
//then while you do other things, and the OS task switches, the counters continue to count,
//and when you call UpdateCPUTime, the measured spped is accurate
int StartTimingCPU()
{
  //detect ability to get info
  __asm
  {
    pushfd; //push extented flags
    pop eax;  //store eflags into eax
    mov ebx, eax; //save ebx for testing later
    xor eax, (1<<21) ;  //switch bit 21
    push eax; //push eflags
    popfd;  //pop them again
    pushfd; //push extended flags
    pop eax;  //store eflags into eax
    cmp eax, ebx; //see if bit 21 has changed
    jz no_cpuid;  //make sure its now on
  }

  //make ourselves high priority just for the time between when we measure the time and the CPU ticks
  DWORD priority_class = GetPriorityClass(GetCurrentProcess());
  int thread_priority = GetThreadPriority(GetCurrentThread());
  SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
  SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

  //start timing
  s_milliseconds0 = (int)timeGetTime();

  __asm
  {
    lea   ecx, s_ticks0;  //get the offset
    mov   dword ptr [ecx], 0; //zero the mem
    mov dword ptr [ecx+4], 0; 
    rdtsc ; //read time stamp counter
    mov [ecx], eax; //store the negative
    mov [ecx+4], edx; //in the variable
  }

  //restore thread priority
  SetThreadPriority(GetCurrentThread(), thread_priority);
  SetPriorityClass(GetCurrentProcess(), priority_class);

  return 0;

no_cpuid:
  return -1;
}

//UpdateCPUTime
//stops timing the CPU by adjusting the timers to account for the amount of elapsed time and 
//the number of CPU cycles during the timing period
void UpdateCPUTime()
{
  DWORD priority_class = GetPriorityClass(GetCurrentProcess());
  int thread_priority = GetThreadPriority(GetCurrentThread());
}