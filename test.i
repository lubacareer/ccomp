# 0 "test.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "test.c"



extern int global_counter;


volatile int status_register;


struct Point {
    int x;
    int y;
};


union Data {
    int i;
    float f;
    char str[20];
};


enum Color {
    RED,
    GREEN,
    BLUE
};


typedef struct Point Point2D;


static int file_scope_variable = 0;


const double PI = 3.14159;


struct Node;


void print_point(Point2D p);


inline int max(int a, int b) {
    return a > b ? a : b;
}


static inline int min(int a, int b) {
    return a < b ? a : b;
}


void (*signal_handler)(int);

int main() {

    int i = 0, j, k = 10;


    char *messages[3];
    messages[0] = "Hello";
    messages[1] = "World";
    messages[2] = "!";


    int (*matrix)[2];
    int arr[2][2] = {{1, 2}, {3, 4}};
    matrix = arr;


    Point2D p1 = {10, 20};
    union Data data;
    data.i = 10;


    for (i = 0; i < 3; i++) {
        if (i % 2 == 0) {
            print_point(p1);
        } else {

        }
    }


    int count = 5;
    while (count > 0) {
        count--;
    }
    do {
        count++;
    } while (count < 5);


}

void print_point(Point2D p) {

}
