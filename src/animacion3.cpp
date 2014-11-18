//
//  animacion3.cpp
//  camaraExterior2
//
//  Created by el5jinete on 11/9/14.
//
//
#include "ofApp.h"
#include "animacion3.h"


void Animacion3::setup(){
    ofTrueTypeFont::setGlobalDpi(72);
    tipografia_18.loadFont("fonts/Dekar.otf", 18);
    tipografia_36.loadFont("fonts/Dekar.otf", 36);
    //pantalla.loadImage("pantalla3.png");
    lineasTiempo.load("miscelaneas3/lineasTiempo.svg");
    barraCelesteAudio.load("miscelaneas3/barraCelesteAudio.svg");
    barraCelesteDatosTermicos.load("miscelaneas3/barraCelesteDatosTermicos.svg");
    barraCelesteLuminocidad.load("miscelaneas3/barraCelesteLuminocidad.svg");
    circuloAmarillo.load("miscelaneas3/circuloAmarillo.svg");
    circuloCyan.load("miscelaneas3/circuloCyan.svg");
    circuloMagenta.load("miscelaneas3/circuloMagenta.svg");
    lampara.load("miscelaneas3/lampara.svg");
    lineaAbajo.load("miscelaneas3/lineaAbajo.svg");
    musica.load("miscelaneas3/musica.svg");
    termometro.load("miscelaneas3/termometro.svg");
    margen=20;
    
    //Sonido
    haySonido = false;
    left.assign(256, 0.0);
    
    
    
}

void Animacion3::update(){
    if (ofGetFrameNum()/50%2) {
        valor_1 = ofMap(ofNoise(ofRandom(0, 1000)) , 0, 1, 0, 999 );
        valor_2 = ofMap(ofNoise(ofRandom(0, 1000)) , 0, 1, 0, 999 );
        valor_3 = ofMap(ofNoise(ofRandom(0, 1000)) , 0, 1, 0, 999 );
    }
    
    if (ofGetFrameNum()/200%2) {
        valor_4 = ofMap(ofRandom(0, 1000) , 0, 10, 0, 100);
        valor_5 = ofMap(ofRandom(0, 1000) , 0, 10, 0, 100);
        valor_6 = ofMap(ofRandom(0, 1000) , 0, 10, 0, 100);
    }
    
    if (ofGetFrameNum()/60%2) {
        valor_7 = ofMap(ofNoise(ofRandom(0, 1000)) , 0, 1, 0, 999 );
        valor_8 = ofMap(ofNoise(ofRandom(0, 1000)) , 0, 1, 0, 999 );
        valor_9 = ofMap(ofNoise(ofRandom(0, 1000)) , 0, 1, 0, 999 );
    }
    
    for(int i=0; i<left.size(); i++){
        left[i] = ofMap(ofNoise(ofRandom(0, 1)) , 0.0, 1.0, 0.0, 1.0 ) * 0.5;
        
    }
    

    
}

