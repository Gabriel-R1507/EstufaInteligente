//Mapenado pinos do Arduino
int pino_cooler = 13;
int pino_rele1 = 12;
int pino_rele2 = 11;
int pino_termometro = A0;
int pino_umidade = A1;

//configurando variaveis 
int umidade_limite = 0;
int temperatura_limite = 0;
int timer = 0;
int timer_agua = 0;
bool ligar = false;

//Incluindo bibliotecas
#include <PubSubClient.h>

#define TOPICO_SUBSCRIBE "EstufaInteligenteSend"
#define TOPICO_PUBLISH   "EstufaInteligenteRecive"

#define ID_MQTT  "Estufainteligente05K"  


// Cinfiguração do wifi
const char* SSID = "Caçador107";
const char* PASSWORD = "74240654";
  
//Configurando Broker
const char* BROKER_MQTT = "iot.eclipse.org";
int BROKER_PORT = 1883;
 
 
//Variáveis e objetos globais
WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoDeSaida = '0';
  
//Prototypes
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);





void setup() {
  Serial.begin(9600);
  reconectWiFi();
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
  
  pinMode(pino_cooler, OUTPUT);
  pinMode(pino_rele1, OUTPUT);
  pinMode(pino_rele2, OUTPUT);
  pinMode(pino_termometro, INPUT);
  pinMode(pino_umidade, INPUT);
}

void loop() {
  if(timer > 9000){
    ligar = true;
  }
  else{
    ligar = false;
  }
  
  if(ligar){
    digitalWrite(pino_rele2, LOW);
  }
  else{
    digitalWrite(pino_rele2, HIGH);
  }
  timer = ( timer + 1 ) % 10000;


  
  int SensorTempTensao=analogRead(pino_termometro);
  float Tensao = SensorTempTensao*5;
  Tensao/=1023;

  float TemperaturaC = Tensao / 0.010;

  if(TemperaturaC > 20.00){
    digitalWrite(pino_cooler, HIGH);
  }
  else{
    digitalWrite(pino_cooler, LOW);
  }



  int Umiade=analogRead(pino_umidade);
  if(Umiade > 306){
    timer_agua = timer_agua + 1;
    if(timer_agua < 2000){
      digitalWrite(pino_rele1, LOW);
    }
    else{
      timer = 0;
      digitalWrite(pino_rele1, HIGH);
    }
  }
  else{
    timer_agua = 0;
    digitalWrite(pino_rele1, HIGH);
  }

  VerificaConexoesWiFIEMQTT();
  EnviaEstadoOutputMQTT();
  MQTT.loop();
  Serial.print("Umidade");
  Serial.println(Umiade);
  Serial.print("Temperatura");
  Serial.println(TemperaturaC);
  
  
  delay(100);
}
  

void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado ao MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            delay(2000);
        }
    }
}

void reconectWiFi() 
{
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100)
    }
    Serial.print("Conectado com sucesso na rede ");
    Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT();
     reconectWiFi();
}
 
void EnviaEstadoOutputMQTT(void)
{
  int SensorTempTensao=analogRead(pino_termometro);
  float Tensao = SensorTempTensao*5;
  Tensao/=1023;
  float TemperaturaC = Tensao / 0.010;

  MQTT.publish(TOPICO_PUBLISH, analogRead(pino_umidade));
  
  MQTT.publish(TOPICO_PUBLISH, TemperaturaC);
      
  delay(1000);
}
