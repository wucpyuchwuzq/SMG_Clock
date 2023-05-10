#include <Wire.h>
#include <MsTimer2.h>
#include "ClickButton.h"
#include "DS1307.h"
#include <string.h>
#include <stdint.h>
#include <avr/wdt.h>
#include <LedControl.h>

#define TIMES_PERIOD 1  //定时时间间隔，ms
#define LOG_INFO(s) Serial.println(s);
#define LOG_INFO_NONLN(ss) Serial.print(ss);
#define LOG_INT(var) Serial.println(var,DEC);
#define LOG_INT_NONLN(vars) Serial.print(vars,DEC);

unsigned char T9_[]={
                    B00000000,
                    B01110000,
                    B01010000,
                    B01110000,
                    B00010000,
                    B01110000,
                    B00000000,
                    B00000000};
unsigned char T8_[]={
                    B00000000,
                    B01110000,
                    B01010000,
                    B01110000,
                    B01010000,
                    B01110000,
                    B00000000,
                    B00000000};
unsigned char T7_[]={
                    B00000000,
                    B01110000,
                    B00010000,
                    B00010000,
                    B00010000,
                    B00010000,
                    B00000000,
                    B00000000};
unsigned char T6_[]={
                    B00000000,
                    B01110000,
                    B01000000,
                    B01110000,
                    B01010000,
                    B01110000,
                    B00000000,
                    B00000000};
unsigned char T5_[]={
                    B00000000,
                    B01110000,
                    B01000000,
                    B01110000,
                    B00010000,
                    B01110000,
                    B00000000,
                    B00000000};
unsigned char T4_[]={
                    B00000000,
                    B01010000,
                    B01010000,
                    B01110000,
                    B00010000,
                    B00010000,
                    B00000000,
                    B00000000};
unsigned char T3_[]={
                    B00000000,
                    B01110000,
                    B00010000,
                    B01110000,
                    B00010000,
                    B01110000,
                    B00000000,
                    B00000000};

unsigned char T2_[]={
                    B00000000,
                    B01110000,
                    B00010000,
                    B01110000,
                    B01000000,
                    B01110000,
                    B00000000,
                    B00000000};

unsigned char T1_[]={
                    B00000000,
                    B00100000,
                    B00100000,
                    B00100000,
                    B00100000,
                    B00100000,
                    B00000000,
                    B00000000};

unsigned char T0_[]={
                    B00000000,
                    B01110000,
                    B01010000,
                    B01010000,
                    B01010000,
                    B01110000,
                    B00000000,
                    B00000000};
                    
unsigned char T_9[]={
                    B00000000,
                    B00000111,
                    B00000101,
                    B00000111,
                    B00000001,
                    B00000111,
                    B00000000,
                    B00000000};
unsigned char T_8[]={
                    B00000000,
                    B00000111,
                    B00000101,
                    B00000111,
                    B00000101,
                    B00000111,
                    B00000000,
                    B00000000};
unsigned char T_7[]={
                    B00000000,
                    B00000111,
                    B00000001,
                    B00000001,
                    B00000001,
                    B00000001,
                    B00000000,
                    B00000000};
unsigned char T_6[]={
                    B00000000,
                    B00000111,
                    B00000100,
                    B00000111,
                    B00000101,
                    B00000111,
                    B00000000,
                    B00000000};
unsigned char T_5[]={
                    B00000000,
                    B00000111,
                    B00000100,
                    B00000111,
                    B00000001,
                    B00000111,
                    B00000000,
                    B00000000};
unsigned char T_4[]={
                    B00000000,
                    B00000101,
                    B00000101,
                    B00000111,
                    B00000001,
                    B00000001,
                    B00000000,
                    B00000000};
unsigned char T_3[]={
                    B00000000,
                    B00000111,
                    B00000001,
                    B00000111,
                    B00000001,
                    B00000111,
                    B00000000,
                    B00000000};
unsigned char T_2[]={
                    B00000000,
                    B00000111,
                    B00000001,
                    B00000111,
                    B00000100,
                    B00000111,
                    B00000000,
                    B00000000};
unsigned char T_1[]={
                    B00000000,
                    B00000010,
                    B00000010,
                    B00000010,
                    B00000010,
                    B00000010,
                    B00000000,
                    B00000000};
unsigned char T_0[]={
                    B00000000,
                    B00000111,
                    B00000101,
                    B00000101,
                    B00000101,
                    B00000111,
                    B00000000,
                    B00000000};                  
byte Love[] = {
                    B00000000,
                    B01101100,
                    B11111110,
                    B11111110,
                    B01111100,
                    B00111000,
                    B00010000,
                    B00000000};

byte Point_[] = {
                    B00000000,
                    B00000000,
                    B00100000,
                    B00000000,
                    B00100000,
                    B00000000,
                    B00000000,
                    B00000000};

byte _Point[] = {
                    B00000000,
                    B00000000,
                    B00000010,
                    B00000000,
                    B00000010,
                    B00000000,
                    B00000000,
                    B00000000};
byte Month_CH[] = {     
                    B00111100,
                    B00100100,
                    B00111100,
                    B00100100,
                    B00111100,
                    B00100100,
                    B01000100,
                    B00000000}; 
byte Day_CH[] = {
                    B00111100,
                    B00100100,
                    B00100100,
                    B00111100,
                    B00100100,
                    B00100100,
                    B00111100,
                    B00000000};   
