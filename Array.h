#ifndef _ARRAY_H
#define _ARRAY_H

template <class T>
class Array
{
	private:
		T (*front);
		T (*rear);
		int length;
		int capacity;
		int current;
	
	public:
		Array();
		Array(int capacity);
		Array(const Array& source);
		~Array();

		int Store(int index, T item);
		int Read(T& item, int index);
		T Read(int index);
		int AppendFromFront(T item);
		int AppendFromRear(T item);
		int Insert(T item, int index);
		int LinearSearchByUnique(void* key, int (*compare)(void* one, void* other));
		void LinearSearchByDuplicate(void* key, int (*resultset),int *count, int (*compare)(void*, void*));
		void InsertionSort(int length, int (*compare)(void*, void*));
		int Modify(T item, int index);
		int Delete(int index);
		int DeleteFromFront();
		int DeleteFromRear();

		void GetAt(T& item);
		T GetAt() const;
		int GetLength() const;
		int GetCapacity() const;

		int MoveFirst();
		int MoveNext();
		int MovePrevious();
		int MoveLast();

		Array& operator = (const Array& source);
		T& operator [](int index);
		T& operator ++();
		T& operator ++(int);
		T& operator --();
		T& operator --(int);
		T& operator +(int index);
		T& operator -(int index);
};

template <class T>
inline int Array<T>::GetLength() const
{
	return this->length;
}

template <class T>
inline int Array<T>::GetCapacity() const
{
	return this->capacity;
}

template <class T>
Array<T>::Array()
{
	this->front = 0;
	this->rear = 0;
	this->capacity  = 0;
	this->length = - 0;
	this->current = -1;
}

template <class T>
Array<T>::Array(int capacity)
{
	this->front = new T[capacity];
	if(this->front != 0)
	{
		this->rear = this->front + capacity;
		this->capacity = capacity;
		this->length = 0;
		this->current = -1;
	}
}

template <class T>
Array<T>::Array(const Array& source)
{
	this->front = new T[source.capacity];
	if(this->front != 0)
	{
		for(int i = 0; i < source.length; i++)
		{
			this->front[i] = source.front[i];
		}

		this->rear = this->front + source.capacity;
		this->capacity = source.capacity;
		this->length = source.length;
		this->current = source.current;
	}
}

template <class T>
Array<T>::~Array()
{
	if(this->front != 0)
	{
		delete[] this->front;
	}
}

template <class T>
Array<T>& Array<T>::operator =(const Array& source)
{
	if(this->front != 0)
	{
		delete[] tihs->front;
	}

	this->front = new T[source.capacity];
	if(this->front != 0)
	{
		for(int i=0; i<source.length; i++)
		{
			this->front[i] = source.front[i];
		}

		this->rear = this->front + source.capacity;
		this->capacity = source.capacity;
		this->length = source.length;
		this->current = source.current;
	}

	return (*this);
}

template <class T>
int Array<T>::Store(int index, T item)
{
	int result = -1;
	if(index < this->capacity)
	{
		this->front[index] = item;
		this->length++;
		result = index;
	}
	return result;
}

template <class T>
int Array<T>::Read(T& item, int index)
{
	int result = -1;
	if(index < this->capacity)
	{
		item = this->front[index];
		result = index;
	}

	return result;
}

template <class T>
T Array<T>::Read(int index)
{
	T item;
	if(index < this->capacity)
	{
		item = this->front[index];
	}

	return item;
}

template <class T>
int Array<T>::LinearSearchByUnique (void* key, int (*compare)(void* one, void* other))
{
	int result;
	int i = 0;

	while(i < this->length && comapre(this->front+i, key) != 0)
	{
		i++;
	}

	if(i < this->length)
	{
		result = i;
	}

	else
	{
		result = -1;
	}

	return result;
}

template <class T>
void Array<T>::LinearSearchByDuplicate(void* key, int (*resultset), int *count, int (*compare)(void*, void*))
{
	int i = 0;
	*count = 0;

	for(i = 0; i< this->length; i++)
	{
		if(compare(this->front + i, key) == 0)
		{
			resultset[*count] = i;
			(*count)++;
		}
	}
}

template <class T>
int Array<T>::AppendFromFront(T item)
{
	T* temp = new T[this->capacity + 1];

	if(temp != 0)
	{
		this->current = 0;
		for(int i=0; i<this->length; i++)
		{
			temp[i+1] = this->front[i];
		}

		temp(this->current) = item;

		if(this->front != 0)
		{
			delete[] this->front;
		}

		this->front = temp;
		this->rear = (this->front) + (this->capacity);
		this->capacity++;
		this->length++;
	}

	else
	{
		this->current = -1;
	}

	return this->current;
}

