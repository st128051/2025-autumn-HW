#include <iostream>

template <class T>
class Array
{
    static const int size = 1000;
    T array[size];
public:
    Array() {};

    Array(const T* b) {
        for (int i = 0; i < size; ++i) {
            array[i] = b[i];
        }
    }

    void show() {
        for (int i = 0; i < size; ++i) {
            std::cout << array[i] << " ";
        }
        std::cout << std::endl;
    }

    T minimum(Array<T>& m) {
        T min_val = array[0];
        for (int i = 1; i < size; ++i) {
            if (array[i] < min_val) {
                min_val = array[i];
            }
        }
        return min_val;
    }
};


int main() {}