/* 宋体 [未指定字号]*/
/* 一[0xD2BB]    8x8  */
byte Monday_CH[]={0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00};
/* 宋体 [未指定字号]*/
/* 二[0xB6FE]    8x8  */
byte Tuesday_CH[]={0x00,0x00,0x3C,0x00,0x00,0x00,0x7E,0x00};
/* 宋体 [未指定字号]*/
/* 三[0xC8FD]    8x8  */
byte Wednesday_CH[]={0x00,0x00,0x3C,0x00,0x3C,0x00,0x7E,0x00};
/* 宋体 [未指定字号]*/
/* 四[0xCBC4]    8x8  */
byte Thursday_CH[]={0x00,0x7E,0x5A,0x5A,0x6E,0x42,0x7E,0x00};
/* 宋体 [未指定字号]*/
/* 五[0xCEE5]    8x8  */
byte Friday_CH[]={0x00,0x7C,0x10,0x7C,0x14,0x14,0x7E,0x00};
/* 宋体 [未指定字号]*/
/* 六[0xC1F9]    8x8  */
byte Saturday_CH[]={0x00,0x10,0x08,0x7E,0x00,0x24,0x42,0x00};
/* 宋体 [未指定字号]*/
/* 七[0xC6DF]    8x8  */
byte Sunday_CH[]={0x00,0x10,0x10,0x7E,0x10,0x10,0x1E,0x00};                                     
//任务结构
typedef struct _TASK_COMPONENTS
{
  int Run; //程序运行标记： 0-不运行，1-运行
  int Timer; //计时器
  int ItvTime;  //任务运行时间间隔
  void (*TaskHook)(void); //要运行的任务函数
}TASK_COMPONENTS;//任务定义,TASK_COMPONENTS是_TASK_COMPONENTS的别名

void TaskKeyCheck();
void TaskUpdateTime();
void TaskSetTime();
void TaskReadRTC();
void TaskRemarks();
void TaskPWMout();

static TASK_COMPONENTS TaskComps[]=
{
  {0,1,1,TaskKeyCheck},  //按键检测
  {0,1000,1000,TaskUpdateTime},  //静态显示时间
  {0,500,500,TaskSetTime},  //动态设置时间
  {0,200,200,TaskReadRTC},//读取RTC
//  {0,2,2,TaskPWMout}//产生PWM
};

//任务清单
typedef enum _TASK_LIST
{
  TASK_KEY_CHECK, 
  TASK_UPDATE_TIME,
  TASK_SET_TIME,
  TASK_READ_RTC,
//  TASK_PWM_OUT,
  TASKS_MAX   //总共可分配的定时任务数目
}TASK_LIST;

enum _key_states_e{//单个按键的状态机模式
  _FSM_KEY_NONE, //未按下
  _FSM_KEY_TAP, //单击
  _FSM_KEY_DOUBLE, //双击
  _FSM_KEY_TRIPLE,    //三击
  _FSM_KEY_LONG_PRESS = -1,   //长按
  _FSM_KEY_MAX_NUM = 8    //最大按键动作数
}key_states_e;

typedef struct now_date{ //实际时间
uint8_t t_hour;
uint8_t t_min;
uint8_t t_sec;
uint16_t t_year;
uint8_t t_month;
uint8_t t_day;
uint8_t t_week;   
}NOW_DATE;
NOW_DATE now_date; //当前时间结构体变量
NOW_DATE temp_date; //临时时间结构体变量
String timedata = "";

enum display_states_e{//显示状态
  _DIS_IDLE,//无刷新的空闲状态
  _DIS_UPDATE_TIMES,  //静态刷新显示时间
  _DIS_SET_HOUR,   //设置小时
  _DIS_SET_MIN,//设置分钟
  _DIS_SET_SEC,//设置秒
  _DIS_SET_YEAR,//设置年
  _DIS_SET_MONTH,//设置月
  _DIS_SET_DAY,//设置日
  _DIS_SET_WEEK,//设置星期
  _DIS_SET_INVALID//设置无效
};

int key_states=_FSM_KEY_NONE; //按键状态
const uint8_t button_Pin = 8; //按键检测脚
ClickButton mybutton(button_Pin, LOW, CLICKBTN_PULLUP);
DS1307 myclock;//define a object of DS1307 class

struct SYS_STATUS
{
  uint8_t system_states; //系统状态
}sys_state_s = {_DIS_IDLE};

uint8_t test_led_pin = 13;//状态指示灯引脚

void idel_task();
void (*func)(void)=idel_task;//函数指针

enum led_onoff_e{
  _LED_ALL_ON, // 全亮
  _LED_HOUR_OFF, // 小时闪
  _LED_MIN_OFF, //分钟闪
  _LED_SEC_OFF,    //秒闪
  _LED_YEAR_OFF,   //年闪
  _LED_MONTH_OFF,   //月闪
  _LED_DAY_OFF,   //日闪
  _LED_WEEK_OFF   //星期闪
};
unsigned char (*p)[10];//数组指针
unsigned char *sp_x[10]={T_0,T_1,T_2,T_3,T_4,T_5,T_6,T_7,T_8,T_9};//指针数组
unsigned char *spx_[10]={T0_,T1_,T2_,T3_,T4_,T5_,T6_,T7_,T8_,T9_};//指针数组
unsigned char *weekx_[8]={0x00,Monday_CH,Tuesday_CH,Wednesday_CH,Thursday_CH,Friday_CH,Saturday_CH,Sunday_CH};//指针数组

LedControl g_lc = LedControl(4, 5, 6, 8);//(int dataPin, int clkPin, int csPin, int numDevices)

//数码管引脚定义
const uint8_t data_pin = 9;
const uint8_t clk_pin = 10;
const uint8_t rck_pin = 11;
const uint8_t pwm_pin = 3;

//四位数码管引脚定义
const uint8_t dio_dpdp_pin = 7;
const uint8_t clk_dpdp_pin = 8;
const uint8_t stb_dpdp_pin = 12;
const uint8_t disp_pos[]={0xc0,0xc2,0xc4,0xc6};

uint8_t seg_light_value = 2;//数码管亮度值 0-20,数值越大，亮度越亮
uint8_t matrix_light_value = 2;//点阵屏亮度值 0-16,数值越大，亮度越亮

