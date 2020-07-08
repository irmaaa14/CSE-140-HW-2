
/*
 Created by:
 William Breytberg
 Irma Gonzalez Padilla
 Justin Yee
 */

//Libraries
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

//Global Variable
char parsedArr[6][10]; //Holds the original string as segments
char foundArr[6][10];  //Holds the decimal value of the string
char binStr[10000];       //Holds the binary as a string

//Functions

bool FindOp()
{ // Determines which OpCode it is
    if (strcmp(parsedArr[0], "add") == 0)
    {
        strcpy(foundArr[5], "32");
        strcpy(binStr, "100000");
        return 1;
    }
    else if (strcmp(parsedArr[0], "addu") == 0)
    {
        strcpy(foundArr[5], "33");
        strcpy(binStr, "100001");
        return 1;
    }
    else if (strcmp(parsedArr[0], "and") == 0)
    {
        strcpy(foundArr[5], "36");
        strcpy(binStr, "100100");
        return 1;
    }
    else if (strcmp(parsedArr[0], "jr") == 0)
    {
        strcpy(foundArr[5], "8");
        strcpy(binStr, "001000");
        return 1;
    }
    else if (strcmp(parsedArr[0], "nor") == 0)
    {
        strcpy(foundArr[5], "39");
        strcpy(binStr, "100111");
        return 1;
    }
    else if (strcmp(parsedArr[0], "or") == 0)
    {
        strcpy(foundArr[5], "37");
        strcpy(binStr, "100101");
        return 1;
    }
    else if (strcmp(parsedArr[0], "slt") == 0)
    {
        strcpy(foundArr[5], "42");
        strcpy(binStr, "101010");
        return 1;
    }
    else if (strcmp(parsedArr[0], "sltu") == 0)
    {
        strcpy(foundArr[5], "43");
        strcpy(binStr, "101011");
        return 1;
    }
    else if (strcmp(parsedArr[0], "sll") == 0)
    {
        strcpy(foundArr[5], "0");
        strcpy(binStr, "000000");
        return 1;
    }
    else if (strcmp(parsedArr[0], "srl") == 0)
    {
        strcpy(foundArr[5], "2");
        strcpy(binStr, "000010");
        return 1;
    }
    else if (strcmp(parsedArr[0], "sub") == 0)
    {
        strcpy(foundArr[5], "34");
        strcpy(binStr, "100010");
        return 1;
    }
    else if (strcmp(parsedArr[0], "subu") == 0)
    {
        strcpy(foundArr[5], "35");
        strcpy(binStr, "100011");
        return 1;
    }
    else
    {
        strcpy(foundArr[5], "-1");
        strcpy(binStr, "222222");
        return 0;
    }
}

int FindR(int i)
{                  // Determines the registers
    char *regName; //Contains letter values of registar
    int regNum;    //Contains the numbers
    
    if (strcmp(parsedArr[i], "zero") == 0)
    {
        return 0;
    }
    else if (strcmp(parsedArr[i], "at") == 0)
    {
        return 1;
    }
    else if (strcmp(parsedArr[i], "gp") == 0)
    {
        return 28;
    }
    else if (strcmp(parsedArr[i], "sp") == 0)
    {
        return 29;
    }
    else if (strcmp(parsedArr[i], "fp") == 0)
    {
        return 30;
    }
    else if (strcmp(parsedArr[i], "ra") == 0)
    {
        return 31;
    }
    
    regName = parsedArr[i];
    regNum = parsedArr[i][1];
    regNum = regNum - 48;
    //printf("FindR:%d | %s | %d \n", regNum, regName, parsedArr[i][0]);
    
    if (strncmp(regName, "v", 1) == 0)
    {
        if (0 < regNum && regNum < 1)
            return 2 + regNum;
    }
    else if (strncmp(regName, "a", 1) == 0)
    {
        if (0 < regNum && regNum < 3)
            return 4 + regNum;
    }
    else if (strncmp(regName, "t", 1) == 0)
    {
        if (0 <= regNum && regNum <= 7)
            return 8 + regNum;
    }
    else if (strncmp(regName, "s", 1) == 0)
    {
        if (0 < regNum && regNum < 7)
            return 16 + regNum;
    }
    else if (strncmp(regName, "t", 1) == 0)
    {
        if (8 < regNum && regNum < 9)
            return 24 + regNum;
    }
    else if (strncmp(regName, "k", 1) == 0)
    {
        if (0 < regNum && regNum < 1)
            return 26 + regNum;
    }
    
    return -1; //Failed to find register
}

