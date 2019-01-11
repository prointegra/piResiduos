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

//###############################################################
//# mask7_slots.h for ProcessViewServer created: vie mar 17 12:33:32 2017
//# please fill out these slots
//# here you find all possible events
//# Yours: Lehrig Software Engineering
//# PANTALLA DE EDICION DE DI
//###############################################################

// todo: uncomment me if you want to use this data aquisiton
// also uncomment this classes in main.cpp and pvapp.h
// also remember to uncomment rllib in the project file
//extern rlModbusClient     modbus;  //Change if applicable
//extern rlSiemensTCPClient siemensTCP;
//extern rlPPIClient        ppi;
extern std::string type;
extern std::string nombre;
extern station * myStation;
extern SYNC_DATA my_ssh_syncro_data;
extern GLOBAL_DATA globalconfiguration;
#include <boost/algorithm/string.hpp>
#include "mask7_data.h"
#include "mask7_tools.h"
#include "mask_tools.h"


static int slotInit(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //
  pvResize(p,0,1910,1020);
  std::string wholeTitle = getTitle();
  pvSetText(p,LABTYPE,wholeTitle.c_str());
  //memset(d,0,sizeof(DATA));
  
  //dynamic GUI construction
  if(formDI->retDepMovType() == DEF_MOV_TRANSFER || formDI->retDepMovType() == DEF_MOV_SALIDA)
    {
      //a) centro nuestro centro de origen

	std::string temp;
	station * localOrigin;
	formDI->retDepOriginStation(localOrigin);
        pvSetText(p,EDITNOMBRE_A,localOrigin->getName().c_str());
	pvSetText(p,EDITNIF_A,localOrigin->getNif().c_str());
	pvSetText(p,EDITDIREC_A,localOrigin->getAddress().c_str());
	temp = std::to_string(localOrigin->getZip());
	pvSetText(p,EDITCP_A,temp.c_str());
	pvSetText(p,EDITMUNI_A,localOrigin->getCity().c_str());
	pvSetText(p,EDITPRO_A,localOrigin->getProvence().c_str());
	pvSetText(p,EDITCA_A,localOrigin->getRegion().c_str());
	temp = std::to_string(localOrigin->getNima());
	pvSetText(p,EDITNIMA_A,temp.c_str());
	temp = std::to_string(localOrigin->getNumIns());
	pvSetText(p,EDITREG_A,temp.c_str());



      //TODO RODRIGO A COMPLETAR (puedes ver sus funciones en station.h)

      //(Al final dejar esto, hay que borrar la instancia de la clase localOrigin de memoria)
      delete localOrigin;
      //b) cliente, our costumer, who am I?

      costumer * bio;
      formDI->retOurId(bio);

      pvSetText(p,EDITNOMBRE_B,bio->getName().c_str());
      pvSetText(p,EDITNIF_B,bio->getNif().c_str());
      pvSetText(p,EDITDIREC_B,bio->getAddress().c_str());
	temp = std::to_string(bio->getCp());
      pvSetText(p,EDITCP_B,temp.c_str());
      pvSetText(p,EDITMUNI_B,bio->getCity().c_str());
      pvSetText(p,EDITPRO_B,bio->getProvence().c_str());
      pvSetText(p,EDITCA_B,bio->getRegion().c_str());
	temp = std::to_string(bio->getNima());
      pvSetText(p,EDITNIMA_B,temp.c_str());
	temp = std::to_string(bio->getNumIns());
      pvSetText(p,EDITREG_B,temp.c_str());
	temp = std::to_string(bio->getPhone());
      pvSetText(p,EDITTFN_B,temp.c_str());
      pvSetText(p,EDITEMAIL_B,bio->getMail().c_str());

      //TODO RODRIGO A COMPLETAR
      delete bio;
    }
  else
    {
      //b) cliente, nuestro cliente
      if(formDI->retDepCosName().compare("OTROS"))
	{	

	std::string temp;
		pvSetText(p,EDITNOMBRE_B,formDI->retDepCosName().c_str());
	      pvSetText(p,EDITNIF_B,formDI->retDepCosNif().c_str());
	      pvSetText(p,EDITDIREC_B,formDI->retDepCosAddr().c_str());
		temp = std::to_string(formDI->retDepCosZip());
	      pvSetText(p,EDITCP_B,temp.c_str());
	      pvSetText(p,EDITMUNI_B,formDI->retDepCosCity().c_str());
	      pvSetText(p,EDITPRO_B,formDI->retDepCosProv().c_str());
	      pvSetText(p,EDITCA_B,formDI->retDepCosReg().c_str());
		temp = std::to_string(formDI->retDepCosNima());
	      pvSetText(p,EDITNIMA_B,temp.c_str());
		temp = std::to_string(formDI->retDepCosNumIns());
	      pvSetText(p,EDITREG_B,temp.c_str());
		temp = std::to_string(formDI->retDepCosPhone());
	      pvSetText(p,EDITTFN_B,temp.c_str());
	      pvSetText(p,EDITEMAIL_B,formDI->retDepCosMail().c_str());
	  //TODO RODRIGO, a completar
	}
      else //CLIENTE PARTICULAR
	{
	std::string temp;

	  pvSetText(p,EDITNOMBRE_B,formDI->retDepPCosName().c_str());
	  pvSetText(p,EDITNIF_B,formDI->retDepPCosNif().c_str());
	  pvSetText(p,EDITDIREC_B,formDI->retDepPCosAddr().c_str());
	  temp = std::to_string(formDI->retDepPCosZip());
	  pvSetText(p,EDITCP_B,temp.c_str());
	  pvSetText(p,EDITMUNI_B,formDI->retDepPCosCity().c_str());
	  pvSetText(p,EDITPRO_B,formDI->retDepPCosProv().c_str());
	  pvSetText(p,EDITCA_B,formDI->retDepPCosReg().c_str());
	  temp = std::to_string(formDI->retDepPCosNima());
	  pvSetText(p,EDITNIMA_B,temp.c_str());
	  temp = std::to_string(formDI->retDepPCosNumIns());
	  pvSetText(p,EDITREG_B,temp.c_str());
          temp = std::to_string(formDI->retDepPCosPhone());
	  pvSetText(p,EDITTFN_B,temp.c_str());
	  pvSetText(p,EDITEMAIL_B,formDI->retDepPCosMail().c_str());

	  pvSetEditable(p,EDITNOMBRE_B,1);
	  pvSetEditable(p,EDITNIF_B,1);
	  pvSetEditable(p,EDITDIREC_B,1);
	  pvSetEditable(p,EDITCP_B,1);
	  pvSetEditable(p,EDITMUNI_B,1);
	  pvSetEditable(p,EDITPRO_B,1);
	  pvSetEditable(p,EDITCA_B,1);
	  pvSetEditable(p,EDITNIMA_B,1);
	  pvSetEditable(p,EDITREG_B,1);
	  pvSetEditable(p,EDITCNAE_A,1);
	  //TODO RODRIGO, a completar
	}
      //A) vacío
    }
  
  
  //console
  consoleRefresh(p,d);
  
  return 0;
}

