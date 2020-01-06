/*
 * File:   main.c
 * Author: Tianming
 *
 * Created on April 12, 2017, 6:16 PM
 */

#include "xc.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stdint.h"


#define FRAME_PER 5
// PIC24FJ64GA002 Configuration Bit Settings
// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))


int mole;
int points;
int timerhelper = 0;
int color;
unsigned char readKeyPadRAW(void);
int counter= 0;
/*
void __attribute__((__interrupt__,__auto_psv__)) _T1Interrupt(void){
    IFS0bits.T1IF = 0;    
    counter++;
    displaymole(counter);
    //renewmole();
}
 */


void write0c(){
LATBbits.LATB6 = 1;
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
LATBbits.LATB6 = 0;
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
}

void write1c(){
LATBbits.LATB6 = 1;
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");
asm("nop");	
LATBbits.LATB6 = 0;
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
}




void writeblue(){
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();

}

void writered(){
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();

}

void writegreen(){
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write1c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
}

void offled(){
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
write0c();
    
}

void wingame(){
int i = 0;

for(i = 0; i < 6000; i++){
delay5000us();
}
for(i = 0; i < 64; i++){
    writered();
}

for(i = 0; i < 3000; i++){
delay5000us();
}

for(i = 0; i < 64; i++){
    writegreen();
}

for(i = 0; i < 3000; i++){
delay5000us();
}

for(i = 0; i < 64; i++){
writeblue();
}

for(i = 0; i < 3000; i++){
delay5000us();
}

for(i = 0; i < 64; i++){
    offled();
}
}

void displaymole(int moleindex){
    int i;
    if(points == 4000){
    T2CONbits.TON = 0; //game is over
        lcd_setCursor(0,0);
        lcd_printStr("You Win!!");

    wingame();
    
  
    }
        
    if(points < 0){
        points = 0;
    }
        color = points / 10;
        if(color > 255){
            color = 255;
        }

        if(color < 0){
            color = 0;
        }
        
if(moleindex == 1){
    drawFrame(color);
    drawFrame(color);
  
   for(i = 0; i < 6;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 54;i++){
    offled();   
   }        
        
    }
    
    if(moleindex == 2){
  
   for(i = 0; i < 3 ;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 51;i++){
    offled();   
   }        
    }

    if(moleindex == 3){
      
  
   for(i = 0; i < 6;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 48;i++){
    offled();   
   }        
    }

 if(moleindex == 4){
      
  
   for(i = 0; i < 24;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 34;i++){
    offled();   
   }        
    }

 if(moleindex == 5){
      
  
   for(i = 0; i < 27;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 31;i++){
    offled();   
   }        
    }
    
     if(moleindex == 6){
      
  
   for(i = 0; i < 30;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 28;i++){
    offled();   
   }        
    }

 if(moleindex == 7){
      
  
   for(i = 0; i < 48;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    }
 if(moleindex == 8){
      
  
   for(i = 0; i < 51;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 3;i++){
    offled();   
   }        
    }
 if(moleindex == 9){
      
  
   for(i = 0; i < 54;i++){
    offled();   
   }          
    drawFrame(color);
    drawFrame(color);
   for(i = 0; i < 6;i++){
    offled();   
   }        
    drawFrame(color);
    drawFrame(color);
    }
}


void delay5000us(){

    int a;

    for(a=0; a<1000; a++){
 
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	               

    }

}

void delay50us(){

    int a;

    for(a=0; a<90; a++){
 
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	               

    }

}


void longdelay(){

    int a;

    for(a=0; a<15000; a++){
 
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	
asm("nop");	               

    }

}

void buzzerapi(int freq){
int b = 0;
int k = 0;
while(k < 62500/freq){
LATBbits.LATB4 = 1;
for(b = 0; b < freq; b++)
{
asm("nop");    
}    
LATBbits.LATB4 = 0;
for(b = 0; b < freq; b++)
{
asm("nop");    
}
k++;
}
LATBbits.LATB4 = 0;

}


int main(void) {
    setup2();
    int j;
    int delay;
    init7segKey();
    lcd_init();

    lcd_printStr("  Start!");

    int level= 0;
    //mole(1);
 //   renewmole();
   //  renewmole();
 unsigned  char memory;

    while(1){

        if (points == 500 && level == 0){
            buzzerapi(1000);
            buzzerapi(2000);
            buzzerapi(1000);
            level = 1;
            PR2 = 50000;    
        }
        if (points == 1000 && level == 1){
            buzzerapi(1000);
            buzzerapi(2000);
            buzzerapi(1000);
             level = 2;
            PR2 = 40000;    
        }
        if (points == 2000 && level == 2){
            buzzerapi(1000);
            buzzerapi(2000);
            buzzerapi(1000);
            level = 3;
            PR2 = 25000;    
        }
                if (points == 3000 && level == 3){

                    buzzerapi(1000);
            buzzerapi(2000);
            buzzerapi(1000);
            level = 4;
            PR2 = 15000;    
           
        }  
        if(points == 0){
           PR1 = 65000; 
        }
 unsigned  char temp;
       //    displaymole(5);
 temp = '\0';
 
   while(temp == '\0'){
       //displaymole(8);
            temp = readKeyPadRAW();    
            while (memory == temp){
            temp = readKeyPadRAW();    
                
            }
            memory = temp;
            
            if (temp == 'd'){
              //  displaymole(1);
  setup2();
  init7segKey();
  points = 0;
      lcd_setCursor(0,0);  
      lcd_printStr("  Start!");
longdelay();
              //  displaymole(1);
              //  buzzerapi(200);
            }
            if (temp == '1'){
              //  displaymole(1);
                molehit(1);
                longdelay();
              //  displaymole(1);
              //  buzzerapi(200);
            }
                        if (temp == '2'){
               molehit(2);
               longdelay();
                          //  displaymole(2);
                          //  buzzerapi(1000);
            }
                        if (temp == '3'){
               molehit(3);
               longdelay();
            }
                        if (temp == '4'){
                molehit(4);
                longdelay();
            }
                        if (temp == '5'){
                molehit(5);
                longdelay();
            }
                        if (temp == '6'){
                molehit(6);
                longdelay();
            }
                        if (temp == '7'){
                molehit(7);
                longdelay();
            }
                        if (temp == '8'){
                molehit(8);
                longdelay();
            }
                        if (temp == '9'){
                molehit(9);
                longdelay();
            }
            
                    TMR1 = 0;
        _T1IF = 0;
            //showChar7seg(pastKeys[1],1);
            //showChar7seg(pastKeys[0],0);
        }
  //displaymole(4);
 //     displaymole(4);
}
    return 0;
    
}


void setup2()
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;

}


