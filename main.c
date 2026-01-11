#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "survivor.h"

int main(void) {
    Survivor survivor[] = {{"Michal", MECHANIC, 60, 99, 8, ACTIVE}};
    printf("Hello %s, wec can tell that you are %s.", survivor[0].name, (survivor[0].danger < 7) ? "not dangerous, you can join to us" : "dangerous, you have to go away");
}