/*
This file is part of PiResiduos.

Copyright 2017-2018, Prointegra SL.

PiResiduos is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

PiResiduos is distributed in the hope that it will 
be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with PiResiduos.  
If not, see <https://www.gnu.org/licenses/>.
*/

/**
@file tableta.cpp
''''''
*/
#include "tableta.h"
#include <QPixmap>
#include <QString>
#include <QPainter>
#include <QFont>
#include <QPoint>
#include <malloc.h>


static unsigned char signArray[9600][6000];

static int max_x,min_x,max_y,min_y;


static std::vector <uint8_t> loadBmp(char * fname, int* _w, int* _h)

{
  unsigned char head[54];
  FILE *f = fopen(fname,"rb");

  // BMP header is 54 bytes
  fread(head, 1, 54, f);

  int w = head[18] + ( ((int)head[19]) << 8) + ( ((int)head[20]) << 16) + ( ((int)head[21]) << 24);
  int h = head[22] + ( ((int)head[23]) << 8) + ( ((int)head[24]) << 16) + ( ((int)head[25]) << 24);

  // lines are aligned on 4-byte boundary
  int lineSize = (w / 8 + (w / 8) % 4);
  int fileSize = lineSize * h;

  //  unsigned char *img = malloc(w * h), *data = malloc(fileSize);
  //std::vector <uint8_t> image;
  //image.resize(w*h);
  
  //unsigned char  *data = (unsigned char *)malloc(fileSize);
  std::vector <uint8_t> data;
  data.resize(fileSize);
  // skip the header
  fseek(f,54,SEEK_SET);

  // skip palette - two rgb quads, 8 bytes
  fseek(f, 8, SEEK_CUR);

  // read data
  fread(&data[0],1,data.size(),f);

  //free(data);
  *_w = w-1; *_h = h-1;
  //return image;
  return data;
}

/*! constructor
 */
tableta::tableta(int &error)
{
  error = 0;
  return;
}

void tableta::setInfoShow(std::string matricula, std::string cliente, std::string material, std::string precio, std::string peso)
{
  std::string command = "convert -size 320x64 -monochrome -colors 2 label:'CLIENTE: ";
  //std::string command = "convert -size 320x104 -flatten label:'CLIENTE: ";
  command += cliente;
  command += "\nMATRÍCULA: ";
  command += matricula;
  command += "\nMATERIAL: ";
  command += material;
  command += "\nPESO: ";
  command += peso;
  command +=" Kg  PRECIO:";
  command += precio;
  command +="' info.bmp";
  
  system(command.c_str());

  return;
}
int tableta::loadInfo()
{
  QImage pngImage("info.bmp","Format_Mono");

  return 0;

}
int tableta::reset()
{
  finishCpt();
  return 0;
}
int tableta::init()
{  
       
  return 0;  
}

int tableta::startCapture()
{
  return 0; 
}
  
void tableta::capture()
{
  return;
}

int tableta::finishCpt()
{
  return 0; 
}


int tableta::stopCapture()
{
  return 0;
}

int tableta::run()
{
  //NOT IMPLEMENTED
       
    return 0;  
}



void insertBit(int x,int y)
{
int radio = BIT_RADIOUS;
  if((x < 0) || (x >= MAX_X))
    return;
  if((y<0) || (y >= MAX_Y))
    return;
  if (x > max_x)
    max_x = x;
  if (x < min_x)
    min_x = x;
  if (y > max_y)
    max_y = y;
  if (y < min_y)
    min_y = y;
  
  signArray[x][y] = 0;
if(radio>0)
  {
for(int i= x-radio; i<=x+radio; i++)
  {
for(int j= y -radio; j <= y +radio; j++)
  {
if(i>=0 && i < MAX_X && j >= 0 && j < MAX_Y)
  {
if(signArray[i][j]> 0)
  {
//std::cout << "writting in " << i << "," << j << std::endl;
if((i == x) && (j == y))
  signArray[i][j] = 0;
 else
   signArray[i][j] = 100;
}
}
}
}
}

  return;
}

void tableta::writeImage(const char* ppmImageName)
{
  FILE *ppmImage;
  ppmImage=fopen(ppmImageName,"wb");
  std::string line;
  if(ppmImage==NULL){
    perror("ERROR: Cannot open output file");
    exit(EXIT_FAILURE);
  }
  fprintf(ppmImage,"P2\n");               // P2 filetype
  fprintf(ppmImage,"%d %d\n",max_x-min_x,max_y-min_y);   // dimensions
  fprintf(ppmImage,"255\n");              // Max pixel
for(int i=min_y;i < max_y; i++)
  {
  for(int j = min_x; j < max_x; j++)
    fprintf(ppmImage,"%d ",signArray[j][i]);
fprintf(ppmImage,"\n");
}
//fwrite(signArray,6000,9600,ppmImage);
  fclose(ppmImage);
  return;
}
