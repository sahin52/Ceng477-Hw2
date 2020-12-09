#include <iostream>
#include <stdarg.h>
int f(int, ... );

int f(int, ... ) {
    return 0;
}

int g() {
        f(1,2,3);
        return 0;
}

struct s{
    int a;
    int b;
};
void TEST(){
    s q = {
        .a = 2,
        .b = 1
    };
    s w = q;
    q.a =3;
    w.b =5;
    std::cout << q.a<<q.b;
    std::cout <<w.a<<w.b;


}

int main(){
    std::cout<<"-------------------------------START--------------------\n";
    TEST();
    std::cout<<"-------------------------------END-----------------------\n";
}