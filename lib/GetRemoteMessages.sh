#!/bin/sh
# Gets the messages from all neighbours.

PREFIX="/smokeparrot"
MESSAGE_STORE="$PREFIX/messages/"

FUNCTIONS="$PREFIX/lib"

NEIGHBOURS="" # TODO: function/file to generate neighbour IP-addresses

for ADDRESS in $NEIGHBOURS; do
  $FUNCTIONS/TransferMessages.sh "$ADDRESS"
  #$FUNCTIONS/CollectMessages.sh
  $FUNCTIONS/ProcessReceivedMessages.sh
done
