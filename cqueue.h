/**
 * @file cqueue.h
 * @author  Mukul Sakhalkar
 * @brief Queue implementation using a doubly linked list. The queue stores
 * treenodes.
 * @version 0.1
 * @date 2021-11-07
 *
 */

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef CQUEUE_H_INCLUDED
#define CQUEUE_H_INCLUDED

/**
 * @brief List element in queue
 * Queue is based on a douby linked list.
 *
 */
typedef struct cqueue_element {
    treenode *_tree_leaf;
    struct cqueue_element *_next;
    struct cqueue_element *_prev;
} cqueue_element;

/**
 * @brief Queue data structure
 *
 */
typedef struct cqueue {
    cqueue_element *_head;
    cqueue_element *_tail;
    size_t _qsize;
} cqueue;

/************ Functions to initialize and free queue and elements ************/
cqueue *init_queue();
void delete_queue(cqueue *q);
cqueue_element *new_element(treenode *);
void delete_element(cqueue_element *);

treenode *front(cqueue *);

/********************** Insertion and Deletion **********************/
void push_queue_head(cqueue *, treenode *);
void push_queue_tail(cqueue *, treenode *);
void pop_queue_head(cqueue *);
void pop_queue_tail(cqueue *);

#endif