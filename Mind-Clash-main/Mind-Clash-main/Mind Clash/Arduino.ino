#include <Arduino.h>

// LED pin definitions
const int ledEsquerdoPins[4] = {13, 12, 11, 10}; // Pinos dos LEDs esquerdos (azul, verde, amarelo, vermelho)
const int ledDireitoPins[4] = {1, 2, 3, 4};     // Pinos dos LEDs direitos (amarelo, vermelho, azul, verde)

// Buzzer pin definitions
const int buzzerEsquerdo = 9; // Pino do buzzer esquerdo
const int buzzerDireito = 5;  // Pino do buzzer direito

// Joystick pin definitions
const int joystickX1 = A0; // Pino analógico do joystick 1 (eixo X)
const int joystickY1 = A1; // Pino analógico do joystick 1 (eixo Y)
const int joystickX2 = A2; // Pino analógico do joystick 2 (eixo X)
const int joystickY2 = A3; // Pino analógico do joystick 2 (eixo Y)

// Game variables
int sequenceLength = 4; // Comprimento inicial da sequência
int currentLED = 0;     // LED atual na sequência
int playerLED = 0;      // LED atual do jogador
int score = 0;          // Pontuação do jogador
bool gameInProgress = false; // Estado do jogo

// Sons para cada LED (exemplo com frequências)
const int leftSounds[4] = {1000, 1200, 1400, 1600}; // Sons para LEDs esquerdos
const int rightSounds[4] = {2000, 2200, 2400, 2600}; // Sons para LEDs direitos

// Protótipo da função showSequence
void showSequence(int sequence[]);

// Função para acender um LED
void lightLED(int ledPin, bool isLeft = true) {
  if (isLeft) {
    digitalWrite(ledEsquerdoPins[ledPin], HIGH);
  } else {
    digitalWrite(ledDireitoPins[ledPin], HIGH);
  }
}

// Função para apagar um LED
void turnOffLED(int ledPin, bool isLeft = true) {
  if (isLeft) {
    digitalWrite(ledEsquerdoPins[ledPin], LOW);
  } else {
    digitalWrite(ledDireitoPins[ledPin], LOW);
  }
}

// Função para tocar um som para um LED específico
void playSound(int ledPin, bool isLeft = true) {
  if (isLeft) {
    tone(buzzerEsquerdo, leftSounds[ledPin]);
    delay(500); // Tempo para tocar o som
    noTone(buzzerEsquerdo);
  } else {
    tone(buzzerDireito, rightSounds[ledPin]);
    delay(500); // Tempo para tocar o som
    noTone(buzzerDireito);
  }
}

// Função para mostrar o menu principal
void displayMainMenu() {
  Serial.println("Jogo da Memória com LEDs e Joysticks");
  Serial.println("Pressione o botão de iniciar para começar o jogo.");

  // Verifica se o botão de iniciar foi pressionado
  int joystickX1Value = analogRead(joystickX1);
  if (joystickX1Value > 500) {
    startGame(); // Inicia o jogo
  }
}

// Função para iniciar o jogo
void startGame() {
  gameInProgress = true;
  score = 0;
  sequenceLength = 4;

  // Gera uma sequência aleatória
  int sequence[sequenceLength];
  for (int i = 0; i < sequenceLength; i++) {
    sequence[i] = random(0, 8); // 0-3 para LEDs esquerdos, 4-7 para LEDs direitos
  }

  // Mostra a sequência para o jogador
  showSequence(sequence);
}

// Função para verificar a entrada do jogador e a lógica do jogo
void playGame() {
  while (playerLED < sequenceLength) {
    // Lê os valores dos joysticks
    int joystickX1Value = analogRead(joystickX1);
    int joystickY1Value = analogRead(joystickY1);
    int joystickX2Value = analogRead(joystickX2);
    int joystickY2Value = analogRead(joystickY2);

    // Verifica a direção do joystick esquerdo
    if (joystickX1Value < 100) {
      lightLED(0, true); // Liga o LED azul esquerdo
      playSound(0, true); // Toca o som do LED azul esquerdo
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(0, true); // Apaga o LED azul esquerdo
      playerLED++;
    } else if (joystickX1Value > 900) {
      lightLED(1, true); // Liga o LED verde esquerdo
      playSound(1, true); // Toca o som do LED verde esquerdo
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(1, true); // Apaga o LED verde esquerdo
      playerLED++;
    } else if (joystickY1Value < 100) {
      lightLED(2, true); // Liga o LED amarelo esquerdo
      playSound(2, true); // Toca o som do LED amarelo esquerdo
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(2, true); // Apaga o LED amarelo esquerdo
      playerLED++;
    } else if (joystickY1Value > 900) {
      lightLED(3, true); // Liga o LED vermelho esquerdo
      playSound(3, true); // Toca o som do LED vermelho esquerdo
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(3, true); // Apaga o LED vermelho esquerdo
      playerLED++;
    }

    // Verifica a direção do joystick direito
    if (joystickX2Value < 100) {
      lightLED(2, false); // Liga o LED amarelo direito
      playSound(2, false); // Toca o som do LED amarelo direito
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(2, false); // Apaga o LED amarelo direito
      playerLED++;
    } else if (joystickX2Value > 900) {
      lightLED(3, false); // Liga o LED vermelho direito
      playSound(3, false); // Toca o som do LED vermelho direito
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(3, false); // Apaga o LED vermelho direito
      playerLED++;
    } else if (joystickY2Value < 100) {
      lightLED(0, false); // Liga o LED azul direito
      playSound(0, false); // Toca o som do LED azul direito
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(0, false); // Apaga o LED azul direito
      playerLED++;
    } else if (joystickY2Value > 900) {
      lightLED(1, false); // Liga o LED verde direito
      playSound(1, false); // Toca o som do LED verde direito
      delay(300); // Pequeno atraso para evitar leituras múltiplas
      turnOffLED(1, false); // Apaga o LED verde direito
      playerLED++;
    }

    // Verifica se o botão do joystick foi pressionado
    if (digitalRead(joystickX1) == HIGH) {
      // Finaliza o jogo
      gameInProgress = false;
      Serial.println("Jogo encerrado.");
      Serial.print("Pontuação final: ");
      Serial.println(score);
      break;
    }
  }
}

// Função para mostrar a sequência de LEDs e sons
void showSequence(int sequence[]) {
  for (int i = 0; i < sequenceLength; i++) {
    int ledIndex = sequence[i];

    // Determina se o LED é esquerdo ou direito
    bool isLeft = (ledIndex < 4);

    // Acende o LED e toca o som correspondente
    lightLED(ledIndex % 4, isLeft);
    playSound(ledIndex % 4, isLeft);
    delay(1000); // Delay entre cada LED na sequência

    // Apaga o LED após o delay
    turnOffLED(ledIndex % 4, isLeft);
    delay(500); // Delay entre cada LED apagado
  }
}

void setup() {
  // Inicializa os pinos dos LEDs como saída
  for (int i = 0; i < 4; i++) {
    pinMode(ledEsquerdoPins[i], OUTPUT);
    pinMode(ledDireitoPins[i], OUTPUT);
  }

  // Inicializa o pino do buzzer como saída
  pinMode(buzzerEsquerdo, OUTPUT);
  pinMode(buzzerDireito, OUTPUT);

  // Inicializa o pino do botão do joystick como entrada
  pinMode(joystickX1, INPUT);
}

void loop() {
  if (!gameInProgress) {
    displayMainMenu(); // Mostra o menu principal quando o jogo não está em andamento
  } else {
    playGame(); // Inicia o jogo quando estiver em andamento
  }
}
