#define AC 12
#define INTERRUPTOR 7

int byte_received;
float tempC;
int tempPin = 0;
int segundos = 0;
char status='f';

void setup(){

  Serial.begin(9600);
  pinMode(AC, OUTPUT);
  pinMode(INTERRUPTOR,INPUT);
  digitalWrite(AC,LOW);
}

void loop(){
  if(segundos == 59){
    tempC = analogRead(tempPin);           //read the value from the sensor
    tempC = (5.0 * tempC * 100.0)/1024.0;  //convert the analog data to temperature
    Serial.println(tempC);             //send the data to the computer
    segundos=0;
  }
  else
  {
    segundos++;
  }

  if(digitalRead(INTERRUPTOR) && (status == 'f'))
  {
    digitalWrite(AC,HIGH);
    Serial.println("I-ON");
    status='n';
  }
  if(!digitalRead(INTERRUPTOR) && (status == 'n'))
  {
    digitalWrite(AC,LOW);
    Serial.println("I-OFF");
    status='f';
  }

  if(!digitalRead(INTERRUPTOR) && (status == 'f'))
  {
    if(Serial.available()> 0)
    {
      byte_received= Serial.read();
      if(byte_received == 'N')
      {
        digitalWrite(AC,HIGH);
        Serial.println("W-ON");
      }
      if(byte_received == 'F')
      {
        digitalWrite(AC,LOW);
        Serial.println("W-OFF");
      }
    }
  }
  else
  {
    while (Serial.read() >= 0)
      ;
  }
  delay(1000);
}