void init7segKey(){
    TRISA = 0b1111111111111111;
    LATA = 0x0000;
    TRISB = 0b0000000000000011;
    LATB = 0xf000;
    T2CON = 0060; // turn off timer, prescalar 1:1, use Tcy as clk source
    PR2 = 65000;
    TMR2 = 0;
    _T2IF = 0; // equivalent to IFS0bits.T1IF = 0;
    _T2IE = 1; // equivalent to IFS0bits.T1IF = 0
    T2CONbits.TON = 1; // now turn on the timer   

    
    T1CON = 0000; // turn off timer, prescalar 1:1, use Tcy as clk source
    PR1 = 15999;
    TMR1 = 0;
    _T1IF = 0; // equivalent to IFS0bits.T1IF = 0;
    T1CONbits.TON = 0;
    I2C2CONbits.I2CEN = 0;
    I2C2BRG = 157;
    IFS3bits.MI2C2IF = 0;
    I2C2CONbits.I2CEN = 1;




    CNPU1bits.CN2PUE = 1;
    CNPU1bits.CN3PUE = 1;
    CNPU2bits.CN30PUE = 1;
    CNPU2bits.CN29PUE = 1;
}

unsigned char readKeyPadRAW(void){
    _LATB12 = 1;
    _LATB13 = 1;
    _LATB14 = 1;
    _LATB15 = 1;
    int key;
    static unsigned char r0[] = {'\0','\0','\0','\0', //00xx
                 '\0','\0','\0','1',  //01xx
                 '\0','\0','\0','2',  //10xx
                 '\0','3','a','\0'};  //11xx
    _LATB12 = 0;
    delay50us();
    key = PORTA & 0x000f;
    _LATB12 = 1;
    if(key != 0x000f)
    return r0[key];
    
    static unsigned char r1[] = {'\0','\0','\0','\0', //00xx
                 '\0','\0','\0','4',  //01xx
                 '\0','\0','\0','5',  //10xx
                 '\0','6','b','\0'};  //11xx
    _LATB13 = 0;
    delay50us();
    key = PORTA & 0x000f;
    _LATB13 = 1;
    if(key != 0x000f)
      return r1[key];
    
    static unsigned char r2[] = {'\0','\0','\0','\0', //00xx
                 '\0','\0','\0','7',  //01xx
                 '\0','\0','\0','8',  //10xx
                 '\0','9','c','\0'};  //11xx
    _LATB14 = 0;
    delay50us();
    key = PORTA & 0x000f;
    _LATB14 = 1;
    if(key != 0x000f)
        return r2[key];
    
    static unsigned char r3[] = {'\0','\0','\0','\0', //00xx
                 '\0','\0','\0','e',  //01xx
                 '\0','\0','\0','0',  //10xx
                 '\0','f','d','\0'};  //11xx
    _LATB15 = 0;
    delay50us();
    key = PORTA & 0x000f;
    _LATB15 = 1;
    if(key != 0x000f)
        return r3[key];
    
 //   return '2';
}




