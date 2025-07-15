#include "siralamagoruntuleyici.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // SiralamaGoruntuleyici penceresi oluştur
    SiralamaGoruntuleyici pencere;
    pencere.setWindowTitle("Sıralama Görselleştirici");
    pencere.resize(800, 600); // Pencerenin boyutunu ayarla
    pencere.show();           // Pencereyi göster

    return app.exec();
}
