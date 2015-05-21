#ifndef IMAGE_IO__H
#define IMAGE_IO__H

unsigned char* lire_image(char* fichier, int* width, int* height, int* lumin);
void ecrire_image(char* fichier, unsigned char* image, int width, int height, int lumin);
#endif
