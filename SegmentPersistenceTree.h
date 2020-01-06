#pragma once

#include "SegmentTree.h"


class Segment3DPersistenceTreeNode : public Segment3DTreeNode{

private:

public:

    Segment3DPersistenceTreeNode(Segment3D segment);

    Segment3DPersistenceTreeNode(Segment3DPersistenceTreeNode &b);

    Segment3DPersistenceTreeNode(Segment3DTreeNode &b);


    /* 区间修改 */

    StaticsType &__modifySegment(Segment3D segment,int diff,Segment3DPersistenceTreeNode**link);

    /* 区间赋值 */

    StaticsType &__setSegment(Segment3D segment,int val,Segment3DPersistenceTreeNode**link);


    void modifySegment(Segment3D segment,int diff);

    void setSegment(Segment3D segment,int val);

};


class Segment3DPersistenceTree{

private:

    list<Segment3DPersistenceTreeNode> heads;
    int count;

    void createDuplicate();

public:

    int xLength;
    int yLength;
    int zLength;

    Segment3DPersistenceTree(int xLength,int yLength,int zLength);

    void modifySegment(Segment3D segment,int diff);

    void modifyPoint(int x,int y,int z,int diff);

    int querySegmentSum(Segment3D segment,int time);

    int queryPoint(int x,int y,int z,int time);

    ExtremeType querySegmentMin(Segment3D segment,int time);

    ExtremeType querySegmentMax(Segment3D segment,int time);

    void setSegment(Segment3D segment,int val);

    void setPoint(int x,int y,int z,int val);

    void debug_output_sum_process(Segment3D segment);

};