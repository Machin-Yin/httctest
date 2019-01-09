#include "addcompanydialog.h"
#include "ui_addcompanydialog.h"

#include <QFile>
#include <QDateTime>
#include <QMessageBox>
#include <QDebug>

AddCompanyDialog::AddCompanyDialog(QMap<QString, QMap<QString, QString> > *companyMap, CompOperType type, QString currentComp, QWidget *parent) :
    QDialog(parent),
    allCompanyMap(companyMap),
    operType(type),
    changeComp(currentComp),
    ui(new Ui::AddCompanyDialog)
{
    ui->setupUi(this);
    init();
    createCities();
    parseProvince();
    getCurrentTime();
    if (operType == CHANGECOMP)
    {
        setTochangeCompInfo();
    }
    connect(ui->provinceComboBox, SIGNAL(activated(QString)), this, SLOT(parseCity(QString)));
}

AddCompanyDialog::~AddCompanyDialog()
{
    delete ui;
}

void AddCompanyDialog::init()
{
    QRegExp regExp("^[0-9\+()-]{1,16}$");
    ui->mobilePhoneLineEdit->setValidator(new QRegExpValidator(regExp,this));
    ui->telephoneLineEdit->setValidator(new QRegExpValidator(regExp,this));
}

void AddCompanyDialog::parseProvince()
{
    ui->provinceComboBox->addItem("");
    for (int i = 0; i < provinceList.count(); i++)
    {
        ui->provinceComboBox->addItem(provinceList.at(i));
    }
}

void AddCompanyDialog::getCurrentTime()
{
    QDateTime now = QDateTime::currentDateTime();
    QString currentTime = now.toString("yyyy-MM-dd hh:mm:ss");
    ui->dateLabel->setText(currentTime);
}

void AddCompanyDialog::setTochangeCompInfo()
{
    QMap <QString, QMap <QString, QString> >::const_iterator iter = allCompanyMap->find(changeComp);
    QMap <QString, QString>  currentCompanyMap = iter.value();
    ui->contactNameLineEdit->setText(currentCompanyMap.value("contactname"));
    ui->mobilePhoneLineEdit->setText(currentCompanyMap.value("mobilephone"));
    ui->telephoneLineEdit->setText(currentCompanyMap.value("telephone"));
    ui->dateLabel->setText(currentCompanyMap.value("date"));
    ui->companyNameLineEdit->setText(currentCompanyMap.value("companyname"));

    int provinceIndex;
    QString provinceName = currentCompanyMap.value("province");
    for (provinceIndex = 0; provinceIndex < provinceList.count(); provinceIndex++)
    {
        if (provinceList.at(provinceIndex) == provinceName)
            break;
    }

    parseCity(provinceName);
    int cityIndex;
    QString cityName = currentCompanyMap.value("city");
    for (cityIndex = 0; cityIndex < cityList.count(); cityIndex++)
    {
        if (cityList.at(cityIndex) == cityName)
            break;
    }

    ui->provinceComboBox->setCurrentIndex(provinceIndex + 1);
    ui->cityComboBox->setCurrentIndex(cityIndex + 1);
}

void AddCompanyDialog::parseCity(QString proName)
{
    cityList.clear();
    QMap <QString, QStringList>::const_iterator iter = proCityMap.find(proName);
    while (iter != proCityMap.end() && iter.key() == proName) {
        cityList = iter.value();
        ++iter;
    }
    ui->cityComboBox->clear();
    ui->cityComboBox->addItem("");
    for (int i = 0; i < cityList.count(); i++)
    {
        ui->cityComboBox->addItem(cityList.at(i));
    }
}

