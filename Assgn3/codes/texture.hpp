#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_
GLuint LoadTexture( std::vector<const char*> filenames, int width, int height );
void FreeTexture( GLuint texture );

GLuint LoadTexture2( const char * filename, int width, int height );
void FreeTexture2( GLuint texture );
#endif 
