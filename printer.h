#ifndef __PRINTERH__
#define __PRINTERH__


#include "utils.h"

using namespace std;
using namespace parser;


void p(const string &a){
    cout << a<<"\n";
}
void p(const float &f){
    cout<<f<<"\n";
}
void p(const parser::Vec3i &v){ //Prints vector
    cout <<"< " << v.x << " " << v.y << " " << v.z << " >";
}
void p(const parser::Vec3f &v){ //Prints vector
    cout <<"" << v.x << " " << v.y << " " << v.z <<"\n";
}
void p(const Vec4f &v){
    cout << v.w << " " << v.x << " "<<   v.y << " " <<v.z<<"\n";
}
void p(const vector<PointLight> &point_lights){
    for(auto i: point_lights){
        p("intensity: ");
        p(i.intensity);
        p(" -- ");
        p("position: ");
        p(i.position);
        p(" | ");
    }
}
void p(const std::vector<Material> &materials){
    for(auto i: materials){
        p( "Ambient: ");
        p( i.ambient);
        p(" -- ");
        p("diffuse: ");
        p(i.diffuse);
        p(" -- ");
        p("mirror: ");
        p(i.mirror);
        p(" -- ");
        p("phong_exponent: ");
        p(i.phong_exponent);
        p(" -- ");
        p("specular: ");
        p(i.specular);
        p(" | " ); 

    }
    p("\n");
}

void p(const Face &face){
    cout << face.v0_id<<" -- " << face.v1_id << " -- " << face.v2_id << "|" << "\n";
}
void p(const std::vector<Vec3f> &vertex_data) {
    for(auto i: vertex_data){
        p("vertex_data: ");
        p(i);
        p("\n");
    }
}
void p(const std::vector<Face> &faces){
    for(auto i: faces)
        p(i);
}
void p(const Mesh &mesh){
    p(" mesh: ");
    p(" faces: ");
    p(mesh.faces);
    p(" material_id: ");
    p(mesh.material_id);
}
void p(const std::vector<Mesh>& meshes){
    for(int i=0;i<meshes.size();i++){
        p(meshes.at(i));
    }
}
// for(int i=0;i<.size();i++){
//         p([i]);
//     }
void p(const Sphere &s){
    p("Sphere: ");
    p(" center_vertex_id: ");
    p(s.center_vertex_id);
    p(" material_id: ");
    p(s.material_id);
    p(" radius: ");
    p(s.radius);
}

void p(const Triangle &t){
    p(" indices: ");
    p(t.indices);
    p(" material_id: ");
    p(t.material_id);
    p("\n");
}


void p(const std::vector<Triangle> &triangles){
    cout << "Triangle ";
    for(auto i: triangles)
        p(i);
    cout<< "|";
}

void p(const std::vector<Sphere> &spheres){
    cout << "Spheres: ";
    for(auto i: spheres){
        p(i);
    }
}


void p(const std::vector<Camera> &cams){
    for(int i=0;i<cams.size();i++){
        p("position: ");
        p(cams[i].position);
        p("\ngaze: ");
        p(cams[i].gaze);
        p("\nup: ");
        p(cams[i].up);
        p("\nnear_plane: ");
        p(cams[i].near_plane);
        p("\nnear_distance: ");
        p(cams[i].near_distance);
        p("\nimage_width: ");
        p(cams[i].image_width);
        p("\nimage_height: ");
        p(cams[i].image_height);
        p("\nimage_name: ");
        p(cams[i].image_name);
        p("\n ");
    }
}


#endif