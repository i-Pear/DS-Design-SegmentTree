#include "base.h"
#include "SegmentTree.h"
#include "SegmentPersistenceTree.h"


int main(){ // 左闭右开
    Segment3DPersistenceTree t(10,10,10);
    t.modifySegment({0,5,0,1,0,1},1);
    t.modifySegment({3,7,0,2,0,2},10);
    t.modifySegment({0,5,0,5,0,5},-5);
    cout<<t.querySegmentMax({0,10,0,10,0,10},3).val;
}
