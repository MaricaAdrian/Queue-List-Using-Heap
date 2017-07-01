/**
*
*	@file priority_queue_using_heap.c
*	@brief In aceasta fila gasim toate functiile pe care le-am declarat in header.
*
*
*
*/
#include "priority_queue_using_heap.h"

/**
* @param queue_size Este folosit pentru a da lungimea dorita noii cozi.
*/
queue_pointer new_queue(int queue_size){

    if(queue_size < 4) /*!< Trebuie alocati cel putin 4 membri pentru fiecare coada */
        queue_size = 4;
    queue_pointer created_queue;
    created_queue = (queue_pointer*)malloc(sizeof(queue)); /*!< Alocam memorie pentru coada */
    created_queue->queue_array = (queue_member *)malloc(sizeof(queue_member) * queue_size); /*!< Alocam memorie pentru membri unei cozii create */
    created_queue->memory_alloc = queue_size; /*!< Am salvat numarul de membri pentru care s-a alocat memorie */
    created_queue->number_of_members = 0; /*!< Intr-o coada noua create nu exista membri */

    return created_queue; /*!< Returnam adresa noii cozi create */
}

/**
* @param push_to_queue Este coada unde vom introduce noua valoare si prioritatea ei.
* @param value Este valoarea care urmeaza sa fie introdusa.
* @param priority Este prioritatea care urmeaza sa fie data valorii.
*/
void queue_push(queue_pointer push_to_queue, int value, int priority){

    queue_member *new_queue_member;
    int son;
    int father;

    if(push_to_queue->number_of_members >= push_to_queue->memory_alloc){ /*! In cazul in care nu exista memorie destula realocam memorie pentru coada si pentru membri ei */
        push_to_queue->memory_alloc = push_to_queue->memory_alloc * 2;
        push_to_queue->queue_array = (queue_member *)realloc(push_to_queue->queue_array, sizeof(queue_member) * push_to_queue->memory_alloc);
    }

    push_to_queue->number_of_members++; /*!< Crestem numbarul de membri cu unu in coada */
    son = push_to_queue->number_of_members - 1; /*!< Fiul este pus ultimul */
    father = (son - 1) / 2;

    while((son > 0) && (priority < push_to_queue->queue_array[father].priority)){
        push_to_queue->queue_array[son] = push_to_queue->queue_array[father]; /*!< Il mutam pe tata in jos */
        son = father; /*! Fiul ia locul tatalui */
        father = (son - 1) / 2; /*! Tatal ia noua pozitie a fiului */
    }
    printf("\nAm inserat valoarea %d cu prioritatea %d in coada pe locul %d", value, priority, son);
    push_to_queue->queue_array[son].value = value;
    push_to_queue->queue_array[son].priority = priority;

}

/**
* @param queue_to_adjust Este coada care va fi ajustata dupa ce din ea s-a retras elementul cu prioritatea cea mai mare.
*/
void queue_adjust(queue_pointer queue_to_adjust){
    int parent;  /*!< Indexul parintelui*/
    int son1; /*!< Indexul primului fiu */
    int son2; /*!< Indexul celui de-al doilea fiu */
    int i;

    parent = 0;
    son1 = 1;
    son2 = 2;

    /*! Ajustam inlantuirea pentru ca queue_array[0] va fi sters */
    do
    {
            /*! Daca exista doar un fiu sau fiul 1 are prioritate mica */
           if ((son2 > queue_to_adjust->number_of_members-1) || (queue_to_adjust->queue_array[son1].priority < queue_to_adjust->queue_array[son2].priority))
           {
               queue_to_adjust->queue_array[parent]=queue_to_adjust->queue_array[son1]; /*!< Primul fiu ia locul parintelui */
               parent = son1;
           }
           else
           {
               queue_to_adjust->queue_array[parent]=queue_to_adjust->queue_array[son2]; /*!< Al doilea fiu ia locul parintelui */
               parent = son2;
           }
           son1 = 2 * parent + 1;
           son2 = 2 * parent + 2;
    } while (son1 <= queue_to_adjust->number_of_members-1); /*!< Incheiem atunci cand parintele nu mai are nici un copil */

    /*! Realocam elementele din vector dupa ce ultimul parinte a fost pus primul */
    int size = queue_to_adjust->number_of_members;
    int current = parent + 1;
    while (current != size)
    {
        queue_to_adjust->number_of_members = current - 1;
        queue_push(queue_to_adjust, queue_to_adjust->queue_array[current].value, queue_to_adjust->queue_array[current].priority);
        current++;
    }

    queue_to_adjust->number_of_members = size-1; /*!< Cu un element mai putin in coada */

    if (queue_to_adjust->number_of_members < queue_to_adjust->memory_alloc/2 && queue_to_adjust->number_of_members >= 4)
    {
        queue_to_adjust->queue_array = realloc(queue_to_adjust->queue_array, sizeof(queue_member) * (queue_to_adjust->memory_alloc/2));
        queue_to_adjust->memory_alloc = queue_to_adjust->memory_alloc/2;
    }
}

