#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <unistd.h>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QDateTime>
#include <QPainter>
#include <QColor>
#include <QMessageBox>
#include <QTimer>
#include <QDesktopWidget>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
#if 0
    test1();
#endif

#if 0
    test2();
#endif

#if 0
    test3();
#endif

#if 0
    test4();
#endif

#if 0
    test5();
#endif

#if 0
    test6();
#endif

#if 0
    test7();
#endif

#if 0
    test8();
#endif

#if 0
    test9();
#endif

#if 0
    test10();
#endif

#if 0
    test11();
#endif

#if 0
    test12();
#endif

#if 0
    test13();
#endif

#if 0
    test14();
#endif

#if 0
    test15();
#endif

#if 0
    test16();
#endif

#if 0
    test17();
#endif

#if 1
    test18();
#endif


    ui->lineEdit_2->setText("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
    ui->lineEdit_2->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit_2->setCursorPosition(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::test1()
{
    QFile file("/opt/softmanager/conf/sys/LocalInstallSoftwareList.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    int i = 0;
    QString curPkgLine;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QString fullname = line.split("\t").at(4);

        qDebug() << "i == " << i++;
        qDebug() << "fullname == " << fullname;
    }
}

void MainWindow::test2()
{
    QByteArray text("228");
    QString b64Str = text.toBase64();
    qDebug() << "b64Str == " << b64Str;
}

void MainWindow::test3()
{
    QString strBuffer;
    QDateTime time;

    time = QDateTime::currentDateTime();

    strBuffer = time.toString("hhmmss");

    QString srcDir = "/home/httc/test/testmod";
//    QString destDir = "/home/httc/test/" + strBuffer;
    QString destDir = "/home/httc/" + strBuffer;

//    QDir dir;
//    bool crtdir = dir.mkdir(destDir);
//    qDebug() << "crtdir == " << crtdir;

    bool copyret = copyDirectoryFiles(srcDir, destDir, true);
//    bool copyret = QFile::copy(srcDir, destDir);


    qDebug() << "copyret == " << copyret;
    qDebug() << "strBuffer == " << strBuffer;


    QString srcFile = srcDir + "/" + "a.txt";
    QString destFile =  destDir + "/" + "a.tmp";
    qDebug() << "srcFile == " << srcFile;
    qDebug() << "destFile == " << destFile;

    bool copyFileRet = copyFileToPath(srcFile, destFile, true);
    qDebug() << "copyFileRet == " << copyFileRet;
}

int MainWindow::test4()
{
    FILE *fp = NULL;
    char buf[10240] = {0};
    char line[1024] = {'\0'};
    int line_count = 0;
    char cmd[1024]= {'\0'};
    snprintf(cmd,sizeof(cmd),"tar -cvf /home/httc/tartest/a.txt.tar.gz /home/httc/tartest/c.txt 2>&1");
//    fp = popen("ls -al","r");
//    fp = popen("tar -cvf /home/httc/tartest/a.txt.tar.gz /home/httc/tartest/c.txt","r");
    fp = popen(cmd,"r");
    if(fp == NULL){
        return 0;
    }
    else
    {
       memset(line, '\0', sizeof(line));
       while(!feof(fp))
       {
           memset(line, '\0', sizeof(line));
            if(fgets(line, 1024, fp))
            {
                if(line[0] == '/n')
                {
                    continue;
                }

                qDebug() << "line == %s" << line;
            }
       }
    }

    char cmderr[1024]= {'\0'};
    QFile::copy("/home/httc/tartest/d.txt", "/home/httc/tartest/c.txt");
    int iCount;
    char sBuf[1024];

    while((iCount=read(STDIN_FILENO, sBuf, 1024))>0)
    {
        if(write(STDOUT_FILENO, sBuf, iCount)!=iCount)
        {
            printf("write eror\n");
            exit(1);
        }
    }


    if(iCount<0)
        printf("read error\n");

        qDebug() << "**********buff == " << buf;


//        fread(buf, 10240, 1, err);
//        printf("buf == %s\n",buf);
//        qDebug() << "buff == " << buf;
//        pclose(fp);

        return 0;
}

void MainWindow::test5()
{
    QString str = "test str";
    int a = 5;
    QString test1 = (a > 3) ? str : QString();
    qDebug() << "test1 == " << test1;
    QString test2 = (a > 7) ? str : QString();
    qDebug() << "test2 == " << test2;
}

void MainWindow::test6()
{
    int i,j;
    QList<int> numbersList;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(i=0;i<10;i++)
    {
        numbersList.append(qrand()%10);
        bool flag=true;
        while(flag)
        {
            for(j=0;j<i;j++)
            {
                if(numbersList[i]==numbersList[j])
                {
                    break;
                }
            }
            if(j<i)
            {
                numbersList[i]=rand()%10;
            }
            if(j==i)
            {
                flag=!flag;
            }
        }
    }
    for(i=0;i<10;i++)
    {
        qDebug()<<numbersList[i];
    }
}

void MainWindow::test7()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int n = 60;
    for(int i=0; i<10; i++)
    {
        int test =qrand() % n;
        qDebug()<<test;
    }
}

void MainWindow::test8()
{
    QString ret = "";
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i = 0; i < 4; i++)
    {
        int c = (qrand() % 2) ? 'a' : 'A';
        ret += static_cast<QChar>(c + qrand() % 26);
    }
    qDebug() << "ret == " << ret;
}

