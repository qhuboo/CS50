#include <stdio.h>
#include <cs50.h>

int get_positive_width(void);

int main(void)
{
    //This is for the left half of the pyramid
    int n = get_positive_width(); //get positive width for the pyramid
    int s = n - 1; //Calculates the number of spaces that will be printed before any bricks in the row
    for (int p = 0; p < n; p++) //This will be the general counter starting at 0 and up to n - 1
    {
        for (int i = 0; i < s; i++)
        {
            printf("%c", ' '); //Prints s number of spaces starting at s = n - 1 and then prints s-- until s = 0
        }
        for (int i = s; i < n; i++)
        {
            printf("#"); //Prints n - s number of bricks until finally printing n number of blocks when s = 0
        }
        s--;
        printf("%s", "  "); //Prints two spaces between the two sides of the pyramid
        //This is for the right side of the pyramid
        int a = 0;
        while (a <= p)
        {
            printf("#"); //Prints a brick up to the current pth iteration until printing n number of them
            a++;
        }
        printf("\n");
    }
}
//This function ensures the value of the width is between 1 and 8 inclusively
int get_positive_width(void)
{
    int n;
    do
    {
        n = get_int("Width: ");
    }
    while (n < 1 || n > 8);
    return n;
}

