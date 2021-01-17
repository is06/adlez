#include <stdio.h>
#include <iostream>
#include <zlib.h>
#include "asefile.h"
#include "asefileloader.h"

using namespace std;

AseFileLoader::AseFileLoader()
{

}

AseFile* AseFileLoader::load(const string& file_path)
{
    FILE* file = fopen(("./content/" + file_path + ".ase").c_str(), "rb");
    if (file == NULL) {
        cerr << "Unable to open aseprite file '" << ("./content/" + file_path + ".ase") << "'" << endl;
        return nullptr;
    }

    AseFile* asefile = new AseFile();
    asefile->header = get_header(file);

    for (WORD frame_index = 0; frame_index < asefile->header.frame_count; frame_index++) {
        asefile->frames.push_back(get_next_frame(file, asefile->header.color_depth));
    }

    fclose(file);

    return asefile;
}

AseHeader AseFileLoader::get_header(FILE* file) const
{
    AseHeader header;
    fread(&header, sizeof(header), 1, file);
    return header;
}

AseFrame AseFileLoader::get_next_frame(FILE* file, AseColorDepth color_depth) const
{
    auto frame = AseFrame();

    // Frame header
    AseFrameHeader frame_header;
    fread(&frame_header, sizeof(frame_header), 1, file);
    frame.header = frame_header;

    // Chunks
    for (DWORD chunk_index = 0; chunk_index < frame.header.chunk_count; chunk_index++) {
        frame.chunks.push_back(get_next_chunk(file, color_depth));
    }

    return frame;
}

AseChunk AseFileLoader::get_next_chunk(FILE* file, AseColorDepth color_depth) const
{
    AseChunk chunk;
    fread(&chunk.size, sizeof(chunk.size), 1, file);
    fread(&chunk.type, sizeof(chunk.type), 1, file);
    chunk.data = AseChunkData();

    switch (chunk.type) {
    case AseChunkType::color_profile:
        chunk.data = get_color_profile_chunk(file);
        break;
    case AseChunkType::palette:
        chunk.data = get_palette_chunk(file);
        break;
    case AseChunkType::old_palette_0:
        chunk.data = get_old_palette_chunk(file);
        break;
    case AseChunkType::layer:
        chunk.data = get_layer_chunk(file);
        break;
    case AseChunkType::tags:
        chunk.data = get_tag_chunk(file);
        break;
    case AseChunkType::cel:
        chunk.data = get_cel_chunk(file, color_depth);
        break;
    default:
        throw AseFileLoaderException("Unhandled chunk type");
        break;
    }

    return chunk;
}

AseColorProfileChunk AseFileLoader::get_color_profile_chunk(FILE* file) const
{
    auto chunk = AseColorProfileChunk();
    fread(&chunk.type, sizeof(chunk.type), 1, file);
    fread(&chunk.flags, sizeof(chunk.flags), 1, file);
    fread(&chunk.gamma_integer, sizeof(chunk.gamma_integer), 1, file);
    fread(&chunk.gamma_fraction, sizeof(chunk.gamma_fraction), 1, file);
    fread(&chunk.reserved, sizeof(chunk.reserved), 1, file);

    if (chunk.type == AseColorProfileType::embedded_icc) {
        fread(&chunk.icc_profile_data_length, sizeof(chunk.icc_profile_data_length), 1, file);
        chunk.icc_profile_data = new BYTE[chunk.icc_profile_data_length];
        fread(chunk.icc_profile_data, sizeof(BYTE), chunk.icc_profile_data_length, file);
    }

    return chunk;
}

AsePaletteChunk AseFileLoader::get_palette_chunk(FILE* file) const
{
    auto chunk = AsePaletteChunk();
    fread(&chunk.entry_count, sizeof(chunk.entry_count), 1, file);
    fread(&chunk.first_color_index, sizeof(chunk.first_color_index), 1, file);
    fread(&chunk.last_color_index, sizeof(chunk.last_color_index), 1, file);
    fread(&chunk.unused, sizeof(chunk.unused), 1, file);

    for (DWORD i = 0; i < chunk.entry_count; i++) {
        auto entry = AsePaletteEntry();
        fread(&entry.flags, sizeof(entry.flags), 1, file);
        fread(&entry.red, sizeof(entry.red), 1, file);
        fread(&entry.green, sizeof(entry.green), 1, file);
        fread(&entry.blue, sizeof(entry.blue), 1, file);
        fread(&entry.alpha, sizeof(entry.alpha), 1, file);

        if (entry.flags == 1) {
            AseString name;
            fread(&name.length, sizeof(name.length), 1, file);

            for (int s = 0; s < name.length; s++) {
                char c = '\0';
                fread(&c, sizeof(char), 1, file);
                name.characters += c;
            }
            entry.name = name;
        }

        chunk.entries.push_back(entry);
    }

    return chunk;
}

