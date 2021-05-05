#include "Train.h"

void Train(double **TrainSetInput, double TrainSetOutput[], double Output[], int DataSize){

    double Adjust[3];
    double **Transpose, *Error, *TrainRes;
    Transpose = MemAlloc(3, DataSize);
    Error = (double *)calloc(DataSize, sizeof(double));
    TrainRes = (double *)calloc(DataSize, sizeof(double));
    
    for(int k = 0; k < 50000; k++){
        //think train
        for(int i = 0; i < DataSize; i++){
            TrainRes[i] = Sigmoid(DotProduct(&TrainSetInput[i][0], Output, 3));
        }

        //error calculation
        for(int i = 0; i < DataSize; i++){
            Error[i] = TrainSetOutput[i] - TrainRes[i];
        }
        for(int i = 0; i < DataSize; i++){
            Error[i] *= DeSigmoid(TrainRes[i]);
        }

        //transpose
        for(int i = 0; i < DataSize; i++){
            for(int j = 0; j < 3; j++){
                Transpose[j][i] = TrainSetInput[i][j];
            }
        }

        //adjustment calculation
        for(int i = 0; i < 3; i++){
            Adjust[i] = DotProduct(Error, &Transpose[i][0], DataSize);
        }

        for(int i = 0; i < 3; i++){
            Output[i] += Adjust[i];
        }
    }
}

//desigmoid calculation
double DeSigmoid(double Input){
    double Output = Input * (1 - Input);
    return Output;
}

//function which calculates the dot product of 2 arraies
double DotProduct(double Array1[], double Array2[], int Column){
    double Product = 0;
    for(int i = 0; i < Column; i++){
        Product += Array1[i] * Array2[i];
    }
    return Product;
}


void ErrorCalclt(double Input1[], double Input2[], double Output[]){
    for(int i = 0; i < 4; i++){
        Output[i] = Input1[i] - Input2[i];
    }

    for(int i = 0; i < 4; i++){
        Output[i] *= DeSigmoid(Input2[i]); 
    }
}

//take time as a seed, gernerate a random number between 1 and -1
double RandomNum(void){
    srand(time(NULL));
    float Output = 2 * (float)rand() / RAND_MAX - 1;
    return Output;
}

//function wich calculates the sigmoid value of the input number
double Sigmoid(double Input){
    double Output = 1 / (1+expf(-Input));
    return Output;
}

//function which compares object with datum
char Analyze(double input[], double AnaDatum[][3]){
	double AnaResult[3] = {0};
	int AnaBak;
	//pass every factor through datum and get 3 numbers stand for possibiliies of 3 different colors
	for(int i=0; i<3; i++){
		AnaResult[i]= DotProduct(input,&AnaDatum[i][0],3);
		AnaResult[i] = Sigmoid(AnaResult[i]);
	}

    //find the biggest number in 3, return its serial number
    //the biggest one means the biggest possibility
    //e.g: if AnaResult[0] is the biggest one, returns "1" to AnaBak, it means RED is the most possible color
	AnaBak = MaxIn3(AnaResult[0], AnaResult[1], AnaResult[2]);
	return AnaBak;
}

//function which returns the serial number of the biggest number in 3
int MaxIn3(double a, double b, double c){
    int N = 1;
    if(b>a){
        N++;
        if(c>b){
            N++;
        }
    }
    else if(c>a){
        N+=2;
    }
    return N;
}

//get 3 numbers from user between 0~255
void ObjInput(double AnaObj[]){
    printf("Please give me 3 numbers between 0~255, they will define a color.\n");
    int i;
    double temp;

    for(i=0; i<3; i++){
        do{
            printf("No.%d is: ", i+1);
            scanf("%lf", &temp);

            if(temp >= 0 && temp <= 255){

                //transfer values into RGB normalized decimal for analyzation
                AnaObj[i] = temp/255;
                break;
            }
            else printf("The value should be between 0 and 255. Please input again.\n");
        } while (1);
    }
    printf("\nThe RGB-color you just inputted is: \n(%.0lf, %.0lf, %.0lf)\n", AnaObj[0]*255, AnaObj[1]*255, AnaObj[2]*255);
}

//generates 3 random values, then pass them to object
void ClrGenerate(double AnaObj[]){
    double RGB[3];
    srand(time(NULL));
    for(int i=0; i<3; i++){
        AnaObj[i] = (float)rand() / RAND_MAX*1; //get a number between 0~1 for analyzation
        RGB[i] = AnaObj[i] * 255;//get RGB value between 0~255 shown to user
    }
    printf("I generated a color whose RGB value is: ");
    printf("(%.0lf, %.0lf, %.0lf)\n", RGB[0], RGB[1], RGB[2]);
}

