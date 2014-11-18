//
//  animacion.cpp
//  camaraExterior
//
//  Created by Federico Joselevich Puiggrós on 9/11/14.
//
//

#include "animacion.h"

void Animacion::setup(){
    margen=10;
    circuloConPuntos.load("miscelaneas/ciruloConPuntos.svg");
    ciruloCategorias.load("miscelaneas/ciruloConPuntosMed.svg");
    
    ofTrueTypeFont::setGlobalDpi(72);
    tipografia_65.loadFont("fonts/Dekar.otf", 65);
    tipografia_36.loadFont("fonts/Dekar.otf", 36);
    tipografia_18.loadFont("fonts/Dekar.otf", 18);
    tipografia_09.loadFont("fonts/Dekar.otf", 9);
    //barraAmarilla
    barraAmarilla.loadImage("miscelaneas/barraAmarilla.png");
    //barraHorizontal
    barraHorizontal.load("miscelaneas/barraHorizontal.svg");
    
    //barra lateral tipitos
    barraLateralVisitantes.load("miscelaneas/barraLateralVisitantes.svg");
    dato_regionesCulturales=89;
    
    textoOutput="";
    
    //regiones culturales
    regionesCulturales.load("miscelaneas/regionesCulturales.svg");
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
    // Regiones
    regiones[0] = "Fvg65gha\ngt af74r N3gr5";
    regiones[1] = "Tr3vg\nxx af74r iu89";
    regiones[2] = "C1hen0\ntr af74r EE#5";
    regiones[3] = "8ef5a\n33 abdD444";
    regiones[4] = "TR45esa\nFF 000 FFF";
    
    datoTipitos=0;
    valorVisitantes=0;
    
   }

void Animacion::update(){
    // grafico amarillo visitantes
    if (ofGetFrameNum()/160%2) {
       valorVisitantes = valorVisitantes + int(ofRandom(0, 3));
    }
    
    datoVisitantes = ofToString(valorVisitantes);
    //datoVisitantesHeight = 50;
    
    //dato2 = ofRandom(0, 10);
    
    /*===== TIPO DE VISITANTE =======*/
    cantidadTipoDeIndividuo = 0;
    
    datoTipoDeVisitante1 = ofNoise(ofRandom(0, 10)) ;
    datoTipoDeVisitante2 = ofNoise(ofRandom(0, 10)) ;
    datoTipoDeVisitante3 = ofNoise(ofRandom(0, 10)) ;
    datoTipoDeVisitante4 = ofNoise(ofRandom(0, 10)) ;
    
    if (ofGetFrameNum()/80%2) {
        valorAlfa = ofMap(ofNoise(ofRandom(0, 10)) , 0, 1, 0, 100);
    } else{
        valorBeta = ofMap(ofNoise(ofRandom(0, 10)) , 0, 1, 0, 100);
    }
    if (ofGetFrameNum()/50%2) {
    valorGama = ofMap(ofNoise(ofRandom(0, 10)) , 0, 1, 0, 100);
    }
    
    datocategoriaAlafa = ofToString(valorAlfa );
    datocategoriaBeta = ofToString(valorBeta);
    datocategoriaGama = ofToString(valorGama);
    
    /*===== REGIONES CULTURALES=======*/
   
    if (ofGetFrameNum()/50%2) {
        dato_regionesCulturales++;
        regionesTexto = regiones[int(ofRandom(0, 5))];
    }
    if (dato_regionesCulturales>100000) {
        dato_regionesCulturales=50;
    }
    
    
    /*===== DATOS TIPITOS ========*/
    
    if (ofGetFrameNum()/50%2) {
       datoTipitos = datoTipitos + ofRandom(-2, 4);
        if(datoTipitos>1023) datoTipitos = 50;
        if(datoTipitos<10) datoTipitos = 20;
    }
    textoTipitos = ofToString( datoTipitos );
    
    /*=== TEXTO QUE CORRE */
     if (ofGetFrameNum()/50%2) {
        textoOutput = "";
        for (int i=0; i<60; i++){
            for (int j=0; j<10; j++){
                textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
                textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
                textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
                textoOutput = textoOutput + textoQueCorre[int(ofRandom(0, 16))];
                textoOutput = textoOutput + " ";
            }
            textoOutput = textoOutput + "\n";
        }
     }
  
}

