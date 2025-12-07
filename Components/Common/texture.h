#pragma once
#include "utils.h"
#include "image.h"
#include <memory>
#include <string>
#include <vector>

namespace Hub
{
    namespace Format
    {
        enum format_t
        {
            Red   = GL_RED,
            RGB   = GL_RGB,
            BGR   = GL_BGR,
            RGBA  = GL_RGBA,
            BGRA  = GL_BGRA,
            DEPTH = GL_DEPTH_COMPONENT,
        };
    }

    // Wrapping types
    namespace Wrapping
    {
        enum wrapping_t
        {
            ClampEdge      = GL_CLAMP_TO_EDGE,
            ClampBorder    = GL_CLAMP_TO_BORDER,
            Repeat         = GL_REPEAT,
            MirroredRepeat = GL_MIRRORED_REPEAT
        };

        enum axis_t
        {
            S = GL_TEXTURE_WRAP_S,
            T = GL_TEXTURE_WRAP_T,
            R = GL_TEXTURE_WRAP_R,
        };
    } // namespace Wrapping

    // Filter types
    namespace Filter
    {
        enum filter_t
        {
            Nearest              = GL_NEAREST,
            Linear               = GL_LINEAR,
            NearestMipmapNearest = GL_NEAREST_MIPMAP_NEAREST,
            LinearMipmapNearest  = GL_LINEAR_MIPMAP_NEAREST,
            NearestMipmapLinear  = GL_NEAREST_MIPMAP_LINEAR,
            LinearMipmapLinear   = GL_LINEAR_MIPMAP_LINEAR
        };

        enum operator_t
        {
            Mag = GL_TEXTURE_MAG_FILTER,
            Min = GL_TEXTURE_MIN_FILTER,
        };
    } // namespace Filter

    enum texture_t
    {
        Texture2D      = GL_TEXTURE_2D,
        TextureCubeMap = GL_TEXTURE_CUBE_MAP,

    };

    class Texture;
    using SPTexture = std::shared_ptr<Texture>;

    class Texture
    {
    public:
        ~Texture();
        operator GLuint() const;

        static SPTexture create();
        static SPTexture create(const SPImage image);
        static SPTexture create(const char* filePath);
        static SPTexture create(texture_t type);

        void setWrapping(Wrapping::axis_t axis, Wrapping::wrapping_t wrapping);
        void setFilter(Filter::operator_t op, Filter::filter_t flt);
        void setBorderColor(const Color& color);
        void image2D(const void* data, Format::format_t format, int width, int height, Type::type_t dataType);
        void generateMipMap();

        void cubeMapImage2D(const std::vector<std::string>& faces);
        void cubeMapImage2D(int width, int height);
        void image2DMultisample(int width, int height);

    private:
        texture_t _textureType;
        Texture(texture_t type);
        Texture(const SPImage image);
        Format::format_t getDefaultFormat(int channelCount = 4);
        GLuint           _obj;
    };
} // namespace Hub