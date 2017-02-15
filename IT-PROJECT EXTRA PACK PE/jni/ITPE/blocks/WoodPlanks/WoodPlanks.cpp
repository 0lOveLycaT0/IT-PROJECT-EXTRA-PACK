#include "WoodPlanks.h"

WoodPlanks::WoodPlanks(std::string const &name,int id) : Block(name,id,Material::getMaterial(MaterialType::WOOD)){
	init();
	setCategory(CreativeItemCategory::BLOCKS);
	setTicking(true);
	setSolid(true);
	renderLayer = mWoodPlanks -> renderLayer;
}

int WoodPlanks::getRenderLayer(BlockSource&s, BlockPos const&pos) const
{
	return mWoodPlanks -> getRenderLayer(s,pos);
}

int WoodPlanks::getExtraRenderLayers() const
{
	return mWoodPlanks -> getExtraRenderLayers();
}

