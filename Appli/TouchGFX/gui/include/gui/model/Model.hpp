#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/Unicode.hpp>

#define MAX_ZONES 20

extern int zoneCount;

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener);

    void tick();

    int getSelectedZone();
    void setSelectedZone(int index);

    int getZoneVolume(int index);
    void setZoneVolume(int index, int value);

private:
    ModelListener* modelListener;

    int selectedZone;

    int zoneVolume[MAX_ZONES];
};

extern "C" void set_zone_name_c(int index, const char* name);

#endif
