arduino-fonera-plug
===================

El proposito de este proyecto es poder encender y apagar un enchufe estándar (220V) vía internet utilizando una página web para ello. Además, cada X segundos (x=60), se monitorizará la temperatura actual.
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
La configuración de lighttpd incluye la activación del modulo mod_cgi para poder ejecutar los scripts sh (la fonera tiene hardware muy limitado, y con sh es más que suficiente), y mod_auth para proteger el acceso vía usuario/password (ambos módulos instalables vía opkg).
El puerto serie de la fonera con OpenWRT por defecto no funcionaba bien, con lo cual hay que utilizar stty para configurar el mismo. El problema, es que al ser tan limitado el hardware, no había espacio suficiente para instalar el paquete "coreutils", por lo tanto, tuve que descargar el paquete, descomprimirlo y copiar el ejecutable stty a /usr/bin (incluido por comodidad).
La configuración del puerto serie se realiza con el siguiente comando:
{{{
}}}
El cual he incluido en el fichero /etc/rc.local (chapuza, pero resolutivo!), junto con ntpdate (instalable vía opkg) para sincronizar el tiempo.
La zona horaria por defecto no viene configurada, con lo cual es necesario configurarla en el fichero <NOMEACUERDO>
La lectura de la temperatura se relaliza con el script "leer_temp.sh", que se ejecuta en segundo plano desde el rc.local.

<...>