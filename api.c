//Library Functions For the LED Matrix


//------------------The First Layer, which will send a single bit to the Matrix.
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



//------------------The second layer functions, which controls single pixel in the matrix

//make one pixel blue
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

//make one pixel red
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

//make one pixel green
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


//off one pixel
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


//write a particular color to a pixel

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


 // write a packed color to a pixel
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


//write a single frame to one pixel
void drawFrame(int frame){

    int r;

    int b;

    r= frame;

    b= 255-frame;

    writeColor(0, r, b);    

}

//generate a packed color or get single color from the packed color
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



//------------------Third layer functions, which control whole matrix

//write a single color to whole matrix

void Paintpurecolor(int Red, int Grn, int Blu){
int i;
for(i = 0; i< 64; i++){
writeColor(Red, Grn, Blu);
}	
delay5000us;
		
}

//write a single color to a single pixel with given index

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

//off all pixels
void erase(){
int i;
for(i = 0; i< 64; i++){
offled();	
}
}
	
// A wheel function generating a wheel
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
    
    for (n=0; n< 63 n++)

    { wheel(n);
    }

	delay5000us;

}



//Library Functions For the buzzer

//generate a voice with given frequence
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

