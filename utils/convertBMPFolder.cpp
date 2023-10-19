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

        if (width != 128 || height != 64) {
            std::cerr << "Invalid dimensions, must be 128x64.\n";
            return bitmap;
        }

        // Calculate padding for each row to be a multiple of 4 bytes.
        int row_padded = ((width + 31) / 32) * 4;
        uint8_t* data = new uint8_t[row_padded];

        bmp.seekg(61);  // Start of data

        bitmap.resize(width * height);  // Pre-allocate size

        for (int y = height - 1; y >= 0; --y) {
            bmp.read(reinterpret_cast<char*>(data), row_padded);

            for (int x = 0; x < width; ++x) {
                int byteIndex = x / 8;
                int bitIndex = x % 8;
                uint8_t pixel = (data[byteIndex] >> (7 - bitIndex)) & 1;

                bitmap[y * width + x] = pixel;
            }
        }

        delete[] data;
    }

    return bitmap;
}

void writeArrayToFile(const std::vector<uint8_t>& bitmap, const std::string& arrayName, const std::string& outputFile) {
    std::ofstream out(outputFile, std::ios_base::app);  // Open in append mode
    if (out.is_open()) {
        out << "uint8_t " << arrayName << "_bmp[] = {";
        for (size_t i = 0; i < bitmap.size(); ++i) {
            out << (int)bitmap[i];
            if (i < bitmap.size() - 1) {
                out << ", ";
            }

            // Insert a newline after every 64 entries
            if ((i + 1) % 64 == 0) {
                out << "\n";
            }
        }
        out << "};\n\n";  // Extra newline to separate arrays
        out.close();
    } else {
        std::cerr << "Couldn't open output file!\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input_folder> <output.hpp>\n";
        return 1;
    }

    std::string inputFolder = argv[1];
    std::string outputFile = argv[2];

    // Clear the output file and write the initial lines
    std::ofstream out(outputFile, std::ofstream::trunc);
    if (out.is_open()) {
        out << "#pragma once\n";
        out << "#include <cstdint>\n\n";
        out.close();
    } else {
        std::cerr << "Couldn't open output file!\n";
        return 1;
    }

    for (const auto &entry : std::filesystem::directory_iterator(inputFolder)) {
        if (entry.path().extension() == ".bmp") {
            std::vector<uint8_t> bitmap = readBMP(entry.path().string());
            if (!bitmap.empty()) {
                std::string arrayName = entry.path().stem().string();  // Filename without extension
                writeArrayToFile(bitmap, arrayName, outputFile);
            }
        }
    }


    std::cout << "Bitmap data written to " << outputFile << "\n";

    return 0;
}