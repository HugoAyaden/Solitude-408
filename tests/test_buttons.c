#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "../lib/game_core.h"

void test_buttons_getDoorCount_none(void)
{
    porteGaucheActive = 0;
    porteDroiteActive = 0;
    CU_ASSERT_EQUAL(buttons_getDoorCount(), 0);
}

void test_buttons_getDoorCount_left(void)
{
    porteGaucheActive = 1;
    porteDroiteActive = 0;
    CU_ASSERT_EQUAL(buttons_getDoorCount(), 1);
}

void test_buttons_getDoorCount_right(void)
{
    porteGaucheActive = 0;
    porteDroiteActive = 1;
    CU_ASSERT_EQUAL(buttons_getDoorCount(), 1);
}

void test_buttons_getDoorCount_both(void)
{
    porteGaucheActive = 1;
    porteDroiteActive = 1;
    CU_ASSERT_EQUAL(buttons_getDoorCount(), 2);
}

int main(void)
{
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    CU_pSuite suite = CU_add_suite("ButtonsGetDoorCountSuite", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (CU_add_test(suite, "no doors", test_buttons_getDoorCount_none) == NULL ||
        CU_add_test(suite, "left door", test_buttons_getDoorCount_left) == NULL ||
        CU_add_test(suite, "right door", test_buttons_getDoorCount_right) == NULL ||
        CU_add_test(suite, "both doors", test_buttons_getDoorCount_both) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}