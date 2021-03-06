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


struct Dict{
    char letter;
    int count;

    Dict(char ch, int c) : letter(ch), count(c){

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
    //?????????????? ?????????? ?????? ?????????????????? ???????????????????? ???????????? "Character too large for enclosing character literal type"

    {
        // 2 ?????????? for
        Timer timer("for-for");
        std::string path = "War and Peace.txt";
        std::ifstream fin;
        fin.open(path);
        if(!fin.is_open()){
            std::cout << "Error, file not opened!" << std::endl;
            return;
        }
        int sum = 0;
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
                    if(std::tolower(buffer[i]) == j){
                        ++count;
                    }
                }
                delete [] buffer;
            }
            fin.clear();
            sum += count;
            std::cout << j << ": " << count << std::endl;
        }
        fin.close();
        std::cout << "ALL: " << sum << std::endl;
        timer.print();
    }


    {
        // for-find
        Timer timer("for-find");
        std::string path = "War and Peace.txt";
        std::ifstream fin;
        fin.open(path);
        if(!fin.is_open()){
            std::cout << "Error, file not opened!" << std::endl;
            return;
        }
        std::vector<char> vec;
        char* buffer = nullptr;
        while(!fin.eof()){
            int n=100;
            buffer = new char[n+1]; buffer[n]='\0';
            fin.read(buffer,n);
            for (int i{0}; i < n; ++i) {
                //vec.emplace_back(std::tolower(buffer[i]));      // 31.6778 ms
                vec.push_back(std::tolower(buffer[i]));           // 15.9473 ms
            }

        }
        buffer = nullptr;
        delete [] buffer;
        fin.close();

        std::string l = "aeiouy";
        std::vector<Dict> dict{Dict{'a', 0}, Dict{'e', 0}, Dict{'i', 0}, Dict{'o', 0}, Dict{'u', 0},  Dict{'y', 0}};
        std::sort(vec.begin(), vec.end());
        for(auto &elem : vec){
            auto item{std::find(l.begin(), l.end(), elem)};
            if(item != l.end()){
                switch (elem) {
                    case 'a':{
                        dict[0].count++;
                        break;
                    }
                    case 'e':{
                        dict[1].count++;
                        break;
                    }
                    case 'i':{
                        dict[2].count++;
                        break;
                    }
                    case 'o':{
                        dict[3].count++;
                        break;
                    }
                    case 'u':{
                        dict[4].count++;
                        break;
                    }
                    case 'y':{
                        dict[5].count++;
                        break;
                    }
                    default:{
                        break;
                    }
                }
            }
        }
        int sum = 0;
        for(int i{0}; i < dict.size(); ++i){
            sum += dict[i].count;
        }
        for (auto &elem : dict){
            std::cout << elem.letter << ": " << elem.count << std::endl;
        }
        std::cout << "ALL: " << sum << std::endl;
        timer.print();
    }


    {
        //for-count_if
        Timer timer("for-count_if");
        std::string path = "War and Peace.txt";
        std::ifstream fin;
        fin.open(path);
        if(!fin.is_open()){
            std::cout << "Error, file not opened!" << std::endl;
            return;
        }
        std::vector<char> vec;
        char* buffer = nullptr;
        while(!fin.eof()){
            int n=100;
            buffer = new char[n+1]; buffer[n]='\0';
            fin.read(buffer,n);
            for (int i{0}; i < n; ++i) {
                vec.push_back(std::tolower(buffer[i]));
            }

        }
        buffer = nullptr;
        delete [] buffer;
        fin.close();

        std::vector<Dict> dict{Dict{'a', 0}, Dict{'e', 0}, Dict{'i', 0}, Dict{'o', 0}, Dict{'u', 0},  Dict{'y', 0}};

        for(int i{0}; i < 6; ++i){
            dict[i].count = std::count_if(vec.begin(), vec.end(), [dict, i](char ch) {
                return dict[i].letter == ch;
            });
        }

        for (auto &elem : dict){
            std::cout << elem.letter << ": " << elem.count << std::endl;
        }
        int sum = 0;
        for(int i{0}; i < dict.size(); ++i){
            sum += dict[i].count;
        }
        std::cout << "ALL: " << sum << std::endl;
        timer.print();
    }


    {
        //count_if-find
        Timer timer("count_if-find");
        std::string path = "War and Peace.txt";
        std::ifstream fin;
        fin.open(path);
        if(!fin.is_open()){
            std::cout << "Error, file not opened!" << std::endl;
            return;
        }
        std::vector<char> vec;
        char* buffer = nullptr;
        while(!fin.eof()){
            int n=100;
            buffer = new char[n+1]; buffer[n]='\0';
            fin.read(buffer,n);
            for (int i{0}; i < n; ++i) {
                vec.push_back(std::tolower(buffer[i]));
            }

        }
        buffer = nullptr;
        delete [] buffer;
        fin.close();

        std::string l = "aeiouy";
        std::vector<Dict> dict{Dict{'a', 0}, Dict{'e', 0}, Dict{'i', 0}, Dict{'o', 0}, Dict{'u', 0},  Dict{'y', 0}};
        int count = std::count_if(vec.begin(), vec.end(), [l](const auto& letter){
            auto iterFind{std::find(l.begin(), l.end(), letter)};
            bool isV{iterFind != l.end()};
            return isV;
        });
        //----------------------For FUN---
        std::string str = "";
        for(int i{0}; i < 6; i++){
            str = l[i];
            dict[i].count = std::count_if(vec.begin(), vec.end(), [str](const auto& letter){
                auto iterFind{std::find(str.begin(), str.end(), letter)};
                bool isV{iterFind != str.end()};
                return isV;
            });
        }
        //----------------------For FUN---
        for (auto &elem : dict){
            std::cout << elem.letter << ": " << elem.count << std::endl;
        }
        std::cout << "ALL: " << count << std::endl;
        timer.print();
    }

}



int main() {
    //task_1();
    //task_2();
    task_3();

    return 0;
}
