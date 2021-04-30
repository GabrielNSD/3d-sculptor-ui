#include "sculptor.h"
#include "voxel.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <queue>

using namespace std;

Voxel ***v;
int x, y, z;

Sculptor::Sculptor(int _nx, int _ny, int _nz)
{
     nx = _nx;
     ny = _ny;
     nz = _nz;
     int i, j, k;

     //alocando memória para o espaço 3d
     v = new Voxel **[nx];
     v[0] = new Voxel *[nx * ny];
     v[0][0] = new Voxel[nx * ny * nz];
     for (i = 1; i < nx; i++)
     {
       v[i] = v[i - 1] + ny;
     }
     for (i = 1; i < nx * ny; i++)
     {
       v[0][i] = v[0][i - 1] + nz;
     }

     for (i = 0; i < _nx; i++)
     {
       for (j = 0; j < _ny; j++)
       {
         for (k = 0; k < _nz; k++)
         {
           v[i][j][k].isOn = false;
         }
       }
     }
}

Sculptor::~Sculptor()
{
  delete[] * *v;
  delete[] * v;
  delete[] v;
  /* for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      delete[] v[x][y];
    }
  }
  for (x = 0; x < nx; x++)
  {
    delete[] v[x];
  }
  delete[] v; */

  cout << "destrutor rodou" << endl;
}

void Sculptor::setColor(float r, float g, float b, float alpha)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = alpha;
}

void Sculptor::putVoxel(int x, int y, int z)
{
  v[x][y][z].isOn = true;
  v[x][y][z].r = this->r;
  v[x][y][z].g = this->g;
  v[x][y][z].b = this->b;
  v[x][y][z].a = this->a;
}

void Sculptor::cutVoxel(int x, int y, int z)
{
  v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
  for (x = x0; x < x1; x++)
  {
    for (y = y0; y < y1; y++)
    {
      for (z = z0; z < z1; z++)
      {
        putVoxel(x, y, z);
      }
    }
  }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1)
{
  for (x = x0; x < x1; x++)
  {
    for (y = y0; y < y1; y++)
    {
      for (z = z0; z < z1; z++)
      {
        cutVoxel(x, y, z);
      }
    }
  }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius)
{
  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if ((pow((x - xcenter), 2) + pow((y - ycenter), 2) + pow((z - zcenter), 2)) <= (pow(radius, 2)))
        {
          putVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius)
{
  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if ((pow((x - xcenter), 2) + pow((y - ycenter), 2) + pow((z - zcenter), 2)) <= (pow(radius, 2)))
        {
          cutVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if (((pow((x - xcenter), 2) / pow(rx, 2)) + (pow((y - ycenter), 2) / pow(ry, 2)) + (pow((z - zcenter), 2) / pow(rz, 2))) <= 1)
        {
          putVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz)
{
  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if (((pow((x - xcenter), 2) / pow(rx, 2)) + (pow((y - ycenter), 2) / pow(ry, 2)) + (pow((z - zcenter), 2) / pow(rz, 2))) <= 1)
        {
          cutVoxel(x, y, z);
        }
      }
    }
  }
}

void Sculptor::limpaVoxels(void)
{
  queue<int> q;
  int lx, ly, lz;
  for (x = 1; x < nx - 1; x++)
  {
    for (y = 1; y < ny - 1; y++)
    {
      for (z = 1; z < nz - 1; z++)
      {
        if ((v[x][y][z].isOn == true) &&
            (v[x + 1][y][z].isOn == true) &&
            (v[x - 1][y][z].isOn == true) &&
            (v[x][y + 1][z].isOn == true) &&
            (v[x][y - 1][z].isOn == true) &&
            (v[x][y][z + 1].isOn == true) &&
            (v[x][y][z - 1].isOn == true))
        {
          q.push(x);
          q.push(y);
          q.push(z);
        }
      }
    }
  }

  while (!q.empty())
  {
    lx = q.front();
    q.pop();
    ly = q.front();
    q.pop();
    lz = q.front();
    q.pop();
    v[lx][ly][lz].isOn = false;
  }
}