void AddCompanyDialog::on_sureButton_clicked()
{
    QString contactNameStr = ui->contactNameLineEdit->text();
    QString mobilePhoneStr = ui->mobilePhoneLineEdit->text();
    QString telePhoneStr = ui->telephoneLineEdit->text();
    QString dateStr = ui->dateLabel->text();
    QString companyNameStr = ui->companyNameLineEdit->text();
    QString provinceStr = ui->provinceComboBox->currentText();
    QString cityStr = ui->cityComboBox->currentText();

    if (contactNameStr.isEmpty()
            || mobilePhoneStr.isEmpty()
            || companyNameStr.isEmpty()
            || provinceStr.isEmpty()
            || cityStr.isEmpty())
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("请确保所有必填内容非空")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }

    QMap<QString, QString> addCompanyMap;
    addCompanyMap.insert("contactname", contactNameStr);
    addCompanyMap.insert("mobilephone", mobilePhoneStr);
    addCompanyMap.insert("telephone", telePhoneStr);
    addCompanyMap.insert("date", dateStr);
    addCompanyMap.insert("companyname", companyNameStr);
    addCompanyMap.insert("province", provinceStr);
    addCompanyMap.insert("city", cityStr);

    if (operType == ADDCOMP && allCompanyMap->contains(ui->companyNameLineEdit->text()))
    {
        QMessageBox msg_box;
        msg_box.setWindowTitle(QString::fromUtf8("提示"));
        msg_box.setText((QString::fromUtf8("已存在该厂商信息")));
        msg_box.setStandardButtons(QMessageBox::Ok);
        msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
        msg_box.exec();

        return;
    }

    if (operType == CHANGECOMP)
    {
        if (companyNameStr != changeComp)
        {
            QMessageBox msg_box;
            msg_box.setWindowTitle(QString::fromUtf8("提示"));
            msg_box.setText((QString::fromUtf8("厂商名称不能修改")));
            msg_box.setStandardButtons(QMessageBox::Ok);
            msg_box.setButtonText(QMessageBox::Ok,QString::fromUtf8("确认"));
            msg_box.exec();

            return;
        }
        allCompanyMap->remove(changeComp);
    }
    allCompanyMap->insert(ui->companyNameLineEdit->text(), addCompanyMap);
    emit companyChanged();

    close();
}


void AddCompanyDialog::on_cancelButton_clicked()
{
    close();
}

