#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

class Model;

class ModelListener
{
public:
    ModelListener() : model(0) {}

    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void zoneNamesUpdated() {}
    virtual void notifyReadyReceived() {}

protected:
    Model* model;
};

#endif
