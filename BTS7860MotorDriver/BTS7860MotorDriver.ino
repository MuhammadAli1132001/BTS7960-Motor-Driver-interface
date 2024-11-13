#include <Arduino.h>
#define RPM 125
#define Push_Enable 11      // Button to initiate the process

int M1_R_Pwm = 5;
int M1_L_Pwm = 6;
int M2_R_Pwm = 10;
int M2_L_Pwm = 9;

int R_IS = 8;
int L_IS = 7;
int R_EN = 11;
int L_EN = 12;

bool initialStart = false;
uint8_t state = 0;
unsigned long startTime = 0;
const unsigned long runDuration = 15000;   // 15 seconds
const unsigned long stopDuration = 4000;   // 4 seconds

void Started(void);
void Move_forward(void);
void Move_reverse(void);
void Stop();

void setup()
{
  pinMode(Push_Enable, INPUT);
  Serial.begin(115200);

  pinMode(M1_R_Pwm, OUTPUT);
  pinMode(M1_L_Pwm, OUTPUT);
  pinMode(M2_R_Pwm, OUTPUT);
  pinMode(M2_L_Pwm, OUTPUT);

  pinMode(R_IS, OUTPUT);
  pinMode(L_IS, OUTPUT);
  pinMode(R_EN, OUTPUT);
  pinMode(L_EN, OUTPUT);

  digitalWrite(R_EN, HIGH);
  digitalWrite(L_EN, HIGH);
  digitalWrite(R_IS, LOW);
  digitalWrite(L_IS, LOW);

  delay(100);
}

void loop()
{
  Started();

  unsigned long currentTime = millis();

  switch (state)
  {
    case 1: // Move forward state
      if (currentTime - startTime < runDuration) {
        Move_forward();
      } else {
        Stop();
        startTime = currentTime;  // Reset the start time
        state = 2;                // Transition to stop before reversing
      }
      break;

    case 2: // Stop state after forward movement
      if (currentTime - startTime < stopDuration) {
        Stop();
      } else {
        startTime = currentTime;
        state = 3;                // Transition to reverse movement
      }
      break;

    case 3: // Move reverse state
      if (currentTime - startTime < runDuration) {
        Move_reverse();
      } else {
        Stop();
        startTime = currentTime;
        state = 0;                // Return to idle state
      }
      break;

    default: // Idle state, waiting for button press
      Stop();
      break;
  }

  delay(10);
}

void Started()
{
  if (!digitalRead(Push_Enable) && state == 0)  // Start only if in idle state
  {
    Serial.println("Enabled button is Pressed");
    state = 1;
    startTime = millis();
  }
}

void Stop()
{
  Serial.println("The motor is currently stopped");
  analogWrite(M1_L_Pwm, 0);
  analogWrite(M1_R_Pwm, 0);
  analogWrite(M2_L_Pwm, 0);
  analogWrite(M2_R_Pwm, 0);
}

void Move_forward()
{
  if (!initialStart)
  {
    for (int i = 0; i <= RPM; i++)
    {
      analogWrite(M1_R_Pwm, 0);
      analogWrite(M1_L_Pwm, i);
      analogWrite(M2_R_Pwm, 0);
      analogWrite(M2_L_Pwm, i);
      delay(20);
    }
    initialStart = true;
  }
  else
  {
    analogWrite(M2_L_Pwm, RPM);
    analogWrite(M1_L_Pwm, RPM);
  }
}

void Move_reverse()
{
  if (!initialStart)
  {
    for (int i = 0; i <= RPM; i++)
    {
      analogWrite(M1_R_Pwm, i);
      analogWrite(M1_L_Pwm, 0);
      analogWrite(M2_R_Pwm, i);
      analogWrite(M2_L_Pwm, 0);
      delay(20);
    }
    initialStart = true;
  }
  else
  {
    analogWrite(M1_R_Pwm, RPM);
    analogWrite(M2_R_Pwm, RPM);
  }
}
