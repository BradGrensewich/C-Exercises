#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct node {
    int number;
    struct node *next;
} node;

node *insert (int num, node *list);
node *sorted_insert(int num, node *list);
int delete (int target, node *list);
int search_list(int target, node *list);
int get_random_number();
void free_list(node *list);
void print_list(node *list);

int main (void) {
    srand(time(NULL));
    node *list = NULL;

    for (int i = 0; i < 10; i++) {
        int num = get_random_number();        
        node *tmp = sorted_insert(num, list);
        if (tmp == NULL) {
            printf("Error inserting into list\n");
            free_list(list);
            return 1;
        } else {
            list = tmp;
        }
    }

    print_list(list);
    free_list(list);
    return 0;

}

//returns pointer to head, returns NULL on failure
node *insert (int num, node *list) {
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->number = num;
    new_node->next = NULL;

    //empty list
    if (list == NULL) {
        list = new_node;
        return list;
    } else {
        for (node *ptr = list; ptr != NULL; ptr = ptr->next) {           
            if (ptr->next == NULL) {
                ptr->next = new_node;
                return list;
            }
        }
    }
    //somehow something goes wrong
    return NULL;
}
//returns pointer to head, returns NULL on failure
node *sorted_insert (int num, node *list) {
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->number = num;
    new_node->next = NULL;
    
    //empty list or number belongs at start of list
    if (list == NULL || new_node->number < list->number) {
        new_node->next = list;
        list = new_node;
        return list;    
    //middle or end
    } else {
        for (node *ptr = list; ptr != NULL; ptr = ptr->next) {
            //belongs in middle
            if (ptr->next != NULL && new_node->number < ptr->next->number) {
                new_node->next = ptr->next;
                ptr->next = new_node;
                return list;
            }
            //end of list           
            if (ptr->next == NULL) {
                ptr->next = new_node;
                return list;
            }
        }
    }
    //somehow something goes wrong
    return NULL;
}

//TODO
int delete (int target, node *list) {

}

//TODO
int search_list(int target, node *list) {
    return 0;
}

//returns int from 1-100
int get_random_number() {
   int random_number = rand() % 100 + 1; 
   return random_number;
   
}

void free_list(node *list) {
    while (list != NULL) {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }

}

void print_list(node *list) {    
    printf("List: ");
    for (node *ptr = list; ptr != NULL; ptr = ptr->next) {
        printf("%d ", ptr->number);
    }
    printf("\n");
}