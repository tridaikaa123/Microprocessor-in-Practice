#include <tv_kit_vdk_18f6722_all.c> 
#define solan 100
unsigned int16 lm35a_ng,lm35a_tp,lm35a_ngt=0;
void h601_adc_lm35a_doc_xuly(usi8 slan) 
{ 
    float lm35a; 
    lm35a=h601_adc_read(slan,chan_lm35a);
    lm35a = lm35a/2.046;
    float_to_ng_2so_tp(lm35a);
    lm35a_ng = so_ng;
    lm35a_tp = so_tp;
}

void hienthi_lcd(usi8 x,y,int1 ht_lcd,ht_tp){
    if(lm35a_ngt!=lm35a_ng)
    {
        lm35a_ngt=lm35a_ng;
        lcd_goto_xy(x,y+2);
        lcd_data(".");
        if(ht_lcd){
            lcd_goto_xy(x,y);
            lcd_data(lm35a_ng/10 + 0x30);
            lcd_data(lm35a_ng%10 + 0x30);
        }
        if(ht_tp){
            lcd_goto_xy(x,y+3);
            lcd_data(lm35a_tp/10 + 0x30);
            lcd_data(lm35a_tp%10 + 0x30);
        }
    }
}

void h601_adc_lm35a_ht_7doan(usi8 z,int1 ht_l7d) 
{ 
    if(ht_l7d) 
    { 
        giaima_bin_2so_vitri_vn(lm35a_ng,z,kx_vn);
        xuat_8led_7doan();
    } 
}

void main()
{ 
    set_up_port();
    lcd_setup();
    lcd_khoi_tao_cgram_so_to();
 
    lcd_goto_xy(0,0); 
    lcd_data("LM35A");
    while(true)
    {
        h601_adc_lm35a_doc_xuly(solan);
        hienthi_lcd(1, 0, 1, 1);
        h601_adc_lm35a_ht_7doan(6,1);
        delay_ms(200);
    } 
}

