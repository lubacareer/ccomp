int a = 1;

int main() {
    int b = 2;
    int a = 3;
    {
        int c = 4;
        d = 5; // Should cause an error
    }
    return 0;
}