void Animacion3::draw(){
    ofPushStyle();
    /*Linea de abajo*/
    ofPushMatrix();
    ofTranslate(20, ofGetHeight()-60);
    lineaAbajo.draw();
    
    
        /* sonido grafico */
        ofSetColor(41, 170,255,200);
        int lineaMedia=0;
        int maxSonido= 40;
        int minSonido= -40;
        int alturaSonido;
        int vol;
        if (ofGetFrameNum()/50%2) {
            vol =ofRandom(15,40);
            maxSonido = vol;
            minSonido = -vol;
        }
        if (ofGetFrameNum()/60%2) {
            vol =ofRandom(5,20);
            maxSonido = vol;
            minSonido = -vol;
        }

        for (int k=25; k<ofGetWidth()-50; k++) {
            ofBeginShape(); //shape
            alturaSonido = ofMap(ofNoise(ofRandom(0, 10)) , 0, 1, minSonido,maxSonido);
            ofVertex(k, lineaMedia);
            ofVertex( k+2, alturaSonido);
            ofVertex( k+4, lineaMedia);
            ofEndShape();

        }

    ofPopMatrix();
    /*Pack Cyan======================*/
    ofPushMatrix();
    base = 20;
    maxPico=15;
    minPico=8;
    pico = 1;
    ancho = 50;
    cantidadPicos = 5;
    ofTranslate( ofGetWidth()  - cantidadPicos * ancho +20, 650);
    //------
    ofSetColor(41, 170,255,200);
    ofFill();
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofSetColor(41, 170,255,150);
    ofFill();
    maxPico=maxPico*1.5;
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofSetColor(41, 170,255,100);
    ofFill();
    maxPico=maxPico*2;
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofPopMatrix();
    
    /*=======================*/
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - cantidadPicos * ancho +20, 670);
    lineasTiempo.draw();
    ofPopMatrix();
    /*=======================*/
    //barraCelesteAudio --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - cantidadPicos * ancho , 433);
    barraCelesteAudio.draw();
    tipografia_36.drawString("SONORIDAD", 0, -tipografia_36.stringHeight("SONORIDAD")/2);
    ofPopMatrix();
    //----------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloCyan.getWidth()*3 -50, 460+ 20);
    musica.draw();
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloCyan.getWidth()*3 -20, 460);
    circuloCyan.draw();
    ofSetColor(41, 170,255);
    tipografia_18.drawString(ofToString(valor_1), circuloCyan.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_1))/2, circuloCyan.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_1))/2);
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloCyan.getWidth()*2 -20, 460);
    circuloCyan.draw();
    ofSetColor(41, 170,255);
    tipografia_18.drawString(ofToString(valor_2), circuloCyan.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_2))/2, circuloCyan.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_2))/2);
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloCyan.getWidth() -20, 460);
    circuloCyan.draw();
    ofSetColor(41, 170,255);
    tipografia_18.drawString(ofToString(valor_3), circuloCyan.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_3))/2, circuloCyan.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_3))/2);
    ofPopMatrix();
    
    /*=======================*/
    ofPopStyle();
    
    /*==============================
     Grafico Amarillo
     ================================*/
    ofPushStyle();
    /*Pack Cyan======================*/
    ofPushMatrix();
    base = 20;
    maxPico=8;
    minPico=2;
    pico = 0;
    ancho = 50;
    cantidadPicos = 5;
    ofTranslate( ofGetWidth()  - cantidadPicos * ancho +20, 350);
    //------
    ofSetColor(241, 233,18,200);
    ofFill();
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofSetColor(241, 233,18,150);
    ofFill();
    maxPico=maxPico*1.5;
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofSetColor(241, 233,18,100);
    ofFill();
    maxPico=maxPico*2;
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(valor_1 , 0, 999, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofPopMatrix();
    
    /*=======================*/
    
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - cantidadPicos * ancho +20, 370);
    lineasTiempo.draw();
    ofPopMatrix();
    /*=======================*/
    //barraCelesteAudio --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - cantidadPicos * ancho , 133);
    barraCelesteLuminocidad.draw();
    tipografia_36.drawString("LUMINOSIDAD", 0, -tipografia_36.stringHeight("LUMINOSIDAD")/2);
    ofPopMatrix();
    //----------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloAmarillo.getWidth()*3 -50, 160+ 20);
    lampara.draw();
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloAmarillo.getWidth()*3 -20, 160);
    circuloAmarillo.draw();
    ofSetColor(241, 233,18,255);
    tipografia_18.drawString(ofToString(valor_4), circuloAmarillo.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_1))/2, circuloAmarillo.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_1))/2);
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloAmarillo.getWidth()*2 -20, 160);
    circuloAmarillo.draw();
    ofSetColor(241, 233,18,255);
    tipografia_18.drawString(ofToString(valor_5), circuloAmarillo.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_2))/2, circuloAmarillo.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_2))/2);
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( ofGetWidth()  - circuloAmarillo.getWidth() -20, 160);
    circuloAmarillo.draw();
    ofSetColor(241, 233,18,255);
    tipografia_18.drawString(ofToString(valor_6), circuloAmarillo.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_3))/2, circuloAmarillo.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_3))/2);
    ofPopMatrix();
    
    /*=======================*/
    ofPopStyle();
    
    /*===========================================
     Grafico Magenta
     ============================================*/
    ofPushStyle();
    /*Pack Cyan======================*/
    ofPushMatrix();
    base = 20;
    maxPico=8;
    minPico=2;
    pico = 0;
    ancho = 50;
    cantidadPicos = 5;
    ofTranslate( margen, 650);
    //------
    ofSetColor(235, 24,90,200);
    ofFill();
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofSetColor(235, 24,90,150);
    ofFill();
    maxPico=maxPico*1.5;
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofSetColor(235, 24,90,100);
    ofFill();
    maxPico=maxPico*2;
    for (int j=1; j<cantidadPicos; j++) {
        ofBeginShape(); //shape
        ofVertex( base, base);
        pico = ofMap(ofNoise(ofRandom(0, 100)) , 0, 1, -minPico,-maxPico);
        ofVertex( (ancho*j)/2, pico*j);
        ofVertex( ancho*j, base);
        ofEndShape();
    }
    ofPopMatrix();
    
    /*=======================*/
    
    ofPushMatrix();
    ofTranslate( margen, 670);
    lineasTiempo.draw();
    ofPopMatrix();
    /*=======================*/
    //barraCelesteAudio --------------------
    ofPushMatrix();
    ofTranslate( margen , 433);
    barraCelesteDatosTermicos.draw();
    tipografia_36.drawString("DATOS TERMICOS", 0, -tipografia_36.stringHeight("DATOS TERMICOS")/2);
    ofPopMatrix();
    //----------
    ofPushMatrix();
    ofTranslate( circuloMagenta.getWidth()*3 + 25, 460 + termometro.getHeight()/2);
    termometro.draw();
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate(20, 460);
    circuloMagenta.draw();
    ofSetColor(235, 24,90,255);
    tipografia_18.drawString(ofToString(valor_7), circuloMagenta.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_1))/2, circuloMagenta.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_1))/2);
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( circuloMagenta.getWidth() +20, 460);
    circuloMagenta.draw();
    ofSetColor(235, 24,90,255);
    tipografia_18.drawString(ofToString(valor_8), circuloMagenta.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_2))/2, circuloMagenta.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_2))/2);
    ofPopMatrix();
    //circulos --------------------
    ofPushMatrix();
    ofTranslate( circuloMagenta.getWidth()*2 +20, 460);
    circuloMagenta.draw();
    ofSetColor(235, 24,90,255);
    tipografia_18.drawString(ofToString(valor_9), circuloMagenta.getWidth()/2 - tipografia_18.stringWidth(ofToString(valor_3))/2, circuloMagenta.getHeight()/2 + tipografia_18.stringHeight(ofToString(valor_3))/2);
    ofPopMatrix();
    
    /*=======================*/
    ofPopStyle();
    
    
    
}
//--------------------------------------------------------------
void Animacion3::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		left[i]		= input[i*2]*0.5;
        
		curVol += left[i] * left[i];
		numCounted+=2;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
	
	// this is how we get the root of rms :)
	curVol = sqrt( curVol );
	
	smoothedVol *= 0.93;
	smoothedVol += 0.07 * curVol;
	
	bufferCounter++;
	
}
//--------------------------------------------------------------

