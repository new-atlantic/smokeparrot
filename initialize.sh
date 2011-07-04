#!/bin/sh
# Initialize Smokeparrot.

source lib/env.sh

rm "$PREFIX/messages/*"
mkdir "$PREFIX/queue"
ln -s "$PREFIX/cgi-bin/smokeparrot.cgi" "/www/cgi-bin/smokeparrot.cgi"
