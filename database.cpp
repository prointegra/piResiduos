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
@file database.cpp
*/
#include "database.h"



/*! SELECT queries */
//table CENTERS
void selAllDatFrmCenter(char *& sql,long code)
{
  sql = new char[sizeof("select CODIGO_CENTRO,TIPO_CENTRO,NOMBRE,NIF,DIRECCION,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO FROM CENTROS WHERE CODIGO_CENTRO = xxxxx AND (BORRADO is null or BORRADO = 0);")+30];
   
  sprintf(sql,"select CODIGO_CENTRO,TIPO_CENTRO,NOMBRE,NIF,DIRECCION,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO FROM CENTROS WHERE CODIGO_CENTRO = %lu AND (BORRADO is null or BORRADO = 0);",code);

  return;
}
void selAllDatFrmLocalCenters(char *& sql)
{
  sql = new char[sizeof("select CODIGO_CENTRO,TIPO_CENTRO,NOMBRE,NIF,DIRECCION,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO FROM CENTROS WHERE TIPO_CENTRO > 0 AND TIPO_CENTRO < 5;")+30];
   
  sprintf(sql,"select CODIGO_CENTRO,TIPO_CENTRO,NOMBRE,NIF,DIRECCION,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO FROM CENTROS WHERE TIPO_CENTRO > 0 AND TIPO_CENTRO < 5;");

  return;
}
void selExtCentersNameCode(char *& sql)
{
  sql = new char[sizeof("select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO =5")+30];
   
  sprintf(sql,"select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO =5");

  return;

}
void selIntCentersNameCode(char *& sql)
{
  sql = new char[sizeof("select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO <5")+30];
   
  sprintf(sql,"select NOMBRE,CODIGO_CENTRO FROM CENTROS WHERE TIPO_CENTRO <5");

  return;

}
//table orders
void selectAllFromOrders(char *& sql, long station_code)
{
  sql = new char[sizeof("SELECT ORDENES.ECOEMBES, ORDENES.CODIGO_CLIENTE, ORDENES.CODIGO_PRODUCTO, ORDENES.FECHA_FIRMA, ORDENES.FECHA_PROGRAMADA, ORDENES.PRECIO_TN, ORDENES.PESO_A_RETIRAR, ORDENES.CODIGO_DESTINO, ORDENES.OPERACION_TRATAMIENTO, ORDENES.REPETIR, CLIENTES.NOMBRE,PRODUCTOS.CODIGO_LER from ORDENES INNER JOIN CLIENTES ON ORDENES.CODIGO_CLIENTE = CLIENTES.CODIGO_CLIENTE INNER JOIN PRODUCTOS ON PRODUCTOS.CODIGO_PRODUCTO = ORDENES.CODIGO_PRODUCTO WHERE ORDENES.CODIGO_DESTINO = XXXXXX")+12];
  
  sprintf(sql,"SELECT ORDENES.ECOEMBES, ORDENES.CODIGO_CLIENTE, ORDENES.CODIGO_PRODUCTO, ORDENES.FECHA_FIRMA, ORDENES.FECHA_PROGRAMADA, ORDENES.PRECIO_TN, ORDENES.PESO_A_RETIRAR, ORDENES.CODIGO_DESTINO, ORDENES.OPERACION_TRATAMIENTO, ORDENES.REPETIR, CLIENTES.NOMBRE,PRODUCTOS.CODIGO_LER from ORDENES INNER JOIN CLIENTES ON ORDENES.CODIGO_CLIENTE = CLIENTES.CODIGO_CLIENTE INNER JOIN PRODUCTOS ON PRODUCTOS.CODIGO_PRODUCTO = ORDENES.CODIGO_PRODUCTO WHERE ORDENES.CODIGO_DESTINO = %lu",station_code);
  
  return;
}
void delOrder(char *& sltQuery, char *& myQuery,long destiny,long costumer,long product)
{
  sltQuery = new char[sizeof("DELETE FROM ordenes WHERE CODIGO_CLIENTE = XXXXX AND CODIGO_DESTINO = XXXXX AND CODIGO_PRODUCTO = XXXXXX AND (REPETIR is null or REPETIR = 0) order by FECHA_HORA asc LIMIT 1") + 32];

  myQuery = new char[sizeof("DELETE FROM ordenes WHERE CODIGO_CLIENTE = XXXXX AND CODIGO_DESTINO = XXXXX AND CODIGO_PRODUCTO = XXXXXX AND (REPETIR is null or REPETIR = 0) order by FECHA_HORA asc LIMIT 1") + 32];
  
  sprintf(sltQuery,"DELETE FROM ordenes WHERE CODIGO_CLIENTE = %lu AND CODIGO_DESTINO = %lu AND CODIGO_PRODUCTO = %lu AND (REPETIR is null or REPETIR = 0) order by FECHA_PROGRAMADA asc LIMIT 1",costumer,destiny,product);

  sprintf(myQuery,"DELETE FROM ordenes WHERE CODIGO_CLIENTE = %lu AND CODIGO_DESTINO = %lu AND CODIGO_PRODUCTO = %lu AND (REPETIR is null or REPETIR = 0) order by FECHA_PROGRAMADA asc LIMIT 1",costumer,destiny,product);
}
////****table TRANSFERS****////

void selAllTransfers(char *& sql, long station_code)
{
 sql = new char[sizeof("select di, fecha_hora, codigo_origen, codigo_producto, codigo_transportista , matricula, remolque, incidencias, comentario_operador, operacion_Tratamiento FROM transferencias WHERE (codigo_destino = XX)")+32];
 
 sprintf(sql,"select di, fecha_hora, codigo_origen, codigo_producto, codigo_transportista , matricula, remolque, incidencias, comentario_operador, operacion_tratamiento FROM transferencias WHERE (codigo_destino = %lu)",station_code);

  return;
}

void sel_all_unsyncro_transfers(char *& sql)
{
 sql = new char[sizeof("select di, fecha_hora, codigo_origen, codigo_destino, codigo_producto, codigo_transportista , matricula, remolque, incidencias, comentario_operador, operacion_Tratamiento FROM transferencias WHERE (SINCRONIZADO = 0)")+32];
 
 sprintf(sql,"select di, fecha_hora, codigo_origen, codigo_destino, codigo_producto, codigo_transportista , matricula, remolque, incidencias, comentario_operador, operacion_tratamiento FROM transferencias WHERE (SINCRONIZADO = 0)");

 return;
}

void delTransfer(char *& sltQuery, char *& myQuery,long origin,long destiny,long product, const char* plate)
{
  sltQuery = new char[sizeof("DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = XXXXX AND CODIGO_DESTINO = XXXXX AND CODIGO_PRODUCTO = XXXXXX AND MATRICULA = \"XXXXXXXX\" order by FECHA_HORA asc LIMIT 1") + 32];

  myQuery = new char[sizeof("DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = XXXXX AND CODIGO_DESTINO = XXXXX AND CODIGO_PRODUCTO = XXXXXX AND MATRICULA = \"XXXXXXXX\" order by FECHA_HORA asc LIMIT 1") + 32];
  
  sprintf(sltQuery,"DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = %lu AND CODIGO_DESTINO = %lu AND CODIGO_PRODUCTO = %lu AND MATRICULA = \"%s\" order by FECHA_HORA asc LIMIT 1",origin,destiny,product,plate);

  sprintf(myQuery,"DELETE FROM transferencias WHERE FECHA_HORA IS NOT NULL AND CODIGO_ORIGEN = %lu AND CODIGO_DESTINO = %lu AND CODIGO_PRODUCTO = %lu AND MATRICULA = \"%s\" order by FECHA_HORA asc LIMIT 1",origin,destiny,product,plate);
}

void delTransfer(char*&sql,const char* fecha_hora, long codigo_origen, long codigo_destino)
{
  sql = new char[sizeof("delete from transferencias where fecha_hora = \"XXXX-XX-XX XX:XX:XX\" and codigo_origen=XXXXXX and codigo_destino=XXXXXX")+64];
 
  sprintf(sql,"delete from transferencias where fecha_hora = \"%s\" and codigo_origen=%lu and codigo_destino=%lu",fecha_hora,codigo_origen,codigo_destino);

  return;
}

void rmt_sel_all_transfers(char*&sql, long codigo_estacion)
{
  sql = new char[sizeof("select DI, FECHA_HORA, CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, MATRICULA, REMOLQUE, INCIDENCIAS, COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO from transferencias where CODIGO_DESTINO = XX and BORRADO = 0")+32];
  sprintf(sql,"select DI, FECHA_HORA, CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, MATRICULA, REMOLQUE, INCIDENCIAS, COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO from transferencias where CODIGO_DESTINO = %lu and BORRADO = 0",codigo_estacion);

  return;
}

