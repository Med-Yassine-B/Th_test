#include "th_test.hpp"


int add(int a,int b){
    return a+b;
}

void test_add(){
    TH_TEST::assert(add(5,5)==10);
    TH_TEST::assert(add(5,3)==10);
    TH_TEST::assert(add(5,2)==10);
    TH_TEST::assert(add(5,9)==10);
}

TEST(test_add);

int main(){
    
    TH_TEST::RUN_TESTS();

    return 0;
}


