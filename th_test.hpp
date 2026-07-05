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
        std::cout << "RUNNING Tests...\n" << std::endl;
        
        for(auto& test:tests){
            current_test=&test;
            test.func();
        }
        std::cout << std::endl;

        std::cout << "--------------------------Tests Report---------------------------------" << std::endl;
        
        int passed_count = 0;
        int total_tests = tests.size();
        
        for(size_t i = 0; i < tests.size(); ++i){
            std::cout << "\t[" << (i + 1) << "/" << total_tests << "] " << tests[i].name << "() ";
            if(tests[i].passed){
                std::cout << "[Passed]" << std::endl;
                passed_count++;
            }else{
                std::cout << "[Failed]" << std::endl;
            }
        }
        std::cout << std::endl;

        std::cout << "Passing Tests [" << passed_count << "/" << total_tests << "]" << std::endl;
    }

}

#endif