AseOldPaletteChunk AseFileLoader::get_old_palette_chunk(FILE* file) const
{
    auto chunk = AseOldPaletteChunk();
    fread(&chunk.packet_count, sizeof(chunk.packet_count), 1, file);

    for (WORD p = 0; p < chunk.packet_count; p++) {
        auto packet = AseOldPalettePacket();
        fread(&packet.entry_count_to_skip, sizeof(packet.entry_count_to_skip), 1, file);
        fread(&packet.color_count, sizeof(packet.color_count), 1, file);

        int color_count = packet.color_count;
        if (color_count == 0) {
            color_count = 256;
        }
        for (BYTE c = 0; c < color_count; c++) {
            auto color = AseOldPaletteColor();
            fread(&color.red, sizeof(color.red), 1, file);
            fread(&color.green, sizeof(color.green), 1, file);
            fread(&color.blue, sizeof(color.blue), 1, file);
            packet.colors.push_back(color);
        }

        chunk.packets.push_back(packet);
    }

    return chunk;
}

AseLayerChunk AseFileLoader::get_layer_chunk(FILE* file) const
{
    auto chunk = AseLayerChunk();
    fread(&chunk.flags, sizeof(chunk.flags), 1, file);
    fread(&chunk.type, sizeof(chunk.type), 1, file);
    fread(&chunk.child_level, sizeof(chunk.child_level), 1, file);
    fread(&chunk.default_width, sizeof(chunk.default_width), 1, file);
    fread(&chunk.default_height, sizeof(chunk.default_height), 1, file);
    fread(&chunk.blend_mode, sizeof(chunk.blend_mode), 1, file);
    fread(&chunk.opacity, sizeof(chunk.opacity), 1, file);
    fread(&chunk.unused, sizeof(chunk.unused), 1, file);

    AseString name;
    fread(&name.length, sizeof(name.length), 1, file);

    for (int s = 0; s < name.length; s++) {
        char c = '\0';
        fread(&c, sizeof(char), 1, file);
        name.characters += c;
    }
    chunk.name = name;

    return chunk;
}

AseTagChunk AseFileLoader::get_tag_chunk(FILE* file) const
{
    auto chunk = AseTagChunk();

    fread(&chunk.count, sizeof(chunk.count), 1, file);
    fread(&chunk.unused, sizeof(chunk.unused), 1, file);

    for (int i = 0; i < chunk.count; i++) {
        auto tag = AseTag();
        fread(&tag.from_frame, sizeof(tag.from_frame), 1, file);
        fread(&tag.to_frame, sizeof(tag.to_frame), 1, file);
        fread(&tag.animation_direction, sizeof(tag.animation_direction), 1, file);
        fread(&tag.unused, sizeof(tag.unused), 1, file);
        fread(&tag.color, sizeof(tag.color), 1, file);
        fread(&tag.extra, sizeof(tag.extra), 1, file);

        AseString name;
        fread(&name.length, sizeof(name.length), 1, file);

        for (int s = 0; s < name.length; s++) {
            char c = '\0';
            fread(&c, sizeof(char), 1, file);
            name.characters += c;
        }
        tag.name = name;

        chunk.tags.push_back(tag);
    }

    return chunk;
}

AseCelChunk AseFileLoader::get_cel_chunk(FILE* file, AseColorDepth color_depth) const
{
    auto chunk = AseCelChunk();
    fread(&chunk.layer_index, sizeof(chunk.layer_index), 1, file);
    fread(&chunk.x, sizeof(chunk.x), 1, file);
    fread(&chunk.y, sizeof(chunk.y), 1, file);
    fread(&chunk.opacity, sizeof(chunk.opacity), 1, file);
    fread(&chunk.type, sizeof(chunk.type), 1, file);
    fread(chunk.unused, sizeof(BYTE), 7, file);

    switch (chunk.type) {
    case AseCelType::raw:
        chunk.cel = get_cel_raw(file, color_depth);
        break;
    case AseCelType::linked:
        chunk.cel = get_cel_linked(file);
        break;
    case AseCelType::compressed:
        chunk.cel = get_cel_compressed(file, color_depth);
        break;
    }

    return chunk;
}

