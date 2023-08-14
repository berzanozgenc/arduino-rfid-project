#include <SPI.h>                          
#include <MFRC522.h>                      
int red_light_pin= 3;
int green_light_pin = 4;
int blue_light_pin = 5;
int RST_PIN = 9;                          
int SS_PIN = 10;                          
MFRC522 rfid(SS_PIN, RST_PIN);            
int i=0;
int j=1;
int password[4]={1,2,3,4};                
int passwordUser[4]={0,0,0,0};            
int count=0;

void setup() { 
 
  Serial.begin(9600);                     
  SPI.begin();                            
  rfid.PCD_Init();                        
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  Serial.begin(9600);     
  pinMode(8,INPUT);                       
  pinMode(2,INPUT);
  pinMode(6,INPUT);
  pinMode(7,INPUT);
  pinMode(1,INPUT);                       
  
}

void loop() {

 RGB_color(255, 0, 0); // RED COLOR
 

  if(digitalRead(8)){
      Serial.println("Girdi 1");
      passwordUser[i]=1;
      i++;
      delay(500);
      j++;
    }
    if(digitalRead(2)){
      Serial.println("Girdi 2");
      passwordUser[i]=2;
      i++;
      delay(500);
      j++;
    }
    if(digitalRead(6)){
      Serial.println("Girdi 3");
      passwordUser[i]=3;
      i++;
      delay(500);
      j++;
    }
    if(digitalRead(7)){
      Serial.println("Girdi 4");
      passwordUser[i]=4;
      i++;
      delay(500); 
      j++;
    }
                                     
  
    if(j==5){
    {
            
      if(password[0] == passwordUser[0] && password[1] == passwordUser[1] && password[2] == passwordUser[2] && password[3] == passwordUser[3]){
        RGB_color(0, 255, 0);         
        delay(5000);
        digitalWrite(1,HIGH);        
        delay(2000);
        digitalWrite(1,LOW);
        count=0;
                                     
      }
      else{
        RGB_color(0,255,100); 
        delay(1000);
        digitalWrite(1,HIGH);            
        delay(1000);
        digitalWrite(1,LOW);
        digitalWrite(1,HIGH);            
        delay(1000);
        digitalWrite(1,LOW);
        count++;
      }
      i=0;
      j=1;

      if (count== 3){
       RGB_color(255, 0, 255);        
       delay(15000);
      }
      
    }
    
}

int state=0; //processing ile haberleşme 
    if(Serial.available()){
          state = Serial.read();
          if(state==1){
            RGB_color(0, 255, 0);
            delay(5000);
          }
          else if(state==2){
           RGB_color(0,255,100);
           delay(1000);
          }     
          else if(state==3){
           RGB_color(255,0,255); 
           delay(15000);
          }          
    }
    

  byte ID[4] = {80, 65, 198, 27};          

  if ( ! rfid.PICC_IsNewCardPresent())    
    return;

  if ( ! rfid.PICC_ReadCardSerial())      
    return;

  if (rfid.uid.uidByte[0] == ID[0] &&     
    rfid.uid.uidByte[1] == ID[1] && 
    rfid.uid.uidByte[2] == ID[2] && 
    rfid.uid.uidByte[3] == ID[3] ) {
        Serial.println("Kapi acildi");
        ekranaYazdir();
        RGB_color(0, 0, 255);            
        delay(3000);
        digitalWrite(1,HIGH);            
        delay(2000);
        digitalWrite(1,LOW);
       
    }
    else{                                 
      Serial.println("Yetkisiz Kart");
      ekranaYazdir();
      digitalWrite(1,HIGH);            
      delay(1000);
      digitalWrite(1,LOW);
      digitalWrite(1,HIGH);            
      delay(1000);
      digitalWrite(1,LOW);
      
    }
  rfid.PICC_HaltA();

}

void ekranaYazdir(){
  Serial.print("ID Numarasi: ");
  for(int sayac = 0; sayac < 4; sayac++){ 
    Serial.print(rfid.uid.uidByte[sayac]);
    Serial.print(" ");
  }
  Serial.println("");
}


void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);

}
