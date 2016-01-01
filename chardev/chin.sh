# chin.sh (chardev insert)
# this will get the system ready to use the chardev.

#!/bin/bash

# Set some variables

modname=chardev

# Check if device file is already there.
if [ -c /dev/chardev ]
then
    printf "ERROR - /dev/chardev already exists.\n"
    exit -1
fi

# Insert Module and make sure it took.
insmod chardev.ko

if [ "$?" != 0 ]
then
    printf "ERROR - Unable to insert the module.\n"
    exit -1
fi

# Create device file.
major=$(awk "\$2==\"$modname\" {print \$1}" /proc/devices) # Find major number of inserted module. Special thanks to LDDR.

mknod /dev/chardev char "$major" 0

if [ "$?" != 0 ]
then
    printf "ERROR - Unable to create the device file.\n"
    rmmod chardev.ko
    exit -1
fi