/*
unsigned int readKeyPadRAW(void) {
int ReadKeyPadRAW1 = 0;
int ReadKeyPadRAW2 = 0;
int ReadKeyPadRAW3 = 0;
int ReadKeyPadRAW4 = 0;
unsigned int djoReturnValue = 0;

LATBbits.LATB12 = 0; // set Row 1 to low
LATBbits.LATB13 = 1;
LATBbits.LATB14 = 1;
LATBbits.LATB15 = 1;
delay50us();// Scope shows this could be just 1-2 cycles
ReadKeyPadRAW1 = PORTA; // sense all 4 columns of row 1; button press = 0
LATBbits.LATB12 = 1;
LATBbits.LATB13 = 0;
LATBbits.LATB14 = 1;
LATBbits.LATB15 = 1;
delay50us();
ReadKeyPadRAW2 = PORTA;
LATBbits.LATB12 = 1;
LATBbits.LATB13 = 1;
LATBbits.LATB14 = 0;
LATBbits.LATB15 = 1;
delay50us();
ReadKeyPadRAW3 = PORTA;
LATBbits.LATB12 = 1;
LATBbits.LATB13 = 1;
LATBbits.LATB14 = 1;
LATBbits.LATB15 = 0;
delay50us();
ReadKeyPadRAW4 = PORTA;
djoReturnValue = ~((ReadKeyPadRAW4 << 0) | (ReadKeyPadRAW3 << 4) | (ReadKeyPadRAW2 << 8) | (ReadKeyPadRAW1 << 12));
return djoReturnValue;
}
*/






//int randomnumber = 3;
void renewmole(){
//randomnumber = randomnumber* 17357;
//srand((unsigned) time(null));
int newmole = mole;
while(newmole == mole){
    mole = rand() % 9 + 1;
}
//mole = randomnumber % 9 + 1;
timerhelper = 0;
displaymole(mole);
}


void molehit(int keyinput){

    if (mole == keyinput){
        buzzerapi(600);
        points += 100;
        renewmole();
    }
    else{
        buzzerapi(300);
        points -= 100;
    //    renewmole();
    }
    
}


//renew the output
void __attribute__((__interrupt__,__auto_psv__)) _T2Interrupt(void) {
    IFS0bits.T2IF = 0;    
    if (timerhelper < 3){
        timerhelper ++;
    }
    else{
        points-= 100;
    renewmole();
    timerhelper = 0;
    }
}    


void showpoint(){
//    lcd_printChar(point);    
}



void display(char L, char R){
//    showChar7seg(L,1);
  // __delay_ms(50);
  //  showChar7seg(R,0);
  // __delay_ms(50);
}

