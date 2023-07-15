#include <stdio.h>
#include <cs50.h>

int luhn(long);

int main(void)
{
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while (number < 0);

    //Testing the number of digits
    int n = 0;
    long testnumber = number;
    while (testnumber != 0)
    {
        testnumber = testnumber / 10;
        n++;
    }
    //Checks whether the number passes the Luhn Algorithm and if it's of correct number length (13, 15, and 16)
    if (luhn(number) == 1 && (n == 13 || n == 15 || n == 16))
    {
        //Testing 16-digit numbers
        if (n == 16)
        {
            long cc = number / 100000000000000; //Truncates all but the first two numbers
            long vcc = cc / 10; //Further truncates the number by one until only first number is left (VISA)
            if (cc == 51 || cc == 52 || cc == 53 || cc == 54 || cc == 55)
            {
                printf("MASTERCARD\n");
            }
            else if (vcc == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //Testing 15-digit numbers
        if (n == 15)
        {
            long cc = number / 10000000000000; //Truncates all but the first two numbers
            if (cc == 34 || cc == 37)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        //Testing 13-digit numbers
        if (n == 13)
        {
            long cc = number / 1000000000000; //Truncates all but the first number
            if (cc == 4)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
    else
    {
        printf("INVALID\n");
    }
}


//Luhns Algorithm Function
int luhn(long number_luhn)
{
    //Doubles every second number starting from the second to last and adds it to the count. (Right to left)
    //If the result of the doubling is a two digit number the digits are added and the result added to the count
    long quotient = 100;
    long truncatednumber = number_luhn;
    long finalnumber;
    int count = 0;
    while (truncatednumber != 0)
    {
        truncatednumber = (number_luhn / quotient) * quotient;
        long finaltruncatednumber = number_luhn - truncatednumber;
        finalnumber = finaltruncatednumber / (quotient / 10);
        quotient = quotient * 100;
        //Here is where the two digits are added if the result of doubling results in a two digit number
        if ((finalnumber * 2) > 9)
        {
            int firstnumber = (finalnumber * 2) / 10;
            int secondnumber = (finalnumber * 2) - (firstnumber * 10);
            finalnumber = firstnumber + secondnumber;
            count += finalnumber;
        }
        //If the result of doubling results is a one digit number the result is added to the count
        else
        {
            count += (finalnumber * 2);
        }
    }
    //Sums every second number starting from the last. (Right to left)
    quotient = 10; //A reset of the quotient so it starts from the last number instead of the second to last
    truncatednumber = number_luhn; //A reset of the truncated number
    long finalnumber2;
    int count2 = 0;
    while (truncatednumber != 0)
    {
        truncatednumber = (number_luhn / quotient) * quotient;
        long finaltruncatednumber = number_luhn - truncatednumber;
        finalnumber2 = finaltruncatednumber / (quotient / 10);
        quotient = quotient * 100;
        count2 += finalnumber2;
    }
    //Calculates whether the credit card number is valid by adding count and count2 and checking if it
    //congruent to 0mod10.
    int finalcount = count + count2;
    if ((finalcount % 10) == 0)
    {
        return 1; //Passes the Luhn Algorithm
    }
    else
    {
        return 0; //Fails the Luhn Algorithm
    }
}