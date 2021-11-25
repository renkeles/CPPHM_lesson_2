#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>

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
struct CmpPtr {
    Cmp cmp;
    CmpPtr() = default;

    template <class T>
    bool operator()(T first, T second) const {
        return cmp(*first, *second);
    }
};

template <class T>
auto SortPointers(std::vector<T*> &vec){

    std::sort(vec.begin(), vec.end(), CmpPtr<Less>());

}

template <class T>
auto PrintVec(std::vector<T*> &vec){
    std::cout << "Print vector: ";
    for(auto *elem : vec){
        std::cout << *elem << " ";
    }
    std::cout << std::endl;
}
//--------------/task2---

class Timer
{
private:
    using clock_t = std::chrono::high_resolution_clock;
    using second_t = std::chrono::duration<double, std::ratio<1> >;

    std::string m_name;
    std::chrono::time_point<clock_t> m_beg;
    double elapsed() const
    {
        return std::chrono::duration_cast<second_t>(clock_t::now() -m_beg).count();
    }

public:
    Timer() : m_beg(clock_t::now()) { }
    Timer(std::string name) : m_name(name), m_beg(clock_t::now()) { }

    void start(std::string name) {
        m_name = name;
        m_beg = clock_t::now();
    }
    void print() const {
        std::cout << m_name << ":\t" << elapsed() * 1000 << " ms" << '\n';
    }
};


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

void task_3(){
    //setlocale(LC_ALL, "ru");
    //Русские буквы при сравнении выкидывают ошибку "Character too large for enclosing character literal type"

    {
        // 2 цикла for
        Timer timer("for-for");
        std::string path = "War and Peace.txt";
        std::ifstream fin;
        fin.open(path);
        if(!fin.is_open()){
            std::cout << "Error, file not opened!" << std::endl;
            return;
        }
        int count = 0;
        char lang[6] = {'a', 'e', 'i', 'o', 'u', 'y'};
        for(char j : lang){
            count = 0;
            fin.seekg(0,std::ifstream::beg);
            while(!fin.eof()){
                int n=100;
                char* buffer=new char[n+1]; buffer[n]=0;
                fin.read(buffer,n);
                for (int i = 0; i < n; ++i) {
                    if(std::tolower(buffer[i]) =='а'){
                        ++count;
                    }
                }
                delete [] buffer;
            }
            fin.clear();
            std::cout << j << ": " << count << std::endl;
        }
        timer.print();
    }

}



int main() {
    //task_1();
    //task_2();
    task_3();

    return 0;
}
