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
@file tableta.h
''' generic class for communicating with signing pads.'''
*/

#ifndef _TABLETA_
#define _TABLETA_


#include <boost/signals2.hpp>
#include <boost/thread.hpp>

#include <time.h>
#include <csignal>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <QPixmap>
#include <QString>
#include <QPainter>
#include <QFont>
#include <QPoint>


#define BIT_RADIOUS 32
#define MAX_X 9600
#define MAX_Y 6000

void insertBit(int x,int y);

class tableta
{
 public:
  tableta(int &error);
  ~tableta(){};

  int reset();
  int loadInfo();
  int init();
  int startCapture();
  int stopCapture( );
  void capture();
  int finishCpt();
  int run();
  void writeImage(const char* ppmImageName);
  void setInfoShow(std::string matricula, std::string cliente, std::string material, std::string material2, std::string peso);
  
  
 private:
  bool useEncryption;
  boost::signals2::signal<void ()> sig;
  boost::thread* t;
  FILE* salida;

};








#endif
