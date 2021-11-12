#include <cassert>

#include "RRTextureManager.h"


bool RRTextureManager::Initialize(MakeTextureInfo mtinfo) { 
	info = mtinfo;
	// текстуры инициализируются как-то так 
	textures[TextureType::forest]	= new RRTexture(LoadTexture("Textures\\Forest.png"));
	textures[TextureType::oil]		= new RRTexture(LoadTexture("Textures\\oil.png"));
	textures[TextureType::mountain] = new RRTexture(LoadTexture("Textures\\Mountain.png"));
	textures[TextureType::gold]		= new RRTexture(LoadTexture("Textures\\gold.png"));

	textures[TextureType::factory1]   = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory1.png"));
	textures[TextureType::factory2]   = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory2.png"));
	textures[TextureType::factory1_1] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory1_1.png"));
	textures[TextureType::factory2_1] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory2_1.png"));
	textures[TextureType::factory1_2] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory1_2.png"));
	textures[TextureType::factory2_2] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory2_2.png"));
	textures[TextureType::factory1_3] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory1_3.png"));
	textures[TextureType::factory2_3] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory2_3.png"));
	textures[TextureType::factory1_4] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory1_4.png"));
	textures[TextureType::factory2_4] = new RRTexture(LoadTexture("Textures\\Buildings\\Factory\\Factory2_4.png"));

	textures[TextureType::house1]   = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House1.png"));
	textures[TextureType::house2]   = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House2.png"));
	textures[TextureType::house1_1] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House1_1.png"));
	textures[TextureType::house2_1] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House2_1.png"));
	textures[TextureType::house1_2] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House1_2.png"));
	textures[TextureType::house2_2] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House2_2.png"));
	textures[TextureType::house1_3] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House1_3.png"));
	textures[TextureType::house2_3] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House2_3.png"));
	textures[TextureType::house1_4] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House1_3.png"));
	textures[TextureType::house2_4] = new RRTexture(LoadTexture("Textures\\Buildings\\House\\House2_3.png")); 

	textures[TextureType::spaceport1]   = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport1.png"));
	textures[TextureType::spaceport2]   = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport2.png"));
	textures[TextureType::spaceport1_1] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport1_1.png"));
	textures[TextureType::spaceport2_1] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport2_1.png"));
	textures[TextureType::spaceport1_2] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport1_2.png"));
	textures[TextureType::spaceport2_2] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport2_2.png"));
	textures[TextureType::spaceport1_3] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport1_3.png"));
	textures[TextureType::spaceport2_3] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport2_3.png"));
	textures[TextureType::spaceport1_4] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport1_4.png"));
	textures[TextureType::spaceport2_4] = new RRTexture(LoadTexture("Textures\\Buildings\\Spaceport\\Spaceport2_4.png")); 

	textures[TextureType::constructing1] = new RRTexture(LoadTexture("Textures\\Constructing1.png"));
	textures[TextureType::constructing2] = new RRTexture(LoadTexture("Textures\\Constructing2.png")); 

	textures[TextureType::tank1]	= new RRTexture(LoadTexture("Textures\\Tank1_1.png"));
	textures[TextureType::tank2]	= new RRTexture(LoadTexture("Textures\\Tank2_1.png"));
	textures[TextureType::worker1]	= new RRTexture(LoadTexture("Textures\\Man1.png"));
	textures[TextureType::worker2]	= new RRTexture(LoadTexture("Textures\\Man2.png"));
	textures[TextureType::scout1]	= new RRTexture(LoadTexture("Textures\\Scout1.png"));
	textures[TextureType::scout2]	= new RRTexture(LoadTexture("Textures\\Scout2.png")); 
	textures[TextureType::hpbar1]	= new RRTexture(LoadTexture("Textures\\UI\\HPBars\\HPBar_1.png")); 
	textures[TextureType::hpbar2]	= new RRTexture(LoadTexture("Textures\\UI\\HPBars\\HPBar_2.png")); 
	textures[TextureType::hpbar3]	= new RRTexture(LoadTexture("Textures\\UI\\HPBars\\HPBar_3.png")); 
	textures[TextureType::hpbar4]	= new RRTexture(LoadTexture("Textures\\UI\\HPBars\\HPBar_4.png")); 
	textures[TextureType::hpbar5]	= new RRTexture(LoadTexture("Textures\\UI\\HPBars\\HPBar_5.png")); 
	textures[TextureType::hpbar6]	= new RRTexture(LoadTexture("Textures\\UI\\HPBars\\HPBar_6.png")); 
	textures[TextureType::tankButton]  = new RRTexture(LoadTexture("Textures\\UI\\TankButton.png"));  
	textures[TextureType::scoutButton] = new RRTexture(LoadTexture("Textures\\UI\\ScoutButton.png"));

	textures[TextureType::manButton]    = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\ManButton.png"));  
	textures[TextureType::manButton1_1] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man1_1.png"));  
	textures[TextureType::manButton1_2] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man1_2.png"));  
	textures[TextureType::manButton1_3] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man1_3.png"));  
	textures[TextureType::manButton1_4] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man1_4.png"));  
	textures[TextureType::manButton2_1] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man2_1.png"));  
	textures[TextureType::manButton2_2] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man2_2.png"));  
	textures[TextureType::manButton2_3] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man2_3.png"));  
	textures[TextureType::manButton2_4] = new RRTexture(LoadTexture("Textures\\UI\\ManButton\\Man2_4.png"));  


	textures[TextureType::houseButton] = new RRTexture(LoadTexture("Textures\\UI\\HouseButton.png"));  
	textures[TextureType::spaceportButton] = new RRTexture(LoadTexture("Textures\\UI\\SpaceportButton.png"));  
	textures[TextureType::factoryButton] = new RRTexture(LoadTexture("Textures\\UI\\FactoryButton.png"));  
	textures[TextureType::field] = new RRTexture(LoadTexture("Textures\\UI\\Field.png"));
	textures[TextureType::buildingResIcon] = new RRTexture(LoadTexture("Textures\\UI\\BuildingResIcon.png"));
	textures[TextureType::goldIcon] = new RRTexture(LoadTexture("Textures\\UI\\GoldIcon.png"));
	textures[TextureType::fuelIcon] = new RRTexture(LoadTexture("Textures\\UI\\FuelIcon.png"));
	  

	return true;
}

void RRTextureManager::Shutdown() {
	// здесь выгружается память, выделенная под текстуры
	for (auto iter = textures.begin(); iter != textures.end(); ++iter) {
		iter->second->Destroy(); // удаляется текстура
		delete iter->second;  // удаляется указатель на неё
	}
}

RRTexture RRTextureManager::LoadTexture(const string& path) {
	RRTexture texture;
	texture.Load(path.c_str(), info);

	return texture;
}

RRTexture* RRTextureManager::GetTexture(TextureType type) {
	assert(type != TextureType::none);
	return textures[type];
}