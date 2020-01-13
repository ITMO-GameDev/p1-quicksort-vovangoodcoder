#ifndef H_ARRAY
#define H_ARRAY

#include <iostream>
#include <iterator>

const int INCREMENT_STEP = 2;

template<typename T>
class Array
{
private:
    T* storage;
    int capacity;
    int size;

public:
    class Iterator : public std::iterator<std::forward_iterator_tag, T>
    {
    private:
        Array<T>& arr;
        int it_pos;
    public:
        Iterator(Array<T>& arr) : arr(arr), it_pos(0) {}

        const T& get() const
        {
            return this->arr[this->it_pos];
        }

        void set(const T& value)
        {
            this->arr[this->it_pos] = value;
        }

        void insert(const T& value)
        {
            this->arr.insert(this->it_pos, value);
        }

        void remove()
        {
            this->arr.remove(this->it_pos);
        }

        void next()
        {
            this->it_pos++;
        }

        void prev()
        {
            this->it_pos--;
        }

        void toIndex(int index)
        {
            this->it_pos = index;
        }

        bool hasNext() const
        {
            return (this->it_pos < this->arr.size - 1);
        }

        bool hasPrev() const
        {
            return (this->it_pos > 0);
        }
    };

    Array(int capacity = 16) :
        capacity(capacity),
        storage(nullptr),
        size(0)
    {
        if (this->capacity != 0)
            this->storage = new T[capacity];
        else
            this->storage = nullptr;
    }

    ~Array() {
        delete[] this->storage;
    }

    Array(const Array& other)
    {
        this->storage = new T[other.capacity];
        std::copy(other.storage,
            other.storage + other.capacity,
            this->storage);

        capacity = other.capacity;
        size = other.size;
    }

    Array& operator =(const Array& other)
    {
        if (&other == this)
            return *this;

        delete[] this->storage;
        this->storage = new T[other.capacity];

        std::copy(other.storage,
            other.storage + other.capacity,
            this->storage);

        capacity = other.capacity;
        size = other.size;

        return *this;
    }

    Array(Array&& other)
    {
        this->storage = new T[other.capacity];
        std::move(other.storage,
            other.storage + other.capacity,
            this->storage);

        capacity = other.capacity;
        size = other.size;

        other.storage = nullptr;
        other.size = 0;
    }


    Array& operator=(Array&& other)
    {
        if (this != &other)
        {
            delete[] this->storage;
            this->storage = new T[other.capacity];

            std::move(other.storage,
                other.storage + other.capacity,
                this->storage);

            capacity = other._capacity;
            size = other.size;

            other.storage = nullptr;
            other.size = 0;
        }
        return *this;
    }

    void insert(const T& value)
    {
        this->insert(this->getSize(), value);
    }

    void insert(int index, const T& value)
    {
        if (this->capacity == this->getSize())
            this->expandStorage();

        for (int i = this->getSize() - 1; i >= index; i--)
            this->storage[i + 1] = std::move(this->storage[i]);

        this->storage[index] = std::move(value);

        this->size++;
    }

    void remove(int index)
    {
        for (int i = index; i < this->getSize(); i++)
            this->storage[i] = std::move(this->storage[i + 1]);

        this->size--;
    }

    void expandStorage()
    {
        T* new_chunk_ptr;
        if (this->getCapacity() == 0)
            this->capacity++;
        this->capacity = this->capacity * INCREMENT_STEP;

        new_chunk_ptr = new T[this->capacity];

        for (int i = 0; i != this->size; i++)
            new_chunk_ptr[i] = std::move(this->storage[i]);

        this->storage = new_chunk_ptr;
    }

    int const getCapacity()
    {
        return capacity;
    }

    T& operator[](int index)
    {
        return this->storage[index];
    }

    const T& operator[](int index) const
    {
        return std::move(this->storage[index]);
    }

    int const getSize()
    {
        return this->size;
    }

    const Iterator iterator()
    {
        Iterator* it = new Iterator(*this);
        it->toIndex(0);
        return *it;
    }
};

#endif
