/* Nguyen Duc Hoang - 9A */
// Date Create:22/8/15
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 100
void goToupper(char word[SIZE]){
word[0] -= 32;
}
void addDot(char word[SIZE]){
int i=0;
while(word[i] != '\0') i++;
word[i] = '.';
word[i+1] = '\0';
}
main(void){
char article[SIZE][SIZE]={{"the"},{"a"},{"one"},{"some"},{"any"}};
char noun[SIZE][SIZE] = {{"boy"},{"girl"},{"dog"},{"game"},{"tree"}};
char verb[SIZE][SIZE] = {{"go"},{"kiss"},{"play"},{"fuck"},{"fly"}};
char prepositon[SIZE][SIZE] = {{"at"},{"in"},{"on"},{"over"},{"under"}};
char sentences[SIZE][SIZE*SIZE];
int wArticle1,wArticle2,wNoun1,wNoun2,wVerb,wPreposition;
int n,i;
srand((unsigned)time(NULL));
printf("Nhap vao so cau ban muon: ");scanf("%d",&n);
for(i=0;i<n;i++){
wArticle1 =rand() % 5;
wArticle2 =rand() % 5;
wNoun1 =rand() % 5;
wNoun2 =rand() % 5;
wVerb =rand() % 5;
wPreposition =rand() % 5;
strcat(sentences[i],article[wArticle1]);
strcat(sentences[i]," ");
strcat(sentences[i],noun[wNoun1]);
strcat(sentences[i]," ");
strcat(sentences[i],verb[wVerb]);
strcat(sentences[i]," ");
strcat(sentences[i],prepositon[wPreposition]);
strcat(sentences[i]," ");
strcat(sentences[i],article[wArticle2]);
strcat(sentences[i]," ");
strcat(sentences[i],noun[wNoun2]);
goToupper(sentences[i]);
addDot(sentences[i]);
puts(sentences[i]);
}
}
