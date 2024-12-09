#include <Servo.h>
#include <SoftwareSerial.h>
#include <HardwareSerial.h>
#include <string.h>

#define trigPin 7
#define echoPin 6
#define ledB 10

SoftwareSerial Bluetooth(18, 19); // Conexão Arduino(RX, TX) e App

// Variaveis dos servos
Servo s24;
Servo s23;
Servo s22;

Servo s21;
Servo s20;
Servo s19;

Servo s18;
Servo s17;
Servo s16;

Servo s7;
Servo s8;
Servo s9;

Servo s10;
Servo s11;
Servo s12;

Servo s1;
Servo s2;
Servo s3;

Servo s15;
Servo s14;
Servo s13;

Servo s5;

int i0H1 = 0;
int i1H1 = 0;
int i2H1 = 0;
int i3H1 = 0;
int i4H1 = 0;
int i5H1 = 0;
int i6H1 = 0;
int i7H1 = 0;
int i8H1 = 0;

int i0T1 = 0;
int i1T1 = 0;
int i2T1 = 0;
int i3T1 = 0;
int i4T1 = 0;
int i5T1 = 0;
int i6T1 = 0;

int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 0;
int i4L1 = 0;
int i5L1 = 0;
int i6L1 = 0;

int i1L2 = 0;
int i2L2 = 0;
int i3L2 = 0;
int i4L2 = 0;
int i5L2 = 0;
int i6L2 = 0;
boolean l1status = LOW;
boolean l2status = LOW;
boolean aStatus = LOW;
boolean attStatus = LOW;
int k = 0;
int a = 0;
int aa = 0;
int period = 1000;
unsigned long time_now = 0;

// Variáveis de uso específico
float distancia;
long duracao;
int dataIn; // Recebe código dos comandos através BLUETOOTH conectado ao app
int dataOut; 
String enderecoVisaoFormiga = ""; // Único dado para enviar do BLUETOOTH ao app
const char idRede = "Pedro Ribeiro";
const char senhaRede = "Hquijar256nakA";
int m = 0;
int h = 0;
int t = 0;
int att = 0;
// int speedV = 30;

void setup() {
  Serial.begin(38400); // Serial para printar no Serial Monitor
  Serial2.begin(115200); // Configura "ESP32CAM" para conexão ao ESP32-CAM
  Serial2.setTimeout(20); // Configura tempo máximo de (em miliseconds) para esperar 
  Bluetooth.begin(115200); // Configura "Bluetooth" para conexão ao módulo HC-05
  Bluetooth.setTimeout(20);

  delay(2000);

  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledB, OUTPUT);
  // Cabeça
  s15.attach(36, 600, 2400);
  s14.attach(35, 600, 2400);
  s13.attach(34, 600, 2400); //garra
  // Rabo
  s5.attach(26, 600, 2400); 
  // Perna 4
  s10.attach(31, 600, 2400);
  s11.attach(32, 600, 2400);
  s12.attach(33, 600, 2400); //rot
  // Perna 5
  s7.attach(28, 600, 2400);
  s8.attach(29, 600, 2400);
  s9.attach(30, 600, 2400); //rot
  // Perna 6
  s1.attach(22, 600, 2400);
  s2.attach(23, 600, 2400);
  s3.attach(24, 600, 2400); //rot
  // Perna 1
  s18.attach(39, 600, 2400);
  s17.attach(38, 600, 2400);
  s16.attach(37, 600, 2400); //rot
  // Perna 2
  s21.attach(42, 600, 2400);
  s20.attach(41, 600, 2400);
  s19.attach(40, 600, 2400); //rot
  // Perna 3
  s24.attach(45, 600, 2400);
  s23.attach(44, 600, 2400);
  s22.attach(43, 600, 2400); //rot

  // Posição inicial
  // Cabeça
  s15.write(72);
  s14.write(50);
  s13.write(90); // Garra
  
  s5.write(65); // Rabo
  
  // Perna 4
  s10.write(65);
  s11.write(35);
  s12.write(40);
  // Perna 5
  s7.write(80);
  s8.write(50);
  s9.write(25);
  // Perna 6
  s1.write(90);
  s2.write(45);
  s3.write(60);

  // Perna 1
  s18.write(60);
  s17.write(90);
  s16.write(100);
  // Perna 2
  s21.write(50);
  s20.write(85);
  s19.write(75);
  // Perna 3
  s24.write(50);
  s23.write(80);
  s22.write(80);

  delay(3000);
}


