//
//  animacion2.cpp
//  camaraExterior2
//
//  Created by el5jinete on 11/9/14.
//
//

#include "animacion2.h"

void Animacion2::setup(){
    ofTrueTypeFont::setGlobalDpi(72);
    tipografia_18.loadFont("fonts/Dekar.otf", 18);
    tipografia_30.loadFont("fonts/Dekar.otf", 30);
    tipografia_36.loadFont("fonts/Dekar.otf", 36);
    margen=10;
    barraArribaMagenta.load("miscelaneas2/barraMagenta.svg");
    barraAbajoCyan.load("miscelaneas2/barraCyan.svg");
    pantalla.loadImage("pantalla2.png");
    graficoBarraVertical.load("miscelaneas2/barraVertical.svg");
    circuloConPuntos.load("miscelaneas/ciruloConPuntos.svg");
    barraVerticalinvertido.load("miscelaneas2/barraVerticalinvertido.svg");
    corazon.load("miscelaneas2/corazon.svg");
    
}

void Animacion2::update(){
    
    
    if (ofGetFrameNum()/50%2) {
        valor_4 = ofMap(ofNoise(ofRandom(0, 80)) , 0, 1, 0, -graficoBarraVertical.getHeight()+margen );
        valor_4_string = ofToString(ofMap(valor_4, 0, -graficoBarraVertical.getHeight()+margen, 100,900));
        valor_11 = valor_11 - ofRandom(-2, 5);
        if(valor_11 < -135){
            valor_11 = -10;
        }
    } else{
        valor_3_string = ofToString(ofMap(valor_3, 0, -graficoBarraVertical.getHeight()+margen, 100,900));
    }
    if (ofGetFrameNum()/10%2) {
         valor_3 = valor_3 + ofMap(ofNoise(ofRandom(0, 50)) , 0, 1, 0, 5 );
        valor_3_string = ofToString(valor_2);
     }
    
    if (ofGetFrameNum()/100%2) {
        valor_2 = valor_2 + ofMap(ofNoise(ofRandom(0, 50)) , 0, 1, 0, 5 );
        valor_2_string = ofToString(valor_2);
    }
    if (ofGetFrameNum()/100%2) {
        valor_1 = valor_1 + ofMap(ofNoise(ofRandom(0, 50)) , 0, 1, 0, 10 );
        valor_1_string = ofToString(valor_2);
    }
    escalaCorazon = ofMap(ofNoise(ofRandom(0, 10)) , 0, 1, 1.0,1.0 );
    
}

