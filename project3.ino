//bcd values for 0-9
//index 0 is MSB
int bcdValues[10][4] = 
{
{0, 0, 0, 0},
{1, 0, 0, 0},
{0, 1, 0, 0},
{1, 1, 0, 0},
{0, 0, 1, 0},
{1, 0, 1, 0},
{0, 1, 1, 0},
{1, 1, 1, 0},
{0, 0, 0, 1},
{1, 0, 0, 1},
};

//pin definitions
const int tens3 = 4;
const int tens2 = 5;
const int tens1 = 6;
const int tens0 = 7;
const int ones3 = 8;
const int ones2 = 9;
const int ones1 = 10;
const int ones0 = 11;
const int ldr = 2;
const int modeSwitch = 3;
const int tensUp = A0;
const int tensDown = A1;
const int onesUp = A2;
const int onesDown = A3;
const int buzzer = 12;

//important variables
bool countdown = false;
bool mode = true; //TRUE is SET, FALSE is RESET
int currentCount = 99;
int setTens = 0;
int setOnes = 0;
unsigned long timebefore = 0;
unsigned long timeafter = 0;
unsigned long interval = 1000;

void setup() 
{
  pinMode(tens3, OUTPUT);
  pinMode(tens2, OUTPUT);
  pinMode(tens1, OUTPUT);
  pinMode(tens0, OUTPUT);
  pinMode(ones3, OUTPUT);
  pinMode(ones2, OUTPUT);
  pinMode(ones1, OUTPUT);
  pinMode(ones0, OUTPUT);
  pinMode(tensUp, INPUT);
  pinMode(tensDown, INPUT);
  pinMode(onesUp, INPUT);
  pinMode(onesDown, INPUT);
  pinMode(ldr, INPUT);
  pinMode(modeSwitch, INPUT);
  pinMode(buzzer, OUTPUT);
  attachInterrupt(0, willCountdown, CHANGE);
  attachInterrupt(1, changeMode, CHANGE);
  Serial.begin(9600);
}

void setDisplay(int numberToSet)
{
  int setTens = numberToSet / 10;
  int setOnes = numberToSet % 10;
  Serial.println(currentCount);
  digitalWrite(tens3, bcdValues[setTens][3]); digitalWrite(tens2, bcdValues[setTens][2]);
  digitalWrite(tens1, bcdValues[setTens][1]);
  digitalWrite(tens0, bcdValues[setTens][0]);
  digitalWrite(ones3, bcdValues[setOnes][3]);
  digitalWrite(ones2, bcdValues[setOnes][2]);
  digitalWrite(ones1, bcdValues[setOnes][1]);
  digitalWrite(ones0, bcdValues[setOnes][0]);
}

void buzzOn()
{
  digitalWrite(buzzer, HIGH);
}

void buzzOff()
{
  digitalWrite(buzzer, LOW);
}

void changeMode()
{
  mode = (digitalRead(modeSwitch));
  if(mode) //when going to SET mode
  {
    currentCount = 0;
    setTens = 0;
    setOnes = 0;
    buzzOff();
    Serial.println("SET MODE");
  }
  else
  {
    Serial.println("RUN MODE");
  }
  setDisplay(currentCount);
}

void willCountdown()
{
  countdown = (digitalRead(ldr));
  timebefore = timeafter;
  Serial.println(countdown);
}

void loop() 
{
  if(mode)//SET
  {
    if(digitalRead(tensUp) && setTens < 9)
    {
      setTens++;
    }
    if(digitalRead(tensDown) && setTens > 0)
    {
      setTens--;
    }
    if(digitalRead(onesUp) && setOnes < 9)
    {
      setOnes++;
    }
    if(digitalRead(onesDown) && setOnes > 0)
    {
      setOnes--;
    }
    currentCount = (setTens * 10) + setOnes;
    setDisplay(currentCount);
  }
  else//RUN
  {
    while(currentCount != 0)
    {
      timeafter = millis();
      if(!countdown)
      {
        timebefore = timeafter;
      }
      Serial.println(timeafter - timebefore);
      if(countdown && (timeafter - timebefore >= 1000))
      {
        timebefore = timeafter;
        currentCount--;
        setDisplay(currentCount);
      }
    }
    if(currentCount == 0)
    {
      buzzOn();
    }
  }
}
