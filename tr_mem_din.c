/**
*   @author rodebox00
*/

#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define BUF_SIZE 1024
#define MAX_BUF 134217728
#define PARA_MIN 5     //numeros parametros minimos del programa


void writeall(int fdout, size_t bytes, char *buffer){
    ssize_t num_written;
    char *buf = buffer; //guardamos el puntero al buffer
    
    while (bytes > 0 && (num_written = write(fdout, buf, bytes)) != -1)
    {
        buf += num_written;
        bytes -= num_written;
    }
    
    if(num_written == -1){
        perror("write()");
        exit(EXIT_FAILURE);
    }

    assert(bytes==0);
}

void change(int fdin, int fdout, char *buffer, size_t bytes, size_t long1, char *cadena1, char *cadena2){
    ssize_t num_read;
    int c = 0;
    size_t bytesleidos;

    while(c == 0){ 

        num_read = read(fdin, buffer, bytes);
        
        if(num_read == -1){
            perror("read()");
            exit(EXIT_FAILURE);
        }else if(num_read < bytes) bytesleidos = num_read;  //Se han leido menos bytes de los pasados por parametro a read
        else bytesleidos = bytes;   

        for(int i=0;i<bytesleidos;i++){
            for(int c=0;c<long1;c++){
                if(cadena1[c] == buffer[i]){
                    buffer[i] = cadena2[c];
                }
            }
        }

        writeall(fdout, bytesleidos, buffer);
        if(num_read == 0) c=1;
    }
}

int main(int argc, char **argv)
{

    if(argc==1){    //Entra si no se reciben argumentos
            fprintf(stderr, "Uso: %s -s SRC -d DST [-t SIZE] [-o FILEOUT] [FILEIN1 FILEIN2 ... FILEINn] \n", argv[0]);
            exit(EXIT_FAILURE);
    }

    int opt;
    size_t bytes = BUF_SIZE;
    char *buffer = NULL;
    char *cadena1 = NULL;
    char *cadena2 = NULL;
    int long1, long2=-1;
    int fdin = STDIN_FILENO;
    int fdout = STDOUT_FILENO;
    char *filein = NULL;
    char *fileout = NULL;
    int paramopc = PARA_MIN;   //contador de parámetros opcionales

    while ((opt = getopt(argc, argv,"s:d:t:o:")) != -1)
    {
        switch (opt)
        {
        case 's':
            cadena1=optarg;
            long1 = strlen(cadena1);
            if((long2 > -1 && long1 != long2) || long1 == 0){
                fprintf(stderr, "Error: SRC y DST deben ser cadenas de caracteres de la misma longitud\n");
                exit(EXIT_FAILURE);
            }
            break;

        case 'd':
            cadena2=optarg;
            long2 = strlen(cadena2);
            if((long1 > -1 && long1 != long2) || long2 == 0){
                fprintf(stderr, "Error: SRC y DST deben ser cadenas de caracteres de la misma longitud\n");
                exit(EXIT_FAILURE);
            }
            break;

        case 't':
            bytes=atoi(optarg);
            if((bytes < 1) || (bytes > MAX_BUF)){
                fprintf(stderr, "Error: SIZE debe ser un valor entre 1 y %d\n", MAX_BUF);
                exit(EXIT_FAILURE);  
            }
            paramopc += 2;
            break;

        case 'o':
            fileout = optarg;
            fdout = open(fileout, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            if (fdout == -1)
            {   
                perror("open(fileout)");
                exit(EXIT_FAILURE);
            }
            paramopc += 2;
            break;

        default:
            fprintf(stderr, "Uso: %s -s SRC -d DST [-t SIZE] [-o FILEOUT] [FILEIN1 FILEIN2 ... FILEINn] \n", argv[0]);
            exit(EXIT_FAILURE);
            break;
        }
    }

    buffer= malloc(bytes);


    if(paramopc == argc)  //No hay ficheros de entrada
    {  
        change(fdin, fdout, buffer, bytes, long1, cadena1, cadena2);

    }else   //Hay ficheros de entrada
    {
        int diferencia = argc-paramopc;
        for(int i=0;i<diferencia;i++){
            fdin = open(argv[paramopc+i], O_RDONLY );
            if (fdin == -1)
            {
                perror("open(filein)");
                exit(EXIT_FAILURE);
            }
            
            change(fdin, fdout, buffer, bytes, long1, cadena1, cadena2);
        }
    }
    
    free(buffer);

return EXIT_SUCCESS;

}