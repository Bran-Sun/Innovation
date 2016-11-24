#include "cube.h"
#include<GL/glu.h>
#include<QKeyEvent>
#include<QTimer>
#include<QPainter>
#include<QFile>
#include<QDebug>

QCube::QCube(QWidget *parent):
    QGLWidget(parent)
{
    int i,j,k;
    fullscreen=false;

    m_x=0;
    m_y=0;
    m_z=0;
    xn=0;xr=0;
    yn=0;yr=0;
    zn=0;zr=0;
//    xRot=0;yRot=0;zRot=0;
    for(i=0;i<3;i++)
        for (j=0;j<3;j++)
            for(k=0;k<3;k++)
            {
                angelx[i][j][k]=0;
                angely[i][j][k]=0;
                angelz[i][j][k]=0;
            }
    scan(cube);
    record=0;
}

QCube::~QCube()
{

}

void QCube::initializeGL()
{
    glEnable(GL_MULTISAMPLE);
    glClearColor(0.0,0.3,0.3,0.0);
    glShadeModel(GL_SMOOTH);

    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

}
void QCube::resizeGL(int w, int h)
{
    glViewport(0,0,(GLint)w,(GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0,(GLfloat)w/(GLfloat)h,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void QCube::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    for (int i=0;i<3;i++)
      for (int j=0;j<3;j++)
            for (int k=0;k<3;k++)
            {
                paintQCube(i,j,k);
            }
}

void QCube::paintQCube(int x, int y, int z)
{
    glLoadIdentity();
    gluLookAt(9.0,3.0,0.0,  0.0f,0.0f,-12.0f,  0.0,1.0,0.0);
    glTranslatef(0.0f,0.0f,-12.0f);
    glRotatef(m_x,1.0f,0.0f,0.0f);
    glRotatef(m_y,0.0f,1.0f,0.0f);
    glRotatef(m_z,0.0f,0.0f,1.0f);
    glRotatef(angelx[x][y][z],1.0f,0.0f,0.0f);
    glRotatef(angely[x][y][z],0.0f,1.0f,0.0f);
    glRotatef(angelz[x][y][z],0.0f,0.0f,1.0f);
 glTranslatef(2*x-2,2*y-2,2*z-2);

    float dif=0.1;
    float fl=0.01;
    glBegin(GL_QUADS);
            glColor3f(0.0f,0.0f,0.0f);
            glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(顶面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(顶面)
            glVertex3f(-1.0f, 1.0f, 1.0f);                  //左下(顶面)
            glVertex3f(1.0f, 1.0f, 1.0f);                   //右下(顶面)


            glVertex3f(1.0f, -1.0f, 1.0f);                  //右上(底面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //左上(底面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(底面)
            glVertex3f(1.0f, -1.0f, -1.0f);                 //右下(底面)

            glVertex3f(1.0f, 1.0f, 1.0f);                   //右上(前面)
            glVertex3f(-1.0f, 1.0f, 1.0f);                  //左上(前面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //左下(前面)
            glVertex3f(1.0f, -1.0f, 1.0f);                  //右下(前面)

           glVertex3f(1.0f, -1.0f, -1.0f);                 //右上(后面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左上(后面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左下(后面)
            glVertex3f(1.0f, 1.0f, -1.0f);                  //右下(后面)

            glVertex3f(-1.0f, 1.0f, 1.0f);                  //右上(左面)
            glVertex3f(-1.0f, 1.0f, -1.0f);                 //左上(左面)
            glVertex3f(-1.0f, -1.0f, -1.0f);                //左下(左面)
            glVertex3f(-1.0f, -1.0f, 1.0f);                 //右下(左面)

            glVertex3f(1.0f, 1.0f, -1.0f);                  //右上(右面)
            glVertex3f(1.0f, 1.0f, 1.0f);                   //左上(右面)
            glVertex3f(1.0f, -1.0f, 1.0f);                  //左下(右面)
            glVertex3f(1.0f, -1.0f, -1.0f);
        glEnd();

        glBegin(GL_QUADS);
                   setcolor(cube[x][y][z].color[1]);
                    glVertex3f(1.0f-dif, 1.0f+fl, -1.0f+dif);                  //右上(顶面)
                    glVertex3f(-1.0f+dif, 1.0f+fl, -1.0f+dif);                 //左上(顶面)
                    glVertex3f(-1.0f+dif, 1.0f+fl, 1.0f-dif);                  //左下(顶面)
                    glVertex3f(1.0f-dif, 1.0f+fl, 1.0f-dif);                   //右下(顶面)


                     setcolor(cube[x][y][z].color[6]);
                    glVertex3f(1.0f-dif, -1.0f-fl, 1.0f-dif);                  //右上(底面)
                    glVertex3f(-1.0f+dif, -1.0f-fl, 1.0f-dif);                 //左上(底面)
                    glVertex3f(-1.0f+dif, -1.0f-fl, -1.0f+dif);                //左下(底面)
                    glVertex3f(1.0f-dif, -1.0f-fl, -1.0f+dif);                 //右下(底面)

                        setcolor(cube[x][y][z].color[3]);
                    glVertex3f(1.0f-dif, 1.0f-dif, 1.0f+fl);                   //右上(前面)
                    glVertex3f(-1.0f+dif, 1.0f-dif, 1.0f+fl);                  //左上(前面)
                    glVertex3f(-1.0+dif, -1.0f+dif, 1.0f+fl);                 //左下(前面)
                    glVertex3f(1.0f-dif, -1.0f+dif, 1.0f+fl);                  //右下(前面)
         setcolor(cube[x][y][z].color[5]);
          glVertex3f(1.0f-dif, -1.0f+dif, -1.0f-fl);                 //右上(后面)
          glVertex3f(-1.0f+dif, -1.0f+dif, -1.0f-fl);                //左上(后面)
          glVertex3f(-1.0f+dif, 1.0f-dif, -1.0f-fl);                 //左下(后面)
          glVertex3f(1.0f-dif, 1.0f-dif, -1.0f-fl);                  //右下(后面)

            setcolor(cube[x][y][z].color[2]);
          glVertex3f(-1.0f-fl, 1.0f-dif, 1.0f-dif);                  //右上(左面)
          glVertex3f(-1.0f-fl, 1.0f-dif, -1.0f+dif);                 //左上(左面)
          glVertex3f(-1.0f-fl, -1.0f+dif, -1.0f+dif);                //左下(左面)
          glVertex3f(-1.0f-fl, -1.0f+dif, 1.0f-dif);                 //右下(左面)

            setcolor(cube[x][y][z].color[4]);
          glVertex3f(1.0f+fl, 1.0f-dif, -1.0f+dif);                  //右上(右面)
          glVertex3f(1.0f+fl, 1.0f-dif, 1.0f-dif);                   //左上(右面)
          glVertex3f(1.0f+fl, -1.0f+dif, 1.0f-dif);                  //左下(右面)
          glVertex3f(1.0f+fl, -1.0f+dif, -1.0f+dif);
      glEnd();
}

void QCube::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_F1:
        fullscreen=!fullscreen;
        if(fullscreen)
        {
            showFullScreen();
        }
        else
        {
        showNormal();
         }
        updateGL();
        break;
       case Qt::Key_R:
        BturnR();
        break;
       case Qt::Key_L:
        turnL();
        break;
    case Qt::Key_U:
        turnU();
        break;
      case Qt::Key_D:
        turnD();
        break;
    case Qt::Key_F:
        turnF();
        break;
     case Qt::Key_B:
        turnB();
        break;
      case Qt::Key_Up:
        m_x +=10;
        updateGL();
        break;
       case Qt::Key_Down:
        m_x -=10;
        updateGL();
        break;
       case Qt::Key_Left:
        m_y +=10;
        updateGL();
         break;
        case Qt::Key_Right:
         m_y -=10;
        updateGL();
        break;
      case Qt::Key_Escape:
        close();
    }
}

void QCube::setcolor(int k)
{
    switch(k)
    {
       case 1: glColor3f(0.0f, 1.0f, 0.0f);                    //绿色
               break;
       case 2:
        glColor3f(1.0f, 0.5f, 0.0f);                    //橙色
        break;
       case 3:
         glColor3f(1.0f, 0.0f, 0.0f);                    //红色
        break;
        case 4:
                glColor3f(1.0f, 1.0f, 0.0f);                    //黄色
               break;
        case 5:
               glColor3f(0.0f, 0.0f, 1.0f);                    //蓝色
             break;
        case 6:
            glColor3f(1.0f, 1.0f, 1.0f);                    //白色
             break;
        case 0:
          glColor3f(0.0f,0.0f,0.0f);
    }
}

void QCube::scan(Piece cube[3][3][3])
{
    int i,j,k,t;
     for (i=0;i<3;i++)
          for (j=0;j<3;j++)
           for (k=0;k<3;k++)
            for(t=1;t<=6;t++)
                cube[i][j][k].color[t]=0;
     for (i=0;i<3;i++)
          for (j=0;j<3;j++)
            {
                 cube[i][j][2].color[3]=3;
             }
         for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[i][0][2-j].color[6]=6;
             }
        for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[2][i][2-j].color[4]=4;
             }
        for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[2-i][2][2-j].color[1]=1;
             }
         for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[0][2-i][2-j].color[2]=2;
             }
         for (j=0;j<3;j++)
          for (i=0;i<3;i++)
            {
                 cube[2-j][i][0].color[5]=5;
             }

}

