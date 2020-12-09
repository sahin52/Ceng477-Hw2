#include "checkWhatCollides.h"
#include <thread>
#include <pthread.h>
typedef unsigned char RGB[3];
using namespace std;
using namespace parser;



// template <typename T> 
// void p(T const& t) 
// { 
//     cout << "slm\n";
//     cout << t; 
// }

Scene idleriDuzelt(Scene scene){
    
    for(int i=0;i< scene.meshes.size();i++){
        scene.meshes[i].material_id--;
        for(int j=0;j<scene.meshes[i].faces.size();j++){
            scene.meshes[i].faces[j].v0_id--;
            scene.meshes[i].faces[j].v1_id--;
            scene.meshes[i].faces[j].v2_id--;
        }
    }
    for(int i=0;i< scene.triangles.size();i++){
        scene.triangles[i].material_id--;
        scene.triangles[i].indices.v0_id--;
        scene.triangles[i].indices.v1_id--;
        scene.triangles[i].indices.v2_id--;
    }
    for(int i=0;i<scene.spheres.size();i++){
        scene.spheres[i].center_vertex_id--;
        scene.spheres[i].material_id--;
    }
    // for(int i=0;i<scene.cameras;i++)
    //     scene.cameras[i].;
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
    for(int cam = 0; cam < scene.cameras.size(); cam++){

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
        cout << processor_count<<"\n";
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
    // p("background color: ");
    // p(scene.background_color);
    // p("\n");
    // p("shadow ray epsilon: ");
    // p(scene.shadow_ray_epsilon);
    // p("\nmax_recursion_depth: ");
    // p(scene.max_recursion_depth);
    // p("\ncameras: ");
    // p(scene.cameras);
    // p("\nambient_light: ");
    // p(scene.ambient_light);
    // p("\npoint_lights: ");
    // p(scene.point_lights);
    // p("\nmaterials: ");
    // p(scene.materials);
    // p("\nvertex_data: ");
    // p(scene.vertex_data);
    // p("\nHere are the objects:");
    // p("\n meshes: ");
    // p(scene.meshes);
    // p("\ntriangles: ");
    // p(scene.triangles);
    // p("\nspheres: ");
    // p(scene.spheres);
    // p("\n");
    // auto a = scene.meshes[0].faces[0];
    // auto b = scene.meshes[0].faces[1];
    // scene.meshes[0].faces.pop_back();
    // scene.meshes[0].faces.pop_back();
    //scene.meshes[0].faces.push_back(b);
    scene = idleriDuzelt(scene);
    generateImages(scene);

    // // The code below creates a test pattern and writes
    // // it to a PPM file to demonstrate the usage of the
    // // ppm_write function.
    // //
    // // Normally, you would be running your ray tracing
    // // code here to produce the desired image.

    // const RGB BAR_COLOR[8] =
    // {
    //     { 255, 255, 255 },  // 100% White
    //     { 255, 255,   0 },  // Yellow
    //     {   0, 255, 255 },  // Cyan
    //     {   0, 255,   0 },  // Green
    //     { 255,   0, 255 },  // Magenta
    //     { 255,   0,   0 },  // Red
    //     {   0,   0, 255 },  // Blue
    //     {   0,   0,   0 },  // Black
    // };

    // int width = 640, height = 480;
    // int columnWidth = width / 8;

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
