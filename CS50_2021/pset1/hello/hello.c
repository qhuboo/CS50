#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What is your name? "); //Gets the users name
    printf("hello, %s\n", name); //Prints hello and the name of the user
}