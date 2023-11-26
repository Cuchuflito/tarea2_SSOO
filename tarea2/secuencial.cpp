#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main() {
    cout << "Loading image..." << endl;

    // Leer la imagen a color
    Mat image = imread("imagen.png", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar la imagen." << endl;
        return -1;
    }

    cout << "Rows (height): " << image.rows << " Cols (width): " << image.cols << endl;
    cout << "Start conversion..." << endl;

    // Convertir la imagen a escala de grises
    cvtColor(image, image, COLOR_BGR2GRAY);

    // Mostrar cada píxel en escala de grises
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            int pixel_value = image.at<uchar>(r, c);
            cout << pixel_value << " ";
        }
        cout << endl;
    }

    cout << "End conversion." << endl;

    // Mostrar la imagen original y la imagen en escala de grises
    imshow("Original Image", imread("imagen.png", IMREAD_COLOR));
    imshow("Grayscale Image", image);
    waitKey(0);

    return 0;
}