void rmt_updt_transfers(char *& sql, std::vector< std::vector <std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transferencias (DI, FECHA_HORA, CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, MATRICULA, REMOLQUE, INCIDENCIAS, COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  newQuery += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA = VALUES(FECHA_HORA) , CODIGO_ORIGEN = VALUES(CODIGO_ORIGEN), CODIGO_DESTINO = VALUES(CODIGO_DESTINO),CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), CODIGO_TRANSPORTISTA = VALUES(CODIGO_TRANSPORTISTA), MATRICULA = VALUES(MATRICULA), REMOLQUE = VALUES(REMOLQUE), INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), OPERACION_TRATAMIENTO = VALUES(OPERACION_TRATAMIENTO)";
  
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;

}


////////////////
////****table products****////
void selProdPermits(char *& sql, const char* type, long product_code)
{
  sql = new char[sizeof("select PERMISO_XX,CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from productos WHERE CODIGO_PRODUCTO = XXXXX")+32];
  
  sprintf(sql,"select PERMISO_%s,CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from productos WHERE CODIGO_PRODUCTO = %lu",type,type,type,type,type,type,product_code);
  
  return;
}
void selProdDataByCode(char *& sql, long code)
{ 
  sql = new char[sizeof("SELECT NOMBRE, NOMBRE2, NOMBRE3,CODIGO_LER,DESCRIPCION_PELIGRO,PRECIO_DEFECTO  from PRODUCTOS WHERE (CODIGO_PRODUCTO=XXXXX AND (BORRADO is null or BORRADO = 0))")+12];
  
  sprintf(sql,"SELECT NOMBRE, NOMBRE2, NOMBRE3,CODIGO_LER,DESCRIPCION_PELIGRO,PRECIO_DEFECTO  from PRODUCTOS WHERE (CODIGO_PRODUCTO=%lu AND (BORRADO is null or BORRADO = 0))",code);
  
  return; 
}

//búsqueda conjunta de tablas productos y clientes-productos para sacar los que están eprmitidos al cliente en cuestión
void selProdsAllowedToClient(char *& sql, const char* codigoCliente, const char* tipoEstacion, bool temporal)
{
  
  sql = new char[sizeof("CREATE TEMPORARY TABLE resultado as select CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PRODUCTOS.CODIGO_PRODUCTO from PRODUCTOS INNER JOIN CLIENTES_PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_CLIENTE= AND CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = PRODUCTOS.CODIGO_PRODUCTO AND PRODUCTOS.PERMISO_XX!=0 AND ((PRODUCTOS.CONTRATO_XX!=0 AND CLIENTES_PRODUCTOS.CONTRATO_XX >=CURRENT_DATE) OR PRODUCTOS.CONTRATO_XX=0) AND ((PRODUCTOS.NPT_XX!=0 AND CLIENTES_PRODUCTOS.NPT_XX!=0) OR PRODUCTOS.NPT_XX=0) AND ((PRODUCTOS.CB_XX!=0 AND CLIENTES_PRODUCTOS.CB_XX!=0) OR PRODUCTOS.CB_XX=0) AND ((PRODUCTOS.CP_XX!=0 AND CLIENTES_PRODUCTOS.CP_XX!=0) OR PRODUCTOS.CP_XX=0) AND ((PRODUCTOS.DCP_XX!=0 AND CLIENTES_PRODUCTOS.DCP_XX!=0) OR PRODUCTOS.DCP_XX=0) AND (BORRADO is null or BORRADO = 0) ORDER BY nombre,nombre2,nombre3")+ strlen(codigoCliente) + 64];

  if(temporal)
    sprintf(sql,"CREATE TEMPORARY TABLE resultado as select CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PRODUCTOS.CODIGO_PRODUCTO from PRODUCTOS INNER JOIN CLIENTES_PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_CLIENTE=%s AND CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = PRODUCTOS.CODIGO_PRODUCTO AND PRODUCTOS.PERMISO_%s!=0 AND ((PRODUCTOS.CONTRATO_%s!=0 AND CLIENTES_PRODUCTOS.CONTRATO_%s >=CURRENT_DATE) OR PRODUCTOS.CONTRATO_%s=0) AND ((PRODUCTOS.NPT_%s!=0 AND CLIENTES_PRODUCTOS.NPT_%s!=0) OR PRODUCTOS.NPT_%s=0) AND ((PRODUCTOS.CB_%s!=0 AND CLIENTES_PRODUCTOS.CB_%s!=0) OR PRODUCTOS.CB_%s=0) AND ((PRODUCTOS.CP_%s!=0 AND CLIENTES_PRODUCTOS.CP_%s!=0) OR PRODUCTOS.CP_%s=0) AND ((PRODUCTOS.DCP_%s!=0 AND CLIENTES_PRODUCTOS.DCP_%s!=0) OR PRODUCTOS.DCP_%s=0) AND (BORRADO is null or BORRADO = 0) ORDER BY nombre,nombre2,nombre3",codigoCliente,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion);
  else
     sprintf(sql,"select CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PRODUCTOS.CODIGO_PRODUCTO from PRODUCTOS INNER JOIN CLIENTES_PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_CLIENTE=%s AND CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = PRODUCTOS.CODIGO_PRODUCTO AND PRODUCTOS.PERMISO_%s!=0 AND ((PRODUCTOS.CONTRATO_%s!=0 AND CLIENTES_PRODUCTOS.CONTRATO_%s >=CURRENT_DATE) OR PRODUCTOS.CONTRATO_%s=0) AND ((PRODUCTOS.NPT_%s!=0 AND CLIENTES_PRODUCTOS.NPT_%s!=0) OR PRODUCTOS.NPT_%s=0) AND ((PRODUCTOS.CB_%s!=0 AND CLIENTES_PRODUCTOS.CB_%s!=0) OR PRODUCTOS.CB_%s=0) AND ((PRODUCTOS.CP_%s!=0 AND CLIENTES_PRODUCTOS.CP_%s!=0) OR PRODUCTOS.CP_%s=0) AND ((PRODUCTOS.DCP_%s!=0 AND CLIENTES_PRODUCTOS.DCP_%s!=0) OR PRODUCTOS.DCP_%s=0) AND (BORRADO is null or BORRADO = 0) ORDER BY nombre,nombre2,nombre3",codigoCliente,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion);

  return;
}

void selAllProds(char*&sql)
{
  sql = new char[sizeof("select codigo_producto, codigo_ler, nombre, nombre2, nombre3, permiso_pt, contrato_pt, npt_pt, cb_pt,cp_pt,dcp_pt, permiso_et, contrato_et, npt_et, cb_et,cp_et,dcp_et, permiso_d5, contrato_d5, npt_d5, cb_d5,cp_d5,dcp_d5, permiso_sal, contrato_sal, npt_sal, cb_sal,cp_sal,dcp_sal, descripcion_peligro FROM productos WHERE (BORRADO is null or BORRADO = 0) order by nombre,nombre2,nombre3")+32];
 
  sprintf(sql,"select codigo_producto, codigo_ler, nombre, nombre2, nombre3, permiso_pt, contrato_pt, npt_pt, cb_pt,cp_pt,dcp_pt, permiso_et, contrato_et, npt_et, cb_et,cp_et,dcp_et, permiso_d5, contrato_d5, npt_d5, cb_d5,cp_d5,dcp_d5, permiso_sal, contrato_sal, npt_sal, cb_sal,cp_sal,dcp_sal, descripcion_peligro FROM productos WHERE (BORRADO is null or BORRADO = 0) order by nombre,nombre2,nombre3");

  return;
}

//c++ style!
void sqlLoadProducts(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into productos (codigo_producto, codigo_ler, nombre, nombre2,nombre3,PERMISO_PT ,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT ,PERMISO_ET ,CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,PERMISO_D5 ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,PERMISO_SAL ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL ,DESCRIPCION_PELIGRO,PRECIO_DEFECTO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
       newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());
  return;
}


