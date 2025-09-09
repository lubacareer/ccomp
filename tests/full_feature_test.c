#include <stdio.h>

// Struct definition
struct Point {
    int x;
    int y;
};

// Union definition
union Data {
    int i;
    float f;
    char s[20];
};

// Typedef
typedef int MyInt;

// Function declaration
int add(int a, int b);
void print_message(char *msg);

// Main function
int main() {
    // Variable declarations
    MyInt a = 5;
    int b = 3;
    float c = 2.5f;
    char d = 'B';
    int result;
    int arr[3] = {10, 20, 30};
    int *ptr = &a;
    struct Point p1;
    union Data data;

    // Assignment operations
    result = a + b; // 8
    result += 1;    // 9
    result -= b;    // 6
    result *= 2;    // 12
    result /= 3;    // 4
    result %= 3;    // 1

    // Arithmetic operations
    int sum = a + b;
    int diff = a - b;
    int prod = a * b;
    int div_res = a / b;
    int mod_res = a % b;

    // Unary operations
    int neg_a = -a;
    int not_a = !a; // Logical NOT
    int addr_a = (int)&a; // Address-of
    int deref_ptr = *ptr; // Dereference

    // Relational operations
    int eq = (a == b); // 0
    int ne = (a != b); // 1
    int lt = (a < b);  // 0
    int le = (a <= b); // 0
    int gt = (a > b);  // 1
    int ge = (a >= b); // 1

    // Logical operations (short-circuit evaluation)
    int logical_and = (a > 0 && b < 10); // 1
    int logical_or = (a < 0 || b > 10);  // 0

    // If-else statements
    if (a > b) {
        print_message("a is greater than b");
    } else if (a < b) {
        print_message("a is less than b");
    } else {
        print_message("a is equal to b");
    }

    // While loop
    int i = 0;
    while (i < 3) {
        printf("While loop iteration: %d\n", i);
        i++;
    }

    // Do-while loop
    int j = 0;
    do {
        printf("Do-while loop iteration: %d\n", j);
        j++;
    } while (j < 2);

    // For loop
    for (int k = 0; k < 2; k++) {
        printf("For loop iteration: %d\n", k);
    }

    // Function call
    int sum_ab = add(a, b);
    printf("Sum of a and b: %d\n", sum_ab);

    // Array access
    int first_element = arr[0];
    arr[1] = 25;
    printf("Array element at index 1: %d\n", arr[1]);

    // Struct member access
    p1.x = 100;
    p1.y = 200;
    printf("Point p1: (%d, %d)\n", p1.x, p1.y);

    // Union member access
    data.i = 123;
    printf("Union data.i: %d\n", data.i);
    data.f = 45.67f;
    printf("Union data.f: %f\n", data.f);

    // Ternary operator
    int max = (a > b) ? a : b;
    printf("Max of a and b: %d\n", max);

    // Cast
    float float_a = (float)a;
    printf("Float a: %f\n", float_a);

    /* end_main: */
    printf("End of main function.\n");

    return 0;
}

// Function definition
int add(int a, int b) {
    return a + b;
}

void print_message(char *msg) {
    printf("%s\n", msg);
}
