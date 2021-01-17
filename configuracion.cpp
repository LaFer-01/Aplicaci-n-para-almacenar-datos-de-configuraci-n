#include "configuracion.h"
#include "ui_configuracion.h"

#include <QDebug>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QMessageBox>

Configuracion::Configuracion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Configuracion)
{
    ui->setupUi(this);
}

Configuracion::~Configuracion()
{
    delete ui;
}


void Configuracion::on_btnGuardar_clicked()
{
    //Obtener la informacion de la GUI
    QString direccion = ui->inDireccion->text();
    int puerto = ui->inPuerto->value();

    bool caja1 = ui->chkCaja1->isChecked();
    bool caja2 = ui->chkCaja2->isChecked();
    bool caja3 = ui->chkCaja3->isChecked();
    bool caja4 = ui->chkCaja4->isChecked();

    //Verificar si la informacion recopilada es correcta

    qDebug()<< direccion <<puerto <<caja1 <<caja2<<caja3 <<caja4;

    //Establecer un nombre de archivo temporal en el directorio "home" del usuario
    QString temporal = QDir::home().absolutePath() + "/sin_titulo.cfg";

    qDebug()<<temporal;

    //Abrir cuadro de dialogo para colocar el nombre del archivo
    QString nombreArchivo = QFileDialog::getSaveFileName(this, "Guardar configuracion",
                                                         temporal,
                                                         ("Archivo de Configuracion (*.cfg)"));

    //Creando el objeto QFile
    QFile archivo(nombreArchivo);

    //Verificar si se puede escribir sobre el nombre
    if(archivo.open(QFile::WriteOnly | QFile::Truncate)){
        //Crear el objeto QTextStream
        QTextStream out(&archivo);
        //Escribiendo datos en el archivo
        out << "Servidor = " <<direccion << '\n';
        out << "Puerto = "   <<puerto << '\n';
        out << "Caja 1 = "  <<caja1 << '\n';
        out << "Caja 2 = "  <<caja2 << '\n';
        out << "Caja 3:"  <<caja3 << '\n';
        out << "Caja 4:"  <<caja4 << '\n';


        //cerrar archivo
        archivo.close();
    }
}

void Configuracion::on_btnAbrir_clicked()
{
    QString archivo = QFileDialog::getOpenFileName(this, "Abrir archivo",
                                                   "C:", "Config (*.cfg)");
    QFile file(archivo);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QStringList datos;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString linea = in.readLine();
        datos << linea;
    }

    QStringList partes = datos[0].split("=");
    QStringList data1 = datos[1].split("=");
    QStringList data2 = datos[2].split("=");
    QStringList data3 = datos[3].split("=");
    QStringList data4 = datos[4].split("=");
    QStringList data5 = datos[5].split("=");

    ui->inDireccion->setText(partes[1]);
    ui->inPuerto->setValue(data1[1].toInt());
    ui->chkCaja1->setChecked(data2[1].toInt());
    ui->chkCaja2->setChecked(data3[1].toInt());
    ui->chkCaja3->setChecked(data4[1].toInt());
    ui->chkCaja4->setChecked(data5[1].toInt());

    file.close();

}
