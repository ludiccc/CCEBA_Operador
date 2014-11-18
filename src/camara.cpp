//
//  camara.cpp
//  operadorControl
//
//  Created by Federico Joselevich Puiggrós on 12/11/14.
//
//

#include "camara.h"


void Camara::setup(string _IP, int _port, int _x, int _y, int _anguloInicial, int _anguloFinal) {
    IP = _IP;
    port = _port;
    x = _x;
    y = _y;
    anguloInicial = _anguloInicial;
    anguloFinal = _anguloFinal;

    camaraRemota.setup(IP,port);

    ultimaPosicion = ofRandom(0,100);
    setPosicion(ultimaPosicion);
}

void Camara::setPosicion(int posicion) {
    cout << "Enviando un cambio de posicion a " <<  IP << " al " << posicion << "\n";
    ofxOscMessage m;
    m.setAddress("/motor/position");
    m.addIntArg(posicion);
    camaraRemota.sendMessage(m);
    
}
