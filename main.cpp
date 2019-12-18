#include <bits/stdc++.h>

using namespace std;


class Segment3D{
public:

    int xL,xR,yL,yR,zL,zR;
    int area;

    Segment3D(int xL,int xR,int yL,int yR,int zL,int zR) :
            xL(xL),xR(xR),yL(yL),yR(yR),zL(zL),zR(zR),area((xR-xL)*(yR-yL)*(xR-xL)){}

    Segment3D(int x,int y,int z) :
            xL(x),xR(x+1),yL(y),yR(y+1),zL(z),zR(z+1),area((xR-xL)*(yR-yL)*(xR-xL)){}

    Segment3D intersect(const Segment3D &b){
        return {max(xL,b.xL),min(xR,b.xR),
                max(yL,b.yL),min(yR,b.yR),
                max(zL,b.zL),min(xR,b.zR)};
    }

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

    int index;
    int val;

    ExtremeType() : ExtremeType(0,0){}

    ExtremeType(int v) : ExtremeType(0,v){}

    ExtremeType(int i,int v) : index(i),val(v){}

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


class Segment3DTreeNode{
public:
    Segment3D mySegment;
    int xMid,yMid,zMid; // Mid点处算作L范围
    Segment3DTreeNode*son[8];
    StaticsType statics;
    int cachedDiff;
    bool ifSet;
    int cachedSet;

    // 八叉树非满，操作时注意判断子树存在性

    // 定义操作优先级：set>modify
    // 即节点既有cachedDiff又有cachedSet时，先执行set
    // 有set时可附加diff，但有diff时请求set需先下传
    // 上层set指令可使下层数据无效化
    // sum要求实时保持最新，当请求细分时下传标记



    /* 构造函数 */

    Segment3DTreeNode(int xL,int xR,int yL,int yR,int zL,int zR) : mySegment(xL,xR,yL,yR,zL,zR){

        if(mySegment.empty()){
            cout<<"Test";
        }
        assert(!mySegment.empty());

        cachedDiff=0;
        ifSet=false;
        cachedSet=0;
        xMid=(xL+xR/2);
        yMid=(yL+yR/2);
        zMid=(zL+zR/2);
        statics=StaticsType(0,0,0);

        if(mySegment.isLeaf()){
            return;
        }

        memset(son,0,sizeof(son));
        // 如果某维度区间大小只有1，则细分该维的L~Mid是无意义的
        if(xR-xL>1)
            son[0]=new Segment3DTreeNode(xL,xMid,yMid,yR,zMid,zR);
        son[1]=new Segment3DTreeNode(xMid,xR,yMid,yR,zMid,zR);
        if(yR-yL>1)
            son[2]=new Segment3DTreeNode(xMid,xR,yL,yMid,zMid,zR);
        if(xR-xL>1 && yR-yL>1)
            son[3]=new Segment3DTreeNode(xL,xMid,yL,yMid,zMid,zR);
        if(xR-xL>1 && zR-zL>1)
            son[4]=new Segment3DTreeNode(xL,xMid,yMid,yR,zL,zMid);
        if(zR-zL>1)
            son[5]=new Segment3DTreeNode(xMid,xR,yMid,yR,zL,zMid);
        if(yR-yL>1 && zR-zL>1)
            son[6]=new Segment3DTreeNode(xMid,xR,yL,yMid,zL,zMid);
        if(xR-xL>1 && yR-yL>1 && zR-zL>1)
            son[7]=new Segment3DTreeNode(xL,xMid,yL,yMid,zL,zMid);
    }

    explicit Segment3DTreeNode(Segment3D segment) : Segment3DTreeNode(segment.xL,segment.xR,segment.yL,segment.yR,
                                                                      segment.zL,segment.zR){} // Wrapper



    /* 区间修改 */

    StaticsType &__modifySegment(Segment3D segment,int diff){

        segment=segment.intersect(mySegment);

        if(segment.empty())return statics;

        if(segment==mySegment){
            cachedDiff+=diff;
            statics.sum+=diff;
            statics.min+=diff;
            statics.max+=diff;
            return statics;
        }else{
            statics.clear();
            for(auto &i : son){
                if(i){
                    auto re=i->__modifySegment(segment,diff);
                    statics.update(re);
                }
            }
            return statics;
        }

    }

    void modifySegment(Segment3D segment,int diff){
        __modifySegment(segment,diff);
    } // Wrapper

