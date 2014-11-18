//
//  animacion3.h
//  camaraExterior2
//
//  Created by el5jinete on 11/9/14.
//
//

#ifndef __camaraExterior2__animacion3__
#define __camaraExterior2__animacion3__


#include <stdio.h>
#include "ofMain.h"
#include "ofxSvg.h"


class Animacion3 : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    // Properties
    int x;
    int y;
    string texto;
    float escala;
    int base;
    int maxPico;
    int minPico;
    int pico;
    int ancho;
    int cantidadPicos;
    
    
    //layout
    int margen;
    int valor_1;
    int valor_2;
    int valor_3;
    int valor_4;
    int valor_5;
    int valor_6;
    int valor_7;
    int valor_8;
    int valor_9;
    //tipografia
    ofTrueTypeFont tipografia_65;
    ofTrueTypeFont tipografia_36;
    ofTrueTypeFont tipografia_18;
    ofTrueTypeFont tipografia_09;
    
    ofxSVG lineasTiempo;
    ofxSVG barraCelesteAudio;
    ofxSVG barraCelesteDatosTermicos;
    ofxSVG barraCelesteLuminocidad;
    ofxSVG circuloAmarillo;
    ofxSVG circuloCyan;
    ofxSVG circuloMagenta;
    ofxSVG lampara;
    ofxSVG lineaAbajo;
    ofxSVG musica;
    ofxSVG termometro;
    
    //test
    ofImage pantalla;
    
    
    //Sonido
    bool haySonido;
    vector <float> left;
    void audioIn(float * input, int bufferSize, int nChannels);
    int 	bufferCounter;
    int 	drawCounter;
    float smoothedVol;
    float scaledVol;
    ofSoundStream soundStream;
    
        
    
    
};


#endif /* defined(__camaraExterior2__animacion3__) */
