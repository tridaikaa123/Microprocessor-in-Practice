#include <tv_kit_vdk_18f6722_all.c>

usi16 T = 15, dis;
int1 alarm=0;
void h609_lcd_cbkc_gp2d12() 
{ 
    lcd_goto_xy(0,0); 
    lcd_data("Tri - 19151087");
}
void b609_adc_cbkc_gp2d12(usi8 sl, int1 ht_tp) 
{ 
    float kc;
    usi16 kc_ng,kc_tp,kc_t;
    kc=h601_adc_read(sl,chan_cbkc);
    kc = pow(4277/kc,1.106); 
    dis = kc;
    if(kc>80) kc=80;
 
    float_to_ng_2so_tp(kc); 
    kc_ng = so_ng;
    kc_tp = so_tp;
    lcd_goto_xy(1,2);
    lcd_data(".");
    if(kc_t!=kc_ng)
    {
        kc_t=kc_ng; 
        lcd_goto_xy(1,0);
        lcd_data(kc_ng/10 + 0x30);
        lcd_goto_xy(1,1);
        lcd_data(kc_ng%10 + 0x30);
        xuat_8led_7doan();
    }
        if(ht_tp){
            lcd_goto_xy(1,3);
            lcd_data(kc_tp/10 + 0x30);
            lcd_goto_xy(1,4);
            lcd_data(kc_tp%10 + 0x30);
        }
    lcd_goto_xy(2,0);
    lcd_data("T: ");
    lcd_goto_xy(2,3);
    lcd_data(T/10 + 0x30);
    lcd_data(T%10 + 0x30);
}

void xuly_alarm(){
    if(alarm == 1){
        if(dis >= T){
            buzzer_on();
            lcd_goto_xy(3,0);
            lcd_data("Buzzer: ON ");
        }
        else{
            buzzer_off();
            lcd_goto_xy(3,0);
            lcd_data("Buzzer: OFF");
        }
    }
    else if(alarm == 0){
        buzzer_off();
    }
}

void sosanh_(){
    if(dis < T){
        xuly_alarm();
        xuat_32led_don_4byte(0xff,0,0,0);
    }
    else if(dis > T){
        xuly_alarm();
        xuat_32led_don_4byte(0,0,0,0xff);
    }
}

void up_dw(){
    if(!input(bt0) == 1){
        delay_ms(20);
        if(!input(bt0) == 1){
            while(!input(bt0) == 1);
            if(T > 70){
                T = 70;
            }
            else T++;
        }
    }
    if(!input(bt1) == 1){
        delay_ms(20);
        if(!input(bt1) == 1){
            while(!input(bt1) == 1);
            if(T < 15){
                T = 15;
            }
            else T--;
        }
    }
    if(!input(bt2) == 1){
        delay_ms(20);
        if(!input(bt2) == 1){
            while(!input(bt2) == 1);
            if(alarm == 1){
                alarm = 0;
            }
            else alarm = 1;
        }
    }
}

void main()
{
    set_up_port();
    lcd_setup();
    lcd_khoi_tao_cgram_so_to(); 
    h609_lcd_cbkc_gp2d12(); 
    lcd_goto_xy(1,0);
    lcd_data(8+0x30);
    lcd_goto_xy(1,1);
    lcd_data(0x30);
    lcd_goto_xy(3,0);
    lcd_data("Buzzer: OFF");
    while(true)
    { 
        b609_adc_cbkc_gp2d12(10,1);
        up_dw();
        sosanh_();
    } 
}


