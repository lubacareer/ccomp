int main() {
    int a = 1;
    int b = 2;
    char c = 'a';
    int *p = &a;

    if (a && b) {} // Logical operator with non-boolean operands
    if (a > c) {} // Relational operator with non-numeric operands
    if (a == c) {} // Equality operator with operands of different types
    if (!a) {} // Logical NOT on a non-boolean
    *a; // Dereference on a non-pointer

    return 0;
}
