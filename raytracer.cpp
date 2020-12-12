#include "checkWhatCollides.h"
#include <thread>
#include <pthread.h>
#include <sstream> 

typedef unsigned char RGB[3];
using namespace std;
using namespace parser;



// template <typename T> 
// void p(T const& t) 
// { 
//     cout << "slm\n";
//     cout << t; 
// }

std::vector<Transformation> getTransformationVectorFromString(std::string transformations){//TODO//Added newly
//Done gibi, need test
    string tmp = "";
    Transformation tempTransformation;
    std::vector<Transformation> res;
    for(auto c:transformations){
        
        if(c==' '){
            tempTransformation.type = tmp[0];
            tmp.erase(0,1);
            //tempTransformation.id = atoi();
            stringstream stream(tmp); 
            int x = 0;
            stream >> x;
            tempTransformation.id = x;

            res.push_back(tempTransformation);

            tmp = "";
        }else{
            tmp = tmp+c;
        }
    }
    return res;
}

Scene idleriDuzelt(Scene scene){//TODO transformaiton idleri
    
    for(int i=0;i< scene.meshes.size();i++){
        scene.meshes[i].material_id--;
        scene.meshes[i].texture_id--;
        //cout << scene.meshes[i].transformations<<endl;
        scene.meshes[i].transformasyonlar = getTransformationVectorFromString(scene.meshes[i].transformations);
        for(int j=0;j<scene.meshes[i].faces.size();j++){
            scene.meshes[i].faces[j].v0_id--;
            scene.meshes[i].faces[j].v1_id--;
            scene.meshes[i].faces[j].v2_id--;
        }
        for(int j=0;j<scene.meshes[i].transformasyonlar.size();j++){
            scene.meshes[i].transformasyonlar[j].id--;    
        }
    }
    for(int i=0;i< scene.triangles.size();i++){
        scene.triangles[i].material_id--;
        scene.triangles[i].indices.v0_id--;
        scene.triangles[i].indices.v1_id--;
        scene.triangles[i].indices.v2_id--;
        scene.triangles[i].texture_id--;
        scene.triangles[i].transformasyonlar = getTransformationVectorFromString(scene.triangles[i].transformations);
        for(int j=0;j<scene.triangles[i].transformasyonlar.size();j++){
            scene.triangles[i].transformasyonlar[j].id--;    
        }
    }
    for(int i=0;i<scene.spheres.size();i++){
        scene.spheres[i].center_vertex_id--;
        scene.spheres[i].material_id--;
        scene.spheres[i].texture_id--;
        scene.triangles[i].transformasyonlar = getTransformationVectorFromString(scene.spheres[i].transformations);
        for(int j=0;j<scene.spheres[i].transformasyonlar.size();j++){
            scene.spheres[i].transformasyonlar[j].id--;    
        }
        
        //cout << scene.spheres[i].transformations<<endl;
    }
    

    // for(int i=0;i<scene.cameras;i++)
    //     scene.cameras[i].;
    //throw ("deneme");
    return scene;
}
RaySabitleri rayiHazirla(const Camera &cam){
    Vec3f gaze =  normalize(cam.gaze);
    Vec3f vector_u = cross(gaze, cam.up);//Yana dogru
    vector_u = normalize(vector_u);
    Vec3f vector_v  = cross(vector_u, gaze);

    //Planein merkezi
    Vec3f merkez;
    merkez.x = cam.position.x + gaze.x * cam.near_distance;
    merkez.y = cam.position.y + gaze.y * cam.near_distance;
    merkez.z = cam.position.z + gaze.z * cam.near_distance;

    //Planein sol en ustu
    Vec3f sol_en_ust;
    sol_en_ust.x = merkez.x + vector_u.x*cam.near_plane.x + vector_v.x*cam.near_plane.w ;
    sol_en_ust.y = merkez.y + vector_u.y*cam.near_plane.x + vector_v.y*cam.near_plane.w ;
    sol_en_ust.z = merkez.z + vector_u.z*cam.near_plane.x + vector_v.z*cam.near_plane.w ;
    //Gaze, vector_u vector_v sol_en_ust
    RaySabitleri res;
    res.vector_u = vector_u;
    res.vector_v = vector_v;
    res.sol_en_ust = sol_en_ust;
    return res;
}

