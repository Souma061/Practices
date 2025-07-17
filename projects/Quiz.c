#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_line 300

int askQuestion(FILE *file)
{
  char question[Max_line];
  char option[4][Max_line];
  int correctOption;
  int userAnswer;

  // Read the question
  if (fgets(question, Max_line, file) == NULL)
  {
    return 0;
  }

  for (int i = 0; i < 4; i++)
  {
    if (fgets(option[i], Max_line, file) == NULL)
    {
      return 0;
    }
  }
  if (fscanf(file, "%d", &correctOption) != 1)
  {
    return 0;
  }

  // Consume the newline character after the number
  fgetc(file);

  // print question and options
  printf("\n%s", question);
  for (int i = 0; i < 4; i++)
  {
    printf("%d. %s", i + 1, option[i]);
  }

  while (1)
  {
    printf("Enter your answer (1 - 4) : ");
    if (scanf("%d", &userAnswer) != 1)
    {
      while (getchar() != '\n')
        ;

      printf("Invalid input. Please enter a number between 1 and 4.\n");
      continue;
    }
    if (userAnswer >= 1 && userAnswer <= 4)
    {
      break;
    }
    else
    {
      printf("Invalid input. Please enter a number between 1 and 4.\n");
    }
  }
  if (userAnswer == correctOption)
  {
    printf("Correct!\n");
    return 1;
  }
  else
  {
    printf("Wrong! The correct answer is option %d.\n", correctOption);
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

  while (!feof(file))
  {
    int result = askQuestion(file);
    if (result == 0 && feof(file))
    {
      break;
    }
    Score += result;
    Total++;
  }
  fclose(file);

  printf("\nYou answered %d out of %d questions correctly.\n", Score, Total);
  if (Total > 0)
    printf("🎯 Your score: %.2f%%\n", (float)Score / Total * 100);
  else
    printf("No valid questions were found.\n");

  // while(1) {
  //   int result = askQuestion(file);
  //   if(result == 0) {
  //     break;
  //   }
  //   score += result;
  //   totalQuestions++;
  // }
  // fclose(file);
  // printf("You answered %d out of %d questions correctly.\n", score, totalQuestions);

  // if(totalQuestions > 0) {
  //   printf("Your score is: %.2f%%\n", (float)score / totalQuestions * 100);
  // } else {
  //   printf("No questions were answered.\n");
  // }
  return 0;
}
