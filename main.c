#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>
#include <ctype.h>

#define LENGTH 10

FILE *fp;

char *name = "sample";

int numberReading();
char *binaryRecordReturn(char *array, int size);

int main()
{
    setlocale(LC_ALL, "Rus");
    fp = fopen(name, "w");
    int c, acc;
    acc = 0;
    char array[100], cb, *data, *a;
    printf("Введите количество вершин графа:\n");

    int numberOfVertices = numberReading();

    char **string = (char**)malloc(numberOfVertices * sizeof(char*));
    
    for(int i = 0; i < numberOfVertices; i++)
    {
        cb = i+1+'0';
        fputc(cb, fp);
        fputc(32, fp);
        printf("Введите вершины, смежные с ");
        printf("%d", (i+1));
        printf("-ой вершиной:\n");
        for(int j = 0; j < 100 && (c = getchar()) != EOF && c != '\n'; j++)
        {
            array[j] = c;
            fputc(c, fp);
            acc++;
        }
        data = (char*)malloc(acc * sizeof(char));
        for(int j = 0; j < acc; j++)
        {
            data[j] = array[j];
        }
        fputc('\n', fp);
        string[i] = data;
        for(int j = 0; j < 100; j++)
        {
            array[j] = '\0';
        }
    }
    printf("\n");
    printf("Таблица смежности графа:");
    printf("\n\n");
    for(int i = 0; i < numberOfVertices; i++)
    {
        a = binaryRecordReturn(string[i], numberOfVertices);
        for(int j = 0; j < numberOfVertices; j++)
        {
            printf("%c ", a[j]);
        }
        printf("\n");
    }
    fclose(fp);
    printf("\n");
    int reb = 0;
    for (int i = 0; i<numberOfVertices; i++) 
        for (int j = 0; j<numberOfVertices; j++)  
            reb = reb + *(a + i*numberOfVertices + j);

    int k = 0.5*(numberOfVertices-1)*(numberOfVertices-2);
    if (reb>k)
        printf ("граф связан\n");
    if (reb<=k)
        printf ("Граф не связан\n");

    system("./makegraph");
    return 0;
}

char *binaryRecordReturn(char *array, int size)
{
    char *str = (char*)malloc(size * sizeof(char));
    for(int i = 0; i < size; i++)
    {
        str[i] = '0';
    }
    for(int i = 0; *array != '\0'; i++)
    {
        if(isdigit(*(array+i)))
        {
            str[*(array+i)-'0'-1] = '1';
        }
        *(array++);
    }

    return &str[0];
}

int numberReading()
{
    int c, acc, a;
    char array[LENGTH];
    acc = 0;
    a = 0;
    for(int j = 0; j < LENGTH && (c = getchar()) != EOF && c != '\n'; j++)
    {
        acc++;
        array[j] = c - '0';
    }
    int b = acc-1;
    for(int j = 0; j < acc; j++, b--)
    {
        a += array[j]*pow(10,b);
    }
    return a;
}