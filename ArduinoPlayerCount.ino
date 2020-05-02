#include <UIPEthernet.h>
#include <ArduinoHttpClient.h>
#include <LiquidCrystal.h>

char serverAddress[] = "192.168.1.105";  
int port = 8080;
uint8_t mac[6] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05};

EthernetClient client;
HttpClient httpClient = HttpClient(client, serverAddress, port);
LiquidCrystal lcd(9, 8, 7, 6, 5,4);

void setup() {
  Serial.begin(9600);
  Ethernet.init(10);  
  Ethernet.begin(mac);
  lcd.begin(16, 2);
}

void loop(){ 
  
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

  Serial.println(online);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Online: ");
  lcd.print(online);
  
  delay(1000);
}
