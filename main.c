#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "survivor.h"

int main(void) {
    Node* head = NULL;
    int choice = -1;
    load_from_file(&head, "survivors.txt");

    while (choice != 0) {
        printf("\n----------Base 17----------\n");
        printf("1. Register a new survivor\n");
        printf("2. Display list of survivors\n");
        printf("3. Search for a survivor\n");
        printf("4. Modify survivor\n");
        printf("5. Sort list of survivors\n");
        printf("6. Remove survivor\n");
        printf("7. Save to file\n");
        printf("8. Read from file\n");
        printf("0. Close program.\n");
        printf("-----------------------------\n");

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
                break;
            }

            case 2: {
                display_list(head);
                break;
            }

            case 3: {
                char searched[100];
                
                printf("Search for a survivor: ");
                scanf("%99s", searched);
                Node* result = search_survivor(head, searched);
                if (result != NULL) {
                    printf("\nSurvivor found\n");
                    printf("Name: %s | Skill: %d | Food: %d | Health: %d | Danger: %d | Status: %d |\n",
                            result->data.name, result->data.skill, result->data.food, result->data.health, result->data.danger, result->data.status);
                } else {
                    printf("Survivor %s not found in the base\n", searched);
                }
                
                break;
            }

            case 4: {
                modify_survivor(head);
                break;
            }

            case 5: {
                if (head == NULL) { 
                    printf("The list is empty\n");
                    break;
                }

                printf("\nSort survivors by:\n");
                printf("1. Name (A-Z)\n");
                printf("2. Danger level (Highest to Lowest)\n");
                printf("Choice: ");

                int sort_choice;
                if (scanf("%d", &sort_choice) != 1) {
                    while (getchar() != '\n');
                    break;
                }
                if (sort_choice == 1) {
                    sort_by_name(head);
                } else if (sort_choice == 2) {
                    sort_by_danger(head);
                } else {
                    printf("Invalid sort choice.\n");
                }
                break;
            }

            case 6: {
                remove_survivor(&head);
                break;
            }

            case 7: {
                save_to_file(head, "survivors.txt");
                printf("Data saved to survivors.txt\n");
                break;
            }
            
            case 8: {
                if(head != NULL) {
                    free_list(head);
                    head = NULL;
                }
                load_from_file(&head, "survivors.txt");
                break;
            }

            case 0: {
                printf("Goodbye...");
                return 0;
                break;
            }
            
            default: {
                printf("\nWRONG!! CHOOSE NUMBER BETWEEN 1-8!\n");
                break;
            }
        }
    }
    free_list(head);
    return 0;
}
