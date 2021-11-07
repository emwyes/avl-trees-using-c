#include "cqueue.h"

/**********************************************************************
                        Initialize and delete queue
**********************************************************************/
/**
 * @brief Initialize and allocate memory to queue
 *
 * @return cqueue* : pointer to allocated queue
 */
cqueue *init_queue() {
    cqueue *mq = (cqueue *)calloc(sizeof(cqueue), 1);
    if (!mq) {
        errno = ENOMEM;
        exit(EXIT_SUCCESS);
    }
    mq->_head = mq->_tail = NULL;
    mq->_qsize = 0;
    return mq;
}

/**
 * @brief Delete queue and free memory for all elements and the queue
 *
 * @param[in] q : pointer to allocated queue to be freed
 */
void delete_queue(cqueue *q) {

    if (!q) {
        return;
    }

    while (q->_head) {
        cqueue_element *temp = q->_head;
        q->_head = q->_head->_next;
        delete_element(temp);
    }
    free(q);
}

/**
 * @brief Return the tree node at the start of the queue
 *
 * @param[in] q : pointer to queue
 * @return treenode* : node at front of queue
 */
treenode *front(cqueue *q) {
    if (!q || !q->_head) {
        return NULL;
    }
    return q->_head->_tree_leaf;
}

/******************* Create and Delete queue elements *******************/
/**
 * @brief Create new queue element with node value of leaf
 *
 * @param[in] leaf : leaf to insert into queue
 * @return cqueue_element* : pointer to newly created element
 */
cqueue_element *new_element(treenode *leaf) {
    cqueue_element *qnode =
        (cqueue_element *)calloc(sizeof(cqueue_element *), 1);

    qnode->_tree_leaf = leaf;
    return qnode;
}

/**
 * @brief Delete the element
 *
 * @param[in] qnode : pointer to node in queue to be deleted
 */
void delete_element(cqueue_element *qnode) {
    if (!qnode)
        return;
    free(qnode);
}

/**********************************************************************
                     Queue Insertions and Deletions
**********************************************************************/
/**
 * @brief Insert element at the head of the queue
 *
 * @param[in] q : pointer to queue
 * @param[in] leaf : node of tree to insert into queue
 */
void push_queue_head(cqueue *q, treenode *leaf) {

    if (!q) {
        return;
    }
    cqueue_element *new_head_element = new_element(leaf);

    // if queue is empty
    if (!q->_head && !q->_tail) {
        q->_head = q->_tail = new_head_element;
    }
    // if not empty
    else if (q->_qsize > 0) {
        new_head_element->_next = q->_head;
        q->_head->_prev = new_head_element;
        q->_head = new_head_element;
    }
    q->_qsize++;
}

/**
 * @brief Insert element at the end of the queue
 *
 * @param[in] q : pointer to queue
 * @param[in] leaf : node of tree to insert into queue
 */
void push_queue_tail(cqueue *q, treenode *leaf) {

    if (!q) {
        return;
    }
    cqueue_element *new_tail_element = new_element(leaf);

    // if queue is empty
    if (!q->_qsize) {
        q->_head = q->_tail = new_tail_element;
    }
    // if not empty
    else if (q->_qsize > 0) {
        new_tail_element->_prev = q->_tail;
        q->_tail->_next = new_tail_element;
        q->_tail = new_tail_element;
    }

    q->_qsize++;
}

/**
 * @brief Remove element from the queue front
 *
 * @param[in] q	: pointer to queue
 */
void pop_queue_head(cqueue *q) {

    if (!q || (!q->_head && !q->_tail)) {
        return;
    }

    cqueue_element *remove = q->_head;
    // only one element in the queue
    if (q->_qsize == 1) {
        q->_head = q->_tail = NULL;
    }
    // more than one element
    else if (q->_qsize > 1) {
        q->_head = q->_head->_next;
        q->_head->_prev = NULL;
    }
    q->_qsize--;
    delete_element(remove);
}

/**
 * @brief Remove element from the queue tail
 *
 * @param[in] q	: pointer to queue
 */
void pop_queue_tail(cqueue *q) {

    if (!q || (!q->_head && !q->_tail)) {
        return;
    }

    cqueue_element *remove = q->_head;
    // only one element in the queue
    if (q->_qsize == 1) {
        q->_head = q->_tail = NULL;
    }

    // more than one element
    else if (q->_qsize > 1) {
        q->_tail = q->_tail->_prev;
        q->_tail->_next = NULL;
    }
    q->_qsize--;
    delete_element(remove);
}