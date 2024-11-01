#include <DHT.h>
#include <SPI.h>
#include <LoRa.h>

#define DHTPIN 4        
#define DHTTYPE DHT22   
#define LORA_SS 5       
#define LORA_RST 14     
#define LORA_DIO0 2     

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  while (!Serial);


  dht.begin();

  // Initializing the LoRa module
  LoRa.begin(915E6); 
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  Serial.println("LoRa initialized");
}

void loop() {

  delay(2000);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if the reading failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT22!");
    return;
  }

  // Display the values on the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");


  LoRa.beginPacket();
  LoRa.print("Humidity: ");
  LoRa.print(humidity);
  LoRa.print(" %");
  LoRa.print(", Temperature: ");
  LoRa.print(temperature);
  LoRa.print(" *C");
  LoRa.endPacket();

  Serial.println("Data sent via LoRa");
}
