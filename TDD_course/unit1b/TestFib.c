/**@file TestFib.c
 * File containing test functions
*/


/**************************************************************************************************
 * INCLUDES
 *************************************************************************************************/
#include "unity.h"
#include "Fib.h"

/**************************************************************************************************
 * PRIVATE DEFINES
 *************************************************************************************************/

/**! Define to deinition of the macro DIMENSION_OF*/
#define     DIMENSION_OF(x)     (sizeof(x)/sizeof(x[0]))

/**! Define the maximum Fibonacci series element supported by 64-bit*/
#define     FIB_MAX_ELEMENT     (45)

/**! Define which tests will run*/
#define     TEST_FIBONACCI_FUNC_1   1


#if TEST_FIBONACCI_FUNC_1  == 1

/**************************************************************************************************
 * FUNCTIONS
 *************************************************************************************************/

/**!Test negative elements and return 0*/ 
void test_negative_elements_return_0(void)
{
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(-1));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(-3));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(-555));
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(-1000));
}

/** !Test differents elements*/
void test_differents_elements(void)
{
    TEST_ASSERT_EQUAL_INT(1,Fibonacci_GetElement(1));
    TEST_ASSERT_EQUAL_INT(2,Fibonacci_GetElement(2));
    TEST_ASSERT_EQUAL_INT(3,Fibonacci_GetElement(3));
    TEST_ASSERT_EQUAL_INT(5,Fibonacci_GetElement(4));
}


/** !tests part of the fibonacci series sequence*/ 
void test_part_of_the_sequence(void)
{
    int expected[] = {1,1,2,3,5,8,13,21,34,55,89,144};
    int i;

    for(i = 1; i<DIMENSION_OF(expected); i++)
    {
        TEST_ASSERT_EQUAL_INT(expected[i], Fibonacci_GetElement(i));
    }
}

/**!tests values that exceed the 64bits limit*/
void test_that_overrun_values(void)
{
    TEST_ASSERT_EQUAL_INT(0,Fibonacci_GetElement(FIB_MAX_ELEMENT));

}

#elif TEST_FIBONACCI_FUNC_1 == 0

//funções teste de fibonacci

#endif  

int main(void) {
    UNITY_BEGIN();
    #if TEST_FIBONACCI_FUNC_1 == 1
        RUN_TEST(test_negative_elements_return_0);
        RUN_TEST(test_differents_elements);
        RUN_TEST(test_part_of_the_sequence);
        RUN_TEST(test_that_overrun_values);
    #endif
    return UNITY_END();
}
