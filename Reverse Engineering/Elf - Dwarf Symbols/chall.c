/* gcc -g -o chall chall.c */
#include <stdio.h>
#include <string.h>

#define PASSWORD_LENGTH 32

char password[] = "UArfStPzkuZNJMDy1TtMY7JWaGjO4UHy";

int main()
{
    char client_password[PASSWORD_LENGTH + 1]; /* add null byte terminator */

    puts("\t\t~~[ Hackfun elf symbols ]~~\n");

    printf("Password: ");
    fgets(client_password, PASSWORD_LENGTH + 1, stdin);

    if (strncmp(password, client_password, PASSWORD_LENGTH) == 0)
        puts("Got it! Congrats!");
    else
        puts("Nope...");

    puts("");

    return 0;
}
