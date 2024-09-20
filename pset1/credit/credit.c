#include <cs50.h>
#include <stdio.h>

// Program to validate credit card numbers

// Functions that will validate if credit card is valid for relevant company
bool amex(long cc);
bool mastercard(long cc);
bool visa(long cc);

int main(void)
{
    long cc = get_long("What's your credit card number? ");

    // If functions are true, print out type of card. Otherwise, print invalid
    if (amex(cc))
    {
        printf("AMEX\n");
    }
    else if (mastercard(cc))
    {
        printf("MASTERCARD\n");
    }
    else if (visa(cc))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Function validate amex
bool amex(long cc)
{
    int digits = 0;
    long sum = 0;
    long first_two_digits = 0;
    long i = 0;
    long j = 0;

    // Multiply every other digit by 2, starting with second-to-last digit
    for (i = 100; i <= cc * 10; i = i * 100)
    {
        if (((cc % i) / (i / 10)) < 5)
        {
            sum = sum + (((cc % i) / (i / 10)) * 2);
        }
        else
        {
            int test = (cc % i) / (i / 10);
            sum = sum + (((cc % i) / (i / 10) * 2) / 10) + (((cc % i) / (i / 10) * 2) % 10);
        }
        digits++;
    }

    // Add the sum of every other digit starting with the last
    for (j = 10; j <= cc * 10; j = j * 100)
    {
        sum = sum + ((cc % j) / (j / 10));
        digits++;
    }

    // Find if modulo 10 of sum of all digits is zero
    if (sum % 10 != 0)
    {
        return false;
    }

    // Find and validate the first two digits
    if (digits > 1)
    {
        if (i > j)
        {
            first_two_digits = cc / (i / 10000);
        }
        else
        {
            first_two_digits = cc / (j / 10000);
        }
    }

    if (first_two_digits != 34 && first_two_digits != 37)
    {
        return false;
    }

    // Validate number of digits
    if (digits != 15)
    {
        return false;
    }

    return true;
}

// Function to validate mastercards
bool mastercard(long cc)
{
    int digits = 0;
    long sum = 0;
    long first_two_digits = 0;
    long i = 0;
    long j = 0;

    // Multiply every other digit by 2, starting with second-to-last digit
    for (i = 100; i <= cc * 10; i = i * 100)
    {
        if (((cc % i) / (i / 10)) < 5)
        {
            sum = sum + (((cc % i) / (i / 10)) * 2);
        }
        else
        {
            int test = (cc % i) / (i / 10);
            sum = sum + (((cc % i) / (i / 10) * 2) / 10) + (((cc % i) / (i / 10) * 2) % 10);
        }
        digits++;
    }

    // Add the sum of every other digit starting with the last
    for (j = 10; j <= cc * 10; j = j * 100)
    {
        sum = sum + ((cc % j) / (j / 10));
        digits++;
    }

    // Find if modulo 10 of sum of all digits is zero
    if (sum % 10 != 0)
    {
        return false;
    }

    // Find and validate the first two digits
    if (digits > 1)
    {
        if (i > j)
        {
            first_two_digits = cc / (i / 10000);
        }
        else
        {
            first_two_digits = cc / (j / 10000);
        }
    }

    if (first_two_digits > 55 || first_two_digits < 51)
    {
        return false;
    }

    // Validate number of digits
    if (digits != 16)
    {
        return false;
    }

    return true;
}

// Function to validate visa cards
bool visa(long cc)
{
    int digits = 0;
    long sum = 0;
    long first_digit = 0;
    long i = 0;
    long j = 0;

    // Multiply every other digit by 2, starting with second-to-last digit
    for (i = 100; i <= cc * 10; i = i * 100)
    {
        if (((cc % i) / (i / 10)) < 5)
        {
            sum = sum + (((cc % i) / (i / 10)) * 2);
        }
        else
        {
            int test = (cc % i) / (i / 10);
            sum = sum + (((cc % i) / (i / 10) * 2) / 10) + (((cc % i) / (i / 10) * 2) % 10);
        }
        digits++;
    }

    // Add the sum of every other digit starting with the last
    for (j = 10; j <= cc * 10; j = j * 100)
    {
        sum = sum + ((cc % j) / (j / 10));
        digits++;
    }

    // Find if modulo 10 of sum of all digits is zero
    if (sum % 10 != 0)
    {
        return false;
    }

    // Find and validate the first digit
    if (digits > 1)
    {
        if (i > j)
        {
            first_digit = cc / (i / 1000);
        }
        else
        {
            first_digit = cc / (j / 1000);
        }
    }
    if (first_digit != 4)
    {
        return false;
    }

    // Validate number of digits
    if (digits != 13 && digits != 16)
    {
        return false;
    }

    return true;
}