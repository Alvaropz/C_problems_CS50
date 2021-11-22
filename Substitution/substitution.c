#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int CmpString; // This variable will be used to compare two strings.
char OrigKey[26]; // This variable will be used as key for my 26 alphabet characters.
int RepChar = 0; // This variable will check if there is any character repeated in my key.
string PlainText; // Variable used to storage the string given by the user.
int letter; // This variable will use to replace the character in the original string for the character in the key.

int main(int argc, char *argv[]) 
// //This is the main function. Here, we will check the two things, the number of the elements in command-line argument and the value of these elements itself.
{
    if (argc < 2 || argc > 2)
//For the purpose of this exercise, we shouldn't have less or more than 2 elements. Why? Because the first one will be "./caesar" and the second one, the number that we will use as reference to transcript our message. So, for instance "./caesar 5" (We have two elements here).
    {
        CmpString = strncmp(argv[0], "./substitution", 14); 
// Here, trough "strncmp", two strings will be compared to see if they are same string. This is "deceptive" because it only checks the amount of characters in the string, no the characters themselves.
        if (CmpString == 0) 
// If the remainder of the comparative is different than 0, it means that the lenght of the strings is not the same.
        {
            printf("Usage: ./substituion KEY\n"); // Hint for the user about how to use the program.
            exit(1);
        }
    }
    if (argc == 2 && (strlen(argv[1]) < 26 || strlen(argv[1]) > 26)) 
// Here, we will check if the amount of characters in the second element is lower or bigger than 26. Remmeber, we need 26 characters.
    {
        printf("Key must contain 26 characters.\n"); // Hint for the user about how to use the program.
        exit(1);
    }
    if (argc == 2 && strlen(argv[1]) == 26) 
// If the amount of elements in command-line is equal a two, that means that we have the right amount of eleements (""./substitution" + "key"). Then if the amount of characters for the string in the second element ("key") is 26 (lenght of the alphabet), that will mean that we have the right amount of characters.
    {
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
// However, we have to check if every character in the string for the second element is a alphabet character. So we have to check each 26 characters.
        {
            if (argv[1][i] < 'A' || (argv[1][i] > 'Z' && argv[1][i] < 'a') || argv[1][i] > 'z') 
// If the program finds a different element than an alphabet character (no matters Upper or Lower case), it will tell to the user.
            {
                printf("Key must onlye contain alphabetic characters\n"); // Hint for the user about how to use the program.
                exit(1);
            }
        }
    }
    for (int i = 0; i < 26; i++) 
// Now, we have to add those characters to our own variable. So will trhough the 26 characters in that string.
    {
        OrigKey[i] = argv[1][i]; 
// Variable "OrigKey" will store the information for each element in "argv" every time that the loop is executed.
        if (OrigKey[i] > 90) 
// If the value is bigger than "90 = Z", we will convert the "lower case" character in upper case. So we will have a standardised key. In this case, all our characters will be Upper Case. If it's already Upper Case, we will add it directly to "OrigKey".
        {
            OrigKey[i] = OrigKey[i] - 32;
        }
    }
    for (int i = 0; i < 26; i++) 
// Now, we have to check if any of those alphabet characters is repeated. We can use ONLY ONE alphabet character for each element in the alphabet. That means that we cannot use the next key "VCHPVZGJNVLSKFBDQVAXEVYMOI". The letter V is repeted several times.
    {
        for (int n = 0; n < 26; n++)
        {
            if (OrigKey[i] == OrigKey[n]) 
// So here we will heck the 26 letters, then, the vale of the current letter with the value of other letters.
            {
                RepChar = RepChar + 1;
// We can use the variable "RepChar" to count how many times is the character in the string. Always, we will have the value of one, because we will check the value of the current character with itself.
                if (RepChar >= 2) // That's why, if a character is repeated, it will mean that the value of "RepChar" is 2.
                {
                    printf("Key must not contain repetaed characters\n"); // Hint for the user about how to use the program.
                    exit(1);
                }
            }
        }
        RepChar = 0; // Remember, at the end of the second loop we have to restore the value for the variable "RepChar". Otherwise, it will always consider that the value is repeated even if it's not.
    }
    PlainText = get_string("plaintext: "); // We get and store the value of the string given by the user.
    printf("ciphertext: ");
    for (int in = 0, lg = strlen(PlainText); in < lg; in++) 
// We will have to check the whole string, as many times as many characters we have in the string.
    {
        if (PlainText[in] >= 'a' && PlainText[in] <= 'z') 
// If the character checked is a lower case, the system will check what is the equivalent for its lower case.
        {
            letter = (PlainText[in] - 97); 
// The variable letter will store the position of the character between "0 and 25", remember, lower case alphabet is between "97" and "122". For instance, "h = 104", "104 - 97 = 7". Position "7" in the alphabet.
            printf("%c", tolower(OrigKey[letter])); 
// Then, the program will take the letter in the position given, for instance "7", and it will be transcrypted for the character "7" in the variable "OrigKey". VERY IMPORTANT! There is a function called "tolower". Remember, in this program we converted all letters in capital letters. However, for the purpose of this exercise, we must keep Upper and Lower cases according to the original text. So if in the text is the word "hello", all these letters must be in lower caes once they have been translated.
        }
        else if (PlainText[in] >= 'A' && PlainText[in] <= 'Z') 
// The variable letter will store the position of the character between "0 and 25", remember, lower case alphabet is between "65" and "190".
        {
            letter = (PlainText[in] - 65);
            printf("%c", OrigKey[letter]);
        }
        else
        {
            printf("%c", PlainText[in]); // If there is a non alphabetic character, we will keep the character in its original form.
        }
    }
    printf("\n");
    exit(0);
}