#include <iostream>
#include <string.h>
#include <vector>

template <typename T, size_t S>
class Array {
public:
	T _arr[S] = { 0 };

	Array(T _val) {
		for (size_t i = 0; i < S; i++)
		{
			_arr[i] = (T)i + _val;
		}
	}

	constexpr size_t Size() const { return S; }

	T& operator[](size_t i) { return _arr[i]; }

	const T& operator[](size_t i) const { return _arr[i]; }

	bool operator==(Array& _other)
	{
		if (_other.Size() != this->Size())
			return false;
		//return _other.Size() != this->Size() ? false : memcmp(_arr, _other._arr, (S-1) * (sizeof(T)));
		
		for (size_t i = 0; i < S; i++)
			if (_other[i] != (*this)[i])
				return false;
		return true;
	}

	Array& operator=(Array& _other) {
		if (_other.Size() != this->Size())
		{
			std::cout << "\nSize mismatch!\n";
			return *this;
		}
		// try memcpy here too.
		for (size_t i = 0; i < S; i++)
			this->_arr[i] = _other._arr[i];

		return *this;
	}
	
	T* begin() {
		return &(this)->_arr[0];
	}

	T* end() {
		return &(this)->_arr[S];
	}
	
private:
	size_t _index = 0;
};

int main() {
	Array<int, 3> arr(0);
	Array<int, 3> arr2(2);
	std::vector<int> vec(10);
	
	arr = arr2;
	// comment in&&out to check changes in output
	std::cout << (arr == arr2) << "\n";

	// arr class has begin, end and Size defined so it should iterate
	// begin, end, Size


}