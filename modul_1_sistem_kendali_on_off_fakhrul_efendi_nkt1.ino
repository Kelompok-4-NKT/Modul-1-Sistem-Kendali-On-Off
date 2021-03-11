/************************************************/

// Modul Praktikum 1 - Sistem Kendali On-Off
// Nama Tim			: NKT
// Nama Anggota 1	: Fakhrul Efendi
// Nama Anggota 2	: Iqbal Syaifullah A.
// Versi Program	: 1.5

/************************************************/
//Deklarasi variabel sensor
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];

//Variabel motor
int pinEnable1 = 4;//Harus diset HIGH apabila akan diaktifkan
int pinEnable2 = 2;//Harus diset HIGH apabila akan diaktifkan
//Motor Kiri
int motor_kiri1 = 5;//Input motor driver 1 L293D
int motor_kiri2 = 6;//Input motor driver 2 L293D
//Motor Kanan
int motor_kanan1 = 3;//Input motor driver 3 L293D
int motor_kanan2 = 11;//Input motor driver 4 L293D

void setup(){
  //Pinmode input sensor
  pinMode(sensor1, INPUT);//Set pin A0 sebagai input
  pinMode(sensor2, INPUT);//Set pin A1 sebagai input
  pinMode(sensor3, INPUT);//Set pin A2 sebagai input
  pinMode(sensor4, INPUT);//Set pin A3 sebagai input
  pinMode(sensor5, INPUT);//Set pin A4 sebagai input
  pinMode(sensor6, INPUT);//Set pin A5 sebagai input
  //Pinmode output motor
  pinMode(pinEnable1, OUTPUT);//Set pin 4 sebagai output
  pinMode(pinEnable2, OUTPUT);//Set pin 2 sebagai output
  pinMode(motor_kiri1, OUTPUT);//Set pin 5 sebagai output
  pinMode(motor_kiri2, OUTPUT);//Set pin 6 sebagai output
  pinMode(motor_kanan1, OUTPUT);//Set pin 3 sebagai output
  pinMode(motor_kanan2, OUTPUT);//Set pin 11 sebagai output
  //Inisialisasi komunikasi serial
  Serial.begin(9600);//Baud Rate standar 9600
  }

  void readsensor(){//Fungsi untuk membaca sensor kemudian menyimpan pada array
    baca_sensor[0] = analogRead(sensor1);
    baca_sensor[1] = analogRead(sensor2);
    baca_sensor[2] = analogRead(sensor3);
    baca_sensor[3] = analogRead(sensor4);
    baca_sensor[4] = analogRead(sensor5);
    baca_sensor[5] = analogRead(sensor6);
    Serial.println(baca_sensor[0]);
  }
  
  void loop(){
    //Nilai terendah photodiode = 33 (Paling Gelap)
    //Nilai tertinggi photodiode = 689 (Paling Terang)
    readsensor();
    //Sensor 1 dan 2 mendeteksi gelap : Motor kanan aktif, Motor kiri mati
    if (baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      digitalWrite(motor_kiri1, LOW);
      digitalWrite(motor_kiri2, LOW);
      
      digitalWrite(pinEnable2, HIGH);
      digitalWrite(motor_kanan1, HIGH);
      digitalWrite(motor_kanan2, LOW);
    }
    //Sensor 3 dan 4 mendeteksi gelap : Kedua motor aktif
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] < 34 && baca_sensor[3] < 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      digitalWrite(motor_kiri1, HIGH);
      digitalWrite(motor_kiri2, LOW);
      
      digitalWrite(pinEnable2, HIGH);
      digitalWrite(motor_kanan1, HIGH);
      digitalWrite(motor_kanan2, LOW);
    }
    //Sensor 5 dan 6 mendeteksi gelap
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] < 34 && baca_sensor[5] < 34 ){
      digitalWrite(pinEnable1, HIGH);
      digitalWrite(motor_kiri1, HIGH);
      digitalWrite(motor_kiri2, LOW);
      
      digitalWrite(pinEnable2, HIGH);
      digitalWrite(motor_kanan1, LOW);
      digitalWrite(motor_kanan2, LOW);
    }
    //Semua sensor tidak mendeteksi gelap : Kedua motor mati
    if (baca_sensor[0] > 34 && baca_sensor[1] > 34 && 
        baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
        baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
      digitalWrite(pinEnable1, HIGH);
      digitalWrite(motor_kiri1, LOW);
      digitalWrite(motor_kiri2, LOW);
      
      digitalWrite(pinEnable2, HIGH);
      digitalWrite(motor_kanan1, LOW);
      digitalWrite(motor_kanan2, LOW);
    }
 }