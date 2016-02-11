#pragma once

#include <memory>

#include <GL/glew.h>

#include <glm/glm.hpp>

#include <map>
#include <memory>
#include <string>

class TextManager {
public:
    struct Character {
	GLuint texture_id;
	glm::ivec2 size;       
	glm::ivec2 bearing;    
	GLuint advance;    
    };

    using CharacterMap = std::map<GLchar, Character>;

public:
    TextManager(const std::string& fontfile);

    ~TextManager();

    Character character(char c) const;

private:
    void _init();

    void _release();

private:
    std::string _fontfile;;
    CharacterMap _charmap;
};

using TextManagerPtr =std::unique_ptr<TextManager>;