void QCube::turnx()
{
   int i,j;
    for (i=0;i<3;i++)
       for(j=0;j<3;j++)
          angelx[xn][i][j]=angelx[xn][i][j]+xr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         if (xr==-1)
         {
         for ( i=0;i<3;i++)
            for( j=0;j<3;j++)
               angelx[xn][i][j]=0;
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[j][2-i]=cube[xn][i][j];
                     layer[j][2-i].color[1]=cube[xn][i][j].color[3];
                     layer[j][2-i].color[3]=cube[xn][i][j].color[6];
                     layer[j][2-i].color[6]=cube[xn][i][j].color[5];
                     layer[j][2-i].color[5]=cube[xn][i][j].color[1];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube[xn][i][j]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
                 for ( i=0;i<3;i++)
                    for( j=0;j<3;j++)
                       angelx[xn][i][j]=0;
                 Piece layer[3][3];
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             layer[j][2-i]=cube[xn][i][j];
                             layer[j][2-i].color[1]=cube[xn][i][j].color[3];
                             layer[j][2-i].color[3]=cube[xn][i][j].color[6];
                             layer[j][2-i].color[6]=cube[xn][i][j].color[5];
                             layer[j][2-i].color[5]=cube[xn][i][j].color[1];
                         }
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             cube[xn][i][j]=layer[i][j];
                       }
                 }

         updateGL();
    }
}

