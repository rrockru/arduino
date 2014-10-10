#define RED_PIN     11
#define GREEN_PIN   10
#define BLUE_PIN    9

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

int r = 0;
int g = 0;
int b = 0;

void rgb(int r, int g, int b) {
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);  
}

void loop()
{  
  int color,i,value,time=100;  // how long does it take each step
  color=random(1,4);    // which color to dim now 
  value=random(0,256);  // new value of that color
  switch(color) {
  case 1: 
    if(r>value) for(i=r;i>value;i--) {
      rgb(i,g,b); 
      delay(time); 
    }
    else for(i=r;i<value;i++) {
      rgb(i,g,b); 
      delay(time); 
    }
    r=value;
    break;
  case 2: 
    if(g>value) for(i=g;i>value;i--) {
      rgb(r,i,b); 
      delay(time); 
    }
    else for(i=g;i<value;i++) {
      rgb(r,i,b); 
      delay(time); 
    }
    g=value;
    break;
  case 3: 
    if(b>value) for(i=b;i>value;i--) {
      rgb(r,g,i); 
      delay(time); 
    }
    else for(i=b;i<value;i++) {
      rgb(r,g,i); 
      delay(time); 
    }
    b=value;
    break;
  } 
  delay(3000);   // some time before next change
}