//get RGB colors from user
void ClrInput(double **TrainSetInput, double **TrainSetOutput, int DataSize){
    printf("\nGet it! Now please follow the instructions, and give me %d groups of values.\n", DataSize);
    printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
    printf("                               Notice                                  \n");
    printf(" -Give me colors in RGB form, each value should be between 0 and 255   \n");
    printf(" -After inputting values, tell me what color it is.                    \n");
    printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n\n");

    int i = 0;
    int Color = 0;
    int Continue = 1;
    double temp;

    do{
        printf("The Red   value of group %d is: ", i+1);
        scanf("%lf", &temp);
        if(temp >= 0 && temp <= 255){
            TrainSetInput[i][0] = temp/255;
            printf("The Green value of group %d is: ", i+1);
            scanf("%lf", &temp);
            if(temp >= 0 && temp <= 255){
                TrainSetInput[i][1] = temp/255;
                printf("The Blue  value of group %d is: ", i+1);
                scanf("%lf", &temp);
                if(temp >= 0 && temp <= 255){
                    TrainSetInput[i][2] = temp/255;
                    printf("The value you just inputted is (%.0lf, %.0lf, %.0lf)\n", TrainSetInput[i][0]*255, TrainSetInput[i][1]*255, TrainSetInput[i][2]*255);
                    do{
                        printf("Tell me what color it is.(1 for Red, 2 for Green, 3 for Blue.)\nThe color is:");
                        scanf("%d", &Color);
                    } while(Color < 1 || Color > 3);
                    TrainSetOutput[i][Color-1] = 1;
                    i++;
                }
                else printf("The value should be between 0 and 255. Please input again.\n");
            }
            else printf("The value should be between 0 and 255. Please input again.\n");
        }
        else printf("The value should be between 0 and 255. Please input again.\n");
    } while (i<DataSize);
}

//function which customize analization datume
void DatumCustomize(double AnaDatumCo[3][3]){
    FILE *file;
    int CusChoice;
    printf("\nHmm, it seems you'd like your own taste.\n.");
    printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
    printf(" Input '1': Use the previous training result.                          \n");
    printf(" Input '2': Initialize my memory and train me again.                   \n");
    printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n\n");
    printf("Input your choice: ");
    scanf("%d", &CusChoice);
    do{
        if(CusChoice == 1){
            file = fopen("DatumStore.txt", "r");
            if(file == NULL){
                printf("\nI haven't been trained by you yet, please train me.\n\n");
                file = fopen("DatumStore.txt", "w");
                if(file == NULL) {
                    printf("Error: data can't be stored.\n");
                }
                else {
                    Retrain(AnaDatumCo);
                    for(int i=0; i<3; i++){
                        for(int j=0; j<3; j++){
                            fprintf(file, "%lf ", AnaDatumCo[i][j]);
                        }
                    }
                    printf("The training result has been stored in DatumStore.txt, you can use it in the next time.\n\n");
                    fclose(file);
                }
            }
            else{
                for(int i=0; i<3; i++){
                    for(int j=0; j<3; j++){
                        fscanf(file, "%lf", &AnaDatumCo[i][j]);
                    }
                }
                printf("I will use the result you trained me last time to analyse the color.\n\n");
                fclose(file);
            }
            break;
        }
        else {
            if(CusChoice == 2){
                file = fopen("DatumStore.txt", "w");
                if(file == NULL) {
                    printf("Error: data can't be stored.\n");
                }
                else {
                    Retrain(AnaDatumCo);
                    for(int i=0; i<3; i++){
                        for(int j=0; j<3; j++){
                            fprintf(file, "%lf ", AnaDatumCo[i][j]);
                        }
                    }
                    printf("The training result has been stored in DatumStore.txt, you can use it for the next time.\n\n");
                    fclose(file);
                }
                break;
            }
            else {
                printf("\nThis choice doesn't exist, make a choice again.\n\n");
                printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––");
                printf(" Input '1': Use the previous training result.                          ");
                printf(" Input '2': Initialize the memory and train me again.                  ");
                printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––");
                scanf("%d", &CusChoice);
            }
        }
    }while (1);
}


void Retrain(double AnaDatumCo[3][3]){
    int DataSize;
    printf("How many groups of color do you plan to give me? ");
    //get a data size from user
    scanf("%d", &DataSize);

    //allocate enough memery to train set based on the data size
    //we need to use pointer to pointer, because the input and output are both 2D array
    double ** TrainSetInput = NULL, ** TrainSetOutput = NULL;
    TrainSetInput = MemAlloc(DataSize, 3);
    TrainSetOutput = MemAlloc(DataSize, 3);

    ClrInput(TrainSetInput, TrainSetOutput, DataSize);

    //allocate enough memery to transpose based on the data size
    double ** TransposeOutput = NULL;
    TransposeOutput = MemAlloc(3, DataSize);

    for(int i=0; i<3; i++){
        for(int j=0; j<DataSize; j++){
            TransposeOutput[i][j] = TrainSetOutput[j][i];
        }
    }


    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            AnaDatumCo[i][j] = RandomNum();
        }
    }


    for(int i=0; i<3; i++){
        Train(TrainSetInput, &TransposeOutput[i][0], &AnaDatumCo[i][0], DataSize);
    }
    printf("\nTraining completed.\n");

    //free all memeries manully allocated
    free(TrainSetInput);
    free(TrainSetOutput);
    free(TransposeOutput);
}

//memery allocation function
double **MemAlloc(int Row, int Column){
    double ** ptr;
    ptr = (double **)calloc(Row, sizeof(double));
    for(int i=0; i<Row; i++){
        ptr[i] = (double *)calloc(Column, sizeof(double));
    }
    return ptr;
}

void OptionPrint(void){
    printf("What do you want to do next?\n");
    printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");
    printf(" Input '1': Give me values, then I will tell you what color it is.     \n");
    printf(" Input '2': Generate values randomly. You can check if I'm correct.    \n");
    printf(" Input '3': Follow your own special taste.                             \n");
    printf(" Input '-1': Quit this program.                                        \n");
    printf("–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n\n");
    printf("Input your choice: ");
}