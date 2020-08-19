#!/bin/bash

# setup variables


echo [NextEngine Build] ndk-build begin.

cp NDKbuild.log NDKbuild_backup.log
cat NDKbuild_backup.log | while read line
do
echo $line
done
rm NDKbuild_backup.log

error_str="error:"
grep "$error_str" NDKbuild.log
if [ $? -ne 0 ]; then
	echo "not find error"
else
	echo "[NextEngine Build] ndk-build find error, exit!"
	exit 5
fi
	
echo [NextEngine Build] ndk-build end.

exit 0
