#pragma once

#include <memory>

namespace Hub
{
    class Image;
    using SPImage = std::shared_ptr<Image>;

    class Image
    {
    public:
        ~Image();

        static SPImage create();
        static SPImage create(const char* filePath);
        static void    filpVerticallyOnLoadEnable(bool val);

        void                 load(const char* filePath);
        int                  getWidth() const;
        int                  getHeight() const;
        const unsigned char* getData() const;
        int                  getChannels() const;

    private:
        Image() = default;
        Image(const char* filePath);

        int            _width    = 0;
        int            _height   = 0;
        int            _channels = 4;
        unsigned char* _data     = nullptr;
    };
} // namespace Hub