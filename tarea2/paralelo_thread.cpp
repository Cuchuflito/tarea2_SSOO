#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <thread>
#include <vector>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

// Función para procesar una porción de la imagen en escala de grises
void processImage(const Mat& input, Mat& output, int startRow, int endRow) {
    cvtColor(input.rowRange(startRow, endRow), output.rowRange(startRow, endRow), COLOR_BGR2GRAY);
}

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

    // Convertir la imagen a escala de grises
    Mat grayscaleImage(image.size(), CV_8UC1);

    // Número de threads (ajústalo según el número de núcleos de tu CPU)
    int numThreads = 4;

    // Vector para almacenar los threads
    vector<thread> threads;

    // Dividir la imagen en segmentos para procesar en paralelo
    int rowsPerThread = image.rows / numThreads;
    int startRow = 0;

    for (int i = 0; i < numThreads; i++) {
        int endRow = (i == numThreads - 1) ? image.rows : startRow + rowsPerThread;
        threads.emplace_back(processImage, ref(image), ref(grayscaleImage), startRow, endRow);
        startRow = endRow;
    }

    // Esperar a que todos los threads terminen
    for (auto& t : threads) {
        t.join();
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
