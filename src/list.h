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
#include "planet.h"
#define DEFUALT_INCREMENT_LENGTH 10

typedef planet* list_type;
typedef struct array_list
{
    size_t size;
    size_t length;
    list_type* list_address;

} array_list;

void init_list(array_list* list);
int list_set_size(array_list* list, size_t size);
int list_trim(array_list* list);
int list_add(array_list* list, list_type item);
list_type list_remove(array_list* list, size_t index);
void free_list(array_list* list);


#endif /* LIST_H_ */
