#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <iostream>
#include <unistd.h>
#include <fstream>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
#pragma pack(1)

typedef int LONG;
typedef unsigned short WORD;
typedef unsigned int DWORD;
int BufferSizeControlador;
char* FileBuffer; int BufferSize;
typedef struct tagBITMAPFILEHEADER {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    fileName("")
{
    ui->setupUi(this);
    QPixmap bkgnd(":/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QImage Logo(":/flecha.png");
    ui->L_flecha->setPixmap(QPixmap::fromImage(Logo));

    QPixmap pix(":/open_file.png");
    pix = pix.scaled(ui->b_fileOpen->size(),Qt::IgnoreAspectRatio);
    QIcon icon(pix);
    ui->b_fileOpen->setIcon(icon);
    ui->b_fileOpen->setIconSize(pix.size());

    ui->LE_imagePath->setText("");
    ui->LE_outputPath->setText("");
    ui->L_output->setText("Favor seleccione la \nprofundidad y haga \nclick en \"Procesar\"");
    ui->L_image->setText("Favor seleccione la \nimagen a procesar");
    ui->b_exportarImagen->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b_fileOpen_clicked()
{
    //#define Picture "ReadInPicture2.bmp"
    fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/Users/adrivega/Documents/UNITEC/2015-3 jul - sept/Estructura de Datos/P2-QuadTree/Imagenes", tr("Image Files (*.bmp)"));
    //fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home/isaac/Desktop/Trabajos/Estructura/proyectos/QuadTree/MapaDeContornos/Imagenes", tr("Image Files (*.bmp)"));
    ui->LE_imagePath->setText(fileName.split("/")[9]);
    ui->L_image->setText("");
    QImage Raw(fileName);
    ui->L_image->setPixmap(QPixmap::fromImage(Raw));
    //#define Picture "ReadInPicture2.bmp"

    //if (!FillAndAllocate(FileBuffer, fileName.toUtf8().constData(), rows, cols, BufferSize)){cout << "File read error" << endl; cout<<"Return 0";}
    if (!FillAndAllocate(FileBuffer, fileName.toUtf8().constData(), rows, cols, BufferSize)){cout << "File read error" << endl; cout<<"Return 0";}

    cout << "Rows: " << rows << " Cols: " << cols << endl;
    RGB_Allocate(reds);
    RGB_Allocate(greens);
    RGB_Allocate(blues);
    GetPixlesFromBMP24( reds,  greens, blues,BufferSize, rows, cols, FileBuffer);

}

void MainWindow::on_b_procesarImagen_clicked()
{
    if(ui->LE_imagePath->text() == "" || ui->sB_profundidad->value() == -1){
        QMessageBox msgbox;
        msgbox.setBaseSize(QSize(310, 150));
        msgbox.setWindowTitle("ERROR");
        msgbox.setText("Favor asegurese que haya \nseleccionado la imagen a procesar \ny la profundidad deseada.");
        msgbox.exec();
    }else{
        //ui->sB_profundidad->setValue(-1);
        ui->L_output->setText("");
        ui->b_exportarImagen->setEnabled(true);
        ui->LE_outputPath->setText(fileName.split("/")[9].split(".")[0].append("Output.bmp"));
        //lecturaImagen();
        //procesarImagen();
        //para agregar la imagen procesada al label de output
        //QImage Raw(fileName);
        //ui->L_output->setPixmap(QPixmap::fromImage(Raw));

    }

}

void MainWindow::on_b_exportarImagen_clicked()
{
#define WriteOutFile "Extracted.bmp"
WriteOutBmp24(FileBuffer,  WriteOutFile,BufferSize);
cout<<BufferSize<<endl;

}

void MainWindow::crearMatrizRGB(unsigned char** &matriz)
{
    matriz = new unsigned char*[rows];
    for(int i = 0; i < rows; i++){
        matriz[i] = new unsigned char[cols];
    }
}

void MainWindow::printMatrizRGB(unsigned char** &matriz)
{
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cout << matriz[i][j] << "\t";
        }
        cout << endl;
    }
}

void MainWindow::procesarImagen()
{
    char* FileBuffer; int BufferSize;

    //#define Picture "Ness.bmp"
    //if (!FillAndAllocate(FileBuffer, Picture, rows, cols, BufferSize)){}
    if (!FillAndAllocate(FileBuffer, fileName.toUtf8().constData(), rows, cols, BufferSize)){}

    RGB_Allocate(reds);
    RGB_Allocate(greens);
    RGB_Allocate(blues);
    GetPixlesFromBMP24( reds,  greens, blues,BufferSize, rows, cols, FileBuffer);
    QString outFileName = QFileDialog::getSaveFileName(this,tr("Save Image"), "/Users/adrivega/Documents/UNITEC/2015-3 jul - sept/Estructura de Datos/P2-QuadTree/Imagenes", tr("Image Files (*.bmp)"));
    #define WriteOutFile outFileName.toUtf8().constData()

    WriteOutBmp24(FileBuffer,  WriteOutFile,BufferSize);
    ui->L_image->setText("");
    QImage Raw(outFileName.toUtf8().constData());
    ui->L_output->setPixmap(QPixmap::fromImage(Raw));
}

/*void MainWindow::ColorTest() {
//     Makes Red Rectangle in top left corner. Rectangle stretches to right alot
    for (int i = rows / 10; i < 3 * rows / 10; i++)
        for (int j = cols / 10; j < 7 * cols / 10; j++)
            reds[i][j] = 0xFF;

// Makes small green box in bottom right
    for (int i = 8 * rows / 10; i < rows; i++)
        for (int j = 8 * cols / 10; j < cols; j++){
            greens[i][j] = 0x00;
            reds[i][j] = 0x00;
        }

// Makes White box in the middle of the screeene
    for (int i = rows * 4 / 10; i < rows * 6 / 10; i++)
        for (int j = cols * 4 / 10; j < cols * 6 / 10; j++) {
            greens[i][j] = 0xFF;
            reds[i][j] = 0x00;
            blues[i][j] = 0xFF;
        }

// Blue verticle rectangle bottom left
    for (int i = rows * 6 / 10; i < rows; i++)
        for (int j = cols * 0; j < cols * 1 / 10; j++)
            blues[i][j] = 0xFF;

    for (int i = 0; i < rows; ++i){
        reds[i][cols/2] = 0xFF;
        greens[i][cols/2] = 0x00;
        blues[i][cols/2] = 0xFF;
    }
    for (int i = 0; i < cols; ++i){
        reds[rows/2][i] = 0xFF;
        greens[rows/2][i] = 0x00;
        blues[rows/2][i] = 0xFF;
    }
}
*/

void MainWindow::RGB_Allocate(unsigned char**& dude) {
    dude = new unsigned char*[rows];
    for (int i = 0; i < rows; i++)
        dude[i] = new unsigned char[cols];
}

bool MainWindow::FillAndAllocate(char*& buffer, const char* Picture, int& rows, int& cols, int& BufferSize) { //Returns 1 if executed sucessfully, 0 if not sucessfull
    std::ifstream file(Picture);

    if (file) {
        file.seekg(0, std::ios::end);
        std::streampos length = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer = new char[length];
        file.read(&buffer[0], length);

        PBITMAPFILEHEADER file_header;
        PBITMAPINFOHEADER info_header;

        file_header = (PBITMAPFILEHEADER) (&buffer[0]);
        info_header = (PBITMAPINFOHEADER) (&buffer[0] + sizeof(BITMAPFILEHEADER));
        rows = info_header->biHeight;
        cols = info_header->biWidth;
        BufferSize = file_header->bfSize;
        return 1;
    }
    else {
        cout << "File: " << Picture << " doesn't Exist!" << endl;
        return 0;
    }
}


void MainWindow::GetPixlesFromBMP24(unsigned char** reds, unsigned char** greens, unsigned char** blues, int end, int rows, int cols, char* FileReadBuffer) { // end is BufferSize (total size of file)
    int count = 1;
int extra = cols % 4; // The nubmer of bytes in a row (cols) will be a multiple of 4.
    for (int i = 0; i < rows; i++){
count += extra;
    for (int j = cols - 1; j >= 0; j--)
        for (int k = 0; k < 3; k++) {
                switch (k) {
                case 0:
                    reds[i][j] = FileReadBuffer[end - count++];
                    break;
                case 1:
                    greens[i][j] = FileReadBuffer[end - count++];
                    break;
                case 2:
                    blues[i][j] = FileReadBuffer[end - count++];
                    break;
                }
            }
            }
}

void MainWindow::WriteOutBmp24(char* FileBuffer, const char* NameOfFileToCreate, int BufferSize) {
    std::ofstream write(NameOfFileToCreate);
    if (!write) {
        cout << "Failed to write " << NameOfFileToCreate << endl;
        return;
    }
    int count = 1;
    int extra = cols % 4; // The nubmer of bytes in a row (cols) will be a multiple of 4.
    for (int i = 0; i < rows; i++){
        count += extra;
        for (int j = cols - 1; j >= 0; j--)
            for (int k = 0; k < 3; k++) {
                switch (k) {
                case 0: //reds
                    FileBuffer[BufferSize - count] = reds[i][j];
                    break;
                case 1: //green
                    FileBuffer[BufferSize - count] = greens[i][j];
                    break;
                case 2: //blue
                    FileBuffer[BufferSize - count] = blues[i][j];
                    break;
                }
                count++;
            }
            }
    write.write(FileBuffer, BufferSize);
}


void MainWindow::on_all_clicked()
{
    char* FileBuffer; int BufferSize;

    #define Picture "Ness.bmp"
    //if (!FillAndAllocate(FileBuffer, Picture, rows, cols, BufferSize)){}
    if (!FillAndAllocate(FileBuffer, fileName.toUtf8().constData(), rows, cols, BufferSize)){}

    RGB_Allocate(reds);
    RGB_Allocate(greens);
    RGB_Allocate(blues);
    GetPixlesFromBMP24( reds,  greens, blues,BufferSize, rows, cols, FileBuffer);
    #define WriteOutFile "newone.bmp"
    WriteOutBmp24(FileBuffer,  WriteOutFile,BufferSize);




}
