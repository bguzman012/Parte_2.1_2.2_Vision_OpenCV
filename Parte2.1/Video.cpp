#include "Video.hpp"

int k = 50;
int mSal = 3;
int mImparSal = 3;
int mPim = 3;
int mImparPim = 3;
int pi = 50;
int minCannyGaussSal = 25;
int minImparCannyGaussSal = 50;
int minCannyBlurSal = 25;
int minImparCannyBlurSal = 50;
int minCannyGaussPim = 25;
int minImparCannyGaussPim = 50;
int minCannyBlurPim = 25;
int minImparCannyBlurPim = 50;

Mat gris;
Mat grisRuidoPimienta;
Mat grisRuidoSal;
Mat imgMedianaSal;
Mat imgMedianaPimienta;
Mat gaussSal;
Mat gaussPim;
Mat gaussCannySal;
Mat gaussCannyPim;
Mat blurCannySal;
Mat blurCannyPim;
Mat cannySalLaplace;
Mat blurSalLaplace;
Mat cannyPimLaplace;
Mat blurPimLaplace;

void generateTrackBarGaussCanny(int v, void *pV)
{
    Mat tmp;
    gaussCannySal = gaussSal.clone();
    int minCannyTmp = minCannyGaussSal;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyGaussSal = minCannyTmp;

    Canny(gaussSal, gaussCannySal, minCannyTmp, 150, 3);

    Laplacian(gaussSal, tmp, CV_16S, 3);
    convertScaleAbs(tmp, cannySalLaplace);
    namedWindow("Gauss Sal Canny", WINDOW_AUTOSIZE);
    namedWindow("Gauss Sal Laplace", WINDOW_AUTOSIZE);
    imshow("Gauss Sal Canny", gaussCannySal);
    imshow("Gauss Sal Laplace", cannySalLaplace);
}

void generateTrackBarBlurCanny(int v, void *pV)
{
    Mat tmp;
    blurCannySal = imgMedianaSal.clone();
    int minCannyTmp = minCannyBlurSal;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyBlurSal = minCannyTmp;

    Canny(imgMedianaSal, blurCannySal, minCannyTmp, 150, 3);

    Laplacian(imgMedianaSal, tmp, CV_16S, 3);
    convertScaleAbs(tmp, blurSalLaplace);
    namedWindow("Blur Sal Canny", WINDOW_AUTOSIZE);
    namedWindow("Blur Sal Laplace", WINDOW_AUTOSIZE);
    imshow("Blur Sal Canny", blurCannySal);
    imshow("Blur Sal Laplace", blurSalLaplace);
}

void generateTrackBarGaussCannyPime(int v, void *pV)
{
    Mat tmp;
    gaussCannyPim = imgMedianaPimienta.clone();
    int minCannyTmp = minCannyGaussPim;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyGaussPim = minCannyTmp;

    Canny(imgMedianaPimienta, gaussCannyPim, minCannyTmp, 150, 3);

    Laplacian(gaussPim, tmp, CV_16S, 3);
    convertScaleAbs(tmp, cannyPimLaplace);
    namedWindow("Gauss Pimienta Canny", WINDOW_AUTOSIZE);
    namedWindow("Gauss Pimienta Laplace", WINDOW_AUTOSIZE);
    imshow("Gauss Pimienta Canny", gaussCannyPim);
    imshow("Gauss Pimienta Laplace", cannyPimLaplace);
}

void generateTrackBarBlurCannyPime(int v, void *pV)
{
    Mat tmp;
    blurCannyPim = imgMedianaPimienta.clone();
    int minCannyTmp = minCannyBlurPim;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyBlurPim = minCannyTmp;

    Canny(imgMedianaPimienta, blurCannyPim, minCannyTmp, 150, 3);

    Laplacian(imgMedianaPimienta, tmp, CV_16S, 3);
    convertScaleAbs(tmp, blurPimLaplace);
    namedWindow("Blur Pimienta Canny", WINDOW_AUTOSIZE);
    namedWindow("Blur Pimienta Laplace", WINDOW_AUTOSIZE);
    imshow("Blur Pimienta Canny", blurCannyPim);
    imshow("Blur Pimienta Laplace", blurPimLaplace);
}

