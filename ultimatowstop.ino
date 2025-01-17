#define pinSH_CP  4   // Pino Clock DIR_CLK
#define pinST_CP  12  // Pino Latch DIR_LATCH
#define pinDS     8   // Pino Data DIR_SER
#define pinEnable 7   // Pino Enable DIR_EN

#define pin1PWM 5
#define pin2PWM 6

#define qtdeCI   1

#define bitMotor1A 5
#define bitMotor1B 7
#define bitMotor2A 0
#define bitMotor2B 6

// Calibragem para deixar motores retos
#define velA 230
#define velB 230

void ci74HC595Write(byte pino, bool estado);

// Definindo pinos dos sensores
const int pinosSensores[5] = {A1, A2, A3, A4, A5};
int leituraDosSensores[5];
int lado = 1;

// Variáveis para contagem de quadrados
unsigned long ultimoTempo = 0; 
const unsigned long intervalo = 200; 
int contagemQuadrados = 0;
bool contarQuadrados = true;

void setup() {
  for(int i = 0; i < 5; i++){
    pinMode(pinosSensores[i], INPUT);
  }
  pinMode(pinSH_CP, OUTPUT);
  pinMode(pinST_CP, OUTPUT);
  pinMode(pinEnable, OUTPUT);
  pinMode(pinDS, OUTPUT);
  
  pinMode(pin1PWM, OUTPUT); 
  pinMode(pin2PWM, OUTPUT); 
  
  digitalWrite(pinEnable, LOW);
  
  Serial.begin(9600);  // Iniciar a comunicação serial para monitorar a contagem de quadrados
}

// Função de loop
void loop() {
  // Obter o tempo atual
  unsigned long tempoAtual = millis();

  if (perdeuLinha())
   {
       pararRobo();
        return;
    }

  // Verifica se todos os sensores estão ativados (linha detectada por todos)
  if ((digitalRead(pinosSensores[0]) == HIGH && digitalRead(pinosSensores[1]) == HIGH && digitalRead(pinosSensores[2]) == LOW && digitalRead(pinosSensores[3]) == HIGH && digitalRead(pinosSensores[4]) == HIGH) || (digitalRead(pinosSensores[0]) == LOW && digitalRead(pinosSensores[1]) == LOW && digitalRead(pinosSensores[2]) == LOW && digitalRead(pinosSensores[3]) == HIGH && digitalRead(pinosSensores[4]) == HIGH) || (digitalRead(pinosSensores[0]) == HIGH && digitalRead(pinosSensores[1]) == HIGH && digitalRead(pinosSensores[2]) == LOW && digitalRead(pinosSensores[3]) == LOW && digitalRead(pinosSensores[4]) == LOW)) {
    contarQuadrados = false; // Parar a contagem de quadrados
    verificarQuadrado(); // Executa a ação de curva
    contagemQuadrados = 0;
    contarQuadrados = true;
  }

  // Continuar contando quadrados se a contagem estiver habilitada
  if (contarQuadrados) {

    // Verifica se o sensor central está ativo (detectando a linha)
    if (digitalRead(pinosSensores[2]) == HIGH) {
      // Se 1 segundo se passou desde a última verificação
      if (tempoAtual - ultimoTempo >= intervalo) {
        ultimoTempo = tempoAtual;

        // Verifica se o sensor direito extremo detecta um quadrado
        if (digitalRead(pinosSensores[4]) == HIGH && digitalRead(pinosSensores[3]) == LOW) {
          contagemQuadrados++; // Incrementa a contagem de quadrados
          lado = 1; // lado direito
        }
        if (digitalRead(pinosSensores[0]) == HIGH && digitalRead(pinosSensores[1]) == LOW) {
          contagemQuadrados++; // Incrementa a contagem de quadrados
          lado = 0; // lado esquerdo
        }
      }
    }
  }

  // Controle de motores com base nos sensores (seguindo a linha normalmente)
  if (digitalRead(pinosSensores[0]) == LOW && digitalRead(pinosSensores[1]) == LOW && digitalRead(pinosSensores[2]) == HIGH && digitalRead(pinosSensores[3]) == LOW && digitalRead(pinosSensores[4]) == LOW){
    analogWrite(pin1PWM, constrain(70, 1, 255));
    analogWrite(pin2PWM, constrain(70, 1, 255));
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, HIGH);
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, HIGH); 
  } else if (digitalRead(pinosSensores[0]) == LOW && digitalRead(pinosSensores[1]) == HIGH && digitalRead(pinosSensores[2]) == LOW && digitalRead(pinosSensores[3]) == LOW && digitalRead(pinosSensores[4]) == LOW){
    analogWrite(pin1PWM, constrain(34, 1, 255));
    analogWrite(pin2PWM, constrain(153, 1, 255));
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, HIGH);
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, HIGH); 
  } else if (digitalRead(pinosSensores[0]) == LOW && digitalRead(pinosSensores[1]) == LOW && digitalRead(pinosSensores[2]) == LOW && digitalRead(pinosSensores[3]) == HIGH && digitalRead(pinosSensores[4]) == LOW){
    analogWrite(pin1PWM, constrain(153, 1, 255));
    analogWrite(pin2PWM, constrain(34, 1, 255));
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, HIGH);
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, HIGH); 
  } else if (digitalRead(pinosSensores[0]) == HIGH && digitalRead(pinosSensores[1]) == LOW && digitalRead(pinosSensores[2]) == LOW && digitalRead(pinosSensores[3]) == LOW && digitalRead(pinosSensores[4]) == LOW){
    analogWrite(pin1PWM, constrain(15, 1, 255));
    analogWrite(pin2PWM, constrain(200, 1, 255));
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, HIGH);
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, HIGH); 
  } else if (digitalRead(pinosSensores[0]) == LOW && digitalRead(pinosSensores[1]) == LOW && digitalRead(pinosSensores[2]) == LOW && digitalRead(pinosSensores[3]) == LOW && digitalRead(pinosSensores[4]) == HIGH){
    analogWrite(pin1PWM, constrain(200, 1, 255));
    analogWrite(pin2PWM, constrain(15, 1, 255));
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, HIGH);
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, HIGH);
  } else {
    analogWrite(pin1PWM, constrain(69, 1, 255));
    analogWrite(pin2PWM, constrain(69, 1, 255));
    ci74HC595Write(bitMotor1A, LOW);
    ci74HC595Write(bitMotor1B, HIGH);
    ci74HC595Write(bitMotor2A, LOW);
    ci74HC595Write(bitMotor2B, HIGH); 
  }
}

