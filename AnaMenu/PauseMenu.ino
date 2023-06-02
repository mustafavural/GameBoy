// Menü seçenekleri
const char* sec[] = {"AnaMenu","Devam"};

byte secim = 0;
bool devam = false;

void secileniYap() {
  // Seçili oyunu çalıştırma
  switch (secim) {
    case 0:
      // Ana Menu
      delay(200); // Buton debouncing için bekleme
      gameBitir=true;
      break;
    case 1:
      devam=true;
      return;
      break;
    default:
      break;
  }
}

void AraMenubutonBasildiMi() {
  // Yukarı butonuna basılıysa seçili seçeneği yukarı hareket ettirme
  if (analogRead(A0) > 1000) {
    delay(200); // Buton debouncing için bekleme
    secim--;
    if (secim < 0) {
      secim = sizeof(sec) / sizeof(sec[0]) - 1;
    }
  }
  
  // Aşağı butonuna basılıysa seçili seçeneği aşağı hareket ettirme
  if (analogRead(A1) > 1000) {
    delay(200); // Buton debouncing için bekleme
    secim++;
    if (secim >= sizeof(sec) / sizeof(sec[0])) {
      secim = 0;
    }
  }
  
  // Seç butonuna basılıysa seçili seçeneği çalıştırma
  if (analogRead(A4) > 1000) {
    delay(200); // Buton debouncing için bekleme
    secileniYap();
  }
}

void AraMenumenuyuEkranaYaz() {
  // Ekranı temizleme
  lcd.clrScr();
  lcd.setFont(SmallFont);
  // Seçenekleri ekrana yazma
  for (int i = 0; i < sizeof(sec) / sizeof(sec[0]); i++) {
    if (i == secim) {
      lcd.print(">", 0, i * 10);
    }
    lcd.print(sec[i], 10, i * 10);
  }
  
  // Ekranı güncelleme
  lcd.update();
}

void AraMenu() {
  devam=false;
  while(!gameBitir && !devam){
    // Ekranı güncelleme
    AraMenumenuyuEkranaYaz();
  
    // Buton girişlerini kontrol etme
    AraMenubutonBasildiMi();
  }
}