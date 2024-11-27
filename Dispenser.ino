#include <Servo.h>

//Library LCD I2C (link di deskripsi)
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Definisikan pin sensor ultrasonik
const int trigPin = 25;
const int echoPin = 26;

// Definisikan pin untuk servo motor
const int servoPin = 14;

// Definisikan variabel untuk menghitung jarak
long duration;
int distance;

Servo myServo;  // Buat objek servo motor

void setup() {
  // Inisialisasi pin output dan input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Atur pin servo
  myServo.attach(servoPin);

  // Mulai Serial Monitor
  Serial.begin(115200);

  //Mulai library LCD
  lcd.begin();
}

void loop() {
  // Kirimkan sinyal ultrasonik
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Baca waktu perjalanan pulsa ultrasonik
  duration = pulseIn(echoPin, HIGH);

  // Hitung jarak berdasarkan waktu perjalanan
  distance = duration * 0.037 / 2; // jika belum presisi ubah pada nilai 0.037

  // Cek apakah ada objek dalam jarak tertentu
  if (distance < 15) {  // Jarak yang dapat disesuaikan
    // Buka pintu dengan menggerakkan servo
    myServo.write(90);  // Atur sudut sesuai kebutuhan untuk membuka pintu
    lcd.setCursor(0, 1);
    lcd.print("Pintu Terbuka");
    delay(3000);  // Tahan pintu terbuka selama 3 detik
  } else {
    myServo.write(0);  // Kembali ke posisi awal untuk menutup pintu
    lcd.setCursor(0, 1);
    lcd.print("Pintu Tertutup");
    delay(1000);  // Tahan selama 1 detik sebelum membaca sensor lagi
  }

  // Tampilkan jarak di Serial Monitor
  Serial.print(distance);
  Serial.println(" cm");
  // Tampilkan jarak di LCD
  lcd.setCursor(0, 0);
  lcd.print("Jarak :");
  lcd.setCursor(8, 0);
  lcd.print(distance);
  lcd.setCursor(11, 0);
  lcd.print("cm");
  delay(500); // Atur interval pembacaan
  lcd.clear();

}