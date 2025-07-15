//21100011007 Fatma Gizem ARI
//hocam programın tum kısımları çalışıyor ama bazen üst üste deneme yapınca kapanıyor.
//tekrar açınca diğerleri de yapılıyor. benim pcden de kaynaklı olabilir emin değilim
//hocam bir de eğer kodlar qt programı olduğu için çalışmazsa lütfen haber edin yanınıza gelip gösteririm.
// ödev puanına çok ihtiyacım var

//mainwindow ekranında kullanıcı sayi girisinde sayıların arasına ',' koyun lütfen

#include "siralamagoruntuleyici.h"
#include <QVBoxLayout>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <QGraphicsRectItem>
#include <QMessageBox>

SiralamaGoruntuleyici::SiralamaGoruntuleyici(QWidget *parent)
    : QWidget(parent), mevcutI(0), mevcutJ(0), mergeL(0), mergeR(0), mergeM(-1), radixDigit(0), heapifyYapiliyor(false), heapifyBoyutu(0) {
    QVBoxLayout *yerlesim = new QVBoxLayout(this);

    algoritmaSecimi = new QComboBox(this);
    algoritmaSecimi->addItems({"Bubble Sort", "Insertion Sort", "Selection Sort", "Merge Sort", "Radix Sort", "Heap Sort"});
    yerlesim->addWidget(algoritmaSecimi);

    sayiGirdisi = new QLineEdit(this);
    yerlesim->addWidget(sayiGirdisi);

    rastgeleButon = new QPushButton("Rastgele Sayılar Üret", this);
    connect(rastgeleButon, &QPushButton::clicked, this, &SiralamaGoruntuleyici::RastgeleSayilarUret);
    yerlesim->addWidget(rastgeleButon);

    kullaniciSayilarButonu = new QPushButton("Girilen Sayıları Kullan", this);
    connect(kullaniciSayilarButonu, &QPushButton::clicked, this, &SiralamaGoruntuleyici::KullaniciSayilariniAl);
    yerlesim->addWidget(kullaniciSayilarButonu);

    siralaButon = new QPushButton("Sıralamayı Başlat", this);
    connect(siralaButon, &QPushButton::clicked, this, &SiralamaGoruntuleyici::SiralamayiBaslat);
    yerlesim->addWidget(siralaButon);

    grafikGorunum = new QGraphicsView(this);
    grafikSahne = new QGraphicsScene(this);
    grafikGorunum->setScene(grafikSahne);
    yerlesim->addWidget(grafikGorunum);

    zamanlayici = new QTimer(this);

    setLayout(yerlesim);
}

void SiralamaGoruntuleyici::RastgeleSayilarUret() {
    sayilar.clear();
    srand(static_cast<unsigned>(time(0)));
    for (int i = 0; i < 20; ++i) {
        sayilar.push_back(rand() % 100 + 10);
    }
    sayiGirdisi->clear();
    mevcutI = 0;
    mevcutJ = 0;
    mergeL = 0;
    mergeR = sayilar.size() - 1;
    mergeM = -1;
    radixDigit = 1;
    heapifyYapiliyor = false;
    heapifyBoyutu = sayilar.size();
    CizimAlaniniYenile();
}

//mainwindow ekranında kullanıcı sayi girisinde sayıların arasına ',' koyun lütfen
void SiralamaGoruntuleyici::KullaniciSayilariniAl() {
    sayilar.clear();
    QStringList girilenSayilar = sayiGirdisi->text().split(",", Qt::SkipEmptyParts);

    for (const QString &sayiStr : girilenSayilar) {
        bool ok;
        int sayi = sayiStr.toInt(&ok);
        if (ok) {
            sayilar.push_back(sayi);
        } else {
            // Geçersiz bir giriş varsa hata mesajı verin
            QMessageBox::warning(this, "Hata", "Geçersiz bir sayı girdiniz.");
            return;
        }
    }

    CizimAlaniniYenile();
}


void SiralamaGoruntuleyici::CizimAlaniniYenile() {
    grafikSahne->clear();
    int genislik = grafikGorunum->width() / sayilar.size();
    for (size_t i = 0; i < sayilar.size(); ++i) {
        int yukseklik = sayilar[i] * 3;
        int x = i * genislik;
        int y = grafikGorunum->height() - yukseklik;

        grafikSahne->addRect(x, y, genislik - 2, yukseklik, QPen(Qt::black), QBrush(Qt::blue));
        QGraphicsTextItem *sayiMetni = grafikSahne->addText(QString::number(sayilar[i]));
        sayiMetni->setDefaultTextColor(Qt::black);
        sayiMetni->setPos(x + genislik / 4, y - 20);
    }
}