unsigned long tempoAnterior = 0;
bool perdeuLinhaConfirmada = false;

bool perdeuLinha() {
    // Verifica se todos os sensores estão no estado LOW
    bool todosLow = true;
    for (int i = 0; i < 5; i++) {
        if (digitalRead(pinosSensores[i]) == HIGH) {
            todosLow = false;  // Se algum sensor estiver HIGH, interrompe a verificação
            perdeuLinhaConfirmada = false; // Reseta o status de "perdeu linha" confirmado
            return false;  // Se qualquer sensor estiver HIGH, retorna imediatamente
        }
    }

    // Se todos os sensores estiverem LOW, começa a contagem de tempo
    if (todosLow) {
        if (!perdeuLinhaConfirmada) {
            tempoAnterior = millis();  // Armazena o tempo inicial da verificação
            perdeuLinhaConfirmada = true;  // Marca que estamos verificando a perda da linha
        }
        // Verifica se os sensores ficaram LOW por pelo menos 0.3 segundos (300 ms)
        if (millis() - tempoAnterior >= 560) {
            return true;  // Retorna que perdeu a linha após 0.3 segundos consecutivos de LOW
        }
    }

    return false;  // Retorna false se os sensores não ficaram LOW por 0.3 segundos
}

void pararRobo()
{
    analogWrite(pin1PWM, 0);
    analogWrite(pin2PWM, 0);
}

void verificarQuadrado() {
  // Verifica se apenas um quadrado foi detectado
  if (contagemQuadrados == 1) {
    // Verifica se o quadrado está no sensor esquerdo ou direito
    if (lado == 1) { // Quadrado no sensor esquerdo
      // Parar o robô
      analogWrite(pin1PWM, 12);
      analogWrite(pin2PWM, 12);
      delay(280);

      // Girar à esquerda (90 graus)
      analogWrite(pin1PWM, 100);
      analogWrite(pin2PWM, 100);
      ci74HC595Write(bitMotor1A, HIGH);
      ci74HC595Write(bitMotor1B, LOW);
      ci74HC595Write(bitMotor2A, LOW);
      ci74HC595Write(bitMotor2B, HIGH);
      
      delay(380); // Tempo necessário para completar a curva de 90 graus

      // Voltar a seguir a linha
      analogWrite(pin1PWM, (velA-50));
      analogWrite(pin2PWM, (velB - 50));

    } else if (lado == 0) { // Quadrado no sensor direito
      // Parar o robô
      analogWrite(pin1PWM, 12);
      analogWrite(pin2PWM, 12);
      delay(280);

      // Girar à direita (90 graus)
      analogWrite(pin1PWM, 100);
      analogWrite(pin2PWM, 100);
      ci74HC595Write(bitMotor1A, LOW);
      ci74HC595Write(bitMotor1B, HIGH);
      ci74HC595Write(bitMotor2A, HIGH);
      ci74HC595Write(bitMotor2B, LOW);

      delay(380); // Tempo necessário para completar a curva de 90 graus

      // Voltar a seguir a linha
      analogWrite(pin1PWM, (velA-50));
      analogWrite(pin2PWM, (velB - 50));
    }
  } 
  contagemQuadrados = 0;
  contarQuadrados = true;
}


