#include <Arduino.h>

const int ledEsquerdoPins[4] = {13, 12, 11, 10}; // Pinos dos LEDs esquerdos (azul, verde, amarelo, vermelho)
const int ledDireitoPins[4] = {1, 2, 3, 4};     // Pinos dos LEDs direitos (amarelo, vermelho, azul, verde)

const int buzzerEsquerdo = 9; // Pino do buzzer esquerdo
const int buzzerDireito = 5;  // Pino do buzzer direito

const int joystickX1 = A0; // Pino analógico do joystick 1 (eixo X)
const int joystickY1 = A1; // Pino analógico do joystick 1 (eixo Y)
const int joystickX2 = A2; // Pino analógico do joystick 2 (eixo X)
const int joystickY2 = A3; // Pino analógico do joystick 2 (eixo Y)

int sequenceLength = 4; // Comprimento inicial da sequência
int currentLED = 0;     // LED atual na sequência
int playerLED = 0;      // LED atual do jogador
int score1 = 0;         // Pontuação do jogador 1
int score2 = 0;         // Pontuação do jogador 2
bool gameInProgress = false; // Estado do jogo

const int leftSounds[4] = {1000, 1200, 1400, 1600}; // Sons para LEDs esquerdos
const int rightSounds[4] = {2000, 2200, 2400, 2600}; // Sons para LEDs direitos

void showSequence(int sequence[]);

void lightLED(int ledPin, bool isLeft = true) {
  if (isLeft) {
    digitalWrite(ledEsquerdoPins[ledPin], HIGH);
  } else {
    digitalWrite(ledDireitoPins[ledPin], HIGH);
  }
}

void turnOffLED(int ledPin, bool isLeft = true) {
  if (isLeft) {
    digitalWrite(ledEsquerdoPins[ledPin], LOW);
  } else {
    digitalWrite(ledDireitoPins[ledPin], LOW);
  }
}

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

void displayMainMenu() {
  Serial.println("Jogo da Memória com LEDs e Joysticks");
  Serial.println("Pressione o botão de iniciar para começar o jogo.");

  int joystickX1Value = analogRead(joystickX1);
  if (joystickX1Value > 500) {
    startGame(); // Inicia o jogo
  }
}

void startGame() {
  gameInProgress = true;
  score1 = 0;
  score2 = 0;
  sequenceLength = 4;

  int sequence[sequenceLength];
  for (int i = 0; i < sequenceLength; i++) {
    sequence[i] = random(0, 8); // 0-3 para LEDs esquerdos, 4-7 para LEDs direitos
  }

  showSequence(sequence);
}

void playGame() {
  while (playerLED < sequenceLength) {
    int joystickX1Value = analogRead(joystickX1);
    int joystickY1Value = analogRead(joystickY1);
    int joystickX2Value = analogRead(joystickX2);
    int joystickY2Value = analogRead(joystickY2);

    if (joystickX1Value < 100) {
      lightLED(0, true);
      playSound(0, true);
      delay(300);
      turnOffLED(0, true);
      playerLED++;
      score1 += 10;
    } else if (joystickX1Value > 900) {
      lightLED(1, true);
      playSound(1, true);
      delay(300);
      turnOffLED(1, true);
      playerLED++;
      score1 += 10;
    } else if (joystickY1Value < 100) {
      lightLED(2, true);
      playSound(2, true);
      delay(300);
      turnOffLED(2, true);
      playerLED++;
      score1 += 10;
    } else if (joystickY1Value > 900) {
      lightLED(3, true);
      playSound(3, true);
      delay(300);
      turnOffLED(3, true);
      playerLED++;
      score1 += 10;
    }

    if (joystickX2Value < 100) {
      lightLED(2, false);
      playSound(2, false);
      delay(300);
      turnOffLED(2, false);
      playerLED++;
      score2 += 10;
    } else if (joystickX2Value > 900) {
      lightLED(3, false);
      playSound(3, false);
      delay(300);
      turnOffLED(3, false);
      playerLED++;
      score2 += 10;
    } else if (joystickY2Value < 100) {
      lightLED(0, false);
      playSound(0, false);
      delay(300);
      turnOffLED(0, false);
      playerLED++;
      score2 += 10;
    } else if (joystickY2Value > 900) {
      lightLED(1, false);
      playSound(1, false);
      delay(300);
      turnOffLED(1, false);
      playerLED++;
      score2 += 10;
    }
  }

  if (playerLED >= sequenceLength) {
    gameInProgress = false;
    updateScores();
  }
}

void showSequence(int sequence[]) {
  for (int i = 0; i < sequenceLength; i++) {
    if (sequence[i] < 4) {
      lightLED(sequence[i], true);
      playSound(sequence[i], true);
      delay(300);
      turnOffLED(sequence[i], true);
    } else {
      lightLED(sequence[i] - 4, false);
      playSound(sequence[i] - 4, false);
      delay(300);
      turnOffLED(sequence[i] - 4, false);
    }
    delay(300);
  }

  playerLED = 0;
  playGame();
}

void updateScores() {
  Serial.print("Player 1: ");
  Serial.println(score1);
  Serial.print("Player 2: ");
  Serial.println(score2);
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(ledEsquerdoPins[i], OUTPUT);
    pinMode(ledDireitoPins[i], OUTPUT);
  }

  pinMode(buzzerEsquerdo, OUTPUT);
  pinMode(buzzerDireito, OUTPUT);

  displayMainMenu();
}

void loop() {
  if (gameInProgress) {
    playGame();
  }
}
