#!/bin/ash  
FILE=/srv/www/log

if [ ! -f $FILE ]
then
	echo "log file not found $FILE"
	exit 1
fi
timestamp=`date +%Y%m%d`
newlogfile=$FILE.$timestamp
cp $FILE $newlogfile
cat /dev/null > $FILE
gzip -f -9 $newlogfile
exit 0
