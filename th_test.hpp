#ifndef TH_TEST_
#define TH_TEST_

#include <vector>
#include <iostream>


#define TEST(func_name)\
    void func_name();\
    struct func_name##registrer{\
        func_name##registrer(){\
            TH_TEST::tests.push_back({&func_name, #func_name,__FILE__,__LINE__});\
        }\
    };\
    struct func_name##registrer func_name##registrer_instance; 




namespace TH_TEST {

    struct test_function{
        void(*func)() ;
        const char* name;
        const char* file;
        int line;
        bool passed=true;
    };
    inline std::vector<struct test_function> tests;

    inline struct test_function* current_test=nullptr;

    inline void assert(bool condition){
        if(!condition){
            std::cerr<<"[Test Failed at"<<current_test->line<<" : "<<current_test->file<<"]"<<std::endl;
            current_test->passed=false;
        }
    }

    inline void RUN_TESTS(){
        std::cout<<"RUNNING Tests..."<<std::endl;
        for(auto test:tests){
            current_test=&test;
            test.func();
        }
        bool all_passed=true;
        std::cout<<"Tests Report:"<<std::endl;
        for(auto test:tests){
            if(test.passed){
                std::cout<<"\t"<<test.name<<"() [Passed]"<<std::endl;
            }else{
                std::cout<<"\t"<<test.name<<"() [Failed]"<<std::endl;
                all_passed=false;
            }
        }
        if(all_passed){
            std::cout<<"[All Tests Passed]"<<std::endl;
        }
    }

}





#endif
