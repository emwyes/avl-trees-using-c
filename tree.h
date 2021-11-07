#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef TREE_H_INCLUDED
#define TREE_H_INCLUDED

#define max(a, b) ((a < b) ? b : a)

/**
 * @brief Print mode
 *
 *  S - Simple printing: prints only the value at the node
 *  V - Verbose printing: prints all information at a node
 *
 */
typedef enum mode { S, V } mode;

/**
 * @brief Main tree node structure
 *
 */
typedef struct node {
    int val;
    int height;
    struct node *parent;
    struct node *right;
    struct node *left;
} treenode;

/********************** Printing functions **********************/
void print_node_info(treenode *, mode);
void print_inorder(treenode *, mode);
void print_preorder(treenode *, mode);
void print_breadth_first(treenode *);

/******************* Allocate and Free memory *******************/
treenode *new_node(int);
void delete_tree(treenode *);
treenode *insert(treenode *, int);

/************************* Get and Set *************************/
int get_balance_factor(treenode *);
int get_height(treenode *);
int update_height(treenode *root);

/************************** Rotations ***************************/
treenode *right_rotate(treenode *);
treenode *left_rotate(treenode *);
treenode *lr_rotate(treenode *);
treenode *rl_rotate(treenode *);
treenode *balance(treenode *);

#endif