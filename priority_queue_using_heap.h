///\file priority_queue_using_heap.h
///\brief This is the header file.
///
#ifndef _PRIORITY_QUEUE_HEAP_H_
#define _PRIORITY_QUEUE_HEAP_H_

#include <stdio.h>
#include <string.h>


struct queue_member{

    int value; /*!< Valoarea fiecarui membru(data). */
    int priority; /*!< Prioritatea in coada */

};
typedef struct queue_member queue_member;

struct queue{

    queue_member *queue_array; /*!< Vector de membri ai cozii. */
    int number_of_members; /*!< Numarul de membrii din coada. */
    int memory_alloc; /*!< Numarul de membrii pentru care a fost alocata memorie */

};

typedef struct queue queue;
typedef struct queue *queue_pointer; /*!< Vectori de cozi. */

queue_pointer new_queue(int queue_size);
void queue_push(queue_pointer push_to_queue, int value, int priority);
void queue_adjust(queue_pointer queue_to_adjust);
void queue_display(queue_pointer queue_to_display);
void queue_pop(queue_pointer queue);
void queue_change_priority(queue_pointer queue, int value, int priority);
void queue_has_value(queue_pointer queue, int data);
int queue_pop_display(queue_pointer queue);
int queue_pop_min_display(queue_pointer queue);

#endif
