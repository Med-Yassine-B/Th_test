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
        std::cerr << "[\033[34m" #condition "\033[0m Failed at: \033[33m" __FILE__ ":" << __LINE__ << "\033[0m]" << std::endl;\
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
        std::cout << "\033[33mRUNNING Tests...\033[0m\n" << std::endl;
        
        for(auto& test:tests){
            current_test=&test;
            test.func();
        }
        std::cout << std::endl;

        std::cout << "\033[36m--------------------------Tests Report---------------------------------\033[0m" << std::endl;
        
        int passed_count = 0;
        int total_tests = tests.size();
        
        for(size_t i = 0; i < tests.size(); ++i){
            std::cout << "\t[" << (i + 1) << "/" << total_tests << "] " << tests[i].name << "() ";
            if(tests[i].passed){
                std::cout << "\033[32m[Passed]\033[0m" << std::endl;
                passed_count++;
            }else{
                std::cout << "\033[31m[Failed]\033[0m" << std::endl;
            }
        }
        std::cout << std::endl;

        if(passed_count == total_tests){
            std::cout << "\033[32mPassing Tests [" << passed_count << "/" << total_tests << "]\033[0m" << std::endl;
        }else{
            std::cout << "\033[31mPassing Tests [" << passed_count << "/" << total_tests << "]\033[0m" << std::endl;
        }
    }

}

#endif
