#include "texture.h"

#include <cstdio>

Texture::Texture(){id = 0;}
Texture::Texture(const char* img_path){
    name = (char *)malloc(strlen(img_path) + 1);
    memcpy(name, img_path, strlen(img_path) + 1);
}
void Texture::Load(const char* img_path){
    name = (char *)malloc(strlen(img_path) + 1);
    memcpy(name, img_path, strlen(img_path) + 1);
    this->Load();
}
void Texture::Load(){
    FILE* my_log=fopen("log.txt","a");
    int width, height, nrChannels;
    unsigned char *data = stbi_load(name, &width, &height, &nrChannels, 0);
    fprintf(my_log, "%s\n", name);
    fprintf(my_log, "width: %d, height: %d, nrChannels: %d\n", width, height, nrChannels);
    if (data)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &id);
        fprintf(my_log, "id: %d\n", id);
        glBindTexture(GL_TEXTURE_2D, id);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        // 加载并生成纹理
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
        // glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        fprintf(my_log,"Failed to load texture\n");
        id = 0;
    }
    stbi_image_free(data);
}

void Texture::Activate(){
    glBindTexture(GL_TEXTURE_2D, id);
}