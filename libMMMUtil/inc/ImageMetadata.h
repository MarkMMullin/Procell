//
// Created by Mark Mullin on 5/18/18.
//

#ifndef FABAR_IMAGEMETADATA_H
#define FABAR_IMAGEMETADATA_H

#include <string>
#include <map>
#include <exiv2/exiv2.hpp>
class ImageMetadata
{
public:
    void ReadExif(uint8_t* imageBuffer,uint32_t& bufferLength);
    void InjectExif(uint8_t* imageBuffer,uint32_t& bufferLength);
    void addExifString(Exiv2::ExifData& exifData,const char* key,const char* data);
    std::string readExifString(Exiv2::ExifData& exifData,const char* key);
    long readExifInt(Exiv2::ExifData& exifData,const char* key);

    inline  std::string GetSource() const {
        return m_source;
    }

    inline  std::string GetDatetime() const {
        return m_datetime;
    }

    inline  std::string GetMillis() const {
        return m_millis;
    }

    inline  std::string GetPose() const {
        return m_pose;
    }

    int GetShotcounter() const {
        return m_shotcounter;
    }

    std::string GetChannel() const {
        return m_channel;
    }

    std::string GetId() const {
        return m_id;
    }

    void SetChannel(const std::string &channel) {
        m_channel = channel;
    }

    void SetId(const std::string &id) {
        m_id = id;
    }


private:
    std::string m_source;
    std::string m_datetime;
    std::string m_millis;
    std::string m_pose;

    // bring the channel and id in-band
    std::string m_channel;
    std::string m_id;

    int m_shotcounter;
};
#endif //FABAR_IMAGEMETADATA_H
