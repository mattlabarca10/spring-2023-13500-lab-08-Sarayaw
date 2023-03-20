#include <iostream> 
#include <string> 
#include <cassert>
#include <vector>
#include <fstream>
#include "funcs.h"
#include "imageio.h"

const int MAX_H = 512;
const int MAX_W = 512;

void invert(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            assert(image[row][col] < 256);
            assert(image[row][col] >= 0);
            int temp = image[row][col];
            temp = 255 - temp; 
            out[row][col] = temp; 
        }
    }

    writeImage(out_name, out, height, width);
    return;
}

void invert_half(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width / 2; col++) {
            assert(image[row][col] < 256);
            assert(image[row][col] >= 0);
            out[row][col] = image[row][col];
        }

        for (int col = width / 2; col < width; col++) {
            assert(image[row][col] < 256);
            assert(image[row][col] >= 0);
            int temp = image[row][col];
            temp = 255 - temp; 
            out[row][col] = temp;
        }
    }

    writeImage(out_name, out, height, width);
    return;
}

void box(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            assert(image[row][col] < 256);
            assert(image[row][col] >= 0);
            // white box should go from 25% -> 75% all dimensions 
            // bottom: (height / 4) * 3 >= row
            // left: width / 4 <= col
            // top: height / 4 <= row
            // right: (width / 4) * 3 >= col
            if ((height / 4) * 3 >= row && width / 4 <= col && height / 4 <= row && (width / 4) * 3 >= col) { 
                out[row][col] = 255;
            } else {
                out[row][col] = image[row][col];
            }
        }
    }

    writeImage(out_name, out, height, width);
    return;
}

void frame(std::string name, std::string out_name) {
    int height, width; 
    int image[MAX_H][MAX_W];
    readImage(name, image, height, width); 

    int out[MAX_H][MAX_W];

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
 

            if((height / 4 <= row && height / 4 + 1 > row && width / 4 <= col && (width / 4) * 3 >= col) || 
			((height / 4) * 3 >= row && (height / 4) * 3 - 1 < row && width / 4 <= col && (width / 4) * 3 >= col) || 
			(width / 4 <= col && width / 4 + 1 > col && height / 4 <= row && (height / 4) * 3 >= row) || 
			((width / 4) * 3 - 1 < col && (width / 4) * 3 >= col && height / 4 <= row && (height / 4) * 3 >= row)) { 
                out[row][col] = 255; 
            } else { 
                out[row][col] = image[row][col];
            }
		}
	}

    writeImage(out_name, out, height, width);
    return; 
}

void scale(std::string name, std::string out_name) {
int height, width;
int image[MAX_H][MAX_W];
readImage(name, image, height, width);
  
 int out[MAX_H][MAX_W];

for (int row = 0; row < height * 2; row++) {
    for (int col = 0; col < width * 2; col++) {
        assert(image[row / 2][col / 2] < 256);
        assert(image[row / 2][col / 2] >= 0);
        out[row][col] = image[row / 2][col / 2];
    }
}

writeImage(out_name, out, height * 2, width * 2);
return;
  }

void pixelate(std::string name, std::string out_name) {
int height, width;
int image[MAX_H][MAX_W];
readImage(name, image, height, width);
  
  int out[MAX_H][MAX_W];

for (int row = 0; row < height; row += 2) {
    for (int col = 0; col < width; col += 2) {
        assert(image[row][col] < 256);
        assert(image[row][col] >= 0);
        int sum = 0;
        int pixels = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (row + i < height && col + j < width) {
                    sum += image[row + i][col + j];
                    pixels++;
                }
            }
        }
        int average = sum / pixels;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (row + i < height && col + j < width) {
                    out[row + i][col + j] = average;
                }
            }
        }
    }
}

writeImage(out_name, out, height, width);
return;
