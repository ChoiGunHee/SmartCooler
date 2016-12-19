float temperate;

void setup()
{
  Serial.begin(9600);
  
}

void loop()
{
  if(Serial.available())
  {
    temperate = Serial.parseFloat();
    
    Serial.print(temperate);
    Serial.println();
  }
  /*
  char temp[100];
  if(Serial.available())
  {
    byte leng = Serial.readBytes(temp, 20);
    
    for(int i=0; i < leng; i++)
    {
      Serial.print(temp[i]);
    }
    Serial.println();
  }
  */
}
