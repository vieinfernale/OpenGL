#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>                  // GLEW for OpenGL functions
#define STB_IMAGE_IMPLEMENTATION      // Compile stb_image
#include <stb_image/stb_image.h>      // Include stb_image for textures

#include <iostream>
#include <string>

unsigned int loadTexture (const std::string& imageFilePath) 
{
    unsigned int textureID;
    int width, height, nChannels;

    // Generate and Bind texture ID
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // S-axis Horizontal
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // T-axis Vertical
    // Minification: Texture is displayed smaller than its original size; involves sampling algorithms to determine texel colors
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    // Magnification: Texture is displayed larger than its original size; involves sampling algorithms to determine texel colors
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // GL_LINEAR produces a smoother pattern where the individual pixels are less visible.

    // Load the image using stb_image.h
    unsigned char* imageData = stbi_load(imageFilePath.c_str(), &width, &height, &nChannels, 0);

    // Process image
    if (imageData != NULL) {
        std::cout << width << height << nChannels << std::endl;
        // Check format
        unsigned int format = (nChannels == 4) ? GL_RGBA : GL_RGB;
        std::cout << format << " " << GL_RGB << std::endl;
        // Upload texture to OpenGL
        /* 2D Texture, 0 - normal 1,2... - small mipmaps, color RGB/RGBA, border=0, color = unsigned bytes, image data pointer */
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData); 
        // Generate Mipmaps: smaller images with lower resolutions
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load the image: " << imageFilePath << std::endl;
    }

    stbi_image_free(imageData);

    return textureID;
}

#endif