void MainWindow::test9()
{
    QFile file("/home/httc/test/readwrite.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);

    while(1)
    {
        QDateTime current_date_time = QDateTime::currentDateTime();
           QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");

        out << "The current time is: " << current_date << "\n";
        qDebug() << "The current time is: " << current_date << "\n";

//        QTime dieTime = QTime::currentTime().addMSecs(2);
//        while( QTime::currentTime() < dieTime )
//            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }

    file.close();
}

void MainWindow::test10()
{
    QStringList list;
    list << "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9" << "10" << "11" << "12" << "13" << "14" << "15" << "16";
//        qDebug() << "list.left()" << list
}

void MainWindow::test11()
{
    QStringList list;
    qDebug() << "list == " << list;
    list.clear();
    qDebug() << "list == " << list;
    list << "11111" << "22222";
    qDebug() << "list == " << list;
    list.clear();
    qDebug() << "list == " << list;
}

void MainWindow::test12()
{
#if 0 // error
    QString test = "hello";
    unsigned char* test1 = (unsigned char*)test.data();
    std::cout << "test1 == " << test1 << std::endl;
    unsigned char test2[10];
    memcpy(test2,test1,test.size());
    std::cout << "test2 == " << test2 << std::endl;
#endif

    QString test = "hello";
    QByteArray ba = test.toUtf8();
    unsigned char *test1 = (unsigned char *)ba.data();
//    unsigned char *res = (unsigned char *)strdup(ba.constData());
    std::cout << "test1 == " << test1 << std::endl;
}

void MainWindow::test13()
{
    QString list;
    list.append("name1");
    list.append("\n");
    list.append("name2");
    list.append("\n");
    list.append("name3");
    list.append("\n");
    list.append("name4");
    list.append("\n");
//    QMessageBox *box = new QMessageBox(QMessageBox::NoIcon,QString::fromUtf8("警告"),
//                                       QString::fromUtf8("以下软件 平台检查失败\n %1结束安装过程").arg(list));
//    box->setStandardButtons(QMessageBox::NoButton);
//    QTimer::singleShot(2000,box,SLOT(accept())); //也可将accept改为close
//    box->show();

//    QMessageBox *box = new QMessageBox(QMessageBox::NoIcon,QString::fromUtf8("警告"),
//                                       QString::fromUtf8("以下软件 平台检查失败\n %1结束安装过程").arg(list));
//    box->setStandardButtons(QMessageBox::NoButton);
//    QTimer::singleShot(5000,box,SLOT(accept()));
//    box->exec();


//    qDebug() << "delete box";
//    delete box;

    QMessageBox box;
    box.setWindowTitle(QString::fromUtf8("警告"));
    box.setText(QString::fromUtf8("以下软件 平台检查失败\n %1结束安装过程").arg(list));
    box.setStandardButtons(QMessageBox::NoButton);
    QTimer::singleShot(2000,&box,SLOT(accept()));

    box.exec();
}

void MainWindow::test14()
{
    QString cutStr = "D7D6D9647807B0EB0C95C05F23E33507";
    QString str1 = cutStr.mid(0, 8);
    QString str2 = cutStr.mid(8, 4);
    QString str3 = cutStr.mid(12, 4);
    QString str4 = cutStr.mid(16, 16);
    qDebug() << "str1 == " << str1;
    qDebug() << "str2 == " << str2;
    qDebug() << "str3 == " << str3;
    qDebug() << "str4 == " << str4;
}

void MainWindow::test15()
{
    std::srand(std::time(0));
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
        }
//        std::srand(std::time(0));
        double value = double(std::rand()) / RAND_MAX  * 6;
        std::cout << "value == " << value << std::endl;
    }
}