void QCube::turnX(int n)
{
    record=0;
    xn=n;
   timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(turnx()));
   timer->start(10);
}

void QCube::turnR()
{
     xr=-1;
   turnX(2);

}
void QCube::BturnR()
{
    xr=1;
    turnX(2);
}

void QCube::turnL()
{
    xr=1;
    turnX(0);
}

void QCube::BturnL()
{
    xr=-1;
    turnX(0);
}
void QCube::turny()
{
   int i,j;
    for (i=0;i<3;i++)
       for(j=0;j<3;j++)
          angely[i][yn][j]=angely[i][yn][j]+yr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         if (yr==-1)
         {
         for ( i=0;i<3;i++)
            for( j=0;j<3;j++)
               angely[i][yn][j]=0;
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[2-j][i]=cube[i][yn][j];
                     layer[2-j][i].color[2]=cube[i][yn][j].color[3];
                     layer[2-j][i].color[3]=cube[i][yn][j].color[4];
                     layer[2-j][i].color[4]=cube[i][yn][j].color[5];
                     layer[2-j][i].color[5]=cube[i][yn][j].color[2];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube[i][yn][j]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
                 for ( i=0;i<3;i++)
                    for( j=0;j<3;j++)
                       angely[i][yn][j]=0;
                 Piece layer[3][3];
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             layer[2-j][i]=cube[i][yn][j];
                             layer[2-j][i].color[2]=cube[i][yn][j].color[3];
                             layer[2-j][i].color[3]=cube[i][yn][j].color[4];
                             layer[2-j][i].color[4]=cube[i][yn][j].color[5];
                             layer[2-j][i].color[5]=cube[i][yn][j].color[2];
                         }
                     for (i=0;i<3;i++)
                      for (j=0;j<3;j++)
                       {
                             cube[i][yn][j]=layer[i][j];
                       }
                }
         updateGL();
    }
}


