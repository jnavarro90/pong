#include "globals.h"

#ifndef ENGINE_H_
#define ENGINE_H_

#define N_INSTANCES 10

#include "instance.h"

class CEngine
{
  protected:
    CInstance* instance[N_INSTANCES];
    bool running;

  public:
    CEngine();
    virtual ~CEngine();

    virtual bool Init();
      virtual bool LoadFiles();
      virtual void BindInstances();
    virtual void Close();
      virtual void UnLoadFiles();

    virtual int OnExecute();
};

#endif /* CENGINE_H_ */
