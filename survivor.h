typedef enum{
    MEDIC,
    ENGINEER,
    SCOUT,
    TECHNICIAN,
    BIOLOGIST,
    MECHANIC
}SurvivorSkill;

typedef enum{
    ACTIVE,
    SICK,
    INJURED,
    OUTSIDE,
    MISSING
}SurvivorStatus;

typedef struct {
    char name[100]; // unique survivor's name
    SurvivorSkill skill; // enum SurvivorSkill
    int food; // 0-100
    int health; // 0-100
    int danger; // 0-10
    SurvivorStatus status; // enum SurvivorStatus
}Survivor;