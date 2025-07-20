#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


void showIntro() {
      printf("=========================================\n");
    printf("      ⌨️  Welcome to Typing Speed Test!     \n");
    printf("=========================================\n");
    printf("📋 Instructions:\n");
    printf("1. Choose a difficulty level (Easy, Medium, Hard).\n");
    printf("2. A paragraph will be shown — start typing when ready.\n");
    printf("3. Your typing will be timed.\n");
    printf("4. At the end, your WPM and accuracy will be shown.\n");
    printf("-----------------------------------------\n");
}

void showParagraph(char *text, int difficulty) {
  if(difficulty == 1) {
    strcpy(text, "The quick brown fox jumps over the lazy dog.");
  } else if(difficulty == 2) {
    strcpy(text, "A journey of a thousand miles begins with a single step.");
  } else if(difficulty == 3) {
    strcpy(text, "To be yourself in a world that is constantly trying to make you something else is the greatest accomplishment.");
  } else {
    printf("Invalid difficulty choice.Back to 'Easy' difficulty.\n");
    strcpy(text, "The quick brown fox jumps over the lazy dog.");
  }

}

void startTyping(const char *originalText) {
  char typedText[500];
  time_t start,end;
  double timeTaken;
  int correctChars = 0;
  int totalChars = strlen(originalText);
  int i;


    printf("\n💬 Start typing the paragraph below:\n\n");
    printf("🟢 %s\n\n", originalText);


    printf("⏳ Your time starts now! Type and press Enter when done:\n\n");

    start = time(NULL);
    fgets(typedText, sizeof(typedText) , stdin);
    typedText[strcspn(typedText, "\n")] = '\0';

    end = time(NULL);
    timeTaken = difftime(end,start);

    for(i = 0; originalText[i] != '\0' && typedText[i] != '\0'; i++) {
      if(originalText[i] == typedText[i]) {
        correctChars++;
      }
    }

    float accuracy = ((float)correctChars / totalChars) * 100;
    float wpm = ((float)strlen(typedText)/5) / (timeTaken / 60.0);

    printf("\n⏱️ Time Taken: %.2f seconds\n", timeTaken);
    printf("✅ Correct Characters: %d / %d\n", correctChars, totalChars);
    printf("🎯 Accuracy: %.2f%%\n", accuracy);
    printf("⌨️  Typing Speed: %.2f WPM\n", wpm);




}



int main() {
  int difficulty;
  char paragraph[500];

  showIntro();

    printf("Select Difficulty:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice: ");
    scanf("%d", &difficulty);
    getchar();

    showParagraph(paragraph, difficulty);
    printf("\n📜 Typing Paragraph:\n%s\n", paragraph);

    startTyping(paragraph);

    return 0;
}
