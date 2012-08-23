#!/bin/ash  

echo "Content-type: text/html"
echo ""

DATE=`date -Iseconds`
echo "<html>"
echo "<head>"
echo "<title>AC remote control $DATE</title>"
echo "</head>"
echo "<body>"
echo "<h1>AC</h1>"
echo "<h2>Estado actual: </h2>"
grep "\-O" /srv/www/log|tail -n1
echo "<h2>Ultima temperatura: </h2>"
grep -v "\-O" /srv/www/log|tail -n1
echo "<br>"
echo "<br>"
echo "<form action="./ac.sh" method="get">"
echo "<input type="radio" name="ac" value="on">ON<br>"
echo "<input type="radio" name="ac" value="off">OFF<br>"
echo "<input type="submit" name="subbtn" value="Aceptar">"
echo "</form>"
echo "<a href="./ver_logs.sh">Logs</h>"
echo "</body>"
echo "</html>"
