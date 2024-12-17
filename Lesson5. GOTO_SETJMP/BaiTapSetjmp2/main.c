#include <stdio.h>
#include <setjmp.h>

enum ErrorCodes
{
    NO_ERROR =  1,
    FILE_ERROR,
    NETWORK_ERROR,
    CALCULATION_ERROR
};

int exception_code;
jmp_buf buf;

char* error_message = NULL;

#define TO_STRING(x) #x

#define TRY if((exception_code = setjmp(buf)) <= NO_ERROR)
#define CATCH(error) else if (exception_code == error)
#define THROW(error, message) {                 \
    exception_code = error;                     \
    error_message = TO_STRING(message);         \
    longjmp(buf, error);                        \
}

void readFile()
{
    printf("Reading File...\n");
    fflush(stdin);
    scanf("%d",&exception_code);
    if(exception_code == FILE_ERROR){
        THROW(FILE_ERROR, File read error: File does not exist!);
    }
}

void networkOperation()
{
    printf("Checking Network...\n");
    fflush(stdin);
    scanf("%d",&exception_code);
    if(exception_code == NETWORK_ERROR){
        THROW(NETWORK_ERROR, Network connection error: Network unavailable!);
    }
}

void calculateData()
{
    printf("Caculate Data...\n");
    fflush(stdin);
    scanf("%d",&exception_code);
    if(exception_code == CALCULATION_ERROR){
        THROW(CALCULATION_ERROR, Data processing error: Incorrect syntax!);
    }
}


int main()
{
    TRY
    {  
        readFile();
        ReadFile_OK:
        networkOperation();
        NetWork_OK:
        calculateData();
    }
    CATCH(FILE_ERROR)
    {
        printf("%s\n", error_message);
        for(int i = 0; i < 5; i++ ){
            printf("Trying to read the file again.\n");
        }
        fflush(stdin);
        scanf("%d",&exception_code);
        if(exception_code == FILE_ERROR){  
            longjmp(buf,FILE_ERROR);
        }
        printf("Read File Successfully!\n");
        goto ReadFile_OK;
    }
    CATCH(NETWORK_ERROR)
    {
        printf("%s\n", error_message);
        for(int i = 0; i < 5; i++ ){
            printf("Trying connect network again.\n");
        }
        fflush(stdin);
        scanf("%d",&exception_code);
        if(exception_code == NETWORK_ERROR){
            longjmp(buf, NETWORK_ERROR);
        }
        fflush(stdin);
        printf("Connect network Successfully!\n");
        goto NetWork_OK;
    } 
    CATCH(CALCULATION_ERROR)
    {
        printf("%s\n", error_message);
        for(int i = 0; i < 5; i++ ){
            printf("Trying caculate file again.\n");
        }
        fflush(stdin);
        scanf("%d",&exception_code);
        if(exception_code == CALCULATION_ERROR){
            longjmp(buf, CALCULATION_ERROR);
        } 
        printf("Caculate file Successfully!\n");
    } 
    int recheck = 0;
    printf("Task executed successfully!\n");
    printf("Do you want to re-check? 1- yes, 0 - no\n");
    fflush(stdin);
    scanf("%d",&recheck);
    if(recheck) longjmp(buf, NO_ERROR);
    return 0;
}
