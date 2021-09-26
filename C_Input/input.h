#define elif else if

#include <stdlib.h>
#include <math.h>

void input_int(int *value)
{
    long long result;
    char input_value;
    int mark;
    int Ok = 1;

    while (Ok)
    {
        Ok = 0;
        result = 0;
        mark = 1;

        input_value = getchar();
        if (input_value == '-')
        {
            mark = -1;
            input_value = getchar();
        }
        if (input_value == '\n')
            Ok = 1;
        else
            do
            {
                if (input_value >= '0' && input_value <= '9')
                    result = result * 10 + (int)input_value-48;
                else
                    Ok = 1;
            } while ((input_value = getchar()) != '\n');
        if (Ok)
            printf("INCORRECT VALUE\nValue must be integer\nInput new value:");
    }

    *value = result * mark;
}

void input_float(double *value)
{
    double result;
    char input_value;
    int mark;
    int Ok = 1;
    int dot, dot_i;

    while (Ok)
    {
        Ok = 0;
        result = 0;
        mark = 1;

        input_value = getchar();
        if (input_value == '-')
        {
            mark = -1;
            input_value = getchar();
        }
        if (input_value == '\n')
            Ok = 1;
        else
            for (dot_i = 0, dot = 0; input_value != '\n'; input_value = getchar())
            {
                if (input_value >= '0' && input_value <= '9')
                {
                    dot_i += dot;
                    result = result * 10 + (int) input_value - 48;
                }
                elif (( input_value == '.' ||  input_value == ',') && dot == 0)
                    dot = 1;
                else
                    Ok = 1;
            }
        if (Ok)
            printf("INCORRECT VALUE\nValue must be float\nInput new value:");
    }

    *value = result / pow(10, dot_i) * mark;
}
