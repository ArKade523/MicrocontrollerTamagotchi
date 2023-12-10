#include <iostream>
#include <fstream>
#include <vector>

// Function to read a 1-bit bitmap and convert it to a 1-bit per pixel array
std::vector<unsigned char> convertBitmapTo1BPP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open file");
    }

    // Read the BMP header
    char header[54];
    file.read(header, 54);

    // Extract width and height from the header
    int width = *reinterpret_cast<int*>(&header[18]);
    int height = *reinterpret_cast<int*>(&header[22]);
    std::cout << "Width: " << width << ", Height: " << height << "\n";

    // Calculate the row size (width in bytes, rounded up to the nearest 4 bytes)
    int rowSize = (width + 7) / 8; // 1 bit per pixel
    int padding = (4 - (rowSize % 4)) % 4;
    std::cout << "Row size: " << rowSize << ", Padding: " << padding << "\n";
    rowSize += padding;

    // Read the bitmap data
    std::vector<unsigned char> bitmapData(rowSize * height);
    file.read(reinterpret_cast<char*>(bitmapData.data()), bitmapData.size());

    // Close the file
    file.close();

    // Convert to 1-bit per pixel format
    std::vector<unsigned char> outputData(width * height / 8);
    for (int y = 0; y < height; ++y) {
        int invertedY = height - 1 - y; // Invert the y-coordinate to start from the bottom
        for (int x = 0; x < width; x += 8) {
            unsigned char byte = 0;
            for (int bit = 0; bit < 8; ++bit) {
                if (x + bit < width) {
                    // Use invertedY instead of y
                    byte |= (bitmapData[invertedY * rowSize + (x + bit) / 8] >> (7 - bit)) & 1;
                }
                byte <<= 1;
            }
            // Use y as it is for outputData since we want to store the data in the correct order
            outputData[y * width / 8 + x / 8] = byte;
        }
    }

    return outputData;
}

void writeArrayToFile(const std::vector<uint8_t>& bitmap, const std::string& outputFile) {
    std::ofstream out(outputFile);
    std::string arrayName = outputFile.substr(0, outputFile.find_last_of('.')) + "_bmp";
    if (out.is_open()) {
        out << "uint8_t " << arrayName << "[] = {";
        for (size_t i = 0; i < bitmap.size(); ++i) {
            out << "0x" << std::hex << (int)bitmap[i];
            if (i < bitmap.size() - 1) {
                out << ", ";
            }

            if ((i + 1) % 8 == 0) {
                out << "\n";
            }
        }
        out << "};\n";
        out.close();
    } else {
        std::cerr << "Couldn't open output file!\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input.bmp> <output.txt>\n";
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    std::vector<uint8_t> bitmap = convertBitmapTo1BPP(inputFile);

    if (bitmap.empty()) {
        std::cerr << "Failed to read BMP or BMP is empty\n";
        return 1;
    }

    writeArrayToFile(bitmap, outputFile);

    std::cout << "Bitmap data written to " << outputFile << "\n";

    return 0;
}
