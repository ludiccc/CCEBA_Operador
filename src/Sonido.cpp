#include "Sonido.h"


void Sonido::actualizar(){
    ofSoundUpdate();
    base.setSpeed(pitch);
}
void Sonido::cambiarPitch(int gradoActual,int gradoAnterior){
    if (gradoAnterior>gradoActual){
        if(pitch>1){
            pitch-=0.1;
        }
    }
    if(gradoAnterior<gradoActual){
        if(pitch<2){
            pitch+=0.1;
        }
    }
}

Sonido::Sonido()
{
    base.loadSound("sonido/base.wav");
    base.setVolume(0.75f);
    base.setLoop(true);
    base.play();
    pitch  = 1;
}

Sonido::~Sonido()
{
    //dtor
}
