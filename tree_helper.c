#include "cqueue.h"
#include "tree.h"
/**********************************************************************
                           Print Functions
**********************************************************************/

/**
 * @brief Prints the information of a node
 *
 * @param[in] node : node in a tree
 * @param[in] m : printing mode
 */
void print_node(treenode *node, mode m) {

    if (m == S) {
        printf("%d ", node->val);
    } else if (m == V) {
        printf("\n");
        printf("Value in node: %d\n", node->val);
        printf("Node at address: %p\n", node);
        printf("Height: %d\n", node->height);
        printf("Parent address: %p\n", node->parent);
        printf("Left child address: %p\n", node->left);
        printf("Right child address: %p\n", node->right);
        printf("Balance Factor: %d", get_balance_factor(node));
        printf("\n");
    }
}

/**
 * @brief Recursive inorder traversal printing of nodes
 *
 * @param[in] root : root of tree
 * @param[in] m : mode of printing
 */
void print_inorder(treenode *root, mode m) {

    if (!root)
        return;
    print_inorder(root->left, m);
    print_node(root, m);
    print_inorder(root->right, m);
}

/**
 * @brief Recursive preorder traversal printing of nodes
 *
 * @param[in] root :  root of tree
 * @param[in] m : mode of printing
 */
void print_preorder(treenode *root, mode m) {

    if (!root)
        return;
    print_node(root, m);
    print_inorder(root->left, m);
    print_inorder(root->right, m);
}

/**
 * @brief Breadth first traversal and printing. Uses a Queue
 *
 * @param[in] root : Root node of tree
 */
void print_breadth_first(treenode *root) {
    if (!root)
        return;

    cqueue *q = init_queue();

    push_queue_tail(q, root);
    push_queue_tail(q, NULL);

    printf("\n");
    while (q->_qsize > 0) {
        treenode *temp = front(q);
        pop_queue_head(q);

        if (temp) {
            if (temp->left) {
                push_queue_tail(q, temp->left);
            }
            if (temp->right) {
                push_queue_tail(q, temp->right);
            }

            print_node(temp, S);
        }

        if (!front(q)) {
            push_queue_tail(q, NULL);
            pop_queue_head(q);
            printf("\n");
        }
    }

    delete_queue(q);
}

/**********************************************************************
                        Tree Allocation Functions
**********************************************************************/

/**
 * @brief Allocate, initialize and return a new node
 *
 * @param[in] val : value to insert into tree
 * @return treenode*
 */
treenode *new_node(int val) {

    treenode *newptr = (treenode *)calloc(sizeof(treenode), 1);

    if (!newptr) {
        errno = ENOMEM;
        exit(-1);
    }
    newptr->val = val;
    return newptr;
}

/**
 * @brief Free the memory by recursively deleting the tree
 *
 * @param[in] root : root of tree
 */
void delete_tree(treenode *root) {
    if (!root)
        return;

    delete_tree(root->left);
    delete_tree(root->right);
    root->parent = NULL;
    free(root);
}

/**
 * @brief Insert a node into the tree and balance the tree
 *
 * @param[in] root : root of the tree
 * @param[in] val : value to be inserted
 * @return treenode* : return the root (fater balancing the tree)
 */
treenode *insert(treenode *root, int val) {

    if (!root) {
        return new_node(val);
    }

    if (val < root->val) {
        root->left = insert(root->left, val);
        root->left->parent = root;
    } else if (val > root->val) {
        root->right = insert(root->right, val);
        root->right->parent = root;
    }

    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    root = balance(root);
    return root;
}

/**********************************************************************
                     Getters and setters for height
**********************************************************************/

/**
 * @brief Get the height of the node. Checks for root being null
 *
 * @param[in] root : root whose height is to be retrieved
 * @return int : height
 */
int get_height(treenode *root) {
    if (!root)
        return 0;
    return root->height;
}

/**
 * @brief Get the balance factor of root i.e
 *        height of left subtree - height of right subtree
 *
 * @param[in] root : node whose balancing factor is to be retrived
 * @return int : balance factor
 */
int get_balance_factor(treenode *root) {

    int left_height = (root->left) ? root->left->height + 1 : 0;
    int right_height = (root->right) ? root->right->height + 1 : 0;

    return left_height - right_height;
}

/**
 * @brief Update height of the current node depending upon the heights of the
 * left and right subtrees.
 *
 * This functionis used after there are rotations in a tree.
 *
 * @param[in] root : node of tree to update the height of
 * @return int : updated height
 */
int update_height(treenode *root) {

    if (!root->left && !root->right) {
        return 0;
    } else {
        return max(get_height(root->left), get_height(root->right)) + 1;
    }

    return -1;
}

/**********************************************************************
                        Rotation functions
**********************************************************************/

/**
 * @brief Right rotation in a tree
 *
 *      |       |
 *      X       Y
 *     /   ->    \
 *    Y           X
 *
 * @param[in] root : root of subtree be rotated
 * @return treenode* : updated root after rotation
 */
treenode *right_rotate(treenode *root) {
    treenode *leftchild = root->left;
    root->left = leftchild->right;
    leftchild->parent = root->parent;
    root->parent = leftchild;

    if (leftchild->right) {
        leftchild->right->parent = root;
    }

    leftchild->right = root;
    root->height = update_height(root);
    leftchild->height = update_height(leftchild);

    return leftchild;
}

/**
 * @brief Left rotation of a tree node and its child
 *
 *    |          |
 *    X          Y
 *     \   ->   /
 *      Y      X
 *
 * @param[in] root : root of subtree be rotated
 * @return treenode* : updated root after rotation
 */
treenode *left_rotate(treenode *root) {
    treenode *rightchild = root->right;
    root->right = rightchild->left;
    rightchild->parent = root->parent;
    root->parent = rightchild;

    if (rightchild->left) {
        rightchild->left->parent = root;
    }
    rightchild->left = root;
    root->height = update_height(root);
    rightchild->height = update_height(rightchild);
    return rightchild;
}

/**
 * @brief Left-Right rotation
 *
 *      |              |              |
 *      X              X              Z
 *     /              /              / \
 *    Y     ->       Z       ->     Y   X
 *     \            /
 *      Z          Y
 *
 * @param[in] root : root of subtree be rotated
 * @return treenode* : updated root after rotation
 */
treenode *lr_rotate(treenode *root) {
    root->left = left_rotate(root->left);
    return right_rotate(root);
}

/**
 * @brief Right-Left rotation
 *
 *      |              |               |
 *      X              X               Z
 *       \              \             / \
 *        Y     ->       Z       ->  X   Y
 *       /                \
 *      Z                  Y
 *
 * @param[in] root : root of subtree be rotated
 * @return treenode* : updated root after rotation
 */
treenode *rl_rotate(treenode *root) {
    root->right = right_rotate(root->right);
    return left_rotate(root);
}

/**
 * @brief Balance the tree depending upon the balancing factors
 *
 * @param[in] root : root of subtree to be balanced
 * @return treenode* : updated root after balancing subtree
 */
treenode *balance(treenode *root) {

    int bal_factor = get_balance_factor(root);

    if (bal_factor == 2) {
        int left_bal_factor = get_balance_factor(root->left);
        if (left_bal_factor == 1) {
            root = right_rotate(root);
        } else if (left_bal_factor == -1) {
            root = lr_rotate(root);
        }

    } else if (bal_factor == -2) {
        int right_bal_factor = get_balance_factor(root->right);
        if (right_bal_factor == -1) {
            root = left_rotate(root);
        } else if (right_bal_factor == 1) {
            root = rl_rotate(root);
        }
    }
    return root;
}