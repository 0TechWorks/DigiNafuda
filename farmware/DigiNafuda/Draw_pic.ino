void draw_pic_spiffs(){

SPIFFS.begin();
if(pic_num==0){lcd.drawPngFile(SPIFFS, "/icon.png", 0, 0);}
else {lcd.drawPngFile(SPIFFS, "/qr.png", 0, 0);}
SPIFFS.end();
do_Light_Sleep();
}

void draw_pic_sd(){

SD.begin(7);
if(pic_num==0){lcd.drawPngFile(SD, "/sd_icon.png", 0, 0);}
else {lcd.drawPngFile(SD, "/sd_qr.png", 0, 0);}
SD.end();
do_Light_Sleep();
}
