#!/bin/bash

#This file is part of PiResiduos.
#
#Copyright 2017-2018, Prointegra SL.
#
#PiResiduos is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
#the Free Software Foundation, either version 3 of the License, or
#(at your option) any later version.
#
#PiResiduos is distributed in the hope that it will 
#be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with PiResiduos.  
#If not, see <https://www.gnu.org/licenses/>.

SCRIPT=$(readlink -f $0)
SCRIPT_PATH=`dirname $SCRIPT`
##ssh tunnel
## EDIT IT!
#ssh-add extras/my_ssh_key
#myPID=$(ps -ef | grep "3307:localhost:3306 user@remote_host -N" | awk '{print $2}' | head -1)
#kill $myPID
#ssh -f -L 3307:localhost:3306 user@remote_host -N
############
##libraries
export LD_LIBRARY_PATH=$SCRIPT_PATH/lib:$LD_LIBRARY_PATH
##
##server
##gdb ./piResiduos
./piResiduos &
sleep 1
pvbrowser
##
