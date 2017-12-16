void Myprintf(char *,...);         //Our printf function
char* convert(unsigned int, int);     //Convert integer number into octal, hex, etc.
 
 
 
void Myprintf(const char* format,...) 
{ 
  const char *traverse; 
  unsigned int i; 
  double f;
  char *s; 
  
  //Module 1: Initializing Myprintf's arguments 
  va_list arg; 
  va_start(arg, format); 
  
  for(traverse = format; *traverse != '\0'; traverse++) 
  { 
    while( *traverse != '%' ) 
    { 
      Serial.print(*traverse);
      traverse++; 
    } 
    
    traverse++; 
    
    //Module 2: Fetching and executing arguments
    switch(*traverse) 
    { 
      case 'c' : i = va_arg(arg,int);   //Fetch char argument
            Serial.print(i);
            break; 
            
      case 'd' : i = va_arg(arg,int);     //Fetch Decimal/Integer argument
            if(i<0) 
            { 
              i = -i;
              Serial.print('-'); 
            } 
            Serial.print(convert(i,10));
            break; 
            
      case 'o': i = va_arg(arg,unsigned int); //Fetch Octal representation
            Serial.print(convert(i,8));
            break; 
            
      case 's': s = va_arg(arg,char *);     //Fetch string
            Serial.print(s); 
            break; 

      case 'f': f = va_arg(arg, double);     //Fetch float/double
            Serial.print(f);
            break; 
            
      case 'x': i = va_arg(arg,unsigned int); //Fetch Hexadecimal representation
            Serial.print(convert(i,16));
            break; 
    } 
  } 
  Serial.println();
  //Module 3: Closing argument list to necessary clean-up
  va_end(arg); 
} 
 
char *convert(unsigned int num, int base) 
{ 
  static char Representation[]= "0123456789ABCDEF";
  static char buffer[50]; 
  char *ptr; 
  
  ptr = &buffer[49]; 
  *ptr = '\0'; 
  
  do 
  { 
    *--ptr = Representation[num%base]; 
    num /= base; 
  }while(num != 0); 
  
  return(ptr); 
}
