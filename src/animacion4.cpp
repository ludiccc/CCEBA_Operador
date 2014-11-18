//
//  animacion4.cpp
//  camaraExterior2
//
//  Created by el5jinete on 11/9/14.
//
//

#include "animacion4.h"


void Animacion4::setup(){
    ofTrueTypeFont::setGlobalDpi(72);
    //pantalla.loadImage("pantalla4.png");
    tipografia_18.loadFont("fonts/Dekar.otf", 18);
    tipografia_09.loadFont("fonts/Dekar.otf", 9);
    
    //Texto que Corre
    textoQueCorre[0]="A";
    textoQueCorre[1]="B";
    textoQueCorre[2]="C";
    textoQueCorre[3]="D";
    textoQueCorre[4]="E";
    textoQueCorre[5]="F";
    textoQueCorre[6]="0";
    textoQueCorre[7]="1";
    textoQueCorre[8]="2";
    textoQueCorre[9]="3";
    textoQueCorre[10]="4";
    textoQueCorre[11]="5";
    textoQueCorre[12]="6";
    textoQueCorre[13]="7";
    textoQueCorre[14]="8";
    textoQueCorre[15]="9";

    
    
}

void Animacion4::update(){
    if (ofGetFrameNum()/60%2) {
        numeroDerecha = ofMap(ofNoise(ofRandom(10)), 0, 1, 0, 100);
    }
    /*=== TEXTO QUE CORRE */
    textoOutput = "";
    for (int i=0; i<10; i++){
        for (int j=0; j<100; j++){
            textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
            textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
            textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
            textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
            textoOutput = textoOutput + " ";
        }
        textoOutput = textoOutput + "\n";
    }


    
}

void Animacion4::draw(){
    ofPushStyle();
    ofSetColor(241, 233, 18);
    ofFill();
    tipografia_09.drawString(textoOutput, 0, 20);
    ofPopMatrix();
    ofSetColor(255);
    ofSetLineWidth(2);
    //linea top right
    ofLine(955, 182, 0, 1000, 182, 0);
    ofLine(1000, 182, 0, 1000, 182+45, 0);
    //linea top left
    ofLine(20, 182, 0, 20+45, 182, 0);
    ofLine(20, 182, 0, 20, 182+45, 0);
    
     //linea bottom left
    ofLine(20, 697, 0, 20, 697+45, 0);
    ofLine(20, 697+45, 0, 20+45, 697+45, 0);
    //linea bottom right
    ofLine(955, 697+45, 0, 1000, 697+45, 0);
    ofLine(1000, 697+45, 0, 1000, 697, 0);
    
    //--- lineas de adentro ---
    ofSetLineWidth(1);
    //linea top left
    ofLine(20+130, 182+130, 0, 20+130+45, 182+130, 0);
    ofLine(20+130, 182+130, 0, 20+130, 182+130+45, 0);
    //linea top right
    ofLine( 955-130, 182+130, 0, 1000-130, 182+130, 0);
    ofLine(1000-130, 182+130, 0, 1000-130, 182+130+45, 0);
    
    
    //linea bottom left
    ofLine(20+130, 697-130, 0, 20+130, 697+45-130, 0);
    ofLine(20+130, 697+45-130, 0, 20+45+130, 697+45-130, 0);
    //linea bottom right
    ofLine(955-130, 697+45-130, 0, 1000-130, 697+45-130, 0);
    ofLine(1000-130, 697+45-130, 0, 1000-130, 697-130, 0);
    
    ofPushStyle();
    ofSetColor(0);
    ofRect(932, 432, 90, 13);
    if (ofGetFrameNum()/60%2) {
        ofSetColor(255);
        ofRect(932, 432, 90, 13);
    }
    ofFill();
    
    tipografia_18.drawString(ofToString( numeroDerecha ), 932 + 45, 432 + 30);
    ofPopStyle();
    
    ofSetColor(0, 176, 76);// video pintado
    //termometro
    // pantalla.draw( 0,0);
    
    
    
}
