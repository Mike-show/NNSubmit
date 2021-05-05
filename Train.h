#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define _CRT_SECURE_NO_WARNINGS

void Train(double **TrainSetInput, double TrainSetOutput[], double Output[], int DataSize);
double DeSigmoid(double Input);
double DotProduct(double Array1[], double Array2[], int Column);
void ErrorCalclt(double Input1[], double Input2[], double Output[]);
double RandomNum(void);
double Sigmoid(double Input);
char Analyze(double input[], double AnaDatum[][3]);
int MaxIn3(double a, double b, double c);
void ObjInput(double AnaObj[]);
void ClrGenerate(double AnaObj[]);
void ClrInput(double **TrainSetInput, double **TrainSetOutput, int DataSize);
void DatumCustomize(double AnaDatumCo[3][3]);
void Retrain(double AnaDatumCo[3][3]);
double **MemAlloc(int Row, int Column);
void OptionPrint(void);