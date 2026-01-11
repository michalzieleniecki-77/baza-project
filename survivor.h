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

struct Survivor {
    char name[100];
    SurvivorSkill skill;
    int food;
    int health;
    int danger;
    SurvivorStatus status;
};