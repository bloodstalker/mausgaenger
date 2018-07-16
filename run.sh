#!/usr/bin/bash
if [[ "$1" == proc ]];then
  cat /proc/bus/input/devices
  exit $?
fi
make
sudo ./mausgaenger --event-id 6 --out ./out --outb ./outb
