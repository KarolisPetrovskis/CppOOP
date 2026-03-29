#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "stack.h"

// Global tracking for the summary report
std::vector<int> failedTests;
int testCounter = 0;
int passCounter = 0;

// Helper to convert bool to string
std::string boolToStr(bool b) { return b ? "true" : "false"; }

// Diagnostic logger
void logDiagnostic(std::ostream &os, std::ofstream &fs, const std::string &name, const std::string &exp, const std::string &act)
{
    testCounter++;
    bool passed = (exp == act);
    if (passed)
        passCounter++;
    else
        failedTests.push_back(testCounter);

    std::string status = passed ? " [PASSED]" : " [FAILED]";
    std::string msg = "TEST #" + std::to_string(testCounter) + ": " + name + status +
                      "\n  -> Expected: " + exp +
                      "\n  -> Actual:   " + act + "\n";

    os << msg << std::endl;
    fs << msg << std::endl;
}

int main()
{
    try
    {
        std::ofstream logFile("log.txt");
        if (!logFile.is_open())
            return 1;

        // TEST 1: Push and Peek
        {
            CustomContainer::Stack<int> s;
            s.push(10);
            s.push(20);
            logDiagnostic(std::cout, logFile, "Push/Peek", "20", std::to_string(s.peek()));
        }

        // TEST 2: Search Index
        {
            CustomContainer::Stack<int> s;
            s.push(100);
            s.push(200);
            s.push(300);
            logDiagnostic(std::cout, logFile, "Search Middle Element", "1", std::to_string(s.search(200)));
        }

        // TEST 3: toString Format (size capacity elements)
        {
            CustomContainer::Stack<int> s;
            s.push(1);
            s.push(2);
            s.push(3);
            // Expected: size=3, cap=10, elements=1 2 3
            logDiagnostic(std::cout, logFile, "toString Format", "3 10 1 2 3", s.toString());
        }

        // TEST 4: Update Top via *=
        {
            CustomContainer::Stack<int> s;
            s.push(50);
            s *= 100;
            logDiagnostic(std::cout, logFile, "Update Top (*=)", "100", std::to_string(s.peek()));
        }

        // TEST 5: Equality (==)
        {
            CustomContainer::Stack<int> s1, s2;
            s1.push(10);
            s2.push(10);
            logDiagnostic(std::cout, logFile, "Equality Operator", "true", boolToStr(s1 == s2));
        }

        // TEST 6: Inequality (!=)
        {
            CustomContainer::Stack<int> s1, s2;
            s1.push(10);
            s2.push(20);
            logDiagnostic(std::cout, logFile, "Inequality Operator", "true", boolToStr(s1 != s2));
        }

        // TEST 7: Less-Than (<)
        {
            CustomContainer::Stack<int> s1, s2;
            s1.push(10); // size 1
            s2.push(10);
            s2.push(20); // size 2
            logDiagnostic(std::cout, logFile, "Size-based Comparison (<)", "true", boolToStr(s1 < s2));
        }

        // TEST 8: Index Access via []
        {
            CustomContainer::Stack<int> s;
            s.push(11);
            s.push(22);
            logDiagnostic(std::cout, logFile, "Index Search Alias ([])", "0", std::to_string(s[11]));
        }

        // TEST 9: Compound Addition (+=)
        {
            CustomContainer::Stack<int> s;
            s.push(10);
            s += 20;
            logDiagnostic(std::cout, logFile, "Compound Addition (+=)", "20", std::to_string(s.peek()));
        }

        // TEST 10: Multi-pop (-=)
        {
            CustomContainer::Stack<int> s;
            s.push(10);
            s.push(20);
            s.push(30);
            s -= 2; // Removes 30 and 20
            logDiagnostic(std::cout, logFile, "Multi-Pop Result (-=)", "10", std::to_string(s.peek()));
        }

        // TEST 11: Assignment Deep Copy
        {
            CustomContainer::Stack<int> s1, s2;
            s1.push(5);
            s2 = s1;
            s1.push(10); // Modify original
            // s2 should be size=1, cap=10, elements=5
            logDiagnostic(std::cout, logFile, "Assignment Independence", "1 10 5", s2.toString());
        }

        // TEST 12: Copy Constructor
        {
            CustomContainer::Stack<int> s1;
            s1.push(7);
            CustomContainer::Stack<int> s2(s1);
            // s2 should be size=1, cap=10, elements=7
            logDiagnostic(std::cout, logFile, "Copy Constructor Match", "1 10 7", s2.toString());
        }

        // TEST 13: Clear via !
        {
            CustomContainer::Stack<int> s;
            s.push(1);
            s.push(2);
            !s;
            // Expected: size=0, cap=10, elements (none)
            logDiagnostic(std::cout, logFile, "Clear Operator (!)", "0 10 ", s.toString());
        }

        // TEST 14: Exception Throwing
        {
            CustomContainer::Stack<int> s;
            std::string caught = "false";
            try
            {
                s.pop(1);
            }
            catch (const CustomContainer::StackUnderflowException &)
            {
                caught = "true";
            }
            logDiagnostic(std::cout, logFile, "Underflow Exception Handling", "true", caught);
        }

        // TEST 15: std::out_of_range on peek
        {
            CustomContainer::Stack<int> s;
            std::string caught = "false";
            try
            {
                s.peek();
            }
            catch (const std::out_of_range &)
            {
                caught = "true";
            }
            logDiagnostic(std::cout, logFile, "Empty Peek Out of Range", "true", caught);
        }

        // TEST 16: updateTop on Empty Stack
        {
            CustomContainer::Stack<int> s;
            std::string caught = "false";
            try
            {
                s.updateTop(5);
            }
            catch (const std::out_of_range &)
            {
                caught = "true";
            }
            logDiagnostic(std::cout, logFile, "Update Top Exception", "true", caught);
        }

        // SUMMARY REPORT
        std::string summary = "\n============================================================\n"
                              "TEST RUN COMPLETE\n"
                              "Total Tests: " +
                              std::to_string(testCounter) + "\n"
                                                            "Passed:      " +
                              std::to_string(passCounter) + "\n"
                                                            "Failed:      " +
                              std::to_string(testCounter - passCounter) + "\n";

        if (failedTests.empty())
        {
            summary += "All tests passed successfully.\n";
        }
        else
        {
            summary += "FAILED TEST NUMBERS: ";
            for (size_t i = 0; i < failedTests.size(); ++i)
            {
                summary += std::to_string(failedTests[i]) + (i == failedTests.size() - 1 ? "" : ", ");
            }
            summary += "\n";
        }
        summary += "============================================================\n";

        std::cout << summary;
        logFile << summary;
        logFile.close();
    }
    catch (...)
    {
        std::cerr << "An unexpected error occurred during testing." << std::endl;
    }
    return 0;
}