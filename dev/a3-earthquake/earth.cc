/** CSci-4611 Assignment 3:  Earthquake
 */

#include "earth.h"
#include "config.h"

#include <vector>

// for M_PI constant
#define _USE_MATH_DEFINES
#include <math.h>


Earth::Earth() {
}

Earth::~Earth() {
}

void Earth::Init(const std::vector<std::string> &search_path) {
    // init shader program
    shader_.Init();

    // init texture: you can change to a lower-res texture here if needed
    earth_tex_.InitFromFile(Platform::FindFile("earth-2k.png", search_path));

    // init geometry
    const int nslices = 60;
    const int nstacks = 30;

    // TODO: This is where you need to set the vertices and indiceds for earth_mesh_.

    // As a demo, we'll add a square with 2 triangles.
    std::vector<unsigned int> indices;

    std::vector<Point2> texCoord;

    
    for (int i = 0; i <=nstacks ; i++) {
        for (int j = 0; j <= nslices; j++) {
            double longitude,latitude;
            longitude = (double) j / nslices * 360 - 180;
            latitude = (double) i/ nstacks * 180 - 90;
            Rnormals.push_back(Vector3(0,  0, 1));
            Pnormals.push_back(Vector3(cos(latitude/ 180 * M_PI) * sin (longitude/ 180 * M_PI),
                                                 sin(latitude/ 180 * M_PI),
                                                 cos(latitude/ 180 * M_PI) * cos (longitude/ 180 * M_PI)));
            Pvertices.push_back(LatLongToSphere(latitude, longitude));
            Rvertices.push_back(LatLongToPlane(latitude, longitude));
            texCoord.push_back(Point2((double) j / nslices, (1.0 - (double) i /nstacks)));
        }
    }
    
    for (int i = 0; i < nstacks; i++) {
        for (int j =0; j < nslices; j++) {
            
            
            //int ba = 2 * i * (nstacks + 1) +2 * j;
            indices.push_back((j+0) + (i + 0) * (nslices + 1));
            indices.push_back((j+1) + (i + 0) * (nslices + 1));
            indices.push_back((j+0) + (i + 1) * (nslices + 1));
            
            
            indices.push_back((j+1) + (i + 0) * (nslices + 1));
            indices.push_back((j+1) + (i + 1) * (nslices + 1));
            indices.push_back((j+0) + (i + 1) * (nslices + 1));
            
        }
    }
    
    
    

    earth_mesh_.SetIndices(indices);

    earth_mesh_.SetVertices(Rvertices);
    earth_mesh_.SetNormals(Rnormals);
    earth_mesh_.SetTexCoords(0, texCoord);

    earth_mesh_.UpdateGPUMemory();
}


void Earth::setP(){
    earth_mesh_.SetVertices(Pvertices);
    earth_mesh_.SetNormals(Pnormals);
    earth_mesh_.UpdateGPUMemory();
}
void Earth::setR(){
    earth_mesh_.SetVertices(Rvertices);
    earth_mesh_.SetNormals(Rnormals);
    
    earth_mesh_.UpdateGPUMemory();
}


void Earth::setL(double current_time){
    Lnormals.clear();
    Lvertices.clear();
    for (int i = 0; i <=30 ; i++) {
        for (int j = 0; j <= 60; j++) {
            double longitude,latitude;
            longitude = (double) j / 60 * 360 - 180;
            latitude = (double) i/ 30 * 180 - 90;
            Lnormals.push_back(Vector3::Lerp((Vector3(0,  0, 1)),Vector3(cos(latitude/ 180 * M_PI) * sin (longitude/ 180 * M_PI),sin(latitude/ 180 * M_PI),cos(latitude/ 180 * M_PI) * cos (longitude/ 180 * M_PI)),current_time));
            Lvertices.push_back(Point3::Lerp(LatLongToPlane(latitude, longitude),LatLongToSphere(latitude, longitude),current_time));
            
        }
    }
    earth_mesh_.SetVertices(Lvertices);
    earth_mesh_.SetNormals(Lnormals);

    
    
}
void Earth::Draw(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // Define a really bright white light.  Lighting is a property of the "shader"
    DefaultShader::LightProperties light;
    light.position = Point3(10,10,10);
    light.ambient_intensity = Color(1,1,1);
    light.diffuse_intensity = Color(1,1,1);
    light.specular_intensity = Color(1,1,1);
    shader_.SetLight(0, light);

    // Adust the material properties, material is a property of the thing
    // (e.g., a mesh) that we draw with the shader.  The reflectance properties
    // affect the lighting.  The surface texture is the key for getting the
    // image of the earth to show up.
    DefaultShader::MaterialProperties mat;
    mat.ambient_reflectance = Color(0.5, 0.5, 0.5);
    mat.diffuse_reflectance = Color(0.75, 0.75, 0.75);
    mat.specular_reflectance = Color(0.75, 0.75, 0.75);
    mat.surface_texture = earth_tex_;

    // Draw the earth mesh using these settings
    if (earth_mesh_.num_triangles() > 0) {
        shader_.Draw(model_matrix, view_matrix, proj_matrix, &earth_mesh_, mat);
    }
}


Point3 Earth::LatLongToSphere(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> sphere calculations in one place.

    
    return Point3(cos(latitude/ 180 * M_PI) * sin (longitude/ 180 * M_PI),
                  sin(latitude/ 180 * M_PI),
                  cos(latitude/ 180 * M_PI) * cos (longitude/ 180 * M_PI));
}

Point3 Earth::LatLongToPlane(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> plane calculations in one place.


    return Point3(longitude / 180 * M_PI,
                  latitude / 90 * (M_PI / 2.0),
                  0);
}



void Earth::DrawDebugInfo(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // This draws a cylinder for each line segment on each edge of each triangle in your mesh.
    // So it will be very slow if you have a large mesh, but it's quite useful when you are
    // debugging your mesh code, especially if you start with a small mesh.
    for (int t=0; t<earth_mesh_.num_triangles(); t++) {
        std::vector<unsigned int> indices = earth_mesh_.triangle_vertices(t);
        std::vector<Point3> loop;
        loop.push_back(earth_mesh_.vertex(indices[0]));
        loop.push_back(earth_mesh_.vertex(indices[1]));
        loop.push_back(earth_mesh_.vertex(indices[2]));
        quick_shapes_.DrawLines(model_matrix, view_matrix, proj_matrix,
            Color(1,1,0), loop, QuickShapes::LinesType::LINE_LOOP, 0.005);
    }
}
