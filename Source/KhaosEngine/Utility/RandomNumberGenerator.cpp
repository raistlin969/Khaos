#include "KhaosEngine\stdafx.h"
#include "Utility\RandomNumberGenerator.h"
#include <time.h>

RandomNumberGenerator::RandomNumberGenerator()
{
	_rseed = 1;
	//safe0 start
	_rseed_sp = 0;
	_mti = MATH_N + 1;
	//safe0 end
}

//return a number from 0 to n (excluding n)
unsigned int RandomNumberGenerator::Random(unsigned int n)
{
	unsigned long y;
	static unsigned long mag01[2] = {0x0, MATH_MATRIX_A};
	if(n == 0)
		return 0;

	//mag01[x] = x * MATRIX_A for x=0,1
	if(_mti >= MATH_N)	//generate N words at one time
	{
		int kk;
		if(_mti == MATH_N + 1)	//if sgenrand() has not been called
			SetRandomSeed(4357);	//a default initial seed is used

		for(kk = 0; kk < MATH_N - MATH_M; ++kk)
		{
			y = (_mt[kk]&MATH_UPPER_MASK) | (_mt[kk+1]&MATH_LOWER_MASK);
			_mt[kk] =_mt[kk+MATH_M] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		for(; kk < MATH_N - 1; ++kk)
		{
			y = (_mt[kk]&MATH_UPPER_MASK) | (_mt[kk+1]&MATH_LOWER_MASK);
			_mt[kk] = _mt[kk+(MATH_M - MATH_N)] ^ (y >> 1) ^ mag01[y & 0x1];
		}
		y = (_mt[MATH_N-1]&MATH_UPPER_MASK) | (_mt[0]&MATH_LOWER_MASK);
		_mt[MATH_N-1] = _mt[MATH_M-1] ^ (y >> 1) ^ mag01[y & 0x1];
		_mti = 0;
	}

	y = _mt[_mti++];
	y ^= MATH_TEMPERING_SHIFT_U(y);
	y ^= MATH_TEMPERING_SHIFT_S(y) & MATH_TEMPERING_MASK_B;
	y ^= MATH_TEMPERING_SHIFT_T(y) & MATH_TEMPERING_MASK_C;
	y ^= MATH_TEMPERING_SHIFT_L(y);

	return (y%n);
}

float RandomNumberGenerator::Random()
{
	//return random float between 0.0 - 1.0
	unsigned int r = (float)Random(0xffffffff);
	float divisor = (float)0xffffffff;
	return (r / divisor);
}

void RandomNumberGenerator::SetRandomSeed(unsigned int n)
{
	//setting intitial seeds to _mt[N] using the generator Line 25 of Table 1
	//in [KNUTH - Art of Computer Programming Vol. 2 (2nd edition) pg 102
	_mt[0] = n & 0xffffffff;
	for(_mti = 1; _mti < MATH_N; ++_mti)
		_mt[_mti] = (69069 * _mt[_mti-1]) & 0xffffffff;
	_rseed = n;
}

unsigned int RandomNumberGenerator::GetRandomSeed()
{
	return _rseed;
}

void RandomNumberGenerator::Randomize()
{
	SetRandomSeed((unsigned int)time(NULL));
}