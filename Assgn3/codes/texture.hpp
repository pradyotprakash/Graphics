#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_
GLuint LoadTexture( std::vector<const char*> filenames, int width, int height );
void FreeTexture( GLuint texture );
#endif 