void MainWindow::test16()
{
    QDir dir = QDir::currentPath();

    QStringList filters;
    filters << "*.cpp" << "*.h" << "*.ui";
    dir.setNameFilters(filters);

    QFileInfoList fileInfoList = dir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList)
    {
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;
        qDebug() << "fileInfo.fileName() == " << fileInfo.fileName();

    }
}

void MainWindow::test17()
{
    char *a = new char('a');
    char *b = new char('b');
    char *c = new char('c');

    char **arr = new char*[10] ();
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;
//    for (int i = 0; i < 10; i++)
//    {
//        arr[i] = new char[100] ();
//        arr[i] = "string";
//    }

    for (int j = 0; j < 10; j++)
    {
        if (arr[j])
        {
            qDebug() << "j == " << j;
            qDebug() << "arr[j] == " << *arr[j];
            printf("%d\n",arr[j]);
            printf("%d\n",*arr[j]);
            qDebug() << "j == " << j;
        }
        delete [] arr[j];
    }
    delete [] arr;
}

void MainWindow::test18()
{
    char **arr = new char*[10] ();

    for (int i = 0; i < 10; i++)
    {
//        arr[i] = "string";
        arr[i] = new char[100] {'a','b','c','\0'};

    }

    for (int j = 0; j < 10; j++)
    {
        if (arr[j])
        {
            qDebug() << "j == " << j;
            qDebug() << "arr[j] == " << arr[j];
            qDebug() << "*arr[j] == " << *arr[j];
            printf("%d\n",arr[j]);
            printf("%d\n",*arr[j]);
            qDebug() << "j == " << j << endl;
        }
        delete [] arr[j];
    }
    delete [] arr;
}

#if 0
void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //填充验证码绘制矩形
    painter.fillRect(245, 150, 100, 30, Qt::white);
    painter.setFont(QFont("Comic Sans MS", 12));
    //绘制验证码
//    for(int i = 0; i < 4; i++)
//    {
//        painter.setPen(m_colors[i]);
//        painter.drawText(245 + 25*i, 150, 25, 30, Qt::AlignCenter, QString(m_verification[i]));
//    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    //绘制噪点
    for(int i=0; i<150; i++)
    {
        painter.setPen(Qt::red);
//        painter.setPen(m_colors[i%4]);
        painter.drawPoint(245 + qrand() % 99, 150 + qrand() % 29);
    }
}
#endif