#define NUM 12
const uint8_t seg[NUM]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x00,0x80};//0-9,不亮,dp
boolean seg_dpoint_off_on = false;
  
const uint8_t intensity_pin = 2; //A2 光检测模块引脚

uint8_t index=0;
char rev_ch = 0; //必须是char
String rev_str = "";

/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*******************************************************************/
/*  系统初始化函数                                                     */
/*******************************************************************/
void setup()
{
  seg_dpdp_init();
  seg_init();   
  key_scan_init();
  matrix_screen_init(); 
  delay(5000); 
   
  pinMode(test_led_pin,OUTPUT);

  MsTimer2::set(TIMES_PERIOD, TaskRemarks);//定时器2影响analogWrite输出PWM，因为都用定时器2
  MsTimer2::start();

  myclock.begin();//启动RTC
  myclock.getTime(); //获取RTC时间
  delay(500);
  now_date.t_hour = myclock.hour; //小时
  now_date.t_min = myclock.minute; //分钟
  now_date.t_sec = myclock.second; //秒
  now_date.t_year = myclock.year; //年
  now_date.t_month = myclock.month; //月
  now_date.t_day = myclock.dayOfMonth; //日
  now_date.t_week = myclock.dayOfWeek; //星期

  if(now_date.t_hour > 23 || now_date.t_min > 59 || now_date.t_sec > 59 || now_date.t_year > 50 || now_date.t_month > 12 || now_date.t_day > 31) 
  {
    myclock.fillByYMD(2022,1,1);
    myclock.fillByHMS(23,1,1);
    myclock.fillDayOfWeek(1);
    myclock.setTime();//write time to the RTC chip 
  }
  //点阵屏显示日期
  matrix_screen_dispdate(now_date.t_year,now_date.t_month,now_date.t_day);
  matrix_screen_dispweek(now_date.t_week);
  matrix_screen_disptemperature();
  temp_date = now_date;
  //wdt_init();
  Serial.begin(9600);
  Serial.println("system init finish");
//  analogWrite(pwm_pin,seg_light_value);
}
/*******************************************************************/
/*  主循环函数                                                     */
/*******************************************************************/
void loop()
{
  TaskProcess();
  if(Serial.available()>0){
    rev_ch = Serial.read();
//    Serial.print(rev_ch);
    rev_str += rev_ch;
    index++;
    //setTime=2022121123012001@
    if(rev_ch == '@'){
       if(index == 25){
//         Serial.println(rev_str);
//         Serial.println(rev_str.substring(0,8));
         if(rev_str.substring(0,8) == "setTime="){ 
            temp_date.t_year = (rev_str.substring(8,12)).toInt(); 
            temp_date.t_month = (rev_str.substring(12,14)).toInt();
            temp_date.t_day = (rev_str.substring(14,16)).toInt();
            temp_date.t_hour = (rev_str.substring(16,18)).toInt();
            temp_date.t_min = (rev_str.substring(18,20)).toInt();
            temp_date.t_sec = (rev_str.substring(20,22)).toInt();
            temp_date.t_week = (rev_str.substring(22,24)).toInt();
           //设置RTC时间
            myclock.fillByYMD(temp_date.t_year,temp_date.t_month,temp_date.t_day);
            myclock.fillByHMS(temp_date.t_hour,temp_date.t_min,temp_date.t_sec);
            myclock.fillDayOfWeek(temp_date.t_week);
            myclock.setTime();//write time to the RTC chip  
            Serial.println("OK,set time success!");     
         }        
       }else{         
          Serial.println("ERROR,such as: setTime=2022121123012001@"); 
       }
       index = 0;
       rev_ch = 0;
       rev_str = "";
    }      
  }
}
/*******************************************************************/
/*  数码管dpdp显示初始化函数                                                     */
/*******************************************************************/
void seg_dpdp_init()
{
  pinMode(dio_dpdp_pin,OUTPUT);
  pinMode(clk_dpdp_pin,OUTPUT);
  pinMode(stb_dpdp_pin,OUTPUT);  
  digitalWrite(dio_dpdp_pin,HIGH);
  digitalWrite(clk_dpdp_pin,HIGH);
  digitalWrite(stb_dpdp_pin,HIGH);

  tm1628_display(disp_pos[0],0x5c);//显示两个圈
  tm1628_display(disp_pos[1],0x00);
  tm1628_display(disp_pos[2],0x00);
  tm1628_display(disp_pos[3],0x63);
}

void tm1628_writedata(uint8_t cmd)
{
  uint8_t i;
  for(i=0;i<8;i++){
    if(cmd & 0x01)
    {
       digitalWrite(dio_dpdp_pin,HIGH); 
    }else{
       digitalWrite(dio_dpdp_pin,LOW);
    }
    digitalWrite(clk_dpdp_pin,LOW);
    delayMicroseconds(10);
    cmd = cmd >> 1;
    digitalWrite(clk_dpdp_pin,HIGH);
  }
  delayMicroseconds(40);
}

void tm1628_wrcom(uint8_t com){
  digitalWrite(stb_dpdp_pin,HIGH);
  delayMicroseconds(5);
  digitalWrite(stb_dpdp_pin,LOW);
  delayMicroseconds(2);
  tm1628_writedata(com);
  delayMicroseconds(2);
}

void tm1628_addrdat(uint8_t addr, uint8_t dat){
  digitalWrite(stb_dpdp_pin,HIGH);
  delayMicroseconds(5);
  digitalWrite(stb_dpdp_pin,LOW);
  delayMicroseconds(2);
  tm1628_writedata(addr);
  tm1628_writedata(dat);
  delayMicroseconds(2);
}