void generateTrackBarMedianaSal(int v, void *pV)
{
    imgMedianaSal = grisRuidoSal.clone();
    if (mSal % 2 != 0)
        mImparSal = mSal;

    medianBlur(grisRuidoSal, imgMedianaSal, mImparSal);
    GaussianBlur(grisRuidoSal, gaussSal, Size(mImparSal, mImparSal), 0, 0, BORDER_DEFAULT);
    namedWindow("Filtro Mediana Sal", WINDOW_AUTOSIZE);
    namedWindow("Filtro Gauss Sal", WINDOW_AUTOSIZE);
    createTrackbar("Canny", "Filtro Gauss Sal", &minCannyGaussSal, 100, generateTrackBarGaussCanny, NULL);
    createTrackbar("Canny", "Filtro Mediana Sal", &minCannyBlurSal, 100, generateTrackBarBlurCanny, NULL);
    imshow("Filtro Mediana Sal", imgMedianaSal);
    imshow("Filtro Gauss Sal", gaussSal);
}

void generateTrackBarMedianaPimienta(int v, void *pV)
{
    imgMedianaPimienta = grisRuidoPimienta.clone();
    if (mPim % 2 != 0)
        mImparPim = mPim;

    medianBlur(grisRuidoPimienta, imgMedianaPimienta, mImparPim);
    GaussianBlur(grisRuidoPimienta, gaussPim, Size(mImparPim, mImparPim), 0, 0, BORDER_DEFAULT);
    namedWindow("Filtro Mediana Pimienta", WINDOW_AUTOSIZE);
    namedWindow("Filtro Gauss Pimienta", WINDOW_AUTOSIZE);
    createTrackbar("Canny", "Filtro Gauss Pimienta", &minCannyGaussPim, 100, generateTrackBarGaussCannyPime, NULL);
    createTrackbar("Canny", "Filtro Mediana Pimienta", &minCannyBlurPim, 100, generateTrackBarBlurCannyPime, NULL);
    imshow("Filtro Mediana Pimienta", imgMedianaPimienta);
    imshow("Filtro Gauss Pimienta", gaussPim);
}

void generateTrackBar(int v, void *pV)
{

    grisRuidoSal = gris.clone();
    double porcentaje = k;
    porcentaje = porcentaje / 100;
    int total = (porcentaje * ((double)(gris.rows)) * ((double)gris.cols));

    int cont = 0;
    int pixel = 0;
    int fila = 0;
    int col = 0;

    while (cont < total)
    {

        fila = rand() % grisRuidoSal.rows;
        col = rand() % grisRuidoSal.cols;
        grisRuidoSal.at<uchar>(fila, col) = 255;
        cont++;
    }

    createTrackbar("M Sal", "Imagen Ruido Sal", &mSal, 33, generateTrackBarMedianaSal, NULL);

    imshow("Imagen Ruido Sal", grisRuidoSal);
}

void generateTrackBarPimienta(int v, void *pV)
{

    grisRuidoPimienta = gris.clone();
    double porcentaje = pi;
    porcentaje = porcentaje / 100;
    int total = (porcentaje * ((double)(gris.rows)) * ((double)gris.cols));

    int cont = 0;
    int pixel = 0;
    int fila = 0;
    int col = 0;

    while (cont < total)
    {

        fila = rand() % grisRuidoPimienta.rows;
        col = rand() % grisRuidoPimienta.cols;
        grisRuidoPimienta.at<uchar>(fila, col) = 0;
        cont++;
    }
    createTrackbar("M Pim", "Imagen Ruido Pimienta", &mPim, 33, generateTrackBarMedianaPimienta, NULL);

    imshow("Imagen Ruido Pimienta", grisRuidoPimienta);
}

