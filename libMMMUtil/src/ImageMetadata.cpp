//
// Created by Mark Mullin on 5/18/18.
//
#include "ImageMetadata.h"

#define MEMORYBASED 0
void ImageMetadata::addExifString(Exiv2::ExifData& exifData,const char* key,const char* data)
{
    // Create a ASCII string value (note the use of create)
    Exiv2::Value::AutoPtr v = Exiv2::Value::create(Exiv2::asciiString);
    // Set the value to a string
    v->read(data);
    Exiv2::ExifKey xkey(key);
    exifData.add(xkey, v.get());
    v.release();
}
std::string ImageMetadata::readExifString(Exiv2::ExifData& exifData,const char* key)
{
    Exiv2::Exifdatum& tag = exifData[key];
    std::string data = tag.toString();
    return data;
}
long ImageMetadata::readExifInt(Exiv2::ExifData& exifData,const char* key)
{
    Exiv2::Exifdatum& tag = exifData[key];
    long data = tag.toLong();
    return data;
}
void ImageMetadata::ReadExif(uint8_t* imageBuffer,uint32_t& bufferLength)
{
    // this is the first insertion of exif data

    // set the host computer identifier
    char pname[128];
    sprintf(pname,"./rectin.jpg");
#if MEMORYBASED
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open((const Exiv2::byte*)imageBuffer, bufferlength);
#else
    FILE * file = fopen(pname, "wb");
    fwrite(imageBuffer, bufferLength, 1, file);
    fclose(file);
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(pname);
#endif
   // assert(image.get() != 0);
    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        std::cout << "NO EXIF DATA " << m_source << std::endl;
        return;
    }

    m_source = readExifString(exifData,"Exif.Image.HostComputer");
    m_datetime = readExifString(exifData,"Exif.Image.DateTimeOriginal");
    m_millis = readExifString(exifData,"Exif.Photo.SubSecTimeOriginal");
    m_shotcounter = readExifInt(exifData,"Exif.Image.ImageNumber");
    m_pose = readExifString(exifData,"Exif.Photo.UserComment");

    //image->io().close();
}
void ImageMetadata::InjectExif(uint8_t* imageBuffer,uint32_t& bufferLength)
{
    Exiv2::ExifData exifData;
    char fname[128];
    //TODO Need to get temp directory dynamically
    sprintf(fname,"./rectout.jpg");
#if MEMORYBASED
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open((const Exiv2::byte*)imageBuffer, bufferlength);
#else
    FILE * file = fopen(fname, "wb");
    fwrite(imageBuffer, bufferLength, 1, file);
    fclose(file);
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(fname);
    if(image.get() == 0)
    {
        std::cout << "BAD IMAGE" << std::endl;
        return;
    }
#endif
    addExifString(exifData,"Exif.Image.HostComputer","fabar");
    addExifString(exifData,"Exif.Image.DateTimeOriginal",m_datetime.c_str());
    addExifString(exifData,"Exif.Photo.SubSecTimeOriginal",m_millis.c_str());
    exifData["Exif.Image.ImageNumber"] = int32_t(m_shotcounter);
    addExifString(exifData,"Exif.Photo.UserComment",m_pose.c_str());
    addExifString(exifData,"Exif.Image.ImageID",m_id.c_str());
    addExifString(exifData,"Exif.Image.Artist",m_channel.c_str());
    image->setExifData(exifData);
    image->writeMetadata();
    image.release();


#if MEMORYBASED
    // copy the library buffer to buff
    int outputBufferSize = image->io().size();
    image->io().seek(0,Exiv2::BasicIo::beg);
    Exiv2::DataBuf buff = image->io().read(outputBufferSize);
    memccpy(imageBuffer,buff.pData_,outputBufferSize,1);
    fprintf(stderr,"original = %d, with exif = %d\n",bufferlength,outputBufferSize);
    bufferlength = outputBufferSize;
#else
    std::ifstream infile(fname);
    infile.seekg(0, infile.end);
    size_t length = infile.tellg();
    infile.seekg(0, infile.beg);
    infile.read((char*) imageBuffer, length);
    bufferLength = length;
#endif
}

