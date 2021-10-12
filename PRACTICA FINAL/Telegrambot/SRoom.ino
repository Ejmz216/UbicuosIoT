#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>//https://github.com/adafruit/DHT-sensor-library
#include "ThingSpeak.h" 
#define DHTPIN 4
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define WIFI_SSID "Familia-Bravo"
#define WIFI_PASSWORD "CONYJUANES"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "2073550382:AAER8NYfr1Km1jkNH07LnTANRRn53NpmkIw"

DHT dht(DHTPIN, DHTTYPE);

unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;

const char* ssid = "Familia-Bravo";
const char* password = "CONYJUANES";
String BOTtoken = "2073550382:AAER8NYfr1Km1jkNH07LnTANRRn53NpmkIw";
String CHAT_ID = "1335501469";


bool tempC = false;
bool tempF = false;
bool hum = false;
bool L1 = false;
bool LV = false;
bool LOFF1 = false;
bool LOFF2 = false;
bool flag1;
bool flag2;
const int ledPIN = 5;
bool Start = false;
unsigned long bot_lasttime;          // last time messages' scan has been done

//-------------MOTOR----------------------
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
 
// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;
//----------------------------------------

const unsigned long BOT_MTBS = 500; // mean time between scan messages
WiFiClient  client;
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);


unsigned long myChannelNumber = 1529977;
const char * myWriteAPIKey = "FM3AVFFBB3P190HQ";

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = bot.messages[i].chat_id;
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "")
      from_name = "Guest";

    if ((text == "/Comenzar") || (text == "/comenzar") || (text == "/start"))
    {
      String welcome = "Bienvenido, " + from_name + "!\n";
      welcome += "Use los siguientes comandos para conocer información o interactuar con su habitación:  \n";
      welcome += "/TemperaturaC: Enseña el valor de temperatura en °C\n";
      welcome += "/TemperaturaF: Enseña el valor de temperatura en °F\n";
      welcome += "/Humedad: Enseña el valor de la humedad en %\n";
      welcome += "/Luz1: Enciende la luz\n";
      welcome += "/Luz1OFF: Apaga todas la luz 1\n";
      welcome += "/Ventilador: Enciende el ventilador\n";
      welcome += "/VentOFF: Apaga el ventilador\n";
      bot.sendMessage(CHAT_ID, welcome, "");
    }

    if (text == "/TemperaturaC")
    {
      tempC = true;
      Serial.println("Temperature C request");
    }
    if (text == "/TemperaturaF")
    {
      tempF = true;
      Serial.println("Temperature F request");
    }
    if (text == "/Humedad")
    {
      hum = true;
      Serial.println("Humidity request");
    }
    if (text == "/Luz1")
    {
      L1 = true;
      Serial.println("Light 1 on");
    }
    if (text == "/Luz1OFF")
    {
      LOFF1 = true;
      Serial.println("Night mode");
    }
      if (text == "/Ventilador")
    {
      LV = true;
    }
       if (text == "/VentOFF")
    {
      LOFF2 = true;
    }




  }
}

void setup()
{

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
 
  //-------------
  dht.begin();
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    delay(100);
    now = time(nullptr);
  }
  ThingSpeak.begin(client); 
  pinMode(ledPIN, OUTPUT);
}

void loop()
{
   bool cambio=false;
  
  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    bot_lasttime = millis();
  }



  float h = dht.readHumidity();
  // Leer temperatura ºC
  float t = dht.readTemperature();
  // si se le pasa a la funcion el parametro true obtenemos la temperatura en ºF
  float f = dht.readTemperature(true);

 if (tempC) {
    Serial.println("Temp °C sended!");
    String myString = String(t);
    bot.sendMessage(CHAT_ID, myString + "°C", "");
    tempC = false;
  }
  if (tempF) {
    Serial.println("Temp °F sended!");
    String myString2 = String(f);
    bot.sendMessage(CHAT_ID, myString2 + "°F", "");
    tempF = false;
  }
  if (hum) {
    Serial.println("Hum sended!");
    String myString3 = String(h);
    bot.sendMessage(CHAT_ID, myString3 + "%", "");
    hum = false;
  }
  if (L1) {
    digitalWrite(ledPIN , HIGH);
    flag1=true;
    L1 = false;
  }

  if (LOFF1) {

    digitalWrite(ledPIN, LOW);
    flag1=false;   
    LOFF1 = false;
  }
   if(LV)
  {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  ledcWrite(pwmChannel, dutyCycle);
   flag2=true;
   cambio=true;
   LV = false;
  }
    if(LOFF2){
       // Stop the DC motor
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
    flag2=false; 
    cambio=true;   
    LOFF2 = false;
    }
    
  ThingSpeak.setField(1, t); 
  ThingSpeak.setField(2, h); 
  // long rssi= WiFi.RSSI();
  //int httpCode = ThingSpeak.writeField(myChannelNumber, 1, rssi, myWriteAPIKey);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  delay(1000);

  tiempo2 = millis();
 if(((tiempo2 > (tiempo1+30000)))||(cambio==true)){
    tiempo1 = millis();
    Serial.print(" "+String(h));
    Serial.print(" "+String(t));
    Serial.print(" "+String(flag1));
    Serial.println(" "+String(flag2)+" ");
 }
}
