#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "../lib/game_core.h"

void test_buttons_getLightCount_none(void)
{
    lumiereGaucheActive = 0;
    lumiereDroiteActive = 0;
    CU_ASSERT_EQUAL(buttons_getLightCount(), 0);
}

void test_buttons_getLightCount_left(void)
{
    lumiereGaucheActive = 1;
    lumiereDroiteActive = 0;
    CU_ASSERT_EQUAL(buttons_getLightCount(), 1);
}

void test_buttons_getLightCount_right(void)
{
    lumiereGaucheActive = 0;
    lumiereDroiteActive = 1;
    CU_ASSERT_EQUAL(buttons_getLightCount(), 1);
}

void test_buttons_getLightCount_both(void)
{
    lumiereGaucheActive = 1;
    lumiereDroiteActive = 1;
    CU_ASSERT_EQUAL(buttons_getLightCount(), 2);
}

int main(void)
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite suite = CU_add_suite("ButtonsGetLightCountSuite", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(suite, "no lights", test_buttons_getLightCount_none) == NULL ||
        CU_add_test(suite, "left light", test_buttons_getLightCount_left) == NULL ||
        CU_add_test(suite, "right light", test_buttons_getLightCount_right) == NULL ||
        CU_add_test(suite, "both lights", test_buttons_getLightCount_both) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
