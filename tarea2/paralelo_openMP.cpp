#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace chrono;

int main() {
    cout << "Loading image..." << endl;

    // Leer la imagen a color
    Mat image = imread("imagen.png", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar la imagen." << endl;
        return -1;
    }

    cout << "Rows (height): " << image.rows << " Cols (width): " << image.cols << endl;
    cout << "Start parallel conversion..." << endl;

    // Iniciar el cronómetro
    auto start_time = high_resolution_clock::now();

    // Convertir la imagen a escala de grises en paralelo con OpenMP
    Mat grayscaleImage(image.size(), CV_8UC1);
#pragma omp parallel for
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            grayscaleImage.at<uchar>(r, c) = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
        }
    }

    // Detener el cronómetro y calcular el tiempo transcurrido
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);

    cout << "End parallel conversion." << endl;
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    // Mostrar la imagen original y la imagen en escala de grises
    imshow("Original Image", image);
    imshow("Grayscale Image", grayscaleImage);
    waitKey(0);

    return 0;
}
