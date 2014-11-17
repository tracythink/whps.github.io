#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include "Stack_page48_h.hpp"

#define Print std::cout

int main() {
    try {
        Stack<int> intStack;
        Stack<float> floatStack;
        // use int Stack
        intStack.push(34);
        intStack.push(45);
        //use float Stack;
        floatStack.push(7.3);
        // two diff-type Stack use operator =
        floatStack = intStack;
        Print << floatStack.top() << '\n';
        floatStack.pop();
        Print << floatStack.top() << '\n';
        floatStack.pop();
        Print << floatStack.top() << '\n';
        floatStack.pop();
    }
    catch (std::exception const & ex) {
        std::cerr << "Exception: " << ex.what() << '\n';
        Stack<int, std::vector> vStack;
        vStack.push(43);
        vStack.push(4);
        Print << vStack.top() << '\n';
        vStack.pop();
    }
    return 0;
}