void QCube::turnY(int n)
{

    record=0;
    yn=n;
   timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(turny()));
   timer->start(10);
}

void QCube::turnU()
{
     yr=-1;
     turnY(2);
}

void QCube::BturnU()
{
    yr=1;
    turnY(2);
}

void QCube::turnD()
{
    yr=1;
    turnY(0);
}

void QCube::BturnD()
{
    yr=-1;
    turnY(0);
}
void QCube::turnz()
{
   int i,j;
    for (i=0;i<3;i++)
       for(j=0;j<3;j++)
          angelz[i][j][zn]=angelz[i][j][zn]+zr;
    updateGL();

   record +=1;
   if (record>=90)
   {
         timer->stop();
         if (zr==-1)
         {
         for ( i=0;i<3;i++)
            for( j=0;j<3;j++)
               angelz[i][j][zn]=0;
         Piece layer[3][3];
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     layer[j][2-i]=cube[i][j][zn];
                     layer[j][2-i].color[4]=cube[i][j][zn].color[1];
                     layer[j][2-i].color[1]=cube[i][j][zn].color[2];
                     layer[j][2-i].color[2]=cube[i][j][zn].color[6];
                     layer[j][2-i].color[6]=cube[i][j][zn].color[4];
                 }
             for (i=0;i<3;i++)
              for (j=0;j<3;j++)
               {
                     cube[i][j][zn]=layer[i][j];
               }
         }
         else
             for (int k=0;k<3;k++)
             {
             for ( i=0;i<3;i++)
                for( j=0;j<3;j++)
                   angelz[i][j][zn]=0;
             Piece layer[3][3];
                 for (i=0;i<3;i++)
                  for (j=0;j<3;j++)
                   {
                         layer[j][2-i]=cube[i][j][zn];
                         layer[j][2-i].color[4]=cube[i][j][zn].color[1];
                         layer[j][2-i].color[1]=cube[i][j][zn].color[2];
                         layer[j][2-i].color[2]=cube[i][j][zn].color[6];
                         layer[j][2-i].color[6]=cube[i][j][zn].color[4];
                     }
                 for (i=0;i<3;i++)
                  for (j=0;j<3;j++)
                   {
                         cube[i][j][zn]=layer[i][j];
                   }
             }
         updateGL();
    }
}

void QCube::turnZ(int n)
{

    record=0;
    zn=n;
   timer=new QTimer(this);
   connect(timer,SIGNAL(timeout()),this,SLOT(turnz()));
   timer->start(10);
}
void QCube::turnF()
{
    zr=-1;
    turnZ(2);
}
void QCube::BturnF()
{
    zr=1;
    turnZ(2);

}

void QCube::turnB()
{
    zr=1;
    turnZ(0);

}
void QCube::BturnB()
{
    zr=-1;
    turnZ(0);
}
