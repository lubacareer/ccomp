int foo() {
    return 0;
}

int foo() { // Duplicate function
    return 1;
}

int main(int argc, char **argv) { // main with arguments
    int a = 1;
    int a = 2; // Duplicate variable
    bar(); // Undefined function call
    return 0;
}