void setup()
{
    /*
    AD1PCFG = 0x9fff;
    T1CON = 0x8010;
    PR1 = 35000;
    TMR1 = 0;
    _T1IF = 0;
    _T1IE = 1;

    TRISA = 0x0000;                    
   // LATA = 0x0001;
    */
     CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff; // all digital
    TRISA = 0;
  //  LATA = 0;
    T2CON = 0060; // turn off timer, prescalar 1:1, use Tcy as clk source
    PR2 = 65000;
    TMR2 = 0;
    _T2IF = 0; // equivalent to IFS0bits.T1IF = 0;
    _T2IE = 1; // equivalent to IFS0bits.T1IF = 0
  //  T2CONbits.TON = 1; // now turn on the timer   
    LATA = 0b0000000000001111;
    LATB = 0b1111000000000000;
 

}

void writeColor (int r, int g, int b){         
    int i;
    
    for (i =0; i<8 ;i++){  
        if(0b10000000 & r)
           write1c();
        else
            write0c();
        r=r<<1;
    }  
    for ( i=0; i<8; i++){       
        if(0b10000000 & g)
            write1c();
        else
            write0c();
        g=g<<1;
   }
    for ( i=0; i<8; i++){         
        if(0b10000000 & b)
            write1c();
        else
            write0c();
        b=b<<1;
    }
 }


void writePacCol (uint32_t PackedColor){       
    int i;
    int r;
    int g;
    int b;
    r = getR(PackedColor);
    g = getG(PackedColor);
    b = getB(PackedColor);
    for (i =0; i<8 ;i++){   
        if(0b10000000 & r)
           write1c();
        else
            write0c();
        r=r<<1;
    }  
    for ( i=0; i<8; i++){       
        if(0b10000000 & g)
            write1c();
        else
            write0c();
        g=g<<1;
   }
    for ( i=0; i<8; i++){           
        if(0b10000000 & b)
            write1c();
        else
            write0c();
        b=b<<1;
    }
        delay50us();
}



void drawFrame(int frame){

    int r;

    int b;

    r= frame;

    b= 255-frame;

    writeColor(0, r, b);    

}

void Paintpurecolor(int Red, int Grn, int Blu){
int i;
for(i = 0; i< 64; i++){
writeColor(Red, Grn, Blu);
}	
delay5000us;
		
}

void Writesinglepixel(uint32_t PackedColor, int index){
int i;
for(i = 0; i< index; i++){
offled();	
}
writePacCol(PackedColor);
for(i = 0; i< (63 - index); i++)
{
offled();
}
}


void erase(){
int i;
for(i = 0; i< 64; i++){
offled();	
}
}
	

	
uint32_t packColor(int Red, int Grn, int Blu){
    long R = Red;
    long B = Blu;
    long G = Grn;
    unsigned long int RGBval = 0;
    RGBval = ((R<<16)| (G<<8)|B);
    return RGBval;
}
int getR(uint32_t RGBval){
    int Red = 0;
    Red = (RGBval>>16);
    return Red;
}
int getG(uint32_t RGBval){
    int Grn = 0;
    Grn = (RGBval>>8);
    return Grn;
}
int getB(uint32_t RGBval){
    int Blu = 0;
    Blu = (RGBval>>0);
    return Blu;
}












uint32_t wheel(int wheelpos)
{  
    int Red;
    int Green;
    int Blue;
    uint32_t Colorp;
    wheelpos=255-wheelpos;              
    if(wheelpos<85)
    {
        Red = 255 - wheelpos*3;
        Green = 0;
        Blue = wheelpos*3;
        Colorp = packColor(Red,Green,Blue); 
        writePacCol(Colorp);
   }
    else 
        if(wheelpos<170)
        {
        wheelpos-=85;
        Red = 0;
        Green = wheelpos*3;
        Blue = 255-wheelpos*3;
        Colorp = packColor(Red,Green,Blue); 
        writePacCol(Colorp);
        }
         else 
         {
                wheelpos-=170;
         Red = wheelpos*3;
        Green = 255-wheelpos*3;
        Blue = 0;
        Colorp = packColor(Red,Green,Blue); 
        writePacCol(Colorp);
               }
}

void runwheel(){

    int n;
    
    for (n=0; n<= 255; n++)

    { wheel(n);
    }

	delay5000us;

}


