
#include <QDebug>
#include <QImage>
#include <QBuffer>
#include <QByteArray>
#include <windows.h>
#include "texture.h"

Texture::Texture() : QOpenGLFunctions()
{
    for (int i=0; i<11; i++)
        pixels[i] = 0;
    pixels[0] = 255;
    pixels[4] = 255;
    pixels[8] = 255;
    pixels[9] = 255;
    pixels[10] = 255;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_TEXTURE_2D);

    /// Må gjøres etter at GL er initialisert
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    qDebug() << "Texture::Texture() id = " << m_id;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 reinterpret_cast<const GLvoid*>(pixels));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture(const QString& filnavn)
{
    initializeOpenGLFunctions();
    lesBitmap(filnavn.toStdString());
    settTekstur();
}

GLuint Texture::id() const
{
    //if (glIsTexture(m_id)) qDebug() << "Texture " << m_id << "is texture";
    return m_id;
}

void Texture::lesBitmap(const std::string &filnavn)
{
    BITMAPFILEHEADER bmFileHeader;
    BITMAPINFOHEADER bmInfoHeader;

    std::fstream fil(filnavn.c_str(), std::ios::in | std::ios::binary); // FILE* fp = fopen(bildefil.c_str(),"rb");
    if (fil.is_open()) //if (fp)
    {
        fil.read((char *) &bmFileHeader, 14); //fread(&bmFileHeader, 14, 1, fp);

        fil.read((char *) &bmInfoHeader, sizeof(BITMAPINFOHEADER));	//fread(&bmInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
        m_kolonner = bmInfoHeader.biWidth;
        m_rader = bmInfoHeader.biHeight;
        m_nByte = bmInfoHeader.biBitCount / 8;

        m_bitmap = new unsigned char[m_kolonner * m_rader * m_nByte];
        fil.read((char *) m_bitmap, m_kolonner * m_rader * m_nByte); //fread(bitmap,kolonner * rader * nByte,1,fp);
        fil.close(); //fclose(fp);
    }
    unsigned char tmp;
    // må bytte rød og blå
    for (int k = 0; k < m_kolonner * m_rader * m_nByte; k += m_nByte) {
        tmp = m_bitmap[k];
        m_bitmap[k] = m_bitmap[k + 2];
        m_bitmap[k + 2] = tmp;
    }
}

void Texture::settTekstur()
{
    glGenTextures(1, &m_id);
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGB,
                m_kolonner,
                m_rader,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                m_bitmap);
}

