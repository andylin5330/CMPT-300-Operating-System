typedef struct node{
  void* val; 
  struct node* prev; 
  struct node* next;
}node;

typedef struct LIST{
  node* head_node;
  node* tail_node;
  int exist;
  int length;
  node* curr;
  struct LIST* next;
  int flag;
}LIST;

LIST* head_index;
node* hidden_head;
node* node_pool[300];
LIST* head_array[200];


LIST *ListCreate();
int ListCount(LIST* list);
void *ListFirst(LIST* list);
void *ListLast(LIST* list);
void *ListNext(LIST* list);
void *ListPrev(LIST* list);
void *ListCurr(LIST* list);
int ListAdd(LIST* list,void* item);
int ListInsert(LIST* list, void* item);
int ListAppend(LIST* list, void* item);
int ListPrepend(LIST* list, void* item);
void *ListRemove(LIST* list);
void ListConcat(LIST* list1, LIST* list2);
void ListFree(LIST* list, void(*itemFree)());
void *ListTrim(LIST* list);
void *ListSearch(LIST* list, int(comparator)(void*,void*) , void* comparisonArg);
int comparator(void* a, void* b);