void SiralamaGoruntuleyici::SiralamayiBaslat() {

        //durum değişkenlerini sıfırlama
        mevcutI = 0;
        mevcutJ = 0;
        mergeL = 0;
        mergeR = sayilar.size() - 1;
        mergeM = -1;
        radixDigit = 1;
        heapifyYapiliyor = false;
        heapifyBoyutu = sayilar.size();

    QString secilenAlgoritma = algoritmaSecimi->currentText();
    disconnect(zamanlayici, nullptr, nullptr, nullptr);

    if (secilenAlgoritma == "Bubble Sort") {
        connect(zamanlayici, &QTimer::timeout, this, &SiralamaGoruntuleyici::bubbleSortStep);
    } else if (secilenAlgoritma == "Insertion Sort") {
        connect(zamanlayici, &QTimer::timeout, this, &SiralamaGoruntuleyici::insertionSortStep);
    } else if (secilenAlgoritma == "Selection Sort") {
        connect(zamanlayici, &QTimer::timeout, this, &SiralamaGoruntuleyici::selectionSortStep);
    } else if (secilenAlgoritma == "Merge Sort") {
        connect(zamanlayici, &QTimer::timeout, this, &SiralamaGoruntuleyici::mergeSortStep);
    } else if (secilenAlgoritma == "Radix Sort") {
        connect(zamanlayici, &QTimer::timeout, this, &SiralamaGoruntuleyici::radixSortStep);
    } else if (secilenAlgoritma == "Heap Sort") {
        connect(zamanlayici, &QTimer::timeout, this, &SiralamaGoruntuleyici::heapSortStep);
    }
    zamanlayici->start(100);
}

void SiralamaGoruntuleyici::bubbleSortStep() {
    if (mevcutI < sayilar.size()) {
        if (mevcutJ < sayilar.size() - mevcutI - 1) {
            if (sayilar[mevcutJ] > sayilar[mevcutJ + 1]) {
                std::swap(sayilar[mevcutJ], sayilar[mevcutJ + 1]);
            }
            mevcutJ++;
        } else {
            mevcutJ = 0;
            mevcutI++;
        }
    } else {
        zamanlayici->stop();
    }
    CizimAlaniniYenile();
}


void SiralamaGoruntuleyici::insertionSortStep() {
    if (mevcutI < sayilar.size()) {
        int anahtar = sayilar[mevcutI];
        int j = mevcutI - 1;
        while (j >= 0 && sayilar[j] > anahtar) {
            sayilar[j + 1] = sayilar[j];
            j--;
        }
        sayilar[j + 1] = anahtar;
        mevcutI++;
    } else {
        zamanlayici->stop();
    }
    CizimAlaniniYenile();
}

void SiralamaGoruntuleyici::selectionSortStep() {
    if (mevcutI < sayilar.size()) {
        int minIndex = mevcutI;
        for (int j = mevcutI + 1; j < sayilar.size(); ++j) {
            if (sayilar[j] < sayilar[minIndex]) {
                minIndex = j;
            }
        }
        std::swap(sayilar[mevcutI], sayilar[minIndex]);
        mevcutI++;
    } else {
        zamanlayici->stop();
    }
    CizimAlaniniYenile();
}

void SiralamaGoruntuleyici::mergeSortStep() {
    if (mergeM == -1) {
        if (mergeL < mergeR) {
            int m = mergeL + (mergeR - mergeL) / 2;
            mergeSort(mergeL, m);
            mergeSort(m + 1, mergeR);
            merge(mergeL, m, mergeR);
        }
        zamanlayici->stop();
    }
    CizimAlaniniYenile();
}

void SiralamaGoruntuleyici::mergeSort(int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(l, m);
        mergeSort(m + 1, r);
        merge(l, m, r);
    }
}

void SiralamaGoruntuleyici::merge(int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) {
        L[i] = sayilar[l + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = sayilar[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            sayilar[k] = L[i];
            i++;
        } else {
            sayilar[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        sayilar[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        sayilar[k] = R[j];
        j++;
        k++;
    }
}
void SiralamaGoruntuleyici::radixSortStep() {
    if (radixDigit > maxDigitCount) {
        zamanlayici->stop();
        return;
    }

    std::vector<int> output(sayilar.size());
    int count[10] = {0};

    for (int num : sayilar) {
        int digit = (num / radixDigit) % 10;
        count[digit]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = sayilar.size() - 1; i >= 0; i--) {
        int digit = (sayilar[i] / radixDigit) % 10;
        output[count[digit] - 1] = sayilar[i];
        count[digit]--;
    }

    sayilar = output;
    radixDigit *= 10;
    CizimAlaniniYenile();
}
void SiralamaGoruntuleyici::heapSortStep() {
    if (!heapifyYapiliyor) {
        for (int i = heapifyBoyutu / 2 - 1; i >= 0; i--) {
            heapify(heapifyBoyutu, i);
        }
        heapifyYapiliyor = true;
    }

    if (heapifyBoyutu > 1) {
        std::swap(sayilar[0], sayilar[heapifyBoyutu - 1]);
        heapifyBoyutu--;
        heapify(heapifyBoyutu, 0);
    } else {
        zamanlayici->stop();
    }
    CizimAlaniniYenile();
}

void SiralamaGoruntuleyici::heapify(int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && sayilar[left] > sayilar[largest]) {
        largest = left;
    }

    if (right < n && sayilar[right] > sayilar[largest]) {
        largest = right;
    }

    if (largest != i) {
        std::swap(sayilar[i], sayilar[largest]);
        heapify(n, largest);
    }
}
