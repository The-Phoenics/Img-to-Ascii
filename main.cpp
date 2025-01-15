#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./libs/stb_image.h"
#include "./libs/stb_image_write.h"

#include "render.hpp"
#include "utils.hpp"


int main()
{
    std::string drawing_chars = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

    // Input image file path
    const char* filename = "img/input2.jpg";

    // Load image
    int w, h, channels;
    std::uint8_t* data = stbi_load(filename, &w, &h, &channels, 0);
    if (data == nullptr) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return 1;
    }

    const int rows = h;
    const int columns = w;
    std::vector<std::vector<std::uint8_t>> grayscale_pixel_array(rows, std::vector<std::uint8_t>(columns));

    /*
     * Process the image data. Since the image is in RGBA format,
     * we loop through the data in steps of `channels` and calculate
     * the grayscale value for each pixel.
     */
    for (int i = 0; i < w * h * channels; i += channels) {
        int row = (i / channels) / columns;  // Calculate the row index
        int col = (i / channels) % columns;  // Calculate the column index

        // Extract RGB values from the data
        std::uint8_t r = data[i];
        std::uint8_t g = data[i + 1];
        std::uint8_t b = data[i + 2];

        // Calculate and store the grayscale value in the array
        grayscale_pixel_array[row][col] = RGB::grayscale_avg(r, g, b);
    }

    /*
     * Convert the grayscale pixel array into ASCII art.
     * Each pixel's grayscale value is mapped to a character from the `drawing_chars` string.
     */
    std::vector<std::string> ascii_result(rows);
    for (int r = 0; r < rows; ++r) {
        std::string ascii_text_row;
        for (int c = 0; c < columns; ++c) {
            int grayscale_value = grayscale_pixel_array[r][c];  // Get grayscale value
            int idx_val = map_range_val_from(0, 255, 0, drawing_chars.size() - 1, grayscale_value);  // Map grayscale to character
            ascii_text_row.push_back(drawing_chars.at(idx_val));  // Add character to the row
        }
        ascii_result[r] = ascii_text_row;

        // Print ascii result to a output file
        std::cout << ascii_text_row << '\n';
    }

    // Write ascii result to a output file
    std::ofstream out("img/ascii_output.txt", std::ios::out);
    if (!out) {
        std::cerr << "Failed to open file for writing ASCII output." << std::endl;
        return 1;
    }

    for (const std::string& s : ascii_result) {
        out << s << '\n';
    }
    out.close();

    // Save the processed grayscale/black-and-white image as a single-channel PNG file.
    std::vector<std::uint8_t> output_data(w * h);
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            output_data[i * w + j] = grayscale_pixel_array[i][j];
        }
    }
    
    // Write grayscale output to a png file
    const char* grayscale_output_file = "img/grayscale_output.png";
    if (!stbi_write_png(grayscale_output_file, w, h, 1, output_data.data(), w)) {
        std::cerr << "Failed to write image to " << grayscale_output_file << std::endl;
    }

    stbi_image_free(data);
}
