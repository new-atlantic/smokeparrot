#!/bin/sh
# This script gets a list of current neighbours.

SMOKEPARROT_PATH=/home/smokeparrot
NEIGHBOUR_MAC_LIST="$(/usr/sbin/batctl originators | sed -n '3,$p' | awk '{ print $1 }')"
#DEBUG echo $NEIGHBOUR_MAC_LIST

ADDRESS_LIST=$(cat $SMOKEPARROT_PATH/neighbour.list | awk '{ print $2 }')
#DEBUG echo $ADDRESS_LIST

NEIGHBOUR_IP_LIST=""

for NEIGHBOUR_MAC_ADDRESS in $NEIGHBOUR_MAC_LIST; do
    for MAC_ADDRESS in $ADDRESS_LIST; do
	if [ "$NEIGHBOUR_MAC_ADDRESS" == "$MAC_ADDRESS" ]; then
	    NEIGHBOUR_IP_ADDRESS=$(cat $SMOKEPARROT_PATH/neighbour.list | grep $MAC_ADDRESS | awk '{ print $1 }')
	    NEIGHBOUR_IP_LIST="$NEIGHBOUR_IP_LIST $NEIGHBOUR_IP_ADDRESS"
	fi
    done
done

echo "$NEIGHBOUR_IP_LIST"