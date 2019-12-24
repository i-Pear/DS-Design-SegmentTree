#pragma once
#include <bits/stdc++.h>
using namespace std;

class Segment3D{
public:

    int xL,xR,yL,yR,zL,zR;
    int area;

    Segment3D(int xL,int xR,int yL,int yR,int zL,int zR) :
            xL(xL),xR(xR),yL(yL),yR(yR),zL(zL),zR(zR),area((xR-xL)*(yR-yL)*(zR-zL)){}

    Segment3D(int x,int y,int z) :
            xL(x),xR(x+1),yL(y),yR(y+1),zL(z),zR(z+1),area((xR-xL)*(yR-yL)*(zR-zL)){}

    Segment3D intersect(const Segment3D &b){
        return {max(xL,b.xL),min(xR,b.xR),
                max(yL,b.yL),min(yR,b.yR),
                max(zL,b.zL),min(zR,b.zR)};
    }

    Segment3D &operator=(const Segment3D &b) = default;

    int getVolume() const{
        return area;
    }

    bool contains(const Segment3D &b){
        return xL<=b.xL && xR>=b.xR && yL<=b.yL && yR>=b.yR && zL<=b.zL && zR>=b.zR;
    }

    bool empty() const{
        return xL==xR || yL==yR || zL==zR;
    }

    bool operator==(const Segment3D b) const{
        return xL==b.xL && xR==b.xR && yL==b.yL && yR==b.yR && zL==b.zL && zR==b.zR;
    }

    bool isLeaf() const{
        return area==1;
    }

};


class ExtremeType{
public:

    bool valid;
    int index;
    int val;

    ExtremeType() : index(0),val(0),valid(false){}

    ExtremeType(int v) : ExtremeType(0,v){}

    ExtremeType(int i,int v) : index(i),val(v),valid(true){}

    ExtremeType &operator+(int v){
        val+=v;
        return *this;
    }

    ExtremeType &operator+=(int v){
        val+=v;
        return *this;
    }

    ExtremeType &operator-(int v){
        val-=v;
        return *this;
    }

    ExtremeType &operator-=(int v){
        val-=v;
        return *this;
    }

    ExtremeType &operator=(int v){
        val=v;
        return *this;
    }

    ExtremeType &operator=(ExtremeType v){
        val=v.val;
        return *this;
    }

    bool operator<(const ExtremeType &b) const{
        return val<b.val;
    }

    bool operator==(const ExtremeType &b) const{
        return val==b.val;
    }

    bool operator>(const ExtremeType &b) const{
        return val>b.val;
    }

};


class StaticsType{
public:

    bool valid;
    ExtremeType min;
    ExtremeType max;
    int sum;

    StaticsType(int min,int max,int sum) : min(min),max(max),sum(sum),valid(true){}

    StaticsType() : valid(false){}

    void update(const StaticsType &b){
        if(!b.valid) return;
        if(!valid){
            valid=true;
            *this=b;
            return;
        }
        min=std::min(min,b.min);
        max=std::max(max,b.max);
        sum+=b.sum;
    }

    void add(int v,int area){
        min+=v;
        max+=v;
        sum+=v*area;
    }

    void clear(){
        valid=false;
    }

};