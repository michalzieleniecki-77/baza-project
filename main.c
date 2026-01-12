#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "survivor.h"

int main(void) {
    Node* head = NULL;
    int choice = -1;

    while (choice != 0) {
        printf("\n----Base 17----\n");
        printf("1. Register a new survivor\n");
        printf("2. Search for a survivor\n");
        printf("3. Modify survivor\n");
        printf("4. Sort list of survivors\n");
        printf("5. Remove survivor\n");
        printf("6. Save from file\n");
        printf("7. Read from file\n");
        printf("8. Close program.\n");

        if(scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while(getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1: {
                Survivor newSurvivor = get_survivor_data();
                push(&head, newSurvivor);
                printf("New survivor succesfully added\n");
            }
            case 8: {
                printf("Goodbye...");
                return 0;
            }
            default: {
                printf("\nWRONG!! CHOOSE NUMBER BETWEEN 1-8!\n");
            }
        }
    }
    free_list(head);
    return 0;
}
