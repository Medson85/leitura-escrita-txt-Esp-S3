#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <fileHandler.h>


#define unid_eng 0.0008056640625
#define amostra 10

Adafruit_NeoPixel led_rgd(1, 48, NEO_GRBW + NEO_KHZ800);

float volt[amostra] = {};
int j = 0;
int soma_tensao = 0;
float mediaDeTensao = 0;
//FILE *file;

void setup(){
  Serial.begin(115200);
  led_rgd.begin();
  led_rgd.setBrightness(200);
  pinMode(17, INPUT);

if(!SPIFFS.begin(true)){
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    readFile(SPIFFS, "/hello.txt");
    listDir(SPIFFS, "/", 0);
    writeFile(SPIFFS, "/hello.txt", "Hello ");        //cria arquivo e escreve
    appendFile(SPIFFS, "/hello.txt", "World!\n\n");   //adiciona informação em arquivo já existente
    readFile(SPIFFS, "/hello.txt");                   //le o arquivo
    //deleteFile(SPIFFS, "/foo.txt");                 //apaga o arquivo
    //renameFile(SPIFFS, "/hello.txt", "/foo.txt");   //renomeia o arquivo
    //readFile(SPIFFS, "/foo.txt");         
    //testFileIO(SPIFFS, "/test.txt");

}

void loop(){

  volt[j] = (analogRead(17) * unid_eng);
  soma_tensao = soma_tensao + volt[j];
  
  if (j == amostra){

    mediaDeTensao = soma_tensao / amostra;
    appendFile(SPIFFS, "/hello.txt", ("\nMedia :" + String(mediaDeTensao)).c_str());   //adiciona informação em arquivo já existente
    appendFile(SPIFFS, "/hello.txt", ("\n"));

    for (int inc  = 0; inc < amostra; inc++){/* ZERAR VETOR */
      volt[inc] = 0;
    }
    mediaDeTensao = 0;
    j = 0;
  }//if (j == amostra)
  

  
  
  else{
    appendFile(SPIFFS, "/hello.txt", ("Tensão " + String(j) + " :" + String(volt[j]) + "\n").c_str());   //adiciona informação em arquivo já existente
    Serial.println("Tensão " + String(j) + " :" + String(volt[j]));
    led_rgd.setPixelColor(0, uint32_t (led_rgd.Color(255, 0 , 0)));
    led_rgd.show();
    delay(250);

    /*Serial.println("Tensão : " + String(volt[j]));*/
    led_rgd.setPixelColor(0, uint32_t (led_rgd.Color(0, 255, 0)));
    led_rgd.show();
    delay(250);

    /*Serial.println("Tensão : " + String(volt[j]));*/
    led_rgd.setPixelColor(0, uint32_t (led_rgd.Color(0, 0 , 255)));
    led_rgd.show();
    delay(250);
  }

  j++;
}

void media(){
  
  
  for(int i = 0; i < amostra; i++){
    soma_tensao = soma_tensao + volt[i];
  }
  
  mediaDeTensao = soma_tensao / amostra;
  

}