    void modifyPoint(int x,int y,int z,int diff){
        __modifySegment(Segment3D(x,y,z),diff);
    } // Wrapper



    /* 查询(单点/区间)(区间和/最大值/最小值) */

    int querySegmentSum(Segment3D segment){

        segment=segment.intersect(mySegment);

        if(segment==mySegment){
            return statics.sum;
        }
        int res=0;
        for(auto &i:son){
            if(i)
                res+=i->querySegmentSum(segment);
        }
        return res;
    }

    int queryPoint(int x,int y,int z){
        return querySegmentSum(Segment3D(x,y,z));
    } // Wrapper

    ExtremeType querySegmentMin(Segment3D segment){

        segment=segment.intersect(mySegment);

        if(segment==mySegment){
            return statics.min;
        }
        ExtremeType res;
        bool init=false;
        for(auto &i:son){
            if(i){
                if(!init){
                    res=i->querySegmentMin(segment);
                    init=true;
                }else{
                    res=std::min(res,i->querySegmentMin(segment));
                }
            }
        }
        return res;
    }

    ExtremeType queryPointMin(int x,int y,int z){
        return querySegmentMin(Segment3D(x,y,z));
    }

    ExtremeType querySegmentMax(Segment3D segment){

        segment=segment.intersect(mySegment);

        if(segment==mySegment){
            return statics.max;
        }
        ExtremeType res;
        bool init=false;
        for(auto &i:son){
            if(i){
                if(!init){
                    res=i->querySegmentMax(segment);
                    init=true;
                }else{
                    res=std::max(res,i->querySegmentMax(segment));
                }
            }
        }
        return res;
    }

    ExtremeType queryPointMax(int x,int y,int z){
        return querySegmentMax(Segment3D(x,y,z));
    }


    /* 强制赋值 */

    StaticsType &__setSegment(Segment3D segment,int val){

        segment=segment.intersect(mySegment);

        if(segment.empty())return statics;

        if(segment==mySegment){
            cachedDiff=0;
            ifSet=true;
            cachedSet=val;
            statics.max=statics.min=val;
            statics.sum=val*mySegment.getVolume();
        }else{
            if(cachedDiff){
                pushDownDiff();
            }
            statics.clear();
            for(auto &i:son){
                if(i){
                    auto re=i->__setSegment(segment,val);
                    statics.update(re);
                }
            }
            return statics;
        }
    }

    void setSegment(Segment3D segment,int val){
        __setSegment(segment,val);
    } // Wrapper



    /* 标记下传 */

    void pushDownSet(){
        for(auto &i:son){
            if(i){
                i->cachedDiff=0;
                i->ifSet=true;
                i->cachedSet=cachedSet;
            }
        }
        ifSet=false;
    }

    void pushDownDiff(){
        for(auto &i:son){
            if(i){
                i->cachedDiff+=cachedDiff;
                i->statics.add(cachedDiff,i->mySegment.getVolume());
            }
        }
        cachedDiff=0;
    }

};


class Segment3DTree{
public:
    int xLength;
    int yLength;
    int zLength;
    Segment3DTreeNode head;

    Segment3DTree(int xLength,int yLength,int zLength) : xLength(xLength),yLength(yLength),zLength(zLength),
    head(Segment3D(1,xLength,1,yLength,1,zLength)){}

    void modifySegment(Segment3D segment,int diff){
        head.modifySegment(segment,diff);
    }

    void modifyPoint(int x,int y,int z,int diff){
        head.modifyPoint(x,y,z,diff);
    }

    int querySegmentSum(Segment3D segment){
        head.querySegmentSum(segment);
    }

    int queryPoint(int x,int y,int z){
        head.queryPoint(x,y,z);
    }

    ExtremeType querySegmentMin(Segment3D segment){
        return head.querySegmentMin(segment);
    }

    ExtremeType queryPointMin(int x,int y,int z){
        return head.queryPointMin(x,y,z);
    }

    ExtremeType querySegmentMax(Segment3D segment){
        return head.querySegmentMax(segment);
    }

    ExtremeType queryPointMax(int x,int y,int z){
        return head.queryPointMax(x,y,z);
    }

    void setSegment(Segment3D segment,int val){
        head.setSegment(segment,val);
    }

};


int main(){
    Segment3DTree tree(10,10,10);

}
