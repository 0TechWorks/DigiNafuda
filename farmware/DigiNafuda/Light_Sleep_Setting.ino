void setting_Light_Sleep(){

gpio_sleep_sel_dis(GPIO_NUM_10);

gpio_wakeup_enable(GPIO_NUM_9, GPIO_INTR_LOW_LEVEL);
  
gpio_wakeup_enable(GPIO_NUM_2, GPIO_INTR_LOW_LEVEL);
gpio_wakeup_enable(GPIO_NUM_3, GPIO_INTR_LOW_LEVEL);
gpio_wakeup_enable(GPIO_NUM_20, GPIO_INTR_LOW_LEVEL);
gpio_wakeup_enable(GPIO_NUM_21, GPIO_INTR_LOW_LEVEL);
  
do_Light_Sleep();
}

void do_Light_Sleep(){
esp_sleep_enable_gpio_wakeup();
esp_light_sleep_start();
}
