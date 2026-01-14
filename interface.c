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

    //Getting name
    printf("Enter name: ");
    getchar();
    fgets(survivor.name, sizeof(survivor.name), stdin);
    size_t length = strlen(survivor.name);
    if(length > 0 && survivor.name[length - 1] == '\n') {
        survivor.name[length - 1] = '\0';
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
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error");
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