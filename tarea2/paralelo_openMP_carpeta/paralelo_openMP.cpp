#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace chrono;

int main() {
    cout << "Cargando." << endl;

    // Leer la imagen a color
    Mat image = imread("imagen.png", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar." << endl;
        return -1;
    }

    cout << "Rows (height): " << image.rows << " Cols (width): " << image.cols << endl;
    cout << "Iniciar conversión paralela" << endl;

    // Iniciar el cronómetro
    auto start_time = high_resolution_clock::now();

    // Convertir imagen paralelo con OpenMP
    Mat grayscaleImage(image.size(), CV_8UC1);
#pragma omp parallel for
    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            grayscaleImage.at<uchar>(r, c) = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
        }
    }

    // Detener el cronómetro
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);

    cout << "Conversión terminada" << endl;
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    namedWindow("Imagen Real", WINDOW_NORMAL);
    resizeWindow("Imagen Real", image.cols, image.rows);
    imshow("Imagen Real", image);

    namedWindow("Imagen en escala de grises", WINDOW_NORMAL);
    resizeWindow("Imagen en escala de grises", grayscaleImage.cols, grayscaleImage.rows);
    imshow("Imagen en escala de grises", grayscaleImage);
    waitKey(0);

    return 0;
}
