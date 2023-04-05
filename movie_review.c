#include <stdio.h>
#include<stdlib.h>

void welcome();
int review();
void rating();
void seeReviews();
void rates();
void clear_input_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        //discard characters
    }
    
}

int main(){
    welcome();
    return 0;
}

void welcome(){
    char choice[2];
    printf("\t\tMOVIE REVIEW APPLICATION\n");
    printf("\t\t------------------------\n");
    printf("Hello. Welcome to the movie review application.\n");
    printf("Here you will be able to review any movie of your choice anonymously.\n");
    printf("Also you can rate the movie depending on your prefrence on a scale of 1 - 5.\n");
    printf("What would yu like to do? :)\n\n");
    printf("1. Review a movie\n2. See some reviews\n3. Exit the program!\n");
    printf("Please enter your choice: ");
    fgets(choice, sizeof(choice), stdin);
    int choice2 = atoi(choice);
    switch (choice2)
    {
        case 1:
            if (review() == 0)
            {
                printf("\nYour review is saved. Thank you for submitting your review.\n");
            }
            rating();
            printf("\nThank you. You submittion has been saved.\nTo see all the reviews, restart the program and select option 2. :)\n\n");
            break;
        case 2:
            seeReviews();
            break;
        default:
            printf("\nError code 4: Invalid option. Please choose a valid option\n");
            welcome();
        break;
    }
}

//this function asks the user for the movie title and their opinion on the movie
int review (){
    clear_input_buffer();
    //ask the user for the nber of lines that they will type
    char nl[100];
    printf("\nEnter the number of lines you will type: ");
    fgets(nl, sizeof(nl), stdin);
    int numLines = atoi(nl);
        //1ask for the movie title
    char *movieName;
    movieName = (char *)malloc(100 * sizeof(char));
    //check if memory allocation was successful
    if (movieName == NULL)
    {
        printf("Error code 2: Memory allocation for the movie title failed!\n");
        return 1;
    }
    // clear_input_buffer();
    size_t len = 0;
    printf("\nEnter the title of the movie you want to review: ");
    if (getline(&movieName, &len, stdin) == -1)
    {
        printf("Error code 3: There was an error reading the line!\n");
        return 1;
    }
    //open a file and append the movie title
    FILE *file;
    file = fopen("reviews.txt", "a");
    fprintf(file, "\n\t\t%s", movieName);
    fclose(file);
    free(movieName);
    //allocate memory for the lines
    char **lines;
    lines = (char **)malloc(numLines * sizeof(char *));
    //check for memory allocation error
    if (lines == NULL)
    {
        printf("Error  code 4: Memory allocation for the lines input failed!\n");
        return 1;
    }
    
    //enter your review line by line
    printf("\n(Remember not to make the lines too long)  :)\n");
    for (int i = 0; i < numLines; i++)
    {
        // clear_input_buffer();
        printf("Enter line %d: ", i + 1);
        lines[i] = (char *)malloc(100 * sizeof(char));
        if (lines == NULL)
        {
            printf("Error code 5: Failed to allocate memory for the array!\n");
            return 1;
        }
        //check for error while inputing the reviews
        if (getline(&lines[i], &len, stdin) == -1)
        {
            printf("Error code 6: Failed to read line %d\n", i + 1);
            return 1;
        }
    }
    //open the file in apend mode for writting
    file = fopen("reviews.txt", "a");
    //write in the file and free memory allocation of the array
    for (int i = 0; i < numLines; i++)
    {
        fprintf(file, lines[i]);
        free(lines[i]);
    }
    //close the file
    fclose(file);
    // free the memory allocated for the lines
    free(lines);
    return 0;
}

//this function asks teh user if they would like to rate the ovie or not
void rating(){
    int choice;
    printf("\nDo you wish to rate the movie you have just reviewd?\n1. Yes\n2. No\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch (choice)
    {
        case 1:
            rates();
            printf("Your review has een saved. Thank you. :)\n");
            break;
        case 2:
            printf("Your review has een saved. Thank you. :)\n");
            break;
        default:
            printf("\nError code 4: Invalid option. Please choose a valid option\n");
            rating();
            break;
    }
}

//this functin provides a menu for the user o choose and then write the results to the filee
void rates(){
    int star;
    FILE *file;
    printf("\nHow was the movie you've just reviewed?\n");
    printf("1 star. Not worth my time\n2 star. Somehow close to average.\n");
    printf("3 star. 50 - 50 level\n4 star. Better than average\n5 star. I'll definetly rewatch it.\n");
    printf("Choose between 1 - 5.\nI rate the movie at: ");
    scanf("%d", &star);
    switch (star)
    {
        case 1:
        // open the file and append the review
           file = fopen("reviews.txt", "a");
           fprintf(file, "I rate this movie a 1 star. It is not worth my time!\n");
           fclose(file); // close the file
           break;
        case 2:
        // open the file and append the review
            file = fopen("reviews.txt", "a");
            fprintf(file, "I rate this movie a 2 star. It is somehow close to average!\n");
            fclose(file);// close the file
            break;
        case 3:
        // open the file and append the review
           file = fopen("reviews.txt", "a");
            fprintf(file, "I rate this movie a 3 star. It is at a 50 - 50 level!\n");
            fclose(file);// close the file
            break;
        case 4:
        // open the file and append the review
            file = fopen("reviews.txt", "a");
            fprintf(file, "I rate this movie a 4 star. It is better than average!\n");
            fclose(file);// close the file
            break;
        case 5:
        // open the file and append the review
            file = fopen("reviews.txt", "a");
            fprintf(file, "I rate this movie a 5 star. I'll definetly rewatch it over and over!\n");
            fclose(file);// close the file
            break;
        default:
            printf("\nError code 5: Sorry invalid choice!!\n");
            printf("Please enter a valid choice.");
            rates();
            break;
    }
}

//this function reads the conents on the file and outputs it
void seeReviews(){
    FILE *file;
    file = fopen("reviews.txt", "r");
    printf("\nThe revies of the  varius movies.\n");
    char c = fgetc(file);
    while (c != EOF)
    {
            printf("%c", c);
            c = fgetc(file);
    }
}