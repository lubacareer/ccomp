int foo(int a, int b) {
    return a + b;
}

int main() {
    int x = 1;
    char y = 'a';
    foo(x); // Wrong number of arguments
    foo(x, y); // Wrong type of arguments
    return 'a'; // Wrong return type
}
