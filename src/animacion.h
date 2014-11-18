//
//  animacion.h
//  camaraExterior
//
//  Created by Federico Joselevich Puiggrós on 9/11/14.
//
//

#ifndef __camaraExterior__animacion__
#define __camaraExterior__animacion__

#include <stdio.h>
#include "ofMain.h"
#include "ofxSvg.h"
#define NLetras 16
#define NRegiones 5

class Animacion {
    
public:
    void update();
    void draw();
    
    // Properties
    int x;
    int y;
    string texto;
    float escala;
    
    void setup();
    
    
    //layout
    int margen;
    
    //tipografia
    ofTrueTypeFont tipografia_65;
    ofTrueTypeFont tipografia_36;
    ofTrueTypeFont tipografia_18;
    ofTrueTypeFont tipografia_09;
    
    string textoQueCorre[NLetras];
    string textoOutput;
    string regiones[NRegiones];
    string regionesTexto;
    
    //textos
    //int cantidadCondicionIndividuo;
    //string textoCondicionIndividuo[4];
    
    // grafico amarillo visitantes
    ofxSVG circuloConPuntos;
    string datoVisitantes;
    int valorVisitantes;
    float datoVisitantesHeight;
    
    // circulo amarillo mediano // categorias
    ofxSVG ciruloCategorias;

    string datocategoriaAlafa;
    string datocategoriaBeta;
    string datocategoriaGama;
    
    int valorAlfa;
    int valorBeta;
    int valorGama;
    
    float datoCategoriaHeight;
    
    //barra lateral con tipitos
    ofxSVG barraLateralVisitantes;
    
    //barra Horizontal
    ofxSVG barraHorizontal;
    int cantidadTipoDeIndividuo;
    
    //barra amarilla
    ofImage barraAmarilla;
    
    //regiones culturales
    float dato_regionesCulturales;
    ofxSVG regionesCulturales;
    
    // Datos tipitos
    string textoTipitos;
    int datoTipitos;
    
    // DATOS PROPIOS
    //tipo de Visitante
    float datoTipoDeVisitante1;
    float datoTipoDeVisitante2;
    float datoTipoDeVisitante3;
    float datoTipoDeVisitante4;
    
    
    
};

#endif /* defined(__camaraExterior__animacion__) */