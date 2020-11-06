#!/bin/bash

var=$(tty)
base="not a tty"
#echo $var > text.txt

if [ "$var" = "$base" ]; then
    gnome-terminal
else
    echo $var
fi