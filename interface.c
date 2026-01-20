#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "survivor.h"

Node* create_node(Survivor data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) return NULL;
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

void push(Node** head_ref, Survivor new_data) {
    Node* new_node = create_node(new_data);
    if (new_node == NULL) return;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

Survivor get_survivor_data(void) {
    Survivor survivor;
    int choice;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    //Getting name
    printf("Enter name: ");
    if(fgets(survivor.name, sizeof(survivor.name), stdin)) {
        survivor.name[strcspn(survivor.name, "\n")] = 0;
    }

    //Getting skill
    printf("Enter skill (0:MEDIC, 1:ENGINEER, 2:SCOUT, 3:TECHNICIAN, 4:BIOLOGIST, 5:MECHANIC): ");
    scanf("%d", &choice);
    survivor.skill = (SurvivorSkill)choice;

    //Getting food lvl
    printf("Enter food rations (0-100): ");
    scanf("%d", &survivor.food);

    //Getting health
    printf("Enter health level (0-100): ");
    scanf("%d", &survivor.health);
    
    //Getting danger level
    printf("Enter danger level (0-10): ");
    scanf("%d", &survivor.danger);

    //Getting status
    printf("Enter status (0:ACTIVE, 1:SICK, 2:INJURED, 3:OUTSIDE, 4:MISSING): ");
    scanf("%d", &choice);
    survivor.status = (SurvivorStatus)choice;

    while ((c = getchar()) != '\n' && c != EOF);

    return survivor;
}

const char* get_skill_name(SurvivorSkill skill) {
    switch(skill) {
        case MEDIC: return "MEDIC";
        case ENGINEER: return "ENGINEER";
        case SCOUT: return "SCOUT";
        case TECHNICIAN: return "TECHNICIAN";
        case BIOLOGIST: return "BIOLOGIST";
        case MECHANIC: return "MECHANIC";
        default: return "UNKNOWN";
    }
}

const char* get_status_name(SurvivorStatus status) {
    switch(status) {
        case ACTIVE: return "ACTIVE";
        case SICK: return "SICK";
        case INJURED: return "INJURED";
        case OUTSIDE: return "OUTSIDE";
        case MISSING: return "MISSING";
        default: return "UNKNOWN";
    }
}
void display_list(Node* head) {
    Node* current = head;

    if(current == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("\n---------------------------------------------Survivors List---------------------------------------------\n");
    while(current != NULL) {
        printf("Name: %-10s | Skill: %-10s | Food: %3d | Health: %3d | Danger: %2d | Status: %s\n", 
                current->data.name, 
                get_skill_name(current->data.skill),
                current->data.food,
                current->data.health,
                current->data.danger,
                get_status_name(current->data.status));
        current = current->next;
    }
    printf("----------------------------------------------------------------------------------------------------\n");
}

void free_list(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
}

void save_to_file(Node* head, const char* filename) {
    if (head == NULL) {
        printf("\nWARNING: Current list is empty! Saving will erase your file\n");
        printf("Are you sure? (1-Yes / 0-No): ");
        int confirm;
        if (scanf("%d", &confirm) != 1 || confirm != 1) {
            printf("Save aborted. Your file is safe\n");
            return;
        }
    }
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!!");
        return;
    }

    Node* current = head;
    int counter = 0;
    while (current != NULL) {
        fprintf(file, "%s;%d;%d;%d;%d;%d\n",
            current->data.name,
            (int)current->data.skill,
            current->data.food,
            current->data.health,
            current->data.danger,
            (int)current->data.status
        );
        current = current->next;
        counter++;
    }
    fclose(file);
    printf("%d record/s saved\n", counter);
}

void load_from_file(Node** head_ref, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error");
        return;
    }

    Survivor data;
    int s, st; //skill, status
    int counter = 0;
    while (fscanf(file, " %99[^;]; %d; %d; %d; %d; %d\n", 
            data.name, &s, &data.food, &data.health, &data.danger, &st) == 6) {
                data.skill = (SurvivorSkill)s;
                data.status = (SurvivorStatus)st;
                push(head_ref, data);
                counter++;
            }
            fclose(file);
            printf("%d records loaded\n", counter);
}

Node* search_survivor(Node* head, const char* searched_name) {
    Node* current = head;

    while (current != NULL) {
        if(strcmp(current->data.name, searched_name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void modify_survivor(Node* head) {
    char name_to_find[100];
    int c;
    while((c = getchar()) != '\n' && c != EOF);

    printf("Enter the name of survivor you want to modify: ");
    if(fgets(name_to_find, sizeof(name_to_find), stdin)) {
        name_to_find[strcspn(name_to_find, "\n")] = 0;
    }

    Node* target = search_survivor(head, name_to_find);

    if(target == NULL) {
        printf("Survivor %s not found", name_to_find);
        return;
    }

    int choice;
    printf("\nModifying data for: %s\n", target->data.name);
    printf("1. Health (%d)\n", target->data.health);
    printf("2. Food rations (%d)\n", target->data.food);
    printf("3. Status (%s)\n", get_status_name(target->data.status));
    printf("4. Danger level (%d)\n", target->data.danger);
    printf("0. Cancel\n");
    printf("Choose what to change: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("New health (0-100): ");
            scanf("%d", &target->data.health);
            break;
        case 2:
            printf("New food rations (0-100): ");
            scanf("%d", &target->data.food);
            break;
        case 3:
            printf("New status (0:ACTIVE, 1:SICK, 2:INJURED, 3:OUTSIDE, 4:MISSING): ");
            int new_status;
            scanf("%d", &new_status);
            target->data.status = (SurvivorStatus)new_status;
            break;
        case 4:
            printf("New danger level (0-10): ");
            scanf("%d", &target->data.danger);
            break;
        case 0:
            printf("Modification cancelled.\n");
            return;
        default:
            printf("Invalid choice.\n");
            return;
    }
    while((c = getchar()) != '\n' && c != EOF);
    printf("Data updated succesfully!\n");
}

void remove_survivor(Node** head_ref) {
    if (*head_ref == NULL) { 
        printf("The list is empty\n");
        return;
    }

    char name_to_remove[100];
    printf("Enter the name of the survivor to remove: ");
    scanf("%99s", name_to_remove);

    Node *current = *head_ref;
    Node *prev = NULL;

    while (current != NULL && strcmp(current->data.name, name_to_remove) != 0) {
        prev = current;
        current = current->next;
    }

    if(current == NULL) {
        printf("Survivor %s not found\n", name_to_remove);
        return;
    }

    if (current->data.status == OUTSIDE) {
        printf("Error. %s is currently OUTSIDE the base\n", name_to_remove);
        return;
    }

    if (prev == NULL) {
        *head_ref = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    printf("Survivor %s has been succesfully removed from the base\n", name_to_remove);
}

void swap_nodes_data(Node* a, Node* b) {
    Survivor temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void sort_by_name(Node* head) { 
    if (head == NULL) return;
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while(ptr1->next != lptr) {
            if(strcmp(ptr1->data.name, ptr1->next->data.name) > 0 ) {
                swap_nodes_data(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while(swapped);
    printf("List sorted alphabetically by name.\n");
}

void sort_by_danger(Node* head) {
    if (head == NULL) return;
    int swapped;
    Node* ptr1;
    Node* lptr = NULL;

    do {
        swapped = 0;
        ptr1 = head;

        while(ptr1->next != lptr) {
            if(ptr1->data.danger < ptr1->next->data.danger) {
                swap_nodes_data(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }while(swapped);
    printf("List sorted by danger level.\n");
}