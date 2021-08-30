//display pins
int segA = 5;  // >>  11
int segB = 13; // >>  7
int segC = 10; // >>  4
int segD = 8;  // >>  2
int segE = 7;  // >>  1
int segF = 4;  // >>  10
int segG = 11; // >>  5
int segPt = 9; // >>  3
//------------//

//display digit
int d1 = 6;   // >> 12
int d2 = 3;   // >> 9
int d3 = 2;   // >> 8
int d4 = 12;  // >> 6
//------------//

int down = A1;    // decrement by 1 available parks
int up = A3;      // increment by 1 available parks

int down_value = 0;  // variable to store the value coming from the button
int up_value = 0;

int delayTime = 10; //delayTime <Don't change it, if you don't know where is it!>

int i=0;
int prev_value=0;
int value=0;
int state = 0;
int prev_down = 0;
int prev_up = 0;

int migl, cent, dec, uni;

//=============================================//
//init all pin used
void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}



//=============================================//
void loop() {
  
down_value = analogRead(down); // let's scale the value to 1/5
up_value = analogRead(up);

if(prev_down == 0 && prev_up == 0 )
        state = 1; 

if(up_value > 600 && state==1){
  value++;
  state = 0;
}
if(down_value > 600 && state == 1) {
  value --;
  state = 0;
  if(value<0) value=0;
  
}

uni= value %10; //separo le unitù
dec= (value%100)/10; //separo le decine
cent = (value%1000)/100; //separo le centinaia
migl = value/1000;
//Serial.println(uni);
//Serial.println(dec);
//Serial.println(cent);
//Serial.println(migl);
writeN(migl,cent,dec,uni);
if(value!= prev_value){
  Serial.println(value);
  prev_value =  value;
}

prev_down = down_value;
prev_up = up_value;

//down(1,0,2,4);
  
//all(5);
//zero(); 
//writeN(5,7,6,4);
//first(5); 
}



//=============================================//
//Write a Number - writeN(1,9,9,0) -> 1990
void writeN(int a,int b,int c,int d){
    
    if(a==0 && b==0 && c==0){
     selectDwriteL(4,d);
    return ;
    }

    if(a==0 && b==0){
      selectDwriteL(3,c);
      selectDwriteL(4,d);
      return;
    }

    if(a==0){
      selectDwriteL(2,b);
      selectDwriteL(3,c);
      selectDwriteL(4,d);
      return;
    }

    else {
      selectDwriteL(1,a);
      selectDwriteL(2,b);
      selectDwriteL(3,c);
      selectDwriteL(4,d);
      return;
    }
       
    
}

//=============================================//

//=============================================//
//Select Wich Digit (selectD) is going to Display (writeL)
void selectDwriteL(int d,int l){
  switch (d) { // choose a digit
    case 0: digitalWrite(d1, HIGH); //case 0 - All ON
            digitalWrite(d2, HIGH);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, HIGH);
            break;
    case 1: digitalWrite(d1, HIGH);//case 1 - Digit Number 1
            digitalWrite(d2, LOW);
            digitalWrite(d3, LOW);
            digitalWrite(d4, LOW);
            break;
    case 2: digitalWrite(d1, LOW);//case 2 - Digit Number 2
            digitalWrite(d2, HIGH);
            digitalWrite(d3, LOW);
            digitalWrite(d4, LOW);
            break;
    case 3: digitalWrite(d1, LOW);//case 1 - Digit Number 3
            digitalWrite(d2, LOW);
            digitalWrite(d3, HIGH);
            digitalWrite(d4, LOW);
            break;
    case 4: digitalWrite(d1, LOW);//case 1 - Digit Number 4
            digitalWrite(d2, LOW);
            digitalWrite(d3, LOW);
            digitalWrite(d4, HIGH);
            break;
  }

  switch (l) { // choose a Number
    case 0: zero();
            none();
            break;
    case 1: one();
            none();
            break;
    case 2: two();
            none();
            break;
    case 3: three();
            none();
            break;
    case 4: four();
            none();
            break;
    case 5: five();
            none();
            break;
    case 6: six();
            none();
            break;
    case 7: seven();
            none();
            break;
    case 8: eight();
            none();
            break;
    case 9: nine();
            none();
            break;
    case 10: point(); // print a Point
            break;
    case 11: none(); // make all them off !
            break;
  }

delayMicroseconds(delayTime); // delayTime for nice display of the Number !

}

//=============================================//
//shown one Number in the 4 Digit
void all(int n){
  selectDwriteL(0,n);
}
void first(int n){
  selectDwriteL(1,n); 
}

//=============================================//
void zero(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void one(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void two(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void three(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void four(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void five(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void six(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void seven(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void eight(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void nine(){
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segPt, HIGH);
}
//=============================================//
void point(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, LOW);
}
//=============================================//
void none(){
  digitalWrite(segA, HIGH);
  digitalWrite(segB, HIGH);
  digitalWrite(segC, HIGH);
  digitalWrite(segD, HIGH);
  digitalWrite(segE, HIGH);
  digitalWrite(segF, HIGH);
  digitalWrite(segG, HIGH);
  digitalWrite(segPt, HIGH);
}

void turn_off(){
            digitalWrite(d1, LOW);
            digitalWrite(d2, LOW);
            digitalWrite(d3, LOW);
            digitalWrite(d4, LOW);
}
