#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./libs/stb_image.h"
#include "./libs/stb_image_write.h"

class RGB {
public:
    // RGBA channels
    std::uint8_t r = NULL;
    std::uint8_t g = NULL;
    std::uint8_t b = NULL;
    std::uint8_t a = NULL;

    RGB(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_b a = )
        : r(r), g(b), b(b) {}
    ~RGB() {}

    std::uint8_t get_grayscale_avg() {
        if (!r || !g || !b)
            std::cout << "Channel/RGB values are invalid\n";
        std::uint8_t gray_value = (static_cast<unsigned int>(r) + static_cast<unsigned int>(g) + static_cast<unsigned int>(b)) / 3;
        return gray_value;
    }

    static std::uint8_t grayscale_avg(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
        if (!r || !g || !b)
            std::cout << "Channel values pointers are invalid\n";
        std::uint8_t value = (static_cast<unsigned int>(r) + static_cast<unsigned int>(g) + static_cast<unsigned int>(b)) / 3;
        return value;
    }
};

/*
* this maps from a bigger range to a smaller range eg. from (0 -> 50) to (3 -> 7)
*/
int map_range_val_from(int fr_lower, int fr_upper, int to_lower, int to_upper, int value) {
    if (fr_lower == fr_upper || to_lower == to_upper) {
        return -1;
    }
    float scale = static_cast<float>(to_upper - to_lower) / (fr_upper - fr_lower);
    int mapped_value = to_lower + static_cast<int>((value - fr_lower) * scale);
    return mapped_value;
}

int main()
{
    std::string drawing_chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

    const char* filename = "img/536x354.jpg";

    // image width, height, color channels(4 for rgba)
    int w, h, channels, req_comp = 0, data_size = 0;

    // load image
    std::uint8_t* data = stbi_load(filename, &w, &h, &channels, req_comp); // what is unsigned char*?
    if (data == NULL)
        std::cout << "Failed to load image: " << filename << std::endl;
    data_size = w * h * channels;
    
    static int grayscale_pixel_array_size = data_size / 4;
    std::vector<std::uint8_t> grayscale_pixel_array(grayscale_pixel_array_size);

    // convert data to grayscale
//    std::uint8_t *r, *g, *b;
//    for (size_t i = 0; i < data_size; i++) {
//        int modulo = i % channels;
//        auto* value = &data[i];
//        switch (modulo) {
//            case 0:
//                r = value;
//                break;
//            case 1:
//                g = value;
//                break;
//            case 2:
//                b = value;
//                grayscale_avg(r, g, b);
//                break;
//            default:
//                // skip alpha values
//                break;
//        }
    
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
                grayscale_pixel_array.at(i) = get_grayscale_avg(r, g, b);
                break;
            default:
                // skip alpha values
                break;
        }

        // *value = *value - *value / 3; // decrease the color values
        // std::cout << static_cast<unsigned int>(data[i]) << " "; // why cast needed?
    }

    // write processed data to a new image
    const char* grayscale_output_file = "img/grayscale.png";
    int result = stbi_write_png(grayscale_output_file, w, h, channels, data, 0); // what is stride?
    if (!result)
        std::cout << "Failed to write image data into" << grayscale_output_file << std::endl;

    // print ascii art
    for (size_t r = 0; r < h; r++) { // r += 2 to reduce height
        for (size_t c = 0; c < w * channels; c += channels) { // c += channels * 2 to reduce width
            int val = data[w * channels * r + c];
            int idx_val = map_range_val_from(0, 255, 0, drawing_chars.size() - 1, val);
            char ch = drawing_chars.at(idx_val);
            std::cout << ch;
        }
        std::cout << "\n";
    }

    stbi_image_free(data);
}

