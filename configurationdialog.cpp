#include "configurationdialog.h"
#include "ui_configurationdialog.h"

void ConfigurationDialog::updateOKButtonState()
{
    QPushButton *okButton = ui->buttonBox->button(QDialogButtonBox::Ok);
    okButton->setDisabled(ui->lineEdit_P1->text().isEmpty() || ui->lineEdit_P2->text().isEmpty());
}

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);
    updateOKButtonState();
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::setPlayer1Name(const QString &p1name)
{
    ui->lineEdit_P1->setText(p1name);
}

void ConfigurationDialog::setPlayer2Name(const QString &p2name)
{
    ui->lineEdit_P2->setText(p2name);
}

QString ConfigurationDialog::player1Name() const
{
    return ui->lineEdit_P1->text();
}

QString ConfigurationDialog::player2Name() const
{
    return ui->lineEdit_P2->text();
}