/**
* @param queue_to_display Este coada despre care dorim sa obtinem informatii.
*/

void queue_display(queue_pointer queue_to_display){
    int i;
    printf("\nMarimea alocata cozii: %d", queue_to_display->number_of_members); ///Afiseaza marimea cozii
    printf("\nSpatiu alocat cozii: %d", queue_to_display->memory_alloc); ///Afiseaza spatiu alocat cozii
    printf("\nValorile din coada: "); ///Afiseaza valorile din coada.
    for (i = 0; i < queue_to_display->number_of_members; i++)
        printf("%d ", queue_to_display->queue_array[i].value);
    printf("\nPrioritatea valorilor: ");
    for (i = 0; i < queue_to_display->number_of_members; i++)
        printf("%d ", queue_to_display->queue_array[i].priority);
}

/**
* @param queue Coada de unde o sa retragem valoarea cu cea mai mare prioritate
* @return Valoarea care are cea mai mare prioritate
*/

int queue_pop_display(queue_pointer queue){
    int out;

    if (queue->number_of_members == 0)
    {
        printf("\nNu poti retrage dintr-o coada goala.");
        return 0;
    }


    out = queue->queue_array[0].value; /*! Daca coada nu este goala retragem valoarea cu prioritatea cea mai mare */
    return out;
}

/**
* @param queue Coada de unde o sa retragem valoarea cu cea mai mica prioritate
* @return Valoarea care are cea mai mica prioritate
*/

int queue_pop_min_display(queue_pointer queue){
    int out;

    if (queue->number_of_members == 0)
    {
        printf("\nNu poti retrage dintr-o coada goala.");
        return 0;
    }


    out = queue->queue_array[queue->number_of_members - 1].value; /*! Daca coada nu este goala retragem valoarea cu prioritatea cea mai mare */
    return out;
}

/**
* @param queue Coada de unde o sa scoatem valoarea cu cea mai mare prioritate
*/

void queue_pop(queue_pointer queue){
    int out;

    if (queue->number_of_members == 0)
    {
        printf("\nNu poti sterge dintr-o coada goala.");
        return;
    }

    out = queue->queue_array[0].value; /*! Daca coada nu este goala retragem valoarea cu prioritatea cea mai mare */
    if (queue->number_of_members == 1)
        queue->number_of_members = 0;
    else
        queue_adjust(queue);
    printf("A fost sters elementul cu cea mai mare prioritate %d.", out);
}

/**
* @param queue Coada unde vrem sa schimbam valorii date prioritatea
* @param value Valoarea pe care o cautam
* @param priority Noua prioritate
*/

void queue_change_priority(queue_pointer queue, int value, int priority){
    int i;
    for (i = 0; i < queue->number_of_members; i++)
    {
        if (queue->queue_array[i].value == value)
        {
            queue->queue_array[i].priority = priority;
            return;
        }
    }
    printf("Valoarea %d nu a putut fi gasita in coada.\n");
    return;
}

/**
* @param queue Coada unde o sa cautam valoarea
* @param data Valoarea pe care o cautam
*/

void queue_has_value(queue_pointer queue, int data){
    int i;
    for (i = 0; i < queue->number_of_members; i++)
    {
        if (queue->queue_array[i].value == data)
            printf("\nValoarea %d se gaseste in coada.", data);
    }
      printf("\nNu am gasit valoarea %d in coada.", data);
}
