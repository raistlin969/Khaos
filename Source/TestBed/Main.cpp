#include <Windows.h>
#include "Utility\Optional.h"

Optional<int> Calculate()
{
	Optional<int> spline;
	spline = 10;
  spline.Clear();
	return spline;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Optional<int> answer = Calculate();
	return 0;
}