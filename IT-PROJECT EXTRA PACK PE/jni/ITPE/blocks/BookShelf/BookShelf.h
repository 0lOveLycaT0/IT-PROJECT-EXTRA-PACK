#pragma once

#include <memory>
#include "mcpe/block/Block.h"

class BookShelf : public Block
{
public:	
    BookShelf(std::string const&,int);
public:
	virtual int getRenderLayer(BlockSource&, BlockPos const&) const;
	virtual int getExtraRenderLayers() const;
};