void lcd_cmd(char package) {
    IFS3bits.MI2C2IF = 0;     
    I2C2CONbits.SEN = 1; //Initiate Start condition
    while(I2C2CONbits.SEN);
    IFS3bits.MI2C2IF = 0;
    // SEN will clear when Start Bit is complete
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = 0b00000000; // 8-bits consisting of control byte
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = package; // 8-bits consisting of the data byte
    while(!IFS3bits.MI2C2IF);
    IFS3bits.MI2C2IF = 0;    
    I2C2CONbits.PEN = 1;
    while(I2C2CONbits.PEN);
    IFS3bits.MI2C2IF = 0;
}
void lcd_init(void){
    wait(50);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110111); // contrast C3-C0
    lcd_cmd(0b01011101); // C5-C4, Ion, Bon
    lcd_cmd(0b01101100); // follower control
    wait(200);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001110); // Display On
    lcd_cmd(0b00000001); // Clear Display

}

void lcd_setCursor(char x,char y){
    int Cur;
    Cur = 0x40 * x + y;
    Cur = Cur + 0x80;
    lcd_cmd(Cur);
    
}

void lcd_printStr(const char *s)
{
  
    I2C2CONbits.SEN = 1;      //Initiate Start condition  
    while(I2C2CONbits.SEN);    //wait for SEN = 0
    
     IFS3bits.MI2C2IF = 0;
     I2C2TRN = 0b01111100;          // 8-bits consisting of the slave address and the R/nW bit
        
      while(!IFS3bits.MI2C2IF); 
    
      //not the final char
    while(*(s+1) != '\0')
    {
        IFS3bits.MI2C2IF = 0;
        I2C2TRN = 0b11000000;         // 8-bits consisting of control byte
        while(!IFS3bits.MI2C2IF); 
        IFS3bits.MI2C2IF = 0;
        I2C2TRN = *s;            // 8-bits consisting of the data byte
        while(!IFS3bits.MI2C2IF); 
        IFS3bits.MI2C2IF = 0;
        s++;
    }
      //the final char
         IFS3bits.MI2C2IF = 0;
        I2C2TRN = 0b01000000;         // 8-bits consisting of control byte

        while(IFS3bits.MI2C2IF == 0); //wait until it equals 1
        IFS3bits.MI2C2IF = 0;
        I2C2TRN = *s;            // 8-bits consisting of the data byte
        
        while(IFS3bits.MI2C2IF == 0); //wait until it equals 1
        IFS3bits.MI2C2IF = 0;
        
        
     I2C2CONbits.PEN = 1;          // Send Sto(P) Sequence
     
     while(I2C2CONbits.PEN);  // PEN will clear when Stop bit is complete
}

void lcd_printChar(char package) {
    IFS3bits.MI2C2IF = 0;  
    I2C2CONbits.SEN = 1; //Initiate Start condition
    while(I2C2CONbits.SEN); // SEN will clear when Start Bit is complete
    IFS3bits.MI2C2IF = 0;  
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;   
    I2C2TRN = 0b11000000; // only send one word
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = package; // display a word 
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;        
    I2C2CONbits.PEN = 1;//end command
    while(I2C2CONbits.PEN);
    IFS3bits.MI2C2IF = 0;
}
 
void finalchar(char package) {
    IFS3bits.MI2C2IF = 0;  
    I2C2CONbits.SEN = 1; //Initiate Start condition
    while(I2C2CONbits.SEN); // SEN will clear when Start Bit is complete
    IFS3bits.MI2C2IF = 0;  
    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;   
 
    I2C2TRN = 0b01000000; //send last one word
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;
    I2C2TRN = package; // display a word 
    while(IFS3bits.MI2C2IF == 0);
    IFS3bits.MI2C2IF = 0;        
    I2C2CONbits.PEN = 1;//end command
    while(I2C2CONbits.PEN);
    IFS3bits.MI2C2IF = 0;
}


void wait(int ms){
    int i=0;
    T1CONbits.TON = 1;
    for(i=0;i<ms;i++){
        while(_T1IF==0){
        };
        IFS0bits.T1IF = 0;
    }
    T1CONbits.TON = 0;
}