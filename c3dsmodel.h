#ifndef CKUKAMODEL_H
#define CKUKAMODEL_H

#include <QtOpenGL>
#include "ctreddiobject.h"
#include "lib3ds/lib3ds.h"

struct str_boundedBox{
    float minX;
    float maxX;
    float minY;
    float maxY;
    float minZ;
    float maxZ;
};


class C3DSModel: public CTreddiObject{
public:
    typedef struct str_boundedBox boundedBox;

public:
    C3DSModel(const char* file3ds, float x=0, float y=0, float z=0);
    ~C3DSModel();

    virtual void customRender();
    void renderModel();

    void* getBoundedBox();

    float absoluteSize();

    float scaleTo( float size );
    float scaleFactor( );

    void setSelfIlluminate();

    void buildDisplayList();

private:
    bool            m_loaded;

    Lib3dsFile*     m_fileModel;

    QString         m_fileName;

    QList<float(*)[3]>  m_normalsList;

    double          m_scaleFactor;

    bool            m_selfIlluminate;

    GLuint  m_displayList;
};

#endif // CKUKAMODEL_H
