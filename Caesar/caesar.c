#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char L; //This variable will allow me convert the current "character" in its transcripetd "character". This means, for instance "a = a + 5" where 5 is the number that I'll use as reference.

int main(int argc, char *argv[]) 
//This is the main function. Here, we will check the two things, the number of the elements in command-line argument and the value of these elements itself.
{
    if (argc < 2 || argc > 2) 
//For the purpose of this exercise, we shouldn't have less or more than 2 elements. Why? Because the first one will be "./caesar" and the second one, the number that we will use as reference to transcript our message. So, for instance "./caesar 5" (We have two elements here).
    {
        printf("Usage: ./caesar key\n"); 
        // If the condition is false, we will print the message "Usage: ./caesar key" as hint for the user.
        exit(1); // Also, we will force the program to stop it because the condition is false.
    }
    for (int i = 0, n = strlen(argv[1]); i < n; i++) 
// Here, we will check in the information in the second element of the command-line are actually numbers. Because the program "shouldn't" deal with other information beyond numbers.
    {
        if (argv[1][i] < '0' || argv[1][i] > '9') 
//Be careful here. Here, we are saying if the information for the element 1 (Remember, position "0" is "./caesar" and position "1" is the number that we will insert) in its position "i" where "i" is the position of the element inside the string is below or above of the characters "0" or "9", it's not a valid information. Easy explanation: "./caesar[0] 45[1]". [1] = 45 = 4[0]5[1]. So, for instance "./caesar 5b", "./caesar f6" are invalid elements.
        {
            printf("Usage: ./caesar key\n");
            exit(1);
        }
    }
    const int key = atoi(argv[1]); 
    // Here, we are literally transforming a string of numbers in integers that won't change in the future (that's why it's a constant). Here we are using our variable "key" to defined as number. So we are saying that, for the second element in command-line, take that information and transform it in a number. "Atoi" will allow me to do that.
    string plaintext = get_string("plaintext: "); 
    // Here, we will assign the text introduced by the user in a string variable.
    printf("ciphertext: "); // Here, we will give the information to the user as the following text is the transcripted text.
    for (int in = 0, lg = strlen(plaintext); in < lg; in++) 
// Here, we will theck the whole string with a loop. Where "in" is the current position in the array, "lg" the complete lenght of the array. Remember, the first element in an array is always "0", that's why we start in 0. Repeat the process by adding the value of 1 to "in" until "in" is the same value of "lg".
    {
        //Here we have three conditions, the first one check if the current charactar that is being check is between "a" and "z". If it's true, you have to transform the value of L. L = (((The ASCII character position for the current element) - 97)) + the value of key) divided by 26 [But you actually taking the rest of it] + 97. Easy explanation:
        // a + 10 --> L = (((97 -97) + 10) % 26) + 97; L = (((0) + 10) % 26) + 97; L = (10 % 26) + 97; L = (10) + 97; L = 107; L = "k".
        // w + 20 --> L = (((119 - 97) + 20) % 26) + 97; L = (((22) + 20) % 26) + 97; L = (44 % 26) + 97; L = (18) + 97; L = 115; L = "q".
        //IMPORTANT! The hardest part here is to figure out how to "restart" the alphabet once you have gone beyond the letter "z". We can do that with "% 26". When we get the rest of the number, we can add up 97 and we will get the new value. Why are we adding up 97? Because 97 = a in the ASCII alphabet.
        if (plaintext[in] >= 'a' && plaintext[in] <= 'z')
        {
            L = (((plaintext[in] - 97) + key) % 26) + 97;
            printf("%c", L);
        } //Same process here, but with Capital Letters and adding the number 65, where  65 = A.
        else if (plaintext[in] >= 'A' && plaintext[in] <= 'Z')
        {
            L = (((plaintext[in] - 65) + key) % 26) + 65;
            printf("%c", L);
        }
        else //If the value is either not lower case or upper case, we leave the symbol as we found it by default.
        {
            printf("%c", plaintext[in]);
        }
    }
    printf("\n");
}
