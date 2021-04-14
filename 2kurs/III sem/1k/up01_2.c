#include <stdio.h>
#include <ctype.h>

int
main(void)
{
    int character;
    int max = 0;
    int acc = 0;
    while(1) {
        character = getchar();
        if (islower(character)) {
            if(character != 'q') {
                acc++;
            } else {
                while(islower(character)){
                    character = getchar(); 
                }
                acc = 0;
            }
        } else {
            if (acc > max) {
                max = acc;
            }
            acc = 0;
        }
        if (character == EOF) {
            break;
        }
    }
    printf("%d\n", max);
    return 0;
}