int A=5;
int B=2;
int C=7;
int D=9;
int E=6;
int F=4;
int G=3;
int H=1;
int I=0;
int J=8;

int cle[] = {C,B,F,A,C,E,A,B,D,E};
int cl[10] = {H,F,A,E,I,B,A,C,G,D};
  


void clo(){
  delay(1000);
  for (int i=0; i < 10; i++){
    if (i+1 <= sizeof(cle))
    {
        cl[i] = abs(cl[i] - cle[i]);
     
    } 
      Serial.println("");
      cl[random(5,9)] = random(0,9);
      cl[random(5,9)] = random(0,9);
      Serial.print(cl[i]);
                  
    }   }
    
          Serial.print("--->");
          Serial.print(cl[5]);
          Serial.print(cl[6]);
          Serial.print(cl[7]);
          Serial.print(cl[8]);
          Serial.print(cl[9]);
          Serial.println("");
          delay(500);

}


void setup ()
{
  Serial.begin (9600) ;
 
}
 
void loop () 
{
    clo();
 
}
