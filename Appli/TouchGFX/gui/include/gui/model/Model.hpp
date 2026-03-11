#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;


#define ZONE_COUNT 4
#define ZONE_NAME_MAX_LEN 20

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

    // zone names
    void setZoneName(int index, const char* name);
    const char* getZoneName(int index) const;
    void setAllZoneNames(const char* names[], int count);

    static char zoneNames[ZONE_COUNT][ZONE_NAME_MAX_LEN];

private:
    ModelListener* modelListener;

    int selectedZone;
    int zoneVolume[ZONE_COUNT];
};

#endif
