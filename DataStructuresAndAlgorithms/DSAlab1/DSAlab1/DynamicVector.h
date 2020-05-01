#pragma once
#include <iostream>
#include <stdexcept>
template <class T>
class DynamicVector
{
private:
	T* elems;
	int size;
	int cap;
	static const int DEFAULT_CAPACITY = 10;
public:
	DynamicVector();
	DynamicVector(int capacity);
	DynamicVector(const DynamicVector& v);
	~DynamicVector();
	T* getAll();
	int get_size() const;

	T getElement(int pos) const;
	DynamicVector& operator=(const DynamicVector& v);
	template <typename U>
	friend DynamicVector<U>& operator + (const T& e, DynamicVector<T>& v);
	/*
	adds an element to the array
	*/
	void add(const T &e);
	void add_to_pos(int pos,T e);
	/*
	deletes an element from the array
	*/
	void remove(int pos);
	T& operator [] (int pos);
	DynamicVector& operator + (const T& e);
private:
	void resize(double factor = 2);
};

template<class T>
inline DynamicVector<T>::DynamicVector()
{
	cap = DEFAULT_CAPACITY;
	size = 0;
	elems = new T[DEFAULT_CAPACITY];
}

template<class T>
inline DynamicVector<T>::DynamicVector(int capacity)
{
	cap = capacity;
	size = 0;
	elems = new T[cap];
}

template<class T>
DynamicVector<T>::~DynamicVector()
{
	delete[] elems;
}

template<class T>
void DynamicVector<T>::add_to_pos(int pos,T e)
{
	if (pos >= 0 && pos <= this->size)
	{
		if(this->size==this->cap)
			resize();
		this->size++;
		for (int i = this->size - 1; i > pos; i--)
			this->elems[i] = this->elems[i - 1];
		this->elems[pos] = e;
	}
	else
		throw std::invalid_argument("Invalid position!");
}

template <class T>
DynamicVector<T>::DynamicVector(const DynamicVector& v)
{
	this->size = v.size;
	this->cap = v.cap;
	this->elems = new T[this->cap];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];
}

template <class T>
void DynamicVector<T>::resize(double factor)
{
	this->cap *= factor;
	T* els = new T[this->cap];
	for (int i = 0; i < this->size; i++)
		els[i] = this->elems[i];

	delete[] this->elems;
	this->elems = els;
}

template <class T>
void DynamicVector<T>::add(const T &e)
{
	if (this->size == this->cap)
		this->resize(2);
	this->elems[this->size] = e;
	this->size++;

	
}

template<class T>
DynamicVector<T>& DynamicVector<T>::operator + (const T& e)
{
	this->add(e);
	return *this;
}

template <class T>
DynamicVector<T>& DynamicVector<T>::operator=(const DynamicVector& v)
{
	if (this == &v)
		return *this;

	this->size = v.size;
	this->cap = v.cap;

	delete[] this->elems;
	this->elems = new T[this->cap];
	for (int i = 0; i < this->size; i++)
		this->elems[i] = v.elems[i];

	return *this;
}
template<class T>
T* DynamicVector<T>::getAll()
{
	return elems;
}

template <class T>
int DynamicVector<T>::get_size() const
{
	return size;
}

template<class T>
void DynamicVector<T>::remove(int pos)
{
	if (pos < 0 || pos >= this->size)
		return;

	T* els = new T[this->cap];
	for (int i = 0; i < pos; i++)
		els[i] = this->elems[i];

	for (int i = pos; i < this->size; i++)
		els[i] = this->elems[i + 1];

	delete[] this->elems;
	this->elems = els;
	this->size--;
}

template <class T>
T DynamicVector<T>::getElement(int pos) const
{
	if (pos<0 || pos > this->size)
		throw std::invalid_argument("Invalid position");
	return this->elems[pos];
}
template<class T>
T& DynamicVector<T>::operator [] (int pos)
{
	return elems[pos];
}
template<class T>
DynamicVector<T>& operator + (const T& e, DynamicVector<T>& v)
{
	v.add(e);
	return v;
}


