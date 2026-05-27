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
    virtual void notifyGoToLaunch() {}
    virtual void notifyIOColorsChanged() {}
    virtual void notifyDeviceInfoChanged() {}

protected:
    Model* model;
};

#endif
