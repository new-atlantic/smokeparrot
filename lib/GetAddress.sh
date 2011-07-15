#!/bin/sh
# Get the MAC address of this Smokeparrot instance

DEVICE="br-lan"
# Todo: This is hardwired. Should be replaced by a script to recognize the type of connection smokeparrot utilizes.

/sbin/ifconfig $DEVICE | /usr/bin/awk '/inet/ {print $2}' | /usr/bin/awk '{FS=":"}{ print $2 }'