#!/bin/sh
# Get the MAC address of this Smokeparrot instance

DEVICE="eth0"
# Todo: This is hardwired. Should be replaced by a script to recognize the type of connection smokeparrot utilizes.

/sbin/ifconfig $DEVICE | /usr/bin/awk '/HWaddr/ {print $5}'
