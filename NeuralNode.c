
#include "Train.h"

int main(void){
    int Choice;
    int AnaResult = 0;
    double AnaDatum[3][3] = { //default analyzation datums, for option 1 and 2
        {15.437946,  -18.944745,  -18.944745},//Row 1 is the datum for RED
        {-18.944745,  15.437946,  -18.944745},//Row 2 is the datum for GREEN
        {-18.944745,  -18.944745,  15.437946}//Row 3 is the datum for BLUE
    };
    double AnaDatumCo[3][3] = {0}; //customized analyzation datums used in option 3
    double AnaObj[3] = {0}; //analyzation object in RGB values


    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf("*                                                                       *\n");
    printf("*                         INSTRUCTION                                   *\n");
    printf("*                                                                       *\n");
    printf("* Input '1': Give me values, then I will tell you what color it is.     *\n");
    printf("*                                                                       *\n");
    printf("* Input '2': Generate values randomly. You can check if I'm correct.    *\n");
    printf("*                                                                       *\n");
    printf("* Input '3': Follow your own special taste.                             *\n");
    printf("*                                                                       *\n");
    printf("* Input '-1': Quit this program.                                        *\n");
    printf("*                                                                       *\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
    printf("Input your choice: ");
    scanf("%d", &Choice);
    
    do{
        switch (Choice)
        {
            case 1:
                ObjInput(AnaObj); //input RGB values
                AnaResult = Analyze(AnaObj, AnaDatum); //analyzation and return result
            break;

            case 2:
                ClrGenerate(AnaObj);//generate RGB values
                AnaResult = Analyze(AnaObj, AnaDatum);//analyzation and return result
            break;

            case 3:
                DatumCustomize(AnaDatumCo);//customize analyzation datums
                ObjInput(AnaObj);//input RGB values
                AnaResult = Analyze(AnaObj, AnaDatumCo);//analyzation and return result
            break;

            case -1:
            break;

            default:
                printf("No such a choice, please tell me what you want to do.\n\n");
            break;
        }
        
        switch (AnaResult){
            case 1:
                    printf("\nThis color can be called Red.\n\n");
                    OptionPrint();
                    scanf("%d", &Choice);
            break;
                
            case 2:
                    printf("\nThis color can be called Green.\n\n");
                    OptionPrint();
                    scanf("%d", &Choice);
            break;        

            case 3:
                    printf("\nThis color can be called Blue.\n\n");
                    OptionPrint();
                    scanf("%d", &Choice);
            break;

            default: break;
        }
    } while(Choice != -1);

    printf("\nGoodbye!\n\n");
}