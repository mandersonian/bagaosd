/*
Original code : 
http://playground.arduino.cc/Main/RunningAverage
*/
#include "RunningUintAverage.h"
#include <stdlib.h>

RunningUintAverage::RunningUintAverage(int n)
{
	_size = n;
	_ar = (unsigned int*) malloc(_size * sizeof(unsigned int));
	clear();
}

RunningUintAverage::~RunningUintAverage()
{
	free(_ar);
}

// resets all counters
void RunningUintAverage::clear() 
{ 
	_cnt = 0;
	_idx = 0;
	_sum = 0;
	for (int i = 0; i< _size; i++) _ar[i] = 0;  // needed to keep addValue simple
}

// adds a new value to the data-set
void RunningUintAverage::addValue(unsigned int value)
{
	_sum -= _ar[_idx];
	_ar[_idx] = value;
	_sum += _ar[_idx];
	_idx++;
	if (_idx == _size) _idx = 0;  // faster than %
	if (_cnt < _size) _cnt++;
}

// returns the average of the data-set added sofar
unsigned int RunningUintAverage::getAverage()
{
	if (_cnt == 0) return 0; // NaN ?  math.h
	return (_sum / _cnt);
}

// END OF FILE