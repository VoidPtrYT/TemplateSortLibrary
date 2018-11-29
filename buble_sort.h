#pragma once
#include "sort.h"
#include "counted_buble_sort.h"
namespace vptsl
{
	template <typename T>
	class buble_sort :
		public sort<T>
	{
	public:
		buble_sort(void) :
			sort()
		{ }
		explicit buble_sort(T* pStart, size_t size) :
			sort<T>(pStart, size)
		{}
		explicit buble_sort(T* pStart, T* pEnd) :
			sort<T>(pStart, pEnd)
		{}

		void start_sort(bool(*predicate)(T& firstVal, T& secondVal)) override
		{
			for (size_t i = 0; i < this->_size; ++i)
			{
				for (size_t j = 0; j < this->_size - i - 1; ++j)
				{
					if (predicate(this->_pStart[j], this->_pStart[j + 1]))
					{
						T tmp = this->_pStart[j];
						this->_pStart[j] = this->_pStart[j + 1];
						this->_pStart[j + 1] = tmp;
					}
				}
			}
		}

		void start_sort(void) override
		{
			this->start_sort([](T& l, T& r)
			{
				return l < r;
			});
		}

		~buble_sort(void) = default;
	};
}