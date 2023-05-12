
# Monitor de Temperatura e Umidade

- Ao atingir a temperatura de 35ºC o acionador 1 é ativado;
- Ao atingir a umidade de 70% o acionador 2 é ativado;
- As informações são enviadas a cada 5 segundos para a plataforma [ThingSpeak](https://thingspeak.com/channels/2144388).

## Instalação

```bash
  git clone https://github.com/gabrielrleite/Monitor-de-Temperatura-e-Umidade.git
  Abra o arquivo `monitor_temp_hum.ino` com o Arduino IDE
  Faça o upload do código e instalação das bibliotecas
```
## Biblitecas

```
  - Adafruit_Sensor
  - DHT
  - WiFi
  - HTTPClient
  - LiquidCrystal_I2C
```

## Componentes Utlizados

```
  - ESP32
  - LCD 20x4 (I2C)
  - DHT22
  - LED Vermelho
  - LED Verde
  - Resistor 220Ω 2x
```
## Screenshots

![Circuito Desligado](https://github.com/gabrielrleite/Monitor-de-Temperatura-e-Umidade/blob/main/src/Circuito.png)

![Circuito Ligado](https://github.com/gabrielrleite/Monitor-de-Temperatura-e-Umidade/blob/main/src/Circuito_2.png)


## Referência

 - [WOKWI](https://wokwi.com/projects/364472568698491905)
 - [ThingSpeak](https://thingspeak.com/channels/2144388)
 - [Arduino IDE](https://www.arduino.cc/en/software)
 - [Editor read.me](https://readme.so/pt/editor)


## Licença

[MIT](https://choosealicense.com/licenses/mit/)

