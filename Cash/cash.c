#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    float Money = 0;
    int Coins = 0;
    do{
        Money = get_float("Money: \n");
    }
    while (Money <= 0);
    Money = round(Money * 100);
    while (Money >= 25)
     {
         Money = Money - 25;
         Coins = Coins + 1;
     }
     while (Money >= 10)
     {
         Money = Money - 10;
         Coins = Coins + 1;
     }
     while (Money >= 5)
     {
         Money = Money - 5;
         Coins = Coins + 1;
     }
     while (Money > 0)
     {
         Money = Money - 1;
         Coins = Coins + 1;
     }
     printf("%i Coins", Coins);
     printf("\n");
}
