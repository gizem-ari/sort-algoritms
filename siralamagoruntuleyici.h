#ifndef SIRALAMAGORUNTULEYICI_H
#define SIRALAMAGORUNTULEYICI_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTimer>
#include <vector>

class SiralamaGoruntuleyici : public QWidget {
    Q_OBJECT

public:
    explicit SiralamaGoruntuleyici(QWidget *parent = nullptr);

private slots:
    void RastgeleSayilarUret();
    void KullaniciSayilariniAl();
    void SiralamayiBaslat();
    void bubbleSortStep();
    void insertionSortStep();
    void selectionSortStep();
    void mergeSortStep();
    void radixSortStep();
    void heapSortStep();

private:
    void CizimAlaniniYenile();
    void mergeSort(int l, int r);
    void merge(int l, int m, int r);
    void heapify(int n, int i);

    std::vector<int> sayilar;
    QGraphicsView *grafikGorunum;
    QGraphicsScene *grafikSahne;
    QComboBox *algoritmaSecimi;
    QLineEdit *sayiGirdisi;
    QPushButton *rastgeleButon;
    QPushButton *siralaButon;
    QPushButton *kullaniciSayilarButonu;
    QTimer *zamanlayici;

    // Sıralama için kontrol değişkenleri
    int mevcutI;
    int mevcutJ;
    int mergeL, mergeR, mergeM;
    int radixDigit;
    bool heapifyYapiliyor;
    int heapifyBoyutu;
    int maxDigitCount;
};

#endif // SIRALAMAGORUNTULEYICI_H
