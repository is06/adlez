#ifndef ASEFILE_H
#define ASEFILE_H

#include <string>
#include <vector>

using namespace std;

typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

enum class AseChunkType : WORD
{
    none = 0x0000,
    old_palette_0 = 0x0004,
    old_palette_1 = 0x0011,
    layer = 0x2004,
    cel = 0x2005,
    cel_extra = 0x2006,
    color_profile = 0x2007,
    mask = 0x2016,
    path = 0x2017,
    tags = 0x2018,
    palette = 0x2019,
    user_data = 0x2020,
    slice = 0x2022,
};

enum class AseColorDepth : WORD
{
    rgba = 32,
    grayscale = 16,
    indexed = 8,
};

enum class AseColorProfileType : WORD
{
    none = 0,
    srgb = 1,
    embedded_icc = 2,
};

enum class AseLoopAnimationDirection : BYTE
{
    forward = 0,
    reverse = 1,
    ping_pong = 2,
};

enum class AseLayerFlags : WORD
{
    visible = 1,
    editable = 2,
    lock_movement = 4,
    background = 8,
    prefer_linked_cels = 16,
    layer_group_display_collapsed = 32,
    is_reference_layer = 64,
};

enum class AseLayerType : WORD
{
    normal = 0,
    group = 1,
};

enum class AseCelType : WORD
{
    raw = 0,
    linked = 1,
    compressed = 2,
};

struct AseString
{
    WORD length;
    string characters;
};

struct AseChunkData {};

struct AseColorProfileChunk : public AseChunkData
{
    AseColorProfileType type = AseColorProfileType::none;
    WORD flags = 0;
    WORD gamma_integer = 0;
    WORD gamma_fraction = 0;
    BYTE reserved[8];
    DWORD icc_profile_data_length = 0;
    BYTE* icc_profile_data;
};

struct AseOldPaletteColor
{
    BYTE red;
    BYTE green;
    BYTE blue;
};

struct AseOldPalettePacket
{
    BYTE entry_count_to_skip;
    BYTE color_count;
    vector<AseOldPaletteColor> colors;
};

struct AseOldPaletteChunk : public AseChunkData
{
    WORD packet_count;
    vector<AseOldPalettePacket> packets;
};

struct AsePaletteEntry
{
    WORD flags;
    BYTE red;
    BYTE green;
    BYTE blue;
    BYTE alpha;
    AseString name;
};

struct AsePaletteChunk : public AseChunkData
{
    DWORD entry_count;
    DWORD first_color_index;
    DWORD last_color_index;
    BYTE unused[8];
    vector<AsePaletteEntry> entries;
};

struct AseLayerChunk : public AseChunkData
{
    AseLayerFlags flags;
    AseLayerType type;
    WORD child_level;
    WORD default_width;
    WORD default_height;
    WORD blend_mode;
    BYTE opacity;
    BYTE unused[3];
    AseString name;
};

struct AseTag
{
    WORD from_frame = 0;
    WORD to_frame = 0;
    AseLoopAnimationDirection animation_direction = AseLoopAnimationDirection::forward;
    BYTE unused[8];
    BYTE color[3];
    BYTE extra = 0;
    AseString name;
};

struct AseTagChunk : public AseChunkData
{
    WORD count = 0;
    BYTE unused[8];
    vector<AseTag> tags;
};

struct AsePixel {};

struct AsePixelRGBA : AsePixel
{
    BYTE data[4];
};

struct AsePixelGrayscale : AsePixel
{
    BYTE data[2];
};

struct AsePixelIndexed : AsePixel
{
    BYTE index;
};

struct AseCel {};

struct AseCelRaw : AseCel
{
    WORD width;
    WORD height;
    vector<AsePixel> pixels;
};

struct AseCelLinked : AseCel
{
    WORD frame_position;
};

struct AseCelChunk : public AseChunkData
{
    WORD layer_index;
    short x;
    short y;
    BYTE opacity;
    AseCelType type;
    BYTE unused[7];
    AseCel cel;
};

struct AseChunk
{
    DWORD size = 0;
    AseChunkType type = AseChunkType::none;
    AseChunkData data;
};

struct AseFrameHeader
{
    DWORD byte_count = 0;
    WORD magic_number = 0;
    WORD old_chunk_count = 0;
    WORD frame_duration = 0;
    BYTE unused[2];
    DWORD chunk_count = 0;
};

struct AseFrame
{
    AseFrameHeader header;
    vector<AseChunk> chunks;
};

struct AseHeader
{
    DWORD file_size = 0;
    WORD magic_number = 0;
    WORD frame_count = 0;
    WORD width = 0;
    WORD height = 0;
    AseColorDepth color_depth;
    DWORD flags = 0;
    WORD speed = 0;
    WORD unused_0 = 0;
    WORD unused_1 = 0;
    BYTE palette_entry = 0;
    BYTE unused_2[3];
    WORD color_count = 0;
    BYTE pixel_width = 0;
    BYTE pixel_height = 0;
    short grid_position_x = 0;
    short grid_position_y = 0;
    WORD grid_width = 0;
    WORD grid_height = 0;
    BYTE unused_3[84];
};

struct AseFile
{
    AseHeader header;
    vector<AseFrame> frames;
};

#endif // ASEFILE_H