void tm1628_display(uint8_t addr, uint8_t val){
  tm1628_wrcom(0x03);
  tm1628_wrcom(0x44);

  tm1628_addrdat(addr,val);
  tm1628_wrcom(0x8f);
  digitalWrite(stb_dpdp_pin,HIGH);
  delayMicroseconds(100);
}
/*******************************************************************/
/*  数码管显示初始化函数                                                     */
/*******************************************************************/
void seg_init()
{
  //引脚配置为输出
  pinMode(data_pin,OUTPUT);
  pinMode(clk_pin,OUTPUT);
  pinMode(rck_pin,OUTPUT);
  pinMode(pwm_pin,OUTPUT);
  digitalWrite(pwm_pin,HIGH);
  //显示....
  analogWrite(pwm_pin,200);//数码管亮度
  
  digitalWrite(rck_pin,LOW);
  shiftOut(data_pin,clk_pin,MSBFIRST,seg[11]);
  delay(20);//延迟很重要,显示不闪烁
  shiftOut(data_pin,clk_pin,MSBFIRST,seg[11]);
  delay(20);//延迟很重要,显示不闪烁);
  shiftOut(data_pin,clk_pin,MSBFIRST,seg[11]);
  delay(20);//延迟很重要,显示不闪烁
  shiftOut(data_pin,clk_pin,MSBFIRST,seg[11]);
  digitalWrite(rck_pin,HIGH);  
}
/*******************************************************************/
/*  空任务函数                                                     */
/*******************************************************************/
void idel_task()
{
  
}
/*******************************************************************/
/*  看门狗初始化                                                     */
/*******************************************************************/
void wdt_init()
{
//  get_mcusr();
  wdt_enable(WDTO_8S);//设置看门狗溢出时间
}
/*******************************************************************/
/*  按键检测初始化                                                     */
/*******************************************************************/
void key_scan_init()
{
  mybutton.debounceTime   = 20;   // Debounce timer in ms
  mybutton.multiclickTime = 250;  // Time limit for multi clicks
  mybutton.longClickTime  = 1000; // time until "held-down clicks" register  
}
/*******************************************************************/
/*  亮度随光强变化而变化                                                     */
/*******************************************************************/
void intensity_to_light()
{
  uint16_t intensity_value = 0; 
  static uint8_t new_seg_light_value = 0;
  static uint8_t new_matrix_light_value = 0;
  
  intensity_value = analogRead(intensity_pin);
  LOG_INFO("intensity_value:");
  LOG_INT(intensity_value);
  if(intensity_value < 200){//最亮
    new_seg_light_value = 10;
    new_matrix_light_value = 13;
  }else if((intensity_value > 200) && (intensity_value < 400))
  {
    new_seg_light_value = 8;
    new_matrix_light_value = 10;
  }else if((intensity_value > 400) && (intensity_value < 700))
  {
    new_seg_light_value = 6;
    new_matrix_light_value = 8;
  }else if((intensity_value > 700) && (intensity_value < 900))
  {
    new_seg_light_value = 4;
    new_matrix_light_value = 4;
  }else if(intensity_value > 900)//最暗
  {
    new_seg_light_value = 2;
    new_matrix_light_value = 2;
  }
  if(seg_light_value != new_seg_light_value){
    seg_light_value = new_seg_light_value;
    analogWrite(pwm_pin,seg_light_value); //改变数码管亮度   
    LOG_INFO("seg_light_value:");
    LOG_INT(seg_light_value);
  }
  if(matrix_light_value != new_matrix_light_value){
    matrix_light_value = new_matrix_light_value;
    for(int k=0;k<8;k++){
      g_lc.setIntensity(k, matrix_light_value);//亮度
    }
    LOG_INFO("matrix_light_value:");
    LOG_INT(matrix_light_value);
  }
}
/*******************************************************************/
/*  点阵屏显示初始化                                                     */
/*******************************************************************/
void matrix_screen_init()
{
  uint8_t k=0,j=0;
  for(k=0;k<8;k++){
    g_lc.shutdown(k,false);//开显示
    g_lc.setIntensity(k, matrix_light_value);//亮度
    g_lc.clearDisplay(k);//清除显示    
    for(j=0;j<8;j++)
      g_lc.setRow(k, j, Love[j]); //心型
  }  
}
/*******************************************************************/
/*  按键状态检测函数                                                     */
/*******************************************************************/
int mybutton_check()
{
  mybutton.Update();
  return mybutton.clicks;   
}
/*******************************************************************/
/*  任务标记函数                                                     */
/*******************************************************************/
void TaskRemarks()
{
   static unsigned char i=0;   //必须是static类型

   for(i=0;i<TASKS_MAX;i++)   //逐个任务处理
   {
     if(TaskComps[i].Timer) //时间不为0
     {
      TaskComps[i].Timer--; //减去一个节拍
      if(TaskComps[i].Timer<=0)//时间减完了
      {
       TaskComps[i].Timer = TaskComps[i].ItvTime;  //恢复计时器值，重新下一次
       TaskComps[i].Run = 1; //任务可以运行
      }
     }
   }
}
/*******************************************************************/
/*  任务进程函数                                                     */
/*******************************************************************/
void TaskProcess()
{
   static unsigned char i=0;  //必须是static类型

   for(i=0;i<TASKS_MAX;i++) //逐个任务时间处理
   {
    if(TaskComps[i].Run)  //任务可以运行
    {
       TaskComps[i].TaskHook();  //调用任务函数
       TaskComps[i].Run = 0; //标志清0
    }
   }
}
/*******************************************************************/
/*  按键检测任务函数                                                     */
/*******************************************************************/
void TaskKeyCheck()
{
  //LOG_INFO("key_check");
  key_states = mybutton_check();
  switch(key_states){
        case _FSM_KEY_TAP:{ //单击
          LOG_INFO("single clicks");
          setting_change_to_next();
        }
    break;
        case _FSM_KEY_DOUBLE:{ //双击
          LOG_INFO("double clicked");
          setting_value_rise(sys_state_s.system_states);
        }
    break;
        case _FSM_KEY_TRIPLE:{ //三击
          LOG_INFO("triple clicked");
          setting_value_fall(sys_state_s.system_states);
        }
    break;
        case _FSM_KEY_LONG_PRESS:{  //长按
          LOG_INFO("long clicked");
          setting_enter_or_exit();
        }
    break;
        default:{ //未定义
          //LOG_INFO("no-defined");
        }
    break;
  }
  key_states = _FSM_KEY_MAX_NUM;  
}
/*******************************************************************/
/*  更新时间显示任务函数                                                     */
/*******************************************************************/
void TaskUpdateTime()
{
  //LOG_INFO("update_time");

    digitalWrite(test_led_pin,!(digitalRead(test_led_pin)));
    intensity_to_light();//改变亮度
    if(sys_state_s.system_states != _DIS_IDLE) return;    
    
    temp_date.t_hour = now_date.t_hour;
    temp_date.t_min = now_date.t_min;
    temp_date.t_sec = now_date.t_sec; 
//    serial_log_disptime(); 

    seg_dis_time(temp_date.t_hour,temp_date.t_min,temp_date.t_sec); //数码管显示时间

    if(temp_date.t_day != now_date.t_day){
      temp_date.t_year == now_date.t_year;
      temp_date.t_month == now_date.t_month;
      temp_date.t_day == now_date.t_day;
      matrix_screen_dispdate(temp_date.t_year,temp_date.t_month,temp_date.t_day);//点阵屏显示日期
      temp_date.t_week == now_date.t_week;
      matrix_screen_dispweek(temp_date.t_week);//点阵屏显示星期
    }
}
/*******************************************************************/
/*  设置时间任务函数                                                     */
/*******************************************************************/
void TaskSetTime()
{
  //LOG_INFO("set_time");
  //wdt_reset(); //喂狗
  //(*func)();//调用函数指针所指向的函数,不能指向 NULL
  switch(sys_state_s.system_states)
  {
    case _DIS_SET_HOUR: 
      display_set_onoff(_LED_HOUR_OFF);break;
    case _DIS_SET_MIN: 
      display_set_onoff(_LED_MIN_OFF);break;
    case _DIS_SET_SEC: 
      display_set_onoff(_LED_SEC_OFF);break;
    case _DIS_SET_YEAR: 
      display_set_onoff(_LED_YEAR_OFF);break;
    case _DIS_SET_MONTH: 
      display_set_onoff(_LED_MONTH_OFF);break;
    case _DIS_SET_DAY: 
      display_set_onoff(_LED_DAY_OFF);break;
    case _DIS_SET_WEEK: 
      display_set_onoff(_LED_WEEK_OFF);break;
    default: break;
  }
}
/*******************************************************************/
/*  读取RTC时间值任务函数                                                     */
/*******************************************************************/
void TaskReadRTC()
{
    if(sys_state_s.system_states != _DIS_IDLE) return;//空闲状态
    
    
    myclock.getTime(); //获取RTC时间
    now_date.t_hour = myclock.hour; //小时
    now_date.t_min = myclock.minute; //分钟
    now_date.t_sec = myclock.second; //秒
    now_date.t_year = myclock.year; //年
    now_date.t_month = myclock.month; //月
    now_date.t_day = myclock.dayOfMonth; //日
    now_date.t_week = myclock.dayOfWeek; //星期      
}
/*******************************************************************/
/*  产生PWM任务函数                                                     */
/*******************************************************************/
void TaskPWMout()
{
  static int count=0;

  if(count <= seg_light_value){
    digitalWrite(pwm_pin,HIGH);
    count++;
  }else if((count>seg_light_value)&&(count < 10)){
    digitalWrite(pwm_pin,LOW);
    count++;
  }else if(count == 10){
    count = 0;
  }
}
/*******************************************************************/
/*  切换到下一个设置显示                                                     */
/*******************************************************************/
void setting_change_to_next()
{
  switch(sys_state_s.system_states)
  {
    case _DIS_SET_HOUR: 
      sys_state_s.system_states = _DIS_SET_MIN;break;
    case _DIS_SET_MIN: 
      sys_state_s.system_states = _DIS_SET_SEC;break;
    case _DIS_SET_SEC: 
      sys_state_s.system_states = _DIS_SET_YEAR;break;
    case _DIS_SET_YEAR: 
      sys_state_s.system_states = _DIS_SET_MONTH;break;
    case _DIS_SET_MONTH: 
      sys_state_s.system_states = _DIS_SET_DAY;break;
    case _DIS_SET_DAY: 
      sys_state_s.system_states = _DIS_SET_WEEK;break;
    case _DIS_SET_WEEK: 
      sys_state_s.system_states = _DIS_SET_HOUR;break;
    default: break;
  }
}
/*******************************************************************/
/*  进入或退出设置                                                     */
/*******************************************************************/
void setting_enter_or_exit()
{
  
  if(sys_state_s.system_states == _DIS_IDLE) //空闲状态
  {
    sys_state_s.system_states = _DIS_SET_HOUR; //进入设置小时
    temp_date = now_date; //暂存时间
  }
  else //设置状态
  {
    sys_state_s.system_states = _DIS_IDLE; //进入空闲状态
    set_now_times();
    g_lc.shutdown(0, false);
    g_lc.shutdown(1, false);
    g_lc.shutdown(2, false);
    g_lc.shutdown(3, false);
  }
}
/*******************************************************************/
/*  设置RTC时间                                                     */
/*******************************************************************/
void set_now_times()
{
  temp_date.t_year = temp_date.t_year + 2000;
  myclock.fillByYMD(temp_date.t_year,temp_date.t_month,temp_date.t_day);
  myclock.fillByHMS(temp_date.t_hour,temp_date.t_min,temp_date.t_sec);
  myclock.fillDayOfWeek(temp_date.t_week);
  myclock.setTime();//write time to the RTC chip 
}
/*******************************************************************/
/*  数值上调                                                     */
/*******************************************************************/
void setting_value_rise(uint8_t display_states)
{
  switch(display_states){
    case _DIS_SET_INVALID://无效状态
      break;
    case _DIS_SET_HOUR:if(temp_date.t_hour < 23){temp_date.t_hour++;}else{temp_date.t_hour = 0;}   //小时加1
      break;
    case _DIS_SET_MIN:if(temp_date.t_min < 59){temp_date.t_min++;}else{temp_date.t_min = 0;}//分钟加1
      break;
    case _DIS_SET_SEC:if(temp_date.t_sec < 59){temp_date.t_sec++;}else{temp_date.t_sec = 0;}//秒加1
      break;
    case _DIS_SET_YEAR:if(temp_date.t_year < 50){temp_date.t_year++;}else{temp_date.t_year = 22;}//年加1
      break;
    case _DIS_SET_MONTH:if(temp_date.t_month < 12){temp_date.t_month++;}else{temp_date.t_month = 1;}//月加1
      break;
    case _DIS_SET_DAY:if(temp_date.t_day < 30){temp_date.t_day++;}else{temp_date.t_day = 1;}//日加1
      break;
    case _DIS_SET_WEEK:if(temp_date.t_week < 7){temp_date.t_week++;}else{temp_date.t_week = 1;}//星期加1
      break;
    case _DIS_IDLE://无刷新的空闲状态
      break;
    default: 
      break;
  }
}
/*******************************************************************/
/*  数值下调                                                     */
/*******************************************************************/
void setting_value_fall(uint8_t display_states)
{
  switch(display_states){
    case _DIS_SET_INVALID://无效状态
      break;
    case _DIS_SET_HOUR:if(temp_date.t_hour > 0){temp_date.t_hour--;}else{temp_date.t_hour = 23;}   //小时减1
      break;
    case _DIS_SET_MIN:if(temp_date.t_min > 0){temp_date.t_min--;}else{temp_date.t_min = 59;}//分钟减1
      break;
    case _DIS_SET_SEC:if(temp_date.t_sec > 0){temp_date.t_sec--;}else{temp_date.t_sec = 59;}//秒减1
      break;
    case _DIS_SET_YEAR:if(temp_date.t_year > 22){temp_date.t_year--;}else{temp_date.t_year = 50;}//年减1
      break;
    case _DIS_SET_MONTH:if(temp_date.t_month > 1){temp_date.t_month--;}else{temp_date.t_month = 12;}//月减1
      break;
    case _DIS_SET_DAY:if(temp_date.t_day > 1){temp_date.t_day--;}else{temp_date.t_day = 30;}//日减1
      break;
    case _DIS_SET_WEEK:if(temp_date.t_week > 1){temp_date.t_week--;}else{temp_date.t_week = 7;}//星期减1
      break;
    case _DIS_IDLE://无刷新的空闲状态
      break;
    default: 
      break;
  }  
}

