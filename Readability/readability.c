#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

float totalLetters = 0;
float totalWords = 0;
float totalSentences = 0;
float Grade = 0; // This will be the final operation to find the index about how difficult the text is.

int main(void)
{
    string text = get_string("Text: "); // We will get the string here.
    
    // Here, we will create two "local" variables, 'n' will take the lenght of the text thanks to de function "streln". Then, "i" will be used as index for the array.
    //If the information asocciated for the specific index "i" is equal to a value for uppercase and lowercase that means that it's actuall a letter in the text.
    //Example: If the value for text(5) (position 5 in the text as string) is equal to a value between A & Z or z & z. That means that it's a letter.
    for (int i = 0, n = strlen(text); i < n; i++) 
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            totalLetters = totalLetters + 1;
        }
    }

    //In the next loop, we will do the same that the letters loop, the only difference is that we will check the "blank spaces" instead of actual characters.
    //Also, we have added a small exception, just in case there are more "black spaces" in a row telling to the program to jump if there is too many "blank spaces" in a row.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            totalWords = totalWords + 1;
            while (text[i] == ' ')
            {
                i = i + 1;
            }
        }
    }
    //Here, I had to add an additional sum for the words, because after the last word there are no more "blank spaces" so it won't be counted.
    totalWords = totalWords + 1;
    
    //In the case of the sentences, we know that the sentence is over if there is a ".", "?" or "!". We also have to check the whole string.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            totalSentences = totalSentences + 1;
        }
    }
    
    //This is the formula, the most important thing here is to be aware that we need a "float" number for all variables, otherwise it won't provide the right decimals at the end and the operation will fail.
    Grade = round(0.0588 * ((totalLetters / totalWords) * 100) - 0.296 * ((totalSentences / totalWords) * 100) - 15.8);

    //For the result, the only specification to be aware about is the signs according to ">", "<" or "=". But this only depends of this formula, so pay attetion to the specifications.
    if (Grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if ((Grade >= 1) && (Grade < 16))
    {
        printf("Grade %.0f\n", Grade);
    }
    else if (Grade < 1)
    {
        printf("Before Grade 1\n");
    }
}