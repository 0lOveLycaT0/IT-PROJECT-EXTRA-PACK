#pragma once

#include <memory>
#include "mcpe/block/Block.h"

class Bookshelf : public Block
{
public:	
    Bookshelf(std::string const&,int);
public:
	virtual int getRenderLayer(BlockSource&, BlockPos const&) const;
	virtual int getExtraRenderLayers() const;
};

