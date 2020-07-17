#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void progressCallback(int index, int dataSize);
void handleData( void (*pCallback)(int, int), char* data, int dataSize );

void handleData( void (*pCallback)(int, int), char* data, int dataSize )
{
    int i=0;
    int j=0;
    while(data[i]!='\0' && i<dataSize)
    {
        while(j<=i)
        {
            printf("%c",data[j]);
            ++j;
        }
        ++i;
        j=0;
        /* this points to the progressCallback function
         * which will divide strlen(data) by the index (i) 
         * and return the percent.
         * We use strlen(data) and not dataSize
         * because, even if the user gives the size to be a specific number
         * the string he enters may be actually smaller in size.
         * so the percent would not be realistic.
         */
        pCallback(i,strlen(data));
    }
}

void progressCallback(int index, int dataSize)
{ 
    // print the percent with only 2 decimals to avoid redundance
    printf(" : %.2f%%\n", (float)index/(float)dataSize);
    // we cast both ints to float to make sure that the result is realistic.
}



int main(void)
{
    int dataSize = 0;
    char* buffer = 0;
    printf("Please give the size in bytes of the data you want to send.\n");
    printf("Keep in mind that one byte must be left for the \\0 special character ( string terminator ) :");
    scanf("%d",&dataSize);

    // allocating memory for the char* depending on the size the user gave.
    buffer = (char*)malloc(dataSize);
    if(buffer == 0)
    {
        fprintf(stderr,"Error when allocating the buffer.\n");
        exit(EXIT_FAILURE);
    }
    // clear the buffer in order to avoid reading before we actually want it
    getchar();

    //reads the buffer from standard input (keyboard)
    fgets(buffer,dataSize,stdin);

    /* if what we read has the size smaller than the buffer size we gave
     * fgets will also read the \n(enter)
     * so it needs to be remove explicitly.
     */
    if( buffer[strlen(buffer)-1] == '\n' )
    {
        buffer[strlen(buffer)-1] = '\0';
    }

    /* & gives the adress of the respective function 
     * so now the parameter will actually be an indicator to the 
     * progressCallback function
     */
    handleData(&progressCallback,buffer,dataSize);
    return 0;
}
