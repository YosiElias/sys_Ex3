#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD 30
#define TXT 1026

void gimatriaFunc();   //A
void atbashFunc();  //B
void atbashConvert(char* str);  //for B

void printSub(char *text, int word, int i);
int anagram(int size);

char word[31], text[1026]; //global variable
char wordAtbash[31]; //global variable



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

int printSeqGim(int size) {
    int wordGim = 0;
    for (int i = 0;i< strlen(word);i++)
        wordGim += gimatria(word[i]);
    int count = 0;
    char *f = text, *l = text;
    int a = 0, b = 0;
    int sum = gimatria(*f);
    while (b < size) {
        while (gimatria(*f) == 0 && a < size) {
            a++;
            f++;
        }
        while (gimatria(*l) == 0 && b < size) {
            b++;
            l++;
            sum += gimatria(*l);
        }
        if (sum < wordGim) {
            b++;
            l++;
            sum += gimatria(*l);
        }
        else if (sum > wordGim) {
            sum -= gimatria(*f);
            a++;
            f++;
        }
        else {
            if (count == 1) {
                printf("~%.*s", b - a + 1, text + a);
            } else {
                printf("%.*s", b - a + 1, text + a);
                count = 1;
            }
            sum -= gimatria(*f);
            a++;
            f++;
        }
    }
    return 0;
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
    printSeqGim(strlen(text));
    printf("\nAtbash Sequences: ");
    atbashFunc();
    printf("\nAnagram Sequences: ");
    anagram(strlen(text));
    return 0;
}



void atbashConvertWord()
{
    int i=0;
    while(word[i]!='\0')
    {
        if(!((word[i]>=0&&word[i]<65)||(word[i]>90&&word[i]<97)||(word[i]>122&&word[i]<=127)))
        {
            if(word[i]>='A'&&word[i]<='Z')
                wordAtbash[i] = 'Z'+'A'-word[i];
            if(word[i]>='a'&&word[i]<='z')
                wordAtbash[i] = 'z'+'a'-word[i];
        }

        if(((word[i]>=0&&word[i]<65)||(word[i]>90&&word[i]<97)||(word[i]>122&&word[i]<=127)))
        {
            wordAtbash[i] = word[i];
        }

        i++;
    }
}


void atbashFunc()
{
    atbashConvertWord();
    char* sTempText = text;
    char* sTempRevText = text;
    int lenghText = strlen(text), lenghWord =strlen(wordAtbash),
            countWord = 0, countRevWord = 0,
            curText=0, curWord=0, curRevWord=lenghWord-1,
            firstTime=1;
    for (int i=0; i<lenghText; i++)
    {
        if (text[curText]==' ' || text[curText]=='\t' || text[curText]=='\n')
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
            if (text[curText] == wordAtbash[curWord]) {
                curWord++;
                countWord++;
                if (curWord == lenghWord) {
                    printSub(sTempText, countWord, firstTime);
                    firstTime=0;
                    countWord = 0;
                    curWord = 0;
                    sTempText = &text[curText + 1];//init new start to word in text
                }
            }
            else
            {
                if (text[curText] == wordAtbash[0])
                {
                    curWord=1;
                    countWord=1;
                    sTempText = &text[curText];//init new start to word in text
                    if (curWord == lenghWord) {
                        printSub(sTempText, countWord, firstTime);
                        firstTime=0;
                        countWord = 0;
                        curWord = 0;
                        sTempText = &text[curText + 1];//init new start to word in text
                    }
                } else {
                    countWord = 0;
                    curWord = 0;
                    if (curText != lenghText - 1)
                        sTempText = &text[curText + 1];//init new start to word in text
                }
            }
            if (text[curText] == wordAtbash[curRevWord]) {
                curRevWord--;
                countRevWord++;
                if (curRevWord == -1) {
                    printSub(sTempRevText, countRevWord, firstTime);
                    firstTime=0;
                    countRevWord = 0;
                    curRevWord = lenghWord-1;
                    sTempRevText = &text[curText + 1];//init new start to word in text
                }
            }  else
            {
                if (text[curText] == wordAtbash[lenghWord - 1])
                {
                    curRevWord= lenghWord - 2;
                    countRevWord=1;
                    sTempRevText = &text[curText];//init new start to word in text
                    if (curRevWord == -1) {
                        printSub(sTempRevText, countRevWord, firstTime);
                        firstTime=0;
                        countRevWord = 0;
                        curRevWord = lenghWord-1;
                        sTempRevText = &text[curText + 1];//init new start to word in text
                    }
                } else {
                    countRevWord = 0;
                    curRevWord = lenghWord - 1;
                    if (curText != lenghText - 1)
                        sTempRevText = &text[curText + 1];//init new start to word in text
                }
            }
        }
        curText++;
    }

}

void printSub(char *text, int word, int first) {
    if (!first)
        printf("~");
    for (int i = 0; i < word; ++i) {
        printf("%c", text[0]);
        text++;
    }
}



int cmp(const void *a, const void *b) { return *(char *)a - *(char *)b; }
int anagram(int size) {
    int a = 0, b = 0, count = 0, flag = 0;
    int length = strlen(word);
    for (int i = 0; i < length; i++) {
        if (*(word + i) != ' ')
            count++;
    }
    int spaces = length - count;
    char temp[length + 1];
    char wordNotSpace[length + 1 - spaces];
    strcpy(temp, word);
    qsort(temp, strlen(temp), 1, (cmp));
    strcpy(wordNotSpace, temp + spaces);
    int count2 = 0;
    if (b == 0 && *(text + b) != ' ' && *(text + b) != '\n' && *(text + b) != '\t') {
        count2++;
    }
    while (b < size) {
        if (*(text + a) == ' ' || *(text + a) == '\n' || *(text + a) == '\t') {
            a++;
            continue;
        }
        if (count2 < count) {
            b++;
            if (b < size && *(text + b) != ' ' && *(text + b) != '\n' && *(text + b) != '\t') {
                count2++;
            }
            continue;
        }
        if (count2 > count) {
            if (*(text + a) != ' ' && *(text + a) != '\n' && *(text + a) != '\t' ) {
                count2--;
            }
            a++;
            continue;
        }
        if (count == count2) {
            int len = b - a + 1;
            char *dest = (char *) malloc(sizeof(char) * (len + 1));
            char* toFree = dest;
            if (dest != NULL){
                for (int i = a; i <= b && (*(text + i) != '\0'); i++) {
                    *dest = *(text + i);
                    dest++;
                }
                *dest = '\0';
                int spaces2 = len - count2;
                char temp2[len + 1];
                char wordNotSpace2[len + 1 - spaces2];
                strcpy(temp2, dest - len);
                qsort(temp2, strlen(temp2), 1, cmp);
                strcpy(wordNotSpace2, temp2 + spaces2);

                if (strcmp(wordNotSpace, wordNotSpace2) == 0) {
                    if (flag == 1) {
                        printf("~%s", dest - len);
                    } else {
                        printf("%s", dest - len);
                        flag = 1;
                    }
                }
                count2--;
                a++;
            }
            free(toFree);
        }
    }
    return 1;
}
