#include "linkedlist.h"
#include <stdio.h>

//test file
int main(int argc, char* argv[]){
    // printf("test2\n");
    LIST* list1 = ListCreate();
    
    printf("list1 length is = %d\n" ,ListCount(list1));
    // printf("test3\n");
    // if(ListFirst(list1) == NULL){
    //     printf("NULL\n");
    // };
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAppend(list1, 7);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListAdd(list1, 1);
    ListPrepend(list1, 8);
    ListPrepend(list1, 8);
    ListPrepend(list1, 8);
    ListPrepend(list1, 8);
    ListPrepend(list1, 8);
    ListPrepend(list1, 8);
    ListPrepend(list1, 8);
    ListInsert(list1, 5);
    ListInsert(list1, 5);
    ListInsert(list1, 5);
    
    ListInsert(list1, 5);
    ListInsert(list1, 5);
    ListInsert(list1, 5);
    ListInsert(list1, 5);
    ListInsert(list1, 5);
    ListInsert(list1, 5);
    ListRemove(list1);
    printf("list1 length is = %d", ListCount(list1));
    printf("\n");
    LIST* list2 = ListCreate();
    ListAppend(list2, 7);
    ListAppend(list2, 7);
    ListRemove(list2);

    // ListConcat(list1, list2);
    // ListAdd(list1, 1);
    // printf("%d",list1->curr);
    // printf("\n");
    // printf("%d", ListFirst(list1));
    // ListAdd(list1, 2);
    // printf("%d",list1->curr);
    // printf("\n");
    // printf("%d", ListLast(list1));
    // ListAdd(list1, 3);
    // ListAdd(list1, 4);
    // ListInsert(list1, 5);
    // ListAdd(list1, 6);
    printf("list2 length is = %d", ListCount(list2));
    printf("\n");
    // printf("%d",list1->curr);
    // printf("\n");
    // printf("%d", ListLast(list1));
    // printf("list2 length is = %d", ListCount(list2));
    // printf("\n");
    // void *curr_p = ListCurr(list1);
    // printf("curr_p = %p\n", curr_p);
    // ListRemove(list1);
    // ListRemove(list1);
    // printf("\n");

    // printf("%d", ListLast(list1));
    // ListConcat(list1, list2);
    // LIST* list3 = ListCreate();
    // ListAdd(list3, 5);
    // ListInsert(list3, 6);
    // ListAppend(list3, 7);
    // ListPrepend(list3, 8);
    // printf("list3 length is = %d", ListCount(list3));
    // printf("\n");


//   LIST* list = ListCreate();
//   //listAdd(), ListAppend and ListCurr()
//   void* item = 3;
//   ListAppend(list, item);
//   ListAdd(list, item);
//   ListPrepend(list, item);
//   ListPrepend(list, item);
//   void *curr_p = ListCurr(list);
//   printf("curr_p = %p\n", curr_p);
//   ListAdd(list, item);
//   // ListInsert(list, item);
//   //ListCount()
//   int len = ListCount(list);
//   printf("len = %d\n", len);
//   //ListTrim()
//   node* temp;
//   temp = ListTrim(list);
//   printf("should return 3, val = %d\n", temp->val);
//   return 0; // tests pass
    
    return 0;
}