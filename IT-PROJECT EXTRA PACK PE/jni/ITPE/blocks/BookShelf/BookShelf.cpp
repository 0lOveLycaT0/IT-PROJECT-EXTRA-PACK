#include "BookShelf.h"

BookShelf::BookShelf(std::string const &name,int id) : Block(name,id,Material::getMaterial(MaterialType::WOOD)){
	init();
	setCategory(CreativeItemCategory::DECORATIONS);
	setTicking(true);
	setSolid(true);
	renderLayer = mBookshelf -> renderLayer;
}

int BookShelf::getRenderLayer(BlockSource&s, BlockPos const&pos) const
{
	return mBookshelf -> getRenderLayer(s,pos);
}

int BookShelf::getExtraRenderLayers() const
{
	return mBookshelf -> getExtraRenderLayers();
}

