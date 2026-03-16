#ifndef MODEL_HPP
#define MODEL_HPP

extern int zoneCount;

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }

    void tick();

    void setSelectedZone(int index);
    int getSelectedZone();

    void setZoneVolume(int index, int value);
    int getZoneVolume(int index);

    void setZoneName(int index, const char* name);
    const char* getZoneName(int index);

    volatile bool zoneNamesChanged;   // ← ADD flag

protected:
    ModelListener* modelListener;
    int selectedZone;
    int zoneVolumes[16];
    char zoneNames[16][32];
};

#ifdef __cplusplus
extern "C" {
#endif

void set_zone_name_c(int idx, const char* name);

#ifdef __cplusplus
}
#endif

extern Model* modelInstance;

#endif
