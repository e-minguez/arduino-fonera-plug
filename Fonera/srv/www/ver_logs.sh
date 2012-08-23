#!/bin/ash  

echo "Content-type: text/html"
echo ""

echo "<html><head><title>Logs</title></head>"
echo "<body>Log:"
echo "<br>"
while read line; do
	echo "${line}"
	echo "<br>"
done < ./log
echo "<a href="./"><- Volver</a>"
echo "</body></html>"
