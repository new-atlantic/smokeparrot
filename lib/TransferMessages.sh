#!/bin/sh
# Transfers messages from other Smokeparrot nodes into the queue.

PREFIX="/smokeparrot"
MESSAGE_STORE="$PREFIX/messages/"

MESSAGE_QUEUE="$PREFIX/queue/"

USERNAME="root"
REMOTE_HOST="$1"

# Transfer the messages from the remote hosts message store to the local queue.
# TODO: Test with private keys. Check settings.
/usr/bin/scp -r "$USERNAME@$REMOTE_HOST:$MESSAGE_STORE/*" "$MESSAGE_QUEUE" 
