#include <tv_kit_vdk_18f6722_all.c> 
unsigned int8 mp8;
usi16 A[16]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
void h425_gan_gt_led_7d()
{
   for(int i=0; i<8; i++){
      led_7d[i] = A[i+4];
   }
}
void h425_dpst_A()//dich sang trai 1 bit
{
   for(int i=15; i>0; i--)
   {
      A[i] = A[i-1];
   }
}
void h425_dtsp_A()//dich sang trai 1 bit
{
   for(int i=0; i<15; i++)
   {
      A[i] = A[i+1];
   }
}
void b425_kiemtra_phim()
{
   mp8 = key_tip229_cdoi_c2(10);
   if((mp8>0)&&(mp8<10))
   {
      xuat_32led_don_4byte(0,0,0,mp8);
      h425_dpst_A();
      A[4] = ma7doan[mp8%16];
      h425_gan_gt_led_7d();
      xuat_8led_7doan();
      delay_ms(500);
   }
   if (mp8 == 13){ //undo
      h425_dtsp_A();
      h425_gan_gt_led_7d();
      xuat_8led_7doan();
      delay_ms(500);
   }
   if (mp8 == 15){ //redo
      h425_dpst_A();
      h425_gan_gt_led_7d();
      xuat_8led_7doan();
      delay_ms(500);
   }
}
void main()
{
   set_up_port();
   while(true)
   { 
      b425_kiemtra_phim();
   } 
}
