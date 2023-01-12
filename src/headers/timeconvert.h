#ifndef TIMECONVERT_H
#define TIMECONVERT_H
#include "qmath.h"
#include "rizTypes.h"
using namespace rizTypes;

float riz2real(float realBpm, float startFloor, float startTime, float rizTime) 
{
	return startFloor + (60 / realBpm) * (rizTime - startTime);
}

float real2riz(float realBpm, float startFloor, float startTime, float realTime)
{
	return (realTime - startFloor) / (60 / realBpm) + startTime;
}

float real2rizWrapped(KeyPoint shift, float bpm, float time)
{
	return real2riz(shift.value * bpm, shift.floorPosition, shift.time, time);
}

float riz2realWrapped(KeyPoint shift, float bpm, float time)
{
	return riz2real(shift.value * bpm, shift.floorPosition, shift.time, time);
}
#endif