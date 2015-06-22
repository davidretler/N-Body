/*
 * list.h
 *
 *  Created on: Jun 16, 2015
 *      Author: david
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define DEFUALT_INCREMENT_LENGTH 10

typedef planet* list_type;
typedef struct array_list
{
    size_t size;
    size_t length;
    list_type* list_address;

} array_list;

void init_list(array_list* list)
{
    list->size = 0;
    list->length = 0;
    list->list_address = 0;
}

/*
 Set the size of the list

 Allows you to set the size of the list, as long as you are making it larger
 Makes sure to copy the old list data into the new one, and free the memory
 allocated to hold the data previously
 */
int list_set_size(array_list* list, size_t size)
{
    if (size >= 0 && size >= list->length)
    {
        list_type* new_list_address = malloc(size * (sizeof(list_type))); //allocate space for the larger array_list
        for (int i = 0; i < list->length; i++) //copy the old array into the new one
        {
            new_list_address[i] = list->list_address[i];
        }
        if (list->list_address != 0)
        {
            free(list->list_address);			//free the memory from the old list
        }
        //set the new list address to new_list_address and update size
        list->list_address = new_list_address;
        list->size = size;

        return 0;
    }
    else if (size < list->length)
    {
        //new capacity is smaller than length
        return -1;
    }

    //something went wrong
    return -2;
}

/*
 Trims the list if necessary
 */
int list_trim(array_list* list)
{
    if (list->size > list->length + DEFUALT_INCREMENT_LENGTH)
    {
        list_set_size(list, list->length + DEFUALT_INCREMENT_LENGTH);
        return 0;										//trimming sucessfull
    }
    return -1; 										//did not need to be trimmed
}

int list_add(array_list* list, list_type item)
{
    if (list->size > list->length)	//if the list is long enough to accomodate
    {
        list->list_address[list->length] = item;			//just add the item
        list->length++;
        return 0;
    }
    else	//if the list is not long enough, expand the list
    {
        list_set_size(list, list->size + DEFUALT_INCREMENT_LENGTH);
        list_add(list, item);						//and then add the item
        return 0;
    }
    return -1;
}

/*
 Remove the ith element from the list, and return it's value
 */
list_type list_remove(array_list* list, size_t index)
{
    if (index < list->length)			//if there really is something to remove
    {
        list_type element = list->list_address[index];
        for (int i = index; i < list->length; i++)			//shift everything after the removed element to the left
        {
            list->list_address[i] = list->list_address[i + 1];
        }
        list->length--;							//decrement list length
        //list_trim(list);						//trim, if necessary
        //trimming after each removal takes time but
        //saves space
        return element;
    }

    return 0;
}

/*
 * Frees the memory in use by the list
 */
void free_list(array_list* list)
{
    free(list->list_address);
    free(list);
}

#endif /* LIST_H_ */

