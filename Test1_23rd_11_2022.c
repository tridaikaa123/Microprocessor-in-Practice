#include <tv_kit_vdk_18f6722_all.c>
unsigned int16 lm35a_ng, lm35a_tp, lm35a_ngt=0, gtmin = 0,gtmax = 25;


void hienthi_thongtin() 
{ 
    lcd_goto_xy(0,0); 
    lcd_data("TRI - 19151087");
    lcd_goto_xy(2,0); 
    lcd_data("TMAX: ");
    lcd_goto_xy(3,0); 
    lcd_data("TMIN: ");
}

void doc_value_lm35(usi8 slan) 
{ 
    float lm35a;
    lm35a=h601_adc_read(slan,chan_lm35a);
    lm35a = lm35a/2.046;
    float_to_ng_2so_tp(lm35a);
    lm35a_ng = so_ng;
    lm35a_tp = so_tp;
    if(lm35a >= gtmax){
        xuat_32led_don_4byte(0,0,0,0xff);
    }
    else if(lm35a <= gtmin){
        xuat_32led_don_4byte(0,0,0xff,0);
    }
    else if((lm35a < gtmax) && (lm35a > gtmin)){
        xuat_32led_don_4byte(0,0xff,0,0);
    }

}
void hienthi_nhietdo(){
    lcd_goto_xy(2,6);
    lcd_data(gtmax/10 + 0x30);
    lcd_goto_xy(2,7);
    lcd_data(gtmax%10 + 0x30);
    lcd_goto_xy(3,6);
    lcd_data(gtmin/10 + 0x30);
    lcd_goto_xy(3,7);
    lcd_data(gtmin%10 + 0x30);
}
void hienthi_lcd(usi8 x,y,int1 ht_ng,ht_tp){
    if(lm35a_ngt!=lm35a_ng)
    {
        lm35a_ngt=lm35a_ng;
        lcd_goto_xy(x,y+2);
        lcd_data(".");
        if(ht_ng){
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

void test_phim_up(){
    if(phim_up_c1(c_ktnp,0) == co_nhan){
        if(gtmax > 60){
            gtmax = 0;
        }
        else{
            gtmax++;
        }
    }
    hienthi_nhietdo();
}

void test_phim_dw(){
    if(phim_bt1_c1(c_ktnp,0) == co_nhan){
        if(gtmin > 60){
            gtmin = 0;
        }
        else{
            gtmin++;
        }
    }
    hienthi_nhietdo();
}

void main()
{
    set_up_port();
    lcd_setup();
    hienthi_thongtin();
    while(true)
    {
        doc_value_lm35(100);
        test_phim_up();
        test_phim_dw();
        hienthi_nhietdo();
        hienthi_lcd(1, 0, 1, 1);
        delay_ms(200);
    } 
}
