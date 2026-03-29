#include "stack.h"
#include <sstream>
#include <algorithm>

namespace CustomContainer
{
    template <typename T>
    class Stack<T>::Inner
    {
    public:
        T *data;
        int capacity;
        int size;

        Inner();
        Inner(const Inner &other);
        ~Inner();

        void grow();
        void push(const T &value);
        void pop(int count);
        void updateTop(const T &newValue);
        void clear();
        int search(const T &value) const;
        const T &peek() const;
        std::string toString() const;
    };

    template <typename T>
    Stack<T>::Inner::Inner() : capacity(10), size(0)
    {
        data = new T[capacity];
    }

    template <typename T>
    Stack<T>::Inner::Inner(const Inner &other) : capacity(other.capacity), size(other.size)
    {
        data = new T[capacity];
        for (int i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    template <typename T>
    Stack<T>::Inner::~Inner()
    {
        delete[] data;
    }

    template <typename T>
    void Stack<T>::Inner::grow()
    {
        int newCap = 1;
        if (capacity != 0)
        {
            newCap = capacity * 2;
        }
        capacity = newCap;
        T *newData = new T[capacity];
        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

    template <typename T>
    void Stack<T>::Inner::push(const T &value)
    {
        if (size == capacity)
        {
            grow();
        }
        data[size++] = value;
    }

    template <typename T>
    void Stack<T>::Inner::pop(int count)
    {
        if (count <= size)
        {
            size -= count;
        }
        else
        {
            throw StackUnderflowException("StackUnderflowException: Pop count exceeds size.");
        }
    }

    template <typename T>
    void Stack<T>::Inner::updateTop(const T &newValue)
    {
        if (size != 0)
        {
            data[size - 1] = newValue;
        }
        else
        {
            throw std::out_of_range("Standard Exception: Cannot edit top of an empty stack.");
        }
    }

    template <typename T>
    void Stack<T>::Inner::clear()
    {
        size = 0;
    }

    template <typename T>
    int Stack<T>::Inner::search(const T &value) const
    {
        int foundIndex = -1;
        for (int i = static_cast<int>(size) - 1; i >= 0; --i)
        {
            if (data[i] == value && foundIndex == -1)
            {
                foundIndex = i;
            }
        }
        return foundIndex;
    }

    template <typename T>
    const T &Stack<T>::Inner::peek() const
    {
        if (size != 0)
        {
            return data[size - 1];
        }
        else
        {
            throw std::out_of_range("Standard Exception: Cannot peek at an empty stack.");
        }
    }

    template <typename T>
    std::string Stack<T>::Inner::toString() const
    {
        std::ostringstream oss;
        oss << size << " " << capacity << " ";
        for (int i = 0; i < size; ++i)
        {
            oss << data[i];
            if (i != size - 1)
            {
                oss << " ";
            }
        }
        return oss.str();
    }

    template <typename T>
    Stack<T>::Stack() : pimpl(new Inner())
    {
    }

    template <typename T>
    Stack<T>::Stack(const Stack &otherStack) : pimpl(new Inner(*otherStack.pimpl))
    {
    }

    template <typename T>
    Stack<T> &Stack<T>::operator=(const Stack &otherStack)
    {
        if (this != &otherStack)
        {
            Inner *newInner = new Inner(*otherStack.pimpl);
            delete pimpl;
            pimpl = newInner;
        }
        return *this;
    }

    template <typename T>
    Stack<T>::~Stack()
    {
        delete pimpl;
    }

    template <typename T>
    void Stack<T>::push(const T &value)
    {
        pimpl->push(value);
    }

    template <typename T>
    void Stack<T>::pop(int count)
    {
        pimpl->pop(count);
    }

    template <typename T>
    void Stack<T>::updateTop(const T &newValue)
    {
        pimpl->updateTop(newValue);
    }

    template <typename T>
    void Stack<T>::clear()
    {
        pimpl->clear();
    }

    template <typename T>
    int Stack<T>::search(const T &value) const
    {
        return pimpl->search(value);
    }

    template <typename T>
    const T &Stack<T>::peek() const
    {
        return pimpl->peek();
    }

    template <typename T>
    int Stack<T>::size() const
    {
        return pimpl->size;
    }

    template <typename T>
    Stack<T> &Stack<T>::operator+=(const T &value)
    {
        push(value);
        return *this;
    }

    template <typename T>
    Stack<T> &Stack<T>::operator-=(int count)
    {
        pop(count);
        return *this;
    }

    template <typename T>
    Stack<T> &Stack<T>::operator*=(const T &newValue)
    {
        updateTop(newValue);
        return *this;
    }

    template <typename T>
    void Stack<T>::operator!()
    {
        clear();
    }

    template <typename T>
    int Stack<T>::operator[](const T &value) const
    {
        return search(value);
    }

    template <typename T>
    bool Stack<T>::operator==(const Stack &otherStack) const
    {
        bool result = true;
        if (pimpl->size != otherStack.pimpl->size)
        {
            result = false;
        }
        else
        {
            for (int i = 0; i < pimpl->size; ++i)
            {
                if (pimpl->data[i] != otherStack.pimpl->data[i])
                {
                    result = false;
                }
            }
        }
        return result;
    }

    template <typename T>
    bool Stack<T>::operator!=(const Stack &otherStack) const
    {
        return !(*this == otherStack);
    }

    template <typename T>
    bool Stack<T>::operator<(const Stack &otherStack) const
    {
        return std::lexicographical_compare(pimpl->data, pimpl->data + pimpl->size,
                                            otherStack.pimpl->data, otherStack.pimpl->data + otherStack.pimpl->size);
    }

    template <typename T>
    bool Stack<T>::operator<=(const Stack &otherStack) const
    {
        bool result = false;
        if ((*this < otherStack) || (*this == otherStack))
        {
            result = true;
        }
        return result;
    }

    template <typename T>
    bool Stack<T>::operator>(const Stack &otherStack) const
    {
        return !(*this <= otherStack);
    }

    template <typename T>
    bool Stack<T>::operator>=(const Stack &otherStack) const
    {
        return !(*this < otherStack);
    }

    template <typename T>
    std::string Stack<T>::toString() const
    {
        return pimpl->toString();
    }

    template class Stack<int>;
}