#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxXmlSettings.h"
#include "camara.h"
#include "Sonido.h"
#include "ofxCvHaarFinder.h"
#include <math.h>       /* atan2 */
#include "animacion.h"
#include "animacion2.h"
#include "animacion3.h"
#include "animacion4.h"


//------ESTADOS PARA EL OPERADOR------
#define STANDBY 0
#define CONTROLA 1
#define CONTROLANDO 2
#define FINALIZA 3
//------------------------------------

// listen on port 12345

#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp {
	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    
    void audioIn(float * input, int bufferSize, int nChannels);
    ofSoundStream soundStream;
    vector <float> left;
    
		ofTrueTypeFont font;
		ofxOscReceiver receiver;

    int port;
    string destIP;
    int destPort;

    Camara camaras[4];
    
    ofVideoGrabber video;
    
    ofxCvGrayscaleImage grayImage;
    ofxCvHaarFinder finder;
    vector <ofImage> operadoresDetectados;
    
    
    bool lastFrameFoundCara;


    //---------VARIABLES PARA DETECTAR LA "TENSION" DEL LUGAR Y MODIFICAR EL SONIDO---------
    Sonido sonido;
    int estadoOperador; //para el boton
    bool operando;
    unsigned int operandoTimer;
    bool huboOperador; //variable para saber si en el rango de tiempo, alguien opera
    //--------------TENSION-------------
    int gradoTension;
    int gradoAnterior;
    int rangoTiempo;
    int contadorTiempo;
    int indiceImg;
    float tiempoOperador;
    bool actualizarRango;

    int numeroOperador;//cantidad de operadores
    int tiempoControl;//de cada operador
    int cantClicks; //de cada operador
    //------------------------------------
    //--------------------------------------------------------------------------------------

    ofxXmlSettings XML;

		int current_msg_string;
		string msg_strings[NUM_MSG_STRINGS];
		float timers[NUM_MSG_STRINGS];

		int mouseX, mouseY;
		string mouseButtonState;

        
    // Interfaz
    ofImage base;
    ofImage marcoOperador;
    ofImage marcoCamaras;
    ofTrueTypeFont tipografia_24;
    ofTrueTypeFont tipografia_38;
    ofTrueTypeFont tipografia_65;

    Animacion animacion0;
    Animacion animacion1;
    Animacion2 animacion2;
    Animacion3 animacion3;
    Animacion4 animacion4;
    
    //Animacion Apertura y Cierre de pantalla del operador
    ofImage fondoEscudoLeft;
    ofImage fondoRight;
    bool abrir;
    bool movimientoOn;
    float counter;
    

};
