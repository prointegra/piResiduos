# piResiduos
garbage managing software, (currently only in spanish) we have several local nodes managing input/ouput materials, and a central administration server.
developed using pvbrowser(https://github.com/pvbrowser/pvb) SCADA framework.

## dependencies
libharu >= 2.3.0
SmtpClient-for-Qt (https://github.com/bluetiger9/SmtpClient-for-Qt) Put it inside lib folder, see lib/README.md for more info.
pvbrowser (pvslib and rllib)
boost

## remote database connection and web administration page
piResiduos is developed for working with a central remote MySQL database in mind, you'll need a VPS and it's connections for tunneling the database (SSH) and being able to syncronize, update, share, etc.

Also there will be files app will backup via SSH tunneling.

You'll have to configure this connection in config.ini, in piResiduos.sh, in extra/scripts... files and in generic_tools.cpp (function int copy_files_to_remote_server(std::string folder_in_backup))

put the ssh key for example in extras/ .

for building the local database execute in terminal it's creations cript

 sqlite3 bio.db < bio.sqlite3
 
## remote server database structure

 see file bio.remote.

 mysql> show tables;
 +-----------------------------------+
 | Tables_in_biogesin_SistGestPesaje |
 +-----------------------------------+
 | basculistas                       |
 | centros                           |
 | clientes                          |
 | clientes_asociado                 |
 | clientes_productos                |
 | configuracion                     |
 | entidades_facturacion             |
 | movimientos                       |
 | ordenes                           |
 | permisos                          |
 | productos                         |
 | roles                             |
 | transferencias                    |
 | transito                          |
 | transito_salidas                  |
 | transportistas                    |
 | usuarios                          |
 | vehiculos                         |
 +-----------------------------------+
 
 mysql> describe basculistas;
 +---------+---------+------+-----+---------+----------------+
 | Field   | Type    | Null | Key | Default | Extra          |
 +---------+---------+------+-----+---------+----------------+
 | CODIGO  | int(11) | NO   | PRI | NULL    | auto_increment |
 | NOMBRE  | text    | NO   |     | NULL    |                |
 | NIF     | text    | NO   |     | NULL    |                |
 | BORRADO | int(11) | NO   |     | 0       |                |
 +---------+---------+------+-----+---------+----------------+
 
 mysql> describe centros;
 +--------------------+-------------+------+-----+---------+-------+
 | Field              | Type        | Null | Key | Default | Extra |
 +--------------------+-------------+------+-----+---------+-------+
 | CODIGO_CENTRO      | int(20)     | NO   | PRI | NULL    |       |
 | TIPO_CENTRO        | varchar(20) | NO   |     | NULL    |       |
 | NOMBRE             | text        | NO   |     | NULL    |       |
 | NIF                | varchar(50) | NO   |     | NULL    |       |
 | DOMICILIO          | text        | NO   |     | NULL    |       |
 | PROVINCIA          | text        | NO   |     | NULL    |       |
 | POBLACION          | text        | NO   |     | NULL    |       |
 | CP                 | varchar(5)  | NO   |     | NULL    |       |
 | COMUNIDAD_AUTONOMA | text        | NO   |     | NULL    |       |
 | NIMA               | varchar(10) | NO   |     | NULL    |       |
 | NUM_INSCRIPCION    | varchar(50) | NO   |     | NULL    |       |
 | TELEFONO           | varchar(50) | NO   |     | NULL    |       |
 | MAIL               | text        | NO   |     | NULL    |       |
 | BORRADO            | int(11)     | NO   |     | 0       |       |
 +--------------------+-------------+------+-----+---------+-------+

 mysql> describe clientes;
 +-----------------------+-------------+------+-----+---------+----------------+
 | Field                 | Type        | Null | Key | Default | Extra          |
 +-----------------------+-------------+------+-----+---------+----------------+
 | CODIGO                | int(11)     | NO   | PRI | NULL    | auto_increment |
 | NOMBRE                | text        | YES  |     | NULL    |                |
 | NIF                   | text        | YES  |     | NULL    |                |
 | DIRECCION             | text        | YES  |     | NULL    |                |
 | PROVINCIA             | text        | YES  |     | NULL    |                |
 | POBLACION             | text        | YES  |     | NULL    |                |
 | CP                    | int(11)     | YES  |     | NULL    |                |
 | ENTIDAD_FACTURACION   | int(11)     | YES  |     | NULL    |                |
 | CBC                   | int(11)     | YES  |     | NULL    |                |
 | TIPO                  | int(11)     | NO   |     | NULL    |                |
 | COMUNIDAD_AUTONOMA    | text        | NO   |     | NULL    |                |
 | NIMA                  | varchar(10) | NO   |     | NULL    |                |
 | NUM_INSCRIPCION       | varchar(50) | NO   |     | NULL    |                |
 | TELEFONO              | varchar(50) | NO   |     | NULL    |                |
 | MAIL                  | text        | NO   |     | NULL    |                |
 | TRANSPORTISTA_DEFECTO | int(11)     | NO   |     | 0       |                |
 | BORRADO               | int(11)     | NO   |     | 0       |                |
 +-----------------------+-------------+------+-----+---------+----------------+

 mysql> describe clientes_asociado;
 +-----------------+---------+------+-----+---------+----------------+
 | Field           | Type    | Null | Key | Default | Extra          |
 +-----------------+---------+------+-----+---------+----------------+
 | id              | int(11) | NO   | PRI | NULL    | auto_increment |
 | codigo_padre    | int(11) | NO   |     | NULL    |                |
 | codigo_asociado | int(11) | NO   |     | NULL    |                |
 +-----------------+---------+------+-----+---------+----------------+

 


## hardware needed
It was first designed using a privative signing pad, it has been removed in this free version, now I think I would use a software signing pad using dual screens.

It uses scales, and we communicate it using a basic rs232 serial protocol, sending a command and receiving the weight. (we use boost, is easy to understand it protocol seeing source code) You can bypass it inserting plate by hand.

It uses privative cameras for taking plates from trucks, they are from a Spanish company bad for free software but also technical support, so we have developed our own library using it's http API. You can bypass it inserting plate by hand.

## Compile and execute
It has been developed only for GNU/Linux, it's working now for real under ubuntu 16.04 (xenial)

Once dependencies are installed or compiled and linked.

 qmake
 make
 sh piResiduos.sh

Happy Hacking!

## license and copyright
 This file is part of PiResiduos.

 Copyright 2017-2019, Prointegra SL.

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






