#include <cstdint>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./libs/stb_image.h"
#include "./libs/stb_image_write.h"

void greyscale_avg(std::uint8_t* r, std::uint8_t* g, std::uint8_t* b) {
    if (!r || !g || !b)
        std::cout << "Channel values pointers are invalid\n";
    std::uint8_t grey = (static_cast<unsigned int>(*r) + 
                         static_cast<unsigned int>(*g) + 
                         static_cast<unsigned int>(*b)) / 3;
    *r = grey;
    *g = grey;
    *b = grey;
}

int main()
{
    // dark to light brightness depth value characters
    std::string drawing_chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";
    std::cout << "drawing chars size: " << drawing_chars.size() << std::endl;

    const char* filename = "img/test_img.png";
    int w, h, channels, req_comp = 0, data_size = 0; // image width, height, color channels(4 for rgba)
    // what are all these values for?

    // load
    std::uint8_t* data = stbi_load(filename, &w, &h, &channels, req_comp); // what is unsigned char*?
    if (data == NULL)
        std::cout << "Failed to load image: " << filename << std::endl;
    data_size = w * h * channels;

    std::cout << w << " " << h << " " << channels << std::endl << data[0] << std::endl;

    // convert data to greyscale
    std::uint8_t *r, *g, *b;
    for (size_t i = 0; i < data_size; i++) {
        int modulo = i % channels;
        auto* value = &data[i];
        switch (modulo) {
            case 0:
                r = value;
                break;
            case 1:
                g = value;
                break;
            case 2:
                b = value;
                greyscale_avg(r, g, b);
                break;
            default:
                // skip alpha values
                break;
        }

        // *value = *value - *value / 3; // decrease the color values
        // *value = 255; // complete white image
        // std::cout << static_cast<unsigned int>(data[i]) << " "; // why cast needed?
    }

    // write processed data to a new image
    int result = stbi_write_png("result.png", w, h, channels, data, 0); // what is stride?
    if (!result)
        std::cout << "Failed to write image data into result.png\n";

    // free
    stbi_image_free(data);
}

