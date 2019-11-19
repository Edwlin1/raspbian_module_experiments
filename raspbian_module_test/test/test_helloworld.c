#include "unity.h"
#include "helloworld.h"
#include "mock_module.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_initPasses(void)
{
	pr_info_Expect("Hello world init\n");

	init_logic();
}

void test_initFails(void)
{
	pr_info_Expect("Goodbye world init\n");

	init_logic();
}
