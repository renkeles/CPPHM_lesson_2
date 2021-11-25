#include <iostream>
#include <vector>
#include <algorithm>

template <class T>
auto Swap(T &t1, T &t2){
    T tmp = t1;
    t1 = t2;
    t2 = tmp;
}
//---------------task2---
struct Less {
    template <class T>
    bool operator()(T first, T second) const {
        return first < second;
    }
};

template <class Cmp>
struct Cmp_ptr {
    Cmp cmp;
    Cmp_ptr() = default;

    template <class T>
    bool operator()(T first, T second) const {
        return cmp(*first, *second);
    }
};

template <class T>
auto SortPointers(std::vector<T*> &vec){

    std::sort(vec.begin(), vec.end(), Cmp_ptr<Less>());

}

template <class T>
auto PrintVec(std::vector<T> &vec){
    std::cout << "Print vector: ";
    for(auto *elem : vec){
        std::cout << *elem << " ";
    }
    std::cout << std::endl;
}
//--------------/task2---

void task_1(){
    int first = 2;
    int second = 3;
    int *ptr_1 = &first;
    int *ptr_2 = &second;
    std::cout << "PTR1 "<< *ptr_1 << " " << *ptr_2 << std::endl;
    Swap(ptr_1, ptr_2);
    std::cout << "PTR2 "<< *ptr_1 << " " << *ptr_2 << std::endl;
}

void task_2(){
    {
        int a{3};
        int b{2};
        int c{1};

        std::vector<int*> vec {&a, &b, &c};
        std::cout << "abc = " << a << " " << b << " " << c << std::endl;
        PrintVec(vec);
        std::cout << "---Sort---" << std::endl;
        SortPointers(vec);
        PrintVec(vec);
        std::cout << "abc = " << a << " " << b << " " << c << std::endl;
    }
/*
    {
        float a{1.3};
        float b{1.2};
        float c{1.1};

        std::vector<float*> vec {&a, &b, &c};
        std::cout << "abc = " << a << " " << b << " " << c << std::endl;
        PrintVec(vec);
        std::cout << "---Sort---" << std::endl;
        SortPointers(vec);
        PrintVec(vec);
        std::cout << "abc = " << a << " " << b << " " << c << std::endl;
    }
*/
}


int main() {
    //task_1();
    //task_2();

    return 0;
}
