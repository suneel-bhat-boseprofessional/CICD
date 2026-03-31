#ifndef MODEL_HPP
#define MODEL_HPP

enum { MODEL_MAX_ZONES = 16, MODEL_ZONE_NAME_MAX_LEN = 32, MODEL_MAX_SOURCES_PER_ZONE = 8, MODEL_SOURCE_NAME_MAX_LEN = 32 };

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

    void setZoneSourceCount(int zoneIdx, int count);
    int  getZoneSourceCount(int zoneIdx) const;
    void setZoneSourceName(int zoneIdx, int srcIdx, const char* name);
    const char* getZoneSourceName(int zoneIdx, int srcIdx) const;
    void setSelectedSource(int zoneIdx, int srcIdx);
    int  getSelectedSource(int zoneIdx) const;

    volatile bool zoneNamesChanged;

protected:
    ModelListener* modelListener;
    int  selectedZone;
    int  zoneVolumes[MODEL_MAX_ZONES];
    int  zonePrevVolumes[MODEL_MAX_ZONES];
    bool zoneMuted[MODEL_MAX_ZONES];
    char zoneNames[MODEL_MAX_ZONES][MODEL_ZONE_NAME_MAX_LEN];
    char zoneSources[MODEL_MAX_ZONES][MODEL_MAX_SOURCES_PER_ZONE][MODEL_SOURCE_NAME_MAX_LEN];
    int  zoneSourceCount[MODEL_MAX_ZONES];
    int  selectedSource[MODEL_MAX_ZONES];
};

#ifdef __cplusplus
extern "C" {
#endif

void set_zone_name_c(int idx, const char* name);
void set_zone_count_c(int count);
int  get_zone_count_c(void);
void set_zone_volume_c(int idx, int value);
void set_zone_muted_c(int idx, int muted);
void set_zone_source_count_c(int zoneIdx, int count);
void set_zone_source_name_c(int zoneIdx, int srcIdx, const char* name);
void set_selected_source_c(int zoneIdx, int srcIdx);

#ifdef __cplusplus
}
#endif

extern Model* modelInstance;

#endif
