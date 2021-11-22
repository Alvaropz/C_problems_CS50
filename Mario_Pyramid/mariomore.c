#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int Height = 0;
    int Width = 0;
    do {
        Height = get_int("Height: \n");
        if ((Height >= 1) && (Height <= 8))
        {
             while (Height != 0)
             {
                 for(int a = Height - 1; a > 0; a--)
                 {
                     printf(" ");    
                 }
                 Width = Width + 1;
                 for (int a = 0; a < Width; a++)
                 {
                     printf("#");
                 }
                 printf("  ");
                  for (int a = 0; a < Width; a++)
                 {
                     printf("#");
                 }
                 printf("\n");
                 Height = Height - 1;
             }
             break;
            }
        }
    while ((Height < 1) || (Height > 8));
}
