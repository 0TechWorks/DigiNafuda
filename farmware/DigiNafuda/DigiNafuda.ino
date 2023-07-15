//SD_PIN
/*
 * Connect the SD card to the following pins:
 *
 * SD Card | ESP32
 *    D2       -
 *    D3       SS-7
 *    CMD      MOSI-6
 *    VSS      GND
 *    VDD      3.3V
 *    CLK      SCK-4
 *    VSS      GND
 *    D0       MISO-5
 *    D1       -
 */

//LCD_PIN
 /*
 01 GND
 02 LDEK
 03 LEDA  (3.3V)
 04 3.3V
 05 GND
 06 GND 
 07 D/C        (IO00)
 08 CS         (IO01)
 09 SCL        (IO04)
 10 SDA/MOSI   (IO06)
 11 RESET (3.3V)
 12 GND
 */


 
#include <SPI.h>
#include <SD.h>
#include "FS.h"
#include <LovyanGFX.hpp>
#include "SPIFFS.h"

#include "esp_system.h"
#include "driver/ledc.h"

int i =4;
int pic_num=0;
char i_char[10];



class LGFX : public lgfx::LGFX_Device
{

lgfx::Panel_ST7789      _panel_instance;
lgfx::Bus_SPI        _bus_instance;

public:


  LGFX(void)
  {
    {
      auto cfg = _bus_instance.config();

// SPIバスの設定
      cfg.spi_host = SPI2_HOST;     // 使用するSPIを選択  ESP32-S2,C3 : SPI2_HOST or SPI3_HOST / ESP32 : VSPI_HOST or HSPI_HOST
      // ※ ESP-IDFバージョンアップに伴い、VSPI_HOST , HSPI_HOSTの記述は非推奨になるため、エラーが出る場合は代わりにSPI2_HOST , SPI3_HOSTを使用してください。
      cfg.spi_mode = 0;             // SPI通信モードを設定 (0 ~ 3)
      cfg.freq_write = 80000000;    // 送信時のSPIクロック (最大80MHz, 80MHzを整数で割った値に丸められます)
      cfg.freq_read  = 16000000;    // 受信時のSPIクロック
      cfg.spi_3wire  = false;        // 受信をMOSIピンで行う場合はtrueを設定
      cfg.use_lock   = true;        // トランザクションロックを使用する場合はtrueを設定
      cfg.dma_channel = SPI_DMA_CH_AUTO; // 使用するDMAチャンネルを設定 (0=DMA不使用 / 1=1ch / 2=ch / SPI_DMA_CH_AUTO=自動設定)
      // ※ ESP-IDFバージョンアップに伴い、DMAチャンネルはSPI_DMA_CH_AUTO(自動設定)が推奨になりました。1ch,2chの指定は非推奨になります。
      cfg.pin_sclk = 4;            // SPIのSCLKピン番号を設定
      cfg.pin_mosi = 6;            // SPIのMOSIピン番号を設定
      cfg.pin_miso = 5;            // SPIのMISOピン番号を設定 (-1 = disable)
      cfg.pin_dc   = 0;            // SPIのD/Cピン番号を設定  (-1 = disable)
     // SDカードと共通のSPIバスを使う場合、MISOは省略せず必ず設定してください。
//*/


      _bus_instance.config(cfg);    // 設定値をバスに反映します。
      _panel_instance.setBus(&_bus_instance);      // バスをパネルにセットします。
    }

    { // 表示パネル制御の設定を行います。
      auto cfg = _panel_instance.config();    // 表示パネル設定用の構造体を取得します。

      cfg.pin_cs           =    1;  // CSが接続されているピン番号   (-1 = disable)
      cfg.pin_rst          =    -1;  // RSTが接続されているピン番号  (-1 = disable)
      cfg.pin_busy         =    -1;  // BUSYが接続されているピン番号 (-1 = disable)

      // ※ 以下の設定値はパネル毎に一般的な初期値が設定されていますので、不明な項目はコメントアウトして試してみてください。

      cfg.panel_width      =   240;  // 実際に表示可能な幅
      cfg.panel_height     =   240;  // 実際に表示可能な高さ
      cfg.offset_x         =     0;  // パネルのX方向オフセット量
      cfg.offset_y         =     0;  // パネルのY方向オフセット量
      cfg.offset_rotation  =     0;  // 回転方向の値のオフセット 0~7 (4~7は上下反転)
      cfg.dummy_read_pixel =     8;  // ピクセル読出し前のダミーリードのビット数
      cfg.dummy_read_bits  =     1;  // ピクセル以外のデータ読出し前のダミーリードのビット数
      cfg.readable         =  true;  // データ読出しが可能な場合 trueに設定
      cfg.invert           = true;  // パネルの明暗が反転してしまう場合 trueに設定
      cfg.rgb_order        = false;  // パネルの赤と青が入れ替わってしまう場合 trueに設定
      cfg.dlen_16bit       = false;  // 16bitパラレルやSPIでデータ長を16bit単位で送信するパネルの場合 trueに設定
      cfg.bus_shared       =  true;  // SDカードとバスを共有している場合 trueに設定(drawJpgFile等でバス制御を行います)

// 以下はST7735やILI9163のようにピクセル数が可変のドライバで表示がずれる場合にのみ設定してください。
//    cfg.memory_width     =   240;  // ドライバICがサポートしている最大の幅
//    cfg.memory_height    =   320;  // ドライバICがサポートしている最大の高さ

      _panel_instance.config(cfg);
    }

//*
    { // バックライト制御の設定を行います。（必要なければ削除）
      //auto cfg = _light_instance.config();    // バックライト設定用の構造体を取得します。

     // cfg.pin_bl = 32;              // バックライトが接続されているピン番号
      //cfg.invert = false;           // バックライトの輝度を反転させる場合 true
      //cfg.freq   = 44100;           // バックライトのPWM周波数
      //cfg.pwm_channel = 7;          // 使用するPWMのチャンネル番号

      //_light_instance.config(cfg);
     // _panel_instance.setLight(&_light_instance);  // バックライトをパネルにセットします。
    }
//*/

//*
    
//*/

    setPanel(&_panel_instance); // 使用するパネルをセットします。
  }
};

