#include "textmanager.h"
#include "debug.h"

#include <ft2build.h>
#include FT_FREETYPE_H 

TextManager::TextManager(const std::string& fontfile)
    : _fontfile{fontfile}
{
    _init();
}

TextManager::~TextManager()
{
    _release();
}

TextManager::Character TextManager::character(char c) const
{
    auto it = _charmap.find(c);
    if (it == _charmap.end()) {
	return Character{};
    } else {
	return it->second;
    }
}    

void TextManager::_init()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
	// TODO: Error handling
	DEBUG_MSGERR("Freetype: could not init FreeType Library\n");
	return;
    }

    FT_Face face;
    if (FT_New_Face(ft, _fontfile.c_str(), 0, &face)) {
	//TODO: Error handling
	DEBUG_MSGERR("Freetype: failed to load font\n");
	return;
    }

    FT_Set_Pixel_Sizes(face, 0, 24);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    //Load only first 128 ASCII characters

    bool is_error{false};
    for (GLubyte c = 0; c < 128; ++c) {
	if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
	    // TODO: Error handling
	    DEBUG_MSGERR("Freetype: failed to load Glyph\n");
	    is_error = true;
	    break;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	CHECK_ERR();
	glBindTexture(GL_TEXTURE_2D, texture);
	if (glIsTexture(texture) != GL_TRUE) {
	    DEBUG_PRINT("Invalid texture id\nTexture id: %d\n", texture);
	    is_error = true;
	    break;	    
	}
	
	glTexImage2D(GL_TEXTURE_2D,
		     0,
		     GL_RED,
		     face->glyph->bitmap.width,
		     face->glyph->bitmap.rows,
		     0,
		     GL_RED,
		     GL_UNSIGNED_BYTE,
		     face->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Character character = {
	    texture, 
	    glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
	    glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
	    static_cast<GLuint>(face->glyph->advance.x)
	};

	_charmap[c] = character;
    }

    CHECK_ERR();    
    
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextManager::_release()
{
    for (const std::pair<GLchar, Character>& pair : _charmap) {
	if (glIsTexture(pair.second.texture_id) == GL_TRUE) {
	    glDeleteTextures(1, &pair.second.texture_id);
	}
    }
    CHECK_ERR();    
}
