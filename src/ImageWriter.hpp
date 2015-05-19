#ifndef IIMAGEWRITER_H_
#define IIMAGEWRITER_H_

#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "Image.hpp"
#include "aliases.hpp"

class ImageWriter
{
public:
    ImageWriter( Image<RGB> _image);
    ~ImageWriter();
    void writeOnPPM( const std::string _imagepath );
    void setColorGamut( const int _colorGamut );
private:
    Image<RGB> image;
    int colorGamut;

};

#endif

