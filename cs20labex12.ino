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
const int tens3 = 3;
const int tens2 = 4;
const int tens1 = 5;
const int tens0 = 6;
const int ones3 = 7;
const int ones2 = 8;
const int ones1 = 9;
const int ones0 = 10;
const int ldr = 2;
const int modeSwitch = 1;

//important variables
bool countdown = false;
bool mode = true; //TRUE is SET, FALSE is RESET
int currentCount = 99;
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
  pinMode(ldr, INPUT);
  attachInterrupt(0, willCountdown, CHANGE);
  attachInterrupt(3, changeMode, CHANGE);
  Serial.begin(9600);
}

void setDisplay(int numberToSet)
{
  int setTens = numberToSet / 10;
  int setOnes = numberToSet % 10;
  Serial.println(currentCount);
  digitalWrite(tens3, bcdValues[setTens][3]);
  digitalWrite(tens2, bcdValues[setTens][2]);
  digitalWrite(tens1, bcdValues[setTens][1]);
  digitalWrite(tens0, bcdValues[setTens][0]);
  digitalWrite(ones3, bcdValues[setOnes][3]);
  digitalWrite(ones2, bcdValues[setOnes][2]);
  digitalWrite(ones1, bcdValues[setOnes][1]);
  digitalWrite(ones0, bcdValues[setOnes][0]);
}

void changeMode()
{
  mode = (digitalRead(modeSwitch));
  if(mode) //when going to SET mode
  {
    currentCount = 0;
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
  if()//SET
  {
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
  }
}
