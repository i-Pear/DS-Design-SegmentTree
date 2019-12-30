#include "base.h"
#include "SegmentTree.h"
#include "SegmentPersistenceTree.h"


int main(){ // 左闭右开
    Segment3DPersistenceTree t(4,4,4);
    t.setSegment({0,3,0,3,0,3},10);
    t.modifySegment({1,3,1,3,1,3},1);
    t.modifySegment({0,2,0,2,0,2},-1);
    t.debug_output_sum_process({0,3,0,3,0,3});
}