/*******************************************************************/
/*  设置模式显示闪烁函数                                                     */
/*******************************************************************/
void display_set_onoff(uint8_t led_onoff)
{
  static uint8_t s_led_onoff=0;
  s_led_onoff = led_onoff;
//  serial_log_set_time(s_led_onoff);
  if(sys_state_s.system_states == _DIS_SET_HOUR || sys_state_s.system_states == _DIS_SET_MIN || sys_state_s.system_states == _DIS_SET_SEC){
//    matrix_screen_set_time(s_led_onoff);
      seg_set_time(s_led_onoff);
  }
  else if(sys_state_s.system_states == _DIS_SET_YEAR || sys_state_s.system_states == _DIS_SET_MONTH || sys_state_s.system_states == _DIS_SET_DAY){
    matrix_screen_set_date(s_led_onoff);
  }
  else if(sys_state_s.system_states == _DIS_SET_WEEK){
    matrix_screen_set_week(s_led_onoff);
  }
}

/*******************************************************************/
/*  点阵屏显示时间                                                     */
/*******************************************************************/
void matrix_screen_disptime(uint8_t Hour,uint8_t Min,uint8_t Sec)
{
  uint8_t hour_H,hour_L;
  uint8_t min_H,min_L;
  uint8_t sec_H,sec_L;

  seg_dpoint_off_on = !seg_dpoint_off_on;
  if(Hour<0 || Hour > 23) Hour = 0;
  if(Min<0 || Min > 59) Min = 0;
  if(Sec<0 || Sec > 59) Sec = 0;

    hour_H = Hour/10;
    hour_L = Hour%10;
    min_H = Min/10;
    min_L = Min%10;
    sec_H = Sec/10;
    sec_L = Sec%10;

    //点阵屏显示时分秒
    for(uint8_t i=0;i<8;i++){ 
    g_lc.setRow(3, i, spx_[hour_H][i]|sp_x[hour_L][i]);
    g_lc.setRow(2, i, sp_x[min_H][i]|Point_[i]);
    g_lc.setRow(1, i, spx_[min_L][i]|_Point[i]);
    g_lc.setRow(0, i, spx_[sec_H][i]|sp_x[sec_L][i]);
    }
}
void seg_dis_time(uint8_t Hour,uint8_t Min,uint8_t Sec)
{
  uint8_t hour_H,hour_L;
  uint8_t min_H,min_L;
  uint8_t sec_H,sec_L;
  
//  if(Hour<0 || Hour > 23) Hour = 0;
//  if(Min<0 || Min > 59) Min = 0;
//  if(Sec<0 || Sec > 59) Sec = 0;

    hour_H = Hour/10;
    hour_L = Hour%10;
    min_H = Min/10;
    min_L = Min%10;
    sec_H = Sec/10;
    sec_L = Sec%10;
    
    seg_dpoint_off_on = !seg_dpoint_off_on;
    //数码管显示小时和分钟

    
    digitalWrite(rck_pin,LOW);
    if(seg_dpoint_off_on) shiftOut(data_pin,clk_pin,MSBFIRST,seg[min_L]);
    else shiftOut(data_pin,clk_pin,MSBFIRST,seg[min_L]|seg[11]);
    delay(10);//延迟很重要,显示不闪烁
    shiftOut(data_pin,clk_pin,MSBFIRST,seg[min_H]);
    delay(10);//延迟很重要,显示不闪烁
    shiftOut(data_pin,clk_pin,MSBFIRST,seg[hour_L]);
    delay(10);//延迟很重要,显示不闪烁
    shiftOut(data_pin,clk_pin,MSBFIRST,seg[hour_H]);
    digitalWrite(rck_pin,HIGH);  
}
/*******************************************************************/
/*  数码管设置时间                                                     */
/*******************************************************************/
void seg_set_time(uint8_t led_onoff)
{
  static boolean s_dis_dynamic_flag=false; //动态显示标志位
  s_dis_dynamic_flag = !s_dis_dynamic_flag;
  seg_dis_time(temp_date.t_hour,temp_date.t_min,temp_date.t_sec);
  if(s_dis_dynamic_flag)
  {
    
  }
  else
  {
     switch(led_onoff)
     {
      case _LED_HOUR_OFF: {
        
      }break;
      case _LED_MIN_OFF:{
        
      }break;
      default: break;
     }    
  }
}
/*******************************************************************/
/*  点阵屏设置时间                                                     */
/*******************************************************************/
void matrix_screen_set_time(uint8_t led_onoff)
{
  static boolean s_dis_dynamic_flag=false; //动态显示标志位
  s_dis_dynamic_flag = !s_dis_dynamic_flag;
  matrix_screen_disptime(temp_date.t_hour,temp_date.t_min,temp_date.t_sec);
  if(s_dis_dynamic_flag)
  {
    g_lc.shutdown(0, false);
    g_lc.shutdown(1, false);
    g_lc.shutdown(2, false);
    g_lc.shutdown(3, false);
  }
  else
  {
     switch(led_onoff)
     {
      case _LED_HOUR_OFF: g_lc.shutdown(3, true);    g_lc.shutdown(1, false);    g_lc.shutdown(2, false);    g_lc.shutdown(0, false);break;
      case _LED_MIN_OFF: g_lc.shutdown(3, false);    g_lc.shutdown(1, true);    g_lc.shutdown(2, true);    g_lc.shutdown(0, false);break;
      case _LED_SEC_OFF: g_lc.shutdown(3, false);    g_lc.shutdown(1, false);    g_lc.shutdown(2, false);    g_lc.shutdown(0, true);break;
      default: break;
     }    
  }
}
/*******************************************************************/
/*  点阵屏显示日期                                                     */
/*******************************************************************/
void matrix_screen_dispdate(uint8_t Year,uint8_t Month,uint8_t Day)
{
  uint8_t year_H,year_L;
  uint8_t month_H,month_L;
  uint8_t day_H,day_L;
  if(Year<0 || Year > 50) Year = 50;
  if(Month<0 || Month > 12) Month = 1;
  if(Day<0 || Day > 31) Day = 1;

    year_H = Year/10;
    year_L = Year%10;
    month_H = Month/10;
    month_L = Month%10;
    day_H = Day/10;
    day_L = Day%10;
    for(uint8_t i=0;i<8;i++){ 
      g_lc.setRow(7, i, spx_[month_H][i]|sp_x[month_L][i]);
      g_lc.setRow(6, i, Month_CH[i]);
      g_lc.setRow(5, i, spx_[day_H][i]|sp_x[day_L][i]);
      g_lc.setRow(4, i, Day_CH[i]);
    }    
//    for(uint8_t i=0;i<8;i++){ 
//    g_lc.setRow(3, i, spx_[year_H][i]|sp_x[year_L][i]);
//    g_lc.setRow(2, i, sp_x[month_H][i]|Point_[i]);
//    g_lc.setRow(1, i, spx_[month_L][i]|_Point[i]);
//    g_lc.setRow(0, i, spx_[day_H][i]|sp_x[day_L][i]);
//    }
}
/*******************************************************************/
/*  点阵屏设置日期                                                     */
/*******************************************************************/
void matrix_screen_set_date(uint8_t led_onoff)
{
  static boolean s_dis_dynamic_flag=false; //动态显示标志位
  s_dis_dynamic_flag = !s_dis_dynamic_flag;
  matrix_screen_dispdate(temp_date.t_year,temp_date.t_month,temp_date.t_day);
  if(s_dis_dynamic_flag)
  {
    g_lc.shutdown(0, false);
    g_lc.shutdown(1, false);
    g_lc.shutdown(2, false);
    g_lc.shutdown(3, false);
  }
  else
  {
     switch(led_onoff)
     {
      case _LED_YEAR_OFF: g_lc.shutdown(3, true);    g_lc.shutdown(1, false);    g_lc.shutdown(2, false);    g_lc.shutdown(0, false);break;
      case _LED_MONTH_OFF: g_lc.shutdown(3, false);    g_lc.shutdown(1, true);    g_lc.shutdown(2, true);    g_lc.shutdown(0, false);break;
      case _LED_DAY_OFF: g_lc.shutdown(3, false);    g_lc.shutdown(1, false);    g_lc.shutdown(2, false);    g_lc.shutdown(0, true);break;
      default: break;
     }    
  }
}
/*******************************************************************/
/*  点阵屏显示星期                                                     */
/*******************************************************************/
void matrix_screen_dispweek(uint8_t Week)
{
  uint8_t week_H,week_L;
  
  if(Week<1 || Week > 7) Week = 1;

    week_H = Week/10;
    week_L = Week%10;
    
    for(uint8_t i=0;i<8;i++){ 
      g_lc.setRow(2, i, weekx_[week_L][i]);
    }
}
/*******************************************************************/
/*  点阵屏显示星期                                                     */
/*******************************************************************/
void matrix_screen_disptemperature()
{
  uint8_t temperature_value,temperature_H,temperature_L;

  temperature_value=31;
  temperature_H = temperature_value/10;
  temperature_L = temperature_value%10;
  
  for(uint8_t i=0;i<8;i++){ 
    g_lc.setRow(0, i, spx_[temperature_H][i]|sp_x[temperature_L][i]);
  }
}
/*******************************************************************/
/*  点阵屏设置日期                                                     */
/*******************************************************************/
void matrix_screen_set_week(uint8_t led_onoff)
{
  static boolean s_dis_dynamic_flag=false; //动态显示标志位
  s_dis_dynamic_flag = !s_dis_dynamic_flag;
  matrix_screen_dispweek(temp_date.t_week);
  if(s_dis_dynamic_flag)
  {
    g_lc.shutdown(0, false);
    g_lc.shutdown(1, true);
    g_lc.shutdown(2, true);
    g_lc.shutdown(3, true);
  }
  else
  {
     switch(led_onoff)
     {
      case _LED_WEEK_OFF: g_lc.shutdown(3, true);    g_lc.shutdown(1, true);    g_lc.shutdown(2, true);    g_lc.shutdown(0, true);break;
      default: break;
     }    
  }
}