AseCelRaw AseFileLoader::get_cel_raw(FILE* file, AseColorDepth color_depth) const
{
    auto cel = AseCelRaw();
    fread(&cel.width, sizeof(cel.width), 1, file);
    fread(&cel.height, sizeof(cel.height), 1, file);

    switch (color_depth) {
    case AseColorDepth::rgba:
    {
        DWORD pixel_count = cel.width * cel.height;
        for (DWORD i = 0; i < pixel_count; i++) {
            auto pixel = AsePixelRGBA();
            fread(&pixel, sizeof(pixel), 1, file);
            cel.pixels.push_back(pixel);
        }
        break;
    }
    case AseColorDepth::grayscale:
    {
        DWORD pixel_count = cel.width * cel.height;
        for (DWORD i = 0; i < pixel_count; i++) {
            auto pixel = AsePixelGrayscale();
            fread(&pixel, sizeof(pixel), 1, file);
            cel.pixels.push_back(pixel);
        }
        break;
    }
    case AseColorDepth::indexed:
    {
        DWORD pixel_count = cel.width * cel.height;
        for (DWORD i = 0; i < pixel_count; i++) {
            auto pixel = AsePixelIndexed();
            fread(&pixel, sizeof(pixel), 1, file);
            cel.pixels.push_back(pixel);
        }
        break;
    }
    }

    return cel;
}

AseCelLinked AseFileLoader::get_cel_linked(FILE* file) const
{
    auto cel = AseCelLinked();
    fread(&cel.frame_position, sizeof(cel.frame_position), 1, file);
    return cel;
}

AseCelRaw AseFileLoader::get_cel_compressed(FILE* file, AseColorDepth color_depth) const
{
    auto cel = AseCelRaw();
    fread(&cel.width, sizeof(cel.width), 1, file);
    fread(&cel.height, sizeof(cel.height), 1, file);

    constexpr int chunk_size = 16384;

    int result;
    unsigned int uncompressed_length = 0;
    z_stream stream;
    unsigned char in[chunk_size];
    unsigned char out[chunk_size];

    // Allocate inflate state
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;
    stream.avail_in = 0;
    stream.next_in = Z_NULL;

    result = inflateInit(&stream);
    if (result != Z_OK) {
        throw AseFileLoaderException("Unable to init compressed data inflate");
    }

    // Decompress until stream ends or end of file
    do {
        // Read a 16K chunk from file
        stream.avail_in = fread(in, 1, chunk_size, file);
        if (ferror(file)) {
            (void)inflateEnd(&stream);
            throw AseFileLoaderException("File error on inflate");
        }
        if (stream.avail_in == 0) {
            break;
        }
        stream.next_in = in;

        do {
            stream.avail_out = chunk_size;
            stream.next_out = out;

            result = inflate(&stream, Z_NO_FLUSH);

            // Error handling
            if (result == Z_STREAM_ERROR) {
                throw AseFileLoaderException("Unable to inflate data: Stream error");
            }
            switch (result) {
            case Z_NEED_DICT:
                (void)inflateEnd(&stream);
                throw AseFileLoaderException("Unable to inflate data: Need dict");
                break;
            case Z_DATA_ERROR:
                (void)inflateEnd(&stream);
                throw AseFileLoaderException("Unable to inflate data: Data error");
                break;
            case Z_MEM_ERROR:
                (void)inflateEnd(&stream);
                throw AseFileLoaderException("Unable to inflate data: Memory error");
                break;
            }

            uncompressed_length = chunk_size - stream.avail_out;
        } while (stream.avail_out == 0);
    } while (result != Z_STREAM_END);

    (void)inflateEnd(&stream);

    if (uncompressed_length > 0) {
        // Feed the pixel data with inflate out data
        switch (color_depth) {
        case AseColorDepth::rgba:
        {
            for (DWORD i = 0; i < uncompressed_length; i += 4) {
                AsePixelRGBA pixel;
                pixel.data[0] = out[i];
                pixel.data[1] = out[i + 1];
                pixel.data[2] = out[i + 2];
                pixel.data[3] = out[i + 3];
                cel.pixels.push_back(pixel);
            }
            break;
        }
        case AseColorDepth::grayscale:
        {
            for (DWORD i = 0; i < uncompressed_length; i += 2) {
                AsePixelGrayscale pixel;
                pixel.data[0] = out[i];
                pixel.data[1] = out[i + 1];
                cel.pixels.push_back(pixel);
            }
            break;
        }
        case AseColorDepth::indexed:
        {
            for (DWORD i = 0; i < uncompressed_length; i ++) {
                AsePixelIndexed pixel;
                pixel.index = out[i];
                cel.pixels.push_back(pixel);
            }
            break;
        }
        }
    }

    return cel;
}
