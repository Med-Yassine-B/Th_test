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

#define ASSERT(condition)\
{\
    if(!(condition)){\
        std::cerr<<"[" #condition " Failed at: " __FILE__ ":" <<__LINE__ <<"]"<<std::endl;\
        TH_TEST::current_test->passed=false;\
    }\
}



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


    inline void RUN_TESTS(){
        std::cout<<"RUNNING Tests..."<<std::endl;
        for(auto& test:tests){
            current_test=&test;
            test.func();
        }
        bool all_passed=true;
        int passed_count=0;
        int total=tests.size();
        std::cout<<"Tests Report:"<<std::endl;
        int  i=0;
        for(auto& test:tests){
            i++;
            if(test.passed){
                std::cout<<"["<<i<<"/"<<total<<"] "<<test.name<<"() [Passed] "<<std::endl;
                passed_count++;
            }else{
                std::cout<<"["<<i<<"/"<<total<<"] "<<test.name<<"() [Failed] "<<std::endl;
                all_passed=false;
            }
        }
        std::cout<<"Tests Passed ["<<passed_count<<"/"<<total<<"]"<<std::endl;
        if(all_passed){
            std::cout<<"[All Tests Passed]"<<std::endl;
        }
    }

}





#endif