/*******************************************************************/
/*  串口打印时间                                                     */
/*******************************************************************/
void serial_log_disptime(void)
{
      timedata += temp_date.t_hour;
      timedata += ":";
      timedata += temp_date.t_min;
      timedata += ":";
      timedata += temp_date.t_sec;
      timedata += "  ";
      timedata += temp_date.t_year;
      timedata += "/";
      timedata += temp_date.t_month;
      timedata += "/";
      timedata += temp_date.t_day;
      timedata += "  ";
      timedata += temp_date.t_week;
      LOG_INFO(timedata);
      timedata = "";  
}

void serial_log_set_time(uint8_t led_onoff)
{
  static boolean s_dis_dynamic_flag=false; //动态显示标志位
  s_dis_dynamic_flag = !s_dis_dynamic_flag;
  if(s_dis_dynamic_flag)
  {
    if(led_onoff == _LED_HOUR_OFF)
    {
      timedata += "--";
      timedata += ":";
      timedata += temp_date.t_min;
      timedata += ":";
      timedata += temp_date.t_sec;
      timedata += "  ";
      timedata += temp_date.t_year;
      timedata += "/";
      timedata += temp_date.t_month;
      timedata += "/";
      timedata += temp_date.t_day;
      timedata += "  ";
      timedata += temp_date.t_week;      
    }
    if(led_onoff == _LED_MIN_OFF)
    {
      timedata += temp_date.t_hour;
      timedata += ":";
      timedata += "--";
      timedata += ":";
      timedata += temp_date.t_sec;
      timedata += "  ";
      timedata += temp_date.t_year;
      timedata += "/";
      timedata += temp_date.t_month;
      timedata += "/";
      timedata += temp_date.t_day;
      timedata += "  ";
      timedata += temp_date.t_week;     
    }
    if(led_onoff == _LED_SEC_OFF)
    {
      timedata += temp_date.t_hour;
      timedata += ":";
      timedata += temp_date.t_min;
      timedata += ":";
      timedata += "--";
      timedata += "  ";
      timedata += temp_date.t_year;
      timedata += "/";
      timedata += temp_date.t_month;
      timedata += "/";
      timedata += temp_date.t_day;
      timedata += "  ";
      timedata += temp_date.t_week;     
    }
    if(led_onoff == _LED_YEAR_OFF)
    {
      timedata += temp_date.t_hour;
      timedata += ":";
      timedata += temp_date.t_min;
      timedata += ":";
      timedata += temp_date.t_sec;
      timedata += "  ";
      timedata += "****";
      timedata += "/";
      timedata += temp_date.t_month;
      timedata += "/";
      timedata += temp_date.t_day;
      timedata += "  ";
      timedata += temp_date.t_week;     
    }
    if(led_onoff == _LED_MONTH_OFF)
    {
      timedata += temp_date.t_hour;
      timedata += ":";
      timedata += temp_date.t_min;
      timedata += ":";
      timedata += temp_date.t_sec;
      timedata += "  ";
      timedata += temp_date.t_year;
      timedata += "/";
      timedata += "**";
      timedata += "/";
      timedata += temp_date.t_day;
      timedata += "  ";
      timedata += temp_date.t_week;    
    }
    if(led_onoff == _LED_DAY_OFF)
    {
      timedata += temp_date.t_hour;
      timedata += ":";
      timedata += temp_date.t_min;
      timedata += ":";
      timedata += temp_date.t_sec;
      timedata += "  ";
      timedata += temp_date.t_year;
      timedata += "/";
      timedata += temp_date.t_month;
      timedata += "/";
      timedata += "**";
      timedata += "  ";
      timedata += temp_date.t_week;    
    }
    if(led_onoff == _LED_WEEK_OFF)
    {
      timedata += temp_date.t_hour;
      timedata += ":";
      timedata += temp_date.t_min;
      timedata += ":";
      timedata += temp_date.t_sec;
      timedata += "  ";
      timedata += temp_date.t_year;
      timedata += "/";
      timedata += temp_date.t_month;
      timedata += "/";
      timedata += temp_date.t_day;
      timedata += "  ";
      timedata += "*";    
    }    
  }
  else
  {
    timedata += temp_date.t_hour;
    timedata += ":";
    timedata += temp_date.t_min;
    timedata += ":";
    timedata += temp_date.t_sec;
    timedata += "  ";
    timedata += temp_date.t_year;
    timedata += "/";
    timedata += temp_date.t_month;
    timedata += "/";
    timedata += temp_date.t_day;
    timedata += "  ";
    timedata += temp_date.t_week; 
  }
    LOG_INFO(timedata);
    timedata = "";   
}
