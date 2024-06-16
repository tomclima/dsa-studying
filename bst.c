#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define endl \n

const int ERROR = -1111111111;


typedef struct bst_node{
    int key;
    int element;
    int height;
    struct bst_node *left;
    struct bst_node *right;
} bst_node;

bst_node *create_bstnode(int key, int element){
    bst_node *node = (bst_node*)malloc(sizeof(bst_node)*1);
    node->key = key;
    node->element = element;
    node->left = NULL;
    node->right = NULL;

    return node;
}

typedef struct bst_tree{
    bst_node *root;
    int nodecount;
} bst_tree;

bst_tree *create_bst(){
    bst_tree *tree = (bst_tree*)malloc(sizeof(bst_tree)*1);
    tree->root = NULL;
    tree->nodecount = 0;

    return tree;
}

int* bst_findhelp(bst_node *rt, int key){
    if(!rt){return NULL;}
    if(rt->key > key){return bst_findhelp(rt->left, key);};
    if(rt->key < key){return bst_findhelp(rt->right, key);}
    
    else{return &(rt->element);};
}

int* bst_find(bst_tree *tree, int key){
    return bst_findhelp(tree->root, key);
}

int bst_getheight(bst_node *rt){
    if(!rt){return -1;}
    else{return rt->height;}
}

int bst_getbalance(bst_node *rt){
    if(!rt){return 0;}
    else{
        return (bst_getbalance(rt->left) - bst_getheight(rt->right));
    }
}

bst_node *bst_rightrotate(bst_node *rt){
    bst_node *l = rt->left;
    bst_node *lr = l->right;

    l->right = rt;
    rt->left = lr;
    rt->height = 1 + max(bst_getheight(rt->left), bst_getheight(rt->right->height));
    l->height = 1 + max(bst_getheight(l->left), bst_getheight(l->right->height));

    return l;
}

bst_node *bst_leftrotate(bst_node *rt){
    bst_node *r = rt->right;
    bst_node *rl = r->left;

    r->left = rt;
    rt->right = rl;
    rt->height = 1 + max(bst_getheight(rt->left), bst_getheight(rt->right->height));
    r->height = 1 + max(bst_getheight(r->left), bst_getheight(r->right->height));
    return r;
}




bst_node *bst_inserthelp(bst_node *rt, int key, int element){
    if(!rt){return create_bstnode(key, element);};
    if(rt->key > key){
        rt->left = bst_inserthelp(rt->left, key, element);
    }
    else{
        rt->right = bst_inserthelp(rt->right, key, element);
    }
    
    rt->height = 1 + max(bst_getheight(rt->left), bst_getheight(rt->right->height)); 

    int balance = bst_getbalance(rt);
    if(balance < -1 && key > rt->right->key){return bst_leftrotate(rt);}
    if(balance > 1 && key < rt->left->key){return bst_rightrotate(rt);}
    if(balance > 1 && key > rt->left->key){
        rt->left = bst_leftrotate(rt->left);
        return bst_rightrotate(rt);
    }
    else {
        rt->right = bst_rightrotate(rt->right);
        return bst_leftrotate(rt);
    }
    return rt;
}


void bst_insert(bst_tree *bst, int key, int element){
    bst->root = bst_inserthelp(bst->root, key, element);
    bst->nodecount++;
}

bst_node *bst_getmin(bst_node *rt){
    if(!rt->left){return rt;}
    else{
        return getmin(rt->left);
    }
}

bst_node *bst_deletemin(bst_node *rt){
    if(!rt->left){return rt;}
    else{
        rt->left = bst_deletemin(rt->left);
    }
    return rt;
}

bst_node *bst_getmax(bst_node *rt){
    if(rt->right){return rt;}
    else{return bst_getmax(rt->right);}
}

bst_node *bst_deletemax(bst_node *rt){
    if(!rt->right){return rt;}
    else{rt->right = bast_deletemax(rt->right);}
    return rt;
}


bst_node *bst_removehelp(bst_node *rt, int key){
    if(!rt) {return NULL;}
    if(rt->key>key){rt->left = bst_removehelp(rt->left, key);}
    if(rt->key<key){rt->left = bst_removehelp(rt->right, key);}
    else{
        if(!rt->left){return rt->right;}
        if(!rt->right){return rt->left;}
        else{
            bst_node *temp = bst_getmin(rt->right);
            rt->element = temp->element;
            rt->key = temp->key;
            rt->right = bst_deletemin(rt->right);
        }
    }

    rt->height = 1 + max(bst_getheight(rt->left), bst_getheight(rt->right->height));
    int balance = bst_getbalance(rt);

    if(balance < -1 && key > rt->right->key){return bst_rightrotate(rt);}
    if(balance > 1 && key > rt->right->key){return bst_leftrotate(rt);}
    if(balance > 1 && key > rt->left->key){
        rt->left = bst_rightrotate(rt->left);
        return bst_leftrotate(rt);
    }
    else {
        rt->right = bst_leftrotate(rt->right);
        return bst_rightrotate(rt);
    }
    return rt;
}


int* bst_remove(bst_tree *bst, int key){
    int *temp = bst_findhelp(bst->root, key);
    int value;

    if(temp != NULL){
        bst->root = bst_removehelp(bst->root, key);
        bst->nodecount--;
    }
    else{
        value = ERROR;
    }
    return value;
}


void bst_preorder(bst_node *rt){
    if(rt){
        printf(" %d", rt->key);
        bst_preorder(rt->left);
        bst_preorder(rt->right);
    }
}

void bst_posorder(bst_node *rt){
    if(rt){
        bst_posorder(rt->left);
        bst_posorder(rt->right);
        printf(" %d", rt->key);
    }
}

void bst_inorder(bst_node *rt){
    if(rt){
        bst_inorder(rt->left);
        printf(" %d", rt->key);
        bst_inorder(rt->right);
    }
}



int main(void){
    bst_tree *tree = create_bst();
    
    
}

