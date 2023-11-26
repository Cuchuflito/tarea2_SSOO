#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>

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
    cout << "Start sequential conversion..." << endl;

    // Iniciar el cronómetro
    auto start_time = high_resolution_clock::now();

    // Convertir la imagen a escala de grises de manera secuencial
    Mat grayscaleImage;
    cvtColor(image, grayscaleImage, COLOR_BGR2GRAY);

    // Mostrar los primeros valores de las filas
    cout << "First values of some rows:" << endl;
    for (int r = 0; r < min(5, grayscaleImage.rows); r++) {
        for (int c = 0; c < min(5, grayscaleImage.cols); c++) {
            cout << static_cast<int>(grayscaleImage.at<uchar>(r, c)) << " ";
        }
        cout << endl;
    }

    // Detener el cronómetro y calcular el tiempo transcurrido
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);

    cout << "End sequential conversion." << endl;
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    // Mostrar la imagen original y la imagen en escala de grises
    imshow("Original Image", image);
    imshow("Grayscale Image", grayscaleImage);
    waitKey(0);

    return 0;
}
