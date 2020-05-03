#include <UIPEthernet.h>
#include <ArduinoHttpClient.h>
#include <LiquidCrystal.h>

char serverAddress[] = "192.168.1.105";  
int port = 8080;
uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};
int maximumPlayers = 0;
int buzzerPin = 3;

EthernetClient client;
HttpClient httpClient = HttpClient(client, serverAddress, port);
LiquidCrystal lcd(9, 8, 7, 6, 5,4);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando...");
  
  Ethernet.init(10);  
  Ethernet.begin(mac);
  pinMode(buzzerPin, OUTPUT);
}

void loop(){ 

  analogWrite(buzzerPin, 255);
  httpClient.get("/DataProvider/");
  int responseCode = httpClient.responseStatusCode();
  String response = httpClient.responseBody();
  String online = "-";
  
  if(responseCode == 200){
      online = response;
  } else { 
      Serial.print("Error: "); 
      Serial.println(responseCode); 
  }

  if(online.toInt() > maximumPlayers){
    
    maximumPlayers = online.toInt();
    
    for(int i = 0; i < 3;i++){
      analogWrite(buzzerPin, 0);
      delay(50);
      analogWrite(buzzerPin, 255);
      delay(100);
    }
    
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Online: ");
  lcd.print(online);
  lcd.setCursor(0, 1);
  lcd.print("Recorde: ");
  lcd.print(maximumPlayers);
  
  delay(1000);
}