void Animacion::draw(){
     ofPushStyle();

    ofSetColor(241, 233, 18,100);
    ofFill();
    tipografia_09.drawString(textoOutput, 20, 20);
    
   
    /*===============================================================================*/
    //barraAmarilla
    barraAmarilla.draw(ofGetWidth()/4 , ofGetHeight() - barraAmarilla.getHeight());
    
    /*===== CANTIDAD DE INDIVIDUOS ===========================================================*/
    
    ofPushMatrix();
    
    //posicion circulo
	ofTranslate(ofGetWidth() / 4 + margen , ofGetHeight()  - circuloConPuntos.getHeight() - tipografia_36.stringWidth("09#af#FC00")/2 - margen);
    //ofRotate( ofMap(mouseX, 0, ofGetWidth(), 0, 360) );
    ofSetColor(241, 233, 18);
    tipografia_36.drawString( datoVisitantes, circuloConPuntos.getWidth()/2- tipografia_36.stringWidth(datoVisitantes)/2 , circuloConPuntos.getHeight()/2 + tipografia_36.stringHeight(datoVisitantes)/2 );
    circuloConPuntos.draw();
    //titulo del circulo
    tipografia_36.drawString( "09#af#FC00", circuloConPuntos.getWidth()/2 - tipografia_36.stringWidth("INDIVIDUOS")/2 , circuloConPuntos.getHeight() + tipografia_36.stringHeight("INDIVIDUOS") );
    
    ofPopMatrix();
    
    /*===== CATEGORIA DE INDIVIDUOS ===========================================================*/
    //------------ Alfa ----------------------
    ofPushMatrix();
    //posicion circulo
	ofTranslate(ofGetWidth() / 4 + circuloConPuntos.getWidth() + 50,
                ofGetHeight()  - ciruloCategorias.getHeight() - tipografia_18.stringWidth("FVMfsggt¿ ALFA")/2 - 20);
    //ofRotate( ofMap(mouseX, 0, ofGetWidth(), 0, 360) );
    ofSetColor(241, 233, 18);
    tipografia_18.drawString( datocategoriaAlafa, ciruloCategorias.getWidth()/2 - tipografia_18.stringWidth(datocategoriaAlafa)/2 , ciruloCategorias.getHeight()/2 + tipografia_18.stringHeight(datocategoriaAlafa)/2  );
    //dibujo circulo
    ciruloCategorias.draw();
    //titulo del circulo
    tipografia_18.drawString( "FVMfsggt¿ AtF4", ciruloCategorias.getWidth()/2 - tipografia_18.stringWidth("CATEGORIA AtF4")/2 , ciruloCategorias.getHeight() + tipografia_18.stringHeight("FVMfsggt¿ AtF4") +margen);
    
    ofPopMatrix();
    //------------ Beta ----------------------
    ofPushMatrix();
    //posicion circulo
	ofTranslate(ofGetWidth() / 4 + circuloConPuntos.getWidth()*2 + 50,
                ofGetHeight()  - ciruloCategorias.getHeight() - tipografia_18.stringWidth("FVMfsggt¿ ALFA")/2 - 20);
    //ofRotate( ofMap(mouseX, 0, ofGetWidth(), 0, 360) );
    ofSetColor(241, 233, 18);
    tipografia_18.drawString( datocategoriaBeta, ciruloCategorias.getWidth()/2 - tipografia_18.stringWidth(datocategoriaBeta)/2 , ciruloCategorias.getHeight()/2 + tipografia_18.stringHeight(datocategoriaBeta)/2  );
    //dibujo circulo
    ciruloCategorias.draw();
    //titulo del circulo
    tipografia_18.drawString( "FVMfsggt¿ B3T7", ciruloCategorias.getWidth()/2 - tipografia_18.stringWidth("FVMfsggt¿ B3T7")/2 , ciruloCategorias.getHeight() + tipografia_18.stringHeight("FVMfsggt¿ B3T7") +margen);
    
    ofPopMatrix();
    //------------ Gama ----------------------
    ofPushMatrix();
    //posicion circulo
	ofTranslate(ofGetWidth() / 4 + circuloConPuntos.getWidth()*3 + 50,
                ofGetHeight()  - ciruloCategorias.getHeight() - tipografia_18.stringWidth("FVMfsggt¿ Gh60")/2 - 20);
    //ofRotate( ofMap(mouseX, 0, ofGetWidth(), 0, 360) );
    ofSetColor(241, 233, 18);
    tipografia_18.drawString( datocategoriaGama, ciruloCategorias.getWidth()/2 - tipografia_18.stringWidth(datocategoriaGama)/2 , ciruloCategorias.getHeight()/2 + tipografia_18.stringHeight(datocategoriaGama)/2  );
    //dibujo circulo
    ciruloCategorias.draw();
    //titulo del circulo
    tipografia_18.drawString( "FVMfsggt¿ Gh60", ciruloCategorias.getWidth()/2 - tipografia_18.stringWidth("FVMfsggt¿ Gh60")/2 , ciruloCategorias.getHeight() + tipografia_18.stringHeight("FVMfsggt¿ Gh60") +margen);
    
    ofPopMatrix();
    
    
    /*===== TIPO DE VISITANTE ===========================================================*/
    //BARRA 1
    //barraHorizontal
    ofPushMatrix();
	ofTranslate(ofGetWidth() - barraHorizontal.getWidth() - margen , ofGetHeight() / 2 - circuloConPuntos.getHeight()/2 );
    barraHorizontal.draw();
    //ofPopStyle();
    ofSetColor(234, 29, 91);
    tipografia_18.drawString("g!dGHmlagr", 0, cantidadTipoDeIndividuo * 50);
    //ofPushStyle();
    ofSetColor(234, 29, 91, 50);
    ofRect(5, cantidadTipoDeIndividuo * 50, ofMap(datoTipoDeVisitante1 , 0, 1, 0 + margen+5, barraHorizontal.getWidth() - margen), 10);
    ofPopMatrix();
    cantidadTipoDeIndividuo++;
    /*------------------------------*/
    
    //BARRA 2
    //barraHorizontal
    ofPushMatrix();
	ofTranslate(ofGetWidth() - barraHorizontal.getWidth() - margen , ofGetHeight() / 2 - circuloConPuntos.getHeight()/2 + cantidadTipoDeIndividuo * 50);
    barraHorizontal.draw();
    //ofPopStyle();
    ofSetColor(234, 29, 91);
    tipografia_18.drawString("n4j56jdf7", 0, 0);
    //ofPushStyle();
    ofSetColor(234, 29, 91, 50);
    ofRect(5, 0, ofMap(datoTipoDeVisitante2, 0, 1, 0 + margen+5, barraHorizontal.getWidth() - margen), 10);
    ofPopMatrix();
    cantidadTipoDeIndividuo++;
    /*------------------------------*/
    //BARRA 3
    //barraHorizontal
    ofPushMatrix();
	ofTranslate(ofGetWidth() - barraHorizontal.getWidth() - margen , ofGetHeight() / 2 - circuloConPuntos.getHeight()/2 + cantidadTipoDeIndividuo * 50);
    barraHorizontal.draw();
    //ofPopStyle();
    ofSetColor(234, 29, 91);
    tipografia_18.drawString("g560djjF00", 0, 0);
    //ofPushStyle();
    ofSetColor(234, 29, 91, 50);
    ofRect(5, 0, ofMap(datoTipoDeVisitante3, 0, 1, 0 + margen+5, barraHorizontal.getWidth() - margen), 10);
    ofPopMatrix();
    cantidadTipoDeIndividuo++;
    /*------------------------------*/
    //BARRA 4
    //barraHorizontal
    ofPushMatrix();
	ofTranslate(ofGetWidth() - barraHorizontal.getWidth() - margen , ofGetHeight() / 2 - circuloConPuntos.getHeight()/2 + cantidadTipoDeIndividuo * 50);
    barraHorizontal.draw();
    //ofPopStyle();
    ofSetColor(234, 29, 91);
    tipografia_18.drawString("FF00rtf", 0, 0);
    //ofPushStyle();
    ofSetColor(234, 29, 91, 50);
    ofRect(5, 0, ofMap(datoTipoDeVisitante4, 0, 1, 0 + margen+5, barraHorizontal.getWidth() - margen), 10);
    ofPopMatrix();
    cantidadTipoDeIndividuo++;
    /*------------------------------*/
    

    /*===============================================================================*/   
    
    
    //regionesculturales
    ofPushMatrix();
    ofTranslate( margen*2, regionesCulturales.getHeight() );
     if (ofGetFrameNum()/50%2) {
         ofColor c(2234, 29, 91);
         regionesCulturales.getPathAt(35).setColor(c);
     } else {
         regionesCulturales.getPathAt(35).setColor(255);
     }
    ofSetColor(234, 29, 91);
    regionesCulturales.draw();
    //ofMap(mouseX, 0, ofGetWidth(), 0, 360)
    tipografia_36.setLineHeight(36);
    tipografia_36.drawString(regionesTexto, 10, 120);
    tipografia_36.drawString( ofToString(dato_regionesCulturales), 0 + margen, 0);
    
    ofPopMatrix();
    
    /*=============== BARRA TIPITOS ========================*/
    
    ofPushMatrix();
	ofTranslate(ofGetWidth() - barraLateralVisitantes.getWidth() - margen , barraLateralVisitantes.getHeight()/2 );
    ofPushStyle();
    ofSetColor(234, 29, 91,150);
    ofRect(5, barraLateralVisitantes.getHeight() - 15, ofMap( datoTipitos,0,1024,0,barraLateralVisitantes.getWidth() - margen) , 10);
    ofPopStyle();
    barraLateralVisitantes.draw();
    
    
    tipografia_18.drawString(textoTipitos, barraLateralVisitantes.getWidth() - tipografia_18.stringWidth(textoTipitos) - margen , 10);
    
    ofPopMatrix();
    ofPopStyle();
    
    
    

    
    
    
    
    
}