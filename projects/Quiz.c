#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <fcntl.h>

#define Max_line 300
volatile sig_atomic_t timeoutFlag = 0;

void handle_timeout(int sig)
{
    timeoutFlag = 1;
    printf("\n⏰ Time's up!\n");
}

int getInputWithTimeout(int *answer, int timeout_seconds)
{
    fd_set readfds;
    struct timeval tv;
    char buffer[100];

    timeoutFlag = 0;

    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);

    tv.tv_sec = timeout_seconds;
    tv.tv_usec = 0;

    printf("You have %d seconds to answer: ", timeout_seconds);
    fflush(stdout);

    int result = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);

    if (result == 0)
    {
        // Timeout
        printf("\n⏰ Time's up!\n");
        return 0;
    }
    else if (result > 0)
    {
        // Input available
        if (fgets(buffer, sizeof(buffer), stdin) != NULL)
        {
            if (sscanf(buffer, "%d", answer) == 1)
            {
                return 1; // Success
            }
        }
        printf("Invalid input format!\n");
        return 0;
    }
    else
    {
        // Error
        printf("Input error!\n");
        return 0;
    }
}

int askQuestion(FILE *file, int *used5050, int *usedskip)
{
    char question[Max_line];
    char option[4][Max_line];
    int correctOption, userAnswer;

    // Read question and options
    if (fgets(question, Max_line, file) == NULL)
        return -1;
    for (int i = 0; i < 4; i++)
    {
        if (fgets(option[i], Max_line, file) == NULL)
            return -1;
    }
    if (fscanf(file, "%d\n", &correctOption) != 1)
        return -1;

    // Ask question
    printf("\n%s", question);
    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s", i + 1, option[i]);
    }

    printf("\nEnter your answer (1 - 4): ");

    if (!getInputWithTimeout(&userAnswer, 10) || userAnswer < 1 || userAnswer > 4)
    {
        printf("❗ Time's up or invalid input!\n");
        return 0;
    }

    if (userAnswer == correctOption)
    {
        printf("✅ Correct!\n");
        return 1;
    }
    else
    {
        printf("❌ Wrong!\n");

        int useLifeline = 0;

        if (*used5050 == 0 || *usedskip == 0)
        {
            printf("Do you want to use a lifeline? (1: Yes, 0: No): ");

            if (!getInputWithTimeout(&useLifeline, 10))
            {
                printf("❗ Time's up or invalid input!\n");
                return 0;
            }

            if (useLifeline == 1)
            {
                if (*used5050 == 0)
                {
                    printf("Using 50-50 lifeline...\n");
                    *used5050 = 1;

                    printf("Options left:\n");
                    printf("%d. %s", correctOption, option[correctOption - 1]);

                    for (int i = 0; i < 4; i++)
                    {
                        if ((i + 1) != correctOption)
                        {
                            printf("%d. %s", i + 1, option[i]);
                            break;
                        }
                    }

                    timeoutFlag = 0;
                    printf("Enter your answer (1 - 4): ");

                    if (!getInputWithTimeout(&userAnswer, 10) || userAnswer < 1 || userAnswer > 4)
                    {
                        printf("❗ Time's up or invalid input!\n");
                        return 0;
                    }

                    if (userAnswer == correctOption)
                    {
                        printf("✅ Correct after lifeline!\n");
                        return 1;
                    }
                    else
                    {
                        printf("❌ Still wrong.\n");
                        return 0;
                    }
                }
                else if (*usedskip == 0)
                {
                    printf("Using skip lifeline... Question skipped.\n");
                    *usedskip = 1;
                    return 0;
                }
                else
                {
                    printf("❗ No lifelines available.\n");
                }
            }
        }

        return 0;
    }
}

int main()
{
    FILE *file = fopen("questions.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // Register signal handler
    signal(SIGALRM, handle_timeout);

    int Score = 0;
    int Total = 0;
    int used5050 = 0;
    int usedskip = 0;

    int result;
    while ((result = askQuestion(file, &used5050, &usedskip)) != -1)
    {
        Score += result;
        Total++;
    }

    fclose(file);

    printf("\nYou answered %d out of %d questions correctly.\n", Score, Total);
    printf("✅ Your score: %.2f%%\n", ((float)Score / Total) * 100);
    return 0;
}
