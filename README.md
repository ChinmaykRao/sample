// 1. to find biggest of 2 no. using if else
#include <stdio.h>
int main()
{
 int a,b;
 printf("enter the 2 no\n");
 scanf("%d %d", a,b);
 if (a>b)
 {
 printf("%d is largest\n",a);
 }
 else if (b>a)
 {
 printf("%d is largest\n",b);
 }
 else 
 {
 printf("both are equal\n")
 }
 return 0;
 }

// 2. to print the grade of student
#include <stdio.h>

int main() {
    int mark;
    printf("Enter mark: ");
    scanf("%d", &mark);

    if (mark >= 90 && mark <= 100) {
        printf("Grade A\n");
    }
    else if (mark >= 75 && mark <= 89) {
        printf("Grade B\n");
    }
    else if (mark >= 60 && mark <= 74) {
        printf("Grade C\n");
    }
    else if (mark >= 50 && mark <= 59) {
        printf("Grade D\n");
    }
    else {
        printf("Grade F\n");
    }

    return 0;
}

// 3.to read roll no name and mark
#include <stdio.h>

int main() {
    char roll_no[20];
    char name[50];
    float pmarks, mmarks, cmarks;
    float totalmarks, percentage;

    printf("Enter the Roll No ");
    scanf("%s", roll_no);

    printf("Enter the Name ");
    scanf(" %[^\n]s", name);

    printf("Enter the Phy marks ");
    scanf("%f", &pmarks);

    printf("Enter the Math marks ");
    scanf("%f", &mmarks);

    printf("Enter the Chem marks ");
    scanf("%f", &cmarks);

    totalmarks = pmarks + mmarks + cmarks;
    percentage = (totalmarks / 300) * 100;

    printf("\n--- Summary ---\n");
    printf("Roll No: %s\n", roll_no);
    printf("Name: %s\n", name);
    printf("Phy Marks: %.2f\n", pmarks);
    printf("Math Marks: %.2f\n", mmarks);
    printf("Chem Marks: %.2f\n", cmarks);
    printf("Total Marks: %.2f\n", totalmarks);
    printf("Percentage: %.2f%%\n", percentage);

    
    return 0;
}

// 4.calculator pgm

#include <stdio.h>

int main() {
    float num1, num2, result;
    char operator;

    printf("Enter Number1: ");
    scanf("%f", &num1);

    printf("Enter the operator: ");
    scanf(" %c", &operator);

    printf("Enter Number2: ");
    scanf("%f", &num2);

    switch (operator) {
        case '+':
            result = num1 + num2;
            printf("Result: %.2f\n", result);
            break;
        case '-':
            result = num1 - num2;
            printf("Result: %.2f\n", result);
            break;
        case '*':
            result = num1 * num2;
            printf("Result: %.2f\n", result);
            break;
        case '/':
            if (num2 != 0) {
                result = num1 / num2;
                printf("Result: %.2f\n", result);
            } else {
                printf("Error\n");
            }
            break;
        default:
            printf("Invalid operator.\n");
    }

    return 0;
}
