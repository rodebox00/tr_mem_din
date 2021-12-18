## Ejecución:

Este programa está escrito en base al estándar POSIX y simula la ejecución del comando tr. El programa se debe ejecutar según este patrón:

`./tr_mem_din -s SRC -d DST [-t SIZE] [-o FILEOUT] [FILEIN1 FILEIN2 ... FILEINn]`

Si no se incluye ningún fichero con la opción `-o` se usará la salida estándar. Ambas cadenas indicadas en `SRC` y `DST` deben tener la misma longitud que debe ser mayor o igual a 1. La opción `-t` permite indicar el tamaño del buffer de lectura/escritura que utilizará en programa, en caso de omisión se empleará un buffer de 1024 bytes. Los ficheros `FILEIN` corresponden a los ficheros de entrada a modificar, si no se indica ninguno se empleará la entrada estándar.

----------------------------------------------------------------------------

## Execution:

This program is written based on the POSIX standard and simulates the execution of the tr command. The program should run according to this pattern: 

`./tr_mem_din -s SRC -d DST [-t SIZE] [-o FILEOUT] [FILEIN1 FILEIN2 ... FILEINn]`

If no files are included with the `-o` option, standard output will be used. Both strings indicated in `SRC` and` DST` must have the same length that must be greater than or equal to 1. The `-t` option allows you to indicate the size of the read / write buffer that the program will use, otherwise a 1024 byte buffer will be used. The `FILEIN` files correspond to the input files to be modified, if no one is specified, standard input will be used.  