Scene applyTransformations(Scene scene){//TODO
    p(scene.meshes);
    p(scene.triangles);
    p(scene.spheres);
    for(auto &sphere: scene.spheres){
        for(auto transformasyon: sphere.transformasyonlar){
            if(transformasyon.type=='r'){
                Vec3f newCenter = rotate(scene.vertex_data[sphere.center_vertex_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                scene.vertex_data.push_back(newCenter);
                sphere.center_vertex_id = scene.vertex_data.size() - 1;
                
            }else if(transformasyon.type == 't'){
                Vec3f newCenter = translate(scene.vertex_data[sphere.center_vertex_id],scene.translations[transformasyon.id]);
                scene.vertex_data.push_back(newCenter);
                sphere.center_vertex_id = scene.vertex_data.size() - 1;
            }else if(transformasyon.type == 's'){
                auto newSphere = scale(sphere,scene.scalings[transformasyon.id]);
                sphere.radius = newSphere.radius;
            }else{
                cout<<"ERROR! UNKNOWN TRANSFORMATION" + transformasyon.type<<endl;
            }
        }    
    }
    for(auto &triangle: scene.triangles){
        for(auto transformasyon: triangle.transformasyonlar){
            if(transformasyon.type=='r'){
                // Vec3f newV0 = rotate(scene.vertex_data[triangle.indices.v0_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                // scene.vertex_data.push_back(newV0);
                // triangle.indices.v0_id = scene.vertex_data.size() - 1;
                // Vec3f newV1 = rotate(scene.vertex_data[triangle.indices.v1_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                // scene.vertex_data.push_back(newV1);
                // triangle.indices.v1_id = scene.vertex_data.size() - 1;
                
                // Vec3f newV2 = rotate(scene.vertex_data[triangle.indices.v2_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                // scene.vertex_data.push_back(newV2);
                // triangle.indices.v2_id = scene.vertex_data.size() - 1;
                
                
            }else if(transformasyon.type == 't'){
            //     Vec3f newV0 = translate(scene.vertex_data[triangle.indices.v0_id],scene.translations[transformasyon.id]);
            //     scene.vertex_data.push_back(newV0);
            //     triangle.indices.v0_id = scene.vertex_data.size() - 1;
            //     Vec3f newV1 = translate(scene.vertex_data[triangle.indices.v1_id],scene.translations[transformasyon.id]);
            //     scene.vertex_data.push_back(newV1);
            //     triangle.indices.v1_id = scene.vertex_data.size() - 1;

            //     Vec3f newV2 = translate(scene.vertex_data[triangle.indices.v2_id],scene.translations[transformasyon.id]);
            //     scene.vertex_data.push_back(newV2);
            //     triangle.indices.v2_id = scene.vertex_data.size() - 1;

            }else if(transformasyon.type == 's'){
            //     Vec3f newV0 = scale(scene.vertex_data[triangle.indices.v0_id],scene.scalings[transformasyon.id]);
            //     scene.vertex_data.push_back(newV0);
            //     triangle.indices.v0_id = scene.vertex_data.size() - 1;

            //     Vec3f newV1 = scale(scene.vertex_data[triangle.indices.v1_id],scene.scalings[transformasyon.id]);
            //     scene.vertex_data.push_back(newV1);
            //     triangle.indices.v1_id = scene.vertex_data.size() - 1;

            //     Vec3f newV2 = scale(scene.vertex_data[triangle.indices.v2_id],scene.scalings[transformasyon.id]);
            //     scene.vertex_data.push_back(newV2);
            //     triangle.indices.v2_id = scene.vertex_data.size() - 1;
            }else{
                cout<<"ERROR! UNKNOWN TRANSFORMATION" + transformasyon.type<<endl;
            }
        }    
    }
    for(auto &mesh: scene.meshes){
        for(auto &face: mesh.faces){
            for(auto transformasyon: mesh.transformasyonlar){
                if(transformasyon.type=='r'){
                    // Vec3f newV0 = rotate(scene.vertex_data[face.v0_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                    // scene.vertex_data.push_back(newV0);
                    // face.v0_id = scene.vertex_data.size() - 1;

                    // Vec3f newV1 = rotate(scene.vertex_data[face.v1_id],scene.rotations[transformasyon.id].angle, {scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                    // scene.vertex_data.push_back(newV1);
                    // face.v1_id = scene.vertex_data.size() - 1;

                    // Vec3f newV2 = rotate(scene.vertex_data[face.v2_id],scene.rotations[transformasyon.id].angle, {scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                    // scene.vertex_data.push_back(newV2);
                    // face.v2_id = scene.vertex_data.size() - 1;
                }else if(transformasyon.type == 't'){
                     Vec3f newV0 = translate(scene.vertex_data[face.v0_id],scene.translations[transformasyon.id]);
                    scene.vertex_data.push_back(newV0);
                    face.v0_id = scene.vertex_data.size() - 1;

                    Vec3f newV1 = translate(scene.vertex_data[face.v1_id],scene.translations[transformasyon.id]);
                    scene.vertex_data.push_back(newV1);
                    face.v1_id = scene.vertex_data.size() - 1;

                    Vec3f newV2 = translate(scene.vertex_data[face.v2_id],scene.translations[transformasyon.id]);
                    scene.vertex_data.push_back(newV2);
                    face.v2_id = scene.vertex_data.size() - 1;


                }else if(transformasyon.type == 's'){

                    // Vec3f newV0 = scale(scene.vertex_data[face.v0_id],scene.scalings[transformasyon.id]);
                    // scene.vertex_data.push_back(newV0);
                    // face.v0_id = scene.vertex_data.size() - 1;

                    // Vec3f newV1 = scale(scene.vertex_data[face.v1_id],scene.scalings[transformasyon.id]);
                    // scene.vertex_data.push_back(newV1);
                    // face.v1_id = scene.vertex_data.size() - 1;

                    // Vec3f newV2 = scale(scene.vertex_data[face.v2_id],scene.scalings[transformasyon.id]);
                    // scene.vertex_data.push_back(newV2);
                    // face.v2_id = scene.vertex_data.size() - 1;

                }else{
                    cout<<"ERROR! UNKNOWN TRANSFORMATION " + transformasyon.type<<endl;
                }
            }    
        }
    }

    p("--------------------------------");
    p(scene.meshes);
    p(scene.triangles);
    p(scene.spheres);
    return scene;

}

void threadable(int i, int to,const Scene &scene,const RaySabitleri &raySabitleri,unsigned char * image,const int &width,const  int &height,const int &cam){
    for(;i<to;i++){
        p("image creating boss..."+to_string(i)+"/"+to_string(to));
        for(int j=0;j<width;j++){
            

            auto ray  = generateRay(i,j,scene.cameras[cam], raySabitleri);
            // if(i%100==0 && j%100==0) {
                
            //     std::cout << i << " " << j<< " " << ray.yon.x << " ";
            //     std::cout << ray.yon.y << " ";
            //     std::cout << ray.yon.z << std::endl;
            // }
            //TODO transformasyonlari burada uygula
            Vec3i pixel = checkWhatCollides(ray,scene);//bir pixel

            image[i*width*3+3*j  ] =(unsigned char)  pixel.x; 
            image[i*width*3+3*j+1] =(unsigned char)  pixel.y;
            image[i*width*3+3*j+2] =(unsigned char)  pixel.z;
        }
    }
}
/**
 * Gets the scene and returns the image as a char* 
 * Uses details like width and height 
 * 
 * 
 * 
 */
void generateImages(const Scene &scene){
    cout << "Generating Images\n";
    cout << "Cam numbers: " +to_string(scene.cameras.size())<<"\n";
    for(int cam = 0; cam < scene.cameras.size(); cam++){
        cout<<"cam "+to_string(cam)<<"\n";
        RaySabitleri raySabitleri = rayiHazirla(scene.cameras[cam]);
        unsigned char * image = new unsigned char[(scene.cameras[cam].image_height*scene.cameras[cam].image_width)* 3];
        int width = scene.cameras[cam].image_width;
        int height = scene.cameras[cam].image_height;
        int thread_number=4;
        //thread 1: 0-height/4
        //thread 2: height/4+1-height/2
        //thread 3: height/2+1-3*height/4
        //thread 4: 3*height/4+1-height
        //std::thread first();
        //threadable(0,height/4,scene,raySabitleri,image,width,height,cam);
        //TODO less than 4 i ise tek thread
        const auto processor_count = std::thread::hardware_concurrency();
        cout << processor_count<<" is the processor count\n";
        std::thread t1 = std::thread(threadable,0         ,height/4    ,scene,raySabitleri,image,width,height,cam);
        std::thread t2 = std::thread(threadable,height/4  ,height/2    ,scene,raySabitleri,image,width,height,cam);
        std::thread t3 = std::thread(threadable,height/2  ,3*height/4  ,scene,raySabitleri,image,width,height,cam);
        std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t4 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t5 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t6 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t7 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);
        // std::thread t8 = std::thread(threadable,3*height/4,height      ,scene,raySabitleri,image,width,height,cam);

        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        // t1.join();
        
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        // thread anan = thread(tmpthreadable);
        // anan.join();
        p("Generating image: "+scene.cameras[cam].image_name);
        write_ppm(scene.cameras[cam].image_name.c_str(), image, scene.cameras[cam].image_width,scene.cameras[cam].image_height);



        // for(int i=0;i<height;i++){
        //     //if(i%(height/100)==0)
        //         p("image creating boss..."+to_string(i)+"/"+to_string(height));
        //     for(int j=0;j<width;j++){
                

        //         auto ray  = generateRay(i,j,scene.cameras[cam], raySabitleri);
        //         // if(i%100==0 && j%100==0) {
                    
        //         //     std::cout << i << " " << j<< " " << ray.yon.x << " ";
        //         //     std::cout << ray.yon.y << " ";
        //         //     std::cout << ray.yon.z << std::endl;
        //         // }
        //         Vec3i pixel = checkWhatCollides(ray,scene);//bir pixel

        //         image[i*width*3+3*j  ] =(unsigned char)  pixel.x; 
        //         image[i*width*3+3*j+1] =(unsigned char)  pixel.y;
        //         image[i*width*3+3*j+2] =(unsigned char)  pixel.z;
        //     }
        // }
        // p("Generating image: "+scene.cameras[cam].image_name);
        // write_ppm(scene.cameras[cam].image_name.c_str(), image, scene.cameras[cam].image_width,scene.cameras[cam].image_height);
    }
    
}



int main(int argc, char* argv[])
{
    // Sample usage for reading an XML scene file
    parser::Scene scene;
    p("Basladi");
    scene.loadFromXml(argv[1]);
    p(scene.cameras.size());
    p("No of cameras");
    scene = idleriDuzelt(scene);
    scene = applyTransformations(scene);
    generateImages(scene);



    // unsigned char* image = new unsigned char [width * height * 3];

    // int i = 0;
    // for (int y = 0; y < height; ++y)
    // {
    //     for (int x = 0; x < width; ++x)
    //     {
    //         int colIdx = x / columnWidth;
    //         image[i++] = BAR_COLOR[colIdx][0];
    //         image[i++] = BAR_COLOR[colIdx][1];
    //         image[i++] = BAR_COLOR[colIdx][2];
    //     }
    // }

    //write_ppm("test.ppm", image, scene.cameras[0].image_width,scene.cameras[0].image_height);

}
