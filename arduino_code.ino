#include <LiquidCrystal.h>

LiquidCrystal lcd1(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd2(10, 9, 7,6,1,0);
// Define pins and values for voltage measurement
const int voltPin0=A0;  
const int voltPin1=A1;  
const float threshold=0.01;
const float C2 = 1e-6; 
const float R3 = 100;   
const float C4 = 1e-6;  
const float R1 = 1000;   
float Rx=0;           
float Cx=0;           

void setup() {
 
  lcd1.begin(16, 2);  
  lcd1.print("Schering Bridge");
  lcd2.begin(16, 2);  
  lcd2.print("Schering Bridge");
  pinMode(voltPin0, INPUT);
  pinMode(voltPin1, INPUT);
  delay(1000); 
}

void loop() {
  // Read the voltage from the bridge and scale it to actual voltage
  float voltage0 = analogRead(voltPin0) * (5.0/1023.0);
  float voltage1 = analogRead(voltPin1) * (5.0 /1023.0);

  // Check if the bridge is balanced (voltage difference near zero)
  if (abs(voltage0 - voltage1) <= threshold) {
    Rx = R3*(C4/C2);
    Cx = C2*(R1/R3);
    float D = (2*3.14159*1000)*Cx*Rx;
    float Q= 1/D;
    float Rx = (C4/C2)*R3;
    // Display the results on the LCD
    lcd1.clear();
    lcd1.setCursor(0,0);  
    lcd1.print("Rx: ");
    lcd1.print(Rx,0);  
    lcd1.setCursor(0,1);  
    lcd1.print("Cx: ");
    lcd1.print(Cx,6);     
  
    lcd2.clear();
    lcd2.setCursor(0,0);  
    lcd2.print("Q: ");
    lcd2.print(Q,6);  
    lcd2.setCursor(0,1);  
    lcd2.print("D: ");
    lcd2.print(D,4);  
    delay(500);
  } else {
    lcd1.clear();
    lcd1.setCursor(0,0); 
    lcd1.print("Schering Bridge");
    lcd1.setCursor(0,1);  
    lcd1.print("is NOT Balanced"); 
     
    lcd2.clear();
    lcd2.setCursor(0,0); 
    lcd2.print("Voltage Diff:");
    lcd2.setCursor(0,1);  
    lcd2.print(abs(voltage0-voltage1), 3); 
    delay(500); 
  }
}
