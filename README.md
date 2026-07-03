# CPP_TESTING_FRAMEWORK

An easy to use testing framework for cpp


## usage
Simply copy the ./th_test.hpp to your test/ directory and include the header following the ./test_example.cpp

### Simple example

```cpp
//file_to_test.cpp

int squared(int x){
    return x*x;
}

```

```cpp
//test.cpp

#include "th_test.hpp"
#include "file_to_test.cpp"

void test_squared(){
    ASSERT(squared(2)==4)//passing test
    ASSERT(squared(2)==6)//failing test
    ASSERT(squared(2)==4)//failing test

}
TEST(test_squared)
//note: this will register as a single test but throw multiple errors!

int main(){
    //tests are gonna run here and show the failing ones
    TH_TEST::RUN_TESTS();

    return 0;
}

```

## How the testing framework works
the testing works by registering tests and their data (file,line,function name) in a vector, execute the tests and track if they passed.then show the resaults


## Why use this framework?
- This framework helps creating test cases easily for cpp programs
- Easy to add to the project (a single header copy/paste)
- Easy to use and non time consuming

