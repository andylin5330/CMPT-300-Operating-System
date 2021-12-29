#include "linkedlist.h"
#include <stdio.h>

int initialized = 0;
//creating list
LIST* ListCreate(){
    printf("%d\n", initialized);
    if(initialized == 0){
        node* temp_node = &node_pool[0];
        LIST* temp_head = &head_array[0];
        for(int i=0; i<300; i++){
            temp_node->next = &node_pool[i];
            temp_node = temp_node->next;
        }
        for(int j=0; j<200; j++){
            temp_head->next = &head_array[j];
            temp_head = temp_head->next;
        }
        head_index = &head_array[0];
        hidden_head = &node_pool[0];
        initialized = 1;
    }
    if(head_index==NULL){
        return NULL;
    }
    
    LIST* new_head = head_index;
    head_index = head_index->next;
    new_head->next = NULL;
    new_head->head_node = NULL;
    new_head->tail_node = NULL;
    new_head->curr = NULL; 
    new_head->length = 0;
    new_head->exist = 1;
    new_head->flag = 0;
    return new_head;
}

//count the length of the list
int ListCount(LIST* list){
    return list->length;
}

//return the head node in the list
void *ListFirst(LIST* list){
    if(list->exist == 0){
        return NULL;
    }
    if(list->head_node == NULL){
        list->curr = NULL;
        return NULL;
    }
    list->curr = list->head_node;
    return list->curr;
}

//return the tail node in the list
void *ListLast(LIST* list){
    if(list->exist == 0){
        return NULL;
    }
    if(list->head_node == NULL){
        list->curr = NULL;
        return NULL;
    }
    list->curr = list->tail_node;
    return list->curr;
}


//return the current next node
void *ListNext(LIST* list){
    if(list->exist == 0){
        return NULL;
    }
    else if(list->head_node == NULL){
        list->curr = NULL;
        return NULL;
    }
    else if(list->flag == 1){
        list->curr = list->head_node;
        list->flag = 0;
        return list->curr;
    }
    else if(list->curr == NULL){
        return NULL;
    }
    list->curr = list->curr->next;
    return list->curr;
}

//return the current previous node
void *ListPrev(LIST* list){
    if(list->exist == 0){
        return NULL;
    }
    else if(list->head_node == NULL){
        list->curr = NULL;
        return NULL;
    }
    else if(list->flag == 1 || list->curr == list->head_node){
        list->flag = 1;
        list->curr = NULL;
        return NULL;
    }
    else if(list->curr == NULL){
        list->curr = list->tail_node;
        return list->curr;
    }
    list->curr = list->curr->prev;
    return list->curr;
}


//return the current current node
void *ListCurr(LIST* list){
    if(list->exist == 0){
        return NULL;
    }
    if(list->head_node == NULL){
        list->curr = NULL;
        return NULL;
    }
    if(list->flag == 1){
        return NULL;
    }
    if(list->curr == NULL){
        return NULL;
    }
    return list->curr;
}

//Add the item at the next node of the current node
int ListAdd(LIST* list, void* item){
    if(list->exist == 0){
        return -1;
    }
    if(hidden_head == NULL){
        return -1;
    }
    node* ava_node = hidden_head;
    hidden_head = hidden_head->next; 
    ava_node->val = item;
    if(list->length == 0){
        ava_node->prev = NULL;
        ava_node->next = NULL;
        list->head_node = ava_node;
        list->tail_node = ava_node;
        list->curr = ava_node;
    }
    else if(list->flag == 1){
        ava_node->prev = NULL;
        ava_node->next = list->curr->next;
        list->curr->next->prev = ava_node;
        list->curr->next = ava_node;
        list->head_node = ava_node;
        list->curr = ava_node;
        list->flag = 0;
    }
    else if(list->curr == NULL){
        ava_node->prev = list->tail_node->prev;
        ava_node->next = NULL;
        list->tail_node->prev->next = ava_node;
        list->tail_node = ava_node;
        list->curr = ava_node;
    }
    else{
        ava_node->next = list->curr->next;
        ava_node->prev = list->curr;
        list->curr->next = ava_node;
        if(list->curr == list->tail_node){
            list->tail_node = ava_node;  
        }
        else{
            ava_node->next->prev = ava_node;
        }
        list->curr = ava_node;
    }
    list->length ++;
    return 0;
}

//Insert the item at the previous node of the current node
int ListInsert(LIST* list, void* item){
    if(list->exist == 0){
        return -1;
    }
    if(hidden_head == NULL){
        return -1;
    }
    node* ava_node = hidden_head;
    hidden_head = hidden_head->next;
    ava_node->val = item;
    if(list->length == 0){
        ava_node->prev = NULL;
        ava_node->next = NULL;
        list->head_node = ava_node;
        list->tail_node = ava_node;
        list->curr = ava_node;
    }
    else if(list->flag == 1){
        ava_node->prev = NULL;
        ava_node->next = list->curr->next;
        list->curr->next->prev = ava_node;
        list->curr->next = ava_node;
        list->head_node = ava_node;
        list->curr = ava_node;
        list->flag = 0;
    }
    else if(list->curr == NULL){
        ava_node->prev = list->tail_node->prev;
        ava_node->next = NULL;
        list->tail_node->prev->next = ava_node;
        list->tail_node = ava_node;
        list->curr = ava_node;
    }
    else{
        ava_node->prev = list->curr->prev;
        ava_node->next = list->curr;
        list->curr->prev = ava_node;
        if(list->curr == list->head_node){
            list->head_node = ava_node;
        }
        else{
            ava_node->prev->next = ava_node;
        }
        list->curr = ava_node;
    }
    list->length ++;
    return 0;
}