void loop() {
  
  if (Serial2.available() > 0) {
    enderecoVisaoFormiga = Serial2.read(); // Receber IP da ESP32-CAM
    Bluetooth.println(enderecoVisaoFormiga);
  }

  Serial2.println(idRede);
  delay(200)
  Serial2.println(senhaRede);
  

  // Verifica se bluetooth está recebendo dados
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.read(); // Lê os dados
    Serial.println(dataIn);

    // INICIO - Entrada de comandos (movimento, ataque e controle de garra)
    
    /*// Envia credenciais ao ESP32-CAM
    if (dataIn == 1) {
      idRede = Bluetooth.read();
      Serial2.println(idRede);
      delay(200);
      senhaRede = Bluetooth.read();
      Serial2.println(senhaRede);
    }

    // Processa IP e envia à variável de endereço para a visão da formiga
    if (dataIn == 2) {
      dataOut = enderecoVisaoFormiga;
      Bluetooth.println(dataOut);
    }
    */

    // Anda para frente
    if (dataIn == 3) {
      m = 3;
    }

    // Anda para trás
    if (dataIn == 4) {
      m = 4;
    }

    // Gira sentido antihorário
    if (dataIn == 5) {
      m = 5;
    }

    // Gira sentido horário
    if (dataIn == 6) {
      m = 6;
    }

    /*
    if (dataIn == 10) {
      t = 10;
    }
    if (dataIn == 11) {
      h = 11;
    }
    if (dataIn >= 15) {
      speedV = dataIn;
    }
    */
    // FIM - Entrada de comandos
  }

  // Move frente
  if (m == 3) {
    movePerna1();
    movePerna3();
    movePerna5();
    if (l1status == HIGH) {
      movePerna2();
      movePerna4();
      movePerna6();
    }
  }

  // Move reverse
  if (m == 4) {
    movePerna1Rev();
    movePerna3Rev();
    movePerna5Rev();
    if (l1status == HIGH) {
      movePerna2Rev();
      movePerna4Rev();
      movePerna6Rev();
    }
  }

  // Rotação antihorário (esquerda)
  if (m == 5) {
    moveCabecaEsquerda();
    movePerna1();
    movePerna3();
    movePerna5Esquerda();
    if (l1status == HIGH) {
      movePerna2();
      movePerna4Esquerda();
      movePerna6Esquerda();
    }
  }

  // Rotação horário (direita)
  if (m == 6) {
    moveCabecaDireita();
    movePerna1Direita();
    movePerna3Direita();
    movePerna5();
    if (l1status == HIGH) {
      movePerna2Direita();
      movePerna4();
      movePerna6();
    }
  }

  // Fecha Garra
  if (dataIn == 7) {
    fecha();
  }

  // Abre Garra
  if (dataIn == 8) {
    abre();
  }

  // Ataque
  if (dataIn == 9) {
    prepararAtaque();
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(1000);
        a = 1;
      }
      ataque();
      if (attStatus == HIGH) {
        while (aa == 0) {
          delay(2000);
          aa = 1;
        } 
        attStatus = LOW;
      }
    }
  }

  if (dataIn == 0) {
    posicaoinicial();

    if (pegarDistancia() > 40) {
      att = 0;
    }
    if (pegarDistancia() <= 40) {
      att = 1;
      dataIn = 99;
    }
    
    
    int valorSensor = analogRead(A3);
    float tensao = valorSensor * (5.00 / 1023.00) * 2.9;
    //Serial.println(tensao);
    
    if (tensao < 11) {
      digitalWrite(ledB, HIGH);
    }
    else {
      digitalWrite(ledB, LOW);
    }
  }
  
  /*
  // mordida
  if (dataIn == 6) {
    mordida();
  }
  // Rabo
  if (t == 10) {
    rabo();
  }
  // Cabeça
  if (h == 11) {
    moveCabeca();
  }
  if (dataIn == 12) {
    posicaoInicialRabo();
  }
  if (dataIn == 13) {
    posicaoInicialCabeca();
  }
  */

  if (att == 1) {
    prepararAtaque();
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(2000);
        a = 1;
      }
      if (pegarDistancia() > 30) {
        att = 2;
        a = 0;
        aStatus = LOW;
        posicaoInicialCabeca();
      }
      if (pegarDistancia() < 30) {
        att = 3;
        a = 0;
        aStatus = LOW;
        posicaoInicialCabeca();
      }
    }
  }

  if (att == 2) {
    cancelaAtaque();
    if (aStatus == HIGH) {
      dataIn = 0;
      att = 0;
    }
  }

  if (att == 3) {
    ataque();
    if (attStatus == HIGH) {
      while (aa == 0) {
        delay(2000);
        aa = 1;
      } attStatus = LOW;
    }
    if (aStatus == HIGH) {
      while (a == 0) {
        delay(2000);
        a = 1;
      }
      dataIn = 0;
      att = 0;
      posicaoInicialCabeca();
    }
  }
  //delay(speedV);
}

