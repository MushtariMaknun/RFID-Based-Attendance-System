#include <SPI.h>
#include <MFRC522.h>
//#include <LiquidCrystal.h>// include the library code:

//LiquidCrystal lcd(2);  //(or the latch pin of the 74HC595)

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte card_ID[4]; //card UID size 4byte
byte Name1[4]={0x99,0x35,0x72,0xA9};//first UID card
byte Name2[4]={0x8B,0x25,0x8F,0xB9};//second UID card
byte Name3[4]={0x60,0x4B,0xF6,0xA7};//THIRD UID card 
byte Name4[4]={0x4A,0x1F,0xC8,0x49};//Fourth UID card 
byte Name5[4]={0x70,0xAB,0xF9,0xA7};//Fifth UID card 
byte Name6[4]={0xAA,0x88,0x56,0xBC};//Sixth UID card 

int NumbCard[6];//the number of cards. in my case i have just two cards.
int j=0;  
int statu[6];//the number of cards. in my case i have just two cards.
int s=0;        

int const RedLed=6;
int const GreenLed=5;
int const Buzzer=8;

String Log;
String Name;//user name
long Number;//user number
int n ;//The number of card you want to detect (optional)  
int ID=1;
void setup() {
  //lcd.begin(16, 2);
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,ID,Date,Name,Number,Time IN,Time OUT");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)

  pinMode(RedLed,OUTPUT);
  pinMode(GreenLed,OUTPUT);
  pinMode(Buzzer,OUTPUT);
  
  //lcd.setCursor(2,0);
  //lcd.print("Good Morning");//Wlecome Message will appear in the beginning. 
  delay(200);
   }
   
void loop() {
  //look for new card
   if ( ! mfrc522.PICC_IsNewCardPresent()) {
  return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }

 for (byte i = 0; i < mfrc522.uid.size; i++) {
     card_ID[i]=mfrc522.uid.uidByte[i];

       if(card_ID[i]==Name1[i]){
       Name="First Employee";//user name
       Number=123456;//user number
       j=0;
       s=0;
      }
      else if(card_ID[i]==Name2[i]){
       Name="Second Employee";//user name
       Number=789101;//user number
       j=1;
       s=1;
      }
      else if(card_ID[i]==Name3[i]){
       Name="third Employee";//user name
       Number=789101;//user number
       j=2;
       s=2;
      }
      else if(card_ID[i]==Name4[i]){
       Name="fourth Employee";//user name
       Number=789101;//user number
       j=3;
       s=3;
      }
      else if(card_ID[i]==Name5[i]){
       Name="Fifth Employee";//user name
       Number=789101;//user number
       j=4;
       s=4;
      }
      else if(card_ID[i]==Name6[i]){
       Name="Sixth Employee";//user name
       Number=789101;//user number
       j=5;
       s=5;
      }
      else{
          digitalWrite(GreenLed,LOW);
          digitalWrite(RedLed,HIGH);
          goto cont;//go directly to line 142
     }
}
      if(NumbCard[j] == 1 && statu[s] == 0){
      statu[s]=1;
     // lcd.clear();
     // lcd.setCursor(0,0);
     // lcd.print("Good Bye");
     // lcd.setCursor(0,1);
     // lcd.print(Name);
      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.print(",");
      Serial.print("");
      Serial.print(",");
      Serial.println("TIME");
      ID=ID+1;
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      }
      else if(NumbCard[j] == 0){
      NumbCard[j] = 1;
      
      n++;//(optional)
     // lcd.clear();
     // lcd.setCursor(4,0);
     // lcd.print("Welcome ");
     // lcd.setCursor(0,1);
     // lcd.print(Name);
      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.print(",");
      Serial.print("TIME");
      Serial.print(",");
      Serial.println("");
      digitalWrite(GreenLed,HIGH);
      digitalWrite(RedLed,LOW);
      digitalWrite(Buzzer,HIGH);
      delay(30);
      digitalWrite(Buzzer,LOW);
      ID=ID+1;
      }
      else if(statu[s] == 1){
     //lcd.clear();
     //lcd.setCursor(0,0);
     //lcd.print(Name);
     //lcd.setCursor(0,1);
     //lcd.print("Already Left");
      }
      delay(1000);
      //lcd.clear();
      //lcd.setCursor(2,0);
      //lcd.print("Good Morning");

cont:
delay(2000);
digitalWrite(GreenLed,LOW);
digitalWrite(RedLed,LOW);

//if you want to close the Excel when all card had detected and save Excel file in Names Folder. in my case i have just 2 card (optional)
/*if(n==2){
    Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
    Serial.println("FORCEEXCELQUIT");
    }*/
}
    
