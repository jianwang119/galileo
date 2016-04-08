#ifndef _DYNAMIC_ARRAY_H
#define _DYNAMIC_ARRAY_H

#include "global_define.h"

namespace galileo
{
	template<class T>
	class c_dynamic_array
	{
	public:
		c_dynamic_array()
		{
			count = 0;
			data_size = 4;
			data = new T[data_size];
		}

		c_dynamic_array(int s)
		{
			count = 0;
			data_size = s;
			data = new T[data_size];
		}

		~c_dynamic_array()
		{
			data_size = 0;
			if (data != 0)
				delete[] data;
		}

		c_dynamic_array(const c_dynamic_array<T>& rhs)
		{
			if (data != 0)
				delete[] data;

			count = rhs.length();
			data_size = rhs.data_size;
			data = new T[data_size];

			for (int i = 0; i < rhs.length(); i++)
				data[i] = rhs[i];
		}

		c_dynamic_array<T>& operator=(const c_dynamic_array<T>& rhs)
		{
			if (&rhs == this)
				return *this;

			if (data != null)
				delete[] data;

			count = rhs.length();
			data_size = rhs.data_size;
			data = new T[data_size];

			for (int i = 0; i < rhs.length(); i++)
				data[i] = rhs[i];

			return *this;
		}

		bool append(T item)
		{
			if (count == data_size)
			{
				data_size *= 2;
				T* temp = data;
				if (!(data = new T[data_size]))
					return false;
				for (int i = 0; i < count; i++)
					data[i] = temp[i];
				delete temp;
			}

			data[count++] = item;
			return true;
		}

		bool truncate()
		{
			if (count != data_size)
			{
				T* temp = data;
				data_size = count;
				if (!(data = new T[data_size]))
					return false;
				for (int i = 0; i < count; i++)
					data[i] = temp[i];
				delete temp;
			}
		}

		void clear()
		{
			count = 0;
		}

		int length() const
		{
			return count;
		}

		bool empty() const
		{
			return length() == 0;
		}

		const T& operator[](int i) const
		{
			return data[i];
		}

		T& operator[](int i)
		{
			return data[i];
		}

	private:
		T* data;
		int data_size;
		int count;
	};
}

#endif
