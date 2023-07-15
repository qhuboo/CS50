#include <cs50.h>
#include <stdio.h>

int main(void) 
{
    long n = get_long("Number: ");
    
    long luhn_number;
    long check_number = 0;
    long quotient = 10;
    int counter = 1;
    int sum = 0;
    int thirteenth, fourteenth, fifteenth, sixteenth;
    while (check_number != n)
    {   
	// Luhn_number is the counterth number of n 
	luhn_number = (n % quotient) / (quotient / 10);
	// This is the current total number that has been recorded, when this matches n then the while loop terminates
	check_number = (n % quotient);
	if ((counter % 2) == 0)
	{
	    // If the counter is even add the digits of product current counterth number (luhn_number) * 2
	    sum += ((luhn_number * 2) % 10) + ((luhn_number * 2) / 10);
	}
	else
	{
	    sum += luhn_number; // If the counter is odd then add to the sum the current counterth number (luhn_number)
	}
	if (counter == 13)
        {
	    thirteenth = luhn_number; // Record thirteenth number
	}
	else if (counter == 14)
	{
 	    fourteenth = luhn_number; // Record fourteenth number
	}
	else if (counter == 15)
	{
	    fifteenth = luhn_number; // Record fifteenth number
	}
	else if (counter == 16)
	{
	    sixteenth = luhn_number; // Record sixteenth number
	}
	counter++;
	quotient *= 10;
    }
    // Determines the type of card after Luhns Algorithm and correct n length has been satisfied, (counter - 1) = number n length
    if ((sum % 10) == 0 && ((counter - 1) == 13 || (counter - 1) == 15 || (counter - 1) == 16))
    {
	if ((counter - 1) == 13  && thirteenth == 4)
	{
	    printf("VISA\n");
	}
	else if ((counter - 1) == 15 && fifteenth == 3 && (fourteenth == 4 || fourteenth == 7))
	{
	    printf("AMEX\n");
	}
	else if ((counter - 1) == 16)
	{
	    if (sixteenth == 4)
	    {
		printf("VISA\n");
            }
	    else if (sixteenth == 5 && (fifteenth == 1 || fifteenth == 2 || fifteenth == 3 || fifteenth == 4 || fifteenth == 5))
	    {
		printf("MASTERCARD\n");
            }
	    else
	    {
		printf("INVALID\n");
	    }
        }
	else
	{
	    printf("INVALID\n");
	}
    }
    else
    {
	printf("INVALID\n");
    }
}