static int slotNullEvent(PARAM *p, DATA *d)
{
  if(p == NULL || d == NULL) return -1;
  //máquina de cambio de estados Entrada PT
  std::cout << "#######DEBUG EDICION DI######" << std::endl;
 
  std::cout << "############" << std::endl;
  //maquinaEstados(p,d);
  //actualizaEstado(p,d);
  //console
  consoleRefresh(p,d);
  //date and Time
  setDate(p,d,LABDATE);
  setTime(p,d,LABTIME);
  //syncronization
  int i = reconnectSSH(&my_ssh_syncro_data);
  if(i == -1)
    console.push_back("ERROR: hubo un error intentando reconectar el tunel ssh, ejecute el script manualmente");
  else if (i>=0)
    console.push_back("INFO: reconexión del tunel ssh para la base de datos central, efectuada");
  return 0;
}

static int slotButtonEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonPressedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotButtonReleasedEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
     if(id == BUT1) //salvar
    {
      std::cout << "form save" << std::endl;
      switch(formDI->retForm())
	{
	case(1): //unloading
	  if(formEntrada)
	    delete formEntrada;
	  formEntrada = new inputForm();
	  formEntrada->copyFrom(formDI);
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	case(2)://loading
	  if(formSalida)
	    delete formSalida;
	  formSalida = new outputForm();	  
	  formSalida->copyFrom(formDI);
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask5(p);
	  break;
	default://unknown
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	}
    }
    else if(id == BUT2) //CANCEL
    {
      std::cout << "form reset" << std::endl;
      switch(formDI->retForm())
	{
	case(1):
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	case(2):
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask5(p);
	  break;
	default:
	  if(formDI)
	    delete formDI;
	  formDI = NULL;
	  show_mask4(p);
	  break;
	}
    }
  else if(id == BUT1234)
    show_mask6(p);
  else if(id == BUT5)
    show_mask7(p);    
  else if(id == BUT6)
    show_mask8(p);    
  else if(id == BUT78)
    show_mask9(p);
  else if(id == BUT910)
    show_mask10(p);
  return 0;
}

