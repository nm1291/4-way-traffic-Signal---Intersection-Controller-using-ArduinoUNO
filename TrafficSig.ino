//4 way Traffic Signal Controller
//By Nikhil Mascarenhas ( nikhil.mascarenhas@gmail.com )
//Feel free to use, distribute and modify this code.
//Demo Video: www.youtube.com
//Code is hosted at: 

//4 x 3 matrix rows represents  the traffic signals for the 4 roads
//columns represent red, yellow, green.
int sig[4][3] = {13,12,11,10,9,8,7,6,5,4,3,2};

//buzzer can be used if required
int buz = 1;


void setup()
{  
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<3;j++)
      pinMode(sig[i][j], OUTPUT);
  pinMode(buz,OUTPUT);
}

//defines signal statuses when 'k' th  road is green
void stateGo(int k)
{
   //buzzer is off
   analogWrite(buz,0); 
   //all lights are turned off for a fraction of a second.
   int i,j;
    for(i=0;i<4;i++)
      for(j=0;j<3;j++)
        digitalWrite(sig[i][j],LOW);
        
    //all roads except the 'k'th road is red.
    for(i=0;i<4;i++)
      if(i!=k)
        digitalWrite(sig[i][0],HIGH);
    
    //kth road is green.
    digitalWrite(sig[k][2],HIGH);
    
    //wait 24 seconds
    delay(24000);
    
    //blink green as a "hurry up" warning for next 6 seconds
    for(i=0;i<6;i++)
    {
      digitalWrite(sig[k][2],LOW);
      delay(500);
      digitalWrite(sig[k][2],HIGH);
      delay(500);
    }
}

//defines signal statuses when the 'k' th signal is "ready to go"
//'k-1'th signal is returning from green.
void statePause(int k)
{
  int i,j;
  int p = k-1;
  if(p==-1)
    p=3;
    
  //turn off all lights for a fraction of a second.
  for(i=0;i<4;i++)
      for(j=0;j<3;j++)
        digitalWrite(sig[i][j],LOW);
        
  //all red lights except p (i.e k-1) are red.
  for(i=0;i<4;i++)
    if(i!=p)
          digitalWrite(sig[i][0], HIGH);
  
  //also  p and k roads have yellow
  digitalWrite(sig[p][1],HIGH);
  digitalWrite(sig[k][1],HIGH);
  
  //for 5 seconds switch off and switch on buzzer.
  for(i=0;i<10;i++)
  {
    analogWrite(buz,255);
    delay(250);
    analogWrite(buz,0);
    delay(250);
  }
}
void loop()
{
  stateGo(0);
  statePause(1);
  stateGo(1);
  statePause(2);
  stateGo(2);
  statePause(3);
  stateGo(3);
  statePause(0);
}
