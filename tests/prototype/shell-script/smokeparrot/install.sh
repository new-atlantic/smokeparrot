#!/bin/sh
# Script to create the smokeparrot directory structure on the a remote device.
# TODO: creating a smokeparrot-user, copying the img, css & js, transfering ssh-keys and more.

TARGET_DEVICE="$1"

/usr/bin/ssh root@$TARGET_DEVICE 'mkdir /smokeparrot'
/usr/bin/ssh root@$TARGET_DEVICE 'mkdir /smokeparrot/messages /smokeparrot/queue'
/usr/bin/scp -r cgi/ "root@$TARGET_DEVICE:/smokeparrot/"
/usr/bin/scp -r lib/ "root@$TARGET_DEVICE:/smokeparrot/"
/usr/bin/scp -r html/ "root@$TARGET_DEVICE:/smokeparrot/"
/usr/bin/scp settings "root@$TARGET_DEVICE:/smokeparrot/"

/usr/bin/ssh root@$TARGET_DEVICE 'ln -s /smokeparrot/cgi/smokeparrot.cgi /www/cgi-bin/smokeparrot.cgi'
