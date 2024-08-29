void delay1(int);
void port_intialization();
void setup() {
  // put your setup code here, to run once:
  port_intialization();
  volatile int debounce;
  volatile int *inpA,*inpD,*setA,temp,count;
  inpA = (volatile  int *)0x50000010;
  inpD = (volatile  int *)0x50000c10;
  setA = (volatile  int *)0x50000018; 
  *setA = 0xffff0000;  
  *inpA=0x00000000;
  *inpD=0x00000000;
  while(1){  
    for(count=8;count<16;count++){
        if(count==13) continue;                      
        if ((*inpA & (1 << count))){          
          for(debounce=0;debounce<10000;debounce++);                   
          *setA = 1<<(count-8);
          delay1(2);
          *setA = 0xffff0000;
          delay1(2);      
        }
    }
    if((*inpD & 0x00000001)){
      for(debounce=0;debounce<10000;debounce++);                   
          *setA = 0x00000020;
          delay1(2);
          *setA = 0xffff0000;
          delay1(2);
    }   
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}
void delay1(int num){
  volatile int i;
  while(num){
    for(i=0;i<100000;i++);
    num--;
  }
}
void port_intialization(){
  volatile  int *configA,*configD;
  configA = (volatile  int *)0x50000000;  // Cast to volatile int pointer
  configD = (volatile  int *)0x50000fff;  // Cast to volatile int pointer
  *configA = 0x00005555; 
  *configD = 0x00000001;
}
