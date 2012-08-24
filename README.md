arduino-fonera-plug
===================

El propósito de este proyecto es poder encender y apagar un enchufe estándar (220V) vía internet utilizando una página web para ello. Además, cada X segundos (x=60), se monitorizará la temperatura actual.

En el caso de no querer utilizar la web, se utilizará un interruptor pulsador para accionarlo.

Todos los accionamientos, así como las temperaturas, serán registradas en ficheros de texto separados con comas (formato csv) para poder ser tratados en un futuro y sacar gráficas de los mismos.

Los materiales utilizados son:
- Fonera 2200
- Arduino UNO
- Sensor de temperatura (LM35)
- Transistor BD135
- Diodo 1N4007
- Interruptor pulsador
- Cableado
- Paciencia :)

FONERA
------
La fonera se ha flasheado con OpenWRT 8.09.2 e instalado lighttpd (vía opkg) para servir las páginas necesarias para el funcionamiento:
- index.html
- temperaturas.sh
- ac.sh
- estados.sh

Configuraciones
---------------
El puerto serie de la fonera con OpenWRT por defecto no se que valores utiliza, con lo cual hay que utilizar stty para configurar el mismo.

El problema, es que al ser tan limitado el hardware, no había espacio suficiente para instalar el paquete "coreutils", por lo tanto, tuve que descargar el paquete, descomprimirlo y copiar el ejecutable stty a /usr/bin (incluido por comodidad).

La configuración del puerto serie se realiza con el siguiente comando:
``
stty -F /dev/ttyS0 cs8 9600 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke noflsh -ixon -crtscts
`
El cual he incluido en el fichero /etc/rc.local (chapuza, pero resolutivo!), junto con ntpdate (instalable vía opkg) para sincronizar el tiempo.

La configuración de lighttpd incluye la activación de los modulos:
* mod_cgi - para poder ejecutar los scripts sh (la fonera tiene hardware muy limitado, y con sh es más que suficiente)
* mod_auth - para proteger el acceso vía usuario/password (ambos módulos instalables vía opkg).
Además, como openwrt incluye un servidor web embebido que escucha por el puerto 80 por defecto, se ha modificado la configuración de lighttpd para que escuche en el puerto 81.

La zona horaria por defecto no viene configurada, con lo cual es necesario configurarla en el fichero /etc/config/system

Por defecto, openwrt tiene cerrado el puerto de ssh para la interfaz de wan, pero en este caso, la interfaz de wan es la wireless, con lo cual se ha tenido que abrir el ssh para poder administrar la fonera, puesto que la tarjeta de red (interfaz lan) no se usa (/etc/firewall.user)

Además, en el fichero /etc/config/firewall se ha abierto el puerto 81 (donde escucha lighttpd), redireccionandolo al 80.

La lectura de la temperatura se realiza con el script "lee_temp.sh", que se ejecuta en segundo plano desde el /etc/rc.local, que guarda lo que llega del puerto serie (tanto la temperatura, como el estado del interruptor o la activación vía web), y la fecha en modo csv (la idea es poder procesarlo luego y sacar gráficas) en /srv/www/log

El fichero /srv/www/rotar_logs.sh es un "logrotate" chapucero :)

Web
---
La web utiliza scripts "ash" (ocupa menos que bash), para hacer la web dinámica sin tener que utilizar php/perl/...

El index muestra el último estado del aire acondicionado, y la última temperatura recogida, así como la posibilidad de encender o apagar el aire acondicionado, y un visor del log.

To do
-----
- Procesar los logs y sacar gráficas con ellos
- Hacer "paginables" los logs
- Añadir un display que indique el estado del AC y la temperatura actual
- Añadir un led que cambie de color dependiendo de la temperatura
- Reducir el tamaño (pcb?)
- ¿Alguna cosa más? ;)
