#include <iostream>
#include "stack.h"

int main()
{
    try
    {
        std::cout << "--- Stack Class Demonstration ---\n";

        // 1. Default constructor
        CustomContainer::Stack<int> s1;

        // 2. push() and +=
        s1.push(10);
        s1.push(20);
        s1 += 30;

        // 3. peek()
        std::cout << "Top element (peek): " << s1.peek() << "\n";

        // 4. search() and []
        std::cout << "Index of 20: " << s1.search(20) << "\n";
        std::cout << "Index of 10 using []: " << s1[10] << "\n";

        // 5. updateTop() and *=
        s1.updateTop(35);
        s1 *= 40;
        std::cout << "Top element after updates: " << s1.peek() << "\n";

        // 6. toString()
        std::cout << s1.toString() << "\n";

        // 7. Copy constructor
        CustomContainer::Stack<int> s2(s1);

        // 8. pop() and -=
        s2.pop();
        s2 -= 1;

        // 9. Comparisons (==, !=, <, <=, >, >=)
        std::cout << "s1 == s2? " << (s1 == s2 ? "Yes" : "No") << "\n";
        std::cout << "s1 != s2? " << (s1 != s2 ? "Yes" : "No") << "\n";
        std::cout << "s1 > s2? " << (s1 > s2 ? "Yes" : "No") << "\n";
        std::cout << "s1 >= s2? " << (s1 >= s2 ? "Yes" : "No") << "\n";
        std::cout << "s2 < s1? " << (s2 < s1 ? "Yes" : "No") << "\n";
        std::cout << "s2 <= s1? " << (s2 <= s1 ? "Yes" : "No") << "\n";

        // 10. Assignment operator
        CustomContainer::Stack<int> s3;
        s3 = s1;

        // 11. Size
        std::cout << "Size of s1: " << s1.size() << "\n";

        // 12. clear() and !
        s3.clear();
        !s1;
        std::cout << "s1 after operator!: " << s1.toString() << "\n";

        std::cout << "--- End of Demonstration ---\n";
    }
    catch (...)
    {
        std::cout << "An exception occurred during the demonstration.\n";
    }
    return 0;
}