void MainWindow::paintEvent(QPaintEvent *event)
{
    int LineCount=4;
    QColor color(93,116,49);
    QPainter painter(this);
    painter.setBrush(Qt::NoBrush);
    QPen pen(Qt::SolidLine);
    pen.setColor(Qt::black);
    pen.setWidthF(0.5);
    painter.setPen(pen);
    painter.drawPoint(0,0);

    for(int current = 0; current<LineCount; current++)
    {
        for(int i=current;i<(this->width()-current);i+=2) //x
        {
            //            this->getInvertColor(this->x()+i,this->y()+current,color);
            pen.setColor(color);
            painter.setPen(pen);
            painter.drawPoint(i,current);   //draw top
            //                    this->getInvertColor(i+this->x(),this->height()-current-1+this->y(),color);
            pen.setColor(color);
            painter.setPen(pen);
            painter.drawPoint(i,this->height()-current-20); //draw bottom
        }
        for(int i=current;i<(this->height()-current);i+=2) //y
        {
            //            this->getInvertColor(current+this->x(),i+this->y(),color);
            pen.setColor(color);
            painter.setPen(pen);
            painter.drawPoint(current,i);   //draw left
            //            this->getInvertColor(this->width()-current-1+this->x(),i+this->y(),color);
            pen.setColor(color);
            painter.setPen(pen);
            painter.drawPoint(this->width()-current-1,i); //draw right
        }
    }
}

bool MainWindow::getInvertColor(int x, int y, QColor &color)
{
    int ret = m_image.valid(x,y);
    if(ret)
        {
        QRgb rgb = m_image.pixel(x,y);
        color.setRgb(rgb);
        color.setRed(255-color.red() + 20);
        color.setBlue(255-color.blue() +20);
        color.setGreen(255-color.green()+20);
        }
    else
        {
        color.setRed(0 + 30);
        color.setBlue(0 +30);
        color.setGreen(0+30);
        }
    return ret;
}

void MainWindow::showEvent( QShowEvent * event )
{
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
    m_image = QPixmap::grabWindow(QApplication::desktop()->winId()).toImage();
#else
    QScreen *screen = QGuiApplication::primaryScreen();
    m_image = screen->grabWindow(0).toImage();
#endif

}

bool MainWindow::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}

bool MainWindow::copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
//    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

bool MainWindow::lineEditLimitInput(const QString inStr, QString *retStr, int limit)
{
    std::string stdname = inStr.toStdString();

    unsigned int i = 0;
    int addnum = 0;
    while (i<stdname.length())
    {
        unsigned char c = (unsigned char)stdname[i];
        if ((c & 0xfc) == 0xfc)
        {
            addnum = 6;
        }
        else if ((c & 0xf8) == 0xf8)
        {
            addnum = 5;
        }
        else if ((c & 0xf0) == 0xf0)
        {
            addnum = 4;
        }
        else if ((c & 0xe0) == 0xe0)
        {
            addnum = 3;
        }
        else if ((c & 0xc0) == 0xc0)
        {
            addnum = 2;
        }
        else
        {
            addnum = 1;
        }
        i += addnum;
        if (i > limit)
        {
            i-=addnum;
            std::string substr = stdname.substr(0, i);
            *retStr = QString::fromLocal8Bit(substr.c_str());
            return true;
        }
        addnum = 0;
    }
    return false;
}

//void MainWindow::on_lineEdit_textChanged(const QString &arg1)
//{
//    qDebug() << "arg1 == " << arg1;
//    QString text = ui->lineEdit->text().toUtf8();
//    QString retstr;
//    bool ret = lineEditLimitInput(text, &retstr, 16);
//    if (ret)
//    {
//         ui->lineEdit->setText(retstr);
//    }

//}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    qDebug() << "arg1 == " << arg1;
    QString text = ui->lineEdit->text().toUtf8();
    QString retstr;
    bool ret = lineEditLimitInput(text, &retstr, 16);
    if (ret)
    {
         ui->lineEdit->setText(retstr);
    }
}