void AddCompanyDialog::createCities()
{
    provinceList << QString::fromUtf8("北京") << QString::fromUtf8("天津") << QString::fromUtf8("河北省") << QString::fromUtf8("山西省") << QString::fromUtf8("内蒙古自治区") << QString::fromUtf8("辽宁省") << QString::fromUtf8("吉林省") << QString::fromUtf8("黑龙江省") << QString::fromUtf8("上海") << QString::fromUtf8("江苏省") << QString::fromUtf8("浙江省") << QString::fromUtf8("安徽省") << QString::fromUtf8("福建省") << QString::fromUtf8("江西省") << QString::fromUtf8("山东省") << QString::fromUtf8("河南省") << QString::fromUtf8("湖北省") << QString::fromUtf8("湖南省") << QString::fromUtf8("广东省") << QString::fromUtf8("广西壮族自治区") << QString::fromUtf8("海南省") << QString::fromUtf8("重庆") << QString::fromUtf8("四川省") << QString::fromUtf8("贵州省") << QString::fromUtf8("云南省") << QString::fromUtf8("西藏自治区") << QString::fromUtf8("陕西省") << QString::fromUtf8("甘肃省") << QString::fromUtf8("青海省") << QString::fromUtf8("宁夏回族自治区") << QString::fromUtf8("新疆维吾尔自治区") << QString::fromUtf8("香港") << QString::fromUtf8("澳门") << QString::fromUtf8("台湾");

    QStringList beijing;
    beijing << QString::fromUtf8("北京市");

    QStringList tianjin;
    tianjin << QString::fromUtf8("天津市");

    QStringList hebei;
    hebei << QString::fromUtf8("石家庄市") << QString::fromUtf8("唐山市") << QString::fromUtf8("秦皇岛市") << QString::fromUtf8("邯郸市") << QString::fromUtf8("邢台市") << QString::fromUtf8("保定市") << QString::fromUtf8("张家口市") << QString::fromUtf8("承德市") << QString::fromUtf8("沧州市") << QString::fromUtf8("廊坊市") << QString::fromUtf8("衡水市");

    QStringList shanxi;
    shanxi << QString::fromUtf8("太原市") << QString::fromUtf8("大同市") << QString::fromUtf8("阳泉市") << QString::fromUtf8("长治市") << QString::fromUtf8("晋城市") << QString::fromUtf8("朔州市") << QString::fromUtf8("晋中市") << QString::fromUtf8("运城市") << QString::fromUtf8("忻州市") << QString::fromUtf8("临汾市") << QString::fromUtf8("吕梁市");

    QStringList neimeng;
    neimeng << QString::fromUtf8("呼和浩特市") << QString::fromUtf8("包头市") << QString::fromUtf8("乌海市") << QString::fromUtf8("赤峰市") << QString::fromUtf8("通辽市") << QString::fromUtf8("鄂尔多斯市") << QString::fromUtf8("呼伦贝尔市") << QString::fromUtf8("巴彦淖尔市") << QString::fromUtf8("乌兰察布市") << QString::fromUtf8("兴安盟") << QString::fromUtf8("锡林郭勒盟") << QString::fromUtf8("阿拉善盟");

    QStringList liaoning;
    liaoning << QString::fromUtf8("沈阳市") << QString::fromUtf8("大连市") << QString::fromUtf8("鞍山市") << QString::fromUtf8("抚顺市") << QString::fromUtf8("本溪市") << QString::fromUtf8("丹东市") << QString::fromUtf8("锦州市") << QString::fromUtf8("营口市") << QString::fromUtf8("阜新市") << QString::fromUtf8("辽阳市") << QString::fromUtf8("盘锦市") << QString::fromUtf8("铁岭市") << QString::fromUtf8("朝阳市") << QString::fromUtf8("葫芦岛市");

    QStringList jilin;
    jilin << QString::fromUtf8("长春市") << QString::fromUtf8("吉林市") << QString::fromUtf8("四平市") << QString::fromUtf8("辽源市") << QString::fromUtf8("通化市") << QString::fromUtf8("白山市") << QString::fromUtf8("松原市") << QString::fromUtf8("白城市") << QString::fromUtf8("延边朝鲜族自治州");

    QStringList heilongjiang;
    heilongjiang << QString::fromUtf8("哈尔滨市") << QString::fromUtf8("齐齐哈尔市") << QString::fromUtf8("鸡西市") << QString::fromUtf8("鹤岗市") << QString::fromUtf8("双鸭山市") << QString::fromUtf8("大庆市") << QString::fromUtf8("伊春市") << QString::fromUtf8("佳木斯市") << QString::fromUtf8("七台河市") << QString::fromUtf8("牡丹江市") << QString::fromUtf8("黑河市") << QString::fromUtf8("绥化市") << QString::fromUtf8("大兴安岭地区");

    QStringList shanghai;
    shanghai << QString::fromUtf8("上海市");

    QStringList jiangsu;
    jiangsu << QString::fromUtf8("南京市") << QString::fromUtf8("无锡市") << QString::fromUtf8("徐州市") << QString::fromUtf8("常州市") << QString::fromUtf8("苏州市") << QString::fromUtf8("南通市") << QString::fromUtf8("连云港市") << QString::fromUtf8("淮安市") << QString::fromUtf8("盐城市") << QString::fromUtf8("扬州市") << QString::fromUtf8("镇江市") << QString::fromUtf8("泰州市") << QString::fromUtf8("宿迁市");

    QStringList zhejiang;
    zhejiang << QString::fromUtf8("杭州市") << QString::fromUtf8("宁波市") << QString::fromUtf8("温州市") << QString::fromUtf8("嘉兴市") << QString::fromUtf8("湖州市") << QString::fromUtf8("绍兴市") << QString::fromUtf8("金华市") << QString::fromUtf8("衢州市") << QString::fromUtf8("舟山市") << QString::fromUtf8("台州市") <<QString::fromUtf8("丽水市");

    QStringList  anhui;
    anhui << QString::fromUtf8("合肥市") << QString::fromUtf8("芜湖市") << QString::fromUtf8("蚌埠市") << QString::fromUtf8("淮南市") << QString::fromUtf8("马鞍山市") << QString::fromUtf8("淮北市") << QString::fromUtf8("铜陵市") << QString::fromUtf8("安庆市") << QString::fromUtf8("黄山市") << QString::fromUtf8("滁州市") << QString::fromUtf8("阜阳市") << QString::fromUtf8("宿州市") << QString::fromUtf8("六安市") << QString::fromUtf8("亳州市") << QString::fromUtf8("池州市") << QString::fromUtf8("宣城市");

    QStringList fujian;
    fujian << QString::fromUtf8("福州市") << QString::fromUtf8("厦门市") << QString::fromUtf8("莆田市") << QString::fromUtf8("三明市") << QString::fromUtf8("泉州市") << QString::fromUtf8("漳州市") << QString::fromUtf8("南平市") << QString::fromUtf8("龙岩市") << QString::fromUtf8("宁德市");

    QStringList jiangxi;
    jiangxi << QString::fromUtf8("南昌市") << QString::fromUtf8("景德镇市") << QString::fromUtf8("萍乡市") << QString::fromUtf8("九江市") << QString::fromUtf8("新余市") << QString::fromUtf8("鹰潭市") << QString::fromUtf8("赣州市") << QString::fromUtf8("吉安市") << QString::fromUtf8("宜春市") << QString::fromUtf8("抚州市") << QString::fromUtf8("上饶市");

    QStringList shandong;
    shandong << QString::fromUtf8("济南市") << QString::fromUtf8("青岛市") << QString::fromUtf8("淄博市") << QString::fromUtf8("枣庄市") << QString::fromUtf8("东营市") << QString::fromUtf8("烟台市") << QString::fromUtf8("潍坊市") << QString::fromUtf8("济宁市") << QString::fromUtf8("泰安市") << QString::fromUtf8("威海市") << QString::fromUtf8("日照市") << QString::fromUtf8("莱芜市") << QString::fromUtf8("临沂市") << QString::fromUtf8("德州市") << QString::fromUtf8("聊城市") << QString::fromUtf8("滨州市") << QString::fromUtf8("菏泽市");

    QStringList henan;
    henan << QString::fromUtf8("郑州市") << QString::fromUtf8("开封市") << QString::fromUtf8("洛阳市") << QString::fromUtf8("平顶山市") << QString::fromUtf8("安阳市") << QString::fromUtf8("鹤壁市") << QString::fromUtf8("新乡市") << QString::fromUtf8("焦作市") << QString::fromUtf8("濮阳市") << QString::fromUtf8("许昌市") << QString::fromUtf8("漯河市") << QString::fromUtf8("三门峡市") << QString::fromUtf8("南阳市") << QString::fromUtf8("商丘市") << QString::fromUtf8("信阳市") << QString::fromUtf8("周口市") << QString::fromUtf8("驻马店市");

    QStringList hubei;
    hubei << QString::fromUtf8("武汉市") << QString::fromUtf8("黄石市") << QString::fromUtf8("十堰市") << QString::fromUtf8("宜昌市") << QString::fromUtf8("襄阳市") << QString::fromUtf8("鄂州市") << QString::fromUtf8("荆门市") << QString::fromUtf8("孝感市") << QString::fromUtf8("荆州市") << QString::fromUtf8("黄冈市") << QString::fromUtf8("咸宁市") << QString::fromUtf8("随州市") << QString::fromUtf8("恩施土家族苗族自治州");

    QStringList hunan;
    hunan << QString::fromUtf8("长沙市") << QString::fromUtf8("株洲市") << QString::fromUtf8("湘潭市") << QString::fromUtf8("衡阳市") << QString::fromUtf8("邵阳市") << QString::fromUtf8("岳阳市") << QString::fromUtf8("常德市") << QString::fromUtf8("张家界市") << QString::fromUtf8("益阳市") << QString::fromUtf8("郴州市") << QString::fromUtf8("永州市") << QString::fromUtf8("怀化市") << QString::fromUtf8("娄底市") << QString::fromUtf8("湘西土家族苗族自治州");

    QStringList guangdong;
    guangdong << QString::fromUtf8("广州市") << QString::fromUtf8("韶关市") << QString::fromUtf8("深圳市") << QString::fromUtf8("珠海市") << QString::fromUtf8("汕头市") << QString::fromUtf8("佛山市") << QString::fromUtf8("江门市") << QString::fromUtf8("湛江市") << QString::fromUtf8("茂名市") << QString::fromUtf8("肇庆市") << QString::fromUtf8("惠州市") << QString::fromUtf8("梅州市") << QString::fromUtf8("汕尾市") << QString::fromUtf8("河源市") << QString::fromUtf8("阳江市") << QString::fromUtf8("清远市") << QString::fromUtf8("东莞市") << QString::fromUtf8("中山市") << QString::fromUtf8("潮州市") << QString::fromUtf8("揭阳市") << QString::fromUtf8("云浮市");

    QStringList guangxi;
    guangxi << QString::fromUtf8("南宁市") << QString::fromUtf8("柳州市") << QString::fromUtf8("桂林市") << QString::fromUtf8("梧州市") << QString::fromUtf8("北海市") << QString::fromUtf8("防城港市") << QString::fromUtf8("钦州市") << QString::fromUtf8("贵港市") << QString::fromUtf8("玉林市") << QString::fromUtf8("百色市") << QString::fromUtf8("贺州市") << QString::fromUtf8("河池市") << QString::fromUtf8("来宾市") << QString::fromUtf8("崇左市");

    QStringList hainan;
    hainan << QString::fromUtf8("海口市") << QString::fromUtf8("三亚市") << QString::fromUtf8("三沙市") << QString::fromUtf8("儋州市");

    QStringList chongqing;
    chongqing << QString::fromUtf8("重庆市");

    QStringList sichuan;
    sichuan << QString::fromUtf8("成都市") << QString::fromUtf8("自贡市") << QString::fromUtf8("攀枝花市") << QString::fromUtf8("泸州市") << QString::fromUtf8("德阳市") << QString::fromUtf8("绵阳市") << QString::fromUtf8("广元市") << QString::fromUtf8("遂宁市") << QString::fromUtf8("内江市") << QString::fromUtf8("乐山市") << QString::fromUtf8("南充市") << QString::fromUtf8("眉山市") << QString::fromUtf8("宜宾市") << QString::fromUtf8("广安市") << QString::fromUtf8("达州市") << QString::fromUtf8("雅安市") << QString::fromUtf8("巴中市") << QString::fromUtf8("资阳市") << QString::fromUtf8("阿坝藏族羌族自治州") << QString::fromUtf8("甘孜藏族自治州") << QString::fromUtf8("凉山彝族自治州");

    QStringList guizhou;
    guizhou << QString::fromUtf8("贵阳市") << QString::fromUtf8("六盘水市") << QString::fromUtf8("遵义市") << QString::fromUtf8("安顺市") << QString::fromUtf8("毕节市") << QString::fromUtf8("铜仁市") << QString::fromUtf8("黔西南布依族苗族自治州") << QString::fromUtf8("黔东南苗族侗族自治州") << QString::fromUtf8("黔南布依族苗族自治州");

    QStringList yunnan;
    yunnan << QString::fromUtf8("昆明市") << QString::fromUtf8("曲靖市") << QString::fromUtf8("玉溪市") << QString::fromUtf8("保山市") << QString::fromUtf8("昭通市") << QString::fromUtf8("丽江市") << QString::fromUtf8("普洱市") << QString::fromUtf8("临沧市") << QString::fromUtf8("楚雄彝族自治州") << QString::fromUtf8("红河哈尼族彝族自治州") << QString::fromUtf8("文山壮族苗族自治州") << QString::fromUtf8("西双版纳傣族自治州") << QString::fromUtf8("大理白族自治州") << QString::fromUtf8("德宏傣族景颇族自治州") << QString::fromUtf8("怒江傈僳族自治州") << QString::fromUtf8("迪庆藏族自治州");

    QStringList xizang;
    xizang << QString::fromUtf8("拉萨市") << QString::fromUtf8("日喀则市") << QString::fromUtf8("昌都市") << QString::fromUtf8("林芝市") << QString::fromUtf8("山南市") << QString::fromUtf8("那曲地区") << QString::fromUtf8("阿里地区");

    QStringList shan3xi;
    shan3xi << QString::fromUtf8("西安市") << QString::fromUtf8("铜川市") << QString::fromUtf8("宝鸡市") << QString::fromUtf8("咸阳市") << QString::fromUtf8("渭南市") << QString::fromUtf8("延安市") << QString::fromUtf8("汉中市") << QString::fromUtf8("榆林市") << QString::fromUtf8("安康市") << QString::fromUtf8("商洛市");

    QStringList gansu;
    gansu << QString::fromUtf8("兰州市") << QString::fromUtf8("嘉峪关市") << QString::fromUtf8("金昌市") << QString::fromUtf8("白银市") << QString::fromUtf8("天水市") << QString::fromUtf8("武威市") << QString::fromUtf8("张掖市") << QString::fromUtf8("平凉市") << QString::fromUtf8("酒泉市") << QString::fromUtf8("庆阳市") << QString::fromUtf8("定西市") << QString::fromUtf8("陇南市") << QString::fromUtf8("临夏回族自治州") << QString::fromUtf8("甘南藏族自治州");

    QStringList qinghai;
    qinghai << QString::fromUtf8("西宁市") << QString::fromUtf8("海东市") << QString::fromUtf8("海北藏族自治州") << QString::fromUtf8("黄南藏族自治州") << QString::fromUtf8("海南藏族自治州") << QString::fromUtf8("果洛藏族自治州") << QString::fromUtf8("玉树藏族自治州") << QString::fromUtf8("海西蒙古族藏族自治州");

    QStringList ningxia;
    ningxia << QString::fromUtf8("银川市") << QString::fromUtf8("石嘴山市") << QString::fromUtf8("吴忠市") << QString::fromUtf8("固原市") << QString::fromUtf8("中卫市");

    QStringList xinjiang;
    xinjiang << QString::fromUtf8("乌鲁木齐市") << QString::fromUtf8("克拉玛依市") << QString::fromUtf8("吐鲁番市") << QString::fromUtf8("哈密市") << QString::fromUtf8("昌吉回族自治州") << QString::fromUtf8("博尔塔拉蒙古自治州") << QString::fromUtf8("巴音郭楞蒙古自治州") << QString::fromUtf8("阿克苏地区") << QString::fromUtf8("克孜勒苏柯尔克孜自治州") << QString::fromUtf8("喀什地区") << QString::fromUtf8("和田地区") << QString::fromUtf8("伊犁哈萨克自治州") << QString::fromUtf8("塔城地区") << QString::fromUtf8("阿勒泰地区");

    QStringList xianggang;
    xianggang << QString::fromUtf8("香港特别行政区");

    QStringList aomen;
    aomen << QString::fromUtf8("澳门特别行政区");

    QStringList taiwan;
    taiwan << QString::fromUtf8("台湾省");

    proCityMap.insert(QString::fromUtf8("北京"), beijing);
    proCityMap.insert(QString::fromUtf8("天津"), tianjin);
    proCityMap.insert(QString::fromUtf8("河北省"), hebei);
    proCityMap.insert(QString::fromUtf8("山西省"), shanxi);
    proCityMap.insert(QString::fromUtf8("内蒙古自治区"), neimeng);
    proCityMap.insert(QString::fromUtf8("辽宁省"), liaoning);
    proCityMap.insert(QString::fromUtf8("吉林省"), jilin);
    proCityMap.insert(QString::fromUtf8("黑龙江省"), heilongjiang);
    proCityMap.insert(QString::fromUtf8("上海"), shanghai);
    proCityMap.insert(QString::fromUtf8("江苏省"), jiangsu);
    proCityMap.insert(QString::fromUtf8("浙江省"), zhejiang);
    proCityMap.insert(QString::fromUtf8("安徽省"), anhui);
    proCityMap.insert(QString::fromUtf8("福建省"), fujian);
    proCityMap.insert(QString::fromUtf8("江西省"), jiangxi);
    proCityMap.insert(QString::fromUtf8("山东省"), shandong);
    proCityMap.insert(QString::fromUtf8("河南省"), henan);
    proCityMap.insert(QString::fromUtf8("湖北省"), hubei);
    proCityMap.insert(QString::fromUtf8("湖南省"), hunan);
    proCityMap.insert(QString::fromUtf8("广东省"), guangdong);
    proCityMap.insert(QString::fromUtf8("广西壮族自治区"), guangxi);
    proCityMap.insert(QString::fromUtf8("海南省"), hainan);
    proCityMap.insert(QString::fromUtf8("重庆"), chongqing);
    proCityMap.insert(QString::fromUtf8("四川省"), sichuan);
    proCityMap.insert(QString::fromUtf8("贵州省"), guizhou);
    proCityMap.insert(QString::fromUtf8("云南省"), yunnan);
    proCityMap.insert(QString::fromUtf8("西藏自治区"), xizang);
    proCityMap.insert(QString::fromUtf8("陕西省"), shan3xi);
    proCityMap.insert(QString::fromUtf8("甘肃省"), gansu);
    proCityMap.insert(QString::fromUtf8("青海省"), qinghai);
    proCityMap.insert(QString::fromUtf8("宁夏回族自治区"), ningxia);
    proCityMap.insert(QString::fromUtf8("新疆维吾尔自治区"), xinjiang);
    proCityMap.insert(QString::fromUtf8("香港"), xianggang);
    proCityMap.insert(QString::fromUtf8("澳门"), aomen);
    proCityMap.insert(QString::fromUtf8("台湾"), taiwan);

}
