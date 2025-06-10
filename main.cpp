#include <iostream>
#include "sculptor.h"


int main() {
    // Cria um objeto Sculptor com tamanho 50x50x50
    Sculptor sculptor(80, 80, 80);

    // cinza
    sculptor.setColor(0.5, 0.5, 0.5, 1.0);

    // Coloca uma esfera
    sculptor.putSphere(25, 5, 25, 5);
    //cortar metade da esfera
    sculptor.cutBox(20, 30, 6, 10, 20, 30);

    //marrom
    sculptor.setColor(0.3, 0.2, 0.1, 1.0);

    //cabo do martelo
    sculptor.putBox(23, 27, 6, 30, 23, 27);

    //apoio mão
    sculptor.putBox(25, 32, 3, 6, 30, 33 );
    sculptor.cutBox(25, 40, 4, 5, 31, 32 );
    sculptor.cutEllipsoid(31, 6, 31, 3, 1, 3);
    sculptor.cutEllipsoid(27, 3, 32, 3, 2, 3);

    // cinza claro
    sculptor.setColor(0.7, 0.7, 0.7, 1.0);
    //acabo detalhe
    sculptor.putBox(22, 28, 9, 10, 22, 28);
    sculptor.putBox(22, 28, 15, 16, 22, 28);
    sculptor.putBox(22, 28, 21, 22, 22, 28);
    sculptor.putBox(22, 28, 27, 28, 22, 28);

    //retangulo
    sculptor.putBox(18, 32, 30, 44, 13, 37);
    //retangulos laterais
    sculptor.putBox(19, 31, 31, 43, 37, 38);
    sculptor.putBox(20, 30, 32, 42, 38, 39);
    sculptor.putBox(21, 29, 33, 41, 39, 40);

    sculptor.putBox(19, 31, 31, 43, 12, 13);
    sculptor.putBox(20, 30, 32, 42, 11, 12);
    sculptor.putBox(21, 29, 33, 41, 10, 11);


    sculptor.putBox(32, 33, 31, 43, 14, 36);
    sculptor.putBox(33, 34, 32, 42, 15, 35);

    sculptor.putBox(17, 18, 31, 43, 14, 36);
    sculptor.putBox(16, 17, 32, 42, 15, 35);
    // Salva o arquivo no formato OFF
    sculptor.writeOFF("modelo.off");

    std::cout << "Arquivo OFF gerado com sucesso!\n";
    return 0;
}
