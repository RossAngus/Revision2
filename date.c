
#include "date.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * Author: Ross Angus, 2244073A
 * SP Exercise 1)
 * “This is my own work as defined in the Academic Ethics agreement"
 */

struct date {
    int d;
    int m;
    int y;
};

/*
 * date_create creates a Date structure from `datestr`
 * `datestr' is expected to be of the form "dd/mm/yyyy"
 * returns pointer to Date structure if successful,
 *         NULL if not (syntax error)
 */
Date *date_create(char *datestr){
    Date dates = {};
    Date* date = (Date*) malloc(sizeof(Date));

    sscanf(datestr,"%n/%n/%n;", &dates.d, &dates.m, &dates.y);

    if (date!=NULL) {
        return date;
    }else{
        return NULL;
    }
}

/*
 * date_duplicate creates a duplicate of `d'
 * returns pointer to new Date structure if successful,
 *         NULL if not (memory allocation failure)
 */
Date *date_duplicate(Date *d){

    Date *date = malloc(sizeof(Date));

    if (d == NULL){
        return NULL;
    }else{
        date->d = d->d;
        date->m = d->m;
        date->y = d->y;
        return date;
    }
}


/*
 * date_compare compares two dates, returning <0, 0, >0 if
 * date1<date2, date1==date2, date1>date2, respectively
 */

int date_compare(Date *date1, Date *date2){

    /* i know this is ugly, but it should work (year>year, (year=year, month>month), (year=year, month=month, day > day))*/

    if (date1->y > date2->y || (date1->y == date2->y && date1->m > date2->m) || (date1->y == date2->y && date1->m == date2->m && date1->d > date2->d) ) {
        return 1;
    }else if (date1->y < date2->y || (date1->y == date2->y && date1->m < date2->m) || (date1->y == date2->y && date1->m == date2->m && date1->d < date2->d) ) {
            return -1;
    }else{
        return 0;
    }

}

/*
 * date_destroy returns any storage associated with `d' to the system
 */
void date_destroy(Date *d){
    free(d);
/* _DATE_H_INCLUDED_ */
}
