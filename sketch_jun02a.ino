const int motor1pin1 = 2;
const int motor1pin2 = 3;
const int motor2pin1 = 4;
const int motor2pin2 = 5;

//const int speed1 = 9;
//const int speed2 = 10;
int mySpeed = 100;
int defSpeed = 100;
int delay_long = 400;
int delay_short = 800;
int ok = 0;

int prev_l = 0;
int cur_l = 1;

void setup() {  
  pinMode(13, OUTPUT);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
//  pinMode(speed1, OUTPUT); 
//  pinMode(speed2, OUTPUT);
  Serial.begin(9600);
  
  while (!Serial);
  Serial.println("Input 1 to Turn LED on and 2 to off");
  Serial.println("Input W(FORWARD), A(LEFT), S(BACK), D(RIGHT) ");
}

void loop() {
//  analogWrite(speed1, mySpeed); //ENA pin
//  analogWrite(speed2, mySpeed); //ENB pin
  if (Serial.available())
  {
    char comand = Serial.read();
    if (comand == 'w') {
      Serial.print("FORWARD\n");
      W_forward();
    } else if (comand == 's') {
      Serial.print("BACKWARDS\n");
      S_back();
    } else if (comand == 'd') {
      Serial.print("RIGHT\n");
      D_right();
    } else if (comand == 'a') {
      Serial.print("LEFT\n");
      A_left();
    } else if (comand == 'q') {
      ok = 1;
      Serial.print("Mode changed (short distance)\n");
    } else if (comand == 'e') {
      Serial.print("Mode changed (non-stop moving)\n");
      ok = 0;
      //delay_short = 
    } else if (comand == 'f') {
      Serial.print("STOP\n");
      Stop();
    }
  }
}

void Stop() {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, HIGH);
  
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, HIGH);
}
void W_forward() {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
      delay(delay_long);
    if (ok == 1) {
      Stop();
    }
}

void A_left()
{
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
  
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    delay(delay_short);
    if (ok == 0)
      W_forward();
    else
      Stop();
}

void D_right()
{
  if (prev_l != cur_l) {
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    
    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    delay(delay_short);
    if (ok == 0)
    W_forward();
    else
      Stop();
  }  
}

void S_back(){
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
  
    digitalWrite(motor2pin1, LOW);
    digitalWrite(motor2pin2, HIGH);
    delay(delay_long);
    if (ok == 1) {
      Stop();
    }
    //else
      //delay(delay_long); 
}
