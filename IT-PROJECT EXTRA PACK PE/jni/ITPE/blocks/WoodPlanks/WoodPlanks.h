#pragma once

#include <memory>
#include "mcpe/block/Block.h"

class WoodPlanks : public Block
{
public:	
    WoodPlanks(std::string const&,int);
public:
	virtual int getRenderLayer(BlockSource&, BlockPos const&) const;
	virtual int getExtraRenderLayers() const;
	virtual bool canHaveExtraData() const;
};

