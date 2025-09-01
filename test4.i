# 0 "test4.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "test4.c"
int foo(int a, int b) {
    return a + b;
}

int main() {
    int x = 1;
    char y = 'a';
    foo(x);
    foo(x, y);
    return 'a';
}
