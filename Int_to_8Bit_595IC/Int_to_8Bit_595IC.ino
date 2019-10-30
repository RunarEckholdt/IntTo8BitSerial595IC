/*
  Runar Eckholdt

  1[Q1 ]|----|16[VCC]
  2[Q2 ]|    |15[Q0]
  3[Q3 ]|    |14[DATA]
  4[Q4 ]|    |13[ENABLE] GND
  5[Q5 ]|    |12[STORE]
  6[Q6 ]|    |11[CLK]
  7[Q7 ]|    |10[RESET] Must stay high at all times unless you want to reset
  8[GND]|____|9 [CHAIN/Q7]




*/


const byte data = 13;
const byte clk = 12;
const byte store = 11;

byte sepNums;

void setup() {
  Serial.begin(9600);
  antNums();

  pinMode(data, OUTPUT);
  pinMode(clk, OUTPUT);
  pinMode(store, OUTPUT);
  digitalWrite(data, LOW);
  digitalWrite(clk, LOW);
  digitalWrite(store, HIGH);
  
}

void loop() {
  shift();

}



int shift() {
  int numbers [sepNums];
  for (byte i = 0; i < sepNums; i++) {
    numbers[i] = getNumber(i+1);
  }
  int number = mergeNumbers(numbers);
  printNumbers(numbers);
  doShift(number);
}

void printNumbers(int numbers[]){
  for (int i = 0; i<sepNums;i++){
    Serial.print(numbers[i]);
    Serial.print(" = ");
    Serial.println(numbers[i],BIN);
    }
  }

int mergeNumbers(int numbers []){
  if(sepNums==1){
    return numbers[0];
    }
  else if(sepNums==2){
    int numb1=numbers[0]<<4;
    return numb1|numbers[1];
    }
  else if(sepNums==4){
    int numb1 = numbers[0]<<6;
    int numb2 = numbers[1]<<4;
    int numb3 = numbers[2]<<2;
    return numb1|numb2|numb3|numbers[3];
    
    }
  }


void antNums() {
  Serial.print("How many seperate numbers?: ");
  while (!Serial.available());
  byte input = Serial.parseInt();
  if (8 % input == 0) {
    Serial.println(input);
    sepNums = input;
  } else {
    Serial.println("Not valid");
    Serial.println("Answer of 8 mod (input) must be 0");
    Serial.print("In this case ");
    Serial.print("8");
    Serial.print(" mod ");
    Serial.print(input);
    Serial.print(" = ");
    Serial.println(8 % input);
    antNums();
  }
}

byte getNumber(byte i) {
  //getting a number from the Serial
  byte num;
  Serial.print("Insert number ");
  Serial.print(i);
  Serial.print(": ");
  while (!Serial.available());
  num = Serial.parseInt();

  if (num < pow(2, 8 / sepNums)) {
    Serial.println(num);
    return num;
  } else {
    Serial.println("Outside bitrange");
    getNumber(i);
  }

}
  void doStore() {
    digitalWrite(store, LOW);
    digitalWrite(store, HIGH);
  }

  void doShift(int number) {
    digitalWrite(store, LOW);
    //for (int i = 0; i < sepNums;i++) {
      shiftOut(data, clk, LSBFIRST, number);
      Serial.print(number);
      Serial.print(" = ");
      Serial.println(number,BIN);
    //}
    digitalWrite(store, HIGH);
  }
