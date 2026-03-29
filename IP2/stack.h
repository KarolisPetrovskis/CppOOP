#pragma once

#include <string>
#include <stdexcept>

/**
 * @namespace CustomContainer
 * @brief Custom namespace for the Stack ADT implementation.
 */
namespace CustomContainer
{
    /**
     * @class StackUnderflowException
     * @brief Thrown when attempting to pop more elements than available.
     */
    class StackUnderflowException : public std::runtime_error
    {
    public:
        /**
         * @brief Constructs the exception with a specific message.
         * @param msg The error message string.
         */
        explicit StackUnderflowException(const std::string &msg) : std::runtime_error(msg) {}
    };

    /**
     * @class Stack
     * @tparam T Type of elements stored in the stack.
     * @brief A Last-In-First-Out container using the Pimpl Idiom.
     */
    template <typename T>
    class Stack
    {
    private:
        /**
         * @class Inner
         * @brief The actual implementation of the Stack, hidden from users of the Stack class.
         */
        class Inner;
        /** @brief Pointer to the private implementation. */
        Inner *pimpl;

    public:
        /**
         * @brief Default constructor. Initializes an empty stack with default capacity.
         */
        Stack();

        /**
         * @brief Copy constructor. Performs a deep copy of the @p other stack.
         * @param other The stack to copy from.
         */
        Stack(const Stack &other);

        /**
         * @brief Assignment operator. Performs a deep copy after cleaning existing resources.
         * @param other The stack to assign from.
         * @return Reference to this stack.
         */
        Stack &operator=(const Stack &other);

        /**
         * @brief Destructor. Frees the dynamically allocated implementation object.
         */
        ~Stack();

        /**
         * @brief Adds a new value to the top of the stack.
         * @param value The element to insert.
         */
        void push(const T &value);

        /**
         * @brief Removes a specified number of elements from the top.
         * @param count Number of elements to remove.
         * @throw StackUnderflowException if @p count is greater than current size.
         */
        void pop(int count = 1);

        /**
         * @brief Replaces the current top element with a new value.
         * @param newValue The value to write to the top position.
         * @throw std::out_of_range if the stack is empty.
         */
        void updateTop(const T &newValue);

        /**
         * @brief Removes all elements from the stack, resetting it to an empty state.
         */
        void clear();

        /**
         * @brief Searches for a value in the stack.
         * @param value The element to search for.
         * @return The index of the element if found, otherwise -1.
         */
        int search(const T &value) const;

        /**
         * @brief Retrieves the top element without removing it.
         * @return A const reference to the top element.
         * @throw std::out_of_range if the stack is empty.
         */
        const T &peek() const;

        /**
         * @brief Returns the number of elements currently in the stack.
         * @return The current size as an integer.
         */
        int size() const;

        /**
         * @brief Alias for push().
         */
        Stack &operator+=(const T &value);

        /**
         * @brief Alias for pop().
         */
        Stack &operator-=(int count);

        /**
         * @brief Alias for updateTop().
         */
        Stack &operator*=(const T &newValue);

        /**
         * @brief Alias for clear().
         */
        void operator!();

        /**
         * @brief Alias for search().
         * @param value The element to locate within the stack.
         * @return The index of the element if found, otherwise -1.
         */
        int operator[](const T &value) const;

        /**
         * @brief Checks if two stacks contain the same elements in the same order.
         * @param otherStack The stack to compare against this instance.
         * @return True if both stacks have identical size and elements.
         */
        bool operator==(const Stack &otherStack) const;

        /**
         * @brief Checks if two stacks are not identical.
         * @param otherStack The stack to compare against this instance.
         * @return True if sizes or elements differ.
         */
        bool operator!=(const Stack &otherStack) const;

        /**
         * @brief Compares two stacks lexicographically.
         * @param otherStack The stack to compare against this instance.
         * @return True if this stack is lexicographically less than @p otherStack.
         */
        bool operator<(const Stack &otherStack) const;

        /**
         * @brief Checks if this stack is less than or equal to @p otherStack.
         * @param otherStack The stack to compare against this instance.
         * @return True if this stack is less than or equal to @p otherStack.
         */
        bool operator<=(const Stack &otherStack) const;

        /**
         * @brief Checks if this stack is greater than @p otherStack.
         * @param otherStack The stack to compare against this instance.
         * @return True if this stack is greater than @p otherStack.
         */
        bool operator>(const Stack &otherStack) const;

        /**
         * @brief Checks if this stack is greater than or equal to @p otherStack.
         * @param otherStack The stack to compare against this instance.
         * @return True if this stack is greater than or equal to @p otherStack.
         */
        bool operator>=(const Stack &otherStack) const;

        /**
         * @brief Returns a summary string of the stack state.
         * @return String containing current size, capacity and elements first to last.
         */
        std::string toString() const;
    };
}