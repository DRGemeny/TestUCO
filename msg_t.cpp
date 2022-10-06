#include "msg_t.h"
#include "myclient.h"

void msg_t::ShowMesTextEdit(QTextEdit *tE)
{
   QString str;
   quint16 word;
   if((numMes == 3) || (numMes == 5))
       str = "          -->";
   if((numMes == 4) || (numMes == 6))
       str = "         <--";
   str +=( QString("Mes=%8; Addr1=%1; Addr2=%2; Addr3=%3; RegAddr=%4; Length=%5; Tag=%6; CRC=%7;").
          arg(dst1,4,16,QChar('0')).
          arg(dst2,4,16,QChar('0')).
          arg(dst3,4,16,QChar('0')).
          arg(addrReg,4,16,QChar('0')).
          arg(dataLen,4,16,QChar('0')).
          arg(tag,4,16,QChar('0')).
          arg(crc,4,16,QChar('0')).
          arg(numMes,4,16,QChar('0'))).toUpper();
   if ((numMes == 6 ) || (numMes == 3))
   {
       str += "\n";
       foreach(word, data)
           str += (QString("               0x%1\n").arg(word,4,16,QChar('0')).toUpper());
   }
   str.chop(1);
   tE->append(str);

    /*   QString str ;
   quint16 word;   
   foreach(word, listPac)
       str += (QString("0x%1\n").arg(word,4,16,QChar('0')).toUpper());
   tE->append(str);
*/
}
void msg_t::ShowMesTextEditMas(QTextEdit *tE)
{
   QString str ;
   quint16 word;
   foreach(word, listPac)
       str += (QString("0x%1\n").arg(word,4,16,QChar('0')).toUpper());
   tE->append(str);
}


msg_t::msg_t (QByteArray *ba)
{
    bool ok;
    QList <QByteArray> qbaList = ba->split('\n');
    int len = qbaList.length();
    quint16 *buf = new quint16[len];
    for (int i = 0; i < len-1; i++)
        buf[i] = qbaList[i].toUShort(&ok, 16);
    numMes = buf[0];
    dst1 = (buf[1] & 0xF000) >> 12;
    dst2 = (buf[1] & 0x01F0) >> 4;
    dst3 = buf[1] & 0x000F;
    addrReg = buf[2] & 0x00FF;
    type =  buf[2] >> 12 ;
    dataLen = buf[3];
    reserve = buf[4];
    crc = buf[len - 2];
    if (numMes == 6){
        for (int i = 0 ; i < dataLen; i++)
            data.append(buf[i+6]);
    }
    masPac = new unsigned short [len-1];
    for(int i = 0; i < len-1; i++)
    {
        masPac[i] = buf[i];
        listPac.append(buf[i]);
    }
    delete[] buf;
//    int crc1 = CRC16(reinterpret_cast<unsigned char*>(masPac), static_cast<unsigned short>((len * 2) - 2));
  //  if (crc != crc1) ok = -1;
//    ok = 0;
}


msg_t::msg_t (unsigned short numMes1, unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
              unsigned short addrReg1, msgType type1, QList<unsigned short> data1)
{
    numMes = numMes1;
    dst1 = addrl1;
    dst2 = addrl2;
    dst3 = addrl3;
    addrReg = addrReg1;
    type = type1;
    dataLen = static_cast<unsigned short> (data1.length());
    data = data1;

    int lengthPack;
    if (type == msgType::write) lengthPack = dataLen + 6;
    else lengthPack = 6;
    masPac = new unsigned short [lengthPack];
    listPac.append(static_cast<unsigned short>((dst1 << 12) | (dst2 << 4) | dst3));
    listPac.append (static_cast<unsigned short>((type << 12) | addrReg));
    listPac.append(dataLen);
    listPac.append(tag);
    listPac.append(0x0000);
    if (type == msgType::write) {
        for (int i = 0; i < dataLen; i++) {
            listPac.append(data[i]);
        }
    }
    for (int i = 0; i < lengthPack-1; i++)
        masPac[i] = listPac[i];
//    crc = CRC16(reinterpret_cast<unsigned char*>(masPac), static_cast<unsigned short>((lengthPack * 2) - 2));
  //  masPac[lengthPack - 1] = crc;
    //listPac.append(crc);
}

msg_t::msg_t (unsigned short numMes1, unsigned short addrl1, unsigned short addrl2, unsigned short addrl3,
              unsigned short addrReg1, msgType type1, unsigned short dataLenMsg, QList<unsigned short> data1)
{
    numMes = numMes1;
    dst1 = addrl1;
    dst2 = addrl2;
    dst3 = addrl3;
    addrReg = addrReg1;
    type = type1;
    dataLen = dataLenMsg;
    data = data1;

    int lengthPack;
    if (type == msgType::write) lengthPack = dataLen + 6;
    else lengthPack = 6;
    masPac = new unsigned short [lengthPack];
    listPac.append(static_cast<unsigned short>((dst1 << 12) | (dst2 << 4) | dst3));
    listPac.append (static_cast<unsigned short>((type << 12) | addrReg));
    listPac.append(dataLen);
    listPac.append(tag);
    listPac.append(0x0000);
    if (type == msgType::write) {
        for (int i = 0; i < dataLen; i++) {
            listPac.append(data[i]);
        }
    }
    for (int i = 0; i < lengthPack-1; i++)
        masPac[i] = listPac[i];
    crc = CRC16(reinterpret_cast<unsigned char*>(masPac), static_cast<unsigned short>((lengthPack * 2) - 2));
    masPac[lengthPack - 1] = crc;
    listPac.append(crc);
}

msg_t::msg_t (int len, unsigned short* buf)
{
    numMes = buf[0];
    dst1 = (buf[1] & 0xF000) >> 12;
    dst2 = (buf[1] & 0x01F0) >> 4;
    dst3 = buf[1] & 0x000F;
    addrReg = buf[2] & 0x00FF;
    type =  buf[2] >> 12 ;
    dataLen = buf[3];
    reserve = buf[4];
//    crc = buf[len - 1];
    if (dataLen != 0) {
        for (int i = 5 ; i < len; i++)
            data.append(buf[i]);
    }
    masPac = new unsigned short [len];
    for(int i = 0; i < len; i++)
    {
        masPac[i] = buf[i];
        listPac.append(buf[i]);
    }
//    int crc1 = CRC16(reinterpret_cast<unsigned char*>(masPac), static_cast<unsigned short>((len * 2) - 2));
  //  if (crc != crc1) ok = -1;
//    ok = 0;
}



QByteArray msg_t::toByteArray()
{
    QByteArray outPacketC03;
    unsigned short lengthData = static_cast<unsigned short>(this->dataLen);
    outPacketC03.append(QString("0x%1\n").arg(numMes,4,16,QChar('0')));
    outPacketC03.append(QString("0x%1\n").arg(dst1,4,16,QChar('0')));
    outPacketC03.append(QString("0x%1\n").arg(dst2,4,16,QChar('0')));
    outPacketC03.append(QString("0x%1\n").arg(dst3,4,16,QChar('0')));
    outPacketC03.append(QString("0x%1\n").arg(addrReg,4,16,QChar('0')));
    outPacketC03.append(QString("0x%1\n").arg(lengthData,4,16,QChar('0')));
    outPacketC03.append(QString("0x%1\n").arg(tag,4,16,QChar('0')));
    if(numMes == 3){
        for (int i = 0; i < lengthData; i++)
            outPacketC03.append(QString("0x%1\n").arg(data[i],4,16,QChar('0')));
    }
    return outPacketC03;
}

msg_t::msg_t ()
{}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
