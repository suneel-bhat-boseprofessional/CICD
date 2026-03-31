#ifndef MODEL_HPP
#define MODEL_HPP

enum { MODEL_MAX_ZONES = 16, MODEL_ZONE_NAME_MAX_LEN = 32 };

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
    int  getSelectedZone();

    void setZoneVolume(int index, int value);
    int  getZoneVolume(int index);

    void setZoneMuted(int index, bool muted);
    bool getZoneMuted(int index);

    void setZoneCount(int count);
    int  getZoneCount() const;

    void        setZoneName(int index, const char* name);
    const char* getZoneName(int index);

    volatile bool zoneNamesChanged;

protected:
    ModelListener* modelListener;
    int  selectedZone;
    int  zoneVolumes[MODEL_MAX_ZONES];
    int  zonePrevVolumes[MODEL_MAX_ZONES];
    bool zoneMuted[MODEL_MAX_ZONES];
    char zoneNames[MODEL_MAX_ZONES][MODEL_ZONE_NAME_MAX_LEN];
};

#ifdef __cplusplus
extern "C" {
#endif

void set_zone_name_c(int idx, const char* name);
void set_zone_count_c(int count);
int  get_zone_count_c(void);
void set_zone_volume_c(int idx, int value);
void set_zone_muted_c(int idx, int muted);

#ifdef __cplusplus
}
#endif

extern Model* modelInstance;

#endif
