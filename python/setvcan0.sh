#!/bin/bash
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
    echo "vcan0 is up"
else
    echo "vcan0 interface configuration necessary"
    set_eth
fi