/////////////////////////////////////////////////////
////****table costumers****////
void selCosDataByCode(char *& sql, long code)
{
  sql = new char[sizeof("SELECT NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, CODIGO_ENTIDAD_FACTURACION, CBC, TIPO, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from CLIENTES WHERE (CODIGO_CLIENTE=XXXXX AND (BORRADO is null or BORRADO = 0))")+12];

  sprintf(sql,"SELECT NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, CODIGO_ENTIDAD_FACTURACION, CBC, TIPO, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from CLIENTES WHERE (CODIGO_CLIENTE=%lu AND (BORRADO is null or BORRADO = 0))",code);

  return;
}
void selAllDatFrmCostumers(char *& sql)
{
  sql = new char[sizeof("SELECT CODIGO_CLIENTE,NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, CODIGO_ENTIDAD_FACTURACION, CBC, TIPO, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from CLIENTES WHERE (BORRADO is null or BORRADO = 0) order by NOMBRE")+12];

  sprintf(sql,"SELECT CODIGO_CLIENTE,NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, CODIGO_ENTIDAD_FACTURACION, CBC, TIPO, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from CLIENTES WHERE (BORRADO is null or BORRADO = 0) order by NOMBRE");

  return;
}

void sel_default_driver(char *& sql, long code)
{
  sql = new char[sizeof("select TRANSPORTISTA_DEFECTO from CLIENTES where (CODIGO_CLIENTE=XXXXX AND (BORRADO is null or BORRADO = 0))")+12];

  sprintf(sql,"select TRANSPORTISTA_DEFECTO from CLIENTES where (CODIGO_CLIENTE=%lu AND (BORRADO is null or BORRADO = 0))",code);

  return;
}

void rmt_sel_all_costumers(char *& sql)
{

  sql = new char[sizeof("select CODIGO, NOMBRE , NIF , DIRECCION , PROVINCIA ,POBLACION ,CP , ENTIDAD_FACTURACION ,CBC ,TIPO , COMUNIDAD_AUTONOMA , NIMA , NUM_INSCRIPCION , TELEFONO , MAIL, TRANSPORTISTA_DEFECTO from clientes WHERE  (BORRADO is null or BORRADO = 0);")+12];
  sprintf(sql,"select CODIGO, NOMBRE , NIF , DIRECCION , PROVINCIA ,POBLACION ,CP , ENTIDAD_FACTURACION ,CBC ,TIPO , COMUNIDAD_AUTONOMA , NIMA , NUM_INSCRIPCION , TELEFONO , MAIL, TRANSPORTISTA_DEFECTO from clientes WHERE  (BORRADO is null or BORRADO = 0)");

  return;
}


////////
////****table costumers-products****////
void selProdCosPermits(char *& sql, const char* type, long product_code, long costumer_code)
{
  sql = new char[sizeof("select CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from clientes_products WHERE CODIGO_PRODUCTO = XXXXX AND CODIGO_CLIENTE = XXXXX")+32];
  
  sprintf(sql,"select CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from clientes_productos WHERE CODIGO_PRODUCTO = %lu AND CODIGO_CLIENTE = %lu",type,type,type,type,type,product_code, costumer_code);
  
  return;
}

void sel_price_cos_prod(char *&sql, long product_code, long costumer_code)
{
  sql = new char[sizeof("select PRECIO_TRATAMIENTO from clientes_products WHERE CODIGO_PRODUCTO = XXXXX AND CODIGO_CLIENTE = XXXXX")+32];
  
  sprintf(sql,"select PRECIO_TRATAMIENTO from clientes_products WHERE CODIGO_PRODUCTO = %lu AND CODIGO_CLIENTE = %lu",product_code, costumer_code);
  
  return;
}
void sel_DIbasis_cos_prod(char *& sql,const char* tipoEstacion, long codigoCliente, long codigoProducto)
{
  sql = new char[sizeof("select NPT_XXX,PRECIO_TRATAMIENTO from clientes_productos WHERE (CODIGO_PRODUCTO = xxxxx AND CODIGO_CLIENTE = xxxxx)") + 32];
  
  sprintf(sql,"select NPT_%s,PRECIO_TRATAMIENTO from clientes_productos WHERE (CODIGO_PRODUCTO = %lu AND CODIGO_CLIENTE = %lu)",tipoEstacion,codigoProducto,codigoCliente);

  return;
}

//c++ style!
void load_cos_prod(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert or ignore into clientes_productos (CODIGO_PRODUCTO,CODIGO_CLIENTE,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT , CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL, PRECIO_TRATAMIENTO) values ";
  row=0;
    for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
       newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());
  return;
}

///remote
void rmt_sel_all_cos_prod(char*&sql)
{
  sql = new char[sizeof("select CODIGO_PROD,CODIGO_CLIENTE,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT , CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL, PRECIO_TRATAMIENTO from clientes_productos")+32];
  sprintf(sql,"select CODIGO_PROD,CODIGO_CLIENTE,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT , CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL, PRECIO_TRATAMIENTO from clientes_productos");

  return;
}

//////// 
////****table movements****////
void selLastDiFromMovementsByClientProduct(char *& sql, long costumer_code, long product_code)
{
  sql = new char[sizeof("select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=XXXXX AND CODIGO_PRODUCTO=XXXXX ORDER BY DATETIME(FECHA_HORA_FINAL) DESC;") + 64];

  sprintf(sql,"select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=%lu AND CODIGO_PRODUCTO=%lu ORDER BY DATETIME(FECHA_HORA_FINAL) DESC", costumer_code,product_code);

  return;
}

void sel_all_unsyncro_movements(char *& sql)
{
  sql = new char[sizeof("select CODIGO_MOV,DI,FECHA_HORA_INICIO,FECHA_HORA_FINAL,TIPO_MOV,CODIGO_CLIENTE,CODIGO_PRODUCTO,CODIGO_TRANSPORTISTA,PESO_NETO,PESO_TARA,PESO_BRUTO,PRECIO,VEHICULO,REMOLQUE,CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS,COMENTARIO_OPERADOR,CLIENTE_PARTICULAR_NOMBRE,CLIENTE_PARTICULAR_NIF,CLIENTE_PARTICULAR_DOMICILIO,CLIENTE_PARTICULAR_PROVINCIA,CLIENTE_PARTICULAR_POBLACION,CLIENTE_PARTICULAR_CODIGO_POSTAL,CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA,CLIENTE_PARTICULAR_NIMA,CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO,CLIENTE_PARTICULAR_TELEFONO,CLIENTE_PARTICULAR_CORREO_ELECTRONICO,DESTINO_NOMBRE,DESTINO_NIF,DESTINO_DOMICILIO,DESTINO_PROVINCIA,DESTINO_POBLACION,DESTINO_CODIGO_POSTAL,DESTINO_COMUNIDAD_AUTONOMA,DESTINO_NIMA,DESTINO_NUM_INSCRIPCION_REGISTRO,DESTINO_TELEFONO,DESTINO_CORREO_ELECTRONICO,TIPO_CLIENTE from MOVIMIENTOS where SINCRONIZADO = 0") + 64];

   sprintf(sql,"select CODIGO_MOV,DI,FECHA_HORA_INICIO,FECHA_HORA_FINAL,TIPO_MOV,CODIGO_CLIENTE,CODIGO_PRODUCTO,CODIGO_TRANSPORTISTA,PESO_NETO,PESO_TARA,PESO_BRUTO,PRECIO,VEHICULO,REMOLQUE,CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS,COMENTARIO_OPERADOR,CLIENTE_PARTICULAR_NOMBRE,CLIENTE_PARTICULAR_NIF,CLIENTE_PARTICULAR_DOMICILIO,CLIENTE_PARTICULAR_PROVINCIA,CLIENTE_PARTICULAR_POBLACION,CLIENTE_PARTICULAR_CODIGO_POSTAL,CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA,CLIENTE_PARTICULAR_NIMA,CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO,CLIENTE_PARTICULAR_TELEFONO,CLIENTE_PARTICULAR_CORREO_ELECTRONICO,DESTINO_NOMBRE,DESTINO_NIF,DESTINO_DOMICILIO,DESTINO_PROVINCIA,DESTINO_POBLACION,DESTINO_CODIGO_POSTAL,DESTINO_COMUNIDAD_AUTONOMA,DESTINO_NIMA,DESTINO_NUM_INSCRIPCION_REGISTRO,DESTINO_TELEFONO,DESTINO_CORREO_ELECTRONICO,TIPO_CLIENTE from MOVIMIENTOS where SINCRONIZADO = 0");
 return;
}

void upd_all_unsyncro_movements(char *& sql)
{
 sql = new char[sizeof("UPDATE MOVIMIENTOS SET SINCRONIZADO = 1  WHERE SINCRONIZADO = 0")+32];

 sprintf(sql,"UPDATE MOVIMIENTOS SET SINCRONIZADO = 1  WHERE SINCRONIZADO = 0");

 return;
}

