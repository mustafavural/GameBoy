// Yılanın pozisyonu ve boyutu
byte snakeX[10];
byte snakeY[10];
byte snakeSize;

// Yılanın yönü
byte snakeDir; // 0: yukarı, 1: sağ, 2: aşağı, 3: sol

// Yem pozisyonu
byte foodX;
byte foodY;

//Oyun Durumu
bool gameover;

void snakeGame() {
  // Yılanın başlangıç yönünü ayarlama
  snakeDir = 1;
  // Yılanın başlangıç boyutunu ayarlama
  snakeSize = 3;
  // Yılanın başlangıç pozisyonunu ayarlama
  snakeX[0]=42;
  snakeY[0]=24;
  // Rastgele yem pozisyonu belirleme
  randomSeed(analogRead(0));
  foodX = random(2, 81);
  foodY = random(7, 45);
  gameover = false;
}

void snakePlay() {
  // Oyun devam ediyorsa yılanın hareketini güncelleme
  if (!gameover) {
    updateSnake();
  }
  
  // Ekranı güncelleme
  drawScreen();
  
  // 50ms bekleme
  delay(50);

  // Buton girişlerini kontrol etme
  checkButtons();  
}

void checkButtons() {
  // Yukarı butonuna basılıysa ve yılan aşağı gitmiyorsa yukarı yönde hareket etme
  if (analogRead(A0) > 1000 && snakeDir != 2) {
    snakeDir = 0;
  }
  
  // Aşağı butonuna basılıysa ve yılan yukarı gitmiyorsa aşağı yönde hareket etme
  if (analogRead(A1) > 1000 && snakeDir != 0) {
    snakeDir = 2;
  }
  
  // Sol butonuna basılıysa ve yılan sağa gitmiyorsa sola yönde hareket etme
  if (analogRead(A2) > 1000 && snakeDir != 1) {
    snakeDir = 3;
  }
  
  // Sağ butonuna basılıysa ve yılan sola gitmiyorsa sağa yönde hareket etme
  if (analogRead(A3) > 1000 && snakeDir != 3) {
    snakeDir = 1;
  }

  // Start butonuna basılıysa oyunu duraklat
  if (analogRead(A4) > 1000) {
    delay(200);
    AraMenu();
  }
}

void updateSnake() {
  // Yılanın kuyruğunu kaydırma
  for (byte i = snakeSize - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }
  
  // Yılanın başını güncelleme
  if (snakeDir == 0) {
    snakeY[0]--;
  } else if (snakeDir == 1) {
    snakeX[0]++;
  } else if (snakeDir == 2) {
    snakeY[0]++;
  } else if (snakeDir == 3) {
    snakeX[0]--;
  }

  // Duvara çarptı, oyunu bitirme
  if (snakeX[0] <= 1 || snakeX[0] >= 83 || snakeY[0] <= 5 || snakeY[0] >= 47) {
    gameover = true;
  }
  
  // Yılanın kendine çarpmasını kontrol etme
  for (byte i = 1; i < snakeSize; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameover = true;
    }
  }
  
  // Yılanın yemi yemesini kontrol etme
  if ((snakeX[0] >= foodX) && 
      (snakeX[0] <= foodX + 2) &&
      (snakeY[0] >= foodY) && 
      (snakeY[0] <= foodY + 2)) {
    // Yılan yemi yedi, yılanın boyutunu artırma
    snakeSize++;
    // Yılan yemi yediğinde beep çalma
    playTone(600,100);
    // Yeni bir yem pozisyonu belirleme
    foodX = random(2, 81);
    foodY = random(7, 45);
  }
}

void playTone(short frekans, short sure){
  tone(3,frekans,sure);
  delay(sure);
  noTone(3);
}

void drawScreen() {
  // Ekranı güncelleme
  lcd.update();
  // Ekranı temizleme
  lcd.clrScr();
  lcd.setFont(SmallFont);
  
  
  if(!gameover){
  //Puanı göster
  lcd.setFont(TinyFont);
  lcd.print("SKOR:", 53, 0);
  lcd.printNumI(snakeSize-3, 75, 0);

  // Çerçeve çizme
  lcd.drawRect(0, 5, 83, 47);

  // Yılanı çizme
  for (byte i = 0; i < snakeSize; i++) {
    lcd.drawRect(snakeX[i], snakeY[i], snakeX[i] + 1, snakeY[i] + 1);
  }
  
  // Yemi çizme
  lcd.drawRect(foodX, foodY, foodX + 2, foodY + 2);
  }
  else{
  // Oyun bittiğinde ekrana mesaj yazma
    MaxSkorGonder(snakeSize-3, "snake");
    lcd.print("GAME OVER", CENTER, 20);
    lcd.setFont(TinyFont);
    lcd.print("SKOR:", 23, 28);
    lcd.printNumI(snakeSize-3, 45, 28);
    lcd.print("EN YUKSEK", CENTER, 34);
    lcd.setFont(SmallFont);
    lcd.printNumI(100, CENTER, 41);
    lcd.update();
    playTone(500,200);
    playTone(400,300);
    playTone(300,400);
  }
}