#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    // Called from Model::tick when zone names changed from backend events.
    virtual void zoneNamesUpdated() {}
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
