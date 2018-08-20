//boolean opf = false;

void ckflag(){
//  if((PM_Warning >= 2)||(CO_Warning >= 2)||(CO2_Warning >= 2)||(LPG_Warning >= 2)){opf = true;}
  if((CO_Warning >= 2)){opf = true;}
  }
void BT_setup(){
  Serial1.begin(38400);
}

void HBridge_setup(){
  pinMode(HB1_pin, OUTPUT);
  pinMode(HB2_pin, OUTPUT);
  pinMode(HB3_pin, OUTPUT);
  digitalWrite(HB1_pin, LOW);
  digitalWrite(HB2_pin, LOW);
  digitalWrite(HB3_pin, LOW);
}

void Buzzer_setup(){
  pinMode(Buzzer_pin, OUTPUT);
}
void Buzz(){
  digitalWrite(Buzzer_pin, HIGH);
}
void Silence(){
  digitalWrite(Buzzer_pin, LOW);
}

void Open_Fan(){
  Serial1.print("A:1");
  //Serial.println("Open Fan !");
}
void Close_Fan(){
  Serial1.print("A:0");
  //Serial.println("Close Fan !");
}
void Open_Window(){
  digitalWrite(HB1_pin, HIGH);
  digitalWrite(HB2_pin, HIGH);
  digitalWrite(HB3_pin, HIGH);
//  Serial1.print("A:1");
  //Serial1.print("B:1");
  //Serial.println("Open Window !");
}
void Close_Window(){
  digitalWrite(HB1_pin, HIGH);
  digitalWrite(HB2_pin, HIGH);
  digitalWrite(HB3_pin, LOW);
//  Serial1.print("A:0");
  //Serial1.print("B:0");
  //Serial.println("Close Window !");
}

//byte PM_Warning = 0;   // 50, 100, 150
//byte CO_Warning = 0;   // 35, 50, 125
//byte CO2_Warning = 0;  // 700, 1000, 2500
//byte LPG_Warning = 0;  // 1000, 1500, 2500
void Check_Warning(){
  static int cnt = 0;
  if(cnt > Send_BT_Confidence){
    ckflag();
//    if((PM_Warning==3)||(CO_Warning==3)||(CO2_Warning==3)||(LPG_Warning==3)){
//    if((PM_Warning>=4)||(CO_Warning >= 4)||(CO2_Warning >= 4)){
    if((CO_Warning>=4)){
      if(opf == true){
//        Open_Fan();
        Open_Window();
      }
//      Open_Fan();
//      Open_Window();
//      Buzz();
    }
//    else if((PM_Warning >= 1)||(CO_Warning >= 1)||(CO2_Warning >= 1)||(LPG_Warning >= 1)){
//    else if((PM_Warning >= 2)||(CO_Warning >= 2)||(CO2_Warning >= 2)){
    else if((CO_Warning >= 2)){    
      if(opf == true){
//        Open_Fan();
        Open_Window();
//        Silence();
      }
    }
//    else if((PM_Warning == 1)||(CO_Warning == 1)||(CO2_Warning == 1)){
    else if((CO_Warning == 1)){
      if(opf == true){
//        Open_Fan();
        Open_Window();
//        Silence();
      }
    }
//    else if((PM_Warning == 0)||(CO_Warning == 0)||(CO2_Warning == 0)){
    else if((CO_Warning == 0)){
      Close_Fan();
      Close_Window();
      opf = false;
//      Silence();
    }
    else{
      Close_Fan();
      Close_Window();
      opf = false;
//      Close_Window();
//      Silence();
    }
    cnt = 0;  // initialize the counter
  }
  
  cnt++;
}



