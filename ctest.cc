
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <list>
#include <stdint.h>

#include <CUnit.h>
#include <Basic.h>

#include "ctest.h"
#include "c_list.h"

void test_list(void)
{

    uint32_t  times = 10000000 , i = 0;
    c_list *list = list_init();
    clock_t start,end;

    std::list<c_list_node*>   clist;

    start = clock();
    for ( i = 0 ; i < times; ++i)
    {
        c_list_node *nd = list_node_new();
        list_push_back(list,nd);
    }
    free(list);
    end = clock();


    fprintf(stdout,"c_list Time Ellapsed:%d\n",(end-start));


    start = clock();
    for ( i = 0 ; i < times; ++i)
    {
        c_list_node *nd = list_node_new();
        clist.push_back(nd);
    }
    clist.clear();
    end = clock();


    fprintf(stdout,"c++ list Time Ellapsed:%d\n",end-start);

}

void test_init(void)
{
    c_list *list = list_init();

    CU_ASSERT(list != NULL);
    CU_ASSERT( list->size == 0);

    free(list);
}

void test_push_back(void)
{
    c_list *list = list_init();

    c_list_node *n1 = list_node_new(),
                *n2 = list_node_new(),
                *n3 = list_node_new();

    CU_ASSERT( list != NULL );

    list_push_back(list,n1);
    list_push_back(list,n2);
    list_push_back(list,n3);

    CU_ASSERT( list->size == 3 );
    CU_ASSERT( list->tail->pre == n3);
    CU_ASSERT( list->head->next == n1);

    list_free(list);
}

void run_test(void)
{
    int ret;

    CU_BasicRunMode mode = CU_BRM_VERBOSE;
    CU_ErrorAction  erract = CUEA_IGNORE;


    CU_TestInfo tests[] =
    {
        {"test_init",test_init},
        {"test_push_back",test_push_back}
    };

    CU_SuiteInfo suits[] =
    {
        {"suit_1",NULL,NULL,NULL,NULL,tests}
    };

    if ( CUE_SUCCESS != CU_initialize_registry())
    {
        fprintf(stderr,"Test Error\n");
        return;
    }
    if( CUE_SUCCESS != CU_register_suites(suits))
    {
        fprintf(stderr,"Test ERROR\n");
        return;
    }

    CU_basic_set_mode(mode);
    CU_set_error_action(erract);

    ret = CU_basic_run_tests();

    fprintf(stderr,"Test Complete: Return: %d\n",ret);
}
