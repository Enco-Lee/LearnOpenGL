#include "image.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION // must: only contains the relevant definition source code
#include "stb/stb_image.h"       // popular single header image loading library
#endif

#include <iostream>

namespace Hub
{

    Image::Image(const char* filePath)
    {
        load(filePath);
    }

    Image::~Image()
    {
        stbi_image_free(_data);
    }

    Hub::SPImage Image::create()
    {
        return SPImage(new Image());
    }

    Hub::SPImage Image::create(const char* filePath)
    {
        return SPImage(new Image(filePath));
    }

    void Image::filpVerticallyOnLoadEnable(bool val)
    {
        stbi_set_flip_vertically_on_load(val);
    }

    void Image::load(const char* filePath)
    {
        _data = stbi_load(filePath, &_width, &_height, &_channels, 0);
        if (!_data)
        {
            std::cerr << "Image load failed: " << filePath << std::endl;
        }
    }

    int Image::getWidth() const
    {
        return _width;
    }

    int Image::getHeight() const
    {
        return _height;
    }

    const unsigned char* Image::getData() const
    {
        return _data;
    }

    int Image::getChannels() const
    {
        return _channels;
    }

} // namespace Hub