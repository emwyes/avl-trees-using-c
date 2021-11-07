#include "tree.h"

#define PRINTMODE S

int main(int argc, char **argv) {

    treenode *tree = NULL;

    for (int i = 5; i < 100; i += 11) {
        tree = insert(tree, i);
    }

    print_inorder(tree, PRINTMODE);
    print_breadth_first(tree);
    delete_tree(tree);

    return 0;
}