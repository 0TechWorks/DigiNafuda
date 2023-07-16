void DiginafudaStart(){

display.setTextSize(3);
display.drawString("SW1 ICON", 20, 20);
display.drawString("SW2 QR", 20, 60);
display.drawString("SW3 LIGHT+",20, 100);
display.drawString("SW4 LIGHT-", 20, 140);

if(SD.begin(7)){display.drawString("SD-OK", 20, 180);}
SD.end();

delay(100);
  
  }
