#ifndef ASEFILELOADER_H
#define ASEFILELOADER_H

#include <zlib.h>
#include <string>
#include "asefile.h"

using namespace std;

class AseFileLoaderException : public exception
{
public:
    AseFileLoaderException(const string& message) { m_message = message; }
    virtual const char* what() const throw() { return m_message.c_str(); }
    virtual ~AseFileLoaderException() {}
private:
    string m_message;
};

class AseFileLoader
{
public:
    AseFileLoader();

    AseFile* load(const string& file_path);

private:
    AseHeader get_header(FILE* file) const;
    AseFrame get_next_frame(FILE* file, AseColorDepth color_depth) const;
    AseChunk get_next_chunk(FILE* file, AseColorDepth color_depth) const;

    AseColorProfileChunk get_color_profile_chunk(FILE* file) const;
    AsePaletteChunk get_palette_chunk(FILE* file) const;
    AseOldPaletteChunk get_old_palette_chunk(FILE* file) const;
    AseLayerChunk get_layer_chunk(FILE* file) const;
    AseTagChunk get_tag_chunk(FILE* file) const;
    AseCelChunk get_cel_chunk(FILE* file, AseColorDepth color_depth) const;
    AseCelRaw get_cel_raw(FILE* file, AseColorDepth color_depth) const;
    AseCelLinked get_cel_linked(FILE* file) const;
    AseCelRaw get_cel_compressed(FILE* file, AseColorDepth color_depth) const;
};

#endif // ASEFILELOADER_H