template <class T>
int Array<T>::AppendFromRear (T item)
{
	T* temp = new T[this->capacity + 1];
	if(temp != 0)
	{
		for(int i =0; i< this->length; i++)
		{
			temp[i] = this->front[i];
		}

		this->current = this->capacity;
		temp[this->current] = item;

		if(this->front != 0)
		{
			delete[] this->front;
		}

		this->front = temp;
		this->rear = (this->front) + (this->capacity);
		this->capacity++;
		this->length++;
	}

	else
	{
		this->current = -1;
	}

	return this->current;
}

template <class T>
int Array<T>::Modify(T item,int index)
{
	this->current = -1;
	if(index < this->capacity)
	{
		this->current = index;
		this->front[this->current] = item;
	}

	return this->current;
}

template <class T>
int Array<T>::Insert(T item, int index)
{
	this->current = -1;
	T* temp;

	temp = new T[this->capacity + 1];
	if(temp != 0)
	{
		for(int i = 0; i < index; i++)
		{
			temp[i] = this->front[i];
		}

		for(i = index+1; i<= this->length; i++)
		{
			temp[i] = this->front[i-1];
		}

		this->current = index;
		this[this->current] = item;

		if(this->front != 0)
		{
			delete[] this->front;
		}

		this->front = temp;
		this->rear = (this->front) + (this->capacity);
		this->capacity = this->capacity++;
	}

	return this->current;
}

template <class T>
int Array<T>::Delete (int index)
{
	this->current = index;
	T* temp;

	temp = new T[this->capacity - 1];
	if(temp != 0)
	{
		for(int i = 0; i < index; i++)
		{
			temp[i] = this->front[i];
		}

		for(i = index; i < this->length; i++)
		{
			temp[i] = this->front[i+1];
		}

		if(this->front != 0)
		{
			delete[] this->front;
		}

		this->front = temp;
		this->rear = (this->front) + (this->capacity -1);
		this->capacity--;
		this->length--;
		this->current = -1;
	}

	return this->current;
}

template <class T>
int Array<T>::DeleteFromFront()
{
	this->current = 0;
	T* temp;

	temp = new T[this->capacity -1];
	if(temp != 0)
	{
		for(int i=1; i< this->capacity; i++)
		{
			temp[i-1] = this->front[i];
		}

		if(this->front != 0)
		{
			delete[] this->front;
		}
		this->front = temp;
		this->rear = (this->front) + (this->capacity -1);
		this->capacity--;
		this->length--;
		this->current = -1;
	}

	return this->current;
}

template <class T>
int Array<T>::DeleteFromRear()
{
	this->current = 0;
	T* temp;

	temp = new T[this->capacity -1];
	if(temp != 0)
	{
		for(int i = 0; i< this->capacity -1; i++)
		{
			temp[i] = this->front[i];
		}

		if(this->front != 0)
		{
			delete[] this->front;
		}

		this->front = temp;
		this->rear = (this->front) + (this->capacity -1);
		this->capacity--;
		this->length--;
		this->current = -1;
	}

	return this->current;
}

template <class T>
void Array<T>::GetAt(T& item)
{
	item = this->front[this->current];
}

template <class T>
T Array<T>::GetAt() const
{
	return this->front[this->current];
}

template <class T>
int Array<T>::MoveFirst()
{
	this->current = 0;
	return this->current;
}

template <class T>
int Array<T>::MoveLast()
{
	this->current = this->capacity -1;
	return this->current;
}

template <class T>
int Array<T>::MovePrevious()
{
	this->current--;
	if(this->current < 0)
	{
		this->current = 0;
	}

	return this->current;
}

template <class T>
int Array<T>::MoveNext()
{
	this->current++;
	if(this->current >= this->capacity)
	{
		this->current = this->capacity -1;
	}

	return this->current;
}

template <class T>
void Array<T>::InsertionSort(int length, int (*compare)(void*, void*))
{
	int i,j, index;
	T* temp;
	temp = new T;
	for(i=1; i < length; i++)
	{
		*temp = this->front[i];
		j=0, index=0;
		while((j<i) && (compare(this->front + j, temp) < 0))
		{
			j++;
		}

		index = j;

		for(j=i; j>index; j--)
		{
			this->front[j] = this->front[j-1];
		}

		this->front[index] = *temp;
	}
}

template <class T>
T& Array<T>::operator [](int index)
{
	return this->front[index];
}

template <class T>
T& Array<T>::operator ++()
{
	this->current++;
	if(this->current >= this->capacity)
	{
		this->current = this->capacity-1;
	}

	return this->front + this->current;
}

template <class T>
T& Array<T>::operator ++(int)
{
	this->current++;
	if(this->current >= this->capacity)
	{
		this->current = this->capacity - 1;
	}

	return this->front + (this->current -1);
}


#endif