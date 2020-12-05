#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;
#include "Video.hpp"
int main(int argc, char *argv[])
{
    Video video;
    int n, opcion;
    do
    {
        printf( "\n   1. Imagen A.", 163);
        printf( "\n   2. Imagen B.", 163);
        printf( "\n   3. Imagen C.", 163);
        printf( "\n   4. Salir." );
        printf( "\n\n   Introduzca opci%cn (1-4): ", 163);
        scanf( "%d", &opcion );
        switch ( opcion )
        {
            case 1:
                    video.mostrarImagen1();
                    break;

            case 2: 
                    video.mostrarImagen2();
                    break;

            case 3: 
                    video.mostrarImagen3();
         }

         /* Fin del anidamiento */

    } while ( opcion != 4 );
    
    
    return 0;
};