void upd_syncro_movements(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert or ignore into MOVIMIENTOS (CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOV, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, CENTRO_DESTINO, INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO, SINCRONIZADO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      myRow->at(2) = mysql2sqliteDate(myRow->at(2));
      myRow->at(3) = mysql2sqliteDate(myRow->at(3));      
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\",1)"; //<- sincronizado to 1 here, last value
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;

}

///remote///
void rmt_sel_last_movement(char *& sql,long station_code,int year)
{
  std::string from_mov_code, to_mov_code;

  from_mov_code = std::to_string(year) + std::to_string(station_code) + "0000000";
  to_mov_code = std::to_string(year) + std::to_string(station_code) + "9999999";

   sql = new char[sizeof("select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, CENTRO_DESTINO, INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO from movimientos where (CODIGO_MOV >= 2018160000000 and CODIGO_MOV < 2018169999999) ORDER BY CODIGO_MOV DESC LIMIT 1;") + 64];

   sprintf(sql,"select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, CENTRO_DESTINO, INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO from movimientos where (CODIGO_MOV >= %s and CODIGO_MOV < %s) ORDER BY CODIGO_MOV DESC LIMIT 1;",from_mov_code.c_str(), to_mov_code.c_str());

  return;
}


////////
////****TABLE TRANSITO****////
void  updtScaleOutTrans(char *& sql, const char* fecha_hora, long codigo_cliente, long codigo_producto, unsigned int peso_salida, const char* comentario, const char * incidencias)
{
  
  sql = new char[sizeof("UPDATE TRANSITO SET PESO_SALIDA = XXXXXXXXX , comentario_operador = XXXXXXXX, incidencias = XXXXXXXXX WHERE (FECHA_HORA = (XXXX-XX-XX XX:XX:XX) AND CODIGO_CLIENTE=XXXXXX AND CODIGO_PRODUCTO=XXXXXX)")+32 + strlen(comentario) + strlen(incidencias)];

  sprintf(sql,"update transito set PESO_SALIDA = %u, comentario_operador = \"%s\", incidencias = \"%s\" WHERE (FECHA_HORA = \"%s\" AND CODIGO_CLIENTE = \"%lu\" AND CODIGO_PRODUCTO = \"%lu\")",peso_salida,comentario, incidencias,fecha_hora,codigo_cliente,codigo_producto);

  return;
}

void sel_all_unsyncro_transito(char *& sql, int fromStation)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA) FROM TRANSITO WHERE CODIGO_ESTACION=XXXXX AND SINCRONIZADO=0")+12];
  sprintf(sql,"SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA FROM TRANSITO WHERE CODIGO_ESTACION=%d AND SINCRONIZADO=0",fromStation);
  return;
}

void sel_all_transito(char *& sql)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA) FROM TRANSITO")+12];
  sprintf(sql,"SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA FROM TRANSITO");
  return;
}

void sel_all_transito(char *& sql, int fromStation)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA) FROM TRANSITO WHERE CODIGO_ESTACION=XXXXX")+12];
  sprintf(sql,"SELECT DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA FROM TRANSITO WHERE CODIGO_ESTACION=%d",fromStation);
  return;
}

void rmt_del_transito(char *& sql, int fromStation)
{
  sql = new char[sizeof("DELETE FROM transito WHERE CODIGO_ESTACION=XXXXX")+12];
  sprintf(sql,"DELETE FROM transito WHERE CODIGO_ESTACION=%d",fromStation);
  return;
}

/////
///////////////////////////////////
/**** TABLE TRANSITO_SALIDAS *****/
void  updtScaleOutTransSal(char *& sql, const char* fecha_hora, long codigo_cliente, long codigo_producto, unsigned int peso_salida, const char* comentario, const char * incidencias)
{
  
  sql = new char[sizeof("UPDATE TRANSITO_SALIDAS SET PESO_SALIDA = XXXXXXXXX , comentario_operador = \"XXXXXXXX\", incidencias = \"XXXXXXXXX\" WHERE (FECHA_HORA = (XXXX-XX-XX XX:XX:XX) AND CODIGO_CLIENTE=XXXXXX AND CODIGO_PRODUCTO=XXXXXX)")+32 + strlen(comentario) + strlen(incidencias) ];

  sprintf(sql,"update transito_salidas set PESO_RETIRADO = %u , comentario_operador = \"%s\", incidencias = \"%s\" WHERE (FECHA_HORA = \"%s\" AND CODIGO_CLIENTE = \"%lu\" AND CODIGO_PRODUCTO = \"%lu\")",peso_salida,comentario, incidencias, fecha_hora,codigo_cliente,codigo_producto);

  return;
}

void sel_all_unsyncro_transito_dep(char *& sql,int fromStation)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR) FROM TRANSITO_LOCAL WHERE CODIGO_ESTACION=XXXXX AND SICNRONIZADO = 0")+12];
  sprintf(sql,"SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR FROM TRANSITO_SALIDAS WHERE CODIGO_ESTACION=%d AND SINCRONIZADO = 0",fromStation);

}

void sel_all_transito_dep(char *& sql)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR) FROM TRANSITO_LOCAL")+12];
  sprintf(sql,"SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR FROM TRANSITO_SALIDAS");
  return;
}
void sel_all_transito_dep(char *& sql, int fromStation)
{
  sql = new char[sizeof("SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR) FROM TRANSITO_LOCAL WHERE CODIGO_ESTACION=XXXXX")+12];
  sprintf(sql,"SELECT DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR FROM TRANSITO_SALIDAS WHERE CODIGO_ESTACION=%d",fromStation);
  return;
}
void rmt_del_transito_dep(char *& sql, int fromStation)
{
  sql = new char[sizeof("DELETE FROM transito_salidas WHERE CODIGO_ESTACION=XXXXX")+12];
  sprintf(sql,"DELETE FROM transito_salidas WHERE CODIGO_ESTACION=%d",fromStation);
  return;
}
/////////////////////////////////

//////////////
//TABLE TRUCKS
void sel_all_cars(char *& sql)
{
  sql = new char[sizeof("select matricula from vehiculos where borrado is null or borrado = 0")+32];
  sprintf(sql,"select matricula from vehiculos where borrado is null or borrado = 0");
}

void sel_all_cos_from_car(char *&sql, const char *matricula)
{
  sql = new char[sizeof("select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE1 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE2 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE3 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE4 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE5 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE6 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE7 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE8 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE9 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"\" THEN CODIGO_CLIENTE10 END) R1 from VEHICULOS")+strlen(matricula)*10+32];

  sprintf(sql,"select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE1 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE2 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE3 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE4 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE5 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE6 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE7 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE8 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE9 END) R1 from VEHICULOS UNION select MAX(CASE WHEN MATRICULA = \"%s\" THEN CODIGO_CLIENTE10 END) R1 from VEHICULOS",matricula,matricula,matricula,matricula,matricula,matricula,matricula,matricula,matricula,matricula);

  return;
}

//load
//c++ style!
void load_cars(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{

  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into vehiculos (CODIGO_VEHICULO, MATRICULA, VEHICULO_REMOLQUE, TARA, PMA, CODIGO_CLIENTE1, CODIGO_CLIENTE2, CODIGO_CLIENTE3, CODIGO_CLIENTE4, CODIGO_CLIENTE5, CODIGO_CLIENTE6, CODIGO_CLIENTE7, CODIGO_CLIENTE8, CODIGO_CLIENTE9, CODIGO_CLIENTE10) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
       newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());
  return;
}
//remote
void rmt_sel_all_cars(char*&sql)
{
  sql = new char[sizeof("select CODIGO_VEHICULO,MATRICULA,VEHICULO_REMOLQUE ,TARA , PMA ,CODIGO_CLIENTE1 , CODIGO_CLIENTE2 ,CODIGO_CLIENTE3 ,CODIGO_CLIENTE4 ,CODIGO_CLIENTE5,CODIGO_CLIENTE6 , CODIGO_CLIENTE7 ,CODIGO_CLIENTE8 ,CODIGO_CLIENTE9 ,CODIGO_CLIENTE10 from vehiculos WHERE (BORRADO is null or BORRADO = 0);")+32];
  sprintf(sql,"select CODIGO_VEHICULO,MATRICULA,VEHICULO_REMOLQUE ,TARA , PMA ,CODIGO_CLIENTE1 , CODIGO_CLIENTE2 ,CODIGO_CLIENTE3 ,CODIGO_CLIENTE4 ,CODIGO_CLIENTE5,CODIGO_CLIENTE6 , CODIGO_CLIENTE7 ,CODIGO_CLIENTE8 ,CODIGO_CLIENTE9 ,CODIGO_CLIENTE10 from vehiculos WHERE (BORRADO is null or BORRADO = 0);");

  return;
}
//

