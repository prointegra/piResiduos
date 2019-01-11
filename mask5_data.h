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

#ifndef _MASK5_DATA_
#define _MASK5_DATA_


typedef struct // (todo: define your data structure here)
{
  tableta *miTableta;
  std::string comboCliente;
  std::string editClient;
  std::string tmpClient;
  std::string comboProducto;
  std::string comboProducto2;

  std::string camImage;
  std::string txtPlate;
  std::string enPlate;
    
  std::vector <std::string> allVehiculos;
  
  std::vector <std::string> allClientes;
  std::vector <std::string> allClientesCodes;

  std::string productoActual;
  std::string productoCodeActual;  
  std::vector <std::string> allProductos;
  std::vector <std::string> allProductos2;
  std::vector <std::string> allProductos3;
  std::vector <std::string> allProductosCodes;
  std::vector <std::string> allProductosLers;
  std::vector <std::vector <std::string>> allPermisosNecesariosProducto;
  std::vector <std::string> allPermisosProductoCliente;

  std::string pre_transito_plate;
  std::string post_transito_plate;
  std::string transito_plate;
  //
  //finales
  int selectedOrder;
  int camionElegido;
  std::string plateElegida;
  
  //formulario
  std::string formEnCliente;
  int enFutEstado;
  int llegada;

  //triggers
  int retroceder;
  int cancelar;
  int proceder;
  int plateTaking;
  int processTag;
  int pesaje1;
  int resetPeso1;
  int pesaje2;
  int resetPeso2;
  int firmar;
  int firmado;
  int test;
  int editDI;
  int ret;
  
  //allow controls
  int f1Unloads;
  int f2Loads;
  int f3Config;
  int f4Sincro;
  int f5Toggle;
  
  int lastMask;

  //consola
  std::vector <std::string> localConsole;

}
DATA;

#endif
