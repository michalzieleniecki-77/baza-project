#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "survivor.h"

Node* create_node(Survivor data);

int main(void) {
    //Survivor survivor[] = {{"Michal", MECHANIC, 60, 99, 8, ACTIVE}};
    //printf("Hello %s, wec can tell that you are %s.", survivor[0].name, (survivor[0].danger < 7) ? "not dangerous, you can join to us" : "dangerous, you have to go away");
    Survivor michal = {"Michal", MECHANIC, 60, 99, 2, ACTIVE};
    Node* head = create_node(michal);
    printf("%s", head->data.name);
}

Node* create_node(Survivor data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        return NULL; 
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}