void Sculptor::writeOFF(char *filename)
{
    limpaVoxels();
  //contar quantos voxels são verdadeiros
  float lado = 0.5;
  int voxelsOn = 0;
  int index = 0;

  for (int i = 0; i < nx; i++)
  {
    for (int j = 0; j < ny; j++)
    {
      for (int k = 0; k < nz; k++)
      {
        if (v[i][j][k].isOn == true)
        {
          voxelsOn++;
        }
      }
    }
  }
  cout << voxelsOn << endl;
  //abrir arquivo
  ofstream f;
  f.open(filename);
  f << "OFF"
    << "\n";

  //escrever o número de vértices e numero de faces (contador * 8 e contador * 6)
  f << voxelsOn * 8 << " " << voxelsOn * 6 << " 0 \n";
  f << "\n";

  //escrever coordenadas de todos os voxels verdadeiros

  cout << index << endl;

  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if (v[x][y][z].isOn == true)
        {
          f << x - lado << " " << y + lado << " " << z - lado << " "
            << "\n"
            << flush; //P0
          f << x - lado << " " << y - lado << " " << z - lado << " "
            << "\n"
            << flush; //P1
          f << x + lado << " " << y - lado << " " << z - lado << " "
            << "\n"
            << flush; //P2
          f << x + lado << " " << y + lado << " " << z - lado << " "
            << "\n"
            << flush; //P3
          f << x - lado << " " << y + lado << " " << z + lado << " "
            << "\n"
            << flush; //P4
          f << x - lado << " " << y - lado << " " << z + lado << " "
            << "\n"
            << flush; //P5
          f << x + lado << " " << y - lado << " " << z + lado << " "
            << "\n"
            << flush; //P6
          f << x + lado << " " << y + lado << " " << z + lado << " "
            << "\n"
            << flush; //P7

          f << "\n";
        }
      }
    }
  }

  //escrever vertices de todos os voxels verdadeiros
  voxelsOn = 0;
  cout << index << endl;
  for (x = 0; x < nx; x++)
  {
    for (y = 0; y < ny; y++)
    {
      for (z = 0; z < nz; z++)
      {
        if (v[x][y][z].isOn == true)
        {
          index = voxelsOn * 8;
          //face 1
          f << std::fixed;
          f << 4 << " " << index + 0 << " " << index + 3 << " " << index + 2 << " " << index + 1 << " ";
          f << setprecision(2) << v[x][y][z].r << " "
            << setprecision(2) << v[x][y][z].g << " "
            << setprecision(2) << v[x][y][z].b << " "
            << setprecision(2) << v[x][y][z].b << "\n";

          //face 2
          f << 4 << " " << index + 4 << " " << index + 5 << " " << index + 6 << " " << index + 7 << " ";
          f << setprecision(2) << v[x][y][z].r << " "
            << setprecision(2) << v[x][y][z].g << " "
            << setprecision(2) << v[x][y][z].b << " "
            << setprecision(2) << v[x][y][z].b << "\n";

          //face 3
          f << 4 << " " << index + 0 << " " << index + 1 << " " << index + 5 << " " << index + 4 << " ";
          f << setprecision(2) << v[x][y][z].r << " "
            << setprecision(2) << v[x][y][z].g << " "
            << setprecision(2) << v[x][y][z].b << " "
            << setprecision(2) << v[x][y][z].b << "\n";

          //face 4
          f << 4 << " " << index + 0 << " " << index + 4 << " " << index + 7 << " " << index + 3 << " ";
          f << setprecision(2) << v[x][y][z].r << " "
            << setprecision(2) << v[x][y][z].g << " "
            << setprecision(2) << v[x][y][z].b << " "
            << setprecision(2) << v[x][y][z].b << "\n";

          //face 5
          f << 4 << " " << index + 7 << " " << index + 6 << " " << index + 2 << " " << index + 3 << " ";
          f << setprecision(2) << v[x][y][z].r << " "
            << setprecision(2) << v[x][y][z].g << " "
            << setprecision(2) << v[x][y][z].b << " "
            << setprecision(2) << v[x][y][z].b << "\n";

          //face 6
          f << 4 << " " << index + 1 << " " << index + 2 << " " << index + 6 << " " << index + 5 << " ";
          f << setprecision(2) << v[x][y][z].r << " "
            << setprecision(2) << v[x][y][z].g << " "
            << setprecision(2) << v[x][y][z].b << " "
            << setprecision(2) << v[x][y][z].b << "\n";

          f << "\n";
          voxelsOn++;
        }
      }
    }
  }

  f.close();
}


int Sculptor::isOn(int i, int j, int k)
{
    if(v[i][j][k].isOn == true){
        return 1;
    } else {
        return 0;
    }
}

int Sculptor::getRed(int _i, int _j, int _k)
{
    return v[_i][_j][_k].r*255;
}

int Sculptor::getGreen(int _i, int _j, int _k)
{
    return v[_i][_j][_k].g*255;
}

int Sculptor::getBlue(int _i, int _j, int _k)
{
    return v[_i][_j][_k].b*255;
}
