# chin.sh (chardev insert)
# this will get the system ready to use the chardev.

#!/bin/bash

# Check if module is loaded.
modinfo chardev.ko # Returns "1" if it can't find the module

if [ $? ]
then
    printf "ERROR - The module was already loaded.\n"
    exit -1
fi

# Check if device file is already there.
if [ -c /dev/chardev ]
then
    printf "ERROR - /dev/chardev already exists.\n"
    exit -1
fi

# Insert Module and make sure it took.
insmod ./chardev.ko

if [ $? ]
then
    printf "ERROR - Unable to insert the module.\n"
    return -1
fi

# Create device file.
major=$(awk "\$2==\"$module\" {print \$1}" /proc/devices) # Find major number of inserted module. Special thanks to LDDR.

mknod /dev/chardev char $major 0

if [ $? ]
then
    printf "ERROR - Unable to create the device file.\n"
    return -1
fi


