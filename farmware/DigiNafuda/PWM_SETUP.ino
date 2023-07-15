void set_LCD_Light(){
ledc_timer_bit_t bit_num = (ledc_timer_bit_t) 4; // duty range = 2^4 = 16

   // Enable LEDC PWM peripheral
   periph_module_enable(PERIPH_LEDC_MODULE);

   // Set Duty
   int duty = 4;  // 4/16 = 25% 15mA


   // setup the timer
   ledc_timer_config_t clk_timer;
   clk_timer.bit_num = bit_num; //                                                                                                                                                                                                                                                                                                                                                                                                    4
   clk_timer.freq_hz = 80000; // 5KHz
   clk_timer.speed_mode = LEDC_LOW_SPEED_MODE;
   clk_timer.timer_num = LEDC_TIMER_0;
   clk_timer.clk_cfg = LEDC_USE_RTC8M_CLK;
   ledc_timer_config(&clk_timer);

   // setup the pwm channel
   ledc_channel_config_t pwm_channel;
   pwm_channel.channel = LEDC_CHANNEL_0;
   pwm_channel.duty = duty;
   pwm_channel.gpio_num = GPIO_NUM_10;
   pwm_channel.intr_type = LEDC_INTR_DISABLE;
   pwm_channel.speed_mode = LEDC_LOW_SPEED_MODE;
   pwm_channel.timer_sel = LEDC_TIMER_0;
   ledc_channel_config(&pwm_channel);

   // Set the PWM to the duty specified
   ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
   ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
   }

void PWMdutyPlus(){
display.fillScreen(TFT_WHITE);
if(16>i){i=i+1;}
ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
DispPWM();
NoOPeration_Delay();
}

void PWMdutyMinus(){

display.fillScreen(TFT_WHITE);
if(i>1){i=i-1;}
ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
DispPWM();
NoOPeration_Delay();
}




void DispPWM(){
display.setTextColor(TFT_BLACK);
display.setTextSize(5);
sprintf(i_char, "%d", i);
display.drawString(i_char, 100, 100);
}

void NoOPeration_Delay(){

for (int NOP_Delay = 0; NOP_Delay <= 6000000; NOP_Delay++) {
NOP();
}
}
