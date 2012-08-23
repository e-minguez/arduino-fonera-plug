#!/bin/ash  

echo "Content-type: text/html"
echo ""

DATE=`date -Iseconds`
WHATTODO=`echo "$QUERY_STRING" | sed -n 's/^.*ac=\([^&]*\).*$/\1/p' | sed "s/%20/ /g"`
echo "<html><head><title>What You Said</title></head>"
echo "<body>Has pulsado $WHATTODO"
echo "<br>"
echo "<a href="./"><- Volver</a>"
echo "</body></html>"
if [ "$WHATTODO" == "on" ]
then
	echo "N" > /dev/ttyS0
else
	echo "F" > /dev/ttyS0
fi
exit 0
