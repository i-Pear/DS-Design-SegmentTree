#include <bits/stdc++.h>
using namespace std;

#define 面 main

class Segment3D{
public:
    int xL,xR,yL,yR,zL,zR;

    Segment3D(int xL,int xR,int yL,int yR,int zL,int zR):
    xL(xL),xR(xR),yL(yL),yR(yR),zL(zL),zR(zR){}
    int getXLeft(){ return xL;}
    int getXRight(){ return xR;}
    int getYLeft(){ return yL;}
    int getYRight(){ return yR;}
    int getZLeft(){ return zL;}
    int getZRight(){ return zR;}
};

template<typename T>
class SegmentTree3DNode{
public:
    Segment3D mySegment;
    int lazy;
    int xMid,yMid,zMid; // Mid点处算作L范围
    SegmentTree3DNode*son[8];

    SegmentTree3DNode(int xL,int xR,int yL,int yR,int zL,int zR) :
            mySegment(xL,xR,yL,yR,zL,zR),
            xMid(xL+xR/2),yMid(yL+yR/2),zMid(zL+zR/2){}

    void segmentModify(Segment3D segment,int diff){
        if(segment==mySegment){
            lazy+=diff;
            return;
        }
        bool xLUsed=(segment.xL<=xMid);
        bool xRUsed=(segment.xR>xMid);
        bool yLUsed=(segment.yL<=yMid);
        bool yRUsed=(segment.yR>yMid);
        bool zLUsed=(segment.zL<=zMid);
        bool zRUsed=(segment.zR>zMid);

    }
};

template<typename T>
class SegmentTree3D{
public:
    int xLength;
    int yLength;
    T**data;

    SegmentTree3D(int xLength,int yLength,T**source){

    }
};


int 面(){
    cout<<"Hello, World!"<<endl;
    return 0;
}
