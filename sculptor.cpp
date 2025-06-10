#include "sculptor.h"
#include <fstream>
#include <iomanip>

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
    nx = _nx;
    ny = _ny;
    nz = _nz;
    // aloca a matriz de voxels v
    v = new Voxel**[nx];
    for (int i = 0; i < nx; i++) {
        v[i] = new Voxel*[ny];
        for (int j = 0; j < ny; j++) {
            v[i][j] = new Voxel[nz];
        }
    }
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){

            }
        }
    }
}

Sculptor::~Sculptor() {
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
        delete[] v[i];
    }
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}
void Sculptor::putVoxel(int x, int y, int z) {
    v[x][y][z].r=r;
    v[x][y][z].g=g;
    v[x][y][z].b=b;
    v[x][y][z].a=a;
    v[x][y][z].show = true;
}
void Sculptor::cutVoxel(int x, int y, int z) {
    v[x][y][z].show = false;
}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                if (i >= 0 && i < nx && j >= 0 && j < ny && k >= 0 && k < nz){
                    v[i][j][k].r=r;
                    v[i][j][k].g=g;
                    v[i][j][k].b=b;
                    v[i][j][k].a=a;
                    v[i][j][k].show = true;
                }
            }
        }
    }
}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1) {
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                if (i >= 0 && i < nx && j >= 0 && j < ny && k >= 0 && k < nz){
                    v[i][j][k].show = false;
                }
            }
        }
    }
}
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for(int i=xcenter-radius; i<=xcenter+radius; i++){
        for(int j=ycenter-radius; j<=ycenter+radius; j++){
            for(int k=zcenter-radius; k<=zcenter+radius; k++){
                int x_esfera = i - xcenter;
                int y_esfera = j - ycenter;
                int z_esfera = k - zcenter;

                if (x_esfera*x_esfera + y_esfera*y_esfera + z_esfera*z_esfera <= radius*radius && i>=0 && j>=0 && k>=0){                        v[i][j][k].r=r;
                    v[i][j][k].r=r;
                    v[i][j][k].g=g;
                    v[i][j][k].b=b;
                    v[i][j][k].a=a;
                    v[i][j][k].show = true;
                }
            }
        }
    }
}
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius) {
    for(int i=xcenter-radius; i<=xcenter+radius; i++){
        for(int j=ycenter-radius; j<=ycenter+radius; j++){
            for(int k=zcenter-radius; k<=zcenter+radius; k++){
                int x_esfera = i - xcenter;
                int y_esfera = j - ycenter;
                int z_esfera = k - zcenter;

                if (x_esfera*x_esfera + y_esfera*y_esfera + z_esfera*z_esfera <= radius*radius && i>=0 && j>=0 && k>=0){
                    v[i][j][k].show = false;
                }
            }
        }
    }
}
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for(int i=xcenter-rx; i<=xcenter+rx; i++){
        for(int j=ycenter-ry; j<=ycenter+ry; j++){
            for(int k=zcenter-rz; k<=zcenter+rz; k++){
                int x = i - xcenter;
                int y = j - ycenter;
                int z = k - zcenter;

                float var_x = (float)x/rx;
                float var_y = (float)y/ry;
                float var_z = (float)z/rz;

                if (var_x *var_x + var_y*var_y + var_z*var_z <= 1 && i>=0 && j>=0 && k>=0){
                    v[i][j][k].r=r;
                    v[i][j][k].g=g;
                    v[i][j][k].b=b;
                    v[i][j][k].a=a;
                    v[i][j][k].show = true;
                }
            }
        }
    }
}
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz) {
    for(int i=xcenter-rx; i<=xcenter+rx; i++){
        for(int j=ycenter-ry; j<=ycenter+ry; j++){
            for(int k=zcenter-rz; k<=zcenter+rz; k++){
                int x = i - xcenter;
                int y = j - ycenter;
                int z = k - zcenter;

                float var_x = (float)x/rx;
                float var_y = (float)y/ry;
                float var_z = (float)z/rz;

                if (var_x *var_x + var_y*var_y + var_z*var_z <= 1 && i>=0 && j>=0 && k>=0){
                    v[i][j][k].show = false;
                }
            }
        }
    }
}
void Sculptor::writeOFF(const char *filename) {
    std::ofstream fout;
    int nvoxels=0;

    fout.open(filename);
    if (!fout.is_open()) {
        exit(1);
    }
    fout << "OFF\n";
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].show==true){
                    nvoxels++;
                }
            }
        }
    }
    // conta quantos voxels estao marcados com show == true
    // lasso aninhado

    fout << nvoxels * 8 << " " << nvoxels * 6 << " 0\n";
    fout <<std::fixed;
    fout<<std::setprecision(1);
    // escrever os vertices
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].show==true){
                    fout << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n";
                    fout << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n";
                    fout << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n";
                    fout << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << "\n";
                    fout << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << "\n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << "\n";
                    fout << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << "\n";
                }
            }
        }
    }
    int fases = 0;

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                if (v[i][j][k].show == true) {
                    fout << "4 " << fases+0 << " " << fases+1 << " " << fases+3 << " " << fases+2 << " "<< v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<  "\n"; // Face esquerda
                    fout << "4 " << fases+4 << " " << fases+5 << " " << fases+7 << " " << fases+6 << " "<< v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<  "\n"; // Face direita
                    fout << "4 " << fases+0 << " " << fases+1 << " " << fases+5 << " " << fases+4 << " "<< v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<  "\n"; // Face inferior
                    fout << "4 " << fases+2 << " " << fases+3 << " " << fases+7 << " " << fases+6 << " "<< v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<  "\n"; // Face superior
                    fout << "4 " << fases+1 << " " << fases+3 << " " << fases+7 << " " << fases+5 << " "<< v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<  "\n"; // Face frontal
                    fout << "4 " << fases+0 << " " << fases+2 << " " << fases+6 << " " << fases+4 << " "<< v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a <<  "\n"; // Face traseira
                    fases += 8;
                }
            }
        }
    }
    // escrever as faces
    fout.close();
}