// void andando_de_re(){
//       analogWrite(pin1PWM, 0);
//       analogWrite(pin2PWM, 0);
//       delay(200);

//       // vai para tras e para um instante
//       analogWrite(pin1PWM, 150);
//       analogWrite(pin2PWM, 150);
//       ci74HC595Write(bitMotor1A, HIGH);
//       ci74HC595Write(bitMotor1B, LOW);
//       ci74HC595Write(bitMotor2A, HIGH);
//       ci74HC595Write(bitMotor2B, LOW);
//       delay(1000);

//       analogWrite(pin1PWM, 0);
//       analogWrite(pin2PWM, 0);
//       //verifica se ele esta do lado direito ou esquerdo
//       if(lado == 0){
//       analogWrite(pin1PWM, 150);
//       analogWrite(pin2PWM, 150);
//       ci74HC595Write(bitMotor1A, LOW);
//       ci74HC595Write(bitMotor1B, HIGH);
//       ci74HC595Write(bitMotor2A, LOW);
//       ci74HC595Write(bitMotor2B, HIGH);
//       delay(500);

//       // Girar à esquerda (90 graus)
//       analogWrite(pin1PWM, 250);
//       analogWrite(pin2PWM, 250);
//       ci74HC595Write(bitMotor1A, LOW);
//       ci74HC595Write(bitMotor1B, HIGH);
//       ci74HC595Write(bitMotor2A, HIGH);
//       ci74HC595Write(bitMotor2B, LOW);
      
//       delay(500); // Tempo necessário para completar a curva de 90 graus

//       // Voltar a seguir a linha
//       analogWrite(pin1PWM, velA);
//       analogWrite(pin2PWM, velB);
      
//       }else if(lado == 1){
//       analogWrite(pin1PWM, 150);
//       analogWrite(pin2PWM, 150);
//       ci74HC595Write(bitMotor1A, LOW);
//       ci74HC595Write(bitMotor1B, HIGH);
//       ci74HC595Write(bitMotor2A, LOW);
//       ci74HC595Write(bitMotor2B, HIGH);
//       delay(500);

//       // Girar à direita (90 graus)
//       analogWrite(pin1PWM, 250);
//       analogWrite(pin2PWM, 250);
//       ci74HC595Write(bitMotor1A, HIGH);
//       ci74HC595Write(bitMotor1B, LOW);
//       ci74HC595Write(bitMotor2A, LOW);
//       ci74HC595Write(bitMotor2B, HIGH);
      
//       delay(500); // Tempo necessário para completar a curva de 90 graus

//       // Voltar a seguir a linha
//       analogWrite(pin1PWM, velA);
//       analogWrite(pin2PWM, velB);
      
//       }
     
// }

// void Faixa_de_Pedestre(){
//       analogWrite(pin1PWM, 100);
//       analogWrite(pin2PWM, 116);
//       ci74HC595Write(bitMotor1A, LOW);
//       ci74HC595Write(bitMotor1B, HIGH);
//       ci74HC595Write(bitMotor2A, LOW);
//       ci74HC595Write(bitMotor2B, HIGH);
//       delay(1500);
//       analogWrite(pin1PWM, 0);
//       analogWrite(pin2PWM, 0);
//       ci74HC595Write(bitMotor1A, LOW);
//       ci74HC595Write(bitMotor1B, HIGH);
//       ci74HC595Write(bitMotor2A, LOW);
//       ci74HC595Write(bitMotor2B, HIGH);
//       delay(7000);
//       analogWrite(pin1PWM, 100);
//       analogWrite(pin2PWM, 116);
//       ci74HC595Write(bitMotor1A, LOW);
//       ci74HC595Write(bitMotor1B, HIGH);
//       ci74HC595Write(bitMotor2A, LOW);
//       ci74HC595Write(bitMotor2B, HIGH);
//       delay(1000);
// }

void ci74HC595Write(byte pino, bool estado) {
  static byte ciBuffer[qtdeCI];

  bitWrite(ciBuffer[pino / 8], pino % 8, estado);
  
  digitalWrite(pinST_CP, LOW); //Inicia a Transmissão
  
  digitalWrite(pinDS, LOW);    //Apaga Tudo para Preparar Transmissão
  digitalWrite(pinSH_CP, LOW);

  for (int nC = qtdeCI-1; nC >= 0; nC--) {
      for (int nB = 7; nB >= 0; nB--) {
  
          digitalWrite(pinSH_CP, LOW);  //Baixa o Clock      
          
          digitalWrite(pinDS,  bitRead(ciBuffer[nC], nB) );     //Escreve o BIT
          
          digitalWrite(pinSH_CP, HIGH); //Eleva o Clock
          digitalWrite(pinDS, LOW);     //Baixa o Data para Previnir Vazamento      
      }  
  }
  
  digitalWrite(pinST_CP, HIGH);  //Finaliza a Transmissão
}