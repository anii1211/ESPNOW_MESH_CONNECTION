#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#define but_on 13
#define but_off 12
#define LED 14

int ESP1 = 0;
int ESP2 = 0;
char s1[20]={'0'};
char s2[20]={'0'};

bool new_data = 0; // Flag to send data only once
 esp_err_t result; // declaration

// Universal MAC Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

bool incomingLED_status;

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message
{
  char but_status;
} struct_message;

// Create a struct_message called myData
struct_message myData;

struct_message incomingReadings;
// Create peer interface
esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&s2, incomingData, sizeof(s2));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingLED_status = incomingReadings.but_status;
  Serial.println(s2);
  digitalWrite(LED, incomingLED_status);
  memset(s2,0,sizeof(s2));
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  pinMode(but_on, INPUT_PULLUP);
  pinMode(but_off, INPUT_PULLUP);
  pinMode(LED, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Send Callback Function
  esp_now_register_send_cb(OnDataSent);

  // Receive Callback Function
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
    /// ..................................................//////////////////
  //   if(ESP1==0 && new_data == 1)
  // {
  //   // myData.but_status = 102;

  //   new_data = 0;
  //   ESP1=1;
  // }
  // // if (digitalRead(but_off) == LOW && new_data == 1)
  // if(ESP2 == 1 && new_data == 1 )
  // {
  //   myData.but_status = 1033;
  //   new_data = 0;
  // }

  // esp_err_t result; // declaration

  // // Send message via ESP-NOW
  // if (new_data == 0)
  // {

  //   result = esp_now_send(broadcastAddress, (uint8_t *) &s1, sizeof(s1));
  //   new_data = 1;
  // }

  // if (result == ESP_OK) 
  // {
  //   Serial.println("Sent with success");
  //   // ESP1++;
  //   // ESP2++;
  // }
  // else
  // {
  //  Serial.println("Error sending the data");
  // }
}

void loop()
{
  // Set values to send
  // if (digitalRead(but_on) == LOW && new_data == 1)
  // if(ESP1==0 && new_data == 1)
  // {
  //   myData.but_status = 2;
  //   new_data = 0;
  //   ESP1=1;
  // }
  // // if (digitalRead(but_off) == LOW && new_data == 1)
  // if(ESP2 == 1 && new_data == 1 )
  // {
  //   myData.but_status = 3;
  //   new_data = 0;
  // }

  // esp_err_t result; // declaration

  // // Send message via ESP-NOW
  // if (new_data == 0)
  // {

  //   result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  //   new_data = 1;
  // }

  // if (result == ESP_OK) 
  // {
  //   Serial.println("Sent with success");
  //   // ESP1++;
  //   // ESP2++;
  // }
  // else
  // {
  //  Serial.println("Error sending the data");
  // }
  while (Serial.available())
   {
    for(uint8_t i = 0; i<20;i++)
    {
      s1[i]=(Serial.read());
    }
    
    result = esp_now_send(broadcastAddress, (uint8_t *) &s1, sizeof(s1));
    memset(s1,0,sizeof(s1));
   }
   if (result == ESP_OK) 
  {
    //Serial.println("Sent with success");
    // ESP1++;
    // ESP2++;
  }
  else
  {
   Serial.println("Error sending the data");
  }
  if(ESP1>500 || ESP2>500)
  {
    ESP1=0;
    ESP2=0;
  }
  // delay(10000);
}void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
