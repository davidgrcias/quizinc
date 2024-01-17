#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

// constants
#define MAX_STRING_LENGTH 50

// struct for representing a question
typedef struct {
    char name[MAX_STRING_LENGTH],
         option1[MAX_STRING_LENGTH],
         option2[MAX_STRING_LENGTH],
         option3[MAX_STRING_LENGTH],
         correctOption[MAX_STRING_LENGTH];
} Question;

// struct for representing a user
typedef struct {
    int totalCorrectOption;
    char selectedOption;
    char name[MAX_STRING_LENGTH];
    float score;
} User;

// function prototypes
void createQuestion(Question **, int *);
void viewQuestions();
void playGame(User **);
void errorMessage();
void setColor(char *);
void resetColor();

// global variables
User *userList[50];
Question *questionList[50];
int totalQuestion = 0;

int main() {
    char choice;

    menu:
    // display main menu
    system("cls");
    printf("Quiz Game Made by David G Tech");
    printf("\n> Press C to Create Questions");
    printf("\n> Press V to View Questions & Answers");
    printf("\n> Press P to Play the Game");
    printf("\n> Press Q to Quit");
    printf("\n__________________________________________\n");
    // get user choice
    choice = toupper(getch());

    switch (choice) {
        case 'C':
            createQuestion(questionList, &totalQuestion);
            getch();
            goto menu;
            break;
        case 'V':
            viewQuestions();
            getch();
            goto menu;
            break;
        case 'P':
            playGame(userList);
            getch();
            goto menu;
            break;
        case 'Q':
            // quit the program
            exit(0);
        default:
            // display error message for invalid user choice
            errorMessage();
            goto menu;
    }
}

void setColor(char *x) {
    if (strcmp(x, "Red") == 0) {
        printf("\x1b[31m");
    } else if (strcmp(x, "Green") == 0) {
        printf("\x1b[32m");
    } else if (strcmp(x, "Yellow") == 0) {
        printf("\x1b[33m");
    }
}

void resetColor() {
    printf("\x1b[0m");
}

void errorMessage() {
    setColor("Red");
    printf("\nInvalid Key");
    resetColor();
    Sleep(1000);
}

void createQuestion(Question **questionList, int *totalQuestion) {
    char choice;

    system("cls");
    printf("Insert Question\n\n");

    do {
        // allocate memory for a new question
        Question *question = malloc(sizeof(Question));
        do {
            printf("Question %d : ", *totalQuestion + 1);
            scanf("%[^\n]", question->name);
            fflush(stdin);
            printf("Answer 1 : ");
            scanf("%[^\n]", question->option1);
            fflush(stdin);
            printf("Answer 2 : ");
            scanf("%[^\n]", question->option2);
            fflush(stdin);
            printf("Answer 3 : ");
            scanf("%[^\n]", question->option3);
            fflush(stdin);

            do {
                // get and validate the correct answer
                setColor("Green");
                printf("Correct Answer : ");
                scanf("%[^\n]", question->correctOption);
                resetColor();
                fflush(stdin);
            } while ((strcmp(question->correctOption, question->option1) != 0) &&
                     (strcmp(question->correctOption, question->option2) != 0) &&
                     (strcmp(question->correctOption, question->option3) != 0));

            // display options to continue creating question or reset
            printf("\n> Press Y to Make More Question");
            printf("\n> Press R to Reset Question %d", *totalQuestion + 1);
            printf("\n> Press Any Other Key Except Y, R to Exit From This Menu\n");
            choice = toupper(getch());
        } while (choice == 'R');

        // save the question
        questionList[*totalQuestion] = question;
        (*totalQuestion)++;

        // display success message
        setColor("Green");
        printf("\nQuestion %d has been made successfully\n", *totalQuestion);
        resetColor();
    } while (choice == 'Y');

    setColor("Yellow");
    printf("\nTotal Questions : %d\n", *totalQuestion);
    resetColor();

    printf("\n> Press Any Key to Back to Menu\n");
}

void viewQuestions() {
    char input;

    system("cls");
    if (totalQuestion == 0) {
        // display message if no questions are available
        setColor("Red");
        printf("There are no questions added yet\n");
        resetColor();
        printf("\n> Press Any Key to Back to Menu\n");
        getch();
        main();
    } else {
        // display questions and answers
        printf("View Questions & Answers\n\n");
        for (int i = 0; i < totalQuestion; i++) {
            printf("Question %d : %s\n", i + 1, questionList[i]->name);
            printf("Answer 1 : %s\n", questionList[i]->option1);
            printf("Answer 2 : %s\n", questionList[i]->option2);
            printf("Answer 3 : %s\n", questionList[i]->option3);


            setColor("Green");
            printf("Correct Answer : %s\n", questionList[i]->correctOption);
            resetColor();
        }
        printf("\n> Press Any Key to Back to Menu\n");
        getch();
        main();
    }
}

void playGame(User **userList) {
    char choice;

    // display error message if no questions are available
    if (totalQuestion < 1) {
        system("cls");
        setColor("Red");
        printf("There are no questions added yet");
        resetColor();

        printf("\n\n> Press Any Key to Back to Menu\n");
        getch();
        main();
    }

    // allocate memory for a new user
    User *user = malloc(sizeof(User));

    system("cls");
    printf("Insert Your Name : ");
    scanf("%[^\n]", user->name);
    fflush(stdin);
    printf("%s, welcome to the quiz!", user->name);
    Sleep(800);
    system("cls");
    printf("Let's get started!");
    Sleep(800);
    user->totalCorrectOption = 0;
    for (int i = 0; i < totalQuestion; i++) {
        quiz:
        system("cls");
        printf("Question %d : %s\n", i + 1, questionList[i]->name);
        printf("A.) %s\n", questionList[i]->option1);
        printf("B.) %s\n", questionList[i]->option2);
        printf("C.) %s\n", questionList[i]->option3);
        user->selectedOption = toupper(getch());
        // check if the selected option is correct
        if (user->selectedOption == 'A') {
            if ((strcmp(questionList[i]->option1, questionList[i]->correctOption) == 0)) {
                user->totalCorrectOption++;
            }
        } else if (user->selectedOption == 'B') {
            if ((strcmp(questionList[i]->option2, questionList[i]->correctOption) == 0)) {
                user->totalCorrectOption++;
            }
        } else if (user->selectedOption == 'C') {
            if ((strcmp(questionList[i]->option3, questionList[i]->correctOption) == 0)) {
                user->totalCorrectOption++;
            }
        } else {
            // display error message for invalid input
            errorMessage();
            goto quiz;
        }
    }
    // display quiz completion message
    system("cls");
    printf("You have completed the quiz\n");
    Sleep(800);
    system("cls");
    user->score = user->totalCorrectOption * (100 / totalQuestion);

    // display user's perfomance
    if (user->score < 100) {
        printf("%s, You didn't get a perfect score. Keep practicing!", user->name);
    } else {
        printf("Congratulations %s! You got a perfect score!", user->name);
    }
    setColor("Green");
    printf("\nCorrect Answer : %d", user->totalCorrectOption);

    setColor("Red");
    printf("\nIncorrect Answer : %d", totalQuestion - user->totalCorrectOption);

    setColor("Yellow");
    printf("\nScore : %g", user->score);

    resetColor();

    printf("\n> Press Any Key to Back to Menu\n");

    getch();
    main();
}
