#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "my_vector.hpp"

template<>
class my_vector<bool>
{
    int *array;
    unsigned size;
    unsigned block_size;
    //一个段（segment）即一个整数值，段大小即为一个整数值所能容纳的最多布尔值数
    // = sizeof(int) * 8;
    const static unsigned seg_size;
public:
    my_vector(unsigned bsz = 1) :
        array((int*)malloc(sizeof(int) * bsz)),
        size(0), block_size(bsz) {}
    ~my_vector() {if (array) free(array);}

    void push_back(bool elem)
        throw (std::runtime_error) {
        if (size == block_size * seg_size) {
            block_size *= 2;
            int* new_array = (int*)realloc(array, block_size * sizeof(int));
            if (new_array != NULL) array = new_array;
            else {
                free(array);
                array = NULL;
                throw std::runtime_error("Out of memory.");
            }
        }
        set(size++, elem);
    }

    void set(unsigned i, bool elem) {
        if (elem) {
            array[i / seg_size] |= (0x1 << (i % seg_size));
        }
        else {
            array[i / seg_size] &= ~(0x1 << (i % seg_size));
        }
    }

    bool operator[] (unsigned i) const {
        return (array[i / seg_size] & (0x1 << (i % seg_size))) != 0;
    }

    unsigned get_mem_size() const {return block_size * sizeof(int);}
};

const unsigned my_vector<bool>::seg_size = sizeof(int) * 8;

int main()
{
    my_vector<char> vi(2);
    my_vector<bool> vb(2);
    for (unsigned i = 0; i < 20; ++i) {
        vi.push_back('a' + i);
        vb.push_back((i % 4) == 0);
    }

    using namespace std;
    cout << "MemSize of my_vector<char> is " << vi.get_mem_size() << endl;
    cout << "MemSize of my_vector<bool> is " << vb.get_mem_size() << endl;

    for (unsigned i = 0; i < 20; ++i)
        cout << ' ' << vi[i];
    cout << endl;

    for (unsigned i = 0; i < 20; ++i)
        cout << vb[i];
    cout << endl;
}
