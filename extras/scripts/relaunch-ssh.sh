#!bin/bash

##ssh tunnel
myPID=$(ps -ef | grep "ssh -f -L 3307:localhost:3306 user@remote_host -N" | awk '{print $2}' | head -1)
kill $myPID
ssh -f -L 3307:localhost:3306 user@remote_host -N
##


