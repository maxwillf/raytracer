
#include "include/film.hpp"
#include "include/lodepng.h"
#include <iostream>
#include <fstream>

template <>
std::vector<Factory<Film, Arguments>::ReadFunPtr> Factory<Film, Arguments>::registeredFuns = std::vector<Factory<Film, Arguments>::ReadFunPtr>();
DerivedRegistrar<Film, Film> ___initFilm;

void Film::writeToFile()
{
    std::ofstream fs(this->getFilename());
        int width = this->buffer[0].size();
        int height = this->buffer.size();
        if (this->getImgType() == "png")
        {
            std::vector<unsigned char> image;
            image.resize(width * height * 4);
            for (int i = 0; i < height; ++i)
{
            for (int j = 0; j < width; ++j)
            {
                image[4 * width * i + 4 * j + 0] = buffer[i][j][0];
                image[4 * width * i + 4 * j + 1] = buffer[i][j][1];
                image[4 * width * i + 4 * j + 2] = buffer[i][j][2];
                image[4 * width * i + 4 * j + 3] = 255;
            }
        }
            lodepng::encode(this->getFilename(), image, width, height);
        }
    else
    {
        int maxColorValue = 255;
        fs << "P3" << std::endl;
        fs << width << " " << height << std::endl;
        fs << maxColorValue << std::endl;

        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                fs << buffer[i][j] << std::endl;
            }
        }
    }
}
