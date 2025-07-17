#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_line 300

int askQuestion(FILE *file, int *used5050, int *usedskip)
{
    char question[Max_line];
    char option[4][Max_line];
    int correctOption, userAnswer;

    // Read question and options
    if (fgets(question, Max_line, file) == NULL) return -1;
    for (int i = 0; i < 4; i++)
    {
        if (fgets(option[i], Max_line, file) == NULL) return -1;
    }
    if (fscanf(file, "%d\n", &correctOption) != 1) return -1;

    // Ask question
    printf("\n%s", question);
    for (int i = 0; i < 4; i++)
    {
        printf("%d. %s", i + 1, option[i]);
    }

    printf("\nEnter your answer (1 - 4): ");
    scanf("%d", &userAnswer);
    while (getchar() != '\n'); // clear buffer

    if (userAnswer == correctOption)
    {
        printf("✅ Correct!\n");
        return 1;
    }
    else
    {
        printf("❌ Wrong!\n");

        int useLifeline = 0;

        // Offer lifeline after wrong answer
        if (*used5050 == 0 || *usedskip == 0)
        {
            printf("Do you want to use a lifeline? (1: Yes, 0: No): ");
            scanf("%d", &useLifeline);
            while (getchar() != '\n');

            if (useLifeline == 1)
            {
                if (*used5050 == 0)
                {
                    printf("Using 50-50 lifeline...\n");
                    *used5050 = 1;
                    // Show correct + one wrong option
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

                    printf("Enter your answer (1 - 4): ");
                    scanf("%d", &userAnswer);
                    while (getchar() != '\n');

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
                    return 0; // no point change
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
