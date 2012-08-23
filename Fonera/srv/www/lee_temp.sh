#!/bin/ash
while true	# loop forever
do
   READ=`dd if=/dev/ttyS0 count=1`
   DATE=`date -Iseconds`
   echo "$READ,$DATE"|tr -d '\r' >> /srv/www/log
done 
exit 0