int Video::conversionImagen()
{
    bool banderaSal = false;
    bool banderaPim = false;

    VideoCapture video(0);

    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("Imagen Ruido Pimienta", WINDOW_AUTOSIZE);
    namedWindow("Imagen Ruido Sal", WINDOW_AUTOSIZE);
    namedWindow("Filtro Mediana Pimienta", WINDOW_AUTOSIZE);
    namedWindow("Filtro Gauss Pimienta", WINDOW_AUTOSIZE);
    namedWindow("Filtro Mediana Sal", WINDOW_AUTOSIZE);
    namedWindow("Filtro Gauss Sal", WINDOW_AUTOSIZE);
    namedWindow("Blur Pimienta Canny", WINDOW_AUTOSIZE);
    namedWindow("Blur Pimienta Laplace", WINDOW_AUTOSIZE);
    namedWindow("Blur Sal Canny", WINDOW_AUTOSIZE);
    namedWindow("Blur Sal Laplace", WINDOW_AUTOSIZE);
    namedWindow("Gauss Pimienta Canny", WINDOW_AUTOSIZE);
    namedWindow("Gauss Pimienta Laplace", WINDOW_AUTOSIZE);
    namedWindow("Gauss Sal Canny", WINDOW_AUTOSIZE);
    namedWindow("Gauss Sal Laplace", WINDOW_AUTOSIZE);

    createTrackbar("Sal", "Gris", &k, 100, generateTrackBar, NULL);
    createTrackbar("Pimienta", "Gris", &pi, 100, generateTrackBarPimienta, NULL);
    createTrackbar("M Sal", "Imagen Ruido Sal", &mSal, 33, generateTrackBarMedianaSal, NULL);
    createTrackbar("M Pim", "Imagen Ruido Pimienta", &mPim, 33, generateTrackBarMedianaPimienta, NULL);
    createTrackbar("Canny", "Filtro Gauss Pimienta", &minCannyGaussPim, 100, generateTrackBarGaussCannyPime, NULL);
    createTrackbar("Canny", "Filtro Mediana Pimienta", &minCannyBlurPim, 100, generateTrackBarBlurCannyPime, NULL);
    createTrackbar("Canny", "Filtro Gauss Sal", &minCannyGaussSal, 100, generateTrackBarGaussCanny, NULL);
    createTrackbar("Canny", "Filtro Mediana Sal", &minCannyBlurSal, 100, generateTrackBarBlurCanny, NULL);

    while (3 == 3)
    {
        Mat catedral;
        video >> catedral;

        srand((unsigned)time(0));

        cvtColor(catedral, gris, COLOR_BGR2GRAY);

        if (waitKey(23) == 115)
        {
            banderaSal = true;
        }
        if (waitKey(23) == 112)
        {
            banderaPim = true;
        }
        if (banderaSal)
        {

            mostrarImagenSal();
            mostrarImagenSalBlur();
            mostrarImagenSalCannyGauss();
            mostrarImagenSalCannyBlur();
        }
        if (banderaPim)
        {

            mostrarImagenPimienta();
            mostrarImagenPimientaBlur();
            mostrarImagenPimeCannyBlur();
            mostrarImagenPimeCannyGauss();
        }

        imshow("Original", catedral);
        imshow("Gris", gris);
    }

    destroyAllWindows();

    return 0;
}

void Video::mostrarImagenPimienta()
{

    grisRuidoPimienta = gris.clone();
    double porcentaje = pi;
    porcentaje = porcentaje / 100;
    int total = (porcentaje * ((double)(gris.rows)) * ((double)gris.cols));

    int cont = 0;
    int pixel = 0;
    int fila = 0;
    int col = 0;

    while (cont < total)
    {

        fila = rand() % grisRuidoPimienta.rows;
        col = rand() % grisRuidoPimienta.cols;
        grisRuidoPimienta.at<uchar>(fila, col) = 0;
        cont++;
    }
    //createTrackbar("M Pim", "Imagen Ruido Pimienta", &mPim, 33, generateTrackBarMedianaPimienta, NULL);
    imshow("Imagen Ruido Pimienta", grisRuidoPimienta);
}

