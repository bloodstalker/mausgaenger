#!bin/bash
if [[ "$1" == proc ]];then 
  cat /proc/bus/input/devices
  exit $?
fi
"./mausgaenger"

