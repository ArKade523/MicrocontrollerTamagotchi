#include <iostream>
#include <fstream>
#include <vector>
#include <string>

std::vector<uint8_t> readBMP(const std::string& file) {
    std::ifstream bmp(file, std::ios::binary);
    std::vector<uint8_t> bitmap;

    if (bmp.is_open()) {
        uint8_t header[54];
        bmp.read(reinterpret_cast<char*>(header), 54);

        int width = *(int*)&header[18];
        int height = *(int*)&header[22];

        // if (width != 128 || height != 64) {
        //     std::cerr << "Invalid dimensions, must be 128x64.\n";
        //     return bitmap;
        // }

        int row_padded = ((width + 31) / 32) * 4;
        uint8_t* data = new uint8_t[row_padded];

        bmp.seekg(61);  // Start of data

        int packedSize = width * height / 8;
        bitmap.resize(packedSize);  // Pre-allocate size for packed bits

        for (int y = height - 1; y >= 0; --y) {
            bmp.read(reinterpret_cast<char*>(data), row_padded);

            for (int x = 0; x < width; x += 8) {
                uint8_t packedByte = 0;
                for (int bit = 0; bit < 8; ++bit) {
                    int byteIndex = (x + bit) / 8;
                    int bitIndex = (x + bit) % 8;
                    uint8_t pixel = (data[byteIndex] >> (7 - bitIndex)) & 1;
                    packedByte |= (pixel << (7 - bit));
                }

                bitmap[y * width / 8 + x / 8] = packedByte;
            }
        }

        delete[] data;
    }

    return bitmap;
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

    std::vector<uint8_t> bitmap = readBMP(inputFile);

    if (bitmap.empty()) {
        std::cerr << "Failed to read BMP or BMP is empty\n";
        return 1;
    }

    writeArrayToFile(bitmap, outputFile);

    std::cout << "Bitmap data written to " << outputFile << "\n";

    return 0;
}
