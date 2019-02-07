#include "tldlist.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tldlist TLDList;
typedef struct tldnode TLDNode;
typedef struct tlditerator TLDIterator;


struct tldnode{
    char *tld_name;
    int count;
    struct tldnode *left, *right, *parent;
};

struct tldlist{
    Date *head;
    Date *tail;
    int count;
    int size;
};

struct tlditerator{
    struct tldlist *tld;
    struct tldnode *nodes;
};
/*
 * Author: Ross Angus, 2244073A
 * SP Exercise 1)
 * “This is my own work as defined in the Academic Ethics agreement"
 *
 * I'm going to comment this file a fair amount to try
 * to figure out how I can get it to work. I'm going to leave
 * in the comments as I find it useful when viewing
 * someone else's code and I'll be referring to this task for
 * the second coursework(probably). I accept that my volume of code
 * isn't substantial, I do not mean to use this to make it seem
 * larger than it is.
 */

/*
 * tldlist_create generates a list structure for storing counts against
 * top level domains (TLDs)
 *
 * creates a TLDList that is constrained to the `begin' and `end' Date's
 * returns a pointer to the list if successful, NULL if not
 */


TLDList *tldlist_create(Date *begin, Date *end) {

    /*create tld as pointer to list, assign memory of size node.
     * split into 2 lines to ensure pointer is set to NULL as
     * im unsure if a new pointer starts as NULL*/
    TLDList* tld = (TLDList*) malloc(sizeof(TLDNode));

    /*return NULL if unsuccessfull
     * otherwise create a list
     * hmmm.. should size be 0 or 2
     * because of the head & tail? */
    if (tld == NULL) {
        free(tld);
        return NULL;
    }else{
        /* call date duplicate to set head and tail vals */
        tld->size = 0;
        tld->head = date_duplicate(begin);
        tld->tail = date_duplicate(end);
    }
    /*error control may reach end of non void function*/
    return tld;
}
/*
 * tldlist_destroy destroys the list structure in `tld'
 * all heap allocated storage associated with the list is returned to the heap
 */
void tldlist_destroy(TLDList *tld){

    /*if the pointer isn't NULL create pointer to node
     * and create pointer to iteration to delete whole list */
    if (tld != NULL) {
        TLDIterator *iter = tldlist_iter_create(tld);
        TLDNode *current;

        /*if the next value is something, delete the current value
         * should loop until reaches tail as tail->next = NULL*/
        while ((current = tldlist_iter_next(iter)) != NULL) {
            free(current->tld_name);
            free(current);
        }
        /*delete pointers*/
        free(tld);
        tldlist_iter_destroy(iter);
    }
}

/*
 * tldlist_add adds the TLD contained in `hostname' to the tldlist if
 * `d' falls in the begin and end dates associated with the list;
 * returns 1 if the entry was counted, 0 if not
 */
int tldlist_add(TLDList *tld, char *hostname, Date *d) {

    TLDNode *node = (TLDNode *)malloc(sizeof(TLDNode));
    TLDList *current = tld;

    /*setup for later recursion*/
    char* hostname_recursion = hostname;
    Date* date_recursion = d;

    /*ok this is where it gets funky.
     * using date.c method compare dates
     * so: if head is greater than date it'll score 1 and should return 0, no?
     * and if tail is greater than date it will do the same, this means d must fall
     * inbetween these values*/
    if (date_compare(tld->head, d) || date_compare(tld->tail, d)) {
        return 0;
        /*if the head value is empty then increment the list size
         * and set the name at the current location to the given string*/
    }else if (tld->head == NULL) {
        tld->size++;
        node->tld_name = hostname;
        /*if the current location pointed to by size isn't empty then increment*/
    }else if (current->size != '\0') {
        tld->size++;
        /*or if the current location is empty, add here */
    }else if (current->size == '\0') {
        node->tld_name= hostname;
    }else{
        /*recurse if not added*/
        tldlist_add(tld, hostname_recursion, date_recursion);
    }
    /*count for tldlist_count &
     *error control may reach end of non void function*/
    tld-> count++;
    return 0;
}

/*
 * tldlist_count returns the number of succe    `ssful tldlist_add() calls since
 * the creation of the TLDList
 */
long tldlist_count(TLDList *tld){
    /* pretty self explanatory */
    return tld -> count;
};
/*
 * tldlist_iter_create creates an iterator over the TLDList; returns a pointer
 * to the iterator if successful, NULL if not
 */
TLDIterator *tldlist_iter_create(TLDList *tld){

    /*usual, create pointers of appropriate size */
    TLDNode *node = (TLDNode *)malloc(sizeof(TLDNode));
    TLDIterator *iter = (TLDIterator *)malloc(sizeof(TLDIterator));
    char *hostname = NULL;
    Date *d = NULL;

    /*surely the iter will begin as NULL?
     * hmmm */
    if (iter == NULL){
        return NULL;
    }else{
        /* set hostname to begin at the value after the '.' which should represent the tld including the '.' ie. '.de' */
        hostname = strrchr(node->tld_name, '.');
        /* set d to the value created by date_create */
        d = date_create(hostname);
        /* try to add to list*/
        tldlist_add(tld, hostname, d);
    }
    /*increment node counter & again
     * error control may reach end of non void function -_- */
    node->count++;
    return 0;
}
/*
 * tldlist_iter_next returns the next element in the list; returns a pointer
 * to the TLDNode if successful, NULL if no more elements to return
 */
TLDNode *tldlist_iter_next(TLDIterator *iter){

    /* sort of setting temp to represent a blank node*/
    TLDNode *temp = iter->nodes;

    /*This was just a very brief touch on the BST
     * I dont claim this to be even vaguely workable */

    /*again, will probably start as NULL...*/
    if(temp == NULL){
        return NULL;
        /*if the parent is occupied, clearly dont place it there*/
    }else while(temp->parent != NULL){
        /*if the left is empty, say that this node is available*/
        if (temp->parent->left == NULL) {
            temp = temp->parent->left;
            /* if right, say right available */
        }else {
            temp = temp->parent->right;
        }
    }
    /*return available location*/
    return temp;
}
/*
 * tldlist_iter_destroy destroys the iterator specified by `iter'
 */
void tldlist_iter_destroy(TLDIterator *iter){
    free(iter);
}
/*
 * tldnode_tldname returns the tld associated with the TLDNode
 */
char *tldnode_tldname(TLDNode *node) {
    return node->tld_name;
}
/*
 * tldnode_count returns the number of times that a log entry for the
 * corresponding tld was added to the list
 */
long tldnode_count(TLDNode *node) {
    return node->count;
}


