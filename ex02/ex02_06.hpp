//文件名：the_class.hpp
template<typename T>
template<typename T>
struct the_class
{
    static int id;
    the_class() {++id;}
};

template<typename T> int the_class<T>::id = 0;
