// Receiver Code
#include <SoftwareSerial.h>
 
// Define the pins for the MAX485
#define DE 3
#define RE 2
 
// Create a SoftwareSerial object to communicate with the MAX485
SoftwareSerial RS485Serial(6, 7); // RX, TX

// Nivel del tanque de agua
float nivel;
float voltajeSalida;
 
void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  RS485Serial.begin(9600);
  Serial.println("Programa de receptor - Iniciada");
 
  // Set the DE and RE pins as outputs
  pinMode(DE, OUTPUT);
  pinMode(RE, OUTPUT);
 
  // Set DE and RE low to enable receiving mode
  digitalWrite(DE, LOW);
  digitalWrite(RE, LOW);
}
 
void loop() {
  if (RS485Serial.available() >= sizeof(float)) {
    
    float frecuenciaPromedio = 0;
    RS485Serial.readBytes((byte*)&frecuenciaPromedio, sizeof(float));
 
    // Print the received data to the serial monitor
    // Serial.print("Frecuencia del oscilador: ");
    Serial.println(frecuenciaPromedio);

    // Convertir la frecuencia a nivel - voltaje
    nivel = 8*(frecuenciaPromedio - 38655.275)/(14.706818);
    Serial.print("El nivel es: ");
    Serial.println(nivel);

    // Salida en voltaje a nivel industrial
    voltajeSalida = 5*nivel/8;
    Serial.print("El voltaje industrial:");
    Serial.println(voltajeSalida);

  }
}