///////////////
//TABLE STAFF
void sel_staff_data_by_code(char*& sql,long code)
{
  sql = new char[sizeof("select nombre,nif from basculistas where codigo = XXXXXXX and (borrado is null or borrado = 0) ")+32];
  sprintf(sql,"select nombre,nif from basculistas where codigo = \"%lu\" and (borrado is null or borrado = 0)",code);
}

void load_staff(char*& sql, std::vector<std::vector<std::string>> load_data)
{
  std::string new_query;
  std::vector<std::vector<std::string>>::iterator my_row;
  int row;

  new_query = "insert into BASCULISTAS (CODIGO, NOMBRE, NIF) values ";
  row=0;
  for(my_row = load_data.begin(); my_row != load_data.end(); ++my_row)
    {
      new_query +="(\"";
      new_query += vectorToString(*my_row,"\",\"");
      new_query +="\")";
      if(row < load_data.size()-1)
      	new_query += ",";
      row++;
    }

  sql = new char[new_query.size() + 32];
  sprintf(sql,new_query.c_str());

  return; 
}

void rmt_sel_all_staff(char *& sql)
{
  sql = new char[sizeof("select CODIGO, NOMBRE, NIF FROM basculistas WHERE BORRADO = 0;")+32];
  sprintf(sql,"select CODIGO, NOMBRE, NIF FROM basculistas WHERE BORRADO = 0;");

  return;
}

//

////////////////
//TABLE BILLING
void sel_fp_by_cos_code(char *& sql, long code)
{
  sql = new char[sizeof("select FP from entidades_facturacion where codigo = (select CODIGO_ENTIDAD_FACTURACION from clientes where codigo_cliente = XXXXX)")+32];
  
  sprintf(sql,"select FP from entidades_facturacion where codigo = (select CODIGO_ENTIDAD_FACTURACION from clientes where codigo_cliente = %lu)",code);
  
}
void load_billing(char *& sql,std::vector< std::vector< std::string>> load_data)
{
  std::string new_query;
  std::vector<std::vector<std::string>>::iterator my_row;
  int row;

  new_query = "insert into entidades_facturacion (CODIGO, NOMBRE, NIF, DIRECCION, CP, POBLACION, PROVINCIA, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, FP, IBAN, ENVIO_FACT, TELEFONO, MAIL) values ";
  row=0;
  for(my_row = load_data.begin(); my_row != load_data.end(); ++my_row)
    {
      new_query +="(\"";
      new_query += vectorToString(*my_row,"\",\"");
      new_query +="\")";
      if(row < load_data.size()-1)
      	new_query += ",";
      row++;
    }

  sql = new char[new_query.size() + 32];
  sprintf(sql,new_query.c_str());

  return;
}
///remote
void rmt_sel_all_billing(char *& sql)
{
  sql = new char[sizeof("select CODIGO,NOMBRE,NIF,DIRECCION,CP,POBLACION,PROVINCIA,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,FP,IBAN,ENVIO_FACT,TELEFONO,MAIL from entidades_facturacion where (borrado is null or borrado = 0) ")+32];
  sprintf(sql,"select CODIGO,NOMBRE,NIF,DIRECCION,CP,POBLACION,PROVINCIA,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,FP,IBAN,ENVIO_FACT,TELEFONO,MAIL from entidades_facturacion where (BORRADO is null or BORRADO = 0)");
}
//
/////////////////////////////////////////////////////
////****table drivers****////
void sel_driver_data_by_code(char *& sql, long code)
{
  sql = new char[sizeof("SELECT NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from TRANSPORTISTAS WHERE (CODIGO_TRANSPORTISTA=XXXXX AND (BORRADO is null or BORRADO = 0))")+12];

  sprintf(sql,"SELECT NOMBRE, NIF, DIRECCION, PROVINCIA, POBLACION, CP, COMUNIDAD_AUTONOMA, NIMA, NUM_INSCRIPCION, TELEFONO, MAIL from TRANSPORTISTAS WHERE (CODIGO_TRANSPORTISTA=%lu AND (BORRADO is null or BORRADO = 0))",code);

  return;
}

/////////////////////////////////////////
void selectAllFromClient(char * &sql, const char *cliente)
{
  sql = new char[sizeof("select * from `CLIENTES` where (`NOMBRE`= ")+30];
   
  sprintf(sql,"select * from `CLIENTES` where (`NOMBRE`= \"%s\")",cliente);

  return;
}
void selNifFromCostumersByCode(char *&sql, const char *costumerCode)
{
  sql = new char[sizeof("select NIF from `CLIENTES` where (CODIGO= ")+30];
   
  sprintf(sql,"select NIF from `CLIENTES` where (`CODIGO_CLIENTE`= \"%s\")",costumerCode);

  return;
}

void selectAllFromLer(char * &sql, const char *ler)
{
  sql = new char[sizeof("select * from PRODUCTOS where (`CODIGO_LER`= ) LIMIT 1")+30];
   
  sprintf(sql,"select * from PRODUCTOS where (`CODIGO_LER`= \"%s\") LIMIT 1",ler);

  return;
}


void selAllProdsCodesPermsFromProductos(char *&sql,const char* tipoEstacion)
{
  sql = new char[sizeof("select CODIGO_PRODUCTO,CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_XX,CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from PRODUCTOS ORDER BY nombre,nombre2,nombre3")+20];
  sprintf(sql,"select CODIGO_PRODUCTO,CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_%s,CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from PRODUCTOS order by nombre,nombre2,nombre3",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion);
  
  return;
}
void selPermitsTypeClientProd(char *& sql,const char* tipoEstacion, const char* codigoCliente, const char* codigoProducto)
{
  sql = new char[sizeof("select CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from CLIENTES_PRODUCTOS WHERE (CODIGO_PRODUCTO = AND CODIGO_CLIENTE = )")+strlen(tipoEstacion)*5 + strlen(codigoCliente) + strlen(codigoProducto)+32];
  
  sprintf(sql,"select CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from CLIENTES_PRODUCTOS WHERE (CODIGO_PRODUCTO =%s AND CODIGO_CLIENTE =%s)",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,codigoProducto,codigoCliente);

  return;
}

void selProdsCodesPermsFromClienteProductos(char *& sql, const char* codigoCliente , const char* tipoEstacion)
{
  sql = new char[sizeof("select CODIGO_PROD,CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX from CLIENTES_PRODUCTOS WHERE CODIGO_CLIENTE =  ORDER BY CODIGO_PROD ASC")+strlen(tipoEstacion)*5 + strlen(codigoCliente) +32];

  sprintf(sql,"select CODIGO_PROD,CONTRATO_%s,NPT_%s,CB_%s,CP_%s,DCP_%s from CLIENTES_PRODUCTOS WHERE CODIGO_CLIENTE =%s ORDER BY CODIGO_PROD ASC",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,codigoCliente);

  return;
}
void selProdsPermsFromProductosByCode(char *& sql, std::vector <std::string> prodCodes, const char* estacion)
{
  std::string temp;
  std::vector <std::string>::iterator iter;
  sql = new char[sizeof("select CODIGO_PROD,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_XX,CONTRATO_XX,NPT_XX,CB_XX,CP_XX,DCP_XX,CODIGO_ER from productos where (codigo_prod=40001) ORDER BY CODIGO_PROD ASC")+ 9*sizeof(char)*prodCodes.size() +32];

  temp = "select CODIGO_PROD,NOMBRE,NOMBRE2,NOMBRE3,PERMISO_";
  temp += estacion;
  temp +=",CONTRATO_";
  temp += estacion;
  temp += ",NPT_";
  temp += estacion;
  temp += ",CB_";
  temp += estacion;
  temp += ",CP_";
  temp += estacion;
  temp += ",DCP_";
  temp += estacion;
  temp += " from productos where (codigo_prod=";
  for(iter = prodCodes.begin();iter != prodCodes.end(); ++iter)
    {
      if(iter == prodCodes.begin())
	  temp += *iter;
      
      else
	{
	  temp += " OR codigo_prod=";
	  temp += *iter;
	}
    }
  temp+=") ORDER BY codigo_prod ASC";
  sprintf(sql,temp.c_str());
  
  return;
}

