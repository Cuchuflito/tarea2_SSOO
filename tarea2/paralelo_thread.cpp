#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <thread>
#include <vector>
#include <chrono>

using namespace cv;
using namespace std;
using namespace chrono;

// Función para procesar una parte de la imagen en escala de grises
void processImage(const Mat& input, Mat& output, int startRow, int endRow) {
    cvtColor(input.rowRange(startRow, endRow), output.rowRange(startRow, endRow), COLOR_BGR2GRAY);
}

int main() {
    cout << "Cargando." << endl;

    Mat image = imread("imagen.png", IMREAD_COLOR);

    if (image.empty()) {
        cerr << "Error al cargar la imagen." << endl;
        return -1;
    }

    cout << "Rows (height): " << image.rows << " Cols (width): " << image.cols << endl;
    cout << "Start parallel conversion..." << endl;

    // Iniciar el cronómetro
    auto start_time = high_resolution_clock::now();

    
    Mat grayscaleImage(image.size(), CV_8UC1);

    // THREADS
    int numThreads = 1;

   
    vector<thread> threads;

    // Dividir la imagen 
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

    // Detener el cronómetro 
    auto stop_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop_time - start_time);

    cout << "Fin Conversión." << endl;
    cout << "Execution time: " << duration.count() << " milliseconds" << endl;

    
    imshow("Imagen Original", image);
    imshow("Imagen Escala de grises", grayscaleImage);
    waitKey(0);

    return 0;
}
