//======================================
//文件名caller2.cpp
#include <iostream>

template<typename T>
void func(T const &v)
{
    std::cout << "func2: " << v << std::endl;
}

void caller2() {
    func(2);
    func(0.2f);
}
