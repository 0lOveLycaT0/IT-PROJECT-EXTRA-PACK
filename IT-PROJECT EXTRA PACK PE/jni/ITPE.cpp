#include <jni.h>
#include <dlfcn.h>
#include <Substrate.h>
#include <cstdlib>
#include <vector>

#include "mcpe/client/renderer/BlockTessellator.h"
#include "mcpe/block/Block.h"
#include "mcpe/block/BlockGraphics.h"
#include "mcpe/item/Item.h"
#include "mcpe/item/BlockItem.h"
#include "mcpe/item/AuxDataBlockItem.h"
#include "mcpe/level/BlockSource.h"
#include "mcpe/entity/Entity.h"
#include "mcpe/client/renderer/Tessellator.h"
#include "mcpe/util/FullBlock.h"
#include "mcpe/level/Level.h"
#include "mcpe/gamemode/GameMode.h"

#include "ITPE/blocks/WoodPlanks/WoodPlanks.h"
#include "ITPE/blocks/Bookshelf/Bookshelf.h"

//Entity* e;
BlockSource* bs;

static bool (*_TessellateInWorld)(BlockTessellator*,Block &,BlockPos const&,unsigned char,bool);
static bool TessellateInWorld(BlockTessellator *tess,Block &block,BlockPos const &pos,unsigned char aux,bool b)
{
	Block* blockk = const_cast<Block*>(&block);
	int x = pos.x, y = pos.y, z = pos.z;
	//BlockSource
	*bs = tess -> getRegion();
	//Random Sand
	srand(x^y^z);
	/*Random Bookshelf*/
	unsigned char bookshelfraux = rand()%10;
	
	//Render Layer
	
	//Solid
	
	if(block.blockId == 5){
		if(bs -> getExtraData(pos) == 1){
			return _TessellateInWorld(tess,*Block::mBlocks[47],pos,0,b);
		}
		return _TessellateInWorld(tess,block,pos,aux,b);
	}
	else if(block.blockId == 47){
	    return _TessellateInWorld(tess,block,pos,bookshelfraux,b);
	}
	else{
		return _TessellateInWorld(tess,block,pos,aux,b);
	}
}

static void (*_InitClientData)();
static void InitClientData(){
	_InitClientData();
	
	/*Blocks*/
	//WoodPlanks
	Item::mItems[5] = new AuxDataBlockItem("wood_planks",5-256,Block::mBlocks[5]);
	
	//BookShelf
	Item::mItems[47] = new AuxDataBlockItem("book_shelf",47-256,Block::mBlocks[47]);
	
	/*Items*/
	//ExtraDataChanger
	Item::mItems[500] = new Item("block_changer",500-256);
	Item::mItems[500]->setIcon("block_changer",0);
	Item::mItems[500]->setIsGlint(true);
	Item::mItems[500]->setCategory(CreativeItemCategory::ITEMS);
}

static void (*_BG_InitBlocks)();
static void BG_InitBlocks(){
	_BG_InitBlocks();
	
	//WoodPlanks
    BlockGraphics::mBlocks[5]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[5]->setTextureItem("wood_planks");
	BlockGraphics::mBlocks[5]->setSoundType(BlockSoundType::WOOD);
	
	//BookShelf
    BlockGraphics::mBlocks[47]=new BlockGraphics("portal");
	BlockGraphics::mBlocks[47]->setTextureItem("book_shelf_top","book_shelf","book_shelf");
	BlockGraphics::mBlocks[47]->setSoundType(BlockSoundType::WOOD);
	
}

static void (*_Bl_InitBlocks)();
static void Bl_InitBlocks(){
	_Bl_InitBlocks();
	
	//WoodPlanks
    Block::mBlocks[5]=new WoodPlanks("wood_planks",5);
	
	//BookShelf
    Block::mBlocks[47]=new WoodPlanks("book_shelf",47);
}

static void (*_InitCreativeItems)();
static void InitCreativeItems(){
	_InitCreativeItems();
	
	//ExtraDataChanger
	Item::addCreativeItem(500,0);
	//WoodPlanks
	Item::addCreativeItem(5,6);
	Item::addCreativeItem(5,7);
	Item::addCreativeItem(5,8);
	Item::addCreativeItem(5,9);
	Item::addCreativeItem(5,10);
	Item::addCreativeItem(5,11);
	
	//WoodPlanks
	Item::addCreativeItem(47,1);
	Item::addCreativeItem(47,2);
	Item::addCreativeItem(47,3);
	Item::addCreativeItem(47,4);
	Item::addCreativeItem(47,5);
	Item::addCreativeItem(47,6);
	Item::addCreativeItem(47,7);
	Item::addCreativeItem(47,8);
	Item::addCreativeItem(47,9);
}

/*static void (*_NormalTick)(Entity*entity);
static void NormalTick(Entity*entity){
	_NormalTick(entity);
	
    ::e = entity;
	*bs = e -> getRegion();
}*/

static void (*_UseItemOn)(GameMode *, Player &, ItemInstance *, const BlockPos &, signed char, const Vec3 &);
static void UseItemOn(GameMode *gm, Player &p, ItemInstance *is, const BlockPos &pos, signed char c, const Vec3 &v3){
	if(is && is -> getId() == 500 && bs -> getBlock(pos) == Block::mBlocks[5]){
		unsigned short ed = bs -> getExtraData(pos);
		bs -> setExtraData(pos,ed + 1);
	}
	else{
		return _UseItemOn(gm,p,is,pos,c,v3);
	}
}

JNIEXPORT jint JNI_OnLoad(JavaVM*,void*){
	MSHookFunction((void *)&BlockTessellator::tessellateInWorld,(void *)TessellateInWorld,(void **)&_TessellateInWorld);
    MSHookFunction((void *)&Item::initClientData,(void *)InitClientData,(void **)&_InitClientData);
	MSHookFunction((void *)&Item::initCreativeItems,(void *)InitCreativeItems,(void **)&_InitCreativeItems);
	MSHookFunction((void *)&BlockGraphics::initBlocks,(void *)BG_InitBlocks,(void **)&_BG_InitBlocks);
	MSHookFunction((void *)&Block::initBlocks,(void *)Bl_InitBlocks,(void **)&_Bl_InitBlocks);
	//MSHookFunction((void *)&Entity::normalTick,(void *)NormalTick,(void **)&_NormalTick);
	MSHookFunction((void *)&GameMode::useItemOn,(void *)UseItemOn,(void **)&_UseItemOn);
	return JNI_VERSION_1_6;
}




