#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    soundStream.listDevices();
    int bufferSize = 256;
    left.assign(bufferSize, 0.0);
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    tipografia_24.loadFont("fonts/Dekar.otf", 24);
    tipografia_38.loadFont("fonts/Dekar.otf", 38);
    tipografia_65.loadFont("fonts/Dekar.otf", 65);
    

    if( XML.loadFile("control.xml") ){
        cout << "control.xml loaded!";
    }else{
        cout << "unable to load mySettings.xml check data/ folder";
    }


    port = XML.getValue("PORT", 12346);
    destIP = XML.getValue("DESTIP", "localhost");
    destPort = XML.getValue("DESTPORT", 12345);

    camaras[0].setup(XML.getValue("CAMARAS:CAMARA0:IP", "127.0.0.1"),
                     XML.getValue("CAMARAS:CAMARA0:PORT", 12346),
                     XML.getValue("CAMARAS:CAMARA0:X", 0),
                    XML.getValue("CAMARAS:CAMARA0:Y", 0),
                    XML.getValue("CAMARAS:CAMARA0:ANGULOINICIAL", 0),
                    XML.getValue("CAMARAS:CAMARA0:ANGULOFINAL", 0)
                     );

    camaras[1].setup(XML.getValue("CAMARAS:CAMARA1:IP", "127.0.0.1"),
                     XML.getValue("CAMARAS:CAMARA1:PORT", 12346),
                     XML.getValue("CAMARAS:CAMARA1:X", 0),
                     XML.getValue("CAMARAS:CAMARA1:Y", 0),
                     XML.getValue("CAMARAS:CAMARA1:ANGULOINICIAL", 0),
                     XML.getValue("CAMARAS:CAMARA1:ANGULOFINAL", 0)
                     );

    camaras[2].setup(XML.getValue("CAMARAS:CAMARA2:IP", "127.0.0.1"),
                     XML.getValue("CAMARAS:CAMARA2:PORT", 12346),
                     XML.getValue("CAMARAS:CAMARA2:X", 0),
                     XML.getValue("CAMARAS:CAMARA2:Y", 0),
                     XML.getValue("CAMARAS:CAMARA2:ANGULOINICIAL", 0),
                     XML.getValue("CAMARAS:CAMARA2:ANGULOFINAL", 0)
                     );

    camaras[3].setup(XML.getValue("CAMARAS:CAMARA3:IP", "127.0.0.1"),
                     XML.getValue("CAMARAS:CAMARA3:PORT", 12346),
                     XML.getValue("CAMARAS:CAMARA3:X", 0),
                     XML.getValue("CAMARAS:CAMARA3:Y", 0),
                     XML.getValue("CAMARAS:CAMARA3:ANGULOINICIAL", 0),
                     XML.getValue("CAMARAS:CAMARA3:ANGULOFINAL", 0)
                     );


	// listen on the given port
	cout << "listening for osc messages on port " << port << "\n";
	receiver.setup(port);


	current_msg_string = 0;
	mouseX = 0;
	mouseY = 0;
	mouseButtonState = "";

	ofBackground(30, 30, 130);

	estadoOperador = STANDBY;

	rangoTiempo = 1000;
    
    nextFindCaras = 0;


    finder.setup("haarcascade_frontalface_default.xml");

    int camWidth 		= 640;	// try to grab at this size.
    int camHeight 		= 480;
    
    video.setVerbose(true);
    video.initGrabber(camWidth,camHeight);
    lastFrameFoundCara = false;
    ofHideCursor();
    
    base.loadImage("base.jpg");
    marcoOperador.loadImage("mini-marco-operador.png");
    marcoCamaras.loadImage("marco-camaras.png");
    
    animacion1.setup();
    animacion2.setup();
    animacion3.setup();
    animacion4.setup();
    //Animacion Apertura y Cierre de pantalla del operador
    counter=0;
    abrir=false;
    movimientoOn=false;
    fondoEscudoLeft.loadImage("bgEscudoLeft.png");
    fondoRight.loadImage("bgRight.png");



}