// === Sessão de funções ===



// Ataque

void prepararAtaque() {
  // Perna 1
  if (i1H1 <= 15) {
    //Perna 1
    s18.write(60 - i1H1);
    s17.write(90 - i1H1);
    // Perna 3
    s24.write(50 + i1H1 / 2);
    s23.write(80 + i1H1);
    // Perna 4
    s10.write(65 + i1H1);
    s11.write(35 + i1H1);
    // Perna 6
    s1.write(90 - i1H1);
    s2.write(45 - i1H1);
    // Cabeça
    s14.write(50 - i1H1 * 2);
    s13.write(90 - i1H1);

  }
  if (i1H1 <= 30) {
    s16.write(100 - i1H1);
    s19.write(75 - i1H1);
    s22.write(80 - i1H1);
    s12.write(35 + i1H1);
    s9.write(30 + i1H1);
    s3.write(60 + i1H1);
    i1H1++;
  }
  if (i1H1 >= 30) {
    aStatus = HIGH;
  }
}

void cancelaAtaque() {
  // LEG 1
  if (i2H1 <= 15) {
    //Perna 1
    s18.write(45 + i2H1);
    s17.write(75 + i2H1);
    // Perna 3
    s24.write(57 - i2H1 / 2);
    s23.write(95 - i2H1);
    // Perna 4
    s10.write(80 - i2H1);
    s11.write(50 - i2H1);
    // Perna 6
    s1.write(75 + i2H1);
    s2.write(30 + i2H1);
    // Cabeça
    s14.write(20 + i2H1 * 2);
    s13.write(75 + i2H1);
  }
  if (i2H1 <= 30) {
    s16.write(70 + i2H1);
    s19.write(45 + i2H1);
    s22.write(50 + i2H1);
    s12.write(65 - i2H1);
    s9.write(60 - i2H1);
    s3.write(90 - i2H1);
    i2H1++;
  }
  if (i2H1 >= 30) {
    aStatus = HIGH;
  }
}

void ataque() {
  // Perna 1
  if (i3H1 <= 10) {
    //Perna 1
    s18.write(45 + i3H1 * 2);
    s17.write(75 + i3H1 * 3);
    // Perna 3
    s24.write(57 - i3H1 / 2);
    s23.write(95 - i3H1 * 3);
    // Perna 4
    s10.write(80 - i3H1 * 2);
    s11.write(50 - i3H1 * 3);
    // Perna 6
    s1.write(75 + i3H1 * 2);
    s2.write(30 + i3H1 * 3);
    // Cabeça
    s14.write(20 + i3H1 * 2);
    s13.write(75 + i3H1 * 3);
  }
  if (i3H1 <= 16) {
    s16.write(70 + i3H1 * 3);
    s19.write(45 + i3H1 * 3);
    s22.write(50 + i3H1 * 3);
    s12.write(65 - i3H1 * 3);
    s9.write(60 - i3H1 * 3);
    s3.write(90 - i3H1 * 3);
    i3H1++;
  }
  if (i3H1 >= 16) {
    attStatus = HIGH;
  }
  if (i3H1 >= 16 & i4H1 < 15) {
    //Perna 1
    s18.write(65 - i4H1 / 3);
    s17.write(105 - i4H1);
    // Perna 3
    //s24.write(50 + i4H1 / 2);
    s23.write(65 + i4H1);
    // Perna 4
    s10.write(60 + i4H1 / 3);
    s11.write(20 + i4H1);
    // Perna 6
    s1.write(95 - i4H1 / 5);
    s2.write(60 - i4H1);
    // Cabeça
    s14.write(40 + i4H1 / 2);
    s13.write(105 - i4H1);
  }
  if (i3H1 >= 16 & i4H1 <= 18) {
    s16.write(118 - i4H1);
    s19.write(93 - i4H1);
    s22.write(98 - i4H1);
    s12.write(17 + i4H1);
    s9.write(12 + i4H1);
    s3.write(42 + i4H1);
    i4H1++;
  }
  if (i4H1 >= 18) {
    aStatus = HIGH;
  }
}

