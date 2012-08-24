#define AC 12
#define INTERRUPTOR 7

int byte_received;
float tempC;
int tempPin = 0;
int segundos = 0;
char status='f';

void setup(){
  // Configuracion del serial para coincidir con la fonera
  Serial.begin(9600);
  // AC = salida
  pinMode(AC, OUTPUT);
  // Interruptor = entrada
  pinMode(INTERRUPTOR,INPUT);
  // El AC arranca apagado
  digitalWrite(AC,LOW);
}

void loop(){
  // Solamente escribe la temperatura cada 59 segundos + el delay = 1 min
  if(segundos == 59){
    // lee el valor del sensor
    tempC = analogRead(tempPin);
    // convierte el valor leido en grados C
    tempC = (5.0 * tempC * 100.0)/1024.0;
    // envia la temperatura por el puerto serie conectado a la fonera
    Serial.println(tempC);
    segundos=0;
  }
  else
  {
    segundos++;
  }
  
  // El interruptor tiene prioridad sobre la web

  // Si el interruptor se pulsa, da igual como esté en la web
  if(digitalRead(INTERRUPTOR) && (status == 'f'))
  {
    digitalWrite(AC,HIGH);
    // Escribe I-ON para distinguir si ha sido desde web o desde el interruptor
    Serial.println("I-ON");
    status='n';
  }
  if(!digitalRead(INTERRUPTOR) && (status == 'n'))
  {
    digitalWrite(AC,LOW);
    Serial.println("I-OFF");
    status='f';
  }

  // Si no esta pulsado el interruptor
  if(!digitalRead(INTERRUPTOR) && (status == 'f'))
  {
    // Comprobar el puerto serie
    if(Serial.available()> 0)
    {
      // En caso de que haya datos, leerlos
      byte_received= Serial.read();
      if(byte_received == 'N')
      {
        // Si es "N", encender el AC y escribir W-ON por el serial
        digitalWrite(AC,HIGH);
        Serial.println("W-ON");
      }
      if(byte_received == 'F')
      {
        // Si es "F", apagar el AC y escribir W-OFF por el serial
        digitalWrite(AC,LOW);
        Serial.println("W-OFF");
      }
    }
  }
  else
  {
    // Limpieza de buffer
    while (Serial.read() >= 0)
      ;
  }
  // Esperar 1 segundo
  delay(1000);
}



