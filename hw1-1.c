// Berke Algül 040230762 

#include <stdio.h>

#define MAX_STR_SIZE 100

char* lowerCase(char* str);
char* upperCase(char* str);
char* sentenceCase(char* str);
char* capitilizedCase(char* str);

int main()
{
    char str[MAX_STR_SIZE];

    // get input from user
    printf("Please enter a string: ");
    fgets(str, MAX_STR_SIZE, stdin);

    //process and print output strings
    printf("\n");
    printf("Original: %s\n", str);
    printf("Lower case: %s\n", lowerCase(str));
    printf("Upper case: %s\n", upperCase(str));
    printf("Sentence case: %s\n", sentenceCase(str));
    printf("Capitilized case: %s\n", capitilizedCase(str));

    return 0;
}

char* lowerCase(char* str)
{
    for(int i=0; i < MAX_STR_SIZE; i++)
    {
        // return at null character (end of string)
        if(str[i] == 0)
            return str;

        // check if char is upper case letter
        if(str[i] < 91 && str[i] > 64)
            str[i] += 32;
    }
}

char* upperCase(char* str)
{
    for(int i=0; i < MAX_STR_SIZE; i++)
    {
        if(str[i] == 0)
            return str;
        
        // check if char is lower case letter
        if(str[i] < 123 && str[i] > 96)
            str[i] -= 32;
    }
}

// Note: This funtion takes account of first space character(s)
// For example: "    hello World!"  ->  "    Hello world!"
char* sentenceCase(char* str)
{
    // make everything lower case first
    str = lowerCase(str);

    // find first non space character    
    int first_character = 0;
    for(; first_character < MAX_STR_SIZE; first_character++) 
    {
        if(str[first_character] != 32)
            break;
    }

    // If first element is lower case letter, we make it upper case
    if(str[first_character] < 123 && str[first_character] > 96)
        str[first_character] -= 32;

    return str;
}

char* capitilizedCase(char* str)
{
    str = sentenceCase(str);
    int bNew_word = 0;

    for(int i = 0; i < MAX_STR_SIZE; i++) 
    {
        if(str[i] == 0)
            return str;

        // check if we get new word
        if(str[i] == 32)
        {
            bNew_word = 1;
            continue;
        }

        if(bNew_word)
        {
            bNew_word = 0;
            //convert to upper case letter
            if(str[i] < 123 && str[i] > 96)
                str[i] -= 32;
        }
    }
}