//Append the node at the end of the list
int ListAppend(LIST* list, void* item){
    if(list->exist == 0){
        return -1;
    }
    if(hidden_head == NULL){
        return -1;
    }
    node* ava_node = hidden_head;
    hidden_head = hidden_head->next;
    ava_node->val = item;
    if(list->length == 0){
        ava_node->prev = NULL;
        ava_node->next = NULL;
        list->head_node = ava_node;
        list->tail_node = ava_node;
        list->curr = ava_node;
    }
    else{
        ava_node->prev = list->tail_node;
        ava_node->next = NULL;
        list->tail_node->next = ava_node;
        list->tail_node = ava_node;
        list->curr = ava_node;
    }
    list->length ++;
    return 0;
}

//Prepend the node at the beginning of the list
int ListPrepend(LIST* list, void* item){
    if(list->exist == 0){
        return -1;
    }
    if(hidden_head == NULL){
        return -1;
    }
    node* ava_node = hidden_head;
    hidden_head = hidden_head->next;
    ava_node->val = item;
    if(list->length == 0){
        ava_node->prev = NULL;
        ava_node->next = NULL;
        list->head_node = ava_node;
        list->tail_node = ava_node;
        list->curr = ava_node;
    }
    else{
        list->head_node->prev = ava_node;
        ava_node->prev = NULL;
        ava_node->next = list->head_node;
        list->head_node = ava_node;
        list->curr = ava_node;
    }
    list->length ++;
    return 0;
}

//removing the whole list
void *ListRemove(LIST* list){
    if(list->exist == 0){
        return -1;
    }
    node* temp = list->curr;
    if(list->flag == 1){
        list->curr = list->head_node;
        list->flag = 0;
        return NULL;
    }
    else if(list->curr == NULL){
        return NULL;
    }
    else if(list->curr == list->head_node){
        list->head_node = temp->next;
        if(list->head_node != NULL){
            list->head_node->prev = NULL;
        }
        else{
            list->tail_node = NULL;
        }
        list->curr = list->head_node;
    }
    else if(list->curr == list->tail_node){
        list->tail_node = temp->prev;
        if(list->tail_node != NULL){
            list->tail_node->next = NULL;
        }
        else{
            list->head_node = NULL;
        }
        list->curr = list->tail_node;
    }
    else{
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        list->curr = temp->next;
    }
    temp->next = hidden_head;
    temp->prev = NULL;
    hidden_head = temp;
    list->length = list->length - 1;
    return temp->val;
}

//list concat
void ListConcat(LIST* list1, LIST* list2){
    if(list1->exist == 0 || list2->exist == 0){
        return NULL;
    }
    if(list1->tail_node != NULL){
        list1->tail_node->next = list2->head_node;
        if(list2->head_node != NULL){
            list2->head_node->prev = list1->tail_node;
        }
    }
    else{
        list1->head_node = list2->head_node;
    }
    list1->length = list1->length + list2->length;
    list1->tail_node = list2->tail_node;
    if(list1->curr == NULL){
        list1->curr = list2->head_node;
    }
    list2->next = head_index;
    head_index = list2;
    list2->exist = 0;
}

//list free
void ListFree(LIST* list, void(*itemFree)()){
    if(list->exist == 0){
        return NULL;
    }
    node* temp = list->head_node;
    while(temp != NULL){
        (*itemFree)(temp->val);
    }
    if(list->tail_node != NULL){
        list->tail_node->next = hidden_head;
        hidden_head = list->head_node;
    }
    list->next = head_index;
    head_index = list;
    list->exist = 0;
}

//list trim
void *ListTrim(LIST* list){
    if(list->exist == 0){
        return NULL;
    }
    if(list->length != 0){
        node* temp = list->tail_node;
        if(temp->prev != NULL){
            temp->prev->next = NULL;
        }
        list->curr = temp->prev;
        temp->next = hidden_head;
        hidden_head = temp;
        return temp;
    }
    else{
        list->curr = NULL;
        return NULL;
    }
}

//list search
void *ListSearch(LIST* list, int(comparator)(void*,void*) , void* comparisonArg){
    if(list->exist == 0){
        return NULL;
    }
    if(list->flag == 1){
        list->curr = list->head_node;   
        list->flag = 0; 
    }
    while(list->curr != NULL){
        if(comparator(list->curr->val, comparisonArg) == 1){
            return list->curr;
        }
        list->curr = list->curr->next;
    }
    return NULL;
}

int comparator(void* a, void* b){
    if(a == b){
        return 1;
    }
    return 0;
}
