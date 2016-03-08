#include "ScaleSave.h"

int CScaleSave::m_count = 0;

CScaleSave::CScaleSave(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);
    m_curSelect = -1;
    tb_info->setSelectionBehavior( QAbstractItemView::SelectRows);
    Load_info_from_ini();
    m_count++;
}


void CScaleSave::on_tb_info_cellClicked(int row,int col)
{
    m_curSelect = row;
    le_name->setText(tb_info->item(m_curSelect,0)->text());
    le_unit->setText(tb_info->item(m_curSelect,1)->text());
    le_len->setText(tb_info->item(m_curSelect,2)->text());

}

void CScaleSave::on_btn_del_clicked()
{
    del_index = scale_list[m_curSelect];
    QVector<CS>::iterator it = scale_list.begin();
    for(;it != scale_list.end();it++) {
        if(it->countCopy == del_index.countCopy) {
            scale_list.erase(it);
             break;
        }
    }
    tb_info->removeRow(m_curSelect);
}

void CScaleSave::on_btn_mod_clicked()
{

    CS sInfo;
    sInfo.m_name = le_name->text();
    sInfo.m_unit = le_unit->text();
    sInfo.m_len = le_len->text();
    del_index = scale_list[m_curSelect];

    QVector<CS>::iterator it = scale_list.begin();
    for(;it != scale_list.end();it++) {
        if(it->countCopy == del_index.countCopy) {
            scale_list.erase(it);
             break;
        }
    }

    scale_list.insert(m_curSelect,sInfo);

    tb_info->item(m_curSelect,0)->setText(le_name->text());
    tb_info->item(m_curSelect,1)->setText(le_unit->text());
    tb_info->item(m_curSelect,2)->setText(le_len->text());
}

void CScaleSave::add_stuInfo_2_ui(CS &Info)
{
    int rowNumber = tb_info->rowCount();

    tb_info->insertRow(rowNumber);

    QTableWidgetItem *nameItem = new QTableWidgetItem;
    nameItem->setText(Info.m_name);

    QTableWidgetItem *unitItem = new QTableWidgetItem;
    unitItem->setText(Info.m_unit);

    QTableWidgetItem *lentItem = new QTableWidgetItem;
    lentItem->setText(Info.m_len);

    tb_info->setItem(rowNumber,0,nameItem);
    tb_info->setItem(rowNumber,1,unitItem);
    tb_info->setItem(rowNumber,2,lentItem);
}

void CScaleSave::Load_info_from_ini()
{
    // 从ini文件读取用户数据
    QSettings fd("Scale.ini",QSettings::IniFormat);

    // 读取所有的组名
    QStringList groupList = fd.childGroups();
    QStringList::iterator it = groupList.begin();

    for(;it != groupList.end();it++)
    {
        CS sInfo;
        sInfo.m_name = fd.value(QString("%1/Name").arg(*it),tr("noname")).toString();
        sInfo.m_unit = fd.value(QString("%1/Unit").arg(*it),tr("20")).toString();
        sInfo.m_len = fd.value(QString("%1/Length").arg(*it),tr("20")).toString();

        // 插入链表
        scale_list.push_back(sInfo);
        // 显示界面
        add_stuInfo_2_ui(sInfo);
    }
}

void CScaleSave::on_btn_add_clicked()
{

    CS sInfo;
    sInfo.m_name = le_name->text();
    sInfo.m_unit = le_unit->text();
    sInfo.m_len = le_len->text();

    // 添加进缓存
    scale_list.push_back(sInfo);
    // 显示在界面
    add_stuInfo_2_ui(sInfo);

    // 清空输入框
    le_name->setText("");
    le_unit->setText("");
    le_len->setText("");
}

void CScaleSave::on_btn_saveinfo_clicked()
{
    qDebug() << __func__ <<" " <<scale_list.size();
    QString groupN;
    QSettings fd("Scale.ini",QSettings::IniFormat);
    fd.clear();
    QVector<CS>::iterator it = scale_list.begin();
    for(;it != scale_list.end();it++)
    {
        qDebug() << "test" << __LINE__;
        groupN =QString("Scale-%1").arg(it->countCopy);
        fd.setValue(QString("%1/Name").arg(groupN),it->m_name);
        fd.setValue(QString("%1/Unit").arg(groupN),it->m_unit);
        fd.setValue(QString("%1/Length").arg(groupN),it->m_len);
    }

}

void CScaleSave::on_btn_ok_clicked()
{
    accept();
}
void CScaleSave::on_btn_cancel_clicked()
{
    reject();
}