void Parser(char str[])
{ //Breaks string into an array and sotre string segments in ParsedString[];
    
    char temp[100] = " ";
    char *ptr;
    int i = 0;
    
    strcat(temp, str);
    
    ptr = strtok(temp, " "); //Find first use of spacebar
    
    while (ptr != NULL)
    { //Go through string str and store each piece in strArr
        strncpy(parsedArr[i], ptr, 6);
        ptr = strtok(NULL, " ");
        i++;
    }
    return;
}

void IntToBinary(int num,int size){
    int i = 1;
    int j = 0;
    char temp[32];
    while(num >= i*2){
        i = i*2;
    }
    printf("bits:%s \n", temp);   // printf ("out num: %d\n",num);
    while(num > 0){
        if(num >= i){
            num = num - i;
            strcpy(temp, "1");
            strcat(temp, binStr);
            strcpy(binStr, temp);
           // strcat(binStr, "1");//bina += "1");
        } else {
            strcpy(temp, "0");
            strcat(temp, binStr);
            strcpy(binStr, temp);
           // strcat(binStr, "0");//bina += "0");
        }
        i = i / 2;
        j++;
    }
    while(j < size){
        strcpy(temp, "0");
        strcat(temp, binStr);
        strcpy(binStr, temp);
       // strcat(binStr,"0"); //bina = "0" + bina;
        j++;
    }
    printf("bits:%s \n", temp);
    return;
}

 void PrintOut() {//Prints out Instruction
 printf ( "operation: %s \n", parsedArr[0]);
     printf ( "Rs: %s (R%s) \n", parsedArr[1], foundArr[1]);
 printf ( "Rt: %s (R%s) \n", parsedArr[2], foundArr[2] );
 printf ( "Rd: %s (R%s) \n", parsedArr[3], foundArr[3]);
 printf ( "Shamt: 0 \n" );
 printf ( "Funct: %s \n", foundArr[5]);
 printf ( "Machine Code: %s \n", binStr );
 }

 

int main()
{
    char input[99]; //takes in user input
    char temp[99];
    
    printf("Please provide an R-type instruction. \n");
    
    //Input String
    //fgets (input, 99, stdin);
    strcpy(input, "add s1 t0 t1");
    
    Parser(input); //separate string based on space bar
    
    //Pick which variable and print
    if (FindOp() == 0)
    { //returns Funct in Dec and in Binary
        printf("Bad Input: Op");
        return 0;
    }
    
    //Shamt(); //append bits to binary
    strcpy(temp, "00000");
    strcat(temp, binStr);
    strcpy(binStr, temp);
    //FindR(); //called 3 times for rs, rt, and rd
    
    //foundArr[1] = FindR(1);//rs
    sprintf(foundArr[1], "%d", FindR(1));
    if (strcmp(foundArr[1], "-1") == 0)
    { //returns Funct in Dec and in Binary
        printf("Bad Input: rs");
        return 0;
    }
    
    // foundArr[2] = FindR(2);//rt
    sprintf(foundArr[2], "%d", FindR(2));
    if(strcmp(foundArr[2], "-1") == 0){
        printf ( "Bad Input: rt" );
        return 0;
    }
  
    // foundArr[3] = FindR(3);//rd
    sprintf(foundArr[3], "%d", FindR(3));
    if(strcmp(foundArr[4], "-1") == 0){
        printf ( "Bad Input: rd" );
        return 0;
    }
    
  //  printf("bits:%s \n", binStr);
    //IntToBin( integer ,length ); //returns a string to represent binary
    IntToBinary(atoi(foundArr[3]),5 );//rd
   // printf("rd: %s bits:%s  & %d\n",parsedArr[2], binStr,(int)foundArr[3][0]);
    IntToBinary(atoi(foundArr[2]),5 );//rt
   // printf("rt bits:%s \n", binStr);
    IntToBinary(atoi(foundArr[1]),5 );//rs
   // printf("rs bits:%s \n", binStr);
    
   // printf("bits:%s \n", binStr);
    
    //OpCode to Binary
    strcpy(temp, "000000");
    strcat(temp, binStr);
    strcpy(binStr, temp);
    //strcat("00000", binStr);
    
    //Print Funct
    PrintOut();
    
    
    return 0;
}