/*
void moveCabeca() {
  if (i0H1 <= 40) {
    s15.write(72 + i0H1);
    i0H1++;
  }
  if (i0H1 >= 40 & i1H1 <= 40) {
    s14.write(50 - i1H1 / 2);
    s15.write(112 - i1H1);
    i1H1++;
  }
  if (i1H1 >= 40 & i2H1 <= 20) {
    s13.write(90 - i2H1);
    i2H1++;
  }
  if (i2H1 >= 20 & i3H1 <= 10) {
    s13.write(70 + i3H1 * 4);
    i3H1++;
  }
  if (i3H1 >= 10 & i4H1 <= 40) {
    s13.write(110 - i4H1);
    i4H1++;
  }
  if (i4H1 >= 40 & i5H1 <= 10) {
    s13.write(70 + i5H1 * 4);
    i5H1++;
  }
  if (i5H1 >= 10 & i6H1 <= 20) {
    s13.write(110 - i6H1);
    i6H1++;
  }
  if (i6H1 >= 20 & i7H1 <= 40) {
    s14.write(30 + i7H1 / 2);
    s15.write(72 - i7H1);
    i7H1++;
  }
  if (i7H1 >= 40 & i8H1 <= 40) {
    s15.write(32 + i8H1);
    i8H1++;
  }
}

void mordida() {
  if (i1H1 <= 20) {
    s13.write(90 - i1H1);
    i1H1++;
  }
  if (i1H1 >= 20 & i2H1 <= 10) {
    s13.write(70 + i2H1 * 4);
    i2H1++;
  }
  if (i2H1 >= 10 & i3H1 <= 40) {
    s13.write(110 - i3H1);
    i3H1++;
  }
  if (i3H1 >= 40 & i4H1 <= 10) {
    s13.write(70 + i4H1 * 4);
    i4H1++;
  }
  if (i4H1 >= 10 & i5H1 <= 40) {
    s13.write(110 - i5H1);
    i5H1++;
  }
  if (i5H1 >= 40 & i6H1 <= 20) {
    s13.write(70 + i6H1);
    i6H1++;
  }
}

void rabo() {
  if (i0T1 <= 25) {
    s5.write(65 - i0T1);
    i0T1++;
  }
  if ( i0T1 >= 25 & i1T1 <= 50) {
    s5.write(40 + i1T1);
    i1T1++;
  }
  if ( i1T1 >= 50 & i2T1 <= 50) {
    s5.write(90 - i2T1);
    i2T1++;
  }
  if ( i2T1 >= 50 & i3T1 <= 50) {
    s5.write(40 + i3T1);
    i3T1++;
  }
  if ( i3T1 >= 50 & i4T1 <= 50) {
    s5.write(90 - i4T1);
    i4T1++;
  }
  if ( i4T1 >= 50 & i5T1 <= 50) {
    s5.write(40 + i5T1);
    i5T1++;
  }
  if ( i5T1 >= 50 & i6T1 <= 25) {
    s5.write(90 - i6T1);
    i6T1++;
  }
}
*/

void moveCabecaEsquerda() {
  if (i0H1 <= 25) {
    s14.write(50 - i0H1);
    s15.write(72 - i0H1);
    s5.write(65 + i0H1); // Tail
    i0H1++;
  }
}

