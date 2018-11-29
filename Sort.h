#pragma once
namespace vptsl
{
	template <typename T>
	class sort
	{
	protected:
		T* _pStart = nullptr;
		T* _pEnd = nullptr;
		size_t _size = 0;
	public:

		sort(void) = default;
		explicit sort(T* pStart, size_t size) :
			_pStart(pStart), _size(size)
		{
			this->_pEnd = &this->_pStart[this->_size - 1];
		}
		explicit sort(T* pStart, T* pEnd) :
			_pStart(pStart), _pEnd(pEnd)
		{
			if (this->_pStart > this->_pEnd)
			{
				T* tmp = this->_pStart;
				this->_pStart = this->_pEnd;
				this->_pEnd = tmp;
			}
			this->_size = this->_pEnd - this->_pStart;
		}

		size_t size(void) const throw()
		{
			return this->_size;
		}
		T* start(void)
		{
			return this->_pStart;
		}
		const T* c_start(void) const
		{
			return this->_pStart;

		}
		T* end(void)
		{
			return this->_pEnd;
		}
		const T* c_cend(void) const
		{
			return this->_pEnd;
		}

		T& at(size_t index)
		{
			return this->_pStart[index];
		}
		inline const T& at(size_t index) const
		{
			return this->_pStart[index];
		}

		T& operator[](size_t index)
		{
			return this->_pStart[index];
		}
		const T& operator [](size_t index) const
		{
			return this->_pStart[index];
		}

		virtual void start_sort(bool(*predicate)(T& firstVal, T& secondVal)) = 0;

		virtual void start_sort(void) = 0;

		~sort(void) = default;
	};
}