void selectClientNameByCode(char *& sql, const char* code)
{
  sql = new char[sizeof("SELECT NOMBRE from CLIENTES WHERE (CODIGO_CLIENTE=XXXXX)")+12];
  sprintf(sql,"SELECT NOMBRE from CLIENTES WHERE (CODIGO_CLIENTE=%s)",code);
  
  return;
}

void selectProductDataByCode(char *& sql, const char* code)
{ 
  sql = new char[sizeof("SELECT NOMBRE, NOMBRE2, CODIGO_LER, NOMBRE 3, PERMISO_PT,CONTRATO_PT,NPT_PT,CB_PT,CP_PT,DCP_PT, PERMISO_ET,CONTRATO_ET,NPT_ET,CB_ET,CP_ET,DCP_ET, PERMISO_D5,CONTRATO_D5,NPT_D5,CB_D5,CP_D5,DCP_D5, PERMISO_SAL,CONTRATO_SAL,NPT_SAL,CB_SAL,CP_SAL,DCP_SAL from PRODUCTOS WHERE (CODIGO_PRODUCTO=XXXXX)")+12];
  sprintf(sql,"SELECT NOMBRE, NOMBRE2, CODIGO_LER, NOMBRE 3, PERMISO_PT,CONTRATO_PT,NPT_PT,CB_PT,CP_PT,DCP_PT, PERMISO_ET,CONTRATO_ET,NPT_ET,CB_ET,CP_ET,DCP_ET, PERMISO_D5,CONTRATO_D5,NPT_D5,CB_D5,CP_D5,DCP_D5, PERMISO_SAL,CONTRATO_SAL,NPT_SAL,CB_SAL,CP_SAL,DCP_SAL from PRODUCTOS WHERE (CODIGO_PRODUCTO=%s)",code);
  
  return; 
}
void selectProductBasisByCode(char *& sql, const char* code)
{  
  sql = new char[sizeof("SELECT CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,DESCRIPCION_PELIGRO from PRODUCTOS WHERE (CODIGO_PRODUCTO=XXXXX)")+12];
  sprintf(sql,"SELECT CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,DESCRIPCION_PELIGRO from PRODUCTOS WHERE (CODIGO_PRODUCTO=%s)",code);
  
  return; 
}
void selectProductBasisByCode(char *& sql, long code)
{  
  sql = new char[sizeof("SELECT CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,DESCRIPCION_PELIGRO from PRODUCTOS WHERE (CODIGO_PRODUCTO=XXXXX)")+12];
  sprintf(sql,"SELECT CODIGO_LER,NOMBRE,NOMBRE2,NOMBRE3,DESCRIPCION_PELIGRO from PRODUCTOS WHERE (CODIGO_PRODUCTO=%ld)",code);
  
  return; 
}

void selPermitsFromClientAndProd(char *& sql,const char* tipoEstacion, const char* codigoCliente, const char* codigoProducto)
{
  sql = new char[sizeof("select case when PRODUCTOS.PERMISO_XXX > 0 then 1 else 0 end,case when PRODUCTOS.CONTRATO_XXX>0 AND CLIENTES_PRODUCTOS.CONTRATO_XXX >= CURRENT_DATE THEN 1 WHEN PRODUCTOS.CONTRATO_XXX=0 THEN 1 ELSE 0 END,case when PRODUCTOS.NPT_XXX>0 AND CLIENTES_PRODUCTOS.NPT_XXX >0 THEN 1 WHEN PRODUCTOS.NPT_XXX=0 THEN 1 ELSE 0 END,case when PRODUCTOS.CB_XXX>0 AND CLIENTES_PRODUCTOS.CB_XXX >0 THEN 1 WHEN PRODUCTOS.CB_SAL=0 THEN 1 ELSE 0 END,case when PRODUCTOS.CP_SAL>0 AND CLIENTES_PRODUCTOS.CP_SAL >0 THEN 1 WHEN PRODUCTOS.CP_SAL=0 THEN 1 ELSE 0 END,case when PRODUCTOS.DCP_SAL>0 AND CLIENTES_PRODUCTOS.DCP_SAL >0 THEN 1 WHEN PRODUCTOS.DCP_SAL=0 THEN 1 ELSE 0 END FROM CLIENTES_PRODUCTOS INNER JOIN PRODUCTOS ON CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = xxxxx AND PRODUCTOS.CODIGO_PRODUCTO = xxxxx AND CLIENTES_PRODUCTOS.CODIGO_CLIENTE = xxxxx") + 32];
  
  sprintf(sql,"select case when PRODUCTOS.PERMISO_%s > 0 then 1 else 0 end,case when PRODUCTOS.CONTRATO_%s>0 and CLIENTES_PRODUCTOS.CONTRATO_%s >= CURRENT_DATE then 1 when PRODUCTOS.CONTRATO_%s=0 then 1 else 0 end,case when PRODUCTOS.NPT_%s>0 and CLIENTES_PRODUCTOS.NPT_%s >0 then 1 when PRODUCTOS.NPT_%s=0 then 1 else 0 end, case when PRODUCTOS.CB_%s>0 and CLIENTES_PRODUCTOS.CB_%s >0 then 1 when PRODUCTOS.CB_%s=0 then 1 else 0 end, case when PRODUCTOS.CP_%s>0 and CLIENTES_PRODUCTOS.CP_%s >0 THEN 1 when PRODUCTOS.CP_%s=0 then 1 else 0 end,case when PRODUCTOS.DCP_%s>0 and CLIENTES_PRODUCTOS.DCP_%s >0 then 1 when PRODUCTOS.DCP_%s=0 then 1 else 0 end from CLIENTES_PRODUCTOS inner join PRODUCTOS on CLIENTES_PRODUCTOS.CODIGO_PRODUCTO = %s and PRODUCTOS.CODIGO_PRODUCTO = %s and CLIENTES_PRODUCTOS.CODIGO_CLIENTE = %s",tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,tipoEstacion,codigoProducto,codigoProducto,codigoCliente);

  return;
}

void selLastDiFromMovementsByClientProduct(char *& sql, const char* codigoCliente, const char* codigoProducto)
{
 sql = new char[sizeof("select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=XXXXX AND CODIGO_PRODUCTO=XXXXX ORDER BY DATETIME(FECHA_HORA) DESC;") + 32];

 sprintf(sql,"select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=%s AND CODIGO_PRODUCTO=%s ORDER BY DATETIME(FECHA_HORA_FINAL) DESC", codigoCliente,codigoProducto);

 return;
}

void selLastDiFromMovementsByClient(char *& sql, const char* codigoCliente)
{
 sql = new char[sizeof("select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=XXXXX ORDER BY DATETIME(FECHA_HORA) DESC;") + 32];

 sprintf(sql,"select DI,FECHA_HORA_FINAL from MOVIMIENTOS where CODIGO_CLIENTE=%s ORDER BY DATETIME(FECHA_HORA_FINAL) DESC", codigoCliente);

 return;
}

void selLastMovCode(char *& sql,const char* codigo_estacion)
{
  time_t myTime = time(NULL);
  struct tm *aTime = localtime(&myTime);
  int year = aTime->tm_year + 1900;

  std::string codigo = std::to_string(year);
  codigo += codigo_estacion;

  std::string codigo_min = codigo + "0000011";
  std::string codigo_max = codigo + "9999999";
  
  sql = new char[sizeof("select CODIGO_MOV FROM MOVIMIENTOS WHERE (CODIGO_MOV >= XXXXXXXXXXXXXXX AND CODIGO_MOV <= XXXXXXXXXXXXXXXX) ORDER BY CODIGO_MOV DESC LIMIT 1")+32];

  sprintf(sql,"select CODIGO_MOV FROM MOVIMIENTOS WHERE (CODIGO_MOV >= %s AND CODIGO_MOV <= %s) ORDER BY CODIGO_MOV DESC LIMIT 1",codigo_min.c_str(),codigo_max.c_str());

  return;
}

void selAllDrivers(char *& sql)
{
 sql = new char[sizeof("select codigo_transportista, nombre, nif, direccion, provincia, poblacion, cp, comunidad_autonoma, nima, num_inscripcion, telefono, mail FROM transportistas order by nombre")+32];
 
 sprintf(sql,"select codigo_transportista, nombre, nif, direccion, provincia, poblacion, cp, comunidad_autonoma, nima, num_inscripcion, telefono, mail FROM transportistas order by nombre");

  return;
}
void selAllMovements(char*&sql)
{
  sql = new char[sizeof("select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOV, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO FROM MOVIMIENTOS")+32];
 
  sprintf(sql,"select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOV, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO FROM MOVIMIENTOS");

  return;
}


