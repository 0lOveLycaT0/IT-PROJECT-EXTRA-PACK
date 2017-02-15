#include "Bookshelf.h"

Bookshelf::Bookshelf(std::string const &name,int id) : Block(name,id,Material::getMaterial(MaterialType::WOOD)){
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setTicking(true);
	setSolid(true);
	renderLayer = mBookshelf -> renderLayer;
}

int Bookshelf::getRenderLayer(BlockSource&s, BlockPos const&pos) const
{
	return mBookshelf -> getRenderLayer(s,pos);
}

int Bookshelf::getExtraRenderLayers() const
{
	return mBookshelf -> getExtraRenderLayers();
}

