#include"Texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
	// Generate texture ID and load texture data
	type = texType;
	int widthImg, heightImg, numColCh;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);
	if (bytes) {
		if (texType == GL_TEXTURE_2D) {
			glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
			glGenerateMipmap(texType);
		}
		else if (texType == GL_TEXTURE_CUBE_MAP) {
			for (GLuint i = 0; i < 6; i++) {
				glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
			}
		}
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(bytes);
	glBindTexture(texType, 0);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit) {
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	shader.Activate();
	glUniform1i(texUni, unit);
}

void Texture::Bind() {
	glBindTexture(type, ID);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &ID);
}