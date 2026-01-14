#ifndef SURVIVOR_H
#define SURVIVOR_H


// Enums
typedef enum{MEDIC, ENGINEER, SCOUT, TECHNICIAN, BIOLOGIST, MECHANIC}SurvivorSkill;
typedef enum{ACTIVE, SICK, INJURED, OUTSIDE, MISSING}SurvivorStatus;

//Structs
typedef struct {
    char name[100]; // unique survivor's name
    SurvivorSkill skill; // enum SurvivorSkill
    int food; // 0-100
    int health; // 0-100
    int danger; // 0-10
    SurvivorStatus status; // enum SurvivorStatus
}Survivor;

typedef struct Node {
    Survivor data;
    struct Node* next;
}Node;

//Prototypes
Node* create_node(Survivor data);
void push(Node** head_ref, Survivor new_data);
void display_list(Node* head);
Survivor get_survivor_data(void);
const char* get_skill_name(SurvivorSkill skill);
const char* get_status_name(SurvivorStatus status);
void free_list(Node* head);
void save_to_file(Node* head, const char* filename);
void load_from_file(Node** head_ref, const char* filename);
#endif