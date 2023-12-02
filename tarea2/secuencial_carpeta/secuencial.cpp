#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

int main() {
    cout << "Cargando..." << endl;

    
    Mat image = imread("imagen.png", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar" << endl;
        return -1;
    }

    cout << "Rows (height): " << image.rows << " Cols (width): " << image.cols << endl;
    cout << "Comienza transformación secuencial." << endl;

    
    auto start_time = high_resolution_clock::now();

    
    Mat grayscaleImage;
    cvtColor(image, grayscaleImage, COLOR_BGR2GRAY); //conversión secuencial

    cout << "Primeros valores nueva imagen" << endl;
    for (int r = 0; r < min(5, grayscaleImage.rows); r++) {
        for (int c = 0; c < min(5, grayscaleImage.cols); c++) {
            cout << static_cast<int>(grayscaleImage.at<uchar>(r, c)) << " ";
        }
        cout << endl;
    }

    
    auto stop_time = high_resolution_clock::now(); //se para y se muestra el tiempo de ejecución
    auto duration = duration_cast<milliseconds>(stop_time - start_time);

    cout << "Conversión secuencial terminada." << endl;
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
