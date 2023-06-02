#include <UIPEthernet.h>

void MaxSkorGonder(byte maxSkor, char gameName[]) {
  byte mac[] = { 0x54, 0x34, 0x41, 0x30, 0x30, 0x31 };

  EthernetClient client;

  Ethernet.begin(mac);
  
  client.connect("192.168.1.5", 80);
    //Serial.println("Baglanti basarili");
    // yüksek skor verimizi girelim
  client.print( "GET /add.php?m=maxSkor&g=gameName");
  client.println( " HTTP/1.1");
  client.print( "Host: " );
  client.println("192.168.1.5");
  client.println( "Connection: close" );
  client.println();
  client.println();
  client.stop(); 
}