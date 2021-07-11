/*
    ==================================================
    Assignment #2 Milestone #1:
    ==================================================
    Name   : Tuan Nguyen
    ID     : 109062166
    Email  : tnguyen140@myseneca.ca
    Section: NFF
*/

#ifndef COMMONHELPERS_H_
#define COMMONHELPERS_H_

// -----------------------------------------
// Function Prototypes
int currentYear(void);
void clearStandardInputBuffer(void);
int getInteger(void);
int getPositiveInteger(void);
int getPositiveInteger2(void);
double getDouble(void);
double getPositiveDouble(void);
double getPositiveDouble2(void);
int getIntFromRange(int lowerBound, int upperBound);
char getCharOption(char string[]);
void getCString(char* string, int lowerBound, int upperBound);
void getCStringNoWhiteSpace(char* string, int lowerBound, int upperBound);
void getCStringPassword(char* string, int bound);
void getCStringCountry(char* string, int lowerBound, int upperBound);

#endif