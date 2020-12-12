#ifndef __APPLYTRANSFORM__
#define __APPLYTRANSFORM__
#include "checkWhatCollides.h"
#include <sstream> 

/**
 * Given a string "s3 t1 r2", makes it Transformation array
 **/
std::vector<Transformation> getTransformationVectorFromString(std::string transformations){//TODO//Added newly
//Done gibi, need test
    // p("TESTING");
    // p("String is: "+transformations+ ".");
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
            tempTransformation.id = x-1;

            res.push_back(tempTransformation);

            tmp = "";
        }else{
            tmp = tmp+c;
        }
    }
    if(tmp == "") return res;
    tempTransformation.type = tmp[0];
    tmp.erase(0,1);
    stringstream stream(tmp); 
    int x = 0;
    stream >> x;
    tempTransformation.id = x-1;
    res.push_back(tempTransformation);
    // p("res is:");
    // p(res);
    return res;
}



Scene applyTransformations(Scene scene){//TODO
    p(scene.meshes);
    p(scene.triangles);
    p(scene.spheres);
    for(auto &sphere: scene.spheres){
        auto transformasyonlar = getTransformationVectorFromString(sphere.transformations);
        sphere.transformasyonlar = transformasyonlar;
        // for(auto transformasyon: transformasyonlar){
        //     if(transformasyon.type=='r'){
        //         Vec3f newCenter = rotate(scene.vertex_data[sphere.center_vertex_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
        //         scene.vertex_data.push_back(newCenter);
        //         sphere.center_vertex_id = scene.vertex_data.size() - 1;
                
        //     }else if(transformasyon.type == 't'){
        //         Vec3f newCenter = translate(scene.vertex_data[sphere.center_vertex_id],scene.translations[transformasyon.id]);
        //         scene.vertex_data.push_back(newCenter);
        //         sphere.center_vertex_id = scene.vertex_data.size() - 1;
        //     }else if(transformasyon.type == 's'){
        //         auto newSphere = scale(sphere,scene.scalings[transformasyon.id]);
        //         sphere.radius = newSphere.radius;
        //     }else{
        //         cout<<"ERROR! UNKNOWN TRANSFORMATION" + transformasyon.type<<endl;
        //     }
        // }    
    }
    for(auto &triangle: scene.triangles){
        auto transformasyonlar = getTransformationVectorFromString(triangle.transformations);
        triangle.transformasyonlar=transformasyonlar;
        // for(auto transformasyon: transformasyonlar){
        //     p("here aq");
        //     if(transformasyon.type=='r'){
        //         p("rotate");
        //         Vec3f newV0 = rotate(scene.vertex_data[triangle.indices.v0_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
        //         scene.vertex_data.push_back(newV0);
        //         triangle.indices.v0_id = scene.vertex_data.size() - 1;
        //         Vec3f newV1 = rotate(scene.vertex_data[triangle.indices.v1_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
        //         scene.vertex_data.push_back(newV1);
        //         triangle.indices.v1_id = scene.vertex_data.size() - 1;
                
        //         Vec3f newV2 = rotate(scene.vertex_data[triangle.indices.v2_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
        //         scene.vertex_data.push_back(newV2);
        //         triangle.indices.v2_id = scene.vertex_data.size() - 1;
                
                
        //     }else if(transformasyon.type == 't'){
        //         p("Before Translation: ");
        //         p(scene.vertex_data);
        //         p(triangle.indices);
        //         Vec3f newV0 = translate(scene.vertex_data[triangle.indices.v0_id],scene.translations[transformasyon.id]);
        //         scene.vertex_data.push_back(newV0);
        //         triangle.indices.v0_id = scene.vertex_data.size() - 1;
        //         Vec3f newV1 = translate(scene.vertex_data[triangle.indices.v1_id],scene.translations[transformasyon.id]);
        //         scene.vertex_data.push_back(newV1);
        //         triangle.indices.v1_id = scene.vertex_data.size() - 1;

        //         Vec3f newV2 = translate(scene.vertex_data[triangle.indices.v2_id],scene.translations[transformasyon.id]);
        //         scene.vertex_data.push_back(newV2);
        //         triangle.indices.v2_id = scene.vertex_data.size() - 1;
        //         p("After Translation: ");
        //         p(scene.vertex_data);
        //         p(triangle.indices);
                
        //     }else if(transformasyon.type == 's'){
        //         p("scale");
        //         Vec3f newV0 = scale(scene.vertex_data[triangle.indices.v0_id],scene.scalings[transformasyon.id]);
        //         scene.vertex_data.push_back(newV0);
        //         triangle.indices.v0_id = scene.vertex_data.size() - 1;

        //         Vec3f newV1 = scale(scene.vertex_data[triangle.indices.v1_id],scene.scalings[transformasyon.id]);
        //         scene.vertex_data.push_back(newV1);
        //         triangle.indices.v1_id = scene.vertex_data.size() - 1;

        //         Vec3f newV2 = scale(scene.vertex_data[triangle.indices.v2_id],scene.scalings[transformasyon.id]);
        //         scene.vertex_data.push_back(newV2);
        //         triangle.indices.v2_id = scene.vertex_data.size() - 1;
        //     }else{
        //         cout<<"ERROR! UNKNOWN TRANSFORMATION" + transformasyon.type<<endl;
        //     }
        // }    
    }
    for(auto &mesh: scene.meshes){
        auto transformasyonlar = getTransformationVectorFromString(mesh.transformations);
        mesh.transformasyonlar = transformasyonlar;
        for(auto &face: mesh.faces){
            for(auto transformasyon: transformasyonlar){
                // if(transformasyon.type=='r'){
                //     //TODO rotate test et, hatali
                //     p(scene.meshes[0].faces[0].v0_id);
                //     p(scene.vertex_data);
                //     Vec3f newV0 = rotate(scene.vertex_data[face.v0_id],scene.rotations[transformasyon.id].angle,{scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                //     scene.vertex_data.push_back(newV0);
                //     face.v0_id = scene.vertex_data.size() - 1;

                //     Vec3f newV1 = rotate(scene.vertex_data[face.v1_id],scene.rotations[transformasyon.id].angle, {scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                //     scene.vertex_data.push_back(newV1);
                //     face.v1_id = scene.vertex_data.size() - 1;

                //     Vec3f newV2 = rotate(scene.vertex_data[face.v2_id],scene.rotations[transformasyon.id].angle, {scene.rotations[transformasyon.id].x,scene.rotations[transformasyon.id].y,scene.rotations[transformasyon.id].z});
                //     scene.vertex_data.push_back(newV2);
                //     face.v2_id = scene.vertex_data.size() - 1;
                //     p("-------------------------------------");
                //     p(scene.meshes[0].faces[0].v0_id);
                //     p(scene.vertex_data);
                // }else if(transformasyon.type == 't'){
                //      Vec3f newV0 = translate(scene.vertex_data[face.v0_id],scene.translations[transformasyon.id]);
                //     scene.vertex_data.push_back(newV0);
                //     face.v0_id = scene.vertex_data.size() - 1;

                //     Vec3f newV1 = translate(scene.vertex_data[face.v1_id],scene.translations[transformasyon.id]);
                //     scene.vertex_data.push_back(newV1);
                //     face.v1_id = scene.vertex_data.size() - 1;

                //     Vec3f newV2 = translate(scene.vertex_data[face.v2_id],scene.translations[transformasyon.id]);
                //     scene.vertex_data.push_back(newV2);
                //     face.v2_id = scene.vertex_data.size() - 1;


                // }else if(transformasyon.type == 's'){

                //     Vec3f newV0 = scale(scene.vertex_data[face.v0_id],scene.scalings[transformasyon.id]);
                //     scene.vertex_data.push_back(newV0);
                //     face.v0_id = scene.vertex_data.size() - 1;

                //     Vec3f newV1 = scale(scene.vertex_data[face.v1_id],scene.scalings[transformasyon.id]);
                //     scene.vertex_data.push_back(newV1);
                //     face.v1_id = scene.vertex_data.size() - 1;

                //     Vec3f newV2 = scale(scene.vertex_data[face.v2_id],scene.scalings[transformasyon.id]);
                //     scene.vertex_data.push_back(newV2);
                //     face.v2_id = scene.vertex_data.size() - 1;

                // }else{
                //     cout<<"ERROR! UNKNOWN TRANSFORMATION " + transformasyon.type<<endl;
                // }
            }    
        }
    }

    // p("--------------------------------");
    // p(scene.meshes);
    // p(scene.triangles);
    // p(scene.spheres);
    return scene;

}


#endif