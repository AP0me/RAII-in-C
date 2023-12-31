#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct heapLLNode{
  void* heap;
  struct heapLLNode* next;
};
struct heapArr{
  struct heapLLNode* heapFirst;
  struct heapLLNode* heapLast;
  int size;
};
struct Args{
  struct heapArr exampleHeap;
};
void freeAll(struct heapArr* heap){
  struct heapLLNode* temp = heap->heapFirst;
  struct heapLLNode* toBeFreed;
  for(int i=0; i<(heap->size); i++){
    free(temp->heap);
    temp = temp->next;
  }
}
void* autoMalloc(struct heapArr* heap, int size){
  void* mem = malloc(size);
  struct heapLLNode* temp = malloc(sizeof(struct heapLLNode));
  temp->next = NULL;  temp->heap = mem;

  if(heap->size==0){ heap->heapFirst = temp; heap->heapLast = temp; }
  else{
    heap->heapLast->next = temp;
    heap->heapLast = heap->heapLast->next;
  }
  heap->size++;
  
  return mem;
}
void* run(struct Args argList, void *(*exampleFunction1)(struct Args)){
  struct heapArr exampleHeap; exampleHeap.size = 0;
  argList.exampleHeap = exampleHeap;
  void *(*result)() = (void *)exampleFunction1(argList);
  freeAll(&exampleHeap);
  return result;
}

int* exampleFunction(struct Args argList){

  int* data1 = (int *)autoMalloc(&argList.exampleHeap, sizeof(int));
  int* data2 = (int *)autoMalloc(&argList.exampleHeap, sizeof(int));
  int* data3 = (int *)autoMalloc(&argList.exampleHeap, sizeof(int));
  int* data4 = (int *)autoMalloc(&argList.exampleHeap, sizeof(int));
  *data1 = 5;
  *data2 = 10;
  *data3 = 15;
  *data4 = 20;
  
  printf("%d\n", *data3);

  return 0;
}

int main(int argc, char** argv){
  struct Args argList;
  int* res = (int *)run(argList, (void *)&exampleFunction);
}
