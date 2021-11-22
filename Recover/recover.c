#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

unsigned char buffer[512];
char newfile[8];
int ImgNum = 0;
int Check = 0;

int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    FILE *oldfile = fopen(argv[1], "r");
    if (oldfile == NULL)
    {
        return 1;
    }
    FILE *img = NULL;
    while (feof(oldfile) == 0)
    {
        fread(buffer, 512, 1, oldfile);
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] &0xf0) == 0xe0)
            {
                if (Check == 0)
                {
                    sprintf(newfile, "%03i.jpg", ImgNum);
                    img = fopen(newfile, "w");
                    fwrite(buffer, 512, 1, img);
                    ImgNum++;
                    Check = 1;
                }
                else if (Check == 1)
                {
                    fclose(img);
                    sprintf(newfile, "%03i.jpg", ImgNum);
                    img = fopen(newfile, "w");
                    fwrite(buffer, 512, 1, img);
                    ImgNum++;
                }
            }
            else if (Check == 1 && feof(oldfile) == 0)
            {
                fwrite(buffer, 512, 1, img);
            }
    }
    fclose(oldfile);
    fclose(img);
}
