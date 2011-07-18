#!/bin/sh
# This script gets a list of current neighbours.

SMOKEPARROT_PATH=/home/smokeparrot
NEIGHBOUR_MAC_LIST="$(/bin/cat /sys/kernel/debug/batman_adv/bat0/originators | /bin/sed -n '3,$p' | /usr/bin/awk '{$1=$2=""; print $0}' | grep -E -o '[[:xdigit:]]{2}(:[[:xdigit:]]{2}){5}' | /usr/bin/sort | /usr/bin/uniq)"

ADDRESS_LIST=$(cat $SMOKEPARROT_PATH/neighbour.list | /usr/bin/awk '{ print $2 }')

NEIGHBOUR_IP_LIST=""

for NEIGHBOUR_MAC_ADDRESS in $NEIGHBOUR_MAC_LIST; do
    for MAC_ADDRESS in $ADDRESS_LIST; do
	if [ "$NEIGHBOUR_MAC_ADDRESS" == "$MAC_ADDRESS" ]; then
	    NEIGHBOUR_IP_ADDRESS=$(cat $SMOKEPARROT_PATH/neighbour.list | grep $MAC_ADDRESS | /usr/bin/awk '{ print $1 }')
	    NEIGHBOUR_IP_LIST="$NEIGHBOUR_IP_LIST $NEIGHBOUR_IP_ADDRESS"
	fi
    done
done

echo "$NEIGHBOUR_IP_LIST"