# 0 "test2.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "test2.c"
int foo() {
    return 0;
}

int foo() {
    return 1;
}

int main(int argc, char **argv) {
    int a = 1;
    int a = 2;
    bar();
    return 0;
}
