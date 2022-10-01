#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int transfer(char *a, char *o, int oPtr);
int evalation(char *a, int aPtr);
int hierarchy(char operand);
char output[100] = {0};

int main()
{
    char formula[100] = {0};
    char output[100] = {0};
    int oPtr;
    int ans;
    printf("Please enter a formula:\n");
    scanf("%s", formula);
    oPtr = transfer(formula, output, 0);
    printf("\nPostfix:%s\n", output);
    ans = evalation(output, oPtr);
    printf("\nthe answer is:%d\n", ans);
    system("pause");
}

int transfer(char *a, char *o, int oPtr) // infix-to-postfix//
{
    int i = 0, j, k;
    int m = strlen(a);
    char stack[100] = {0};
    int sPtr = 0;
    for (i = 0; i < m; i++)
    {
        switch (a[i])
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            if (stack[sPtr] == '^')
            {
                stack[sPtr] = '^';
                sPtr++;
            }
            while (sPtr != 0 && a[i] != '(' && hierarchy(stack[sPtr - 1]) >= hierarchy(a[i]))
            {
                o[oPtr] = stack[sPtr - 1];
                stack[sPtr - 1] = '\0';
                oPtr++;
                sPtr--;
            }
            stack[sPtr] = a[i];
            sPtr++;
            break;
        case '(':
            stack[sPtr] = a[i];
            sPtr++;
            break;
        case ')':
            while (stack[sPtr - 1] != '(')
            {
                o[oPtr] = stack[sPtr - 1];
                stack[sPtr - 1] = '\0';
                oPtr++;
                sPtr--;
            }
            stack[sPtr - 1] = '\0';
            sPtr--;
            break;
        default:
            o[oPtr] = a[i];
            oPtr++;
            break;
        }
        printf("%-8c %-8s %-8s\n", a[i], stack, o);
    }
    while (sPtr != 0)
    {
        o[oPtr] = stack[sPtr - 1];
        stack[sPtr - 1] = '\0';
        oPtr++;
        sPtr--;
    }
    return oPtr;
}

int evalation(char *a, int aPtr)
{
    int i, j;
    int stack[100] = {0};
    int sPtr = 0;
    int ans = 0;
    for (i = 0; i < aPtr; i++)
    {
        switch (a[i])
        {
        case '+':
            stack[sPtr - 2] = stack[sPtr - 2] + stack[sPtr - 1];
            stack[sPtr - 1] = '\0';
            sPtr--;
            break;
        case '-':
            stack[sPtr - 2] = stack[sPtr - 2] - stack[sPtr - 1];
            stack[sPtr - 1] = '\0';
            sPtr--;
            break;
        case '*':
            stack[sPtr - 2] = stack[sPtr - 2] * stack[sPtr - 1];
            stack[sPtr - 1] = '\0';
            sPtr--;
            break;
        case '/':
            stack[sPtr - 2] = stack[sPtr - 2] / stack[sPtr - 1];
            stack[sPtr - 1] = '\0';
            sPtr--;
            break;
        case '^':
            stack[sPtr - 2] = pow(stack[sPtr - 2], stack[sPtr - 1]);
            stack[sPtr - 1] = '\0';
            sPtr--;
            break;
        default:
            stack[sPtr] = a[i] - '0';
            sPtr++;
            break;
        }
        for (j = 0; stack[j] != 0; j++)
        {
            printf("%d ", stack[j]);
        }
        puts("");
    }
    return stack[0];
}

int hierarchy(char operand)
{
    switch (operand)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

// A+B*C^(2^3)/(A+B)//