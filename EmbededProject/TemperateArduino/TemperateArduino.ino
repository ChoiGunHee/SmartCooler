#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

int interrupPin = 8;
float temperate;
float currentTemperate;

void setup()
{
  Serial.begin(9600);

  Serial.println("Serial setUp!");  
  
  pinMode(interrupPin, OUTPUT);
  
  temperate = -1;
  mlx.begin();
}

void loop()
{
  if(Serial.available())
  {
    temperate = Serial.parseFloat();
    
    Serial.print(temperate);
    Serial.println();
  }
  
  currentTemperate = mlx.readObjectTempC();
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); Serial.println("*C");
  Serial.print("Object = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  
  if(temperate > currentTemperate)
  {
    temperate = -1;
    digitalWrite(interrupPin, HIGH);
    Serial.println("complement");
    temperate = -1;
  }
  else
  {
    digitalWrite(interrupPin, LOW);
    Serial.println("not complement");
  }
  
  delay(500);
}
