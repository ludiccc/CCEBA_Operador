#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

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


    areaDeClick.set(600,400,400,300);
    finder.setup("haarcascade_frontalface_default.xml");

    int camWidth 		= 640;	// try to grab at this size.
    int camHeight 		= 480;
    
    video.setVerbose(true);
    video.initGrabber(camWidth,camHeight);
    lastFrameFoundCara = false;

}

//--------------------------------------------------------------
void ofApp::update(){


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
            //cout << "recibida una imagen de " << m.getRemoteIp() << "\n";
            ofBuffer buffer = m.getArgAsBlob(0);
            for (int i = 0; i < 4; i++) {
                if (m.getRemoteIp() == camaras[i].IP) {
                    camaras[i].receivedImage.loadImage(buffer);
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
        finder.findHaarObjects(grayImage, 80, 80);
        
        if (lastFrameFoundCara && finder.blobs.size() == 0) {
            lastFrameFoundCara = false;
        }
        if (!lastFrameFoundCara) {
            for (int i = 0; i < finder.blobs.size(); i++) {
                lastFrameFoundCara = true;
                ofRectangle cur = finder.blobs[i].boundingRect;
                if (operadoresDetectados.size() >= 10) {
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


//--------------------------------------------------------------
void ofApp::draw(){

	string buf;
	buf = "listening for osc messages on port:" + ofToString(port);
	ofDrawBitmapString(buf, 10, 20);
    
    for (int i = 0; i < 4; i++) {
        ofSetColor(128,128,128);
        ofRect(10+(i%2)*170, 60+(i/2)*150,160,120);
        ofDrawBitmapString("IP:"+camaras[i].IP,10+(i%2)*170, 50+(i/2)*150);
        if(camaras[i].receivedImage.getWidth() > 0){
            ofDrawBitmapString("Image:", 10, 160);
            camaras[i].receivedImage.draw(10+(i%2)*170, 60+(i/2)*150);
        }
    }

	// draw mouse state
	buf = "mouse: " + ofToString(mouseX, 4) +  " " + ofToString(mouseY, 4);
	ofDrawBitmapString(buf, 430, 20);
	ofDrawBitmapString(mouseButtonState, 580, 20);

	ofDrawBitmapString("pitch: "+ ofToString(sonido.pitch),650,20);

	for(int i = 0; i < NUM_MSG_STRINGS; i++){
		ofDrawBitmapString(msg_strings[i], 10, 40 + 15 * i);
	}

    ofSetColor(128,128,128);
    ofRect(areaDeClick);
    for (int i = 0; i < 4; i++) {
        ofSetColor(255, 128, 0);
        int tmpX = camaras[i].x+areaDeClick.x;
        int tmpY = camaras[i].y+areaDeClick.y;
        ofRect(tmpX, tmpY, 10, 10);

        ofSetColor(255,0,0);
        // aqu’ habr’a que dibujar el ‡ngulo de visi—n...
        ofLine(tmpX, tmpY, tmpX + cos(ofDegToRad(camaras[i].anguloInicial))*100, tmpY + sin(ofDegToRad(camaras[i].anguloInicial))*100);
        ofSetColor(255,0,255);
        // aqu’ habr’a que dibujar el ‡ngulo de visi—n...
        ofLine(tmpX, tmpY, tmpX + cos(ofDegToRad(camaras[i].anguloFinal))*100, tmpY + sin(ofDegToRad(camaras[i].anguloFinal))*100);
    }
    for (int i = 0; i < operadoresDetectados.size(); i++) {
        operadoresDetectados[i].draw(10+(i%5)*45, 500+(i/5)*45, 50, 50);
    }
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

    if (key=='a'){
        operando = true; //boton del sillon
    }

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
