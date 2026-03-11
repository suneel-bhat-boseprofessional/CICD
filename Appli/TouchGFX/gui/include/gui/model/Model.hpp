#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener);
    void tick();

    // selected zone
    void setSelectedZone(int index);
    int getSelectedZone();

    // volume per zone
    void setZoneVolume(int index, int value);
    int getZoneVolume(int index);

private:
    ModelListener* modelListener;

    int selectedZone;
    int zoneVolume[4];
};

#endif
