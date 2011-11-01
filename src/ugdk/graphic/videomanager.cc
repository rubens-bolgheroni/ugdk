#include <SDL/SDL_opengl.h>
#include <cmath>
#include <ugdk/graphic/videomanager.h>
#include <ugdk/util/pathmanager.h>
#include <ugdk/base/engine.h>
#include <ugdk/graphic/image.h>
#include <ugdk/action/scene.h>
#include <ugdk/action/layer.h>

namespace ugdk {

static Vector2D default_resolution(800.0f, 600.0f);

// Inicializa o gerenciador de video, definindo uma
// resolucao para o programa. Retorna true em caso de
// sucesso.
bool VideoManager::Initialize(const string& title, const Vector2D& size,
                              bool fullscreen, const string& icon) {
	if(ChangeResolution(size, fullscreen) == false)
        ChangeResolution(default_resolution, false);

	if(icon.length() > 0)
		SDL_WM_SetIcon(SDL_LoadBMP(icon.c_str()), NULL);

    // Set window title.
    SDL_WM_SetCaption(title.c_str(), NULL);
    title_ = title;

    /*GLenum err = glewInit();
    if (GLEW_OK != err) {
        // TODO: check errors with glew
    }*/
    
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    blank_image_ = new Image;
    blank_image_->set_frame_size(Vector2D(50.0f, 50.0f));
    blank_image_->set_color(Image::CreateColor(0.0f, 1.0f, 0.0f));

    /*if(GLEW_ARB_framebuffer_object) {
        glGenFramebuffersEXT(1, &light_buffer_id_);
    }*/
    return true;
}

// Changes the resolution to the requested value.
// Returns true on success.
bool VideoManager::ChangeResolution(const Vector2D& size, bool fullscreen) {
    Uint32 flags = SDL_OPENGL;
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    if(fullscreen)
        flags |= SDL_FULLSCREEN;
    if(SDL_SetVideoMode(static_cast<int>(size.x), static_cast<int>(size.y),
            VideoManager::COLOR_DEPTH, flags) == NULL)
        return false;

    //Set projection
	glViewport(0, 0, (GLsizei) size.x, (GLsizei) size.y);
    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();
    glOrtho( 0, size.x, size.y, 0, -1, 1 );

    //Initialize modelview matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //If there was any errors
    if( glGetError() != GL_NO_ERROR )
        return false;

    video_size_ = size;
    fullscreen_ = fullscreen;
    virtual_bounds_ = Frame(0, 0, video_size_.x, video_size_.y);

    // Changing to and from fullscreen destroys all textures, so we must recreate them.
	InitializeLight();
    return true;
}

// Termina o gerenciador de video, retornando true em
// caso de sucesso.
bool VideoManager::Release() {
    for(map<string,Image*>::iterator it = image_memory_.begin();
            it != image_memory_.end(); ++it) {
        Image* img = it->second;
        delete img;
    }
    image_memory_.clear();
    /*if(GLEW_ARB_framebuffer_object) {
        glDeleteFramebuffersEXT(1, &light_buffer_id_);
    }*/
    return true;
}

void VideoManager::TranslateTo(Vector2D& offset) {
    glLoadIdentity();
	// Smaller values causes floating point errors and don't increase the image quality.
	glTranslatef(floor(offset.x), floor(offset.y), 0);
    this->virtual_bounds_ = Frame(-offset.x, -offset.y,
                                  -offset.x+video_size_.x,
                                  -offset.y+video_size_.y);
}

void VideoManager::MergeLights(std::vector<Scene*> scene_list) {
    // Lights are simply added together.
    glBlendFunc(GL_ONE, GL_ONE);

    glPushAttrib(GL_COLOR_BUFFER_BIT | GL_PIXEL_MODE_BIT); // for GL_DRAW_BUFFER and GL_READ_BUFFER
    glDrawBuffer(GL_BACK);
    glReadBuffer(GL_BACK);

    for (int i = 0; i < static_cast<int>(scene_list.size()); i++)
        if (!scene_list[i]->finished())
           scene_list[i]->RenderLight();

    // copy the framebuffer pixels to a texture
    glBindTexture(GL_TEXTURE_2D, light_texture_);
    glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, (GLsizei) video_size_.x, (GLsizei) video_size_.y);
    glBindTexture(GL_TEXTURE_2D, 0);

    glPopAttrib(); // GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT

    // Clear the screen so it's back to how it was before.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

static void DrawLightRect() {
    glEnable(GL_BLEND);
	glBegin( GL_QUADS ); //Start quad
        //Draw square
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(  0.0f, 0.0f );

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(  1.0f, 0.0f );

        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(  1.0f, 1.0f );

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(  0.0f, 1.0f );
    glEnd();
	glDisable(GL_BLEND);
}

void VideoManager::BlendLightIntoBuffer() {
    // BIND DA LIGHT TEXTURE. IT'S SO AWESOME
    glBindTexture(GL_TEXTURE_2D, light_texture_);

    glPushMatrix();
    glLoadIdentity();
    glScalef(video_size_.x, video_size_.y, 1);

    // BLEND FUNC FOR BLENDING THE LIGHT WITH DA SCREEN

    // TODO: check why the hell when using 
    //    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Sometimes a light sets the entire scene to that color.

    glBlendFunc(GL_ZERO, GL_SRC_COLOR);
    DrawLightRect();

    glPopMatrix();
}

// Desenha backbuffer na tela
void VideoManager::Render(std::vector<Scene*> scene_list, std::list<Layer*> interface_list) {

    // Draw all lights to a buffer, merging then to a light texture.
    MergeLights(scene_list);

    // Usual blend function for drawing RGBA images.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Draw all the sprites from all scenes.
    for (int i = 0; i < static_cast<int>(scene_list.size()); i++)
        if (!scene_list[i]->finished())
            scene_list[i]->Render();

    // Using the light texture, merge it into the screen.
    BlendLightIntoBuffer();

    // Draw all interface layers, with the usual RGBA blend.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (std::list<Layer*>::iterator it = interface_list.begin(); it != interface_list.end(); ++it)
        (*it)->Render();


    // Swap the buffers to show the backbuffer to the user.
    SDL_GL_SwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

// Carrega imagem de um arquivo, fazendo o
// gerenciamento de memoria. Retorna NULL
// em caso de falha.
Image* VideoManager::LoadImageFile(const string& filepath) {
    if(image_memory_.count(filepath) == 0) {
    	std::string fullpath = PATH_MANAGER()->ResolvePath(filepath);
		Image* img = new Image();
		if(img == NULL)
			return NULL;
		if(!img->LoadFromFile(fullpath)) {
			delete img;
			return NULL;
		}
        image_memory_[filepath] = img;
    }
    return image_memory_[filepath];
}

void VideoManager::InitializeLight() {
	light_size_ = Vector2D(32.0f, 32.0f);
	if(light_image_ != NULL) {
		delete light_image_;
	}
    light_image_ = new Image;
    light_image_->CreateFogTransparency(light_size_ * 2.0f, light_size_);


    if(light_texture_ != 0) {
        glDeleteTextures(1, &light_texture_);
        light_texture_ = 0;
    }
    glGenTextures(1, &light_texture_);
    glBindTexture(GL_TEXTURE_2D, light_texture_);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, (GLsizei) video_size_.x, 
        (GLsizei) video_size_.y, 0, GL_BGRA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

}  // namespace framework
