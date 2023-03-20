
#include <stdio.h>
#include <stdlib.h>
#include "AdptArray.h"

typedef struct AdptArray_{
    PElement* arr;
    int size;
    COPY_FUNC copyfunc;
    DEL_FUNC delfunc;
    PRINT_FUNC printfunc;
} AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copyfunc, DEL_FUNC delfunc, PRINT_FUNC printfunc)
{
    PAdptArray adptArray = (PAdptArray)malloc(sizeof(AdptArray));
    if(!adptArray) return NULL;
    adptArray->size = 0;
    adptArray->arr = NULL;
    adptArray->copyfunc = copyfunc;
    adptArray->delfunc = delfunc;
    adptArray->printfunc = printfunc;
    return adptArray;
}

void DeleteAdptArray(PAdptArray adptArray)
{
    if(!adptArray)
    {
        return;
    }
    if(!(adptArray->arr))
    {
        free(adptArray);
        return;
    }
    for(int i = 0; i< (adptArray->size); i++)
    {
        if(adptArray->arr[i])
        {
            (adptArray->delfunc)(adptArray->arr[i]);
        }
    }
    free(adptArray->arr);
    free(adptArray);
    return;
}

Result SetAdptArrayAt(PAdptArray adptArray, int index, PElement val)
{
    if(!adptArray || index<0 || val == NULL) return FAIL;
    PElement new_var = (adptArray->copyfunc)(val);
    if(!new_var)return FAIL;
    if((adptArray->size) == 0)
    {
        adptArray->arr = (PElement*)calloc((index+1), sizeof(PElement));
        if(!(adptArray->arr))
        {
            return FAIL;
        }
        adptArray->arr[index] = new_var;
        adptArray->size = index+1;
        return SUCCESS;
    }
    if((adptArray->size) <= index)
    {
        PElement* temp = (PElement*)calloc((index+1), sizeof(PElement));
        if(!temp) return FAIL;
        for(int i = 0; i< (adptArray->size); i++)
        {
            if(adptArray->arr[i]){
                temp[i] = adptArray->arr[i];
            }
        }
        PElement* temp2 = adptArray->arr;
        adptArray->arr = temp;
        free(temp2);
        adptArray->arr[index] = new_var;
        adptArray->size = index+1;
        return SUCCESS;
    }
    if(adptArray->arr[index]) (adptArray->delfunc)(adptArray->arr[index]);
    adptArray->arr[index] = new_var;
    adptArray->size += 1;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray adptArray, int index)
{
    if(!adptArray || !(adptArray->arr) || index<0 || (adptArray->size)<index || !(adptArray->arr[index])) return NULL;
    // if(adptArray->size <= index)
    // {
    //     adptArray->arr = (PElement*)realloc(adptArray->arr, (index+1)*sizeof(PElement));
    //     adptArray->size = index+1;
    //     return NULL;
    // }
    // if(!adptArray->arr[index]) return NULL;
    PElement copy = (adptArray->copyfunc)(adptArray->arr[index]);
    return copy;
}

int GetAdptArraySize(PAdptArray adptArray)
{
    if(!adptArray || !adptArray->arr)return -1;
    return adptArray->size;
}


void PrintDB(PAdptArray adptArray)
{
    if(!adptArray) return;
    for(int i = 0; i < (adptArray->size); i++)
    {
        if((adptArray->arr)[i]){
            (adptArray->printfunc)((adptArray->arr)[i]);
        }
    }
}