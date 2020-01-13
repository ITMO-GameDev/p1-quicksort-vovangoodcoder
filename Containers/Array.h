#pragma once
#include <assert.h>

using namespace std;

const int DEFAULT_CAPACITY = 8;
const int CAPACITY_MULTIPLY = 2;

template<typename T>
class Array final
{
public:
	Array();
	Array(int capacity);
	Array(const Array& Array);
	~Array();

	void insert(const T& value);
	void insert(int index, const T& value);
	void remove(int index);
	const T& operator[](int index) const;
	T& operator[](int index);
	int size() const;

	class Iterator {
	public:
		Iterator(Array<T>* a);
		const T& get() const;
		void set(const T& value);
		void insert(const T& value);
		void remove();
		void next();
		void prev();
		void toIndex(int index);
		bool hasNext() const;
		bool hasPrev() const;
	private:
		int pos;
		const Array<T>* arr;
	};

	Iterator iterator(){ return Iterator(this); }
	const Iterator iterator() const { return Iterator(this); }

private:
	T* a;
	int a_capacity;
	int real_size;

	T* getSpace(int cap);
	void freeSpace(T* arr);
	void moveAfter(T* arr1, T* arr2, int index, int size);
	void moveBefore(T* arr1, T* arr2, int index);
	void moveLeft(T* arr, int index, int size);
};

//public func
template <typename T> Array <T>::Array()
{
	a_capacity = DEFAULT_CAPACITY;
	a = getSpace(a_capacity);
	real_size = 0;
}
template <typename T> Array <T>::Array(int capacity) 
{
	assert(capacity > 0);
	a_capacity = capacity;
	a = getSpace(a_capacity);
	real_size = 0;
}
template <typename T> Array <T>::Array(const Array<T>& Arr)
{
	a_capacity = Arr.a_capacity;
	real_size = Arr.real_size;

	a = getSpace(a_capacity);
	for (int i = 0; i < real_size; i++)
		a[i] = Arr.a[i];
}
template <typename T> Array <T>::~Array() {
	freeSpace(a);
}

template <typename T> void Array <T>::insert(const T& value)
{
	if (a_capacity > real_size)
	{
		a[real_size++] = value;
	}
	else
	{
		a_capacity = a_capacity * CAPACITY_MULTIPLY;
		T* new_a = getSpace(a_capacity);
		moveBefore(a, new_a, real_size);
		a = new_a;
		a[real_size++] = value;
	}
}
template <typename T> void Array <T>::insert(int index, const T& value)
{
	assert(index >= 0 && index <= real_size);
	if (a_capacity > real_size)
	{
		moveAfter(a, a, index, real_size);
		a[index] = value;
		real_size++;
	}
	else
	{
		a_capacity = a_capacity * CAPACITY_MULTIPLY;
		T* new_a = getSpace(a_capacity);
		moveAfter(a, new_a, index, real_size);
		new_a[index] = value;
		moveBefore(a, new_a, index);
		real_size++;
	}
}
template <typename T> void Array <T>::remove(int index)
{
	assert(index >= 0 && index < real_size);
	moveLeft(a, index, real_size);
	real_size--;
}
template <typename T> const T& Array <T>::operator[](int index) const
{
	assert(index >= 0 && index < real_size);
	return a[index];
}
template <typename T> T& Array <T>::operator[](int index)
{
	assert(index >= 0 && index < real_size);
	return a[index];
}
template <typename T> int Array <T>::size() const {
	return real_size;
}

//iterator func
template <typename T> Array<T>::Iterator::Iterator(Array<T>* a)
{
	arr = a;
	pos = 0;
}
template <typename T> const T& Array<T>::Iterator::get() const
{
	return arr->a[pos];
}
template <typename T> void Array<T>::Iterator::set(const T& value)
{
	arr->a[pos] = value;
}
template <typename T> void Array<T>::Iterator::insert(const T& value)
{
	arr->insert(pos, value);
}
template <typename T> void Array<T>::Iterator::remove()
{
	arr->remove(pos);
}
template <typename T> void Array<T>::Iterator::next()
{
	pos++;
}
template <typename T> void Array<T>::Iterator::prev()
{
	pos--;
}
template <typename T> void Array<T>::Iterator::toIndex(int index)
{
	pos = index;
}
template <typename T> bool Array<T>::Iterator::hasNext() const
{
	return pos < arr->size() - 1;
}
template <typename T> bool Array<T>::Iterator::hasPrev() const
{
	return pos > 0;
}

//private func
template <typename T> T* Array <T>::getSpace(int cap) 
{
	T* arr = new T[cap];
	return arr;
}

template <typename T> void Array <T>::freeSpace(T* arr)
{
	delete []arr;
}

template <typename T> void Array <T>::moveAfter(T* arr1, T* arr2, int index, int size)
{
	for (int i = size; i >= index; i--)
		arr2[i] = std::move(arr1[i - 1]);
}
template <typename T> void Array <T>::moveBefore(T* arr1, T* arr2, int index)
{
	for (int i = 0; i < index; i++)
		arr2[i] = std::move(arr1[i]);
}
template <typename T> void Array <T>::moveLeft(T* arr, int index, int size)
{
	for (int i = index; i < size; i++)
		arr[i] = std::move(arr[i+1]);
}