//
//  animacion2.h
//  camaraExterior2
//
//  Created by el5jinete on 11/9/14.
//
//

#ifndef __camaraExterior2__animacion2__
#define __camaraExterior2__animacion2__

#include <stdio.h>
#include "ofMain.h"
#include "ofxSvg.h"


class Animacion2 {
    
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
    ofTrueTypeFont tipografia_30;
    ofTrueTypeFont tipografia_18;
    ofTrueTypeFont tipografia_09;
    
    
    // circulo amarillo mediano // categorias
    ofxSVG circuloCategorias;
    
    string dato_1;
    string dato_2;
    string dato_3;
    string valor_1_string;
    string valor_2_string;
    string valor_3_string;
    string valor_4_string;
    
    int valor_1;
    int valor_11;
    int valor_2;
    int valor_3;
    int valor_4;
    int escalaCorazon;
    
    //barra magenta
    ofxSVG barraArribaMagenta;
    //barra cyan
    ofxSVG barraAbajoCyan;
    ofxSVG barraVerticalinvertido;
    
    //barra Horizontal
    ofxSVG barraHorizontal;
    int cantidadTipoDeIndividuo;
    
    //barras izquierda magentas
    ofxSVG grafico1;
    ofxSVG graficoBarraVertical;
    ofxSVG corazon;
    
    //circulos medios
    ofxSVG circuloAmarillo;
    
    // grafico amarillo visitantes
    ofxSVG circuloConPuntos;
    string datoVisitantes;
    int valorVisitantes;
    
    //test
    ofImage pantalla;
    
    
    
};

#endif /* defined(__camaraExterior2__animacion2__) */
