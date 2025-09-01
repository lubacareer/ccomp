# 0 "test9.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "test9.c"
int main() {
    int a = 1;
    int b = 2;
    char c = 'a';
    int *p = &a;

    if (a && b) {}
    if (a > c) {}
    if (a == c) {}
    if (!a) {}
    *a;

    return 0;
}