void remote_selectAllProducts(char*&sql)
{
  sql = new char[sizeof("select CODIGO_PROD, CODIGO_LER , NOMBRE , NOMBRE2 , NOMBRE3 , PERMISO_PT ,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT ,PERMISO_ET ,CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,PERMISO_D5 ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,PERMISO_SAL ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL ,DESCRIPCION_PELIGRO,PRECIO_DEFECTO from productos WHERE BORRADO = 0;")+32];
  sprintf(sql,"select CODIGO_PROD, CODIGO_LER , NOMBRE , NOMBRE2 , NOMBRE3 , PERMISO_PT ,CONTRATO_PT , NPT_PT , CB_PT ,CP_PT , DCP_PT ,PERMISO_ET ,CONTRATO_ET , NPT_ET , CB_ET ,CP_ET , DCP_ET ,PERMISO_D5 ,CONTRATO_D5 , NPT_D5 , CB_D5 ,CP_D5 , DCP_D5 ,PERMISO_SAL ,CONTRATO_SAL , NPT_SAL , CB_SAL ,CP_SAL , DCP_SAL ,DESCRIPCION_PELIGRO,PRECIO_DEFECTO from productos WHERE BORRADO = 0;");

  return;
}

void remote_selectAllOrders(char*&sql, const char * codigo_estacion)
{
  sql = new char[sizeof("select ECOEMBES, CODIGO_CLIENTE, CODIGO_PRODUCTO, FECHA_FIRMA, FECHA_PROGRAMADA, PRECIO_TN, PESO_RETIRAR , CODIGO_DESTINO , OPERACION_TRATAMIENTO , REPETIR from ordenes where CODIGO_DESTINO = XX")+32];
  sprintf(sql,"select ECOEMBES, CODIGO_CLIENTE, CODIGO_PRODUCTO, FECHA_FIRMA, FECHA_PROGRAMADA, PRECIO_TN, PESO_RETIRAR , CODIGO_DESTINO , OPERACION_TRATAMIENTO , REPETIR from ordenes where CODIGO_DESTINO = %s",codigo_estacion);

  return;
}

void remote_selectAllDrivers(char*&sql)
{
  sql = new char[sizeof("select codigo_transportista, nombre, nif, domicilio, provincia, poblacion, cp, comunidad_autonoma, nima, num_inscripcion, telefono, mail FROM transportistas WHERE BORRADO = 0;")+32];
  sprintf(sql,"select codigo_transportista, nombre, nif, domicilio, provincia, poblacion, cp, comunidad_autonoma, nima, num_inscripcion, telefono, mail FROM transportistas WHERE BORRADO = 0;");

  return;
}

void rmt_selAllFromTransito(char *& sql,int fromStation)
{
  sql = new char[sizeof("select DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR,PESO_SALIDA,CODIGO_ESTACION FROM transito where CODIGO_ESTACION = XXXXX")+32];
  sprintf(sql,"select DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR,PESO_SALIDA,CODIGO_ESTACION FROM transito where CODIGO_ESTACION = %d",fromStation);
  
  return;
}

void rmt_selAllFromTransitoSalidas(char *& sql,int fromStation)
{
  sql = new char[sizeof("select DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES,  INCIDENCIAS, COMENTARIO_OPERADOR,CODIGO_ESTACION FROM transito_salidas where CODIGO_ESTACION = XXXXX")+32];
  sprintf(sql,"select DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES,  INCIDENCIAS, COMENTARIO_OPERADOR,CODIGO_ESTACION FROM transito_salidas where CODIGO_ESTACION = %d",fromStation);

  return;
}

void rmt_selAllStations(char *& sql)
{
  sql = new char[sizeof("select CODIGO_CENTRO,TIPO_CENTRO,NOMBRE,NIF,DOMICILIO,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO FROM centros WHERE BORRADO = 0;")+32];
  sprintf(sql,"select CODIGO_CENTRO,TIPO_CENTRO,NOMBRE,NIF,DOMICILIO,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO FROM centros WHERE BORRADO = 0");
  return;
}

void rmt_selAllMovements(char *& sql)
{
  sql = new char[sizeof("select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO FROM movimientos")+32];
 
  sprintf(sql,"select CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN,CENTRO_DESTINO,INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO FROM movimientos");

  return;
}
//////

/////syncronization
//local
std::string sqlLoadCostumers(std::vector<std::vector<std::string>> dataReturn)
{

  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into clientes (codigo_cliente, nombre,nif, direccion, provincia,poblacion,cp,codigo_entidad_facturacion,cbc,tipo,comunidad_autonoma,nima,num_inscripcion,telefono,mail,transportista_defecto) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }

  return newQuery;
}



//c++ style!
void sqlLoadTransfers(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{

  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transferencias (DI, FECHA_HORA, CODIGO_ORIGEN, CODIGO_DESTINO, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, MATRICULA, REMOLQUE, INCIDENCIAS, COMENTARIO_OPERADOR, OPERACION_TRATAMIENTO,SINCRONIZADO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {  
      //TRANSFORM MYSQL DATES TO SQLITE DATES
      myRow->at(1) = mysql2sqliteDate(myRow->at(1));
      //////////////////////////////////////
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\",1)";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());
  return;
}

//c++ style!
void sqlLoadOrders(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{

  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into ordenes ( ECOEMBES, CODIGO_CLIENTE, CODIGO_PRODUCTO, FECHA_FIRMA, FECHA_PROGRAMADA, PRECIO_TN, PESO_A_RETIRAR , CODIGO_DESTINO , OPERACION_TRATAMIENTO , REPETIR) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      //TRANSFORM MYSQL DATES TO SQLITE DATES
      myRow->at(3) = mysql2sqliteDate(myRow->at(3));
      myRow->at(4) = mysql2sqliteDate(myRow->at(4));
      //////////////////////////////////////
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
       newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());
  return;
}

void sqlLoadDrivers(char *&sql,std::vector<std::vector<std::string>> dataReturn)
{

  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transportistas (codigo_transportista, nombre,nif, direccion, provincia,poblacion,cp,comunidad_autonoma,nima,num_inscripcion,telefono,mail) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}
void sqlLoadTransito(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transito (DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA, CODIGO_ESTACION, SINCRONIZADO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      //TRANSFORM MYSQL DATES TO SQLITE DATES
      myRow->at(1) = mysql2sqliteDate(myRow->at(1));
      //////////////////////////////////////
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\",1)";  //<- 1 for syncronized
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}
void sqlLoadTransitoSalidas(char*& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR, CODIGO_ESTACION, SINCRONIZADO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      //TRANSFORM MYSQL DATES TO SQLITE DATES
      myRow->at(1) = mysql2sqliteDate(myRow->at(1));
      //////////////////////////////////////
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\",1)"; //<- 1 for syncronized
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}
void sqlLoadStations(char *& sql,std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into centros (codigo_centro, tipo_centro, NOMBRE,NIF,DIRECCION,PROVINCIA,POBLACION,CP,COMUNIDAD_AUTONOMA,NIMA,NUM_INSCRIPCION,TELEFONO,MAIL,BORRADO) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}


//remote

void rmt_updtMovements(char *&sql, std::vector<std::vector<std::string>> dataReturn)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into movimientos (CODIGO_MOV, DI, FECHA_HORA_INICIO, FECHA_HORA_FINAL, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, CODIGO_TRANSPORTISTA, PESO_NETO, PESO_TARA, PESO_BRUTO, PRECIO, VEHICULO, REMOLQUE, CENTRO_ORIGEN, CENTRO_DESTINO, INCIDENCIAS, COMENTARIO_OPERADOR, CLIENTE_PARTICULAR_NOMBRE, CLIENTE_PARTICULAR_NIF, CLIENTE_PARTICULAR_DOMICILIO, CLIENTE_PARTICULAR_PROVINCIA, CLIENTE_PARTICULAR_POBLACION, CLIENTE_PARTICULAR_CODIGO_POSTAL, CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA, CLIENTE_PARTICULAR_NIMA, CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO, CLIENTE_PARTICULAR_TELEFONO, CLIENTE_PARTICULAR_CORREO_ELECTRONICO, DESTINO_NOMBRE, DESTINO_NIF, DESTINO_DOMICILIO, DESTINO_PROVINCIA, DESTINO_POBLACION, DESTINO_CODIGO_POSTAL, DESTINO_COMUNIDAD_AUTONOMA, DESTINO_NIMA, DESTINO_NUM_INSCRIPCION_REGISTRO, DESTINO_TELEFONO, DESTINO_CORREO_ELECTRONICO, TIPO_CLIENTE) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  newQuery += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA_INICIO = VALUES(FECHA_HORA_INICIO) ,FECHA_HORA_FINAL = VALUES(FECHA_HORA_FINAL), TIPO_MOVIMIENTO = VALUES(TIPO_MOVIMIENTO), CODIGO_CLIENTE = VALUES(CODIGO_CLIENTE), CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), CODIGO_TRANSPORTISTA = VALUES(CODIGO_TRANSPORTISTA), PESO_NETO = VALUES(PESO_NETO), PESO_TARA = VALUES(PESO_TARA), PESO_BRUTO = VALUES(PESO_BRUTO), PRECIO = VALUES(PRECIO), VEHICULO = VALUES(VEHICULO), REMOLQUE = VALUES(REMOLQUE), CENTRO_ORIGEN = VALUES(CENTRO_ORIGEN), CENTRO_DESTINO = VALUES(CENTRO_DESTINO), INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), CLIENTE_PARTICULAR_NOMBRE = VALUES(CLIENTE_PARTICULAR_NOMBRE), CLIENTE_PARTICULAR_NIF = VALUES(CLIENTE_PARTICULAR_NIF), CLIENTE_PARTICULAR_DOMICILIO = VALUES(CLIENTE_PARTICULAR_DOMICILIO), CLIENTE_PARTICULAR_PROVINCIA = VALUES(CLIENTE_PARTICULAR_PROVINCIA), CLIENTE_PARTICULAR_POBLACION = VALUES(CLIENTE_PARTICULAR_POBLACION), CLIENTE_PARTICULAR_CODIGO_POSTAL = VALUES(CLIENTE_PARTICULAR_CODIGO_POSTAL), CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA = VALUES(CLIENTE_PARTICULAR_COMUNIDAD_AUTONOMA), CLIENTE_PARTICULAR_NIMA = VALUES(CLIENTE_PARTICULAR_NIMA), CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO = VALUES(CLIENTE_PARTICULAR_NUM_INSCRIPCION_REGISTRO), CLIENTE_PARTICULAR_TELEFONO = VALUES(CLIENTE_PARTICULAR_TELEFONO), CLIENTE_PARTICULAR_CORREO_ELECTRONICO = VALUES(CLIENTE_PARTICULAR_CORREO_ELECTRONICO), DESTINO_NOMBRE = VALUES(DESTINO_NOMBRE), DESTINO_NIF = VALUES(DESTINO_NIF), DESTINO_DOMICILIO = VALUES(DESTINO_DOMICILIO), DESTINO_PROVINCIA = VALUES(DESTINO_PROVINCIA), DESTINO_POBLACION = VALUES(DESTINO_POBLACION), DESTINO_CODIGO_POSTAL = VALUES(DESTINO_CODIGO_POSTAL), DESTINO_COMUNIDAD_AUTONOMA = VALUES(DESTINO_COMUNIDAD_AUTONOMA), DESTINO_NIMA = VALUES(DESTINO_NIMA), DESTINO_NUM_INSCRIPCION_REGISTRO = VALUES(DESTINO_NUM_INSCRIPCION_REGISTRO), DESTINO_TELEFONO = VALUES(DESTINO_TELEFONO), DESTINO_CORREO_ELECTRONICO = VALUES(DESTINO_CORREO_ELECTRONICO),  TIPO_CLIENTE = VALUES(TIPO_CLIENTE)";
  
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}