void Animacion2::draw(){
    ofPushStyle(); // Evito que se coloree el video
    
    //---- barras arriba y abajo ----
    ofPushMatrix();
    ofTranslate(0, margen);
    barraArribaMagenta.draw();
    ofPopMatrix();
    
    //  ---- barra cyan -----
    ofPushMatrix();
    ofTranslate( 0, ofGetHeight() - barraAbajoCyan.getHeight() - margen);
    barraAbajoCyan.draw();
    ofPopMatrix();
    
    /*==================================================*/
    //-- barra vertical 1 --
    ofPushMatrix();
    ofTranslate( margen, 30 );
    graficoBarraVertical.draw();
    ofSetColor(234, 29, 91);
    tipografia_30.drawString("CDxhr1", 0, graficoBarraVertical.getHeight() + margen*1.5 );
    ofSetColor(234, 29, 91, 100);
    ofRect( margen*6.5, graficoBarraVertical.getHeight() - margen*2, 10, valor_11);
    ofPopMatrix();
    
    //-- barra vertical 2 --
    ofPushMatrix();
    ofTranslate( margen,  graficoBarraVertical.getHeight() + tipografia_30.stringWidth("CD3hr1") );
    graficoBarraVertical.draw();
    ofSetColor(234, 29, 91);
    tipografia_30.drawString("CD9hr2", 0 , graficoBarraVertical.getHeight() + margen*1.5 );
    ofSetColor(234, 29, 91, 100);
    ofRect( margen*6.5, graficoBarraVertical.getHeight() - margen*2, 10, ofMap(ofNoise(ofRandom(0, 300)) , 0, 1, 0, -graficoBarraVertical.getHeight()+margen ));
    ofPopMatrix();
    
    //-- barra vertical 3 --
    ofPushMatrix();
    ofTranslate( margen,  graficoBarraVertical.getHeight()*2 +30+ tipografia_30.stringWidth("CD3hr2") );
    graficoBarraVertical.draw();
    ofSetColor(234, 29, 91);
    tipografia_30.drawString("CD3hr3", 0 , graficoBarraVertical.getHeight() + margen*1.5 );
    ofSetColor(234, 29, 91, 100);
    ofRect( margen*6.5, graficoBarraVertical.getHeight() - margen*2, 10, ofMap(ofNoise(ofRandom(0, 800)) , 0, 1, 0, -graficoBarraVertical.getHeight()+margen ));
    ofPopMatrix();
    
    //-- Texto Cyan--
    ofSetColor(41, 170, 255);
    tipografia_36.drawString( valor_2_string, 150 + margen, ofGetHeight() - barraAbajoCyan.getHeight() - margen );
    tipografia_30.drawString( valor_3_string, 150 + margen*2 + 207, ofGetHeight() - barraAbajoCyan.getHeight() - margen );
    tipografia_30.drawString( valor_1_string, 150 + margen*2 + 320, ofGetHeight() - barraAbajoCyan.getHeight() - margen );
    
    //------------ Circulo Alfa ----------------------
    ofPushMatrix();
    //posicion circulo
    ofTranslate(ofGetWidth() - circuloConPuntos.getWidth() - 25,
                ofGetHeight()  - circuloConPuntos.getHeight()*2.5 - tipografia_18.stringWidth("C4T3GOR1A AF4LA")/2 - 20);
    //ofRotate( ofMap(mouseX, 0, ofGetWidth(), 0, 360) );
    ofSetColor(241, 233, 18);
    tipografia_18.drawString( ofToString(valor_3+valor_4), circuloConPuntos.getWidth()/2 - tipografia_18.stringWidth( ofToString(valor_3+valor_4) )/2 , circuloConPuntos.getHeight()/2 + tipografia_18.stringHeight( ofToString(valor_3+valor_4) )/2  );
    //dibujo circulo
    circuloConPuntos.draw();
    //titulo del circulo
    tipografia_18.drawString( "C4T3GOR1A AF4LA", circuloConPuntos.getWidth()/2 - tipografia_18.stringWidth("C4T3GOR1A AF4LA")/2 , circuloConPuntos.getHeight() + tipografia_18.stringHeight("C4T3GOR1A AF4LA") +margen);
    ofPopMatrix();
    
    //------------ Circulo Beta ----------------------
    ofPushMatrix();
    //posicion circulo
    ofTranslate(ofGetWidth() - circuloConPuntos.getWidth() - 25,
                ofGetHeight()  - circuloConPuntos.getHeight() - tipografia_18.stringWidth("C4T3GOR1A B3TAL")/2 - 20);
    //ofRotate( ofMap(mouseX, 0, ofGetWidth(), 0, 360) );
    ofSetColor(241, 233, 18);
    tipografia_18.drawString( ofToString(valor_3+valor_2), circuloConPuntos.getWidth()/2 - tipografia_18.stringWidth( ofToString(valor_3+valor_2) )/2 , circuloConPuntos.getHeight()/2 + tipografia_18.stringHeight( ofToString(valor_3+valor_2) )/2  );
    //dibujo circulo
    circuloConPuntos.draw();
    //titulo del circulo
    tipografia_18.drawString( "C4T3GOR1A B3TAL", circuloConPuntos.getWidth()/2 - tipografia_18.stringWidth("C4T3GOR1A B3TAL")/2 , circuloConPuntos.getHeight() + tipografia_18.stringHeight("C4T3GOR1A B3TAL") +margen);
    ofPopMatrix();
    
    /*==================================================*/
    //-- barra vertical 1 --
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - barraVerticalinvertido.getWidth() - 25, 80 );
    barraVerticalinvertido.draw();
    //barrita 1
    ofSetColor(234, 29, 91, 100);
    for (int i=0; i<10; i++) {
        ofRect(31, i*10+5*i + 12, ofMap(ofNoise(ofRandom(0, 10)) , 0, 1, -40, -10), 10);    }
    
    ofPopMatrix();
    /*==================================================*/
    //-- corazon--
    ofPushMatrix();
    ofTranslate( ofGetWidth() - corazon.getWidth() - 24, 75 );
    ofPushMatrix();
    ofTranslate( 0-corazon.getWidth()/2, 0-corazon.getHeight()/2 );
    ofScale(0.5 , 0.5);
    corazon.draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(620, ofGetHeight()-60); 
    
    /* sonido grafico */
    ofSetColor(41, 170,255,200);
    int lineaMedia=0;
    int maxSonido=10;
    int minSonido=-10;
    int alturaSonido;
    int vol;
    
    if (ofGetFrameNum()/50%2) {
        vol =ofRandom(15,30);
        maxSonido = vol;
        minSonido = -vol;
    }
    if (ofGetFrameNum()/60%2) {
        vol =ofRandom(5,20);
        maxSonido = vol;
        minSonido = -vol;
    }
    
    for (int k=0; k<225; k++) {
        ofBeginShape(); //shape
        alturaSonido = ofMap(ofNoise(ofRandom(0, 10)) , 0, 1, minSonido,maxSonido);
        ofVertex(k, lineaMedia);
        ofVertex( k+2, alturaSonido);
        ofVertex( k+4, lineaMedia);
        ofEndShape();
        
    }
    ofPopMatrix();

    
    
    
    
    
    
    ofPopStyle();// Evito que se coloree el video
    
    
    
}