//--------------------------------------------------------------
void ofApp::update(){
    animacion1.update();
    animacion2.update();
    animacion3.update();
    animacion4.update();
    
    //Animacion Apertura y Cierre de pantalla del operador
    //condicional para cerrar
    if( ofGetKeyPressed('s' )){
        if (!operando) {
            operando = true; //boton del sillon
            operandoTimer = ofGetElapsedTimeMillis();
        }
        //Animacion Apertura y Cierre de pantalla del operador
        if(!movimientoOn){
            abrir= true;
            movimientoOn=!movimientoOn;
        }
        
    } else {
        operando = false;
        abrir= false;
        if (!movimientoOn) movimientoOn=true;
        
    }

    // end condicional para cerrar

    if (abrir){
        if(movimientoOn){
            counter= counter+10;
            if(counter > ofGetWidth()/2 + fondoEscudoLeft.getWidth()/2 ) {
              movimientoOn=false;
                counter = ofGetWidth()/2 + fondoEscudoLeft.getWidth()/2;
            }
        }
    }else{
        if(movimientoOn){
            counter= counter-20;
            if(counter <= 0 ) {
                counter=0;
                movimientoOn=false;
            }
        }
    }
    
    //---- end Animacion Apertura


    sonido.actualizar();
    

    //---------------ESTADO OPERADOR OPERANDO---------------
    if (estadoOperador==STANDBY){
        tiempoControl=0;
        cantClicks = 0;
        if (operando){
            cout <<"El operador comienza a controlar"<<"\n";
            numeroOperador++;
            estadoOperador = CONTROLANDO;
        }
    }
    if (estadoOperador==CONTROLANDO){
            tiempoControl++;
            tiempoOperador=ofMap(tiempoControl,0,10000,0,80);
        if(!operando){
            cout <<"El operador ha dejado de controlar"<<"\n";
            cout <<"Persona numero: "<<numeroOperador<< " estuvo "<<tiempoControl<<" milisegundos."<< "\n";
            estadoOperador = STANDBY;
            actualizarRango =true;
        }
    }
    //------------------------------------------------------
    //------------------ANALISIS DE TENSION-----------------
    if (contadorTiempo>rangoTiempo){
        actualizarRango=true;

    }

    if (actualizarRango){
        contadorTiempo=0;
        if (!huboOperador){
            tiempoOperador-=10;
        }
        gradoTension = tiempoOperador+cantClicks/5;
        //le mando el grado de tension al pitch
        sonido.cambiarPitch(gradoTension,gradoAnterior);

        actualizarRango=false;
        huboOperador=false;

    }else{
        contadorTiempo++;
        if (estadoOperador!=STANDBY){
            huboOperador=true;
        }
        gradoAnterior=gradoTension;
    }
    //cout <<"contador: "<<contadorTiempo<<"\n";
    //------------------------------------------------------



	// hide old messages
	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		if(timers[i] < ofGetElapsedTimef()){
			msg_strings[i] = "";
		}
	}

	// check for waiting messages
	while(receiver.hasWaitingMessages()){
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage(&m);

		// check for mouse moved message
		if(m.getAddress() == "/mouse/position"){
			// both the arguments are int32's
			mouseX = m.getArgAsInt32(0);
			mouseY = m.getArgAsInt32(1);
		}
		// check for mouse button message
		else if(m.getAddress() == "/mouse/button"){
			// the single argument is a string
			mouseButtonState = m.getArgAsString(0);
		}
        // check for an image being sent (note: the size of the image depends greatly on your network buffer sizes - if an image is too big the message won't come through )
        else if(m.getAddress() == "/image" ){
            cout << "recibida una imagen de " << m.getRemoteIp() << " quien tiene animacion numero:" << m.getArgAsInt32(0) << "\n";
            //OPofBuffer buffer = m.getArgAsBlob(0);
            for (int i = 0; i < 4; i++) {
                if (m.getRemoteIp() == camaras[i].IP) {
                    camaras[i].animacion = m.getArgAsInt32(0);
                    //OPcamaras[i].receivedImage.loadImage(buffer);
                    ofImage newImg;
                    newImg.loadImage("http://"+camaras[i].IP+"/rpicam/lastscrenshot.png");
                    if (newImg.width > 0) camaras[i].receivedImage = newImg;
                    
                    break;
                }
                
            }
            //receivedImage.loadImage(buffer);
        }
		else{
			// unrecognized message: display on the bottom of the screen
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			for(int i = 0; i < m.getNumArgs(); i++){
				// get the argument type
				msg_string += m.getArgTypeName(i);
				msg_string += ":";
				// display the argument - make sure we get the right type
				if(m.getArgType(i) == OFXOSC_TYPE_INT32){
					msg_string += ofToString(m.getArgAsInt32(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_FLOAT){
					msg_string += ofToString(m.getArgAsFloat(i));
				}
				else if(m.getArgType(i) == OFXOSC_TYPE_STRING){
					msg_string += m.getArgAsString(i);
				}
				else{
					msg_string += "unknown";
				}
			}
			// add to the list of strings to display
			msg_strings[current_msg_string] = msg_string;
			timers[current_msg_string] = ofGetElapsedTimef() + 5.0f;
			current_msg_string = (current_msg_string + 1) % NUM_MSG_STRINGS;
			// clear the next line
			msg_strings[current_msg_string] = "";
		}

	}
    
    video.update();
    //reconocimiento de cara
    if (video.isFrameNew()){
        
        ofxCvColorImage colorImg;
        colorImg.allocate(video.width,video.height);
        colorImg.setFromPixels(video.getPixelsRef());
        grayImage = colorImg;
        /*
         int totalPixels = camWidth*camHeight*3;
         unsigned char * pixels = vidGrabber.getPixels();
         unsigned char * pixelsDest = img.getPixels();
         for (int i = 0; i < totalPixels; i++){
         pixelsDest[i] = pixels[i];
         }*/
        if (nextFindCaras < ofGetElapsedTimeMillis()) {
            nextFindCaras = ofGetElapsedTimeMillis() + 1000;
            finder.findHaarObjects(grayImage, 80, 80);
            
            if (lastFrameFoundCara && finder.blobs.size() == 0) {
                lastFrameFoundCara = false;
            }
            if (!lastFrameFoundCara) {
                for (int i = 0; i < finder.blobs.size(); i++) {
                    lastFrameFoundCara = true;
                    ofRectangle cur = finder.blobs[i].boundingRect;
                    if (operadoresDetectados.size() >= 4) {
                        operadoresDetectados.erase(operadoresDetectados.begin());
                    }
                    
                    ofImage cara;
                    
                    cara.setFromPixels(video.getPixelsRef());
                    cara.crop(cur.x, cur.y, cur.width, cur.height);
                    
                    operadoresDetectados.push_back(cara);
                }
            }
        }
    }
}


//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255,255,255);
    base.draw(0,0);
    
	string buf;
	//buf = "listening for osc messages on port:" + ofToString(port);
	//ofDrawBitmapString(buf, 10, 20);
    
    for (int i = 0; i < 4; i++) {
        //ofSetColor(128,128,128);
        //ofDrawBitmapString("IP:"+camaras[i].IP,259+(i%2)*370, 120+(i/2)*257);
        if(camaras[i].receivedImage.getWidth() > 0){
            ofSetColor(255,255,255);
            camaras[i].receivedImage.draw(259+(i%2)*370, 120+(i/2)*257,370,257);
            
            //
            ofPushMatrix();
            float escala = 370.0/1024.0;
            ofTranslate(259+(i%2)*370, 120+(i/2)*257);
            ofScale(escala, escala);
            if (camaras[i].animacion == 0) animacion1.draw();
            else if (camaras[i].animacion == 1) animacion2.draw();
            else if (camaras[i].animacion == 2) animacion3.draw();
            else if (camaras[i].animacion == 3) animacion4.draw();

            ofPopMatrix();
        }
    }
    ofSetColor(255,255,255);
    marcoCamaras.draw(259,120);
    
    ofPushMatrix();
        buf = "";
        int secs = (ofGetElapsedTimeMillis() - operandoTimer) / 1000;
        int mins = secs/60;
        buf = ofToString(mins) + ":" + ((secs%60)<10?"0":"") + ofToString(secs%60);
    
        ofTranslate(259, 200);
        ofRotateZ(-45);
        ofSetHexColor(0xcd205a);
        tipografia_38.drawString(buf, 0, 0);
    ofPopMatrix();


	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}

    ofSetColor(255,255,255);

    for (int i = 0; i < operadoresDetectados.size(); i++) {
        operadoresDetectados[i].draw(45, 142*i+172, 134, 142);
        marcoOperador.draw(41,142*i+172);
    }
    ofPushStyle();
        ofSetHexColor(0x49bffd);
        ofSetLineWidth(3);
        
        ofBeginShape();
        for (unsigned int i = 0; i < left.size(); i++){
            ofVertex(ofMap(i, 0, 256, 0, ofGetWidth()), 710 -left[i]*380.0f);
        }
        ofEndShape(false);
    ofPopStyle();
    //Dibujo Animacion Apertura y Cierre de pantalla del operador
    fondoRight.draw(ofGetWidth()/2 + counter,0);
    fondoEscudoLeft.draw(0 - counter,0);
    
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == '1') {
        for (int i = 0; i < 4; i++) {
            camaras[i].setPosicion(0);
        }
    } else if (key == '2') {
        for (int i = 0; i < 4; i++) {
            camaras[i].setPosicion(100);
        }
    } else if (key == '3') {
        for (int i = 0; i < 4; i++) {
            camaras[i].setPosicion(50);
        }
    }

    /*if (key=='a'){
        operando = true; //boton del sillon
        operandoTimer = ofGetElapsedTimeMillis();
        //Animacion Apertura y Cierre de pantalla del operador
        if(!movimientoOn){
            abrir= !abrir;
            movimientoOn=!movimientoOn;
        }

    }*/

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key=='a'){
        operando = false;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

    // entonces le tengo que decir a cada motor que se mueva en una direcci—n en particular.
    for (int i = 0; i < 4; i++) {
        /*
        if (x-camaras[i].x == 0) continue; // me evito el problema de dominio
        int angulo = ofRadToDeg(atan2(y-camaras[i].y,x-camaras[i].x))+camaras[i].anguloInicial;
        

        int valorDestino = ofMap(angulo, camaras[i].anguloInicial, camaras[i].anguloFinal, 0, 100);

        cout << "El angulo calculado para " << i << " es de: " << angulo << "\n";
        cout << "El valor de movimiento es " << valorDestino << "\n";
        */
        camaras[i].ultimaPosicion = ofRandom(0,100);
        camaras[i].setPosicion(camaras[i].ultimaPosicion);
    }
    cantClicks++;

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}


//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    //lets go through each sample and calculate the root mean square which is a rough way to calculate volume
    for (int i = 0; i < bufferSize; i++){
        left[i]		= input[i*2]*0.5;
    }
    
    
}