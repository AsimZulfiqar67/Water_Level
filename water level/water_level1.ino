#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library

#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#define wifi_ssid "HighVoltages.co"
#define wifi_password "Highvoltages  670"

#define mqtt_server "tailor.cloudmqtt.com"
#define mqtt_user "kpsfxepp"
#define mqtt_password "50lbq5rQ-eoq"



WiFiClient espClient;
PubSubClient client(espClient);

unsigned int interval = 1000;
#define motor D5
//#define TFT_CS     10
//#define TFT_RST    8  // you can also connect this to the Arduino reset
//                      // in which case, set this #define pin to 0!
//#define TFT_DC     9

#define TFT_RST   D4     // TFT RST pin is connected to NodeMCU pin D4 (GPIO2)
#define TFT_CS    D3     // TFT CS  pin is connected to NodeMCU pin D4 (GPIO0)
#define TFT_DC    D2     // TFT DC  pin is connected to NodeMCU pin D4 (GPIO4)
 
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

 
float p = 3.1415926;

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 15565);
  client.setCallback(callback);
  client.subscribe("WaterLevel");
  client.subscribe("motor"); 
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
 tft.setRotation(90);
 pinMode(motor,OUTPUT);

  tftPrintTest();
  delay(1000);
  tftPrintTest1();
  delay(1000);

}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_server, mqtt_user, mqtt_password)) {
      Serial.println("connected");
        client.subscribe("WaterLevel");
  client.subscribe("motor");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

bool checkBound(float newValue, float prevValue, float maxDiff) {
  return !isnan(newValue) &&
         (newValue < prevValue - maxDiff || newValue > prevValue + maxDiff);
}

void callback(char* topic, byte* payload, unsigned int length) {
String data;
data="";
String tpc=String(topic);
  for (int i = 0; i < length; i++) {
   data += (char)payload[i];
  }
  Serial.println(data);
  if(tpc=="motor"){
    if(data=="1"){
      digitalWrite(motor,HIGH);
      }
      if(data=="0"){
        digitalWrite(motor,LOW);
        }
    }

   if(tpc=="WaterLevel"){
   int mbl=int(data.toInt());
   int value=mbl/10;
   if(value==0){
    tftPrintTest1();
    }
    else if(value==1){
      tftPrintTest1();
      tft.fillRect(0,148,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(55, 150);
      tft.setTextSize(1);
      tft.println("10%");
   
      }
      else if(value==2){
      tftPrintTest1();
      tft.fillRect(0,135,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(55, 137);
      tft.setTextSize(1);
      tft.println("20%");
   
      }
      else if(value==3){
      tftPrintTest1();
      tft.fillRect(0,121,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(55, 123);
      tft.setTextSize(1);
      tft.println("30%");
   
      }
      else if(value==4){
      tftPrintTest1();
      tft.fillRect(0,108,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_RED);
      tft.setCursor(55, 110);
      tft.setTextSize(1);
      tft.println("40%");
    
      }
      else if(value==5){
        tftPrintTest1();
       tft.fillRect(0,94,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(55, 96);
      tft.setTextSize(1);
      tft.println("50%");
    
      }
      else if(value==6){
        tftPrintTest1();
       tft.fillRect(0,81,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(55, 83);
      tft.setTextSize(1);
      tft.println("60%");
    
      }
      else if(value==7){
        tftPrintTest1();
       tft.fillRect(0,67,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(55, 70);
      tft.setTextSize(1);
      tft.println("70%");
      
      }
      else if(value==8){
        tftPrintTest1();
       tft.fillRect(0,54,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(55, 56);
      tft.setTextSize(1);
      tft.println("80%");
      
      }
      else if(value==9){
        tftPrintTest1();
       tft.fillRect(0,40,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(55, 42);
      tft.setTextSize(1);
      tft.println("90%");
      
      }
      else if(value==10){
        tftPrintTest1();
       tft.fillRect(0,27,tft.width(),tft.height()-12,0x04FF);
      tft.setTextColor(ST7735_GREEN);
      tft.setCursor(55, 29);
      tft.setTextSize(1);
      tft.println("100%");
      
      }
   
      if(value<=6){
              digitalWrite(motor,HIGH);

        }else if(value>=10){
                digitalWrite(motor,LOW);

          }

}
}

    void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(1000);

  }
   

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLUE);
  tft.setTextColor(ST7735_BLACK);
  tft.setCursor(23, 20);
  tft.setTextSize(2);
  tft.println("WIRLESS");
   tft.setCursor(33, 50);
  tft.setTextSize(2);
  tft.println("WATER");  
   tft.setCursor(33, 80);
  tft.setTextSize(2);
  tft.println("LEVEL");
   tft.setCursor(12, 110);
  tft.setTextSize(2);
  tft.println("INDICATOR");
 
}

void tftPrintTest1() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_WHITE);
  tft.setTextColor(ST7735_BLACK);
  tft.setCursor(0, 5);
  tft.setTextSize(2);
  tft.println("WATER LEVEL");
  tft.drawLine(0, 27, tft.width(), tft.height()-133, ST7735_BLACK);
  tft.drawLine(0, 40, tft.width(), tft.height()-120, ST7735_BLACK);
  tft.drawLine(0, 54, tft.width(), tft.height()-106, ST7735_BLACK);
  tft.drawLine(0, 67, tft.width(), tft.height()-93, ST7735_BLACK);
  tft.drawLine(0, 81, tft.width(), tft.height()-79, ST7735_BLACK);
  tft.drawLine(0, 94, tft.width(), tft.height()-66, ST7735_BLACK);
  tft.drawLine(0, 108, tft.width(), tft.height()-52, ST7735_BLACK);
  tft.drawLine(0, 121, tft.width(), tft.height()-39, ST7735_BLACK);
  tft.drawLine(0, 135, tft.width(), tft.height()-25, ST7735_BLACK);
  tft.drawLine(0, 148, tft.width(), tft.height()-12, ST7735_BLACK);

  }



 
