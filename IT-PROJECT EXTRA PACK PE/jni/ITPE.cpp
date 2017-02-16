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

#include "ITPE/blocks/WoodPlanks/WoodPlanks.h"
#include "ITPE/blocks/Bookshelf/Bookshelf.h"

//Entity* e;
//BlockSource* bs;

static bool (*_TessellateInWorld)(BlockTessellator*,Block &,BlockPos const&,unsigned char,bool);
static bool TessellateInWorld(BlockTessellator *tess,Block &block,BlockPos const &pos,unsigned char aux,bool b)
{
	Block* blockk = const_cast<Block*>(&block);
	int x = pos.x, y = pos.y, z = pos.z;
	srand(x^y^z);
	/*Random Bookshelf*/
	unsigned char bookshelfraux = rand()%10;
	
	//Render Layer
	
	//Solid
	
	if(block.blockId == 47){
	    return _TessellateInWorld(tess,block,pos,bookshelfraux,b);
	}
	else{
		return _TessellateInWorld(tess,block,pos,aux,b);
	}
}

static void (*_InitClientData)();
static void InitClientData(){
	_InitClientData();
	
	//WoodPlanks
	Item::mItems[5] = new AuxDataBlockItem("wood_planks",5-256,Block::mBlocks[5]);
	
	//BookShelf
	Item::mItems[47] = new AuxDataBlockItem("book_shelf",47-256,Block::mBlocks[47]);
	
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

JNIEXPORT jint JNI_OnLoad(JavaVM*,void*){
	MSHookFunction((void *)&BlockTessellator::tessellateInWorld,(void *)TessellateInWorld,(void **)&_TessellateInWorld);
    MSHookFunction((void *)&Item::initClientData,(void *)InitClientData,(void **)&_InitClientData);
	MSHookFunction((void *)&Item::initCreativeItems,(void *)InitCreativeItems,(void **)&_InitCreativeItems);
	MSHookFunction((void *)&BlockGraphics::initBlocks,(void *)BG_InitBlocks,(void **)&_BG_InitBlocks);
	MSHookFunction((void *)&Block::initBlocks,(void *)Bl_InitBlocks,(void **)&_Bl_InitBlocks);
	//MSHookFunction((void *)&Entity::normalTick,(void *)NormalTick,(void **)&_NormalTick);
	return JNI_VERSION_1_6;
}