void Video::mostrarImagenSal()
{
    grisRuidoSal = gris.clone();
    double porcentaje = k;
    porcentaje = porcentaje / 100;
    int total = (porcentaje * ((double)(gris.rows)) * ((double)gris.cols));

    int cont = 0;
    int pixel = 0;
    int fila = 0;
    int col = 0;

    while (cont < total)
    {

        fila = rand() % grisRuidoSal.rows;
        col = rand() % grisRuidoSal.cols;
        grisRuidoSal.at<uchar>(fila, col) = 255;
        cont++;
    }

    imshow("Imagen Ruido Sal", grisRuidoSal);
}

void Video::mostrarImagenPimientaBlur()
{
    imgMedianaPimienta = grisRuidoPimienta.clone();
    if (mPim % 2 != 0)
        mImparPim = mPim;

    medianBlur(grisRuidoPimienta, imgMedianaPimienta, mImparPim);
    GaussianBlur(grisRuidoPimienta, gaussPim, Size(mImparPim, mImparPim), 0, 0, BORDER_DEFAULT);
    imshow("Filtro Mediana Pimienta", imgMedianaPimienta);
    imshow("Filtro Gauss Pimienta", gaussPim);
}

void Video::mostrarImagenSalBlur()
{
    imgMedianaSal = grisRuidoSal.clone();
    if (mSal % 2 != 0)
        mImparSal = mSal;

    medianBlur(grisRuidoSal, imgMedianaSal, mImparSal);
    GaussianBlur(grisRuidoSal, gaussSal, Size(mImparSal, mImparSal), 0, 0, BORDER_DEFAULT);
    imshow("Filtro Mediana Sal", imgMedianaSal);
    imshow("Filtro Gauss Sal", gaussSal);
}

void Video::mostrarImagenSalCannyGauss()
{
    Mat tmp;
    gaussCannySal = gaussSal.clone();
    int minCannyTmp = minCannyGaussSal;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyGaussSal = minCannyTmp;

    Canny(gaussSal, gaussCannySal, minCannyTmp, 150, 3);

    Laplacian(gaussSal, tmp, CV_16S, 3);
    convertScaleAbs(tmp, cannySalLaplace);
    imshow("Gauss Sal Canny", gaussCannySal);
    imshow("Gauss Sal Laplace", cannySalLaplace);
}
void Video::mostrarImagenPimeCannyGauss()
{

    Mat tmp;
    gaussCannyPim = imgMedianaPimienta.clone();
    int minCannyTmp = minCannyGaussPim;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyGaussPim = minCannyTmp;

    Canny(imgMedianaPimienta, gaussCannyPim, minCannyTmp, 150, 3);
    Laplacian(gaussPim, tmp, CV_16S, 3);
    convertScaleAbs(tmp, cannyPimLaplace);
    imshow("Gauss Pimienta Canny", gaussCannyPim);
    imshow("Gauss Pimienta Laplace", cannyPimLaplace);
}

void Video::mostrarImagenSalCannyBlur()
{

    Mat tmp;
    blurCannySal = imgMedianaSal.clone();
    int minCannyTmp = minCannyBlurSal;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyBlurSal = minCannyTmp;

    Canny(imgMedianaSal, blurCannySal, minCannyTmp, 150, 3);

    Laplacian(imgMedianaSal, tmp, CV_16S, 3);
    convertScaleAbs(tmp, blurSalLaplace);

    imshow("Blur Sal Canny", blurCannySal);
    imshow("Blur Sal Laplace", blurSalLaplace);
}

void Video::mostrarImagenPimeCannyBlur()
{

    Mat tmp;
    blurCannyPim = imgMedianaPimienta.clone();
    int minCannyTmp = minCannyBlurPim;

    minCannyTmp = minCannyTmp + 50;

    if (minCannyTmp % 2 != 0)
        minImparCannyBlurPim = minCannyTmp;

    Canny(imgMedianaPimienta, blurCannyPim, minCannyTmp, 150, 3);

    Laplacian(imgMedianaPimienta, tmp, CV_16S, 3);
    convertScaleAbs(tmp, blurPimLaplace);
    imshow("Blur Pimienta Canny", blurCannyPim);
    imshow("Blur Pimienta Laplace", blurPimLaplace);
}
