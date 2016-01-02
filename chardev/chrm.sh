# chrm.sh (chardev remove)

#!/bin/bash

# Set some variables
mod=chardev.ko
modname=chardev
devpath=/dev/"$modname"

# Delete the device file.

if [ -e "$devpath"  ]
then
	printf "INFO - Deleting device file: %s\n" "$devpath"
	rm -f "$devpath"
else
	printf "INFO - No device file to delete. \n"
fi

# Remove the module.

rmmod "$mod"

if [ "$?" -ne 0 ]
then
	printf "ERROR - Unable to remove the module: %s\n" "$mod"
	exit -1
fi
