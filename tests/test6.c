int main() {
    int x = 1;
    int arr[10];
    char c = 'a';

    if (c) {} // Non-integer condition
    while (c) {} // Non-integer condition

    x[0] = 1; // Using [] on a non-array
    arr[c] = 1; // Using a non-integer index

    return 0;
}
