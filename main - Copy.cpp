/*
    A program that creates an image that assigns a random color to a pixel and also creates a color histogram
    Author: Geordan Townsend
    Date: September 19th
*/
#include <iostream>
#include <vector>
#include <random>
#include <cstdint>


using namespace std;


// Function that generates a random color (0x00RRGGBB)
uint32_t generateRandomColor() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 255);

    uint8_t r = dis(gen);
    uint8_t g = dis(gen);
    uint8_t b = dis(gen);

    return (r << 16) | (g << 8) | b;
}

// Helper functions to extract RGB components
uint8_t extractRed(uint32_t color) {
    return (color >> 16) & 0xFF;
}

uint8_t extractGreen(uint32_t color) {
    return (color >> 8) & 0xFF;
}

uint8_t extractBlue(uint32_t color) {
    return color & 0xFF;
}

// Function to populate the image with random colors
void populateImage(std::vector<std::vector<uint32_t>>& image, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            image[i][j] = generateRandomColor();
        }
    }
}

// Function to compute RGB histograms
void computeHistograms(
    const std::vector<std::vector<uint32_t>>& image,
    std::vector<int>& redHist,
    std::vector<int>& greenHist,
    std::vector<int>& blueHist,
    int rows,
    int cols
) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            uint32_t color = image[i][j];
            ++redHist[extractRed(color)];
            ++greenHist[extractGreen(color)];
            ++blueHist[extractBlue(color)];
        }
}

// Function to display a histogram
void displayHistogram(const std::vector<int>& hist, const std::string& colorName) {
    std::cout << "--- " << colorName << " Channel Histogram ---\n";

    for (int i = 0; i < 256; ++i) {
        std::cout << i << ": ";

        if (hist[i] > 0) {
            for (int j = 0; j < hist[i]; ++j)
                std::cout << "################";
        }

        std::cout << " (" << hist[i] << ")\n";
    }

    std::cout << std::endl;
}

int main() {
    const int ROWS = 10;
    const int COLS = 10;

    // Create a 2D vector to hold random color values
    std::vector<std::vector<uint32_t>> image_data(ROWS, std::vector<uint32_t>(COLS));

    // Populate image_data vecttor with random colors
    populateImage(image_data, ROWS, COLS);

    // Calculate red, green, and blue color histograms
    std::vector<int> redHist(256, 0);
    std::vector<int> greenHist(256, 0);
    std::vector<int> blueHist(256, 0);
    computeHistograms(image_data, redHist, greenHist, blueHist, ROWS, COLS);

    // Display red, green, and blue color histograms
    displayHistogram(redHist, "Red");
    displayHistogram(greenHist, "Green");
    displayHistogram(blueHist, "Blue");

    return 0;
}

