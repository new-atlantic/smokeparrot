#!/bin/sh
# Initialize Smokeparrot.

# Create the folder structure for Smokeparrot and the smokeparrot user.
SMOKEPARROT_PATH="/home/smokeparrot/"
mkdir $SMOKEPARROT_PATH

# Create the smokeparrot user.
echo "smokeparrot:x:2020:" >> /etc/group
echo "smokeparrot:*:2020:2020:Smokeparrot:/home/smokeparrot:/bin/ash" >> /etc/passwd

# Make smokeparrot the owner of smokeparrot.
chown -R smokeparrot:smokeparrot $SMOKEPARROT_PATH

# Remove the test messages.
rm $SMOKEPARROT_PATH/messages/*

# Create a symlink to the smokeparrot cgi-script.
ln -s $SMOKEPARROT_PATH/cgi-bin/smokeparrot.cgi /www/cgi-bin/smokeparrot.cgi

# Install haserl, the cgi-environment.
opkg update
opkg install haserl

# Move the js, css and images to their proper location.
mv $SMOKEPARROT_PATH/media/* /www/

# Clean up
rm -r $SMOKEPARROT_PATH/.git*
rm -r $SMOKEPARROT_PATH/queue/.gitignore
