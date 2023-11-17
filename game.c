#include <stdio.h>
#include <string.h>

int main() {
    char name[50];
    char answer[10];

    // Step 1
    printf("What is your name?\n");
    scanf("%s", name);
    printf("Hello %s, your program will load shortly.\n", name);

    // Step 2
    printf("How do you feel today? (Enter 'fine' or 'not fine')\n");
    scanf("%s", answer);

    if (strcmp(answer, "fine") == 0 || strcmp(answer, "not fine") == 0) {
        // Step 3
        printf("Have you eaten today? (Enter 'yes' or 'no')\n");
        scanf("%s", answer);

        if (strcmp(answer, "yes") == 0) {
            printf("May the good lord strengthen you and keep you in good health.\n");
        } else if (strcmp(answer, "no") == 0) {
            // Step 4
            printf("Have you heard of ulcer? (Enter 'yes' or 'no')\n");
            scanf("%s", answer);

            if (strcmp(answer, "no") == 0) {
                printf("You should look it up and see what you are doing to yourself.\n");
            } else if (strcmp(answer, "yes") == 0) {
                printf("Are you doing a fast? (Enter 'yes' or 'no')\n");
                scanf("%s", answer);

                if (strcmp(answer, "yes") == 0) {
                    printf("Ok, at least try to drink some milk.\n");
                } else if (strcmp(answer, "no") == 0) {
                    printf("Get off your lazy ass and go eat something.\n");
                }
            }
        }
    }

    // Exit message
    printf("Goodbye %s, send figgy money.\n", name);

    return 0;
}

