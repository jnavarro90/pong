#ifndef INSTANCE_H_
#define INSTANCE_H_

#include "globals.h"

class CInstance
{
  protected:
    SDL_Surface* fondo;
    bool i_running;
  public:
    CInstance(){};
    virtual ~CInstance(){};

    virtual bool Init();
      virtual bool LoadFiles();

    virtual void Close(){}
      virtual void UnLoadFiles(){}

    virtual int OnExecute();

    virtual void OnLoop(){};
    virtual void OnEvent(){};
    virtual void OnRender(){};
};



#endif /* INSTANCE_H_ */
