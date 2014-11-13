//
//  camara.h
//  operadorControl
//
//  Created by Federico Joselevich Puiggrós on 12/11/14.
//
//

#ifndef __operadorControl__camara__
#define __operadorControl__camara__

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"

class Camara {
public:
    void setup(string _IP, int _port, int _x, int _y, int _anguloInicial, int _anguloFinal);
    void setPosicion(int);

    
    int x, y;
    int anguloInicial, anguloFinal;
    string IP;
    int port;
    int ultimaPosicion;
    
    ofImage receivedImage;
    
    ofxOscSender camaraRemota;
};

#endif /* defined(__operadorControl__camara__) */
