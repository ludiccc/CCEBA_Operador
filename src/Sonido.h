#ifndef SONIDO_H
#define SONIDO_H

#include "ofMain.h"

class Sonido
{
    public:
        float pitch;
        //objeto sonido

        void actualizar();
        void cambiarPitch(int nuevo,int viejo);

        Sonido();
        virtual ~Sonido();
    protected:
    private:
        ofSoundPlayer base;
};

#endif // SONIDO_H
