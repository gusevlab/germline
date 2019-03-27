#ifndef SHAREDSEGMENTPOINTER_H
#define SHAREDSEGMENTPOINTER_H

#include "BasicDefinitions.h"
#include "SharedSegment.h"

class SharedSegmentPointer
{
public:
	SharedSegmentPointer(SharedSegment * s);
	SharedSegment * get();
private:
	SharedSegment * sp;
};

#endif