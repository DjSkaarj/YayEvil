#include "common.h"
#include "log.h"
#include "textures.h"
#include "strings.h"

GLuint GetTexture(std::string name)
{
	if (Textures.find(name) == Textures.end())
	{
		Log(0, "[GetTexture] [Warning] Texture %s wasn't found, empty texture will be returned.", name.c_str());
		return 0;
	}
	return Textures[name];
}

GLuint YE_LoadImage(const char *filename)
{
	SDL_Surface *image = IMG_Load(filename);
	if (image == NULL)
	{
		Log(0, "[YE_LoadImage] [Warning] Failed to load %s: %s", filename, SDL_GetError());
		return 0;
	}

	GLenum origformat;
	GLenum gpuformat;

	int bpp = image->format->BytesPerPixel;
	int rmask = image->format->Rmask;

	switch (bpp)
	{
	case 4:
		gpuformat = GL_RGBA8;

		if (rmask == 0x000000ff)
			origformat = GL_RGBA;
		else
			origformat = GL_BGRA;
		break;

	case 3:
		gpuformat = GL_RGBA8; // GPUs don't like 24-bit colors

		if (rmask == 0x000000ff)
			origformat = GL_RGB;
		else
			origformat = GL_BGR;
		break;

	case 1:
		gpuformat = GL_LUMINANCE8;
		origformat = GL_LUMINANCE;
		break;

	default:
		Log(0, "[YE_LoadImage] [Warning]  %s: unsupported image format", filename);
		SDL_FreeSurface(image);
		return 0;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexImage2D(GL_TEXTURE_2D, 0, gpuformat, image->w, image->h, 0, origformat, GL_UNSIGNED_BYTE, image->pixels);

	SDL_FreeSurface(image);
	return texture;
}

void YE_LoadTexturesDir(const char* dirpath)
{
	tinydir_dir dir;
	tinydir_file file;
	tinydir_open_sorted(&dir, dirpath);
	for (unsigned int i = 0; i < dir.n_files; i++)
	{
		tinydir_readfile_n(&dir, &file, i);
		if ((YE_EndsWith(file.name, "bmp") || YE_EndsWith(file.name, "png") || YE_EndsWith(file.name, "tiff") || YE_EndsWith(file.name, "jpeg")) && !file.is_dir)
		{
			char path[255];
			strcpy(path, dirpath);
			strcat(path, file.name);
			GLuint texbuffer = YE_LoadImage(path);

			if (texbuffer != 0)
			{
				char loadtex[255];
				strcpy(loadtex, file.name);
				YE_StrToLower(loadtex);
				std::string s = loadtex;
				s.erase(s.end() - 4, s.end());

				Textures.insert(std::pair<std::string, GLuint>(s, texbuffer));
				if (YE_LogTex)
					Log(0, "[Texture loader] Loaded texture %s", file.name);
			}
		}
	}
	tinydir_close(&dir);
}

void YE_LoadTextures(void)
{
	Log(0, "[Texture loader] Loading textures...");
	YE_LoadTexturesDir("textures/");
	Log(0, "[Texture loader] Finished loading textures!");

	Log(0, "[Texture loader] Loading sprites...");
	YE_LoadTexturesDir("textures/sprites/");
	Log(0, "[Texture loader] Finished loading sprites!");
}