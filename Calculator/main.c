#include "gpio.h"
#include "common_macros.h"
#include "lcd.h"
#include "std_types.h"
#include <util/delay.h>

void Calc_app()
{
    // Initialize variables
    uint8 arr[3] = {'U', 'U', 'U'};
    uint8 arr2[3] = {'U', 'U', 'U'};
    uint16 num1;
    uint16 num2;
    uint8 operator = 'U';
    uint8 equal = 'U';
    uint16 result;

    // Get the first number from the user
    for (int i = 0; i < 3; i++)
    {
        uint8 temp = KEYPAD_getPressedKey();
        _delay_ms(200);

        // Check if the pressed key is an operator (+, -, *, or /)
        if (temp == 37 || temp == 45 || temp == 42 || temp == 43)
        {
            operator = temp;
            break;
        }

        arr[i] = temp;
        LCD_intgerToString(temp);
        _delay_ms(200);
    }

    // Convert the first number from an array of digits to a single number
    if (arr[0] == 'U' && arr[1] == 'U' && arr[2] == 'U')
    {
        num1 = 0;
    }
    else if (arr[1] == 'U' && arr[2] == 'U')
    {
        num1 = arr[0];
    }
    else if (arr[2] == 'U')
    {
        num1 = (arr[0] * 10) + arr[1];
    }
    else
    {
        num1 = (arr[0] * 100) + (arr[1] * 10) + arr[2];
    }

    // Get the operator from the user
    if (operator == 'U')
    {
        operator = KEYPAD_getPressedKey();
    }

    LCD_displayCharacter(operator);
    _delay_ms(200);

    // Get the second number from the user
    for (int i = 0; i < 3; i++)
    {
        uint8 temp = KEYPAD_getPressedKey();
        _delay_ms(200);

        // Check if the pressed key is the equal sign (=)
        if (temp == '=')
        {
            equal = temp;
            break;
        }

        arr2[i] = temp;
        LCD_intgerToString(temp);
        _delay_ms(200);
    }

    // Convert the second number from an array of digits to a single number
    if (arr2[0] == 'U' && arr2[1] == 'U' && arr2[2] == 'U')
    {
        num2 = 0;
    }
    else if (arr2[1] == 'U' && arr2[2] == 'U')
    {
        num2 = arr2[0];
    }
    else if (arr2[2] == 'U')
    {
        num2 = (arr2[0] * 10) + arr2[1];
    }
    else
    {
        num2 = (arr2[0] * 100) + (arr2[1] * 10) + arr2[2];
    }

    // Wait for the user to press the equal sign (=)
    while (equal != '=')
        equal = KEYPAD_getPressedKey();

    LCD_displayCharacter(equal);
    _delay_ms(200);

    // Perform the calculation based on the operator
    if (operator == '+')
    {
        result = num1 + num2;
    }
    else if (operator == '-')
    {
        result = num1 - num2;
    }
    else if (operator == '*')
    {
        result = num1 * num2;
    }
    else
    {
        result = num1 / num2;
    }

    // Display the result on the LCD screen
    LCD_intgerToString(result);
    _delay_ms(500);
}

int main()
{
    // Initialize the LCD
    LCD_init();

    while (1)
    {
        // Run the calculator application
        Calc_app();

        _delay_ms(100);

        // Clear the LCD screen for the next calculation
        LCD_clearScreen();
    }
}
