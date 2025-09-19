int ENA = 11; 
int IN1 = 13;
int IN2 = 12;

int ENB = 9; 
int IN3 = 8;
int IN4 = 7;

int CENTER = 3;
int RIGHT = 4;
int LEFT = 5;

int SAMPLE = 5;
int SAMPLE_DELAY = 2;

const bool SENSOR_ACTIVE_LOW_ON_BLACK = false;
const int fast = 255;
const int slow = 150;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(CENTER, INPUT);
  pinMode(RIGHT, INPUT);
  pinMode(LEFT, INPUT);
}

bool sensor_active(int pin)
{
  int sum = 0;
  for(int i = 0; i <= SAMPLE; i++)
  {
    sum += digitalRead(pin);
    delay(SAMPLE_DELAY);
  }
  int majority = (sum > (SAMPLE/2)+1 ) ? HIGH : LOW;
  if(SENSOR_ACTIVE_LOW_ON_BLACK)
    {
      return(majority == LOW);
    }
    else
    {
      return (majority == HIGH);
    } 
}

void stop_motor()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void forward(int left_motor, int right_motor)  // speed of the both motor will come here 
{
  //left motor
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // right motor
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  
  analogWrite(ENA,left_motor);
  analogWrite(ENB,right_motor);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  bool c = sensor_active(CENTER);
  bool r = sensor_active(RIGHT);
  bool l = sensor_active(LEFT);
  
  if(!c && r && l)
  {
    forward(fast,fast);
    Serial.println("forward");
  }
  else if(!r && c && l)
  {
    forward(fast, slow);
    Serial.println("right");
  }
  else if(!l && c && r)
  {
    forward(slow,fast);
    Serial.println("left");
  }
  else if(!r && !c && l)
  {
    forward(fast, (fast+slow)/2);
    Serial.println("slight right");
  }
  else if(!l && !c && r)
  {
    forward(slow, (fast+slow));
    Serial.println("slight left");
  }
  else if  (!c && !r && !l)
  {
    stop_motor();
    Serial.println("two paths");
  }
  else 
  {
    stop_motor();
  }
delay(40);
}