static int slotTextEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;


  std::string myString = text;
  if(id == EDITNOMBRE_A)
    formDI->setDepPCosName(myString);
  else if(id == EDITNIF_A)
    formDI->setDepPCosNif(myString);
  else if(id == EDITDIREC_A)
    formDI->setDepPCosAddr(myString);
  else if(id == EDITCP_A)
 	  try             			
	    {
	     formDI->setDepPCosZip(std::stol(myString));
	    }
	  catch(...)
	    {
	      formDI->setDepPCosZip(0);
	    }
  else if(id == EDITMUNI_A)
    formDI->setDepPCosCity(myString);
  else if(id == EDITPRO_A)
    formDI->setDepPCosProv(myString);
  else if(id == EDITCA_A)
    formDI->setDepPCosReg(myString);
  else if(id == EDITNIMA_A)
 	  try             			
	    {
	     formDI->setDepPCosNima(std::stol(myString));
	    }
	  catch(...)
	    {
	      formDI->setDepPCosNima(0);
	    }
  else if(id == EDITREG_A)
 	  try             			
	    {
	     formDI->setDepPCosNumIns(std::stol(myString));
	    }
	  catch(...)
	    {
	      formDI->setDepPCosNumIns(0);
	    }
  //else if(id == EDITCNAE_A)
    //formDI->setDepPCosXXXXXXXX(myString);


  /* TODO RODRIGO A RELLENAR, EDICIÓN DE UN CLIENTE PARTICULAR
  else if ( id ==
  */
      
  return 0;
}

static int slotSliderEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotCheckboxEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotRadioButtonEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}

static int slotGlInitializeEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlPaintEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotGlResizeEvent(PARAM *p, int id, DATA *d, int width, int height)
{
  if(p == NULL || id == 0 || d == NULL || width < 0 || height < 0) return -1;
  return 0;
}

static int slotGlIdleEvent(PARAM *p, int id, DATA *d)
{
  if(p == NULL || id == 0 || d == NULL) return -1;
  return 0;
}

static int slotTabEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotTableTextEvent(PARAM *p, int id, DATA *d, int x, int y, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || text == NULL) return -1;
  return 0;
}

static int slotTableClickedEvent(PARAM *p, int id, DATA *d, int x, int y, int button)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000 || button < 0) return -1;
  return 0;
}

static int slotSelectionEvent(PARAM *p, int id, DATA *d, int val, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || text == NULL) return -1;
  return 0;
}

static int slotClipboardEvent(PARAM *p, int id, DATA *d, int val)
{
  if(p == NULL || id == -1 || d == NULL || val < -1000) return -1;
  return 0;
}

static int slotRightMouseEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  //pvPopupMenu(p,-1,"Menu1,Menu2,,Menu3");
  return 0;
}

static int slotKeyboardEvent(PARAM *p, int id, DATA *d, int val, int modifier)
{
  if(p == NULL || id == 0 || d == NULL || val < -1000 || modifier < -1000) return -1;
  return 0;
}

static int slotMouseMovedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMousePressedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseReleasedEvent(PARAM *p, int id, DATA *d, float x, float y)
{
  if(p == NULL || id == 0 || d == NULL || x < -1000 || y < -1000) return -1;
  return 0;
}

static int slotMouseOverEvent(PARAM *p, int id, DATA *d, int enter)
{
  if(p == NULL || id == 0 || d == NULL || enter < -1000) return -1;
  return 0;
}

static int slotUserEvent(PARAM *p, int id, DATA *d, const char *text)
{
  if(p == NULL || id == 0 || d == NULL || text == NULL) return -1;
  return 0;
}
