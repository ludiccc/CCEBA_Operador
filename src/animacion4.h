//
//  animacion4.h
//  camaraExterior2
//
//  Created by el5jinete on 11/9/14.
//
//

#ifndef __camaraExterior2__animacion4__
#define __camaraExterior2__animacion4__


#include <stdio.h>
#include "ofMain.h"
#include "ofxSvg.h"
#define NLetras 16


class Animacion4 {
    
public:
    void setup();
    void update();
    void draw();
    
    // Properties
    int x;
    int y;
    string texto;
    float escala;
    
    //layout
    int margen;
    
    //tipografia
    ofTrueTypeFont tipografia_65;
    ofTrueTypeFont tipografia_36;
    ofTrueTypeFont tipografia_18;
    ofTrueTypeFont tipografia_09;
    
    int numeroDerecha;

    
    //test
    ofImage pantalla;
    string textoQueCorre[NLetras];
    string textoOutput;
    
    
    
    
};


#endif /* defined(__camaraExterior2__animacion4__) */
