#include <ESP8266WiFi.h>
#include <PubSubClient.h>


#define wifi_ssid "HighVoltages.co"
#define wifi_password "Highvoltages  670"

#define mqtt_server "tailor.cloudmqtt.com"
#define mqtt_user "kpsfxepp"
#define mqtt_password "50lbq5rQ-eoq"



WiFiClient espClient;
PubSubClient client(espClient);

float d = 18; //Enter depth of your tank here in centimeters
int trig = D1; // Attach Trig of ultrasonic sensor to pin 11
int echo = D2; // Attach Echo of ultrasonic sensor to pin 10
float percent;
float wlevel;


void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 15565);
  client.setCallback(callback);
  client.subscribe("abc");
  client.subscribe("abc2");
  
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
        client.subscribe("abc");
  client.subscribe("abc2");
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
  for (int i = 0; i < length; i++) {
   data += (char)payload[i];
  }
  Serial.println(data);
 



}

void loop() {
 
  // Establish variables for duration of the ping,
// and the distance result in inches and centimeters:
long duration, in, cm;       //'in' is inches and 'cm' is centimeter

// The PING is triggered by a HIGH pulse of 2 or more microseconds.
// Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
delayMicroseconds(2);
digitalWrite(trig, HIGH);
delayMicroseconds(5);
digitalWrite(trig, LOW);

// The same pin is used to read the signal from the PING: a HIGH
// pulse whose duration is the time (in microseconds) from the sending
// of the ping to the reception of its echo off of an object.
pinMode(echo, INPUT);
duration = pulseIn(echo, HIGH);

// Convert the time into a distance
in = microsecondsToInches(duration);
cm = microsecondsToCentimeters(duration);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  percent=(cm/d)*100;
  wlevel=100-percent;
  String waterlevel = String(wlevel);
  client.publish("WateLevel",(char*)waterlevel.c_str());
  delay(1000);
  

  }

long microsecondsToInches(long microseconds)
{
// According to Parallax's datasheet for the PING, there are
// 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
// second). This gives the distance travelled by the ping, outbound
// and return, so we divide by 2 to get the distance of the obstacle.
// See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
// The speed of sound is 340 m/s or 29 microseconds per centimeter.
// The ping travels out and back, so to find the distance of the
// object we take half of the distance travelled.
return microseconds / 29 / 2;
}


    
  
