#pragma once

template<typename T>
class ARRAY_t
{
public:
    ARRAY_t()
    {
        _size = 0;
        _ptr = 0;
        _maxSize = 32;
        _isAlloc = 0;
        TryAlloc();
    }

    ARRAY_t(std::initializer_list<T> vals)
    {
        _size = 0;
        _ptr = 0;
        _maxSize = vals.size();
        _isAlloc = 0;
        TryAlloc();
        for (auto& v : vals)
        {
            Push(v);
        }
    }

    T* begin() const
    {
        return _data;
    }
    T* end() const
    {
        return &_data[_ptr];
    }
    constexpr int Count() const
    {
        return _ptr;
    }

    void TryReAlloc(int newSize) {


        void* mBlock = (T*)calloc(this->_maxSize, sizeof(T));
        memcpy(mBlock, _data, sizeof(T));
        _maxSize = newSize;

        _data = (T*)calloc(this->_maxSize, sizeof(T));
        memcpy(_data, mBlock, sizeof(T));

    }
    void TryAlloc()
    {
        if (!_isAlloc) {
            this->_data = (T*)calloc(this->_maxSize, sizeof(T));
            _isAlloc = 1;
        }
        else {
            TryReAlloc(this->_maxSize * (this->_maxSize / 2));
        }
    }
    void TryDealloc()
    {
        if (_isAlloc) {
            free(this->_data);
            _isAlloc = 0;
        }
    }

    void Push(const T& t)
    {
        _data[_ptr++] = t;
    }
    T& Pop()
    {
        return this->_data[--_ptr];
    }

    T& Get(int index)
    {
        if (index >= _maxSize)
        {
            TryReAlloc(this->_maxSize * (this->_maxSize / 2));
        }
        _ptr = index > _ptr ? index : _ptr;
        return this->_data[index];
    }

    T& operator[](int index)
    {
        return this->Get(index);
    }
private:
    T* _data = (T*)calloc(32,sizeof(T));
    int _ptr;
    int _isAlloc;
    int _size;
    int _maxSize;
};
template<typename T> using Array = ARRAY_t<T>;