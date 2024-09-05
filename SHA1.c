#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CharToAscii(char* text,int size,int* ascii);
void AsciiToBiStr(int* ascii,int size,char biStr[20][9]);
void BiStrReverse(char biStr[20][9],int size);
void JoinAllandAppendOne(char biStr[20][9],char *joinAddOne,int size);
void AppendZero(char *joinAddOne,int length);
int GetBiLength(char biStr[20][9],int size);
void DecToBiStrAndPadUntilSixtyFour(char *BilenChar,int Bilen);
void AppendTOArray(char* needAppend,char * toAppend,int sizeNeedAppend,int sizeToAppend);
void SplitTo32Chunks(char chunks32[16][33],char* chunks512);

int main(){
    char text[] = "HELLO WORLD";
    int* ascii = (int*)malloc(strlen(text)*sizeof(int));
    char biStr[20][9];
    int size = strlen(text);
    CharToAscii(text,size,ascii); //<======
    for(int i = 0;i<size ; i++){
        printf("%d ",ascii[i]);
    }
    printf("\n");
    AsciiToBiStr(ascii,size,biStr); //<======
    for(int i = 0;i<size ; i++){
        printf("%s ",biStr[i]);
    }
    printf("\n");
    BiStrReverse(biStr,size); //<======
    int Bilen = GetBiLength(biStr,size); //<======
    char BilenChar[65]; 
    DecToBiStrAndPadUntilSixtyFour(BilenChar,Bilen); //<======
    printf("DEC TO BI : %d => %s\n",Bilen,BilenChar);
    for(int i = 0; i < size ; i++)
    {
        printf("%s ",biStr[i]);
    }
    printf("\n");
    char joinAddOne[500];
    JoinAllandAppendOne(biStr,joinAddOne,size); //<======
    printf("%s\n",joinAddOne);
    int length = strlen(joinAddOne);
    AppendZero(joinAddOne,length); //<======
    printf("%c \n",joinAddOne[447]);
    printf("size joinaddone = > %d\n",strlen(joinAddOne));
    printf("size of BilenChar = > %d\n",strlen(BilenChar));
    AppendTOArray(joinAddOne,BilenChar,strlen(joinAddOne),strlen(BilenChar)); //<======
    printf("after append : %s\n",joinAddOne);
    printf("Size => %d\n",strlen(joinAddOne));
    char chunks32[16][33];
    SplitTo32Chunks(chunks32,joinAddOne); //<======
    for(int i = 0;i < 16;i++){
        printf("chunks %d => %s => strlen => %d\n",i+1,chunks32[i],strlen(chunks32[i]));
    }
    free(ascii);
    return 0;
}

void CharToAscii(char* text,int size,int* ascii){
    for(int i = 0;i < size;i++){
        ascii[i] = (int)text[i];
    }
}

void AsciiToBiStr(int* ascii,int size,char biStr[20][9]){
    for(int i = 0 ; i<size ; i++){
        int k = 0;
        for(int j = ascii[i];j > 0 ; j /= 2){
            if(j % 2 == 0){
                biStr[i][k] = '0';
            }else{
                biStr[i][k] = '1';
            }
            k++;
        }
        biStr[i][k] = '\0';
    }
}

void BiStrReverse(char biStr[20][9],int size){
    char temp[9];
    for(int i = 0;i < size;i++){
        int k = 0;
        for(int j = 7;j >= 0;j--)
        {
            if(biStr[i][j] == '\0'){
                temp[k] = '0';
            }else if(biStr[i][j] == '0' || biStr[i][j] == '1'){
                temp[k] = biStr[i][j];
            }
            else{
            }
            k++; 
        }
        temp[k+1] = '\0';
        for(int z = 0;z<9;z++)
        {
            biStr[i][z] = temp[z];
        }         
    }
}

void JoinAllandAppendOne(char biStr[20][9],char *joinAddOne,int size){
    int k = 0;
    for(int i = 0;i < size;i++){
        for(int j = 0;j < 8;j++){
            joinAddOne[k] = biStr[i][j];
            k++;
        }
    }
    joinAddOne[k] = '1';
    joinAddOne[k+1] = '\0';
}

void AppendZero(char* joinAddOne,int length){
    while (length % 512 != 448)
    {
        joinAddOne[length] = '0';
        length++;
    }
    joinAddOne[length] = '\0';
}

int GetBiLength(char biStr[20][9],int size){
    int length = 0;
    for(int i = 0;i < size;i++){
        length += strlen(biStr[i]);
    }
    return length;
}

void DecToBiStrAndPadUntilSixtyFour(char *BilenChar,int Bilen){
    char temp[65];
    int index = 0;
    for(int i = Bilen;i > 0;i/=2){
        if(i % 2 == 0){
            temp[index] = '0';
        }else{
            temp[index] = '1';
        }
        index++;
    }
    while(index < 64){
        temp[index] = '0';
        index++;
    }
    temp[index] = '\0';
    printf("%d\n",index);
    index -= 1;
    for(int j = 0;j < strlen(temp);j++){
        BilenChar[j] = temp[index];
        index--;
    }
    printf("2 => %d\n",strlen(temp));
    BilenChar[strlen(temp)] = '\0';
}

void AppendTOArray(char* needAppend,char * toAppend,int sizeNeedAppend,int sizeToAppend){
    int index = sizeNeedAppend;
    for(int i = 0;i<sizeToAppend;i++){
        needAppend[index] = toAppend[i];
        index++;
    }
    needAppend[index] = '\0';
}

void SplitTo32Chunks(char chunks32[16][33],char* chunks512){
    int index = 0;
    for(int i = 0;i < 16;i++){
        for(int j = 0;j<=32;j++){
            if(j != 32){
                chunks32[i][j] = chunks512[index];
                index++;
            }else{
                chunks32[i][j] = '\0';
            }
        }
    }
}