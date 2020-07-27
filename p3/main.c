#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void progressCallback(int index, int dataSize);
void handleData( void (*pCallback)(int, int), char* data, int dataSize );

/*!
 *  \fn  void handleData( void (*pCallback)(int, int), char* data, int dataSize )
 *  \brief The function that handles the given task.
 *  \param pCallback Function pointer that indicates toward the progressCallback function.
 *  \param data Buffer with the string provided as entry data.
 *  \param dataSize Size in bytes of the input data.
 */
void handleData( void (*pCallback)(int, int), char* data, int dataSize )
{
    int i=0;
    while(data[i]!='\0' && i<dataSize) /* either we reach the end of the string(\0), or the maximum limit of bytes. */
    {
        printf("%3d",data[i]);
        ++i;
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

/*!
 *  \fn  void progressCallback(int index, int dataSize)
 *  \brief Receives 2 ints and prints how much is 'index' of 'dataSize'
 *  \param index The actual index of where the parsing process is at that very moment.
 *  \param dataSize Length of the string entered as input.
 */
void progressCallback(int index, int dataSize)
{ 
    /* %6.2f to be alligned perfectly one under another */
    printf(" | %6.2f%%\n", 100*(float)index/(float)dataSize);
}



int main(void)
{
    int dataSize = 0; /*! Wished data size */
    char* buffer = 0; /*! char ptr ( buffer in which we will store the input string) */
    printf("Please give the size in bytes of the data you want to send.\n");
    printf("Keep in mind that one byte must be left for the \\0 special character ( string terminator ) :");
    scanf("%d",&dataSize);

    /* allocating memory for the char* depending on the size the user gave. */
    buffer = (char*)malloc(dataSize);
    if(buffer == 0)
    {
        fprintf(stderr,"Error when allocating the buffer.\n");
        exit(EXIT_FAILURE);
    }

    /* clear the stdin buffer in order to avoid reading before we actually want it */
    getchar();

    printf("\nEnter the data in the buffer: ");
    /* reads the buffer from standard input (keyboard) */
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
