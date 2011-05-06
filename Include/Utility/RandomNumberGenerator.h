#pragma once

//Random number generator.  Code is from Game Coding Complete book

#define MATH_N 624
#define MATH_M 397
#define MATH_MATRIX_A 0x9908b0df //constant vector a
#define MATH_UPPER_MASK 0x80000000
#define MATH_LOWER_MASK 0x7fffffff

//tempering parameters
#define MATH_TEMPERING_MASK_B 0x9d2c5680
#define MATH_TEMPERING_MASK_C 0xefc60000
#define MATH_TEMPERING_SHIFT_U(y) (y >> 11)
#define MATH_TEMPERING_SHIFT_S(y) (y << 7)
#define MATH_TEMPERING_SHIFT_T(y) (y << 15)
#define MATH_TEMPERING_SHIFT_L(y) (y >> 18)

class RandomNumberGenerator
{
	unsigned int _rseed;
	unsigned int _rseed_sp;
	unsigned long _mt[MATH_N]; //array for state vector
	int _mti;	//mti==N+1 means mt[N] is not initialized

public:
	RandomNumberGenerator();
	unsigned int Random(unsigned int n);
	float Random();
	void SetRandomSeed(unsigned int n);
	unsigned int GetRandomSeed();
	void Randomize();
};