#include <LCD5110_Graph.h>

extern uint8_t SmallFont[];
extern unsigned char TinyFont[];
LCD5110 lcd(5, 6, 7, 8, 9);

// Menü seçenekleri
const char* oyunlar[] = {"YILAN", "TETRIS"};

int secilenOyun = 0;
bool gameBitir = false;

void setup() {
  // Buzzer
  pinMode(3, OUTPUT);

  // Ekranı başlatma
  lcd.InitLCD(60);
  lcd.setFont(SmallFont);
  
  // Buton pinlerini giriş olarak ayarlama
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void loop() {
  gameBitir = false;
  // Ekranı güncelleme
  menuyuEkranaYaz();
  
  // Buton girişlerini kontrol etme
  butonBasildiMi();
}

void butonBasildiMi() {
  // Yukarı butonuna basılıysa seçili seçeneği yukarı hareket ettirme
  if (analogRead(A0) > 1000) {
    secilenOyun--;
    if (secilenOyun < 0) {
      secilenOyun = sizeof(oyunlar) / sizeof(oyunlar[0]) - 1;
    }
    delay(200); // Buton debouncing için bekleme
    return;
  }
  
  // Aşağı butonuna basılıysa seçili seçeneği aşağı hareket ettirme
  if (analogRead(A1) > 1000) {
    secilenOyun++;
    if (secilenOyun >= sizeof(oyunlar) / sizeof(oyunlar[0])) {
      secilenOyun = 0;
    }
    delay(200); // Buton debouncing için bekleme
    return;
  }
  
  // Seç butonuna basılıysa seçili seçeneği çalıştırma
  if (analogRead(A4) > 1000) {
    delay(200); // Buton debouncing için bekleme
    secilenOyunuAc();
    return;
  }
}

void menuyuEkranaYaz() {
  // Ekranı temizleme
  lcd.clrScr();
  
  // Seçenekleri ekrana yazma
  for (int i = 0; i < sizeof(oyunlar) / sizeof(oyunlar[0]); i++) {
    if (i == secilenOyun) {
      lcd.print(">", 0, i * 10);
    }
    lcd.print(oyunlar[i], 10, i * 10);
  }
  
  // Ekranı güncelleme
  lcd.update();
}

void secilenOyunuAc() {
  
  // Seçili oyunu çalıştırma
  switch (secilenOyun) {
    case 0:
      // Yılan oyunu
      snakeGame();
      while(!gameBitir){
        snakePlay();
      }
      break;
    case 1:
      // Tetris oyunu
      tetrisGame();
      while(!gameBitir){
        tetrisPlay();
      }
      break;
    default:
      break;
  }
}