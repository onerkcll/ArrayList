#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#define MEMORY_ELEMENT_INCREASE 10

struct array_list
{
    char *ptr;
    int count;
    int ocount;
    size_t element_size;
};

void array_init_list(struct array_list *list, size_t element_size)
{
    list->ptr = (char *)malloc(element_size * MEMORY_ELEMENT_INCREASE);
    //Can hold
    list->count = MEMORY_ELEMENT_INCREASE;
    //Didnt add anything yet
    list->ocount = 0;
    //New Element Size
    list->element_size = element_size;
}

int array_list_count(struct array_list *list)
{
    return list->ocount;
}
void array_list_adding(struct array_list *list, void *ptr)
{ //Adress of value
    if (list->ocount >= list->count)
    {
        //Resize Memory 
        list->ptr = (char *)realloc(list->ptr, ((list->count + MEMORY_ELEMENT_INCREASE) * list->element_size));
        list->count += MEMORY_ELEMENT_INCREASE;
    }

    memcpy(&list->ptr[list->ocount * list->element_size], ptr, list->element_size);
    list->ocount++;
}
bool array_list_get(struct array_list *list, int index, void* out)
{if (index >= list->ocount)
{
    return false;
}

       ///write to   from                                    bytes
    //       |     |                                        | 
    memcpy(out, &list->ptr[index * list->element_size], list->element_size);
    return true;
}
bool array_list_remove(struct array_list *list, int index)
{
    if(index >= list->ocount)
    {
        return false ;
    }

    for (int i = index; i < list->ocount; i++)
    {
        memcpy(&list->ptr[i*list->element_size],&list->ptr[(i+1) * list->element_size], list->element_size);
    }
    
    list->ocount--;
    return true;
}
void array_list_destruct(struct array_list *list)
{
    free(list->ptr);
    list->ptr = NULL;
}

int main(int argc, char **argv)
{
    struct array_list list;
    array_init_list(&list, sizeof(int));
    for (int i = 0; i < 10; i++)
    {
        array_list_adding(&list,&i);
    }
    array_list_remove(&list, 3);
    for (int i = 0; i < array_list_count(&list); i++)
    {   int result = 0;
     array_list_get(&list,i,&result);
     printf("%i\n",result);
    }
    
 array_list_destruct(&list);
  
    return 0;
}