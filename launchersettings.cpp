﻿#include "launchersettings.h"
#include "ui_launchersettings.h"

launcherSettings::launcherSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::launcherSettings)
{
    qDebug() << "launcherSettings::launcherSettings: constructor";
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags().operator ^=(Qt::WindowContextHelpButtonHint));
}

launcherSettings::~launcherSettings()
{
    delete ui;
}

// Отправляем данные
void launcherSettings::on_buttonBox_accepted() {
    qDebug() << "launcherSettings::on_buttonBox_accepted: start";

    // Собираем данные для отправки
    settings.style = ui->styleBox->currentIndex();
    settings.documentMode = ui->documentMode->isChecked();
    settings.launch = ui->launchBox->currentIndex();

    // Отправляем данные
    emit sendData(settings);
}

// Принимаем данные
void launcherSettings::reciveData(Settings launcherS) {
    qDebug() << "launcherSettings::reciveData: start";

    // Применяем изменения
    settings = launcherS;
    ui->styleBox->setCurrentIndex(settings.style);
    ui->documentMode->setChecked(settings.documentMode);
    ui->launchBox->setCurrentIndex(settings.launch);
    this->open();
}
