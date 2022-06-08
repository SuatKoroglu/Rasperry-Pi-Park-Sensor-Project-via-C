''' java
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <time.h>
#include <curl/curl.h>

#define trig 23
#define echo 24
#define BeepPin 17
#define a 200
#define cH 500

void beep(unsigned int note, unsigned int duration)
{
  //This is the semiperiod of each note.
  long beepDelay = (long)(1000000/note);
  //This is how much time we need to spend on the note.
  long time = (long)((duration*1000)/(beepDelay*2));
  for (int i=0;i<time;i++)
  {
    //1st semiperiod
    digitalWrite(BeepPin, HIGH);
    delayMicroseconds(beepDelay);
    //2nd semiperiod
    digitalWrite(BeepPin, LOW);
    delayMicroseconds(beepDelay);
  }

  //Add a little delay to separate the single notes
  digitalWrite(BeepPin, LOW);
  delay(20);
}
int mailAnfrage(){
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    printf("Curl wird gemacht.");
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL,"https://doktoradanis.net/deneme.php?mesaj=Araç Başarıyla Park Edildi!!!&mail=e190503011@stud.tau.edu.tr&konu=Park Basarilibaslik=Parksysteme");

        res = curl_easy_perform(curl);
        printf("\n MAil atıldı. \n");
        if(res != CURLE_OK){
            fprintf(stderr,"curl_easy_perform wurde gescheitert; %s\n",curl_easy_strerror(res));


        }else{
            //printf("Resultat: %s\n", res);
        }

        printf("Curl wurde zurückgegeben.");
        curl_easy_cleanup(curl);
        return 0;
    }

}



int main(void) {
  
  if(wiringPiSetup() ==-1){
    printf("setup wiringPi failed.");
    return -1;
  }

  wiringPiSetupGpio();
  pinMode(echo,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(BeepPin,OUTPUT);
 int t =0;

  while(1){

    digitalWrite(trig,LOW);
    printf("Ölçüm yapılıyor...");
    delay(50);
    digitalWrite(trig,HIGH);
    delay(50);
    digitalWrite(trig,LOW);
    
    long int start_i;
    time_t start;
    long int stop_i;
    time_t stop;
    
    while(digitalRead(echo)==0){
      start = micros();
    }
    while(digitalRead(echo)==1){
      stop = micros();
    }

    start_i = (long int)start;
    stop_i = (long int) stop;
    long int distance = stop_i - start_i;
   
    distance = (distance*17)/1000;

    int mesafeler[5];
    mesafeler[t] = distance;
    if(t==5){
      t=0;
      if(mesafeler[0]== mesafeler[1] && mesafeler[0]== mesafeler[2] && mesafeler[0]== mesafeler[3] && mesafeler[0]== mesafeler[4] ){
        mailAnfrage();
      }

      
    }
    t++;
    printf("Mesafe: %d\n", distance);
    if(distance<=10){
        beep( a, 500);
        
        
      
    }else if (distance >10 && distance <50){
        beep( cH, 500);
    }else{
      digitalWrite(BeepPin,LOW);
    }
    
     
    
  }
  return 0;
}
'''