#include <iostream>
#include <stdarg.h>
#include "../printer.h"
#include "../jpeg.h"

using namespace std;

void rotateTest(){
    auto rot = rotate({0.5, -0.5, -2},45,{0.0, 0.0, 1.0});
    p(rot);
}

void jpegTest(Scene &scene){
    char * filename = "earth_hd.jpg";
    string str = scene.textures[0].imageName;
    int width;
    int height;
    p("3");
    read_jpeg_header(filename,width,height);
    p("4");
    p(width);
    p(height);
    unsigned char * image = new unsigned char[width*height*3];
    read_jpeg(filename,image,width,height);
    unsigned char* anan = new unsigned char[200];
    for(int i=0;i<100;i++){
        cout << (int) image[i]<<"\n";
        if(i%3==2)
            p(fetch(scene,str,0,i/3));
    }

    for(int i=0;i<100;i++){
        anan[i]=image[i];
    }
    cout <<"anan\n";
    cout << anan<<"\n";
}

int main(int argc, char* argv[]){
    //rotateTest();
    Scene scene;
    p("1");
    p(argv[1]);
    scene.loadFromXml(argv[1]);
    p("2");
    // translate();
    // scale();
    jpegTest(scene);

}