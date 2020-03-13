#pragma once

#ifdef USE_GLEW
#include <GL/glew.h>
#else
#include <epoxy/gl.h>
#endif

namespace celestia
{
namespace gl
{

constexpr const int GL_2_1 = 21;

extern bool ARB_shader_texture_lod;
extern bool ARB_vertex_array_object;
extern bool EXT_framebuffer_object;
extern bool EXT_texture_compression_s3tc;
extern bool EXT_texture_filter_anisotropic;

bool init() noexcept;
bool checkVersion(int) noexcept;
} // gl
} // celestia
