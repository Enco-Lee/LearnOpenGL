#include "texture.h"

namespace Hub
{
    Texture::~Texture()
    {
        glDeleteTextures(1, &_obj);
    }

    Texture::operator GLuint() const
    {
        return _obj;
    }

    Hub::SPTexture Texture::create()
    {
        return SPTexture(new Texture(Hub::texture_t::Texture2D));
    }

    SPTexture Texture::create(const SPImage image)
    {
        return SPTexture(new Texture(image));
    }

    Hub::SPTexture Texture::create(const char* filePath)
    {
        auto image = Image::create(filePath);
        return SPTexture(new Texture(image));
    }

    SPTexture Texture::create(texture_t type)
    {
        return SPTexture(new Texture(type));
    }

    void Texture::setWrapping(Wrapping::axis_t axis, Wrapping::wrapping_t wrapping)
    {
        glBindTexture(_textureType, _obj);
        glTexParameteri(_textureType, axis, wrapping);
        glBindTexture(_textureType, 0);
    }

    void Texture::setFilter(Filter::operator_t op, Filter::filter_t flt)
    {
        glBindTexture(_textureType, _obj);
        glTexParameteri(_textureType, op, flt);
        glBindTexture(_textureType, 0);
    }

    void Texture::setBorderColor(const Color& color)
    {
        glBindTexture(GL_TEXTURE_2D, _obj);
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color_ptr(color));
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::image2D(const void* data, Format::format_t format, int width, int height, Type::type_t dataType)
    {
        glBindTexture(GL_TEXTURE_2D, _obj);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, dataType, data);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::generateMipMap()
    {
        glBindTexture(GL_TEXTURE_2D, _obj);
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::cubeMapImage2D(const std::vector<std::string>& faces)
    {
        assert(faces.size() == 6);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _obj);
        for (size_t i = 0; i < faces.size(); ++i)
        {
            const auto&      filePath = faces[i];
            auto             image    = Image::create(filePath.c_str());
            Format::format_t format   = getDefaultFormat(image->getChannels());
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0,
                         format,
                         image->getWidth(),
                         image->getHeight(),
                         0,
                         format,
                         Type::UnsignedByte,
                         image->getData());
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void Texture::cubeMapImage2D(int width, int height)
    {
        glBindTexture(GL_TEXTURE_CUBE_MAP, _obj);
        for (size_t i = 0; i < 6; ++i)
        {

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0,
                         Format::format_t::DEPTH,
                         width,
                         height,
                         0,
                         Format::format_t::DEPTH,
                         Type::UnsignedByte,
                         nullptr);
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }

    void Texture::image2DMultisample(int width, int height)
    {
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _obj);
        glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, width, height, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    }

    Texture::Texture(texture_t type = Texture2D) : _textureType(type)
    {
        glGenTextures(1, &_obj);
    }

    Texture::Texture(const SPImage image) : Texture()
    {
        Format::format_t format = getDefaultFormat(image->getChannels());
        image2D(image->getData(), format, image->getWidth(), image->getHeight(), Type::UnsignedByte);
        generateMipMap();
    }

    Format::format_t Texture::getDefaultFormat(int channelCount)
    {
        switch (channelCount)
        {
            case 1:
                return Format::Red;
                break;
            case 3:
                return Format::RGB;
                break;
            case 4:
                return Format::RGBA;
                break;
        }
        return Format::RGBA;
    }

} // namespace Hub