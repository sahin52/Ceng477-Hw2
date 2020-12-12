#include <iostream>
#include <stdarg.h>
#include "../printer.h"

void rotateTest(){
    auto rot = rotate({0.5, -0.5, -2},45,{0.0, 0.0, 1.0});
    p(rot);
}

int main(){
    rotateTest();
    // translate();
    // scale();


}