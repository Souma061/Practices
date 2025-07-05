#include <stdio.h>
#include <ctype.h>

int main()
{
  FILE *fp;
  char ch;
  int charCount = 0, lineCount = 0, wordcount = 0;
  int inWord = 0;

  fp = fopen("hello.txt", "r");
  if (fp == NULL)
  {
    printf("Error openuing file.\n");
    return 1;
  }

  while ((ch = fgetc(fp)) != EOF)
  {
    charCount++;
    if (ch == '\n')
    {
      lineCount++;
    }
    if (isspace(ch))
    {
      inWord = 0;
    }
    else if (inWord == 0)
    {
      wordcount++;
      inWord = 1;
    }
  }
  fclose(fp);

  printf("Characters: %d\n", charCount);
  printf("Lines: %d\n", lineCount);
  printf("Words: %d\n", wordcount);
  return 0;
}