void moveCabecaDireita() {
  if (i2H1 <= 25) {
    s14.write(50 - i2H1);
    s15.write(72 + i2H1);
    s5.write(65 - i2H1); // Tail
    i2H1++;
  }
}

void fecha() {
  if (i1H1 <= 20) {
    s13.write(90 + i1H1);
    i1H1++;
  }
}

void abre() {
  if (i2H1 <= 20) {
    s13.write(110 - i2H1);
    i2H1++;
  }
}



void movePerna1() {
  // Levanta a perna
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  // Rotaciona a perna
  if (i2L1 <= 30) {
    s16.write(100 - i2L1);
    i2L1++;

  }
  // Volta a posição para tocar o chão
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    s16.write(70 + i4L1);
    i4L1++;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}

void movePerna2() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(75 - i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(45 + i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void movePerna3() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(80 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(50 + i4L1);
  }
}

void movePerna4() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(35 + i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(65 - i4L2);
  }
}

void movePerna5() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(30 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(60 - i4L1);
  }
}

void movePerna6() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(60 + i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(90 - i4L2);
  }
}

void movePerna1Rev() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    //Serial.println(s17.read());
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    //Serial.println(s17.read());
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}

void movePerna2Rev() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void movePerna3Rev() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void movePerna4Rev() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(65 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(35 + i4L2);
  }
}

void movePerna5Rev() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void movePerna6Rev() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(60 + i4L2);
  }
}

void movePerna1Direita() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}

void movePerna2Direita() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void movePerna3Direita() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void movePerna4Esquerda() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(60 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(30 + i4L2);
  }
}

void movePerna5Esquerda() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void movePerna6Esquerda() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(60 + i4L2);
  }
}

void posicaoInicialRabo() {
  i0T1 = 0;
  i1T1 = 0;
  i2T1 = 0;
  i3T1 = 0;
  i4T1 = 0;
  i5T1 = 0;
  i6T1 = 0;
  t = 0;
}

void posicaoInicialCabeca() {
  attStatus = LOW;
  aStatus = LOW;
  i0H1 = 0;
  i1H1 = 0;
  i2H1 = 0;
  i3H1 = 0;
  i4H1 = 0;
  i5H1 = 0;
  i6H1 = 0;
  i7H1 = 0;
  i8H1 = 0;
  h = 0;
  aa = 0;
}

void posicaoinicial() {
  a = 0;
  aa = 0;
  m = 0;
  l1status = LOW;
  l2status = LOW;
  aStatus = LOW;
  attStatus = LOW;
  // Cabeça
  s15.write(72);
  s14.write(55);
  s13.write(90); // garra

  s5.write(65); // rabo

  // Perna 4
  s10.write(65);
  s11.write(35);
  s12.write(40);
  // Perna 5
  s7.write(80);
  s8.write(50);
  s9.write(25);
  // Perna 6
  s1.write(90);
  s2.write(45);
  s3.write(60);

  // Perna 1
  s18.write(60);
  s17.write(90);
  s16.write(100);
  // Perna 2
  s21.write(50);
  s20.write(80);
  s19.write(75);
  // Perna 3
  s24.write(50);
  s23.write(80);
  s22.write(80);
  i0H1 = 0;
  i1H1 = 0;
  i2H1 = 0;
  i3H1 = 0;
  i4H1 = 0;
  i5H1 = 0;
  i6H1 = 0;
  i7H1 = 0;
  i8H1 = 0;

  i0T1 = 0;
  i1T1 = 0;
  i2T1 = 0;
  i3T1 = 0;
  i4T1 = 0;
  i5T1 = 0;
  i6T1 = 0;

  i1L1 = 0;
  i2L1 = 0;
  i3L1 = 0;
  i4L1 = 0;
  i5L1 = 0;
  i6L1 = 0;

  i1L2 = 0;
  i2L2 = 0;
  i3L2 = 0;
  i4L2 = 0;
  i5L2 = 0;
  i6L2 = 0;
}


// === Identificar Distancia ===
int pegarDistancia() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);
  distancia = duracao * 0.034 / 2;
  return distancia;
}
