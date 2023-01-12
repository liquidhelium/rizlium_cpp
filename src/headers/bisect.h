#ifndef BISECT_H
#define BISECT_H
#include <vector>
#include <functional>
using std::vector;

template <typename T>

// 带泛型的二分搜索算法, 基本结构从python标准库抄的((
int bisectByKey(vector<T> sequnce, float want, std::function<float(T)> key = [](T x) {return x;}, int lo = 0, int hi = -1)
{
	int mid = 0;
	if (hi == -1)
		hi = int(sequnce.size());
	while (lo < hi)
	{
		mid = (lo + hi) / 2;
		if (want < key(sequnce[mid]))
		{
			hi = mid;
		}
		else
		{
			lo = mid+1;
		}
	}
	return lo;
}
#endif