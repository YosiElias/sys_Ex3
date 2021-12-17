#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gimatriaFunc();   //A
void atbashFunc();  //B
// void atbashFunc(char word, char text);   //C
void atbashConvert(char* str);  //for B



void printSub(char *text, int word);

char word[31], text[258]; //global variable
char wordAtbash[31], textAtbash[258]; //global variable



int gimatria(char c){
    int sum = c;
    if (sum > 122 || sum < 65 || (sum < 97 && sum > 90)){
        return 0;
    }
    if (sum >= 97 ){
        sum -=32;
    }
    return sum % 64;
}

int printSeqGim(char *s, int size, int wordGim){
    // printf("Gematria Sequences: ");
    int count = 0;
    char *f = s, *l = s;
    int a = 0, b = 0;
    int sum = gimatria(*f);
    while (b < size) {

        if (sum < wordGim ){
            b++;
            l++;
            sum += gimatria(*l);
            if (gimatria(*l) == 0){
                b++;
                l++;
                sum += gimatria(*l);
            }
        }
        else if (sum > wordGim ){
            sum -= gimatria(*f);
            a++;
            f++;
            if (gimatria(*f) == 0){
                a++;
                f++;
            }
        }
        else {
            if (count == 1){
                printf("~%.*s", b-a+1, s + a);
            }
            else{
                printf("%.*s", b-a+1, s + a);
                count = 1;
            }
            sum -= gimatria(*f);
            a++;
            f++;
        }
    }
    return 1;
}

void gimatriaFunc()
{
    int length = strlen( word );
    int gim = 0;
    for (int i=0;i<length;i++){
        gim += gimatria(word[i]);
    }
    printSeqGim(text,strlen(text),gim);
}


int main()
{
    //Get the input:
    char temp;
    int i = 0;
    temp = getchar();
    while(temp!=' ' && temp!='\t' && temp!='\n')
    {
        word[i] = temp;
        temp = getchar();
        i++;
    }
    word[i] = '\0';

    i=0;
    temp = getchar();
    while(temp!='~')
    {
        text[i] = temp;
        temp = getchar();
        i++;
    }
    text[i] = '\0';

    //Functin on input:
    printf("Gematria Sequences: ");
    gimatriaFunc();
    printf("\nAtbash Sequences: ");
    atbashFunc();
    printf("\nAnagram Sequences: ");
    printf("\n");


    // printf("%s", word);     //Todo: for self testing
    // printf("\n%s", text);     //Todo: for self testing
    return 1;
}



void atbashConvertWord()
{
    // char ans[strlen(str)+1];
    int i=0;
    while(word[i]!='\0')
    {
        if(!((word[i]>=0&&word[i]<65)||(word[i]>90&&word[i]<97)||(word[i]>122&&word[i]<=127)))
        {
            if(word[i]>='A'&&word[i]<='Z')
                wordAtbash[i] = 'Z'+'A'-word[i];
            // printf("%c",'Z'+'A'-str[i]);
            if(word[i]>='a'&&word[i]<='z')
                wordAtbash[i] = 'z'+'a'-word[i];
            // printf("%c",'z'+'a'-str[i]);
        }

        if(((word[i]>=0&&word[i]<65)||(word[i]>90&&word[i]<97)||(word[i]>122&&word[i]<=127)))
        {
            wordAtbash[i] = word[i];
            // printf("%c",str[i]);
        }

        i++;
    }
    // printf("%s", wordAtbash);
    // return ans;
}

void atbashConvertText()
{
    // char ans[strlen(str)+1];
    int i=0;
    while(text[i]!='\0')
    {
        if(!((text[i]>=0&&text[i]<65)||(text[i]>90&&text[i]<97)||(text[i]>122&&text[i]<=127)))
        {
            if(text[i]>='A'&&text[i]<='Z')
                textAtbash[i] = 'Z'+'A'-text[i];
            // printf("%c",'Z'+'A'-str[i]);
            if(text[i]>='a'&&text[i]<='z')
                textAtbash[i] = 'z'+'a'-text[i];
            // printf("%c",'z'+'a'-str[i]);
        }

        if(((text[i]>=0&&text[i]<65)||(text[i]>90&&text[i]<97)||(text[i]>122&&text[i]<=127)))
        {
            textAtbash[i] = text[i];
            // printf("%c",str[i]);
        }

        i++;
    }
    // printf("%s", textAtbash);
    // return ans;
}


void atbashFunc()
{
    atbashConvertWord();
    atbashConvertText();
    // char *temp = malloc(strlen(text));
    // char* sWord = wordAtbash;
    char* sTempText = textAtbash;
    char* sTempRevText = textAtbash;
    // char* sRevWord = &wordAtbash[strlen(wordAtbash)-1];
    // char* curWord = &wordAtbash;
//    char* curRevWord = &wordAtbash[strlen(wordAtbash)-1];
    // char *curText = textAtbash[0];
    // char ans[258], ansRev[258];
    int lenghText = strlen(textAtbash), lenghWord =strlen(wordAtbash),
            countWord = 0, countRevWord = 0,
            curText=0, curWord=0, curRevWord=lenghWord-1;
    printf("\n----%s----", textAtbash);

    for (int i=0; i<lenghText; i++)
    {
        if (textAtbash[curText]==' ' || textAtbash[curText]=='\t' || textAtbash[curText]=='\n')
        {
            if (countWord != 0)
                countWord++;
            else
                sTempText++;
            if (countRevWord != 0)
                countRevWord++;
            else
                sTempRevText++;
        }
        else
        {
            if (textAtbash[curText] == wordAtbash[curWord]) {
                curWord++;
                countWord++;
//            curText++;
                if (curWord == lenghWord) {
                    printf("\nans:");
                    printSub(sTempText, countWord);
                    countWord = 0;
                    curWord = 0;
                }
            }
            else
            {
                countWord=0;
                curWord=0;
                if (curText != lenghText-1)  //Todo: need try without this if
                    sTempText = &textAtbash[curText+1];//init new start to word in text
            }
            if (textAtbash[curText] == wordAtbash[curRevWord]) {
                curRevWord--;
                countRevWord++;
                if (curRevWord == -1) {
                    printf("\nans REV:");
                    printSub(sTempRevText, countRevWord);
                    countRevWord = 0;
                    curRevWord = lenghWord-1;
                }
            }  else
            {
                countRevWord=0;
                curRevWord=lenghWord-1;
                if (curText != lenghText-1)  //Todo: need try without this if
                    sTempRevText = &textAtbash[curText+1];//init new start to word in text
            }
        }
        curText++;
    }

}

void printSub(char *data, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%c", data[0]);
        data++;
    }
}