void rmt_updtTransito(char *& sql, std::vector<std::vector<std::string>> dataReturn, int codigo_estacion)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transito (DI, FECHA_HORA, TIPO_MOVIMIENTO, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, CODIGO_ORIGEN, INCIDENCIAS, COMENTARIO_OPERADOR, PESO_SALIDA, CODIGO_ESTACION) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery +="\",";
      newQuery += std::to_string(codigo_estacion);
      newQuery +=")";      
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  newQuery += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA = VALUES(FECHA_HORA), TIPO_MOVIMIENTO = VALUES(TIPO_MOVIMIENTO), CODIGO_CLIENTE = VALUES(CODIGO_CLIENTE), CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), PESO_ENTRADA = VALUES(PESO_ENTRADA), PRECIO = VALUES(PRECIO), MATRICULA = VALUES(MATRICULA), REMOLQUE = VALUES(REMOLQUE), CODIGO_ORIGEN = VALUES(CODIGO_ORIGEN), INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), PESO_SALIDA = VALUES(PESO_SALIDA), CODIGO_ESTACION = VALUES(CODIGO_ESTACION)";
  
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}

void rmt_updtTransitoSalidas(char *& sql, std::vector<std::vector<std::string>> dataReturn, int codigo_estacion)
{
  std::string newQuery;
  std::vector<std::vector<std::string>>::iterator myRow;
  int row;

  newQuery = "insert into transito_salidas (DI, FECHA_HORA, CODIGO_CLIENTE, CODIGO_PRODUCTO, PESO_ENTRADA, PRECIO, MATRICULA, REMOLQUE, PESO_A_RETIRAR, PESO_RETIRADO, CODIGO_DESTINO, ECOEMBES, INCIDENCIAS, COMENTARIO_OPERADOR, CODIGO_ESTACION) values ";
  row=0;
  for(myRow = dataReturn.begin(); myRow != dataReturn.end();++myRow)
    {
      newQuery +="(\"";
      newQuery += vectorToString(*myRow,"\",\"");
      newQuery += "\",";
      newQuery += std::to_string(codigo_estacion);
      newQuery +=")";
      if(row < dataReturn.size()-1)
      	newQuery += ",";
      row++;
    }
  newQuery += " ON DUPLICATE KEY UPDATE  DI = VALUES(DI), FECHA_HORA = VALUES(FECHA_HORA), CODIGO_CLIENTE = VALUES(CODIGO_CLIENTE), CODIGO_PRODUCTO = VALUES(CODIGO_PRODUCTO), PESO_ENTRADA = VALUES(PESO_ENTRADA), PRECIO = VALUES(PRECIO), MATRICULA = VALUES(MATRICULA), REMOLQUE = VALUES(REMOLQUE), PESO_A_RETIRAR = VALUES(PESO_A_RETIRAR), PESO_RETIRADO = VALUES(PESO_RETIRADO), CODIGO_DESTINO = VALUES(CODIGO_DESTINO), INCIDENCIAS = VALUES(INCIDENCIAS), COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), CODIGO_ESTACION = VALUES(CODIGO_ESTACION)";
  
  sql = new char[newQuery.size() + 32];
  sprintf(sql,newQuery.c_str());

  return;
}

void remote_updatePesoSalidaTransito(std::string& sql, long costumer_code, const char* date_time, int station_code, unsigned int scale, const char* comentario, const char* incidents)
{    
  sql = "INSERT INTO transito (FECHA_HORA, CODIGO_CLIENTE, CODIGO_ESTACION,PESO_SALIDA,COMENTARIO_OPERADOR,INCIDENCIAS) VALUES (\"";
  sql += date_time;
  sql += "\",";
  sql += std::to_string(costumer_code);
  sql += ",";
  sql += std::to_string(station_code);
  sql += ",";
  sql += std::to_string(scale);
  sql += ",\"";
  sql += comentario; 
  sql += "\",\"";
  sql += incidents;
  sql += "\") ON DUPLICATE KEY UPDATE PESO_SALIDA = VALUES(PESO_SALIDA),COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), INCIDENCIAS = VALUES(INCIDENCIAS);";
 
  return;
}
void remote_updatePesoSalidaTransitoSalida(std::string& sql, long costumer_code, const char* date_time, long station_code,  unsigned int scale, const char* comentario, const char* incidents)
{    
  sql = "INSERT INTO transito_salidas (FECHA_HORA, CODIGO_CLIENTE, CODIGO_ESTACION,PESO_RETIRADO,COMENTARIO_OPERADOR, INCIDENCIAS) VALUES (\"";
  sql += date_time;
  sql += "\",";
  sql += std::to_string(costumer_code);
  sql += ",";
  sql += std::to_string(station_code);
  sql += ",";
  sql += std::to_string(scale);
  sql += ",\"";
  sql += comentario; 
  sql += "\",\"";
  sql += incidents;
  sql += "\") ON DUPLICATE KEY UPDATE PESO_RETIRADO = VALUES(PESO_RETIRADO),COMENTARIO_OPERADOR = VALUES(COMENTARIO_OPERADOR), INCIDENCIAS = VALUES(INCIDENCIAS);";
 
  return;
}
