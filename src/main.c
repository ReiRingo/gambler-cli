#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define TITLE "Gambler v0.01"
#define DEV "Rei Taylor"

#define START "-start"
#define HELP "-help"

enum
{
    STATE_MENU = 0,
    STATE_GAMBLE = 1,
    STATE_JOB = 2 // WIP
};

/* *******************************
 * SECRET: supplying two arguments
 *         and if the second happens to be an integer
 *         it'll use it as the starting balance
 * ******************************/

void gambler_help(void)
{
    printf(
        TITLE " by " DEV "\n"
        "----------------------------------\n"
        "The game is quite simple;\n"
        " There are two game modes:\n"
        " One is called gambling,\n"
        "the other is called job.\n"
        " You can only use the gambling mode\n"
        "when you reach a specific amount of cash.\n"
        "(Probably more than 10 credits.)\n\n"

        " You can earn credits using the job mode;\n"
        " The job mode is a simple mode where you accept\n"
        "phone calls, and per phone call, you earn a bit of credits.\n\n"

        " In gambling mode, you will bet an amount of\n"
        "cash, and then, you pick either red or black\n"
        "and it will roll, and if you got guessed the correct\n"
        "colour, you earn double of what you bet!\n\n"

        " You usually start with 100 credits,\n"
        "so, make the most of it, and good luck!\n"
    );
}

void gambler_game(long starting_cash, const char *name)
{
    printf("Hello, %s! Welcome to " TITLE "!\n\n", name);

    char input[2] = {0};
    int state = STATE_MENU;

    while(1)
    {
        if(state == STATE_MENU)
        {
            printf(
                "Type:\n"
                " [0] = Quit\n"
                " [1] = Gamble\n"
                " [2] = Job (WIP)\n"
                "\n"
                "> "
            );

            int res = scanf(" %1[0-9]", input);
            putchar('\n');

            if(res == 1)
            {
                if(!strcmp(input, "0"))
                {
                    break;
                }
                else if(!strcmp(input, "1"))
                {
                    break; // todo: gamble
                }
                else if(!strcmp(input, "2"))
                {
                    break; // todo: job
                }
                else
                {
                    puts("Invalid Input!");
                    continue;
                }
            }
            else
            {
                puts("Invalid Input!");
                continue;
            }
        }

        break;
    }

    printf("\n" TITLE ": Exiting...");
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf(
            "Welcome to " TITLE " by " DEV "!\n\n"

            " Start the game by appending:\n"
            " " START "\n"
            " and append with:\n"
            " " HELP "\n"
            " to know more!"
        );
        
        return 0;
    }

    if(!strcmp(argv[1], HELP))
    {
        gambler_help();
    }
    else if (!strcmp(argv[1], START))
    {
        long start_money = 100l;
        const char *starting_name = "Gamble Man";

        if(argc > 2)
        {
            char *endptr;
            errno = 0;

            start_money = strtol(argv[2], &endptr, 10);
            
            if((start_money == LONG_MAX || start_money == LONG_MIN) && errno == ERANGE || endptr == argv[2] || (*endptr))
            {
                fprintf(stderr, TITLE "::CHEATS (1): ERROR VALUE\n");
                return 1;
            }
        }
        if(argc > 3)
        {
            // Override Gamble Man (RIP)
            starting_name = argv[3];
        }

        gambler_game(start_money, starting_name);
    }
    else
    {
        printf(TITLE ": \033[31mUnknown command!\033[0m\n");
        return 1;
    }

    return 0;
}