// 準備したクラスのインスタンスを作成します。
LGFX display;
static LGFX lcd;   
void setup(void)
{
  // SPIバスとパネルの初期化を実行すると使用可能になります。
  display.init();
  display.setTextSize((std::max(display.width(), display.height()) + 255) >> 8);

set_LCD_Light();
  display.fillScreen(TFT_BLACK);


   pinMode(2, INPUT_PULLUP);
   pinMode(3, INPUT_PULLUP);
   pinMode(20, INPUT_PULLUP);
   pinMode(21, INPUT_PULLUP);

display.setTextSize(3);
display.drawString("SW1 ICON", 20, 20);
display.drawString("SW2 QR", 20, 60);
display.drawString("SW3 LIGHT+",20, 100);
display.drawString("SW4 LIGHT-", 20, 140);

if(SD.begin(7)){display.drawString("SD-OK", 20, 180);}
SD.end();

delay(100);

display.setTextColor(TFT_WHITE);
lcd.init();

//lcd.qrcode("Hello world !", 0, 0, 240,15);
//lcd.display();

//SPIFFS.begin();
//lcd.drawPngFile(SPIFFS, "/icon.png", 0, 0);
//SPIFFS.end();

SD.begin(7);
lcd.drawPngFile(SD, "/icon.png", 0, 0);
SD.end();

attachInterrupt(2, INTIO2, FALLING);
attachInterrupt(3, INTIO3, FALLING);
attachInterrupt(20, INTI20, FALLING);
attachInterrupt(21, INTI21, FALLING);

setting_Light_Sleep();

}

uint32_t count = ~0;
void loop(void)
{
//draw_pic_spiffs();
draw_pic_sd();
}



void INTIO2(){pic_num=0;}
void INTIO3(){pic_num=1;}

void  INTI21(){PWMdutyPlus();do_Light_Sleep();}
void  INTI20(){PWMdutyMinus();do_Light_Sleep();}
