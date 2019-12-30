#pragma once

#include "base.h"

class Segment3DTreeNode{

protected:

    Segment3D mySegment;
    int xMid,yMid,zMid; // Mid点处算作L范围
    Segment3DTreeNode*son[8];
    StaticsType statics;
    int cachedDiff;
    bool ifSet;
    int cachedSet;

    /* 区间修改 */

    StaticsType &__modifySegment(Segment3D segment,int diff);

    /* 区间赋值 */

    StaticsType &__setSegment(Segment3D segment,int val);

    /* 标记下传 */

    void pushDownSet();

    void pushDownDiff();

public:

    // 八叉树非满，操作时注意判断子树存在性

    // 定义操作优先级：set>modify
    // 即节点既有cachedDiff又有cachedSet时，先执行set
    // 有set时可附加diff，但有diff时请求set需先下传
    // 上层set指令可使下层数据无效化
    // sum要求实时保持最新，当请求细分时下传标记



    /* 构造函数 */

    Segment3DTreeNode(int xL,int xR,int yL,int yR,int zL,int zR);

    Segment3DTreeNode(const Segment3DTreeNode &b);

    explicit Segment3DTreeNode(Segment3D segment);


    /* 区间修改 */

    void modifySegment(Segment3D segment,int diff);

    void modifyPoint(int x,int y,int z,int diff);


    /* 查询(单点/区间)(区间和/最大值/最小值) */

    int querySegmentSum(Segment3D segment);

    int queryPoint(int x,int y,int z);

    ExtremeType querySegmentMin(Segment3D segment);

    ExtremeType querySegmentMax(Segment3D segment);


    /* 强制赋值 */

    void setSegment(Segment3D segment,int val);

    void setPoint(int x,int y,int z,int val);


    /* 析构函数 */

    ~Segment3DTreeNode();

};


class Segment3DTree{

protected:

    Segment3DTreeNode head;

public:

    int xLength;
    int yLength;
    int zLength;

    Segment3DTree(int xLength,int yLength,int zLength);

    void modifySegment(Segment3D segment,int diff);

    void modifyPoint(int x,int y,int z,int diff);

    int querySegmentSum(Segment3D segment);

    int queryPoint(int x,int y,int z);

    ExtremeType querySegmentMin(Segment3D segment);

    ExtremeType querySegmentMax(Segment3D segment);

    void setSegment(Segment3D segment,int val);

    void setPoint(int x,int y,int z,int val);

};