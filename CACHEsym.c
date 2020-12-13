#include "stdio.h"
#include "stdlib.h"
//Structs
typedef struct {
    short int ETQ;
    short int Datos[8];
}T_LINEA_CACHE;

T_LINEA_CACHE cache[4];
int tiempoglobal = 0;
int numfallos = 0;

//Variables de las direcciones
unsigned int hexa[12];
short int lin;
short int etq;
short int bloq;
short int plbr;
char texto[100];

//Funcion Main
void main()
{
    InicioCache();
    ArchivoRAM();
    ArchivoMemoria();
}

//Funcion lectura archivo "RAM.bin"
void ArchivoRAM() {
    unsigned char RAM[1024];
    FILE *f_ram;
    f_ram = fopen("RAM.bin", "r");
    if (f_ram == NULL) {
        printf("El fichero no se ha podido abrir, intentelo de nuevo.\n");
        exit(-1);
    }
    fread(RAM, sizeof(RAM), 1, f_ram);
    printf("caracter: %d\n", RAM[216]);
    fclose(f_ram);
}

//Funcion lectura archivo "accesos_memoria.txt"
void ArchivoMemoria() {
    FILE *f_memo;
    f_memo = fopen("accesos_memoria.txt", "r");
    if (f_memo == NULL) {
        printf("El fichero no se ha podido abrir, intentelo de nuevo.\n");
        exit(-1);
    }

    fscanf(f_memo, "%x", &hexa[0]);
    lin = (hexa[0] & 0b0000011000) >> 3;
    etq = (hexa[0] & 0b0000000111);
    bloq = hexa[0] >> 5;
    plbr = hexa[0] >> 3;
    //Direcciones
    printf("Linea %d\n", lin);
    printf("Etiqueta %d\n", etq);
    printf("Bloque %d\n", bloq);
    printf("Palabra %d\n", plbr);

    if (cache[0].ETQ == etq) {
        printf("T: %d, Acierto de CACHE, ADDR %04X ETQ %X linea %02X palabra %02X DATO %02X", tiempoglobal, hexa[0], etq, lin, plbr, tiempoglobal);
        tiempoglobal += 1;
    }
    else {
        numfallos++;
        printf("T: %d, Fallo de CACHE %d, ADDR %04X ETQ %X linea %02X palabra %02X bloque %02X", tiempoglobal, numfallos, hexa[0], etq, lin, plbr, bloq);
        tiempoglobal += 10;

    }
    fclose(f_memo);
}
// Funcion inicializar todos los campos de la cache
void InicioCache() {
    for (int i = 0; i < 4; i++) {
        cache[i].ETQ = 0xFF;
        for (int j = 0; j < 8; j++) {
            cache[i].Datos[j] = 0;
        }
    }
}
