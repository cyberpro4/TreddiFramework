#ifndef CKUKAMODEL_H
#define CKUKAMODEL_H

#include <QtOpenGL>
#include "ctreddiobject.h"
#include "lib3ds/lib3ds.h"

class C3DSModel: public CTreddiObject{
public:
    typedef struct str_boundedBox boundedBox;

public:
    C3DSModel(const char* file3ds, float x=0, float y=0, float z=0);
    ~C3DSModel();

    virtual void customRender();

    void buildDisplayList();

private:
    void renderModel();

private:
    bool            m_loaded;

    Lib3dsFile*     m_fileModel;

    QString         m_fileName;

    QList<float(*)[3]>  m_normalsList;

    GLuint  m_displayList;
};

#endif // CKUKAMODEL_H
