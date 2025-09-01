#define MAX_SIZE 100

// External variable declaration
extern int global_counter;

// Volatile variable
volatile int status_register;

// Struct definition
struct Point {
    int x;
    int y;
};

// Union definition
union Data {
    int i;
    float f;
    char str[20];
};

// Enum definition
enum Color {
    RED,
    GREEN,
    BLUE
};

// Typedef for a struct
typedef struct Point Point2D;

// Static variable
static int file_scope_variable = 0;

// Const variable
const double PI = 3.14159;

// Forward declaration of a struct
struct Node;

// Function prototype
void print_point(Point2D p);

// Inline function
inline int max(int a, int b) {
    return a > b ? a : b;
}

// A static inline function
static inline int min(int a, int b) {
    return a < b ? a : b;
}

// Function with complex declarator (pointer to function)
void (*signal_handler)(int);

int main() {
    // Multiple declarations
    int i = 0, j, k = 10;
    
    // Array of pointers
    char *messages[3];
    messages[0] = "Hello";
    messages[1] = "World";
    messages[2] = "!";

    // Pointer to an array
    int (*matrix)[2];
    int arr[2][2] = {{1, 2}, {3, 4}};
    matrix = arr;

    // Struct and union usage
    Point2D p1 = {10, 20};
    union Data data;
    data.i = 10;

    // Control flow: for loop and if-else
    for (i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            print_point(p1);
        } else {
            // do nothing
        }
    }

    // Control flow: while and do-while
    int count = 5;
    while (count > 0) {
        count--;
    }
    do {
        count++;
    } while (count < 5);

    // Control flow: switch (removed for testing)
}

void print_point(Point2D p) {
    // This function is just a stub for demonstration
}
