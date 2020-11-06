#!/bin/bash

var=$(tty)
error="not a tty"

if [ "$var" = "$error" ]; then
    cd /home/root93/Repo/C++/CAN\ Master/qt/CanMaster/bash/
    gnome-terminal --command "./setvcan0.sh"
else
    function check_eth {
        typeset output
        output=$(ip link show "$1" up) && [[ -n $output ]]
    }

    function set_eth {
        sudo -S modprobe vcan
        sudo -S ip link add vcan0 type vcan
        sudo -S ip link set up vcan0
    }

    echo "Start setvcan0 script."

    if check_eth vcan0; then
        echo "vcan0 is up"
    else
        echo "vcan0 interface configuration necessary"
        set_eth
    fi

    clear

    #sudo kill 10
fi