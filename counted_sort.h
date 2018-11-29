#pragma once
#include "Sort.h"
namespace vptsl
{
template <typename T>
class counted_sort :
	public sort<T>
{
protected:
	unsigned long countSwap = 0ul;
	unsigned long countIterations = 0ul;
public:
	counted_sort() :
		sort()
	{}
	counted_sort(T* pStart, size_t size) :
		sort(pStart, size)
	{}
	counted_sort(T* pStart, T* pEnd) :
		sort(pStart, pEnd)
	{}
	~counted_sort(void) = default;

	unsigned long count_swap(void) const throw()
	{
		return this->countSwap;
	}
	unsigned long count_iterations(void) const throw()
	{
		return this->countIterations;
	}
};
}
