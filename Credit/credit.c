#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long CardNumber = 0; // Original number from usser.
    int CardLastNumber = 0; // This variable will get the last number from CardNubmer from the second-to-last digit.
    int AddingNumber = 0; // This will add up the individual numbers from CardLastNumber so we will check if the last number is "0".
    int MemoryNumber = 0; // This variable will be used to add the last digit from the number.
    long CardNumberHolder = 0; 
    // This is a variable to "hold" the card number for the variable Memory Number. I cannot use CardNumber again because this variable is being modified in the first loop.
    long CheckNumber = 0; // This will check at the end of the program what kind of Card we have according to the first two digits.
    int NumberLenght = 0; 
    // This variable will check how long is the Card, because some cards share the same lenght but the first two numbers are different.
    CardNumber = get_long("Number: "); // We will get the number from the user via "prompt".
    CheckNumber = CardNumber; // CheckNumber is getting the value from the CardNumber, so we will know what the first numbers are.
    while (CheckNumber > 0) // This loop will check the first two digits of the Card, so it will know what card type is.
    {
        NumberLenght = NumberLenght + 1; // This code will help you to know the lenght of the Number, adding up everytime the value of 1.
        if (CheckNumber < 100) // Why "<100", because we need the first two numbers to check, for instance "51" for Mastercard.
        {
            NumberLenght = NumberLenght + 1; 
            // So, if the lenght of CheckNumber is below than 100, that will mean that we have the two digits we need, and we add for the last time a number for the lenght of the variable NumberLenght.
            break; // This command is very important, once the condition is true, we must stop the "while loop". Otherwise, we won't have two digits.
        }
        CheckNumber = CheckNumber / 10; 
        // This makes the lenght of the variable CheckNumber shorter, if you divide by 10, you will always remove the last number.
    }
    CardNumberHolder = CardNumber; 
    // CardNumberHolder is getting the value from the CardNumber, so we will get the only the last number for the Card.
    while (CardNumber > 0) // We need to make it zero so we can go through the whole lenght of the Card.
    {
        CardLastNumber = ((CardNumber % 100) / 10) * 2; 
        // Here, we need to take the last TWO numbers from the card with "% 100". Then, from that two numbers, I actually need the first one, so I will divide "/ 10" (Remember, if            you divide something by 10, 100..., you will remove the last numbers.). Then, I need to multiply by 2 to verify later the right amount of the sum.
        if (CardLastNumber > 9) 
            // Here, we can check if the number is bigger than "9". Why? For instance, if you get the number "6" and you multiply by "2" you will get "12". That is a problem because you          need to split again those number to add them up as the exercise request, in this case "1 + 2". So, with this code we can make it. Why "9" and no "10" for instance? This may           sounds pretty obvious but it was a big mistake for me because if you multiply "5" by "2" you will get "10", and you still have to add them up "1 + 0".
        {
            MemoryNumber = CardLastNumber; 
            // This variable will take the two numbers digit, for instance "16" after "8" being multiplied by "2".
            while (MemoryNumber > 0)
            {
                AddingNumber = AddingNumber + (MemoryNumber % 10); 
                // Here we % 10, so we will get the last number split and we add that number to the total sum.
                MemoryNumber = MemoryNumber / 10; // Here, we will remove the last number of those two digits, so we can add the first one too.
            }
        }
        else
        {
            AddingNumber = AddingNumber + CardLastNumber; 
            // If the number is smaller than 10, we don't need to split anything, just add the number to the sum.
        }
        CardNumber = CardNumber / 100;
        // Then we will remove the last two numbers from the Card because remember, we need the second-to-last digit everytime.
    }
    while (CardNumberHolder > 0)
        // This one is easier to do because we just need the last number of the Card, no the second-to-last digit.
    {
        CardLastNumber = CardNumberHolder % 10; // We set the value of CardLastNumber to the last number of the card by %.
        AddingNumber = AddingNumber + CardLastNumber; // Then, we add that numebr to the total sum.
        CardNumberHolder = CardNumberHolder / 100; 
        // And of course, we need still to remove de last two numbers, otherwise, it will take the last one everytime.
    }
    if ((AddingNumber % 10) == 0) 
        // This will know if the value of sum ends in "0". That's the only way to verify if the card is valid. For instance, the total sum is "20", so we will % 10. Then we will get just     the "0" and if that value is equal to 0, that means that is a valid card. But also we need to check what type of card is, not only if it's valid. We can do that with the next "if     else". We will check the first two numbers of the card and the lenght of this ones to know if they are the right card, otherwise, it may have the first two numbers right but the      lenght is wrong. Or the opposite, the lenght might be right, but the first two numbers might be wrong. That's why we will print invalid.
    {
        if (((CheckNumber == 34) || (CheckNumber == 37)) && (NumberLenght == 15))
        {
            printf("AMEX\n");
        }
        else if (((CheckNumber > 50) && (CheckNumber < 56)) && (NumberLenght == 16))
        {
            printf("MASTERCARD\n");
        }
        else if (((CheckNumber > 39) && (CheckNumber < 50)) && ((NumberLenght == 13) || (NumberLenght == 16)))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n"); // If the value of sum is different than 0, we will know straight away that it's an invalid card.
    }
}
