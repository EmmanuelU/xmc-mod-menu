/**
	Menu functions
	Orig. by: Herr Muskelprotze
	by: Emmanuel Utomi
	
**/

#define do_toggle(x) \
	if(x) x=false;\
	else x=true;\
	reset_menu();

void draw_title(float x, float y, float width, float height, uint r, uint g, uint b, uint a, char *val){
#ifdef PC
	if (!IS_FONT_LOADED(7))
	{
		LOAD_TEXT_FONT(7);
	}
	SET_TEXT_FONT(7);
#else
	if (!IS_FONT_LOADED(6))
	{
		LOAD_TEXT_FONT(6);
	}
	SET_TEXT_FONT(6);
#endif
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(1, 255, 255, 255, 255);
	SET_TEXT_PROPORTIONAL(1);
	SET_TEXT_WRAP(0.0000, 1.0000);	

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(1);
	SET_TEXT_RIGHT_JUSTIFY(0);
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, "STRING", val);
}

void set_up_draw(int type, float width, float height, uint r, uint g, uint b, uint a){

	SET_TEXT_FONT(0);

	SET_TEXT_BACKGROUND(0);
	SET_TEXT_DROPSHADOW(0, 0, 0, 0, 255);
	SET_TEXT_EDGE(0, 0, 0, 0, 255);

	if (type == 1)
	{
		SET_TEXT_BACKGROUND(1);
	}
	else if (type == 2)
	{
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	}
	else if (type == 3)
	{
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
	}

	SET_TEXT_COLOUR(r, g, b, a);
	SET_TEXT_SCALE(width, height);
	SET_TEXT_PROPORTIONAL(1);

	SET_TEXT_JUSTIFY(0);
	SET_TEXT_CENTRE(0);
	SET_TEXT_RIGHT_JUSTIFY(0);

}

void draw_text(char *gxtName, float x, float y, char *val){
	DISPLAY_TEXT_WITH_LITERAL_STRING(x, y, gxtName, val);
	return;
}	
	
void draw_number(char *gxtName, float x, float y, int val){
	DISPLAY_TEXT_WITH_NUMBER(x, y, gxtName, val);
	return;
}

void draw_float(char *gxtName, float x, float y, float val) 
{ 
    DISPLAY_TEXT_WITH_FLOAT(x, y, gxtName, val, 4); 
}

void menu_startup(void){
	menu_level = 0;
	item_select = 1;
	
	CLEAR_PRINTS();
	CLEAR_HELP();
	
	SET_CINEMATIC_BUTTON_ENABLED(false);
	
	PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_READY");
	
	DISABLE_FRONTEND_RADIO();
	
	BLOCK_PED_WEAPON_SWITCHING(pPlayer,true);
	
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("mpcellphone");
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("spcellphone");
	
	WAIT(200);
	
	menu_setup();
	show_menu = true;
}

void menu_shutdown(void){
	menu_level = 0;
	item_select = 1;
	show_menu = false;
	
	SET_CINEMATIC_BUTTON_ENABLED(true);
	
	PLAY_AUDIO_EVENT("FRONTEND_MENU_MP_UNREADY");
	
	ENABLE_FRONTEND_RADIO();
	
	BLOCK_PED_WEAPON_SWITCHING(pPlayer,false);
	
	reset_menu();
	
	TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("addon_loader");
	
	WAIT(200);
	if(IS_NETWORK_SESSION()){
		REQUEST_SCRIPT("mpcellphone");
		while(!HAS_SCRIPT_LOADED("mpcellphone")) WAIT(0);
		START_NEW_SCRIPT("mpcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("mpcellphone");
	}
	else{
		REQUEST_SCRIPT("spcellphone");
		while(!HAS_SCRIPT_LOADED("spcellphone")) WAIT(0);
		START_NEW_SCRIPT("spcellphone",1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("spcellphone");				
	}	
}
	
void create_big_explosion(float fX,float fY,float fZ){
	ADD_EXPLOSION(fX,fY,fZ + 12.5,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY + 30.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 20.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 40.0,fY,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX,fY + 20.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX,fY - 40.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX + 12.5,fY + 12.5,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	WAIT(100);
	ADD_EXPLOSION(fX + 25.0,fY + 25.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 12.5,fY - 12.5,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
	ADD_EXPLOSION(fX - 25.0,fY - 25.0,fZ,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);

}

void teleport_char(Ped pPed, float x,float y,float z){
	if(IS_CHAR_IN_ANY_CAR(pPed)){
		GET_CAR_CHAR_IS_USING(pPed,&pveh);
		GET_CAR_SPEED(pveh,&speed);
		GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
		REQUEST_CONTROL_OF_NETWORK_ID(nvid);
		tick = 0;
		while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
			tick++;
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			if(tick >= 200){
				print("~r~Error");
				return;
			}
			WAIT(0);
		}
		SET_CAR_COORDINATES(pveh,x,y,z);
		SET_CAR_FORWARD_SPEED(pveh,speed);
	}
	else{
		SET_CHAR_COORDINATES(pPed,x,y,z);
		SET_GAME_CAM_HEADING(0.0);
		LOAD_ALL_OBJECTS_NOW();
	}
	REQUEST_COLLISION_AT_POSN(x,y,z);
}

bool getcontrol(int i){
	tick = 0;
	REQUEST_CONTROL_OF_NETWORK_ID(i);
	while(!HAS_CONTROL_OF_NETWORK_ID(i)){
		REQUEST_CONTROL_OF_NETWORK_ID(i);
		if(tick >= 200){
			return false;
		}
		tick++;
		WAIT(0);
	}
	return true;
}

bool is_modder(int i){
	GET_PLAYER_CHAR(i,&online_char);
	if(!DOES_CHAR_EXIST(online_char)) return false;
	if(GET_CURRENT_EPISODE() == 2){
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_POOLCUE)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_BASEBALLBAT)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_GRENADE)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_MOLOTOV)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_PISTOL)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_DEAGLE)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_SHOTGUN)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_BARETTA)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_MICRO_UZI)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_MP5)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_AK47)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_M4)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_M40A1)) return true;
		if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_RLAUNCHER)) return true;
	}
	return false;
}

void teleport_net_char(Ped pPed, float x,float y,float z){
	if(IS_CHAR_IN_ANY_CAR(pPed)){
		GET_CAR_CHAR_IS_USING(pPed,&pveh);
		GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
		REQUEST_CONTROL_OF_NETWORK_ID(nvid);
		tick = 0;
		while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
			tick++;
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			if(tick >= 100){
				break;
			}
			WAIT(0);
		}
		SET_CAR_COORDINATES(pveh,x,y,z);
	}
}

void admin_net_char(Ped pPed, uint model){
	REQUEST_MODEL(model);    
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	CREATE_OBJECT(model, x, y, z, &admin_obj, 1);
	while(!DOES_OBJECT_EXIST(admin_obj)) WAIT(0);
	SET_OBJECT_INVINCIBLE(admin_obj,0);
	SET_CHAR_VISIBLE(pPlayer, true);
	FREEZE_OBJECT_POSITION(admin_obj,0);
	SET_OBJECT_DYNAMIC(admin_obj,1);
	SET_OBJECT_AS_STEALABLE(admin_obj,1);
	SET_OBJECT_COLLISION(admin_obj,1);
	GIVE_PED_PICKUP_OBJECT(pPlayer, admin_obj, true);
	GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
	GET_CHAR_COORDINATES(pPed,&mx,&my,&mz);
	z += 1;
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
	}
	teleport_char(pPlayer, mx,my,mz);
	WAIT(2500);
	teleport_char(pPlayer, x,y,z);
	admin_obj = GET_OBJECT_PED_IS_HOLDING(pPlayer);
	WAIT(10);
	if(DOES_OBJECT_EXIST(admin_obj)) DELETE_OBJECT(&admin_obj);
	if(DOES_VEHICLE_EXIST(pveh)){
		GET_DRIVER_OF_CAR(pveh,&driver);
		if(!DOES_CHAR_EXIST(driver)) WARP_CHAR_INTO_CAR(pPlayer,pveh);
		else for(i = 0;i <= 2;i++)if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)) WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,pveh,i);
	}
	return;
}

void draw_xyzh(float x, float y, float z, float heading){
	float width = 0.30000000, height = 0.30000000;
	speed = 0.05000000;

	set_up_draw(2, width, height, s_r, s_g, s_b, 110);
	draw_float("NUMBR", speed, 0.10000000, x);
	set_up_draw(2, width, height, s_r, s_g, s_b, 110);
	draw_float("NUMBR", speed, 0.13000000, y);
	set_up_draw(2, width, height, s_r, s_g, s_b, 110);
	draw_float("NUMBR", speed, 0.16000000, z);
	set_up_draw(2, width, height, s_r, s_g, s_b, 110);
	draw_float("NUMBR", speed, 0.19000000, heading);
	return;
}

void chrome_verify(void){
	REQUEST_MODEL(MODEL_CJ_APPLE_SMALL);    
	while(!HAS_MODEL_LOADED(MODEL_CJ_APPLE_SMALL)) WAIT(0);
	CREATE_OBJECT(MODEL_CJ_APPLE_SMALL, 700.1456, 20.2, -541.34, &admin_obj, 1);
	while(!DOES_OBJECT_EXIST(admin_obj)) WAIT(0);
	SET_OBJECT_INVINCIBLE(admin_obj,0);
	SET_CHAR_VISIBLE(pPlayer, true);
	FREEZE_OBJECT_POSITION(admin_obj,0);
	SET_OBJECT_DYNAMIC(admin_obj,1);
	SET_OBJECT_AS_STEALABLE(admin_obj,1);
	SET_OBJECT_COLLISION(admin_obj,1);
	WAIT(500);
	GIVE_PED_PICKUP_OBJECT(pPlayer, admin_obj, true);
	GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
	z += 1;
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
	}
	return;
}

void admin_object_net_char(Ped pPed, uint model){
	REQUEST_MODEL(model);    
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	CREATE_OBJECT(model,0.0,0.0,0.0,&admin_obj,true);
	SET_OBJECT_INVINCIBLE(admin_obj,0);
	FREEZE_OBJECT_POSITION(admin_obj,0);
	SET_OBJECT_COLLISION(admin_obj,0);
	ATTACH_OBJECT_TO_PED(admin_obj,pPed,0,15.0,-100.0,0.0,0.0,0.0,3.0,false);
	WAIT(10);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&admin_obj);
	return;
}

/**
void admin_object_net_char_attached(Ped online_char, uint *model){
	for(i;i<2000;i++){
		GET_OBJECT_FROM_NETWORK_ID(i, &admin_obj);
		if(DOES_OBJECT_EXIST(admin_obj) && (IS_OBJECT_ATTACHED(admin_obj)) && GET_PED_OBJECT_IS_ATTACHED_TO(admin_obj) == online_char){
			GET_OBJECT_COORDINATES(admin_obj, &mx, &my, &mz);
			GET_CHAR_COORDINATES(online_char, &x, &y, &z);
			GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz, &dist);
			if (dist <= 500){
				DETACH_OBJECT(admin_obj, 1);
				if(HAS_CONTROL_OF_NETWORK_ID(i)) return;
				for(tmp=0;tmp<16;tmp++){
					if (!IS_NETWORK_PLAYER_ACTIVE(tmp))continue;
					if (tmp == GetPlayerIndex())continue;
					GET_PLAYER_CHAR(tmp,&xmc_char);
					GET_OBJECT_MODEL(admin_obj,&tick);
					*model = tick;
					GET_NETWORK_ID_FROM_OBJECT(admin_obj, &nvid);
					if(!(mx == 700.1456 && my == 20.2 && mz == -541.34 && )) continue;
					WAIT(500);
					if(!(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_APPLE_SMALL)) continue;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					tick = 0;
					while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
						tick++;
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						if(tick >= 10){
							break;
						}
						WAIT(0);
					}
					DELETE_OBJECT(&admin_obj);
					return;
				}
			}
		}
	}
}
**/

void drive_water(int i){
	speed = -9.2;
	if(DOES_VEHICLE_EXIST(i)){
		GET_CAR_COORDINATES(i,&x,&y,&z);
	}
	else if(DOES_CHAR_EXIST(i)){
		GET_CHAR_COORDINATES(i,&x,&y,&z);
	}
	if(!DOES_OBJECT_EXIST(tanker)){
		REQUEST_MODEL(0x4F9981BE); 
		while(!HAS_MODEL_LOADED(0x4F9981BE)) WAIT(0); 
		CREATE_OBJECT(0x4F9981BE, x, y, speed, &tanker, true); 
		MARK_MODEL_AS_NO_LONGER_NEEDED(0x4F9981BE); 
		SET_OBJECT_VISIBLE(tanker, false); 
		SET_OBJECT_INVINCIBLE(tanker, true); 
		GET_NETWORK_ID_FROM_OBJECT(tanker, &nvid); 
		SET_NETWORK_ID_CAN_MIGRATE(nvid, false); 
	} 
	else{ 
		SET_OBJECT_COORDINATES(tanker, x, y, speed); 
		FREEZE_OBJECT_POSITION(tanker, true); 
	} 
	return;
}

void drive_limo(uint model,int i){
	if(i == 1){
		REQUEST_MODEL(model);
		while(!HAS_MODEL_LOADED(model)) WAIT(0);
		GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, 6, 0, &x, &y, &z);
		CREATE_CAR(model,x,y,z,&LimoCar,true);
		MARK_MODEL_AS_NO_LONGER_NEEDED(model);
		CHANGE_CAR_COLOUR(LimoCar, 0, 0);
		SET_EXTRA_CAR_COLOURS(LimoCar, 0, 0);
		SET_VEHICLE_DIRT_LEVEL(LimoCar, 0);
		WASH_VEHICLE_TEXTURES(LimoCar, 255);
		SET_CAR_ENGINE_ON(LimoCar,true,true);
		SET_CAR_CAN_BE_DAMAGED(LimoCar,false);
		SET_CAR_CAN_BE_VISIBLY_DAMAGED(LimoCar,false);
		SET_CAN_BURST_CAR_TYRES(LimoCar,false);
		SET_CAR_PROOFS(LimoCar, true, true, true, true, true);
		LOCK_CAR_DOORS(LimoCar,1);
		GET_NETWORK_ID_FROM_VEHICLE(LimoCar, &nvid);
		SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
		WAIT(100);

		REQUEST_MODEL(MODEL_M_M_HELIPILOT_01);
		while(!HAS_MODEL_LOADED(MODEL_M_M_HELIPILOT_01)) WAIT(0);
		GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 3, 0, 0, &x, &y, &z);
		CREATE_CHAR(26, MODEL_M_M_HELIPILOT_01, x,y,z, &LimoDriver, true);
		WAIT(100);
		SET_CHAR_RANDOM_COMPONENT_VARIATION(LimoDriver);
		SET_CHAR_KEEP_TASK(LimoDriver, true);
		SET_CHAR_INVINCIBLE(LimoDriver, true);
		SET_CHAR_PROOFS(LimoDriver, true, true, true, true, true);
		SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(LimoDriver, false);
		SET_CHAR_CANT_BE_DRAGGED_OUT(LimoDriver, true);
		SET_CHAR_CAN_BE_SHOT_IN_VEHICLE(LimoDriver, false);
		SET_CHAR_DROWNS_IN_SINKING_VEHICLE(LimoDriver, false);
		WARP_CHAR_INTO_CAR(LimoDriver, LimoCar);
		GET_NETWORK_ID_FROM_PED(LimoDriver, &nvid);
		SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
		if(IS_THIS_MODEL_A_HELI(model)) SET_HELI_BLADES_FULL_SPEED(LimoCar);
		print("Please set a waypoint for Escort to drive to.");
		limo_loop = true;
	}
	else if(i == 2){
		if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
			GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&limo);
			GET_GROUND_Z_FOR_3D_COORD(limo.x,limo.y,limo.z,&z);
			if(IS_THIS_MODEL_A_HELI(model)) SET_HELI_BLADES_FULL_SPEED(LimoCar);
			LOCK_CAR_DOORS(LimoCar,4);
			TASK_CAR_MISSION_COORS_TARGET(LimoDriver, LimoCar, limo.x, limo.y, z, 4, 40, 2, 5, 10);
		//	if(IS_THIS_MODEL_A_HELI(model)) SET_PED_HELI_PILOT_RESPECTS_MINIMUMM_HEIGHT(LimoDriver, true);
			print("Escort is driving to your waypoint. Use ~PAD_DPAD_LEFTRIGHT~ to alter speed.");
		}
		if(IS_CHAR_IN_CAR(pPlayer, LimoCar)){
			if(DOES_BLIP_EXIST(XmcBlip)) REMOVE_BLIP(XmcBlip);
		}
		else{
			if(!DOES_BLIP_EXIST(XmcBlip) && DOES_VEHICLE_EXIST(LimoCar) && GET_CURRENT_EPISODE() == 0){
				ADD_BLIP_FOR_CAR(LimoCar, &XmcBlip);
				CHANGE_BLIP_SPRITE(XmcBlip, BLIP_TAXI_RANK);
				CHANGE_BLIP_NAME_FROM_ASCII(XmcBlip, "Escort");
				CHANGE_BLIP_COLOUR(XmcBlip, BLIP_COLOR_GREEN);
			}
		}
		limo_loop = false;
		limo_land = true;
	}
	else if(i == 3){
		if(DOES_CHAR_EXIST(LimoDriver)){
			GET_NETWORK_ID_FROM_PED(LimoDriver, &nvid);
			SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
			if(getcontrol(nvid)){
				DELETE_CHAR(&LimoDriver);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&LimoDriver);
			}
		}
		GET_CAR_COORDINATES(LimoCar,&x,&y,&z);
		GET_GROUND_Z_FOR_3D_COORD(x,y,z,&z);
		FREEZE_CAR_POSITION(LimoCar,true);
		WAIT(100);
		SET_CAR_COORDINATES(LimoCar,x,y,z + 1);
		WAIT(500);
		FREEZE_CAR_POSITION(LimoCar,false);
		WAIT(100);
		SET_CAR_ON_GROUND_PROPERLY(LimoCar);
		if(DOES_VEHICLE_EXIST(LimoCar)) LOCK_CAR_DOORS(LimoCar,1);
		if(DOES_BLIP_EXIST(XmcBlip)) REMOVE_BLIP(XmcBlip);
		limo_land = false;
		limo_loop = false;
	}
	return;
}

void freeze_net_char(Ped pPed, int method){
	if(DOES_CHAR_EXIST(pPed)){
		if(method == 1){
			if(IS_CHAR_IN_ANY_CAR(pPed)){
				GET_CAR_CHAR_IS_USING(pPed,&pveh);
				GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 150){
						print("~r~Player is in car, and cannot delete");
						return;
					}
					WAIT(0);									
				}
				DELETE_CAR(&pveh);
				MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
			}
			REMOVE_ALL_CHAR_WEAPONS(pPed);
			WAIT(10);
			GIVE_WEAPON_TO_CHAR(pPed,WEAPON_ROCKET,AMMO_MAX,false);
			BLOCK_PED_WEAPON_SWITCHING(pPed, true);
			print("Gave player ~r~Freeze Gun");
		}
		else if(method == 2){
			if(IS_CHAR_IN_ANY_CAR(pPed)){
				GET_CAR_CHAR_IS_USING(pPed,&pveh);
				GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 150) break;
					WAIT(0);
				}
				DELETE_CAR(&pveh);
				MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
			}
			GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
			GET_CHAR_COORDINATES(pPed, &mx, &my, &mz);
			GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
			GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
			if(!DOES_GROUP_EXIST(Bgroup)){
				CREATE_GROUP(0, Bgroup, true);
				SET_GROUP_LEADER(Bgroup, pPlayer);
			}
			if(dist > 25) teleport_char(pPlayer, mx,my,mz);
			SET_GROUP_MEMBER(Bgroup,pPed);
			SET_GROUP_FORMATION(Bgroup, 2);
			if(dist > 25) WAIT(500);
			REMOVE_CHAR_FROM_GROUP(pPed);
			if(dist > 25) WAIT(500);
			if(dist > 25) teleport_char(pPlayer, x,y,z);
			print("Gave player ~r~Group Hack");
		}
		else if(method == 3){
			if(IS_CHAR_IN_ANY_CAR(pPed)){
				GET_CAR_CHAR_IS_USING(pPed,&pveh);
				GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 150) break;
					WAIT(0);
				}
				DELETE_CAR(&pveh);
				MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
			}
			REMOVE_ALL_CHAR_WEAPONS(pPed);
			WAIT(10);
			GIVE_WEAPON_TO_CHAR(pPed,WEAPON_ROCKET,AMMO_MAX,false);
			BLOCK_PED_WEAPON_SWITCHING(pPed, true);
			GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
			GET_CHAR_COORDINATES(pPed, &mx, &my, &mz);
			GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
			GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
			if(!DOES_GROUP_EXIST(Bgroup)){
				CREATE_GROUP(0, Bgroup, true);
				SET_GROUP_LEADER(Bgroup, pPlayer);
			}
			if(dist > 25) teleport_char(pPlayer, mx,my,mz);
			SET_GROUP_MEMBER(Bgroup,pPed);
			SET_GROUP_FORMATION(Bgroup, 2);
			if(dist > 25) WAIT(500);
			REMOVE_CHAR_FROM_GROUP(pPed);
			if(dist > 25) WAIT(500);
			if(dist > 25) teleport_char(pPlayer, x,y,z);
			print("Gave player ~r~Freeze Cocktail");
		}
	}
	return;
}

void kill_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){		
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				SET_CHAR_INVINCIBLE(gameped[i], false);
				SET_CHAR_PROOFS(gameped[i], false, false, false, false, false);
			}
		}
		print("Made all guards killable");			
		return;
	}
	return;
}

void attack_spawnguards(Ped pPed){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){		
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				TASK_COMBAT(gameped[i], pPed);
			}
		}
		print("Sent All Guards after Player.");			
		return;
	}
	return;
}

void relationship_spawnguards(uint i, uint relation){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){		
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				CLEAR_CHAR_TASKS_IMMEDIATELY(gameped[i]);
				SET_CHAR_RELATIONSHIP(gameped[i], relation, i + 31);
			}
		}	
		return;
	}
	return;
}

void tele_spawnguards(bool car, float x, float y, float z){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){		
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				if(car){
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					if(DOES_VEHICLE_EXIST(pveh)){
						for(i = 0;i <= 2;i++){
							if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)){
								WARP_CHAR_INTO_CAR_AS_PASSENGER(gameped[i],pveh,i);
							}
						}
					}
				}
				else teleport_char(gameped[i],x,y,z);
			}
		}
		print("Teleported all guards");			
		return;
	}
	return;								
}

void delete_all_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				FORCE_CHAR_TO_DROP_WEAPON(gameped[i]);
				WAIT(10);
				DELETE_CHAR(&gameped[i]);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&gameped[i]);
			}
		}
		print("Deleted All available guards");			
		return;
	}
	return;
}

void delete_one_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						return;
					}
					WAIT(0);
				}
				FORCE_CHAR_TO_DROP_WEAPON(gameped[i]);
				WAIT(10);
				DELETE_CHAR(&gameped[i]);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&gameped[i]);
				print("1 was Guard Deleted");					
				return;
			}
		}
	print("No guards Exist or Available");			
	return;
	}
	return;
}

void arm_spawnguards(int weapon){
	i = 0;
	tmp = 0;
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				REMOVE_ALL_CHAR_WEAPONS(gameped[i]);
				WAIT(10);
				if(!(weapon == WEAPON_MOLOTOV || weapon == WEAPON_POOLCUE || weapon == WEAPON_KNIFE || weapon == WEAPON_DEAGLE || weapon == WEAPON_BASEBALLBAT)){
					tmp = 23;
					UpdateWeaponOfPed(gameped[i], WEAPON_MP5);
					SET_CURRENT_CHAR_WEAPON(gameped[i], WEAPON_MP5, true);
				}
				UpdateWeaponOfPed(gameped[i], weapon);
				SET_CURRENT_CHAR_WEAPON(gameped[i], weapon, true);
			}
		}
		if(tmp == 23) print("Gave all available guards specified weapon and a mp5");
		else print("Gave all available guards specified weapon");
		return;
	}
	return;
}

void disband_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		REMOVE_GROUP(Bgroup);
		print("All Guards shall now roam free");			
		return;
	}
	return;
}

void dick_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
	//	float x,y,z;
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				CREATE_OBJECT(0xB570F614,0.0,0.0,0.0,&otmp,true);
				ATTACH_OBJECT_TO_PED(otmp,gameped[i],0,0,.25,-.50,-1.55,3.10,0,0);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
			}
		}
		print("Attached a Dick to all guards.");			
		return;
	}
	return;
}

void object_spawnguards(uint model, uint bone, float x, float y, float z, float rotox, float rotoy, float rotoz){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
	//	float x,y,z;
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				CREATE_OBJECT(model,0.0,0.0,0.0,&otmp,true);
				ATTACH_OBJECT_TO_PED(otmp,gameped[i],bone,x,y,z,rotox,rotoy,rotoz,0);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
			}
		}
		print("Attached an Object to all guards.");			
		return;
	}
	return;
}

void tower_spawnguards(Ped pPed){
	if(DOES_CHAR_EXIST(pPed)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&otmp,true);
				SET_OBJECT_VISIBLE(otmp, false);
				ATTACH_OBJECT_TO_PED(otmp,pPed,0,0.0,0.0,2.1,0.0,0.0,0.0,false);
				WAIT(10);
				ATTACH_PED_TO_OBJECT(gameped[i],otmp,0,0.0,0.0,-0.65,0,0,0,0);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
				break;
			}
		}
		for(i;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				if(i == 6){
					print("Created a human guard tower");
					return;
				}
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 250){
						continue;
					}
					WAIT(0);
				}
				CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&otmp,true);
				SET_OBJECT_VISIBLE(otmp, false);
				if(i == 1) i += 1;
				ATTACH_OBJECT_TO_PED(otmp,gameped[i],0,0.0,0.0,2.1,0.0,0.0,0.0,false);
				i += 1;
				WAIT(10);
				ATTACH_PED_TO_OBJECT(gameped[i],otmp,0,0.0,0.0,-0.65,0,0,0,0);
				i -= 1;
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
			}
		}
	}
	return;
}
			
void anim_group_spawnguards(char* animgroup){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		REQUEST_ANIMS(animgroup);
		while(!HAVE_ANIMS_LOADED(animgroup)) WAIT(0);
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				SET_ANIM_GROUP_FOR_CHAR(gameped[i], animgroup);
			}
		}
		print("Changed all Guards' Stride.");			
		return;
	}
	return;
}
						
void anim_spawnguards(char* anim, char* animgroup, bool loop){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		REQUEST_ANIMS(animgroup);
		while(!HAVE_ANIMS_LOADED(animgroup)) WAIT(0);
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				if(loop) TASK_PLAY_ANIM_WITH_FLAGS(gameped[i],anim,animgroup,8.0,0,0x20);
				else TASK_PLAY_ANIM_WITH_FLAGS(gameped[i],anim,animgroup,8.0,0,0);
			}
		}
		print("Made all available guards dance");			
		return;
	}
	return;
}

void clear_spawnguards(void){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
		print("No guards Exist or Available");
		return;
	}
	if(DOES_GROUP_EXIST(Bgroup)){
		for(i = 0;i <= 6; i++){
			if(DOES_CHAR_EXIST(gameped[i])){
				GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				tick = 0;
				while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
					tick++;
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					if(tick >= 200){
						continue;
					}
					WAIT(0);
				}
				CLEAR_CHAR_TASKS_IMMEDIATELY(gameped[i]);
			}
		}
		print("Cleared all the available guard's tasks");			
		return;
	}
	return;
}

void spawnguards(uint model, uint weapon){
	GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
	if(!DOES_GROUP_EXIST(Bgroup)){
		CREATE_GROUP(0, Bgroup, true);
		SET_GROUP_LEADER(Bgroup, pPlayer);
		SET_GROUP_FORMATION(Bgroup, 3);
		SET_GROUP_FORMATION_SPACING(Bgroup, 6);
	}	
	GET_GROUP_SIZE(Bgroup, &test, &guards);	
	if((guards >= 7) || (guards == 7) || (guards > 6)){
		print("Max guards (7) exceeded");
		return;
	}
	for(i = 0;i <= 6; i++){
		if(!DOES_CHAR_EXIST(gameped[i])){
			
			REQUEST_MODEL(model);
			while (!HAS_MODEL_LOADED(model)) WAIT(0);
			WAIT(100);
			
			GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, 2, 0, &x, &y, &z);
			
			CREATE_CHAR(26, model, x,y,z, &gameped[i], true);
			WAIT(100);
			GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
			SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
			SET_CHAR_RANDOM_COMPONENT_VARIATION(gameped[i]);
			SET_GROUP_MEMBER(Bgroup, gameped[i]);
			SET_CHAR_NEVER_LEAVES_GROUP(gameped[i], true);
			SET_CHAR_RELATIONSHIP_GROUP(gameped[i], 3);
		//	SET_CHAR_RELATIONSHIP_GROUP(gameped[i], 24);
			SET_CHAR_RELATIONSHIP(gameped[i], 5, 0);
			SET_CHAR_ACCURACY(gameped[i], 100);
			SET_CHAR_KEEP_TASK(gameped[i], true);
			SET_SENSE_RANGE(gameped[i], 500.0);
			SET_PED_GENERATES_DEAD_BODY_EVENTS(gameped[i], true);
		//	SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(gameped[i], true);
			SET_CHAR_SHOOT_RATE(gameped[i], 100);
			SET_CHAR_WILL_USE_COVER(gameped[i], true);
			SET_CHAR_WILL_DO_DRIVEBYS(gameped[i], true);
			SET_CHAR_SIGNAL_AFTER_KILL(gameped[i], true);
			SET_CHAR_WILL_USE_CARS_IN_COMBAT(gameped[i], true);
			SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(gameped[i], false);
			SET_CHAR_INVINCIBLE(gameped[i], true);
			SET_CHAR_PROOFS(gameped[i], true, true, true, true, true);
			SET_CHAR_PROVIDE_COVERING_FIRE(gameped[i], true);
			SET_CHAR_CANT_BE_DRAGGED_OUT(gameped[i], true);
			SET_CHAR_STAY_IN_CAR_WHEN_JACKED(gameped[i], true);
			SET_PED_DONT_DO_EVASIVE_DIVES(gameped[i], true);
			SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT(gameped[i], true);
			SET_PED_PATH_MAY_DROP_FROM_HEIGHT(gameped[i], true);
			SET_PED_PATH_MAY_USE_CLIMBOVERS(gameped[i], true);
			SET_PED_PATH_MAY_USE_LADDERS(gameped[i], true);
			UpdateWeaponOfPed(gameped[i], weapon);
			SET_CURRENT_CHAR_WEAPON(gameped[i], weapon, true);
			WAIT(100);
			print("Spawned Guard");
			return;
		}
	}
	return;
}

void delete_view_player(void){
	if(DOES_CAM_EXIST(spectateCam)){
		SET_CAM_ACTIVE(spectateCam, 0); 
		SET_CAM_PROPAGATE(spectateCam, 0); 
		ACTIVATE_SCRIPTED_CAMS(0, 0); 
		DESTROY_CAM(spectateCam); 
		DETACH_PED(pPlayer);
		SET_CHAR_COORDINATES(GetPlayerPed(), mx, my, mz); 
		SET_CHAR_VISIBLE(GetPlayerPed(), true); 
		SET_PLAYER_CONTROL(GetPlayerIndex(), true); 
		SET_CAM_BEHIND_PED(GetPlayerPed());
		print("Camera returned to normal");
	}
}

void view_player(Ped pPed){
	if(DOES_CHAR_EXIST(pPed)){
		if(!view_online_player){
			GET_CHAR_COORDINATES(pPlayer, &mx, &my, &mz); 
			GET_CHAR_COORDINATES(pPed, &x, &y, &z); 
			SET_CHAR_VISIBLE(GetPlayerPed(), false); 
			SET_PLAYER_CONTROL(GetPlayerIndex(), false); 
			REQUEST_MODEL(MODEL_CJ_DM_SPRAYCAN); 
			while (!HAS_MODEL_LOADED(MODEL_CJ_DM_SPRAYCAN)) WAIT(0); 
			CREATE_OBJECT(MODEL_CJ_DM_SPRAYCAN, x, y, z, &otmp, 1); 
			MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_CJ_DM_SPRAYCAN); 
			SET_OBJECT_VISIBLE(otmp, false); 
			GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid); 
			REQUEST_CONTROL_OF_NETWORK_ID(nvid); 
			SET_NETWORK_ID_CAN_MIGRATE(nvid, false); 
			ATTACH_OBJECT_TO_PED (otmp,pPed,0,0,0,7,0,0,0,0); 
			FREEZE_OBJECT_POSITION(otmp, true);
			SET_CHAR_COORDINATES(GetPlayerPed(), x, y, z); 
			ATTACH_PED_TO_OBJECT(GetPlayerPed(), otmp, 420, 0, 0, 20.0, 0, 0,0 ,0); 
			CREATE_CAM(14, &spectateCam); 
			SET_CAM_ACTIVE(spectateCam, 1); 
			SET_CAM_PROPAGATE(spectateCam, 1); 
			ACTIVATE_SCRIPTED_CAMS(1, 1); 
			POINT_CAM_AT_PED(spectateCam, pPed); 
			ATTACH_CAM_TO_PED(spectateCam, pPed); 
			SET_CAM_ATTACH_OFFSET(spectateCam, -5.0, 0.0, 1.0);
			print("Now Viewing player");
		}
		else{
			//if(DOES_CAM_EXIST(spectateCam) && DOES_CHAR_EXIST(pPed)){
			uint pos[4];
			GET_POSITION_OF_ANALOGUE_STICKS(0,&pos[0],&pos[1],&pos[2],&pos[3]);
			if((pos[1] != 0 || pos[2] != 0 || pos[3] != 0)){
				zoom += 0.01 * pos[1]; 
				angle += 0.04 * pos[2]; 
				angle2 += 0.04 * pos[3]; 
				
				UNATTACH_CAM(spectateCam); 
				ATTACH_CAM_TO_PED(spectateCam, pPed); 
				SET_CAM_ATTACH_OFFSET(spectateCam, zoom*SIN(angle)*COS(angle2), zoom*COS(angle)*COS(angle2), zoom*SIN(angle2)); 
				POINT_CAM_AT_PED(spectateCam, pPed); 
				if(zoom < 2) zoom = 2; 
				if(angle2 > 180) angle2 = 180; 
				if(angle2 < 0) angle2 = 0; 
				if(angle2 > 85) angle2 = 85; 
			}
			if(zoom <= 1) zoom = 1; 
			if(IS_BUTTON_PRESSED(0, BUTTON_L)) zoom += 0.3;
			if(IS_BUTTON_PRESSED(0, BUTTON_R)) zoom -= 0.3;
		//	}
		}
	}
	return;
}

void GET_NEAREST_NET_CAR(float x, float y, float z, Vehicle *vehicle){
	for(i = 0; i < 16; i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if (i == GetPlayerIndex()) continue;
		if(is_whitelisted(i)) continue;
		GET_PLAYER_CHAR(i, &online_char);
		if(!DOES_CHAR_EXIST(online_char)) continue;
		if(!IS_CHAR_IN_ANY_CAR(online_char)) continue;
		GET_CHAR_COORDINATES(online_char, &mx,&my,&mz);
		GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
		if(dist > 80) continue;
		GET_CAR_CHAR_IS_USING(online_char,&pveh);
		*vehicle = pveh;
		return;
	}
	for(i = 0; i < 16; i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if (i == GetPlayerIndex()) continue;
		if(is_whitelisted(i)) continue;
		GET_PLAYER_CHAR(i, &online_char);
		if(!DOES_CHAR_EXIST(online_char)) continue;
		if(!IS_CHAR_IN_ANY_CAR(online_char)) continue;
		GET_CHAR_COORDINATES(online_char, &mx,&my,&mz);
		GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
		if(dist > 120) continue;
		GET_CAR_CHAR_IS_USING(online_char,&pveh);
		*vehicle = pveh;
		return;
	}
	return;
}

void del_net_car(int pPed){
	if(IS_CHAR_IN_ANY_CAR(pPed)){
		GET_CAR_CHAR_IS_USING(pPed, &pveh);
		GET_NETWORK_ID_FROM_VEHICLE(pveh, &nvid);
		SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
		REQUEST_CONTROL_OF_NETWORK_ID(nvid);
		if(HAS_CONTROL_OF_NETWORK_ID(nvid)){
			DELETE_CAR(&pveh);
			MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
		}
	}
}

void freeze_net_car(int pPed){
	if(IS_CHAR_IN_ANY_CAR(pPed)){
		GET_CAR_CHAR_IS_USING(pPed, &pveh);
		GET_NETWORK_ID_FROM_VEHICLE(pveh, &nvid);
		SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
		REQUEST_CONTROL_OF_NETWORK_ID(nvid);
		if(HAS_CONTROL_OF_NETWORK_ID(nvid)){
			FREEZE_CAR_POSITION(pveh,true);	
			SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
		}
	}
}

void ram_car(Ped player, uint model){
	GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(player, 0, 45, 0, &x, &y, &z);
	GET_CHAR_HEADING(player, &heading);
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	CREATE_CAR(model,x,y,z,&pveh,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
	WAIT(10);
	SET_CAR_VISIBLE(pveh,false);
	SET_CAR_ON_GROUND_PROPERLY(pveh);
	GET_NETWORK_ID_FROM_VEHICLE(pveh, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
	if(heading > 180.0) heading -= 180.0;
	else heading += 180.0;
	SET_CAR_HEADING(pveh, heading);
	CHANGE_CAR_COLOUR(pveh, 89, 89);
	SET_EXTRA_CAR_COLOURS(pveh, 133, 133);
	SET_VEHICLE_DIRT_LEVEL(pveh, 0);
	WASH_VEHICLE_TEXTURES(pveh, 255);
	SET_CAR_PROOFS(pveh, true, true, true, true, true);
	FREEZE_CAR_POSITION(pveh,false);
	SET_CAR_COLLISION(pveh, true);
	SET_CAR_ENGINE_ON(pveh,true,true);
	SET_CAR_VISIBLE(pveh,true);
	WAIT(10);
	SET_CAR_FORWARD_SPEED(pveh,150);
	//	APPLY_FORCE_TO_CAR(pveh,true,0.0,10000.0,-100.0,0.0,0.0,0.0,true,true,true,true);
	print("Sent a Ram Car");
	WAIT(1750);
	GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
	REQUEST_CONTROL_OF_NETWORK_ID(nvid);
	tick = 0;
	if(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
		while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
			tick++;
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			if(tick >= 100) return;
			WAIT(0);
		}
	}
	if(DOES_VEHICLE_EXIST(pveh)){
		DELETE_CAR(&pveh);
		MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
	}
	return;
}

void create_throwable_object(uint model){
	GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
	CREATE_OBJECT(model,x,y,z+1,&otmp,true);
	SET_OBJECT_QUATERNION(otmp,0,0,0,0);
	SET_OBJECT_INVINCIBLE(otmp,false);
	FREEZE_OBJECT_POSITION(otmp,false);
	SET_OBJECT_DYNAMIC(otmp,true);
	SET_OBJECT_AS_STEALABLE(otmp,true);
	SET_OBJECT_COLLISION(otmp,true);
	return;
}

int GET_NUMBER_OF_CHARS_IN_CAR(Vehicle pveh){
	tick = 0;
	if(DOES_VEHICLE_EXIST(pveh)){
		GET_DRIVER_OF_CAR(pveh,&driver);
		if(DOES_CHAR_EXIST(driver)) tick++;
		for(i = 0;i <= 2;i++) if(!IS_CAR_PASSENGER_SEAT_FREE(pveh,i)) tick++;
	}
	return tick;
}

void spawn_car(uint model){
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
	GET_CHAR_HEADING(pPlayer,&heading);
	if(IS_CHAR_IN_ANY_CAR(pPlayer)){
		GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
		GET_CAR_SPEED(pveh,&speed);
		GET_DRIVER_OF_CAR(pveh,&driver);
		WARP_CHAR_FROM_CAR_TO_COORD(pPlayer,x,y,z);
		if(!DOES_CHAR_EXIST(driver) || pPlayer == driver || !IS_NETWORK_SESSION()){
			DELETE_CAR(&pveh);
			MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
		}
	}
	else GET_CHAR_SPEED(pPlayer, &speed);
	CREATE_CAR(model,x,y,z,&pveh,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
    CHANGE_CAR_COLOUR(pveh, 0, 0);
	SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
    SET_VEHICLE_DIRT_LEVEL(pveh, 0);
    WASH_VEHICLE_TEXTURES(pveh, 255);
	SET_CAR_ENGINE_ON(pveh,true,true);
	WARP_CHAR_INTO_CAR(pPlayer,pveh);
	SET_CAR_PROOFS(pveh, true, true, true, true, true);
	SET_CAR_HEADING(pveh,heading);
	SET_CAR_FORWARD_SPEED(pveh,speed);
	return;
}

void helibomb(void){
	REQUEST_MODEL(0x7E339194);
	while (!HAS_MODEL_LOADED(0x7E339194)) WAIT(0); 	
	GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(GetPlayerPed(), 0.5, -2.1, -2.1, &x, &y, &z);
	GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
	CREATE_OBJECT(0x7E339194, x, y, z, &ObjectProjectile, 1);
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	SET_OBJECT_HEALTH(ObjectProjectile, 100.0);
	SET_OBJECT_ROTATION(ObjectProjectile, 90.0, 0.0, 0.0);
	GET_GROUND_Z_FOR_3D_COORD(x, y, z, &mz);
	speed = z - mz;
		//repeat
	for (i = 1; i <= speed; i++) {
		WAIT(27);
		SLIDE_OBJECT(ObjectProjectile, x, y, mz, 0.0, 0.0, 1.3, 0);
	}
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	PLAY_SOUND_FROM_VEHICLE(-1, "F5_TRUCK_ARSON_BOMB_BLEEP", pveh);
	
		// repeat end!
	WAIT(100);

		//---------------- In Heli
	//BombType(X, Y, Z, width, highness, spacing)
	//BombType(x, y, zground, 7, 2, 2);
	create_big_explosion(x,y,mz);
	create_big_explosion(x,y,mz + 2);
	create_big_explosion(x + 7,y,mz);
	create_big_explosion(x + 7,y,mz);
	create_big_explosion(x - 7,y,mz);
	create_big_explosion(x,y + 7,mz);
	create_big_explosion(x,y - 7,mz);
	
	DELETE_OBJECT(&ObjectProjectile);
	MARK_MODEL_AS_NO_LONGER_NEEDED(0x7E339194);
}

void spawn_car_for_char(Ped pPed, uint model){
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	//spawn car offset 3ft infront of player
	GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 0, 3, 1, &x, &y, &z);
	CREATE_CAR(model,x,y,z,&pveh,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
    CHANGE_CAR_COLOUR(pveh, 0, 0);
	SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
    SET_VEHICLE_DIRT_LEVEL(pveh, 0);
    WASH_VEHICLE_TEXTURES(pveh, 255);
	SET_CAR_CAN_BE_DAMAGED(pveh,false);
	SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
	SET_CAN_BURST_CAR_TYRES(pveh,false);
	SET_HELI_BLADES_FULL_SPEED(pveh);
	SET_CAR_PROOFS(pveh, true, true, true, true, true);
	SET_CAR_ENGINE_ON(pveh,true,true);
	return;
}

void spawn_car_in_line(Ped pPed, uint model){
	speed = 0.0;
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)) WAIT(0);
	GET_CHAR_HEADING(pPlayer,&heading);
	if(heading > 270) heading -= 90.0;
	else heading += 90.0;
	for(i = 1;i <= 5;i++){
		speed += 3.0;
		GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 0, speed, 0, &x, &y, &z);
		if(IS_THIS_MODEL_A_HELI(model)) speed += 15.0;
		CREATE_CAR(model,x,y,z,&pveh,true);
		CHANGE_CAR_COLOUR(pveh, 0, 0);
		SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
		SET_VEHICLE_DIRT_LEVEL(pveh, 0);
		WASH_VEHICLE_TEXTURES(pveh, 255);
		SET_CAR_CAN_BE_DAMAGED(pveh,false);
		SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
		SET_CAN_BURST_CAR_TYRES(pveh,false);
		SET_CAR_PROOFS(pveh, true, true, true, true, true);
		SET_CAR_ENGINE_ON(pveh,true,true);
	}
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
	return;
}

void road_block(Ped pPed){
	GET_CHAR_HEADING(pPed, &heading);
	GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 0, 6, 0, &x, &y, &z);
	GET_GROUND_Z_FOR_3D_COORD(x, y, z, &z);
	z += 0.1;
	CREATE_OBJECT(MODEL_CJ_BARRIER_10, x - 1.5, y, z, &otmp, 1);
	WAIT(1);
	GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
	FREEZE_OBJECT_POSITION(otmp,true);
	SET_OBJECT_VISIBLE(otmp, true);
	SET_OBJECT_INVINCIBLE(otmp, true);
	SET_OBJECT_HEADING(otmp, heading);
	CREATE_OBJECT(MODEL_CJ_BARRIER_10, x + 1.5, y, z, &admin_obj, 1);
	WAIT(1);
	GET_NETWORK_ID_FROM_OBJECT(admin_obj, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
	FREEZE_OBJECT_POSITION(admin_obj,true);
	SET_OBJECT_VISIBLE(admin_obj, true);
	SET_OBJECT_INVINCIBLE(admin_obj, true);
	SET_OBJECT_HEADING(admin_obj, heading);
	WAIT(1000);
	GET_NETWORK_ID_FROM_OBJECT(otmp,&nvid);
	REQUEST_CONTROL_OF_NETWORK_ID(nvid);
	tick = 0;
	if(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
		while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
			tick++;
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			if(tick >= 100) break;
			WAIT(0);
		}
	}
	if(DOES_OBJECT_EXIST(otmp)) DELETE_OBJECT(&otmp);
	GET_NETWORK_ID_FROM_OBJECT(admin_obj,&nvid);
	REQUEST_CONTROL_OF_NETWORK_ID(nvid);
	tick = 0;
	if(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
		while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
			tick++;
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			if(tick >= 100) break;
			WAIT(0);
		}
	}
	if(DOES_OBJECT_EXIST(admin_obj)) DELETE_OBJECT(&admin_obj);
	print("Blocked Players Car.");
	return;
}

void xmc_teleportinfront(void){
	GET_CHAR_HEADING(GetPlayerPed(), &speed);
	GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);
	teleport_char(pPlayer, x+(10*SIN((-1*speed))), y+(10*COS((-1*speed))), z);
}

void xmc_airstrike(void){
	if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
		GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&spawn);
		GET_GROUND_Z_FOR_3D_COORD(spawn.x,spawn.y,spawn.z,&z);
		create_big_explosion(spawn.x,spawn.y,z+5.0);
		print("Launching Airstrike!");
	}
	else print("You need to set a waypoint!");
}

void attachobjecttocar(Vehicle veh,uint model,float offsetX,float offsetY,float offsetZ,float yaw,float pitch,float roll){
	int obj;
	REQUEST_MODEL(model);
	while(!HAS_MODEL_LOADED(model)){ WAIT(0); }
	CREATE_OBJECT(model,0,0,0,&obj,true);
	MARK_MODEL_AS_NO_LONGER_NEEDED(model);
	ATTACH_OBJECT_TO_CAR(obj,veh,0,offsetX,offsetY,offsetZ,yaw,pitch,roll);
	FREEZE_OBJECT_POSITION(obj,true);
	SET_OBJECT_VISIBLE(obj,true);
	SET_OBJECT_INVINCIBLE(obj,true);
	SET_OBJECT_LIGHTS(obj,true);
}

void menu_functions(void){
	#ifdef PREVIEW
	print("Preview Version");
	return;
	#else
	if(menu_level == 1){
		if(last_selected[0] == 1){
			if(item_select == 3){
				SET_CHAR_HEALTH(pPlayer,500);
				ADD_ARMOUR_TO_CHAR(pPlayer,100);
				return;
			}
			if(item_select == 4){
				do_toggle(godmode);
				return;
			}
			if(item_select == 5){
				do_toggle(neverwanted);
				if(neverwanted){
					SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), true);
					ALLOW_EMERGENCY_SERVICES(false);
					SET_MAX_WANTED_LEVEL(0);
					SET_CHAR_WANTED_BY_POLICE(pPlayer, false);
				}
				else
					SET_MAX_WANTED_LEVEL(6);
				return;
			}
			if(item_select == 6){
				do_toggle(pprotection);
				FREEZE_CHAR_POSITION(pPlayer,false);
				return;
			}
			if(item_select == 7){
				if(!superrun){
				print("Press ~PAD_LB~ + ~PAD_A~ to use");
				}
				do_toggle(superrun);
				return;
			}
			if(item_select == 8){
				if(!superjump) print("Press ~PAD_LB~ + ~PAD_X~ to use");
				do_toggle(superjump);
				return;
			}
			if(item_select == 9){
				if(!chronicle) print("Press ~PAD_LB~ + ~PAD_B~ to Blast in front of you");
				WAIT(800);
				do_toggle(chronicle);
				return;
			}
			if(item_select == 10){
				if(IS_CHAR_VISIBLE(pPlayer)) SET_CHAR_VISIBLE(pPlayer, false);
				else SET_CHAR_VISIBLE(pPlayer, true);
				reset_menu();
				return;
			}
			if(item_select == 11){
				if(IS_CHAR_ON_FIRE(pPlayer)) EXTINGUISH_CHAR_FIRE(pPlayer);
				else START_CHAR_FIRE(pPlayer);
				reset_menu();
				return;
			}
			if(item_select == 13){
				if(!inferno){
					if(godmode){
						print("Godmode must be disabled");
						return;
					}
					START_CHAR_FIRE(pPlayer);
					print("Press ~PAD_LB~ + ~PAD_B~ to shoot a fire field.");
					WAIT(800);
					godmode = true;
					reset_menu();
				}
				do_toggle(inferno);
				return;
			}
			if(item_select == 14){
				if(!vehwater) print("Walk or Drive on water");
				do_toggle(vehwater);
				return;
			}
			if(item_select == 15){
				if(!rocket) print("RocketMan Press ~PAD_RB~ and ~PAD_DPAD_ALL~ to shoot a rocket.");
				do_toggle(rocket);
				return;
			}
		}
		if(last_selected[0] == 2){
			if(item_select == 2){
				do_toggle(vhelper);
				return;
			}
			if(item_select == 3){
				if(DOES_CHAR_EXIST(pPlayer)){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						tick = 0;
						while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
							tick++;
							REQUEST_CONTROL_OF_NETWORK_ID(nvid);
							if(tick >= 150){
								print("~r~Error");
								return;
							}
							WAIT(0);
						}
						APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
					}
					else print("Not in vehicle");
				}
				return;
			}
			if(item_select == 4){
				do_toggle(carsonground);
				return;
			}
			if(item_select == 5){
				do_toggle(nfs);
				carsonground = nfs;
				return;
			}
			if(item_select == 6){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					do_toggle(freezecar);
					if(freezecar){
						FREEZE_CAR_POSITION(pveh,true);
						print("Car is now immobile");
					}
					else{
						FREEZE_CAR_POSITION(pveh,false);
						print("Car is now mobile");
					}
					return;
				}
				return;
			}
			if(item_select == 7){
				do_toggle(collision);
				return;
			}
			if(item_select == 8){
				if(!bikefly){
				print("Use ~PAD_RT~ to speed up and ~PAD_LT~ to brake.");
				}
				do_toggle(bikefly);
				return;
			}
			if(item_select == 9){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					// float x,y,z;
					GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
					teleport_char(pPlayer,0.0,4000.0,0.0);
					WAIT(0);
					teleport_char(pPlayer,x,y,z);
				}
				return;
			}
			if(item_select == 10){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					// // Vehicle pveh;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_DRIVER_OF_CAR(pveh,&driver);
					if((driver == pPlayer) || (!DOES_CHAR_EXIST(driver))){
						GET_NETWORK_ID_FROM_VEHICLE(pveh, &nvid);
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						tick = 0;
						while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
							tick++;
							REQUEST_CONTROL_OF_NETWORK_ID(nvid);
							if(tick >= 100){
								break;
							}
							WAIT(0);
						}
						DELETE_CAR(&pveh);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
					else print("You must be the driver of this vehicle");
				}
				return;
			}
			if(item_select == 11){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					// Vehicle pveh;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_CAR_COORDINATES(pveh, &x, &y, &z);
					GET_CAR_HEADING(pveh, &heading);
					if(heading > 180.0) heading -= 180.0;
					else heading += 180.0;
					SET_VEHICLE_QUATERNION(pveh, 0, 0, 0, 0);
					SET_CAR_COORDINATES(pveh, x, y, z);
					SET_CAR_HEADING(pveh, heading);
				//	SET_CAR_ON_GROUND_PROPERLY(pveh);
				}
				return;
			}
			if(item_select == 12){
				//// float x, y, z;
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
					z += 1;
					WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
					APPLY_FORCE_TO_PED(pPlayer, 1 ,0.0f ,0.0f ,900.0f ,0.0f ,0.0f ,0.0f ,1 ,1 ,1 ,1);
					print("Ejected");
					return;
				}
			}
			if(item_select == 13){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					GET_CAR_MODEL(pveh, &model);
					GET_CAR_COLOURS(pveh, &color1, &color2);
					GET_EXTRA_CAR_COLOURS(pveh, &color3, &color4);
					REQUEST_MODEL(model);
					while(!HAS_MODEL_LOADED(model)) WAIT(0);
					GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
					GET_CHAR_HEADING(pPlayer,&heading);
					GET_CAR_SPEED(pveh,&speed);
					GET_DRIVER_OF_CAR(pveh,&driver);
					WARP_CHAR_FROM_CAR_TO_COORD(pPlayer,x,y,z);
					if(!DOES_CHAR_EXIST(driver) || pPlayer == driver || !IS_NETWORK_SESSION()){
						DELETE_CAR(&pveh);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
					CREATE_CAR(model,x,y,z,&pveh,true);
					MARK_MODEL_AS_NO_LONGER_NEEDED(model);
					CHANGE_CAR_COLOUR(pveh, color1, color2);
					SET_EXTRA_CAR_COLOURS(pveh, color3, color4);
					SET_VEHICLE_DIRT_LEVEL(pveh, 0);
					WASH_VEHICLE_TEXTURES(pveh, 255);
					SET_CAR_ENGINE_ON(pveh,true,true);
					WARP_CHAR_INTO_CAR(pPlayer,pveh);
					SET_CAR_PROOFS(pveh, true, true, true, true, true);
					SET_CAR_HEADING(pveh,heading);
					SET_CAR_FORWARD_SPEED(pveh,speed);
					return;
				}
				return;
			}
			if(item_select == 14){
				if(!helistrike){
					print("Press ~PAD_LSTICK_NONE~ when in a Heli to drop a bomb.");
				}
				do_toggle(helistrike);
				return;
			}
			if(item_select == 15){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					TASK_SHUFFLE_TO_NEXT_CAR_SEAT(pPlayer, pveh);
				}
				return;
			}
			if(item_select == 16){
				if(IS_CHAR_IN_ANY_CAR(pPlayer)){
					do_toggle(vehinvis);
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					if(vehinvis) SET_CAR_VISIBLE(pveh, false);
					else SET_CAR_VISIBLE(pveh, true);
				}
				return;
			}
			if(item_select == 17){
				if(DOES_VEHICLE_EXIST(superlock_veh)){
					GET_NETWORK_ID_FROM_VEHICLE(superlock_veh,&nvid);
					if(HAS_CONTROL_OF_NETWORK_ID(nvid)){
						SET_NETWORK_ID_CAN_MIGRATE(nvid,true);
						LOCK_CAR_DOORS(superlock_veh,1);
						WARP_CHAR_INTO_CAR(pPlayer,superlock_veh);
						superlock_veh = INVALID_HANDLE;
						print("Super Lock ~r~OFF");
						return;
					}
				}
				else{
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
						if(HAS_CONTROL_OF_NETWORK_ID(nvid)){
							superlock_veh = pveh;
							SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
							LOCK_CAR_DOORS(superlock_veh,4);
							GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
							z += 1;
							WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
							print("Super Lock ~g~ON");
							return;
						}
					}
					else print("You must be in a car to lock it");
				}
				return;
			}
			if(item_select == 18){
				do_toggle(autoflip);
				return;
			}
			return;
		}
		if(last_selected[0] == 3){
			if(item_select == 2){
				do_toggle(fastreload);
				if(fastreload){
					SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), true);
				}
				else{
					SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), false);
				}
				return;
			}
			else if(item_select == 3){
				if(!autoaim){
					print("Forced Auto Aim");
				}
				do_toggle(autoaim);
				if(autoaim){
					DISABLE_PLAYER_LOCKON(GetPlayerIndex(), false);
				//	ALLOW_LOCKON_TO_FRIENDLY_PLAYERS(GetPlayerIndex(), true);
				}
				else{
					DISABLE_PLAYER_LOCKON(GetPlayerIndex(), true);
				//	ALLOW_LOCKON_TO_FRIENDLY_PLAYERS(GetPlayerIndex(), false);
				}
				return;
			}
			else if(item_select == 5){
				do_toggle(rapidfire);
				return;
			}
			else if(item_select == 7){
				if(!powgun) print("~g~Shoot the Glock at an online player to explode them.");
				if(!powgun){
					GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_PISTOL, AMMO_MAX, 0);
					SET_CURRENT_CHAR_WEAPON(pPlayer, WEAPON_PISTOL, true);
				}
				do_toggle(powgun);
				return;
			}
			else if(item_select == 8){
				if(!pedgun) print("~g~Shoot the Glock to launch a ped.");
				do_toggle(pedgun);
				return;
			}
			else if(item_select == 9){
				if(!rocketgun) print("~g~Shoot the Deagle to fire rockets.");
				if(!rocketgun){
					GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_DEAGLE, AMMO_MAX, 0);
					SET_CURRENT_CHAR_WEAPON(pPlayer, WEAPON_DEAGLE, true);
				}
				else{
					if(DOES_CHAR_EXIST(rocketped[2])) DELETE_CHAR(&rocketped[2]);
				}
				do_toggle(rocketgun);
				return;
			}
			else if(item_select == 10){
				do_toggle(wepvisible);
				return;
			}
			else if(item_select == 11){
				if(GET_CURRENT_EPISODE() == 2){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_EPISODIC_12, AMMO_MAX, 0);
						SET_CURRENT_CHAR_WEAPON(pPlayer, WEAPON_EPISODIC_12, true);
					}
					else print ("You must be in a car");
				}
				else print("You must be on TBOGT");
				return;
			}
			else if(item_select == 12){
				if(!dragongun) print("~g~Shoot the Berretta at online players.");
				if(!dragongun){
					GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_BARETTA, AMMO_MAX, 0);
					SET_CURRENT_CHAR_WEAPON(pPlayer, WEAPON_BARETTA, true);
				}
				do_toggle(dragongun);
				return;
			}
			
		}
		if(last_selected[0] == 4){
			if(item_select == 1){
				if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
					GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&spawn);
					GET_GROUND_Z_FOR_3D_COORD(spawn.x,spawn.y,spawn.z,&z);
					WAIT(10);
					teleport_char(pPlayer,spawn.x,spawn.y,z + 5);
				}
				else print("You need to set a waypoint!");
				
				return;
			}
			if(item_select == 2){
				teleport_char(pPlayer,2175.3516,761.2235,30.0);
				return;
			}
			if(item_select == 3){
				teleport_char(pPlayer,1100.5,-747.0,7.39);
				return;
			}
			if(item_select == 4){
				teleport_char(pPlayer,-178.2,582.6,126.85);
				return;
			}
			if(item_select == 5){
				teleport_char(pPlayer,-236.0,795.9,6.20);
				return;
			}
			if(item_select == 6){
				teleport_char(pPlayer,-415.17,1463.54,39.0);
				return;
			}
			if(item_select == 7){
				teleport_char(pPlayer,-279.77,-99.66,386.791);
				return;
			}
			if(item_select == 8){
				teleport_char(pPlayer,-1079.8,-469.7,2.62);
				return;
			}
			if(item_select == 9){
				teleport_char(pPlayer,1375.8765,197.4544,48.0);
				return;
			}
			if(item_select == 10){
				teleport_char(pPlayer,-532.681,1273.3307,105.65);
				return;
			}
			if(item_select == 11){
				teleport_char(pPlayer,55.3537,1125.3387,2.4527);
				return;
			}
			if(item_select == 12){
				teleport_char(pPlayer,104.13,856.53,45.58);
				return;
			}
			if(item_select == 13){
				teleport_char(pPlayer,-473.0176,1746.8829,6.26);
				return;
			}
			if(item_select == 14){
				teleport_char(pPlayer,237.5457,-805.6555,13.7);
				return;
			}
			if(item_select == 15){
				teleport_char(pPlayer,-3.4734,270.6067,-2.9470);
				return;
			}
			if(item_select == 16){
				teleport_char(pPlayer,-1539.8414,163.2967,9.9000);
				return;
			}
			if(item_select == 17){
				teleport_char(pPlayer,-387.44270000, 1492.48800000, 9.71030100);
				return;
			}
			if(item_select == 18){
				xmc_teleportinfront();
				return;
			}
			if(item_select == 19){
				GET_CHAR_COORDINATES(pPlayer,&x, &y, &z);
				pveh = GET_CLOSEST_CAR(x,y,z, 50, false, 70);
				if(!DOES_VEHICLE_EXIST(pveh))
				pveh = GET_CLOSEST_CAR(x,y,z, 50, false, 71);
				if(!DOES_VEHICLE_EXIST(pveh))
				pveh = GET_CLOSEST_CAR(x,y,z, 50, false, 69);
				if(!DOES_VEHICLE_EXIST(pveh)){	
					print("~r~No Car found.");
					return;
				}
				GET_DRIVER_OF_CAR(pveh,&driver);
				if(!DOES_CHAR_EXIST(driver)){
					WARP_CHAR_INTO_CAR(pPlayer,pveh);
					print("Teleported into Nearest Car as Driver");
				}
				else{
					for(i = 0;i <= 2;i++){
						if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)){
							WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,pveh,i);
							print("Teleported into Nearest Car as Passenger");
						}
					}
				}
				return;
			}
		}
		if(last_selected[0] == 5){
			if(item_select == 4){
				do_toggle(drive_free);
				if(drive_free){
					SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
					SWITCH_AMBIENT_PLANES(false);
				}
				else{
					SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
					SWITCH_AMBIENT_PLANES(true);
				}
				return;
			}
			if(item_select == 5){
				SHUTDOWN_AND_LAUNCH_NETWORK_GAME(2);
				return;
			}
			if(item_select == 6){
				SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME();
				return;
			}
			if(item_select == 7){
				print_long(GET_PLAYER_NAME(GET_HOST_ID()));
			}
			if(item_select == 8){	
				do_toggle(modderprotect);
				return;
			}
			if(item_select == 9){
				for(i = 0; i < 66; i++){
					if(!HAS_ACHIEVEMENT_BEEN_PASSED(i)) AWARD_ACHIEVEMENT(i);
				}
				print("Unlocked All available Achievements");
				return;
			}
			if(item_select == 10){
				do_toggle(gravity);
				if(gravity){
					SET_GRAVITY_OFF(true);
					print("Zero Gravity");
				}
				else{
					SET_GRAVITY_OFF(false);
					print("Normal Gravity");
				}
				return;
			}
			if(item_select == 11){
				GET_CHAR_COORDINATES(pPlayer,&x, &y, &z);
				CLEAR_AREA_OF_CARS(x,y,z,500);
				for(i = 0; i <= 30; i++){
					pveh = GET_CLOSEST_CAR(x,y,z, 500, false, 70);
					if(!DOES_VEHICLE_EXIST(pveh)) pveh = GET_CLOSEST_CAR(x,y,z, 500, false, 71);
					if(!DOES_VEHICLE_EXIST(pveh)) pveh = GET_CLOSEST_CAR(x,y,z, 500, false, 69);
					if(!DOES_VEHICLE_EXIST(pveh)) return;
						
					GET_NETWORK_ID_FROM_VEHICLE(pveh, &nvid);
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					tick = 0;
					while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
						tick++;
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						if(tick >= 200){
							print("Deleted all available cars");
							return;
						}
						WAIT(0);
					}
					DELETE_CAR(&pveh);
					MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
				}
				return;
			}
			if(item_select == 12){
				GET_CHAR_COORDINATES(pPlayer,&x, &y, &z);
				CLEAR_AREA_OF_CHARS(x,y,z,500);
				for(i = 0; i <= 30; i++){
					GET_CLOSEST_CHAR(x,y,z, 500, false, 70, &CharProjectile);
					if(!DOES_CHAR_EXIST(CharProjectile)) GET_CLOSEST_CHAR(x,y,z, 500, false, 71, &CharProjectile);
					if(!DOES_CHAR_EXIST(CharProjectile)) GET_CLOSEST_CHAR(x,y,z, 500, false, 69, &CharProjectile);
					if(!DOES_CHAR_EXIST(CharProjectile)) return;
					
					GET_NETWORK_ID_FROM_PED(CharProjectile, &nvid);
					REQUEST_CONTROL_OF_NETWORK_ID(nvid);
					tick = 0;
					while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
						tick++;
						REQUEST_CONTROL_OF_NETWORK_ID(nvid);
						if(tick >= 200){
							print("Deleted all available peds");
							return;
						}
						WAIT(0);
					}
					DELETE_CHAR(&CharProjectile);
				}
				return;
			}
			if(item_select == 14){
				do_toggle(slowmotion);
				if(!slowmotion) SET_TIME_SCALE(1.0);
				return;
			}
			if(item_select == 16){
				GET_CHAR_HEADING(pPlayer, &heading);
				GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, 1, 0, &x, &y, &z);
				GET_GROUND_Z_FOR_3D_COORD(x, y, z, &z);
				z -= 0.1;
				CREATE_OBJECT(MODEL_CJ_BARRIER_10B, x, y, z, &otmp, 1);
				WAIT(1);
				FREEZE_OBJECT_POSITION(otmp,true);
				SET_OBJECT_VISIBLE(otmp, true);
				SET_OBJECT_INVINCIBLE(otmp, true);
				SET_OBJECT_HEADING(otmp, heading);
				dist = 0;
				for(i = 0; i <= 3; i++){
					dist += 2.0;
					GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(otmp, dist, 0, 0, &x, &y, &z);
					CREATE_OBJECT(MODEL_CJ_BARRIER_10, x, y, z, &ObjectProjectile, 1);
					WAIT(1);
					FREEZE_OBJECT_POSITION(ObjectProjectile,true);
					SET_OBJECT_VISIBLE(ObjectProjectile, true);
					SET_OBJECT_INVINCIBLE(ObjectProjectile, true);
					SET_OBJECT_HEADING(ObjectProjectile, heading);
				}
				dist = 0;
				WAIT(10);
				for(i = 0; i <= 3; i++){
					dist -= 2.0;
					GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(otmp, dist, 0, 0, &x, &y, &z);
					CREATE_OBJECT(MODEL_CJ_BARRIER_10, x, y, z, &ObjectProjectile, 1);
					WAIT(1);
					FREEZE_OBJECT_POSITION(ObjectProjectile,true);
					SET_OBJECT_VISIBLE(ObjectProjectile, true);
					SET_OBJECT_INVINCIBLE(ObjectProjectile, true);
					SET_OBJECT_HEADING(ObjectProjectile, heading);
				}
				print("Spawned Concrete Barrier");
				return;
			}
			if(item_select == 18){
				GET_CHAR_COORDINATES(GetPlayerPed(), &x, &y, &z);
				CLEAR_AREA_OF_OBJECTS(x,y,z,500);
				for(i = 0;i<15000;i++){
					GET_OBJECT_FROM_NETWORK_ID(i, &otmp);
					if(DOES_OBJECT_EXIST(otmp)){
						REQUEST_CONTROL_OF_NETWORK_ID(i);
						tick = 0;
						while(!HAS_CONTROL_OF_NETWORK_ID(i)){
							tick++;
							REQUEST_CONTROL_OF_NETWORK_ID(i);
							if(tick >= 200){
								print("Deleted all available Objects");
								return;
							}
							WAIT(0);
						}
						DELETE_OBJECT(&otmp);
					}
				}
				print("Deleted all available Objects");
				return;
			}
		}
		if(last_selected[0] == 6){
			if(item_select == 1){
				if(DOES_SCRIPT_EXIST("xmc1")){
					do_toggle(xmc1);
					if(xmc1){
						REQUEST_SCRIPT("xmc1");
						while(!HAS_SCRIPT_LOADED("xmc1")){
							REQUEST_SCRIPT("xmc1");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc1", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc1");
						print_long("~g~Launched xmc1.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc1");
						print_long("~r~Killed xmc1.sco");
					}
				}
				else print_long("~r~xmc1.sco Doesn't exist");
				return;
			}
			if(item_select == 2){
				if(DOES_SCRIPT_EXIST("xmc2")){
					do_toggle(xmc2);
					if(xmc2){
						REQUEST_SCRIPT("xmc2");
						while(!HAS_SCRIPT_LOADED("xmc2")){
							REQUEST_SCRIPT("xmc2");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc2", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc2");
						print_long("~g~Launched xmc2.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc2");
						print_long("~r~Killed xmc2.sco");
					}
				}
				else print_long("~r~xmc2.sco Doesn't exist");
				return;
			}
			if(item_select == 3){
				if(DOES_SCRIPT_EXIST("xmc3")){
					do_toggle(xmc3);
					if(xmc3){
						REQUEST_SCRIPT("xmc3");
						while(!HAS_SCRIPT_LOADED("xmc3")){
							REQUEST_SCRIPT("xmc3");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc3", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc3");
						print_long("~g~Launched xmc3.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc3");
						print_long("~r~Killed xmc3.sco");
					}
				}
				else print_long("~r~xmc3.sco Doesn't exist");
				return;
			}
			if(item_select == 4){
				if(DOES_SCRIPT_EXIST("xmc4")){
					do_toggle(xmc4);
					if(xmc4){
						REQUEST_SCRIPT("xmc4");
						while(!HAS_SCRIPT_LOADED("xmc4")){
							REQUEST_SCRIPT("xmc4");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc4", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc4");
						print_long("~g~Launched xmc4.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc4");
						print_long("~r~Killed xmc4.sco");
					}
				}
				else print_long("~r~xmc4.sco Doesn't exist");
				return;
			}
			if(item_select == 5){
				if(DOES_SCRIPT_EXIST("xmc5")){
					do_toggle(xmc5);
					if(xmc5){
						REQUEST_SCRIPT("xmc5");
						while(!HAS_SCRIPT_LOADED("xmc5")){
							REQUEST_SCRIPT("xmc5");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc5", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc5");
						print_long("~g~Launched xmc5.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc5");
						print_long("~r~Killed xmc5.sco");
					}
				}
				else print_long("~r~xmc5.sco Doesn't exist");
				return;
			}
			if(item_select == 6){
				if(DOES_SCRIPT_EXIST("xmc6")){
					do_toggle(xmc6);
					if(xmc6){
						REQUEST_SCRIPT("xmc6");
						while(!HAS_SCRIPT_LOADED("xmc6")){
							REQUEST_SCRIPT("xmc6");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc6", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc6");
						print_long("~g~Launched xmc6.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc6");
						print_long("~r~Killed xmc6.sco");
					}
				}
				else print_long("~r~xmc6.sco Doesn't exist");
				return;
			}
			if(item_select == 7){
				if(DOES_SCRIPT_EXIST("xmc7")){
					do_toggle(xmc7);
					if(xmc7){
						REQUEST_SCRIPT("xmc7");
						while(!HAS_SCRIPT_LOADED("xmc7")){
							REQUEST_SCRIPT("xmc7");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc7", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc7");
						print_long("~g~Launched xmc7.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc7");
						print_long("~r~Killed xmc7.sco");
					}
				}
				else print_long("~r~xmc7.sco Doesn't exist");
				return;
			}
			if(item_select == 8){
				if(DOES_SCRIPT_EXIST("xmc8")){
					do_toggle(xmc8);
					if(xmc8){
						REQUEST_SCRIPT("xmc8");
						while(!HAS_SCRIPT_LOADED("xmc8")){
							REQUEST_SCRIPT("xmc8");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc8", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc8");
						print_long("~g~Launched xmc8.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc8");
						print_long("~r~Killed xmc8.sco");
					}
				}
				else print_long("~r~xmc8.sco Doesn't exist");
				return;
			}
			if(item_select == 9){
				if(DOES_SCRIPT_EXIST("xmc9")){
					do_toggle(xmc9);
					if(xmc9){
						REQUEST_SCRIPT("xmc9");
						while(!HAS_SCRIPT_LOADED("xmc9")){
							REQUEST_SCRIPT("xmc9");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc9", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc9");
						print_long("~g~Launched xmc9.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc9");
						print_long("~r~Killed xmc9.sco");
					}
				}
				else print_long("~r~xmc9.sco Doesn't exist");
				return;
			}
			if(item_select == 10){
				if(DOES_SCRIPT_EXIST("xmc10")){
					do_toggle(xmc10);
					if(xmc10){
						REQUEST_SCRIPT("xmc10");
						while(!HAS_SCRIPT_LOADED("xmc10")){
							REQUEST_SCRIPT("xmc10");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc10", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc10");
						print_long("~g~Launched xmc10.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc10");
						print_long("~r~Killed xmc10.sco");
					}
				}
				else print_long("~r~xmc10.sco Doesn't exist");
				return;
			}
			if(item_select == 11){
				if(DOES_SCRIPT_EXIST("xmc11")){
					do_toggle(xmc11);
					if(xmc11){
						REQUEST_SCRIPT("xmc11");
						while(!HAS_SCRIPT_LOADED("xmc11")){
							REQUEST_SCRIPT("xmc11");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc11", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc11");
						print_long("~g~Launched xmc11.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc11");
						print_long("~r~Killed xmc11.sco");
					}
				}
				else print_long("~r~xmc11.sco Doesn't exist");
				return;
			}
			if(item_select == 12){
				if(DOES_SCRIPT_EXIST("xmc12")){
					do_toggle(xmc12);
					if(xmc12){
						REQUEST_SCRIPT("xmc12");
						while(!HAS_SCRIPT_LOADED("xmc12")){
							REQUEST_SCRIPT("xmc12");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc12", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc12");
						print_long("~g~Launched xmc12.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc12");
						print_long("~r~Killed xmc12.sco");
					}
				}
				else print_long("~r~xmc12.sco Doesn't exist");
				return;
			}
			if(item_select == 13){
				if(DOES_SCRIPT_EXIST("xmc13")){
					do_toggle(xmc13);
					if(xmc13){
						REQUEST_SCRIPT("xmc13");
						while(!HAS_SCRIPT_LOADED("xmc13")){
							REQUEST_SCRIPT("xmc13");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc13", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc13");
						print_long("~g~Launched xmc13.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc13");
						print_long("~r~Killed xmc13.sco");
					}
				}
				else print_long("~r~xmc13.sco Doesn't exist");
				return;
			}
			if(item_select == 14){
				if(DOES_SCRIPT_EXIST("xmc14")){
					do_toggle(xmc14);
					if(xmc14){
						REQUEST_SCRIPT("xmc14");
						while(!HAS_SCRIPT_LOADED("xmc14")){
							REQUEST_SCRIPT("xmc14");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc14", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc14");
						print_long("~g~Launched xmc14.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc14");
						print_long("~r~Killed xmc14.sco");
					}
				}
				else print_long("~r~xmc14.sco Doesn't exist");
				return;
			}
			if(item_select == 15){
				if(DOES_SCRIPT_EXIST("xmc15")){
					do_toggle(xmc15);
					if(xmc15){
						REQUEST_SCRIPT("xmc15");
						while(!HAS_SCRIPT_LOADED("xmc15")){
							REQUEST_SCRIPT("xmc15");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc15", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc15");
						print_long("~g~Launched xmc15.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc15");
						print_long("~r~Killed xmc15.sco");
					}
				}
				else print_long("~r~xmc15.sco Doesn't exist");
				return;
			}
			if(item_select == 16){
				if(DOES_SCRIPT_EXIST("xmc16")){
					do_toggle(xmc16);
					if(xmc16){
						REQUEST_SCRIPT("xmc16");
						while(!HAS_SCRIPT_LOADED("xmc16")){
							REQUEST_SCRIPT("xmc16");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc16", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc16");
						print_long("~g~Launched xmc16.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc16");
						print_long("~r~Killed xmc16.sco");
					}
				}
				else print_long("~r~xmc16.sco Doesn't exist");
				return;
			}
			if(item_select == 17){
				if(DOES_SCRIPT_EXIST("xmc17")){
					do_toggle(xmc17);
					if(xmc17){
						REQUEST_SCRIPT("xmc17");
						while(!HAS_SCRIPT_LOADED("xmc17")){
							REQUEST_SCRIPT("xmc17");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc17", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc17");
						print_long("~g~Launched xmc17.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc17");
						print_long("~r~Killed xmc17.sco");
					}
				}
				else print_long("~r~xmc17.sco Doesn't exist");
				return;
			}
			if(item_select == 18){
				if(DOES_SCRIPT_EXIST("xmc18")){
					do_toggle(xmc18);
					if(xmc18){
						REQUEST_SCRIPT("xmc18");
						while(!HAS_SCRIPT_LOADED("xmc18")){
							REQUEST_SCRIPT("xmc18");
							WAIT(0);
						}
						START_NEW_SCRIPT("xmc18", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("xmc18");
						print_long("~g~Launched xmc18.sco");
					}
					else{
						TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("xmc18");
						print_long("~r~Killed xmc18.sco");
					}
				}
				else print_long("~r~xmc18.sco Doesn't exist");
				return;
			}
		}
	}
	if(menu_level == 2){
		if(last_selected[0] == 1){
			if(last_selected[1] == 2){
				if(item_select == 3){
					DETACH_PED(pPlayer);
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
						if(IS_CAR_ATTACHED(pveh)) DETACH_CAR(pveh); 
						else{
							GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
							z += 1;
							WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
						}
					}
					CLEAR_CHAR_TASKS_IMMEDIATELY(pPlayer);
					SWITCH_PED_TO_RAGDOLL(pPlayer,20,30,false,false,false,false);
					SWITCH_PED_TO_ANIMATED(pPlayer,true);
					GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
					WAIT(30);
					SWITCH_PED_TO_ANIMATED(pPlayer,false);
					GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
					return;
				}
				if(item_select == 4){
					if(!ragdoll) print("Press ~PAD_LB~ + ~PAD_B~ to ragdoll");
					do_toggle(ragdoll);
					return;
				}
				if(item_select == 5){
					if(GET_PLAYER_ID() != GET_HOST_ID()){
						print("~r~You Are Not Host");
						return;
					}
					if(NETWORK_IS_GAME_RANKED()){
						i = (GET_CHAR_MONEY(pPlayer) + 50000);
						SET_CHAR_MONEY(pPlayer, i);
						print("Gave Player Money");
					}
					else print("The Game You Are In is Not Ranked");
				}
				if(item_select == 6){
				//	GIVE_PLAYER_HELMET(GET_PLAYER_ID(),true);
					GIVE_PED_HELMET(pPlayer);
					print("Gave player some headgear");
					return;
				}
				if(item_select == 7){
				//	GIVE_PLAYER_HELMET(GET_PLAYER_ID(),true);
					SET_CHAR_RANDOM_COMPONENT_VARIATION(pPlayer);
					print("Changed player's clothes");
					return;
				}
				if(item_select == 9){
					do_toggle(ninja);
					if(!ninja) SET_CHAR_VISIBLE(pPlayer, true);
					return;
				}
				if(item_select == 10){
					do_toggle(superfight);
					return;
				}
				if(item_select == 11){
					if(!rblip) print("Online Players will not be able to see your blip.");
					do_toggle(rblip);
					godmode = true;
					pprotection = rblip;
					if(!rblip) SET_PLAYER_CONTROL(GetPlayerIndex(), true);
					return;
				}
				if(item_select == 12){
					menu_shutdown();
					WAIT(500);
					if(DOES_SCRIPT_EXIST("player_menuiv")){
						REQUEST_SCRIPT("player_menuiv");
						while(!HAS_SCRIPT_LOADED("player_menuiv")){
							REQUEST_SCRIPT("player_menuiv");
							WAIT(0);
						}
						START_NEW_SCRIPT("player_menuiv", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("player_menuiv");
					}
					else print_long("~r~player_menuiv.sco Doesn't exist");
					return;
				}
				if(item_select == 13){
					menu_shutdown();
					WAIT(500);
					if(DOES_SCRIPT_EXIST("buffy_model")){
						REQUEST_SCRIPT("buffy_model");
						while(!HAS_SCRIPT_LOADED("buffy_model")){
							REQUEST_SCRIPT("buffy_model");
							WAIT(0);
						}
						START_NEW_SCRIPT("buffy_model", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("buffy_model");
					}
					else print_long("~r~buffy_model.sco Doesn't exist");
					return;
				}
				if(item_select == 15){
					do_toggle(bpvest);
					return;
				}
			}
			if(last_selected[1] == 12){
				if(item_select == 2){
					spawnguards(MODEL_M_O_HASID_01, WEAPON_SHOTGUN);
					return;
				}
				else if(item_select == 3){
					spawnguards(MODEL_IG_LILJACOB, WEAPON_MP5);
					return;
				}
				else if(item_select == 4){
					spawnguards(MODEL_IG_BRUCIE, WEAPON_POOLCUE);
					return;
				}
				else if(item_select == 5){
					spawnguards(MODEL_M_Y_GAFR_LO_01, WEAPON_MICRO_UZI);
					return;
				}
				else if(item_select == 6){
					spawnguards(MODEL_M_M_FBI, WEAPON_DEAGLE);
					return;
				}
				else if(item_select == 7){
					spawnguards(MODEL_M_Y_COP, WEAPON_SHOTGUN);
					return;
				}
				else if(item_select == 8){
					spawnguards(MODEL_M_M_FATCOP_01, WEAPON_RLAUNCHER);
					return;
				}
				else if(item_select == 9){
					spawnguards(MODEL_M_Y_MULTIPLAYER, WEAPON_AK47);
					return;
				}
				else if(item_select == 10){
					spawnguards(MODEL_F_Y_MULTIPLAYER, WEAPON_BARETTA);
					return;
				}
				else if(item_select == 11){
					spawnguards(MODEL_M_M_GUNNUT_01, WEAPON_M4);
					return;
				}
				else if(item_select == 12){
					spawnguards(MODEL_M_Y_CLUBFIT, WEAPON_BASEBALLBAT);
					return;
				}
				else if(item_select == 13){
					spawnguards(MODEL_F_Y_STRIPPERC01, WEAPON_POOLCUE);
					return;
				}
				else if(item_select == 14){
					spawnguards(MODEL_M_Y_SWAT, WEAPON_M4);
					return;
				}
				else if(item_select == 15){
					spawnguards(MODEL_M_Y_GMAF_HI_02, WEAPON_DEAGLE);
					return;
				}
				else if(item_select == 16){
					spawnguards(MODEL_M_Y_THIEF, WEAPON_KNIFE);
					return;
				}
				else if(item_select == 17){
					spawnguards(MODEL_M_Y_NHELIPILOT, WEAPON_SNIPERRIFLE);
					return;
				}
				else if(item_select == 18){
					spawnguards(MODEL_M_M_LOONYBLACK, WEAPON_MOLOTOV);
					return;
				}
				else if(item_select == 19){
					spawnguards(MODEL_M_Y_AIRWORKER, WEAPON_UNARMED);
					return;
				}
			}
			if(last_selected[1] == 16){
				if(item_select == 1){
					teleport_char(pPlayer,savex,savey,savez+1);
					print("Teleported to saved location");
					return;
				}
				if(item_select == 2){
					GET_CHAR_COORDINATES(pPlayer,&savex,&savey,&savez);
					print("Saved current location");
					return;
				}
				if(item_select == 3){
					do_toggle(xyzh);
					return;
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(item_select == 6){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						FIX_CAR(pveh);
						SET_VEHICLE_DIRT_LEVEL(pveh,0.0);
						print("Vehicle fixed & washed!");
					}
					return;
				}
				if(item_select == 7){
					if(!hydrolics) print("Hold X for hydrolics");
					do_toggle(hydrolics);
					return;
				}
				if(item_select == 8){
					if(!lowerpveh) print("All Vehicles will now be lowered");
					do_toggle(lowerpveh);
					return;
				}
				if(item_select == 9){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						uint lock;
						// Vehicle pveh;
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						GET_CAR_DOOR_LOCK_STATUS(pveh,&lock);
						if(lock == VEHICLE_DOOR_UNLOCKED){
							LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_LOCKED_BOTH_SIDES);
							print("Doors locked!");
						}
						else{
							LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_UNLOCKED);
							print("Doors unlocked!");
						}
					}
					return;
				}
				if(item_select == 10){
					if(!rainbowcar) print("All Vehicles will now be rainbow colored");
					do_toggle(rainbowcar);
					return;
				}
				if(item_select == 11){
					do_toggle(nos);
					vhelper = !nos;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					if(IS_CHAR_IN_ANY_CAR(pPlayer) && nos){
						SET_CAR_CAN_BE_DAMAGED(pveh,false);
						SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
						SET_CAR_PROOFS(pveh, true, false, true, true, true);
						WAIT(100);
						SET_PETROL_TANK_HEALTH(pveh, -1);
					}
					if(!nos && IS_CHAR_IN_ANY_CAR(pPlayer)){
						FIX_CAR(pveh);
						SET_VEHICLE_DIRT_LEVEL(pveh, 0);
						WASH_VEHICLE_TEXTURES(pveh, 255);
						SET_CAR_ENGINE_ON(pveh,true,true);
						SET_CAR_ENGINE_ON(pveh,true,true);
					}
					return;
				}
				if(item_select == 12){
					if(!veh_height) print("All Cars will now be raised");
					do_toggle(veh_height);
					return;
				}
				if(item_select == 16){
					if(!rocketveh) print("RocketCar, press ~PAD_X~ to fire rockets.");
					do_toggle(rocketveh);
					return;
				}
				if(item_select == 17){
					if(!carjump) print("Car Jump, press ~PAD_RB~ to jump.");
					do_toggle(carjump);
					return;
				}
				if(item_select == 18){
					if(!bw_checker) print("All Vehicles will now be White/Black checkered");
					do_toggle(bw_checker);
					return;
				}
				if(item_select == 19){
					if(!rb_checker) print("All Vehicles will now be Red/Blue checkered");
					do_toggle(rb_checker);
					return;
				}
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(item_select == 1){
					if(menu[item_select].value == 1){
						GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_UNARMED, AMMO_MAX, false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
						print("You have been given advanced weapons.");
					}
					else if(menu[item_select].value == 2){
						GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_UNARMED, AMMO_MAX, false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MOLOTOV,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
						print("You have been given poor weapons.");						
					}
					else if(menu[item_select].value == 3){
						uint episode = GET_CURRENT_EPISODE();
						if(episode == 2){
							GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_UNARMED, AMMO_MAX, false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
							GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
							print("You have been given TBOGT weapons.");
							return;
						}
						print("You must be on The Ballad of Gay Tony to use this");
					}
					return;
				}
				else if(item_select == 3){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_GRENADE,AMMO_MAX,false);
					print("You have been given some grenades");				
				}
				else if(item_select == 4){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_PISTOL,AMMO_MAX,false);
					print("You have been given a Glock 17");		
				}
				else if(item_select == 5){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_DEAGLE,AMMO_MAX,false);
					print("You have been given a Desert Eagle");		
				}
				else if(item_select == 6){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SHOTGUN,AMMO_MAX,false);
					print("You have been given a Pump Shotgun");		
				}
				else if(item_select == 7){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BARETTA,AMMO_MAX,false);
					print("You have been given a Tactical Shotgun");		
				}
				else if(item_select == 8){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MICRO_UZI,AMMO_MAX,false);
					print("You have been given a Micro Uzi");		
				}
				else if(item_select == 9){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MP5,AMMO_MAX,false);
					print("You have been given an MP5");		
				}
				else if(item_select == 10){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_AK47,AMMO_MAX,false);
					print("You have been given an AK-47");		
				}
				else if(item_select == 11){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M4,AMMO_MAX,false);
					print("You have been given an AR-15");		
				}
				else if(item_select == 12){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_M40A1,AMMO_MAX,false);
					print("You have been given an M40A1");		
				}
				else if(item_select == 13){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
					print("You have been given a Sniper Rifle");		
				}
				else if(item_select == 14){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_RLAUNCHER,AMMO_MAX,false);
					print("You have been given an RPG");		
				}
				else if(item_select == 15){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_BASEBALLBAT,1,false);
					print("You have been given a baseball bat");		
				}
				else if(item_select == 16){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_POOLCUE,1,false);
					print("You have been given a pool stick");			
				}
				else if(item_select == 17){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_KNIFE,1,false);
					print("You have been given a knife");			
				}
				else if(item_select == 18){
					GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_MOLOTOV,AMMO_MAX,false);
					print("You have been given a molotov");			
				}
				return;
			}
			if(last_selected[1] == 4){
				if(item_select == 1){
					if(!objectgun){
						print("Use the Glock to shoot the selected object");
					}
					do_toggle(objectgun);
					return;
				}
				else if(item_select == 2){
					if(!del_objgun) print_long("~b~Every shot will delete the last shot object");
					do_toggle(del_objgun);
					return;
				}
				else if(item_select == 3){
					object_launch = 0x3675A6C3;
					print("Object launcher will now shoot Dildos");
				}
				else if(item_select == 4){
					object_launch = 0x2718C626;
					print("Object launcher will now shoot Red cubes");
				}
				else if(item_select == 5){
					object_launch = 0xDD28B247;
					print("Object launcher will now shoot Blue cubes");
				}
				else if(item_select == 6){
					object_launch = 0xBB1F6E71;
					print("Object launcher will now shoot Green cubes");
				}
				else if(item_select == 7){
					object_launch = 0x90FA92C6;
					print("Object launcher will now shoot Bowling Balls");
				}
				else if(item_select == 8){
					object_launch = 0x3C4E43BC;
					print("Object launcher will now shoot Donuts");
				}
				else if(item_select == 9){
					object_launch = 0xFE520830;
					print("Object launcher will now shoot Bricks");
				}
				else if(item_select == 10){
					object_launch = 0x94A8F60F;
					print("Object launcher will now shoot Bins");
				}
				else if(item_select == 11){
					object_launch = 0xEB12D336;
					print("Object launcher will now shoot Dumpsters");
				}
				else if(item_select == 12){
					object_launch = 0x6066DF1D;
					print("Object launcher will now shoot gumball machines");
				}
				else if(item_select == 13){
					object_launch = 0xF4A206E4;
					print("Object launcher will now shoot Bowling Pins");
				}
				else if(item_select == 14){
					object_launch = 0x7FC5F693;
					print("Object launcher will now shoot Sprunk Boxes");
				}
				else if(item_select == 15){
					object_launch = 0xD318157E;
					print("Object launcher will now shoot TV's");
				}
			}
			if(last_selected[1] == 6){
				if(item_select == 1){
					if(!cargun){
						print("Use the Deagle to shoot the selected car");
						GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_DEAGLE, AMMO_MAX, 0);
						SET_CURRENT_CHAR_WEAPON(pPlayer, WEAPON_DEAGLE, true);	
					}
					do_toggle(cargun);
					return;
				}
				else if(item_select == 2){
					if(!del_cargun) print_long("~b~Every shot will delete the last shot car");
					do_toggle(del_cargun);
					return;
				}
				else if(item_select == 3){
					if(!exp_cargun) print_long("~b~Every shot car will explode on impact");
					do_toggle(exp_cargun);
					return;
				}
				else if(item_select == 4){
					if(!strat_cargun) print_long("~b~Every shot car will now shoot facing forward");
					do_toggle(strat_cargun);
					return;
				}
				else if(item_select == 5){
					if(!grond_cargun) print_long("~b~Every shot car will now on be on the ground");
					do_toggle(grond_cargun);
					return;
				}
				else if(item_select == 6){
					car_launch = MODEL_SULTANRS;
					print("Car launcher will now shoot Sultan RS's");
					return;
				}
				else if(item_select == 7){
					car_launch = MODEL_AIRTUG;
					print("Car launcher will now shoot Airtug's");
					return;
				}
				else if(item_select == 8){
					car_launch = MODEL_AMBULANCE;
					print("Car launcher will now shoot Ambulances's");
					return;
				}
				else if(item_select == 9){
					car_launch = MODEL_PHANTOM;
					print("Car launcher will now shoot Phantom's");
					return;
				}
				else if(item_select == 10){
					car_launch = MODEL_BUS;
					print("Car launcher will now shoot Bus's");
					return;
				}
				else if(item_select == 11){
					#ifndef PRIVATE
					print("Private Version Only");
					return;
					#endif
					car_launch = MODEL_TUGA;
					print("Car launcher will now shoot Tug's");
					return;
				}
				else if(item_select == 12){
					car_launch = MODEL_TRASH;
					print("Car launcher will now shoot Trashmaster's");
					return;
				}
				else if(item_select == 13){
					car_launch = MODEL_SUBWAY_LO;
					print("Car launcher will now shoot Trains's (common.rpf must be modded)");
					return;
				}
				else if(item_select == 14){
					car_launch = MODEL_RIPLEY;
					print("Car launcher will now shoot Ripley's");
					return;
				}
				else if(item_select == 15){
					car_launch = MODEL_ADMIRAL;
					print("Car launcher will now shoot Admiral's");
					return;
				}
				else if(item_select == 16){
					car_launch = MODEL_CAVALCADE;
					print("Car launcher will now shoot Cavalcade's");
					return;
				}
				else if(item_select == 17){
					car_launch = MODEL_FUTO;
					print("Car launcher will now shoot Futo's");
					return;
				}
				else if(item_select == 18){
					car_launch = MODEL_NOOSE;
					print("Car launcher will now shoot Noose cruisers's");
					return;
				}
			}
		}
		if(last_selected[0] == 5){
			if(last_selected[1] == 1){
				if(item_select == 2){
					do_toggle(xmc_compact);
					return;
				}
				if(item_select == 3){
					do_toggle(xmc_chat);
					return;
				}
				if(item_select == 4){
					do_toggle(xmc_dim);
					return;
				}
				if(item_select == 5){
					do_toggle(xmc_online_col);
					return;
				}
				if(item_select == 6){
					do_toggle(xmc_keyboard);
					return;
				}
				if(item_select == 7){
					do_toggle(xmc_switch);
					return;
				}
			}
			if(last_selected[1] == 2){
				if(item_select == 1){
					for(i;i <= 5;i++){
						create_throwable_object(0x9976ECC4);
					}
				}
				if(item_select == 2){
					create_throwable_object(0x6066DF1D);
				}
				if(item_select == 3){
					create_throwable_object(0x2718C626);
					create_throwable_object(0xDD28B247);
					create_throwable_object(0xCCEA11CA);
					create_throwable_object(0xBB1F6E71);
					create_throwable_object(0xA6E545FD);
					create_throwable_object(0x5C5030D4);
				}
				if(item_select == 4){
					for(i;i <= 5;i++){
						create_throwable_object(0x9D2A7EF8);
					}
				}
				if(item_select == 5){
					for(i;i <= 5;i++){
						create_throwable_object(0x501811B6);
					}
				}
				if(item_select == 6){
					for(i;i <= 5;i++){
						create_throwable_object(0x48FA2738);
					}
				}
				if(item_select == 7){
					create_throwable_object(0x8079978D);
				}
				if(item_select == 8){
					create_throwable_object(0x3129B913);
				}
				if(item_select == 9){
					create_throwable_object(0xF4A206E4);
				}	
				if(item_select == 10){	
					create_throwable_object(0x7FC5F693);	
				}
				if(item_select == 11){	
					create_throwable_object(0xD318157E);	
				}	
				if(item_select == 12){	
					create_throwable_object(0x90FA92C6);	
				}
			}
			if(last_selected[1] == 3){
				if(item_select == 1){
					create_big_explosion(2247.4224,755.9057,5.853);
					WAIT(500);
					create_big_explosion(2231.6912,737.4642,5.853);
					WAIT(500);
					create_big_explosion(2214.0000,718.9000,5.83);
					WAIT(500);
					print("Launching strike at Aiport helipads!");				
					return;
				}
				if(item_select == 2){
					create_big_explosion(2621.6484,445.9162,5.35);
					print("Launching strike at Aiport Tower!");
					return;
				}
				if(item_select == 3){
					create_big_explosion(2268.2544,519.2332,5.4396);
					WAIT(500);
					create_big_explosion(2228.9453,526.2129,5.4401);
					WAIT(500);
					create_big_explosion(2221.8818,484.9935,5.4562);
					WAIT(500);
					create_big_explosion(2234.6369,456.6962,5.4562);
					print("Launching strike at Aiport parking!");
					return;
				}
				if(item_select == 4){
					xmc_airstrike();
					return;
				}
				if(item_select == 5){
					GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
					ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,50.0f,true,false,0.7f);
					print("Launching strike at your location!");
					return;
				}
			}
			if(last_selected[1] == 13){
				if(item_select == 1){
					ENABLE_FRONTEND_RADIO();
					SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(1);
					SET_MOBILE_PHONE_RADIO_STATE(1);
					RETUNE_RADIO_UP();
					WAIT(1);
					print(GET_PLAYER_RADIO_STATION_NAME());
					return;
				}
				if(item_select == 2){
				//	DISABLE_FRONTEND_RADIO();
					RETUNE_RADIO_TO_STATION_INDEX(255);
					SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(0);
					SET_MOBILE_PHONE_RADIO_STATE(0);
					print("Radio Off");
					return;
				}
				if(item_select == 3){
					ENABLE_FRONTEND_RADIO();
					SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(1);
					SET_MOBILE_PHONE_RADIO_STATE(1);
					RETUNE_RADIO_UP();
					WAIT(1);
					print(GET_PLAYER_RADIO_STATION_NAME());
					return;
				}
				if(item_select == 4){
					ENABLE_FRONTEND_RADIO();
					SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(1);
					SET_MOBILE_PHONE_RADIO_STATE(1);
					RETUNE_RADIO_DOWN();
					WAIT(1);
					print(GET_PLAYER_RADIO_STATION_NAME());
					return;
				}
			}
			if(last_selected[1] == 15){
				if(item_select == 1){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_SUNNY);
					return;
				}
				else if(item_select == 2){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
					return;
				}
				else if(item_select == 3){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY_2);
					return;
				}
				else if(item_select == 4){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_SUNNY_WINDY);
					return;
				}
				else if(item_select == 5){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_SUNNY_WINDY_2);
					return;
				}
				else if(item_select == 6){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_DRIZZLE);
					return;
				}
				else if(item_select == 7){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_FOGGY);
					return;
				}
				else if(item_select == 8){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_RAINING);
					return;
				}
				else if(item_select == 9){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_LIGHTNING);
					return;
				}
				else if(item_select == 10){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					FORCE_WEATHER_NOW(WEATHER_CLOUDY);
					return;
				}
				else if(item_select == 11){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						return;
					}
					GET_TIME_OF_DAY(&tick, &i);
					SET_TIME_OF_DAY(tick + 1, i);
					return;
				}
				else if(item_select == 12){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						fweather = false;
						reset_menu();
						return;
					}
					do_toggle(fweather);
					return;
				}
				else if(item_select == 13){
					if(GET_HOST_ID() != GET_PLAYER_ID()){
						print("~r~You must be Host");
						rweather = false;
						reset_menu();
						return;
					}
					do_toggle(rweather);
					return;
				}
			}
			if(last_selected[1] == 17){
				if(item_select == 1){
					if(!DOES_CAM_EXIST(gta2cam)){
						CREATE_CAM(14, &gta2cam);
						SET_CAM_ACTIVE(gta2cam, 1);
						SET_CAM_PROPAGATE(gta2cam, 1);
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						ATTACH_CAM_TO_PED(gta2cam, pPlayer);
						SET_CAM_ATTACH_OFFSET(gta2cam, 0.0, 0.0, 19.27);
						POINT_CAM_AT_PED(gta2cam, pPlayer);
						SET_CAM_FOV(gta2cam, 70.0);
					}
					else{
						SET_CAM_ACTIVE(gta2cam, 0);
						SET_CAM_PROPAGATE(gta2cam, 0);
						ACTIVATE_SCRIPTED_CAMS(0, 0);
						DESTROY_CAM(gta2cam);
						WAIT(100);
						SET_CAM_BEHIND_PED(pPlayer);
					}
					reset_menu();
					return;
				}
				else if(item_select == 2){
					GET_ROOT_CAM(&XmcCam);
					SET_DRUNK_CAM(XmcCam, 1.0, 15000);
					print("You are drunk for 15 seconds");
				}
			}
			if(last_selected[1] == 19){
				if(item_select == 1){
					drive_limo(limo_model,3);
					return;
				}
				else if(item_select == 2){
					if(limo_loop) print("Please set a waypoint for Escort");
					else if(limo_land) print("Please wait until destination is reached");
					else{
						limo_model = MODEL_STRETCH;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 3){
					if(limo_loop) print("Please set a waypoint for Airlift");
					else{
						limo_model = MODEL_MAVERICK;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 4){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_CAVALCADE;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 5){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_BUS;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 6){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_POLICE;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 7){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_AMBULANCE;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 8){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_FBI;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 9){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_TAXI;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 10){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_PSTOCKADE;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 11){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						limo_model = MODEL_ORACLE;
						drive_limo(limo_model,1);
					}
					return;
				}
				else if(item_select == 12){
					if(limo_loop) print("Please set a waypoint for Escort");
					else{
						if(IS_CHAR_IN_ANY_CAR(pPlayer)){
							GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
							GET_CAR_MODEL(pveh, &model);
							limo_model = model;
							drive_limo(limo_model,1);
						}
					}
					return;
				}
			}
		}
	}
	if(menu_level == 3){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){ //Online players
				if(last_selected[2] == 1){ //All players
					uint player_loop = player_count - 1;
					if(item_select == 1){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								REMOVE_ALL_CHAR_WEAPONS(players[i].ped);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_DEAGLE,AMMO_MAX,false);
								if(GET_CURRENT_EPISODE() != 2) GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_GRENADE,AMMO_MAX,false);
								else GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_EPISODIC_16,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_MP5,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_M4,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_BARETTA,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_POOLCUE,1,false);
								GIVE_WEAPON_TO_CHAR(players[i].ped,WEAPON_ARMOUR,1,false);
								ADD_ARMOUR_TO_CHAR(players[i].ped,99);
							}
						}
						print("Gave everyone weapons");
						return;
					}
					else if(item_select == 2){
						#ifndef PRIVATE
							print("Private Version only");
							return;
						#endif
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								REMOVE_ALL_CHAR_WEAPONS(players[i].ped);
								WAIT(10);
							}
						}
						print("Removed everyone's weapons");
						return;
					}
					else if(item_select == 3){
						if(!chaos) print("All Talking players shall witness chaos");
						do_toggle(chaos);
						return;
					}
					else if(item_select == 4){
						if(IS_CHAR_IN_ANY_CAR(pPlayer)){
							GET_CAR_CHAR_IS_USING(pPlayer,&paveh);
							GET_CAR_HEADING(paveh,&heading);
							GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
							GET_DRIVER_OF_CAR(paveh,&driver);
							if(driver == pPlayer){
								for(i = 0;i <= player_loop;i++){
									if(DOES_CHAR_EXIST(players[i].ped) && IS_CHAR_IN_ANY_CAR(players[i].ped)){
										if(is_whitelisted(i)) continue;
										GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 100){
												break;
											}
											WAIT(0);
										}      	
										if(!IS_CAR_ATTACHED(pveh)){
											speed -= 4.70;
											SET_CAR_HEADING(pveh,heading);
											teleport_net_char(players[i].ped,x,y,z);
											FREEZE_CAR_POSITION(pveh,true);
											ATTACH_CAR_TO_CAR(pveh,paveh,0,0,speed,0,0,0,0);
											LOCK_CAR_DOORS(pveh,4);
										}
										else if(IS_CAR_ATTACHED(pveh)){
											LOCK_CAR_DOORS(pveh,1);
											FREEZE_CAR_POSITION(pveh,false);
											DETACH_CAR(pveh);
										}
									}
								}
							}
							else print("You must be the driver of your own vehicle");
						}
						else print("Your not a in Vehicle");
						return;
					}
					else if(item_select == 5){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
								ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
								WAIT(10);
							}
						}
						print("Attached a Hippo to everyone");
						return;
					}
					else if(item_select == 6){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									// Vehicle pveh;
									GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										if(tick >= 150){
											//print("~r~Error");
											//return;
											continue;
										}
										WAIT(0);
									}
									DELETE_CAR(&pveh);
									WAIT(10);
									MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
								}
							}
							WAIT(50);
						}
						print("Deleted Everyone's cars");
						return;
					}
					else if(item_select == 7){
						//// float x,y,z;
						#ifndef PRIVATE
							print("Private Version only");
							return;
						#endif
						GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
						FREEZE_CHAR_POSITION(pPlayer,true);
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									teleport_net_char(players[i].ped,x,y,z);
								}
							}
						}
						print("Teleported Everyone to you");
						WAIT(500);
						FREEZE_CHAR_POSITION(pPlayer,false);
						return;
					}
					else if(item_select == 8){
						#ifndef PRIVATE
							print("Private Version only");
							return;
						#endif
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									teleport_net_char(players[i].ped,-1079.8,-469.7,2.62);
								}
							}
						}
						print("Teleported Everyone to Jail");
						return;
					}
					else if(item_select == 9){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(!IS_CHAR_IN_ANY_CAR(players[i].ped)) continue;
								GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 150){
										//print("~r~Error");
										//return;
										continue;
									}
									WAIT(0);
								}
								teleport_net_char(players[i].ped,2175.3516,761.2235,30.0);
							}
						}
						print("Teleported Everyone to the Airport");
					}
					else if(item_select == 10){
						for(i = 0;i <= player_loop;i++){
							if(is_whitelisted(i)) continue;
							if(DOES_CHAR_EXIST(players[i].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
									GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 150){
											//print("~r~Error");
											//return;
											continue;
										}
										WAIT(0);
									}
									APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
								}
							}
						}
						print("Slingshot Everyone's cars");
						return;
					}
						else if(item_select == 11){
							for(i = 0;i <= player_loop;i++){
								if(DOES_CHAR_EXIST(players[i].ped)){
									if(is_whitelisted(i)) continue;
									cubes[0] = 0x2718C626; //Red
									cubes[1] = 0xDD28B247; //Blue
									cubes[2] = 0xCCEA11CA; //Yellow
									cubes[3] = 0xBB1F6E71; //Green 
									cubes[4] = 0xA6E545FD; //Purple
									cubes[5] = 0x5C5030D4; //Orange

									GENERATE_RANDOM_INT_IN_RANGE(0,5,&i);

									CREATE_OBJECT(cubes[i],0.0,0.0,0.0,&otmp,true);
									ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0x4B5,0.0,0.0,0.0,0.0,0.0,3.0,false);
									WAIT(10);
									MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								}
							}
							print("Attached a Cube to everyone");
							return;
						}
						else if(item_select == 12){
							for(i = 0;i <= player_loop;i++){
								if(DOES_CHAR_EXIST(players[i].ped)){
									if(is_whitelisted(i)) continue;
									CREATE_OBJECT(0xB570F614,0.0,0.0,0.0,&otmp,true);
									ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0,0,.25,-.50,-1.55,3.10,0,0);
									WAIT(10);
									MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								}
							}
							print("Attached a Dick to everyone");
							return;
						}
						else if(item_select == 13){
							for(i = 0;i <= player_loop;i++){
								if(DOES_CHAR_EXIST(players[i].ped)){
									if(is_whitelisted(i)) continue;
									if(IS_CHAR_IN_ANY_CAR(players[i].ped)){
										GET_CAR_CHAR_IS_USING(players[i].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												continue;
											}
											WAIT(0);
										}
									//	FREEZE_CAR_POSITION(pveh,true);
										SET_CAR_CAN_BE_DAMAGED(pveh,true);
										SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
										SET_CAN_BURST_CAR_TYRES(pveh,true);
										BURST_CAR_TYRE(pveh,0);
										BURST_CAR_TYRE(pveh,1);
										BURST_CAR_TYRE(pveh,4);
										BURST_CAR_TYRE(pveh,5);
										SET_ENGINE_HEALTH(pveh,0.0);
										SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
									}
								}
							}
							print("Made all cars retarded");
							return;
						}
						else if(item_select == 14){
						#ifndef PRIVATE
							print("Private Version only");
							return;
						#endif
							for(i = 0;i <= player_loop;i++){
								if(DOES_CHAR_EXIST(players[i].ped)){
									if(is_whitelisted(i)) continue;
									START_CHAR_FIRE(players[i].ped);
								}
							}
							print("Burned all players");
							return;
						}
						else if(item_select == 15){
							#ifndef PRIVATE
								print("Private Version only");
								return;
							#endif
							for(i = 0;i <= player_loop;i++){
								if(DOES_CHAR_EXIST(players[i].ped)){
									if(is_whitelisted(i)) continue;
									GET_CHAR_COORDINATES(players[i].ped,&x,&y,&z);
									ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
								}
							}
							print("Chronicle'd all players");
							return;
						}
						else if(item_select == 16){
							for(i = 0;i <= player_loop;i++){
								if(is_whitelisted(i)) continue;
								if(DOES_CHAR_EXIST(players[i].ped)){
									CREATE_OBJECT(0x1F925137,0.0,0.0,0.0,&otmp,true);
									ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0xA8F6,0.0,0.0,0.7,0.0,0.0,0.0,false);
									WAIT(10);
								}
							}
							print("Attached a Cone to everyone");
							return;
						}
						else if(item_select == 17){
							for(i = 0;i <= player_loop;i++){
								if(is_whitelisted(i)) continue;
								if(DOES_CHAR_EXIST(players[i].ped)){
									CREATE_OBJECT(0x659BA938,0.0,0.0,0.0,&otmp,true);
									ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0xA8F6,0.0,0.0,0.7,0.0,0.0,0.0,false);
									WAIT(10);
								}
							}
							print("Attached a Tire to everyone");
							return;
						}
						else if(item_select == 18){
							for(i = 0;i <= player_loop;i++){
								if(is_whitelisted(i)) continue;
								if(DOES_CHAR_EXIST(players[i].ped)){
									CREATE_OBJECT(0x90FA92C6,0.0,0.0,0.0,&otmp,true);
									ATTACH_OBJECT_TO_PED(otmp,players[i].ped,0xA8F6,0.015,0.01,0.69,0.0,0.0,0.0,false);
									WAIT(10);
								}
							}
							print("Attached a Bowling Ball to everyone");
							return;
						}
				}
				if(last_selected[2] == 2){
					if(item_select == 1){
						for(i = 0;i <= 6;i++){
							if(DOES_CHAR_EXIST(shortcut_players[i])){
								REMOVE_ALL_CHAR_WEAPONS(shortcut_players[i]);
								WAIT(10);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i], WEAPON_UNARMED, AMMO_MAX, false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_POOLCUE,1,false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_DEAGLE,AMMO_MAX,false);
								if(GET_CURRENT_EPISODE() != 2) GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_GRENADE,AMMO_MAX,false);
								else GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_EPISODIC_16,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_RLAUNCHER,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_MP5,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_BARETTA,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_SNIPERRIFLE,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_M4,AMMO_MAX,false);
								GIVE_WEAPON_TO_CHAR(shortcut_players[i],WEAPON_ARMOUR,1,false);
								ADD_ARMOUR_TO_CHAR(shortcut_players[i],99);
							}
						}
						print("Gave all shortcut players Weapons & Armor");
						return;
					}
					else if(item_select == 2){
						for(i = 0;i <= 6;i++){
							if(DOES_CHAR_EXIST(shortcut_players[i])) REMOVE_ALL_CHAR_WEAPONS(shortcut_players[i]);
						}
						print("All Shortcut Players are now unarmed!");
						return;
					}
					else if(item_select == 3){
						GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
						for(i = 0;i <= 6;i++){
							if(!DOES_CHAR_EXIST(shortcut_players[i])) continue;
							if(!IS_CHAR_IN_ANY_CAR(shortcut_players[i])) continue;
							GET_CAR_CHAR_IS_USING(shortcut_players[i], &pveh);
							teleport_net_char(shortcut_players[i],x,y,z);
						}
						print("Teleported all shortcut players to you");
						return;
					}
					else if(item_select == 4){
						for(i = 0;i <= 6;i++){
							if(!DOES_CHAR_EXIST(shortcut_players[i])) continue;
							if(!IS_CHAR_IN_ANY_CAR(shortcut_players[i])) continue;
							GET_CAR_CHAR_IS_USING(shortcut_players[i],&pveh);
							GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
							REQUEST_CONTROL_OF_NETWORK_ID(nvid);
							tick = 0;
							while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
								tick++;
								if(tick >= 150){
									continue;
								}
								WAIT(0);
							}
							DELETE_CAR(&pveh);
							WAIT(10);
							MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
						}
						print("Deleted all shortcut player's cars");
						return;
					}
					else if(item_select == 7){
						for(i = 0;i <= 6;i++){
							shortcut_players[i] = INVALID_HANDLE;
						}
						print("Removed all shortcut players from list");
						return;
					}
				}
				else{
					uint index = (last_selected[2] - 3);
					if(item_select == 2){
						if(DOES_CHAR_EXIST(players[index].ped)){
							for(i = 0;i <= 6;i++){
								if(!DOES_CHAR_EXIST(shortcut_players[i])){
									shortcut_players[i] = players[index].ped;
									print("Added player to shortcut");
									return;
								}
							}
							print("Shortcut list full (7 Max)");
							return;
						}
						return;
					}
				}
			}
		}
		if(last_selected[0] == 1){
			if(last_selected[1] == 2){
				if(last_selected[2] == 1){
					if(item_select == 1){
						if(menu[item_select].value == 1){
							//Request the anim and make sure it exists then load it
							//This also sets what group of anims your going to be selecting from
							REQUEST_ANIMS("amb@park_taichi_a");
							//Do not proceed until animation group is loaded
							//mainly to avoid freezing
							while(!HAVE_ANIMS_LOADED("amb@park_taichi_a")) WAIT(0);
							//Anims are like a group of dances/moves. Call one in the group you loaded above down here
							//then also say stuff like how long to play dance and if to repeat
							// amb@park_taichi_a = Anim Group    taichi01 = Specific Dance in the loaded anim group
							//pPlayer = you      8.0 = seconds to play
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi01","amb@park_taichi_a",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@park_taichi_b");
							while(!HAVE_ANIMS_LOADED("amb@park_taichi_b")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"taichi02","amb@park_taichi_b",8.0,99999,1);
							return;
						}					
					}
					if(item_select == 2){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@dance_maleidl_a");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_a")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_maleidl_a",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@dance_maleidl_b");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_b")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_maleidl_b",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 3){
							REQUEST_ANIMS("amb@dance_maleidl_c");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_c")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_maleidl_c",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 4){
							REQUEST_ANIMS("amb@dance_maleidl_d");
							while(!HAVE_ANIMS_LOADED("amb@dance_maleidl_d")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_d","amb@dance_maleidl_d",8.0,99999,1);
							return;
						}
					}
					if(item_select == 3){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@dance_femidl_a");
							while(!HAVE_ANIMS_LOADED("amb@dance_femidl_a")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_a","amb@dance_femidl_a",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@dance_femidl_b");
							while(!HAVE_ANIMS_LOADED("amb@dance_femidl_b")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_b","amb@dance_femidl_b",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 3){
							REQUEST_ANIMS("amb@dance_femidl_c");
							while(!HAVE_ANIMS_LOADED("amb@dance_femidl_c")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"loop_c","amb@dance_femidl_c",8.0,99999,1);
							return;
						}					
					}
					if(item_select == 4){
						REQUEST_ANIMS("missstripclublo");
						while(!HAVE_ANIMS_LOADED("missstripclublo")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"pole_dance_a","missstripclublo",8.0,99999,1);
						return;
					}
					if(item_select == 5){
						REQUEST_ANIMS("misscar_sex");
						while(!HAVE_ANIMS_LOADED("misscar_sex")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"m_handjob_intro_low","misscar_sex",8.0,0,0x20);
						return;
					}
					if(item_select == 6){
						REQUEST_ANIMS("busted");
						while(!HAVE_ANIMS_LOADED("busted")) WAIT(0); 
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"idle_2_hands_up","busted",8.0,0,0x20);
						return;
					}
					if(item_select == 7){
						REQUEST_ANIMS("amb@smoking");
						while(!HAVE_ANIMS_LOADED("amb@smoking")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"stand_smoke","amb@smoking",8.0,99999,1);
						return;
					}
					if(item_select == 8){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@drunk");
							while(!HAVE_ANIMS_LOADED("amb@drunk")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"wasted_seated","amb@drunk",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@drunk");
							while(!HAVE_ANIMS_LOADED("amb@drunk")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"wasteda","amb@drunk",8.0,99999,1);
							return;
						}
					}
					if(item_select == 9){
						if(GET_CURRENT_EPISODE() != 0){
							print("~g~You must be on Original");
							return;
						}
						REQUEST_ANIMS("missdwayne1");
						while(!HAVE_ANIMS_LOADED("missdwayne1")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"player_execute","missdwayne1",8.0,0,0);
						return;
					}
					if(item_select == 10){
						REQUEST_ANIMS("doors");
						while(!HAVE_ANIMS_LOADED("doors")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"door_knock","doors",8.0,0,0);
						return;
					}
					if(item_select == 11){
						REQUEST_ANIMS("amb@smoking_spliff");
						while(!HAVE_ANIMS_LOADED("amb@smoking_spliff")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"create_spliff","amb@smoking_spliff",8.0,99999,1);
						return;
					}
					if(item_select == 12){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("ev_dives");
							while(!HAVE_ANIMS_LOADED("ev_dives")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"plyr_roll_left","ev_dives",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("ev_dives");
							while(!HAVE_ANIMS_LOADED("ev_dives")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"plyr_roll_right","ev_dives",8.0,0,0);
							return;
						}
					}
					if(item_select == 13){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@nightclub_ext");
							while(!HAVE_ANIMS_LOADED("amb@nightclub_ext")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"bouncer_a_frisk","amb@nightclub_ext",8.0,0,0);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@nightclub_ext");
							while(!HAVE_ANIMS_LOADED("amb@nightclub_ext")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"bouncer_a_refuse_entry","amb@nightclub_ext",8.0,0,0);
							return;
						}
					}
					if(item_select == 14){
						REQUEST_ANIMS("gestures@mp_male");
						while(!HAVE_ANIMS_LOADED("gestures@mp_male")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"wave","gestures@mp_male",8.0,0,0);
						return;
					}
					if(item_select == 15){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@hooker");
							while(!HAVE_ANIMS_LOADED("amb@hooker")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"idle_a","amb@hooker",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@hooker");
							while(!HAVE_ANIMS_LOADED("amb@hooker")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"idle_b","amb@hooker",8.0,99999,1);
							return;
						}
						if(menu[item_select].value == 3){
							REQUEST_ANIMS("amb@hooker");
							while(!HAVE_ANIMS_LOADED("amb@hooker")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"idle_c","amb@hooker",8.0,99999,1);
							return;
						}
					}
					if(item_select == 16){
						REQUEST_ANIMS("ped");
						while(!HAVE_ANIMS_LOADED("ped")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"fuck_u","ped",8.0,0,0);
						return;
					}
					if(item_select == 17){
						REQUEST_ANIMS("ped");
						while(!HAVE_ANIMS_LOADED("ped")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"hail_taxi","ped",8.0,0,0);
						return;
					}
					if(item_select == 18){
						REQUEST_ANIMS("mini_bowling");
						while(!HAVE_ANIMS_LOADED("mini_bowling")) WAIT(0);
						TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"f_celeb_a","mini_bowling",8.0,0,0);
						return;
					}
					if(item_select == 19){
						if(menu[item_select].value == 1){
							REQUEST_ANIMS("amb@dating");
							while(!HAVE_ANIMS_LOADED("amb@dating")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"car_kiss_ds","amb@dating",8.0,0,0x20);
							return;
						}
						if(menu[item_select].value == 2){
							REQUEST_ANIMS("amb@dating");
							while(!HAVE_ANIMS_LOADED("amb@dating")) WAIT(0);
							TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"car_kiss_ps","amb@dating",8.0,0,0x20);
							return;
						}
					}
				}
				else if(last_selected[2] == 2){
					if(item_select == 1){
						SAY_AMBIENT_SPEECH(pPlayer, "Thanks", 1, 1, 0);
						print("~g~Thanks!");
						return;
					}
					else if(item_select == 2){
						HIGH_FALL_SCREAM(pPlayer);
						print("~g~AAAAHHHHHHH!");
						return;
				   }
					else if(item_select == 3){
						SAY_AMBIENT_SPEECH(pPlayer, "GET_OUT_OF_HERE", 1, 1, 0);
						print("~g~Get out of here!");
						return;
					}
					else if(item_select == 4){
						SAY_AMBIENT_SPEECH(pPlayer, "GENERIC_HI", 1, 1, 0);
						print("~g~Hi!");
						return;
					}
					else if(item_select == 5){
						SAY_AMBIENT_SPEECH(pPlayer, "HOOKER_SEX", 1, 1, 0);
						print("~g~Sexy time!");
						return;
					}
					else if(item_select == 6){
						SAY_AMBIENT_SPEECH(pPlayer, "GENERIC_FUCK_OFF", 1, 1, 0);
						print("~g~Fuck Off!");
						return;
					}
					else if(item_select == 7){
						SAY_AMBIENT_SPEECH(pPlayer, "MOBILE_CHAT", 1, 1, 0);
						print("~g~Phone Chat!");
						return;
					}
					else if(item_select == 8){
						SAY_AMBIENT_SPEECH(pPlayer, "GENERIC_BYE", 1, 1, 0);
						print("~g~Bye!");
						return;
					}
					else if(item_select == 9){
						SAY_AMBIENT_SPEECH(pPlayer, "SHOT_IN_LEG", 1, 1, 0);
						print("~g~I've been Shot!");
						return;
					}
					else if(item_select == 10){
						SAY_AMBIENT_SPEECH(pPlayer, "FIGHT", 1, 1, 0);
						print("~g~Lets Fight!");
						return;
					}
					return;
				}
				else if(last_selected[2] == 8){
					if(item_select == 1){
						CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a Hippo to Player");
						return;
					}
					else if(item_select == 2){
						cubes[0] = 0x2718C626; //Red
						cubes[1] = 0xDD28B247; //Blue
						cubes[2] = 0xCCEA11CA; //Yellow
						cubes[3] = 0xBB1F6E71; //Green 
						cubes[4] = 0xA6E545FD; //Purple
						cubes[5] = 0x5C5030D4; //Orange

						GENERATE_RANDOM_INT_IN_RANGE(0,5,&i);

						CREATE_OBJECT(cubes[i],0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0x4B5,0.0,0.0,0.0,0.0,0.0,3.0,false);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a Cube to Player");
						return;
					}
					else if(item_select == 3){
						CREATE_OBJECT(0xB570F614,0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0,0,.25,-.50,-1.55,3.10,0,0);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a Dick to Player");
						return;
					}
					else if(item_select == 4){
						CREATE_OBJECT(0xEB12D336,0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0,0,0,0.0,0.0,0.0,3.0,false);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a Dumpster to Player");
						return;
					}
					else if(item_select == 5){
						CREATE_OBJECT(0xD318157E,0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0x4B5,0.0,0.0,-0.3,0.0,0.0,3.0,false);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a TV to Player");
						return;
					}
					else if(item_select == 6){
						CREATE_OBJECT(0x1F925137,0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0xA8F6,0.0,0.0,0.7,0.0,0.0,0.0,false);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a Cone to Player");
						return;
					}
					else if(item_select == 7){
						CREATE_OBJECT(0x659BA938,0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0xA8F6,0.0,0.0,0.7,0.0,0.0,0.0,false);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a Tire to Player");
						return;
					}
					else if(item_select == 8){
						CREATE_OBJECT(0x90FA92C6,0.0,0.0,0.0,&otmp,true);
						ATTACH_OBJECT_TO_PED(otmp,pPlayer,0xA8F6,0.015,0.01,0.69,0.0,0.0,0.0,false);
						WAIT(10);
						MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
						print("Attached a Bowling Ball to Player");
						return;
					}
				}
				else if(last_selected[2] == 14){
					if(item_select == 1){
						REQUEST_ANIMS("move_player");
						while(!HAVE_ANIMS_LOADED("move_player")) WAIT(0);
						SET_ANIM_GROUP_FOR_CHAR(pPlayer, "move_player");
						print("Normal");
						return;
					}
					else if(item_select == 2){
						REQUEST_ANIMS("move_injured_upper");
						while(!HAVE_ANIMS_LOADED("move_injured_upper")) WAIT(0);
						SET_ANIM_GROUP_FOR_CHAR(pPlayer, "move_injured_upper");
						print("Injured");
						return;
					}
					else if(item_select == 3){
						REQUEST_ANIMS("move_gng@generic_a");
						while(!HAVE_ANIMS_LOADED("move_gng@generic_a")) WAIT(0);
						SET_ANIM_GROUP_FOR_CHAR(pPlayer, "move_gng@generic_a");
						print("Gangster");
						return;
					}
					else if(item_select == 4){
						REQUEST_ANIMS("move_m@fat");
						while(!HAVE_ANIMS_LOADED("move_m@fat")) WAIT(0);
						SET_ANIM_GROUP_FOR_CHAR(pPlayer, "move_m@fat");
						print("Fat");
						return;
					}
					else if(item_select == 5){
						REQUEST_ANIMS("move_m@cower");
						while(!HAVE_ANIMS_LOADED("move_m@cower")) WAIT(0);
						SET_ANIM_GROUP_FOR_CHAR(pPlayer, "move_m@cower");
						print("Coward");
						return;
					}
					else if(item_select == 6){
						REQUEST_ANIMS("move_f@sexy");
						while(!HAVE_ANIMS_LOADED("move_f@sexy")) WAIT(0);
						SET_ANIM_GROUP_FOR_CHAR(pPlayer, "move_f@sexy");
						print("Girl");
						return;
					}
					else if(item_select == 7){
						REQUEST_ANIMS("move_gng@generic_b");
						while(!HAVE_ANIMS_LOADED("move_gng@generic_b")) WAIT(0);
						SET_ANIM_GROUP_FOR_CHAR(pPlayer, "move_gng@generic_b");
						print("Gangster 2");
						return;
					}
				}
			}
			if(last_selected[1] == 12){
				if(last_selected[2] == 1){
					if(item_select == 1){
						delete_one_spawnguards();
						return;
					}
					else if(item_select == 2){
						delete_all_spawnguards();
						return;
					}
					else if(item_select == 3){
						GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
						tele_spawnguards(false,x,y,z);
						return;
					}
					else if(item_select == 5){
						kill_spawnguards();
						return;
					}
					else if(item_select == 7){
						disband_spawnguards();
						return;
					}
					else if(item_select == 8){
						clear_spawnguards();
						return;
					}
					else if(item_select == 9){
						tower_spawnguards(pPlayer);
					}
					else if(item_select == 10){
						dick_spawnguards();
					}
					else if(item_select == 11){
						GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
						tele_spawnguards(true,x,y,z);
						return;
					}
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					// Vehicle pveh;
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(IS_VEHICLE_EXTRA_TURNED_ON(pveh,item_select))
							TURN_OFF_VEHICLE_EXTRA(pveh,item_select,true);
						else
							TURN_OFF_VEHICLE_EXTRA(pveh,item_select,false);
							
						reset_menu();
						return;
					}
					print("You must be in a vehicle");
				}
				if(last_selected[2] == 3){
					// Vehicle pveh;
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(item_select == 1){
							GET_CAR_COLOURS(pveh,&color1,&color2);
							CHANGE_CAR_COLOUR(pveh,(menu[item_select].value - 1),color2);
							return;
						}
						if(item_select == 2){
							GET_CAR_COLOURS(pveh,&color1,&color2);
							CHANGE_CAR_COLOUR(pveh,color1,(menu[item_select].value - 1));
							return;
						}
						if(item_select == 3){
							GET_EXTRA_CAR_COLOURS(pveh,&color1,&color2);
							SET_EXTRA_CAR_COLOURS(pveh,(menu[item_select].value - 1),color2);
							return;
						}	
						if(item_select == 4){
							GET_EXTRA_CAR_COLOURS(pveh,&color1,&color2);
							SET_EXTRA_CAR_COLOURS(pveh,color1,(menu[item_select].value - 1));
							return;
						}						
					}
					print("You must be in a vehicle");
					return;
				}
				if(last_selected[2] == 4){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
						if(item_select == 1){
							if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
								print("You must be in a car");
								return;
							}
							Object lights;
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.4,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							SET_OBJECT_VISIBLE(lights, true);
							print("Added Blue Neons");
							return;
						}
						else if(item_select == 2){
							if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
								print("You must be in a car");
								return;
							}
							if(GET_CURRENT_EPISODE() != 2){
								print("~g~You must be on Tbogt");
								return;
							}
							Object lights;
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							print("Added Yellow Neons");
							return;
						}
						else if(item_select == 3){
							if(GET_CURRENT_EPISODE() != 2){
								print("~g~You must be on Tbogt");
								return;
							}
							if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
								print("You must be in a car");
								return;
							}
							Object lights;  
							CREATE_OBJECT(0xD611D7B6, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0,0.0999999,0.24,-0.36, 0,-1.56, 1.521);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0xD611D7B6, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0,0.0999999,0.24,-0.36, 0,-1.56, 1.521);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							print("Added Green Neons");
							return;
						}
						else if(item_select == 4){
							Object lights;
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							print("Added Red Neons");
							return;
						}
						else if(item_select == 5){
							if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
								print("You must be in a car");
								return;
							}
							GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
							Object lights;
							//blue
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.4,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							SET_OBJECT_VISIBLE(lights, true);
							//red
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							print("Added Pink Neons");
							return;
						}
						else if(item_select == 6){
							Object lights;
							if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
								print("You must be in a car");
								return;
							}
							GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,0.79,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,-0.79,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,-0.43,0,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.53,0,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,0.79,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,-0.79,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,-0.43,0,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
							WAIT(1);
							ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.53,0,-0.29,-1.55,0,0);
							SET_OBJECT_LIGHTS(lights, true);
							SET_OBJECT_VISIBLE(lights, true);
							SET_OBJECT_INVINCIBLE(lights, 1);
							FREEZE_OBJECT_POSITION(lights, true);
							print("Added Orange Neons");
							return;
						}
					}
				}
				if(last_selected[2] == 5){
					if(item_select == 1){
						if(GET_CURRENT_EPISODE() != 0){
							print("~g~You must be on Original");
							return;
						}
						spawn_car(MODEL_SANCHEZ);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(),&pveh);
						SET_CAR_VISIBLE(pveh,0);
						attachobjecttocar(pveh,0x1F3154CE,-0.0085,-0.0377,0.1170,0,0,1.5600);
						attachobjecttocar(pveh,0x1B11B700,-0.1500,0.5005,-0.1988,0,0,1.5797);
						attachobjecttocar(pveh,0x1B11B700,0.1102,0.5017,-0.2000,0,0,-1.5630);
						attachobjecttocar(pveh,0x1B11B700,-0.1370,-0.6510,-0.1318,0,0,1.5653);
						attachobjecttocar(pveh,0x1B11B700,0.1050,-0.6508,-0.1363,0,0,-1.5547);
						print("~g~BMX Sanchez by Big Fish 500, Buffeting and Despo");
						return;
					}
					if(item_select == 2){
						/**
						if(GET_CURRENT_EPISODE() != 0){
							print("~g~You must be on Original");
							return;
						}
						**/
						Vehicle car;
						spawn_car(MODEL_PHANTOM);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(),&car);
						SET_CAR_VISIBLE(car,0);
						attachobjecttocar(car,0x5BE14B23,-0.2623,2.0525,0.2407,0,0,0);
						attachobjecttocar(car,0x928B899D,-0.2630,3.6310,1.2702,4.6663,0,3.1468);
						attachobjecttocar(car,0xF40BE44B,0.7122,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-1.5710,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,0.9575,0.8092,-0.5478,0,1.5418,0);
						WAIT(10);
						attachobjecttocar(car,0xF40BE44B,-1.8090,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-1.5710,3.7305,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,0.7122,3.7305,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-1.8090,3.7305,-0.5478,0,1.5418,0);
						WAIT(10);
						attachobjecttocar(car,0xF40BE44B,0.9575,3.7305,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,1.2240,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xF40BE44B,-2.0780,0.8092,-0.5478,0,1.5418,0);
						attachobjecttocar(car,0xB76637D8,0.2417,2.0260,0.7427,3.1242,0,-1.5610);
						WAIT(10);
						attachobjecttocar(car,0xB76637D8,-0.8500,2.0260,0.7427,3.1242,0,-1.5610);
						attachobjecttocar(car,0xB76637D8,-0.2168,2.1908,1.7035,0,0,4.6952);
						attachobjecttocar(car,0x572BBD50,-0.2508,-0.3298,0.7502,0,0,0);
						WAIT(10);
						attachobjecttocar(car,0x455B19AF,-0.2635,4.4328,0.7648,0,0,3.1288);
						attachobjecttocar(car,0xF814AD1E,-1.7610,0.8108,-0.6930,0,1.5860,0);
						attachobjecttocar(car,0xF814AD1E,-1.7610,3.7425,-0.6930,0,1.5860,0);
						WAIT(10);
						attachobjecttocar(car,0x7F53DD7E,-0.2195,0.8285,-0.2305,0.7232,0,1.5207);
						attachobjecttocar(car,0x7F53DD7E,-0.2195,3.7613,-0.2305,0.7232,0,1.5207);
						attachobjecttocar(car,0x7F53DD7E,-0.3333,3.7613,-0.2305,0.7232,0,4.7585);
						attachobjecttocar(car,0x7F53DD7E,-0.3333,0.8285,-0.2305,0.7232,0,4.7585);
						WAIT(10);
						attachobjecttocar(car,0x1AE7947B,0.3250,0.5665,0.3285,1.5662,0,0);
						attachobjecttocar(car,0x1AE7947B,-0.2618,0.5665,0.3285,1.5662,0,0);
						attachobjecttocar(car,0x1AE7947B,-0.8925,0.5665,0.3285,1.5662,0,0);
						attachobjecttocar(car,0x3FF24020,1.1743,3.7443,-0.5195,0.0017,0,1.5385);
						WAIT(10);
						attachobjecttocar(car,0x3FF24020,-1.6692,3.7443,-0.5305,0.0393,0,4.7470);
						attachobjecttocar(car,0x3FF24020,1.4160,0.8272,-0.5305,0.0393,0,1.5385);
						attachobjecttocar(car,0x3FF24020,-1.9380,0.8272,-0.5305,0.0393,0,4.7470);
						attachobjecttocar(car,0x41303AF8,-0.2735,4.0410,1.2805,0,0,0);
						print("~g~Monster Truck by Boubouvirus");
						return;
					}
					if(item_select == 3){
						spawn_car(MODEL_PCJ);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(),&pveh);
						attachobjecttocar(pveh,0xD57CEB37,-0.15,-0.75,-0.15,0,0,4.7);
						attachobjecttocar(pveh,0xD57CEB37,0.15,-0.75,-0.15,0,0,1.6);
						print("~g~Big PCJ by Boubouvirus");
						return;
					}
					if(item_select == 4){
						spawn_car(MODEL_ANNIHILATOR);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &pveh);
						SET_CAR_VISIBLE(pveh,0);
						attachobjecttocar(pveh,0x05C1730B,0,-5.3110,-1.0627,0,0,3.1298);
						print("~g~Private Jet Heli");
						return;
					}
					if(item_select == 5){
						spawn_car(MODEL_SENTINEL);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &pveh);
						SET_CAR_VISIBLE(pveh,0);
						attachobjecttocar(pveh,0x7CD44988,-0.40,0,-0.35,0,0,1.5);
						print("~g~Wheelbarrow");
						return;
					}
					if(item_select == 6){
						spawn_car(MODEL_DINGHY);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &pveh);
						SET_CAR_VISIBLE(pveh,0);
						attachobjecttocar(pveh,0xDB0061B6,-0.3290,-0.2512,0.7510,0,0,1.5480);
						attachobjecttocar(pveh,0xF40BE44B,-0.3387,0.4967,0.0752,0,0,0);
						attachobjecttocar(pveh,0xF40BE44B,-0.3387,-0.9180,0.0752,0,0,0);
						attachobjecttocar(pveh,0x1AE7947B,-0.3282,-0.8560,0.7160,1.5680,0,0);
						print("~g~Rocket Boat");
						return;
					}
					if(item_select == 7){
						spawn_car(MODEL_PRIMO);
						WAIT(10);
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &pveh);
						SET_CAR_VISIBLE(pveh,0);
						attachobjecttocar(pveh,0x465F9ABE,-0.0205,-0.1660,0.2867,0,0,0);
						attachobjecttocar(pveh,0x3FF24020,0.9523,1.7792,-0.2047,0,0,1.5883);
						attachobjecttocar(pveh,0x3FF24020,-0.9535,1.7792,-0.2047,0,0,-1.5883);
						attachobjecttocar(pveh,0xD57CEB37,0.9057,-1.700,-0.1695,0,0,1.5360);
						attachobjecttocar(pveh,0xD57CEB37,-0.9830,-1.700,-0.1695,0,0,-1.5360);
						attachobjecttocar(pveh,0x928B899D,-0.2070,1.7878,0.4008,-1.5195,0.0315,3.1118);
						attachobjecttocar(pveh,0x928B899D,0.2070,1.7878,0.4008,-1.5195,0,3.1118);
						attachobjecttocar(pveh,0xEAD6E4A4,0.1788,-2.6883,-0.1218,0,0,0);
						attachobjecttocar(pveh,0xEAD6E4A4,-0.2802,-2.6883,-0.1218,0,0,0);
						attachobjecttocar(pveh,0xFE740BE2,0.01195,2.4590,-0.1002,0.0032,0,3.1188);
						attachobjecttocar(pveh,0x1AE7947B,-0.5722,-1.9208,0.2285,1.2820,0,-0.0080);
						attachobjecttocar(pveh,0x1AE7947B,-0.5722,-2.1500,-0.0170,0,0,0);
						attachobjecttocar(pveh,0x1AE7947B,0.4717,-1.9208,0.2285,1.2820,0,-0.0080);
						attachobjecttocar(pveh,0x1AE7947B,0.4717,-2.1500,-0.0170,0,0,0);
						attachobjecttocar(pveh,0x3859BAC0,-0.5262,0,1.1317,1.5890,0,-0.0073);
						attachobjecttocar(pveh,0x3859BAC0,0.4925,0,1.1317,1.5890,0,-0.0073);
						attachobjecttocar(pveh,0xB76637D8,-0.4395,2.1482,-0.3453,0,-0.1850,4.7690);
						attachobjecttocar(pveh,0xB76637D8,0.4395,2.1482,-0.3453,0,-0.1850,4.7690);
						attachobjecttocar(pveh,0x6A299B19,-0.7207,-3.0395,-0.0290,-0.3763,0,0);
						attachobjecttocar(pveh,0x6A299B19,0.5848,-3.0395,-0.0290,-0.3763,0,0);
						print("~g~Rusty Back to the Future Car");
						return;
					}
				}
				if(last_selected[2] == 13){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
						if(item_select == 1){
							for(i = 0;i <= 5;i++){
								if(IS_CAR_DOOR_FULLY_OPEN(pveh,i)) SHUT_CAR_DOOR(pveh,i);
								else OPEN_CAR_DOOR(pveh,i);
							}
							return;
						}
						if(item_select == 2){
							if(IS_CAR_DOOR_FULLY_OPEN(pveh,4)) SHUT_CAR_DOOR(pveh,4);
							else OPEN_CAR_DOOR(pveh,4);	
							return;
						}
						if(item_select == 3){
							if(IS_CAR_DOOR_FULLY_OPEN(pveh,5)) SHUT_CAR_DOOR(pveh,5);
							else OPEN_CAR_DOOR(pveh,5);	
							return;
						}
						if(item_select == 4){
							if(IS_CAR_DOOR_FULLY_OPEN(pveh,0)) SHUT_CAR_DOOR(pveh,0);
							else OPEN_CAR_DOOR(pveh,0);	
							return;
						}
						if(item_select == 5){
							if(IS_CAR_DOOR_FULLY_OPEN(pveh,1)) SHUT_CAR_DOOR(pveh,1);
							else OPEN_CAR_DOOR(pveh,1);	
							return;
						}
						if(item_select == 6){
							if(IS_CAR_DOOR_FULLY_OPEN(pveh,2)) SHUT_CAR_DOOR(pveh,2);
							else OPEN_CAR_DOOR(pveh,2);	
							return;
						}
						if(item_select == 7){
							if(IS_CAR_DOOR_FULLY_OPEN(pveh,3)) SHUT_CAR_DOOR(pveh,3);
							else OPEN_CAR_DOOR(pveh,3);	
							return;
						}
					}
				}
				if(last_selected[2] == 14){
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
						if(item_select == 1){
							do_toggle(veh_hazard);
							if(!veh_hazard) SET_VEH_HAZARDLIGHTS(pveh,false);
							else SET_VEH_HAZARDLIGHTS(pveh,true);
							return;
						}
						if(item_select == 2){
							do_toggle(veh_indic);
							if(!veh_indic) SET_VEH_INDICATORLIGHTS(pveh,false);
							else SET_VEH_INDICATORLIGHTS(pveh,true);
							return;
						}
					}
				}
				if(last_selected[2] == 15){
					if(item_select == 1){
						spawn_car_in_line(pPlayer, MODEL_INFERNUS);
							print("Spawned Infernus's");
						return;
					}
					else if(item_select == 2){
						spawn_car_in_line(pPlayer, MODEL_SULTANRS);
						print("Spawned Sultan RS's");
						return;
					}
					else if(item_select == 3){
						spawn_car_in_line(pPlayer, MODEL_BANSHEE);
						print("Spawned Banshees");
						return;
					}
					else if(item_select == 4){
						spawn_car_in_line(pPlayer, MODEL_COMET);
						print("Spawned Comets");
						return;
					}
					else if(item_select == 5){
						spawn_car_in_line(pPlayer, MODEL_DINGHY);
						print("Spawned Dinghy Boats");
						return;
					}
					else if(item_select == 6){
						spawn_car_in_line(pPlayer, MODEL_ANNIHILATOR);
						print("Spawned Annihilators");
						return;
					}
					else if(item_select == 7){
						if(!GET_CURRENT_EPISODE() == 2){
							print("You must be on ~r~TBOGT");
							return;
						}
						spawn_car_in_line(pPlayer, MODEL_BULLET);
						print("Spawned Bullet GTs");
						return;
					}
					else if(item_select == 8){
						if(!GET_CURRENT_EPISODE() == 2){
							print("You must be on ~r~TBOGT");
							return;
						}
						spawn_car_in_line(pPlayer, MODEL_APC);
						print("Spawned APC Tanks");
							return;
					}
					else if(item_select == 9){
						if(!GET_CURRENT_EPISODE() == 2){
							print("You must be on ~r~TBOGT");
							return;
						}
						spawn_car_in_line(pPlayer, MODEL_BUZZARD);
						print("Spawned Buzzards");
						return;
					}				
				}
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2 && GET_CURRENT_EPISODE() == 2){
					if(item_select == 1){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_9,AMMO_MAX,false);
						print("You have been given a .44 Pistol.");
						return;
					}
					if(item_select == 2){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_10,AMMO_MAX,false);
						print("You have been given an Explosive AA12.");
						return;
					}
					if(item_select == 3){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_11,AMMO_MAX,false);
						print("You have been given an AA12.");
						return;
					}
					if(item_select == 4){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_12,AMMO_MAX,false);
						print("You have been given a P-90.");
						return;
					}
					if(item_select == 5){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_13,AMMO_MAX,false);
						print("You have been given a Golden Uzi.");
						return;
					}
					if(item_select == 6){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_14,AMMO_MAX,false);
						print("You have been given an M249.");
						return;
					}
					if(item_select == 7){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_15,AMMO_MAX,false);
						print("You have been given an Explosive Sniper.");
						return;
					}
					if(item_select == 8){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_1,AMMO_MAX,false);
						print("You have been given a Grenade Launcher.");
						return;
					}
					if(item_select == 9){
						GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_EPISODIC_16,AMMO_MAX,false);
						print("You have been given some Sticky Bombs.");
						return;
					}					
				}
			}
		}
		if(last_selected[0] == 5){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					if(item_select == 1){
						s_r = 160;
						s_g = 32;
						s_b = 240;
						return;
					}
					if(item_select == 2){
						s_r = 255;
						s_g = 0;
						s_b = 0;
						return;
					}
					if(item_select == 3){
						s_r = 0;
						s_g = 191;
						s_b = 255;
						return;
					}
					if(item_select == 4){
						s_r = 0;
						s_g = 255;
						s_b = 0;
						return;
					}
					if(item_select == 5){
						s_r = 255;
						s_g = 0;
						s_b = 255;
						return;
					}
					if(item_select == 6){
						s_r = 218;
						s_g = 165;
						s_b = 32;
						return;
					}
					if(item_select == 7){
						s_r = 105;
						s_g = 105;
						s_b = 105;
						return;
					}
					if(item_select == 8){
						s_r = 0;
						s_g = 0;
						s_b = 255;
						return;
					}
					if(item_select == 9){
						do_toggle(rainbowmenu);
						return;
					}
				}
			}
		}
	}
	if(menu_level == 4){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				if(last_selected[2] > 2){
					if(last_selected[3] == 1){
						uint index = (last_selected[2] - 3);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(menu[item_select].value == 1){
									REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
									WAIT(10);
									GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_UNARMED, AMMO_MAX, false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_POOLCUE,1,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_DEAGLE,AMMO_MAX,false);
									if(GET_CURRENT_EPISODE() != 2) GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_GRENADE,AMMO_MAX,false);
									else GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_16,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MP5,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_BARETTA,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SNIPERRIFLE,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M4,AMMO_MAX,false);
									
								}
								else if(menu[item_select].value == 2){
									REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
									WAIT(10);
									GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_UNARMED, AMMO_MAX, false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_PISTOL,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MOLOTOV,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_RLAUNCHER,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_MICRO_UZI,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_AK47,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_SHOTGUN,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_M40A1,AMMO_MAX,false);
									GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_POOLCUE,1,false);					
								}
								else if(menu[item_select].value == 3){
									uint episode = GET_CURRENT_EPISODE();
									if(episode == 2){
										REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
										WAIT(10);
										GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_UNARMED, AMMO_MAX, false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_9,AMMO_MAX,false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_10,AMMO_MAX,false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_13,AMMO_MAX,false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_14,AMMO_MAX,false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_15,AMMO_MAX,false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_1,AMMO_MAX,false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_EPISODIC_16,AMMO_MAX,false);
										GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_POOLCUE,1,false);
									}
									else{
										print("You must be on The Ballad of Gay Tony to use this option");
										return;
									}
								}
								GIVE_WEAPON_TO_CHAR(players[index].ped,WEAPON_ARMOUR,1,false);
								ADD_ARMOUR_TO_CHAR(players[index].ped,99);
								print("Player is now armed & dangerous!");
								return;
							}
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
								print("Player is now unarmed!");
								return;
							}
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_RLAUNCHER);
								return;
							}
						}
						else if(item_select == 4){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_POOLCUE);
								return;
							}
						}
						else if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_M4);
								return;
							}
						}
						else if(item_select == 6){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_DEAGLE);
								return;
							}
						}
						else if(item_select == 7){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_BASEBALLBAT);
								return;
							}
						}
						else if(item_select == 8){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_GRENADE);
								return;
							}
						}
						else if(item_select == 9){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_AK47);
								return;
							}
						}
						else if(item_select == 10){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_SHOTGUN);
								return;
							}
						}
						else if(item_select == 11){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_SNIPERRIFLE);
								return;
							}
						}
						else if(item_select == 12){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_MP5);
								return;
							}
						}
						else if(item_select == 13){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_MOLOTOV);
								return;
							}
						}
						else if(item_select == 14){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_EPISODIC_10);
								return;
							}
						}
						else if(item_select == 15){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_EPISODIC_12);
								return;
							}
						}
						else if(item_select == 16){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_EPISODIC_13);
								return;
							}
						}
						else if(item_select == 17){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_EPISODIC_14);
								return;
							}
						}
						else if(item_select == 18){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_EPISODIC_15);
								return;
							}
						}
						else if(item_select == 19){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								UpdateWeaponOfPed(players[index].ped, WEAPON_EPISODIC_16);
								return;
							}
						}
					}
					if(last_selected[3] == 3){
						uint index = (last_selected[2] - 3);
						if(DOES_CHAR_EXIST(players[index].ped)){
							if(item_select == 1){
								tmp = players[index].id;
								do_toggle(players[tmp].mprotection);
								return;
							}
							else if(item_select == 2){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								tmp = players[index].id;
								do_toggle(players[tmp].force);
								return;
							}
							else if(item_select == 3){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								tmp = players[index].id;
								do_toggle(players[tmp].rage);
								return;
							}
							else if(item_select == 4){
								tmp = players[index].id;
								do_toggle(players[tmp].water);
								return;
							}
							else if(item_select == 5){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								tmp = players[index].id;
								do_toggle(players[tmp].disarm);
								return;
							}
							else if(item_select == 6){
								spectatePed = players[index].ped;
								view_player(spectatePed);
								if(view_online_player) delete_view_player();
								do_toggle(view_online_player);
								return;
							}
							else if(item_select == 7){
								tmp = players[index].id;
								do_toggle(players[tmp].rocket);
								if(!players[tmp].rocket) for(i = 0;i <= 1;i++) if(DOES_CHAR_EXIST(rocketped[i])) DELETE_CHAR(&rocketped[i]);
								else{
									GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_DEAGLE, AMMO_MAX, 0);
									SET_CURRENT_CHAR_WEAPON(players[index].ped, WEAPON_DEAGLE, true);
								}
								return;
							}
							else if(item_select == 8){
								tmp = players[index].id;
								do_toggle(players[tmp].cargun);
								if(players[tmp].cargun){
									GIVE_WEAPON_TO_CHAR(players[index].ped, WEAPON_PISTOL, AMMO_MAX, 0);
									SET_CURRENT_CHAR_WEAPON(players[index].ped, WEAPON_PISTOL, true);
								}
								return;
							}
						}
					}
					if(last_selected[3] == 4){
						uint index = (last_selected[2] - 3);
							if(item_select == 1){
								 if(DOES_CHAR_EXIST(players[index].ped)){
									//// float x,y,z;
									GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
									teleport_char(pPlayer,x,y,z);
									print("Teleported to player");
									return;
								}
							}
							else if(item_select == 2){
								if(DOES_CHAR_EXIST(players[index].ped)){
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										// Vehicle pveh;
										Ped tmp;
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_DRIVER_OF_CAR(pveh, &driver);
										if(!DOES_CHAR_EXIST(driver)){
											WARP_CHAR_INTO_CAR(pPlayer,pveh);
											print("Teleported to player's car");
											return;
										}
										for(i = 0;i <= 2;i++){
											if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)){
												WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,pveh,i);
												print("Teleported to player's car");
												return;
											}
										}
									}
									else print("Player ain't in no vehicle!");
									return;
								}
							}
							else if(item_select == 3){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										//// float x,y,z;
										GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
										if(!IS_CHAR_IN_ANY_CAR(pPlayer)) FREEZE_CHAR_POSITION(pPlayer,true);
										else{
											GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
											FREEZE_CAR_POSITION(pveh,true);
										}
										teleport_net_char(players[index].ped,x,y,z);
										WAIT(1000);
										if(!IS_CHAR_IN_ANY_CAR(pPlayer)) FREEZE_CHAR_POSITION(pPlayer,false);
										else{
											GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
											FREEZE_CAR_POSITION(pveh,false);
										}
										return;
									}
									else print("Player ain't in no vehicle!");
									return;
								}
							}
							else if(item_select == 4){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										// // float x,y,z;
										if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
											GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&spawn);
											GET_GROUND_Z_FOR_3D_COORD(spawn.x,spawn.y,1000,&z);
											teleport_net_char(players[index].ped,spawn.x,spawn.y,z + 5);
											print("Player teleported to waypoint");
											return;
										}
										else{
										print("You need to set a waypoint!");
										return;
										}
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 5){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										REMOVE_ALL_CHAR_WEAPONS(players[index].ped);
										teleport_net_char(players[index].ped,-1079.8,-469.7,2.62);
										WAIT(500);
										DELETE_CAR(&pveh);
										MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
										return;
									}
									else print("Player ain't in no vehicle!");
									return;
								}						
							}
							else if(item_select == 6){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										teleport_net_char(players[index].ped,2175.3516,761.2235,30.0);
										print("Player teleported to Airport");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 7){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										teleport_net_char(players[index].ped,-415.17,1463.54,39.0);
										print("Player teleported to Playboy X's house");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 8){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										teleport_net_char(players[index].ped,5000.0,5000.0,5000.0);
										print("Player teleported to the KillZone");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 9){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										teleport_net_char(players[index].ped,2861.228, 1810.172, 998.11);
										print("Player teleported to the Water");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 10){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										teleport_net_char(players[index].ped,-387.44270000, 1492.48800000, 9.71030100);
										print("Player teleported to the Fight Cage");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 11){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
										GET_CAR_CHAR_IS_USING(players[index].ped, &pveh);
										z += 2000.0;
										teleport_net_char(players[index].ped,x,y,z);
										WAIT(1000);
										DELETE_CAR(&pveh);
										MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
										print("Player sent Skydiving");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							else if(item_select == 12){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GENERATE_RANDOM_FLOAT_IN_RANGE(-5000,5000,&x);
										GENERATE_RANDOM_FLOAT_IN_RANGE(-4000,4000,&y);
										GENERATE_RANDOM_FLOAT_IN_RANGE(0,2000,&z);
										teleport_net_char(players[index].ped,x,y,z);
										print("Player sent to a random location");
										return;
									}
									else{
										print("Player ain't in no vehicle!");
										return;
									}
								}
							}
							return;
					}
					else if(last_selected[3] == 5){
						uint index = (last_selected[2] - 3);
						if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									SET_CAR_PROOFS(pveh, true, true, true, true, true);
									SET_CAR_CAN_BE_DAMAGED(pveh,false);
									SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
									SET_CAN_BURST_CAR_TYRES(pveh,false);
									print("Made player's car Invincible");
								}
							}
							return;
						}
						else if(item_select == 4){
							#ifndef EMMAN
							if(is_whitelisted(index)){
								print("Player is whitelisted");
								return;
							}
							#endif
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								uint lock;
								tick = 0;
								// Vehicle pveh;
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 200){
										print("~r~Error");
										return;
									}
									WAIT(0);
								}
								GET_CAR_DOOR_LOCK_STATUS(pveh,&lock);
								if(lock == VEHICLE_DOOR_UNLOCKED){
									LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_LOCKED_BOTH_SIDES);
									print("Doors locked!");
								}
								else{
									LOCK_CAR_DOORS(pveh,VEHICLE_DOOR_UNLOCKED);
									print("Doors unlocked!");
								}
							}
							return;
						}
						if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									tick = 0;
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									GET_CAR_COORDINATES(pveh, &x, &y, &z);
									GET_CAR_HEADING(pveh, &heading);
									if(heading > 180.0) heading -= 180.0;
									else heading += 180.0;
									SET_VEHICLE_QUATERNION(pveh, 0, 0, 0, 0);
									SET_CAR_COORDINATES(pveh, x, y, z);
									SET_CAR_HEADING(pveh, heading);
									print("Flipped Player's Vehicle");
								}
							}
							return;
						}
						if(item_select == 6){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									tick = 0;
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									GET_CAR_HEADING(pveh, &heading);
									GET_CAR_SPEED(pveh,&speed);
									if(heading > 180.0) heading -= 180.0;
									else heading += 180.0;
									SET_CAR_HEADING(pveh, heading);
									SET_CAR_FORWARD_SPEED(pveh,speed);
									print("Flipped Player's Vehicle Around");
								}
							}
							return;
						}
					}
					else if(last_selected[3] == 6){
						uint index = (last_selected[2] - 3);
						if(item_select == 1){
							if(GET_PLAYER_ID() != GET_HOST_ID()){
								print("~r~You Are Not Host");
								return;
							}
							if(NETWORK_IS_GAME_RANKED()){
								i = (GET_CHAR_MONEY(players[index].ped) + 50000);
								SET_CHAR_MONEY(players[index].ped, i);
								print("Gave Player Money");
							}
							else print("The Game You Are In is Not Ranked");
							return;
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
									}
								#endif
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											break;
										}
										WAIT(0);
									}
									SET_CAR_CAN_BE_DAMAGED(pveh,true);
									SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
									SET_CAN_BURST_CAR_TYRES(pveh,true);
								}
								print("Whiskey Tango, this is Rubber Ducky comin' in hot!");
								// // float x,y,z;
								GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
								create_big_explosion(x,y,z);						
							}
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
									}
								#endif
								if(GET_HOST_ID() != GET_PLAYER_ID()){
									if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
										// float x,y,z;
									//	GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
										GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(players[index].ped, 0, 1, 0, &x, &y, &z);
										ADD_EXPLOSION(x,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x,y - 1,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x + 1.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x,y + 1.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x,y + 2.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x,y + 3.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x - 1.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x,y - 1.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x + 0.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x,y + 0.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x - 0.5,y,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										ADD_EXPLOSION(x,y - 0.5,z,EXPLOSION_DIR_WATER_HYDRANT,20.5,false,true,0.0);
										print("Tazed player!");
									}
									else print("Player must be on foot");
								}
								else print("You can't be host");
							}
						}
						else if(item_select == 4){
							#ifndef EMMAN
							if(is_whitelisted(index)){
								print("Player is whitelisted");
								return;
							}
							#endif
							if(DOES_CHAR_EXIST(players[index].ped)){
								if(GET_PLAYER_ID() == GET_HOST_ID())
									NETWORK_KICK_PLAYER(players[index].id,true);
								else
									print("You are not host");
								return;
							}
						}
						else if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								START_CHAR_FIRE(players[index].ped);
								WAIT(10);
								print("Player was set on Fire.");
							}
						return;
						}
						else if(item_select == 6){
							#ifndef EMMAN
							if(is_whitelisted(index)){
								print("Player is whitelisted");
								return;
							}
							#endif
							if((DOES_CHAR_EXIST(players[index].ped)) && (IS_CHAR_IN_ANY_CAR(pPlayer))){
								GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
								GET_CHAR_COORDINATES(players[index].ped,&mx,&my,&mz);
								GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
								if((dist >= 10) && (DOES_GROUP_EXIST(Bgroup))){
									print_long("Victim to far away");
									group_loop = false;
									return;
								}
								GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
								GET_DRIVER_OF_CAR(pveh,&driver);
								if(pPlayer == driver){
									GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
									if(!DOES_GROUP_EXIST(Bgroup)){
										CREATE_GROUP(0, Bgroup, true);
										SET_GROUP_LEADER(Bgroup, pPlayer);
									}
									SET_GROUP_MEMBER(Bgroup,players[index].ped);
									SET_GROUP_FORMATION(Bgroup, 2);
								//	SET_GROUP_SEPARATION_RANGE(Bgroup, 9999);
									group_onlineped = players[index].ped;
									group_loop = true;
									print("~r~Forcing player into car");
									return;
								}
								else print("You must be driver");
							}
							else print("You must be in a car");
							return;
						}
						else if(item_select == 8){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
								ATTACH_OBJECT_TO_PED_PHYSICALLY(otmp,players[index].ped,false,0,0.0,0.0,-0.11,0.0,0.0,3.0,false,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Glitched Player");
							}
							return;
						}
					}
					if(last_selected[3] == 7){
						uint index = (last_selected[2] - 3);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0,0.0,0.0,-0.11,0.0,0.0,3.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Hippo to Player");
							}
							return;
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								cubes[0] = 0x2718C626; //Red
								cubes[1] = 0xDD28B247; //Blue
								cubes[2] = 0xCCEA11CA; //Yellow
								cubes[3] = 0xBB1F6E71; //Green 
								cubes[4] = 0xA6E545FD; //Purple
								cubes[5] = 0x5C5030D4; //Orange

								GENERATE_RANDOM_INT_IN_RANGE(0,5,&i);

								CREATE_OBJECT(cubes[i],0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0x4B5,0.0,0.0,0.0,0.0,0.0,3.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Cube to Player");
							}
							return;
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0xB570F614,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0,0,.25,-.50,-1.55,3.10,0,0);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Dick to Player");
							}
							return;
						}
						else if(item_select == 4){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0xEB12D336,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0,0,0,0.0,0.0,0.0,3.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Dumpster to Player");
							}
							return;
						}
						else if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0xD318157E,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0x4B5,0.0,0.0,-0.3,0.0,0.0,3.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a TV to Player");
							}
							return;
						}
						else if(item_select == 6){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0x69305DBB,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								SET_OBJECT_COLLISION(otmp, 1);
								SET_OBJECT_INVINCIBLE(otmp, 1);
								ATTACH_OBJECT_TO_PED(otmp, players[index].ped, 0, 0, 0, 0, 0, 0, 0, 0);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Troll Box to Player");
							}
							return;
						}
						else if(item_select == 7){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0xEE6024BC,0.0,0.0,0.0,&otmp,true);
								ATTACH_OBJECT_TO_PED(otmp, players[index].ped, 0, 0, 0, 0, 0, 0, 0, 0);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Sultan to Player");
							}
							return;
						}
						else if(item_select == 8){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0x1F925137,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0xA8F6,0.0,0.0,0.7,0.0,0.0,0.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Cone to Player");
							}
							return;
						}
						else if(item_select == 9){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0x659BA938,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0xA8F6,0.0,0.0,0.7,0.0,0.0,0.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Tire to Player");
							}
							return;
						}
						else if(item_select == 10){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(0x90FA92C6,0.0,0.0,0.0,&otmp,true);
								#ifdef EMMAN
								GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10){
										break;
									}
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								#endif
								ATTACH_OBJECT_TO_PED(otmp,players[index].ped,0xA8F6,0.015,0.01,0.69,0.0,0.0,0.0,false);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Bowling Ball to Player");
							}
							return;
						}
						else if(item_select == 11){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								REQUEST_MODEL(MODEL_BUS);    
								while(!HAS_MODEL_LOADED(MODEL_BUS)) WAIT(0);
								CREATE_OBJECT(MODEL_BUS,0.0,0.0,0.0,&otmp,true);
								while(!DOES_OBJECT_EXIST(otmp)) WAIT(0);
								ATTACH_OBJECT_TO_PED(otmp, players[index].ped, 0, 0, 0, 0, 0, 0, 0, 0);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Bus to Player");
							}
							return;
						}
						else if(item_select == 12){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								REQUEST_MODEL(MODEL_MRTASTY);    
								while(!HAS_MODEL_LOADED(MODEL_MRTASTY)) WAIT(0);
								CREATE_OBJECT(MODEL_MRTASTY,0.0,0.0,0.0,&otmp,true);
								while(!DOES_OBJECT_EXIST(otmp)) WAIT(0);
								ATTACH_OBJECT_TO_PED(otmp, players[index].ped, 0, 0, 0, 0, 0, 0, 0, 0);
								WAIT(10);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
								print("Attached a Ice cream truck to Player");
							}
							return;
						}
					}
					if(last_selected[3] == 8){
						uint index = (last_selected[2] - 3);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
								int test, guards;
								GET_GROUP_SIZE(Bgroup, &test, &guards);	
								if((guards <= 0) || (!DOES_GROUP_EXIST(Bgroup))){
									print("No guards Exist or Available");
									return;
								}
								if(DOES_GROUP_EXIST(Bgroup)){
									for(i = 0;i <= 6; i++){
										if(DOES_CHAR_EXIST(gameped[i]) && DOES_CHAR_EXIST(players[index].ped)){
											GET_NETWORK_ID_FROM_PED(gameped[i], &nvid);
											SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											tick = 0;
											while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
												tick++;
												REQUEST_CONTROL_OF_NETWORK_ID(nvid);
												if(tick >= 200){
													continue;
												}
												WAIT(0);
											}
											TASK_COMBAT(gameped[i], players[index].ped);
										}
									}
								}
							}
							print("Sent all Guards after the Player");
							return;
						}
						if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								tower_spawnguards(players[index].ped);
								print("Bodyguard tower!");
							}
							return;
						}
						if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
								tele_spawnguards(false,x,y,z);
							}
							return;
						}
					}
					if(last_selected[3] == 10){
						uint index = (last_selected[2] - 3);
						if(item_select == 1){
							print("~b~Mods below only work on users running XMC 4.0 or higher. (you must be in there menu)");
							return;
						}
						if(item_select == 2){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK4);
							print("~g~Sent a Greeting.");
							return;
						}
						else if(item_select == 3){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK3);
							print("~g~Sent a Warning.");
							return;
						}
						else if(item_select == 4){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK);
							print("~g~Sent a Menu Disable.");
							return;
						}
						else if(item_select == 5){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK2);
							print("~g~Sent an Instant Freeze.");
							return;
						}
						else if(item_select == 6){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK5);
							print("~g~Sent a troll message.");
							return;
						}
						else if(item_select == 7){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK6);
							print("~g~Sent a menu feature disable.");
							return;
						}
						else if(item_select == 8){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK7);
							print("~g~Sent a teleport to you.");
							return;
						}
						else if(item_select == 9){
							print("~b~Mods below only work on users running XMC 5.0 or higher.");
							return;
						}
						else if(item_select == 10){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK8);
							print("~g~Sent a Boot to SinglePlayer.");
							return;
						}
						else if(item_select == 11){
							admin_net_char(players[index].ped, MODEL_CJ_PROC_BRICK9);
							print("~g~Sent a disable Modscript SCO.");
							return;
						}
					}
					if(last_selected[3] == 11){
						uint index = (last_selected[2] - 3);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									// Vehicle pveh;
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									ATTACH_PED_TO_CAR(pPlayer,pveh,0,0.00,0.00,2.0,0.00,0.00,1,1);
									print("Attached You attached to Player's Vehicle");
								}
								else print("Player needs to be in a vehicle");
							}
							return;
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&admin_obj,true);
								SET_OBJECT_VISIBLE(admin_obj, false);
								ATTACH_OBJECT_TO_PED(admin_obj,players[index].ped,0,0.0,0.0,2.1,0.0,0.0,0.0,false);
								WAIT(10);
								ATTACH_PED_TO_OBJECT(pPlayer,admin_obj,0,0.0,0.0,-0.65,0,0,0,0);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&admin_obj);
								print("Attached You to Player's head");
							}
							return;
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								if(IS_CHAR_IN_ANY_CAR(pPlayer) && !IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
									CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&admin_obj,true);
									SET_OBJECT_VISIBLE(admin_obj, false);
									ATTACH_OBJECT_TO_PED(admin_obj,players[index].ped,0,0.0,0.0,2.1,0.0,0.0,0.0,false);
									WAIT(10);
									ATTACH_CAR_TO_OBJECT(pveh,admin_obj,0.0,0.0,0.0,-0.7,0.0,0.0,0.0);
									print("Attached Your car to Player's head");
									return;
								}
								else print("You must be in a vehicle");
							}
							return;
						}
						else if(item_select == 4){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_DRIVER_OF_CAR(pveh,&driver);
									if(driver == pPlayer){
										print("~r~They must be the driver of there own car.");
									}
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 200){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
									if(!IS_CAR_ATTACHED(pveh)){
										CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&admin_obj,true);
										SET_OBJECT_VISIBLE(admin_obj, false);
										ATTACH_OBJECT_TO_PED(admin_obj,pPlayer,0,0.0,0.0,2.1,0.0,0.0,0.0,false);
										FREEZE_CAR_POSITION(pveh,true);
										WAIT(10);
										ATTACH_CAR_TO_OBJECT(pveh,admin_obj,0.0,0.0,0.0,-0.7,0.0,0.0,0.0);
										LOCK_CAR_DOORS(pveh,4);
										print("Attached Player's car to your head");
										return;
									}
									else if(IS_CAR_ATTACHED(pveh)){
										LOCK_CAR_DOORS(pveh,1);
										FREEZE_CAR_POSITION(pveh,false);
										DETACH_CAR(pveh);
										SET_NETWORK_ID_CAN_MIGRATE(nvid,true);
										print("Detached Player's car from your head");
										return;
									}
								}
								else print("Player must be in a vehicle");
							}
							return;
						}
						else if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								GET_CHAR_COORDINATES(players[index].ped, &x, &y, &z);
								z += 1.0;
								CREATE_RANDOM_CHAR(x,y,z, &online_char);
								GET_NETWORK_ID_FROM_PED(online_char,&nvid);
								REQUEST_CONTROL_OF_NETWORK_ID(nvid);
								tick = 0;
								while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
									tick++;
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									if(tick >= 10) break;
									WAIT(0);
								}
								SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
								SET_CHAR_INVINCIBLE(online_char, true);
								SET_CHAR_VISIBLE(online_char, true);
								FREEZE_CHAR_POSITION(online_char, true);
								CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&admin_obj,true);
								SET_OBJECT_VISIBLE(admin_obj, false);
								ATTACH_OBJECT_TO_PED(admin_obj,players[index].ped,0,0.0,0.0,2.1,0.0,0.0,0.0,false);
								WAIT(10);
								ATTACH_PED_TO_OBJECT(online_char,admin_obj,0,0.0,0.0,-0.65,0,0,0,0);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&admin_obj);
								WAIT(200);
								REQUEST_ANIMS("amb@dance_femidl_b");
								while(!HAVE_ANIMS_LOADED("amb@dance_femidl_b")) WAIT(0);
								TASK_PLAY_ANIM_WITH_FLAGS(online_char,"loop_b","amb@dance_femidl_b",8.0,99999,1);
								print("Attached a ped to player's head");
							}
							return;
						}
					}
					if(last_selected[3] == 12){
						uint index = (last_selected[2] - 3);
						if(item_select == 1){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_BUS);
							}
							return;
						}
						else if(item_select == 2){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_INFERNUS);
							}
							return;
						}
						else if(item_select == 3){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_BANSHEE);
							}
							return;
						}
						else if(item_select == 4){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_DINGHY);
							}
							return;
						}
						else if(item_select == 5){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_CAVALCADE);
							}
							return;
						}
						else if(item_select == 6){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_AMBULANCE);
							}
							return;
						}
						else if(item_select == 7){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_TRASH);
							}
							return;
						}
						else if(item_select == 8){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_VIGERO);
							}
							return;
						}
						else if(item_select == 9){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_PHANTOM);
							}
							return;
						}
						else if(item_select == 10){
							if(DOES_CHAR_EXIST(players[index].ped)){
								#ifndef EMMAN
								if(is_whitelisted(index)){
									print("Player is whitelisted");
									return;
								}
								#endif
								ram_car(players[index].ped, MODEL_MRTASTY);
							}
							return;
						}
					}
				}
			}
			if(last_selected[1] == 12){
				if(last_selected[2] == 1){
					if(last_selected[3] == 4){
						if(item_select == 1){
							arm_spawnguards(WEAPON_RLAUNCHER);
							return;
						}
						else if(item_select == 2){
							arm_spawnguards(WEAPON_POOLCUE);
							return;
						}
						else if(item_select == 3){
							arm_spawnguards(WEAPON_M4);
							return;
						}
						else if(item_select == 4){
							arm_spawnguards(WEAPON_DEAGLE);
							return;
						}
						else if(item_select == 5){
							arm_spawnguards(WEAPON_BASEBALLBAT);
							return;
						}
						else if(item_select == 6){
							arm_spawnguards(WEAPON_KNIFE);
							return;
						}
						else if(item_select == 7){
							arm_spawnguards(WEAPON_AK47);
							return;
						}
						else if(item_select == 8){
							arm_spawnguards(WEAPON_SHOTGUN);
							return;
						}
						else if(item_select == 9){
							arm_spawnguards(WEAPON_SNIPERRIFLE);
							return;
						}
						else if(item_select == 10){
							arm_spawnguards(WEAPON_MP5);
							return;
						}
						else if(item_select == 11){
							arm_spawnguards(WEAPON_MOLOTOV);
							return;
						}
					}
					if(last_selected[3] == 6){
						if(item_select == 1){
							if(menu[item_select].value == 1){
								anim_spawnguards("taichi01","amb@park_taichi_a",false);
								return;
							}
							if(menu[item_select].value == 2){
								anim_spawnguards("taichi02","amb@park_taichi_b",false);
								return;
							}					
						}
						if(item_select == 2){
							if(menu[item_select].value == 1){
								anim_spawnguards("loop_a","amb@dance_maleidl_a",false);
								return;
							}
							if(menu[item_select].value == 2){
								anim_spawnguards("loop_b","amb@dance_maleidl_b",false);
								return;
							}
							if(menu[item_select].value == 3){
								anim_spawnguards("loop_c","amb@dance_maleidl_c",false);
								return;
							}
							if(menu[item_select].value == 4){
								anim_spawnguards("loop_d","amb@dance_maleidl_d",false);
								return;
							}
						}
						if(item_select == 3){
							if(menu[item_select].value == 1){
								anim_spawnguards("loop_a","amb@dance_femidl_a",false);
								return;
							}
							if(menu[item_select].value == 2){
								anim_spawnguards("loop_b","amb@dance_femidl_b",false);
								return;
							}
							if(menu[item_select].value == 3){
								anim_spawnguards("loop_c","amb@dance_femidl_c",false);
								return;
							}					
						}
						if(item_select == 4){
							anim_spawnguards("pole_dance_a","missstripclublo",false);
							return;
						}
						if(item_select == 5){
							anim_spawnguards("idle_2_hands_up","busted",true);
							return;
						}
					}
					if(last_selected[3] == 12){
						if(item_select == 1){
							anim_group_spawnguards("move_player");
							print("Normal");
							return;
						}
						else if(item_select == 2){
							anim_group_spawnguards("move_injured_upper");
							print("Injured");
							return;
						}
						else if(item_select == 3){
							anim_group_spawnguards("move_gng@generic_a");
							print("Gangster");
							return;
						}
						else if(item_select == 4){
							anim_group_spawnguards("move_m@fat");
							print("Fat");
							return;
						}
						else if(item_select == 5){
							anim_group_spawnguards("move_m@cower");
							print("Coward");
							return;
						}
						else if(item_select == 6){
							anim_group_spawnguards("move_f@sexy");
							print("Girl");
							return;
						}
						else if(item_select == 7){
							anim_group_spawnguards("move_gng@generic_b");
							print("Gangster 2");
							return;
						}
					}
				}
			}
			
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					spawn_car(menu[item_select].value);
					return;
				}
			}
		}
	}
	if(menu_level == 5){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					if(last_selected[3] == 5){
						for(i = 0;i <= 6;i++){
							if(!DOES_CHAR_EXIST(shortcut_players[i])) continue;
							spawn_car_for_char(shortcut_players[i],menu[item_select].value);
						}
						print(GET_STRING_FROM_TEXT_FILE(GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(menu[item_select].value)));
					}
				}
				if(last_selected[2] > 2){
					if(last_selected[3] == 5){
						if(last_selected[4] == 1){
							uint index = (last_selected[2] - 3);
							if(item_select == 1){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										CHANGE_CAR_COLOUR(pveh, 124, 124);
										SET_EXTRA_CAR_COLOURS(pveh, 133, 133);
										SET_CAR_COLLISION(pveh, false);
										WAIT(100);
										APPLY_FORCE_TO_CAR(pveh,true,500.0,4000.0,200.0,0.0,0.0,0.0,true,true,true,true);
										SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
										print("Trolled Player's vehicle");
									}
									else print("Player not in vehicle");
								}
								return;
							}
							else if(item_select == 2){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										DELETE_CAR(&pveh);
										MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
										print("Deleted Player's vehicle");
									}
									else print("Player not in vehicle");
								}
								return;
							}
							else if(item_select == 3){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										APPLY_FORCE_TO_CAR(pveh,true,0.0,0.0,1000.0,0.0,0.0,0.0,true,true,true,true);
										print("Slingshoted Player's vehicle");
									}
									else print("Player not in vehicle");
								}
								return;
							}
							else if(item_select == 4){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
									//	FREEZE_CAR_POSITION(pveh,true);
										SET_CAR_CAN_BE_DAMAGED(pveh,true);
										SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
										SET_CAN_BURST_CAR_TYRES(pveh,true);
										BURST_CAR_TYRE(pveh,0);
										BURST_CAR_TYRE(pveh,1);
										BURST_CAR_TYRE(pveh,4);
										BURST_CAR_TYRE(pveh,5);
										SET_ENGINE_HEALTH(pveh,0.0);
										GET_CAR_SPEED(pveh,&speed);
										SET_CAR_FORWARD_SPEED(pveh,(speed * 2));
										SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
										print("Made player's car retarded");
									}
								}
								return;
							}
							else if(item_select == 5){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										tick = 0;
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_CAR_SPEED(pveh,&speed);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
										SET_ENGINE_HEALTH(pveh,0.0);
										SET_CAR_ENGINE_ON(pveh,false,true);
										SET_CAR_FORWARD_SPEED(pveh,(speed / 10));
										print("Shut down player's car");
									}
								}
								return;
							}
							else if(item_select == 6){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_CAR_SPEED(pveh,&speed);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										FREEZE_CAR_POSITION(pveh,true);	
										SET_CAR_FORWARD_SPEED(pveh,(speed / 10));
										SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
										print("Froze Player's car in place");
									}
								}
								return;
							}
							else if(item_select == 7){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										GET_CAR_MODEL(pveh, &model);
										GET_CAR_COLOURS(pveh, &color1, &color2);
										GET_EXTRA_CAR_COLOURS(pveh, &color3, &color4);
										DELETE_CAR(&pveh);
										WAIT(10);
										MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
										REQUEST_MODEL(model);
										while(!HAS_MODEL_LOADED(model)) WAIT(0);
										GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
										GET_CHAR_HEADING(pPlayer,&heading);
										if(IS_CHAR_IN_ANY_CAR) WARP_CHAR_FROM_CAR_TO_COORD(pPlayer,x,y,z);
										CREATE_CAR(model,x,y,z,&pveh,true);
										MARK_MODEL_AS_NO_LONGER_NEEDED(model);
										CHANGE_CAR_COLOUR(pveh, color1, color2);
										SET_EXTRA_CAR_COLOURS(pveh, color3, color4);
										SET_VEHICLE_DIRT_LEVEL(pveh, 0);
										WASH_VEHICLE_TEXTURES(pveh, 255);
										SET_CAR_ENGINE_ON(pveh,true,true);
										WARP_CHAR_INTO_CAR(pPlayer,pveh);
										SET_CAR_PROOFS(pveh, true, true, true, true, true);
										SET_CAR_HEADING(pveh,heading);
										print("Stole online player's car");
									}
									else print("Player not in vehicle");
								}
								return;
							}
							else if(item_select == 8){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										CREATE_OBJECT(0x1B42315D,0.0,0.0,0.0,&otmp,true);
										ATTACH_OBJECT_TO_CAR_PHYSICALLY(otmp,pveh,0,0,0,0,0,0.0,0,0,0.0,0,0,0,0);
										WAIT(10);
										MARK_OBJECT_AS_NO_LONGER_NEEDED(&otmp);
										print("Glitched Online Player's Car");
									}
								}
								return;
							}
							else if(item_select == 9){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										road_block(players[index].ped);
									}
								}
								return;
							}
						}
						if(last_selected[4] == 2){
							uint index = (last_selected[2] - 3);
							if(item_select == 1){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										GET_CAR_SPEED(pveh,&speed);
										SET_CAR_FORWARD_SPEED(pveh,(speed * 10));
										print("Boosted Player's car");
									}
								}
								return;
							}
							else if(item_select == 2){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										GET_CAR_SPEED(pveh,&speed);
										SET_CAR_FORWARD_SPEED(pveh,(speed / 10));
										print("Halted Player's car");
									}
								}
								return;
							}
							else if(item_select == 3){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(pPlayer)){
										if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
											GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
											GET_CAR_CHAR_IS_USING(pPlayer,&paveh);
											GET_DRIVER_OF_CAR(paveh,&driver);
											if(driver == pPlayer){
												if((!IS_CHAR_IN_ANY_BOAT(players[index].ped)) && (!IS_CHAR_IN_ANY_HELI(players[index].ped))){
													GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
													REQUEST_CONTROL_OF_NETWORK_ID(nvid);
													tick = 0;
													while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
														tick++;
														REQUEST_CONTROL_OF_NETWORK_ID(nvid);
														if(tick >= 200){
															print("~r~Error");
															return;
														}
														WAIT(0);
													}
													SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
													if(!IS_CAR_ATTACHED(pveh)){
														SET_CHAR_VISIBLE(pPlayer, false);
														SET_CAR_VISIBLE(paveh, false);
														GET_CAR_HEADING(pveh,&heading);
														GET_CHAR_COORDINATES(players[index].ped,&x,&y,&z);
														SET_CAR_HEADING(paveh,heading);
														FREEZE_CAR_POSITION(pveh,true);
														ATTACH_CAR_TO_CAR(pveh,paveh,0,0,0,-0.3,0,0,0);
														LOCK_CAR_DOORS(paveh,4);
														LOCK_CAR_DOORS(pveh,4);
														SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
														print_long("Players vehicle now under your control. Press again to ~r~disable");
														return;
													}
													else if(IS_CAR_ATTACHED(pveh)){
														SET_CHAR_VISIBLE(pPlayer, true);
														SET_CAR_VISIBLE(paveh, true);
														LOCK_CAR_DOORS(paveh,1);
														LOCK_CAR_DOORS(pveh,1);
														FREEZE_CAR_POSITION(pveh,false);
														DETACH_CAR(pveh);
														SET_NETWORK_ID_CAN_MIGRATE(nvid,true);
														print("Players vehicle no longer under control");
														return;
													}
												}
												else print("Player must be in a car or bike");
											}
											else print("You must be the driver of your own vehicle");
										}
										else print("Player not in Vehicle");
									}
									else print("You are not in a Vehicle");
								}
								return;
							}
							else if(item_select == 4){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_HELI(pPlayer)){
										if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
											Object Object1;
											GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
											GET_CAR_CHAR_IS_USING(pPlayer,&paveh);
											GET_DRIVER_OF_CAR(paveh,&driver);
											if(driver == pPlayer){
												GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
												REQUEST_CONTROL_OF_NETWORK_ID(nvid);
												tick = 0;
												while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
													tick++;
													REQUEST_CONTROL_OF_NETWORK_ID(nvid);
													if(tick >= 200){
														print("~r~Error");
														return;
													}
													WAIT(0);
												}
												SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
												if(!IS_CAR_ATTACHED(pveh)){
												//	Vector3 minimum,maximum;
												//	GET_CAR_MODEL(paveh, &model);
												//	GET_MODEL_DIMENSIONS(model, &minimum, &maximum);
													if(IS_CAR_MODEL(paveh, MODEL_SKYLIFT)){
															// Skylift
														GET_CAR_COORDINATES(pveh, &x, &y, &z);
														
														dist = GET_HEIGHT_OF_VEHICLE(pveh, x, y, z, false, true);
														
														if(IS_BIG_VEHICLE(pveh)) y = -3.50000000, z = 0.90;
														
														GET_CAR_HEADING(paveh,&heading);
														GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
														SET_CAR_HEADING(pveh,heading);
														teleport_net_char(players[index].ped,x,y,z);
														FREEZE_CAR_POSITION(pveh,true);
														ATTACH_CAR_TO_CAR(pveh, paveh, 0, 0.00000000, -2.80000000, dist - 0.63, 0.00000000, 0.00000000, 0.00000000);
														LOCK_CAR_DOORS(paveh,4);
														LOCK_CAR_DOORS(pveh,4);
													}
													else{
														REQUEST_MODEL(MODEL_CAR_WINCH);
														while(!HAS_MODEL_LOADED(MODEL_CAR_WINCH)) WAIT(0);
														CREATE_OBJECT(MODEL_CAR_WINCH,x,y,z,&Object1,true);
														ATTACH_OBJECT_TO_CAR(Object1,paveh,0,0,-1.2403,-0.3493,0,-1.07,1.5397);
														MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_CAR_WINCH);
														CREATE_OBJECT(MODEL_CAR_WINCH,x,y,z,&Object1,true);
														ATTACH_OBJECT_TO_CAR(Object1,paveh,0,0,1.6342,1.0,0,-1.3320,1.6270);
														MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_CAR_WINCH);
														GET_CAR_HEADING(paveh,&heading);
														GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
														SET_CAR_HEADING(pveh,heading);
														teleport_net_char(players[index].ped,x,y,z);
														FREEZE_CAR_POSITION(pveh,true);	
														ATTACH_CAR_TO_CAR(pveh,paveh,0,0,-3,-1.5,0,0,0);
														LOCK_CAR_DOORS(paveh,4);
														LOCK_CAR_DOORS(pveh,4);
													}
													print_long("Vehicle attached to heli.");
													return;
												}
												else if(IS_CAR_ATTACHED(pveh)){
													LOCK_CAR_DOORS(paveh,1);
													LOCK_CAR_DOORS(pveh,1);
													FREEZE_CAR_POSITION(pveh,false);
													DETACH_CAR(pveh);
													SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
													print("Vehicle detached from heli.");
													return;
												}
											}
											else print("You must be the driver.");
										}
										else print("Player is not in a vehicle.");
									}
									else print("You are not in a helicopter.");
								}
								return;
							}
							else if(item_select == 5){
								#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
								#endif
								if(IS_CHAR_IN_ANY_CAR(pPlayer)){
									GET_CAR_CHAR_IS_USING(pPlayer,&paveh);
									GET_CAR_HEADING(paveh,&heading);
									if(heading > 180) heading -= 180.0;
									else heading += 180.0;
									GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
									GET_DRIVER_OF_CAR(paveh,&driver);
									if(driver == pPlayer){
										if(DOES_CHAR_EXIST(players[index].ped) && IS_CHAR_IN_ANY_CAR(players[index].ped)){
											GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
											GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											tick = 0;
											while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
												tick++;
												REQUEST_CONTROL_OF_NETWORK_ID(nvid);
												if(tick >= 200){
													print("~r~Error");
													return;
												}
												WAIT(0);
											}      	
											SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
											if(!IS_CAR_ATTACHED(pveh)){
												SET_CAR_HEADING(pveh,heading);
												teleport_net_char(players[index].ped,x,y,z);
												FREEZE_CAR_POSITION(pveh,true);
												ATTACH_CAR_TO_CAR(pveh,paveh,0,0,-4.70,0,0,0,0);
												LOCK_CAR_DOORS(pveh,4);
											}
											else if(IS_CAR_ATTACHED(pveh)){
												LOCK_CAR_DOORS(pveh,1);
												FREEZE_CAR_POSITION(pveh,false);
												DETACH_CAR(pveh);
												SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
											}
										}	
									}
									else print("You must be the driver of your own vehicle");
								}
								else print("Your not a in Vehicle");
								return;
							}
						}
						if(last_selected[4] == 7){
							uint index = (last_selected[2] - 3);
							if(item_select == 1){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										SET_CAR_VISIBLE(pveh,false);
										print("Player's Car Invisible");
									}
									else print("~r~Player not in vehicle");
								}
								return;
							}
							else if(item_select == 2){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
										GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
										GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										tick = 0;
										while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
											tick++;
											REQUEST_CONTROL_OF_NETWORK_ID(nvid);
											if(tick >= 200){
												print("~r~Error");
												return;
											}
											WAIT(0);
										}
										SET_CAR_VISIBLE(pveh,true);
										print("Player's Car Visible");
									}
									else print("~r~Player not in vehicle");
								}
								return;
							}
						}
						if(last_selected[4] == 8){
							uint index = (last_selected[2] - 3);
							if(item_select == 1){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 0, 0);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Black");
								}
								return;
							}
							else if(item_select == 2){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 133, 133);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now White");
								}
								return;
							}
							else if(item_select == 3){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 128, 128);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Blue");
								}
								return;
							}
							else if(item_select == 4){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 125, 125);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Red");
								}
								return;
							}
							else if(item_select == 5){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 99, 99);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Purple");
								}
								return;
							}
							else if(item_select == 6){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 99, 99);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Pink");
								}
								return;
							}
							else if(item_select == 7){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 127, 127);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Yellow");
								}
								return;
							}
							else if(item_select == 8){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 132, 132);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Orange");
								}
								return;
							}
							else if(item_select == 9){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									CHANGE_CAR_COLOUR(pveh, 126, 126);
									SET_EXTRA_CAR_COLOURS(pveh, 0, 0);
									SET_VEHICLE_DIRT_LEVEL(pveh, 0);
									WASH_VEHICLE_TEXTURES(pveh, 255);
									print("Player's Car is now Green");
								}
								return;
							}
						}
						if(last_selected[4] == 9){
							uint index = (last_selected[2] - 3);
							if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
								GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
								if(item_select == 1){
									if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
										print("Player must be in a car");
										return;
									}
									Object lights;
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.4,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									SET_OBJECT_VISIBLE(lights, true);
									print("Added Blue Neons");
									return;
								}
								else if(item_select == 2){
									if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
										print("You must be in a car");
										return;
									}
									if(GET_CURRENT_EPISODE() != 2){
										print("~g~You must be on Tbogt");
										return;
									}
									Object lights;
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xB3AC6409, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									print("Added Yellow Neons");
									return;
								}
								else if(item_select == 3){
									if(GET_CURRENT_EPISODE() != 2){
										print("~g~You must be on Tbogt");
										return;
									}
									if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
										print("You must be in a car");
										return;
									}
									Object lights;  
									CREATE_OBJECT(0xD611D7B6, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0,0.0999999,0.24,-0.36, 0,-1.56, 1.521);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0xD611D7B6, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0,0.0999999,0.24,-0.36, 0,-1.56, 1.521);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									print("Added Green Neons");
									return;
								}
								else if(item_select == 4){
									Object lights;
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									print("Added Red Neons");
									return;
								}
								else if(item_select == 5){
									if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
										print("You must be in a car");
										return;
									}
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									Object lights;
									//blue
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.4,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xD20167BE, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.4,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									SET_OBJECT_VISIBLE(lights, true);
									//red
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.5,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									CREATE_OBJECT(0xCB26803D , 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.2,0.2,-0.2,-190,0,160.2);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									print("Added Pink Neons");
									return;
								}
								else if(item_select == 6){
									Object lights;
									if(!IS_CHAR_IN_ANY_CAR(players[index].ped)){
										print("You must be in a car");
										return;
									}
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,0.79,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,-0.79,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,-0.43,0,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.53,0,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,0.79,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0,-0.79,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,-0.43,0,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									CREATE_OBJECT(0x2F8AEA79, 0.0f, 0.0f, 0.0f, &lights, 1);
									WAIT(1);
									ATTACH_OBJECT_TO_CAR(lights,pveh,0.0f,0.53,0,-0.29,-1.55,0,0);
									SET_OBJECT_LIGHTS(lights, true);
									SET_OBJECT_VISIBLE(lights, true);
									SET_OBJECT_INVINCIBLE(lights, 1);
									FREEZE_OBJECT_POSITION(lights, true);
									print("Added Orange Neons");
									return;
								}
							}
						}
						if(last_selected[4] == 10){
							uint index = (last_selected[2] - 3);
							if(item_select == 1){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									SET_CAR_COLLISION(pveh,true);
									print("Player's Car is now non-translucent");
								}
								return;
							}
							else if(item_select == 2){
								if(!DOES_CHAR_EXIST(players[index].ped)) return;
								if(IS_CHAR_IN_ANY_CAR(players[index].ped)){
									GET_CAR_CHAR_IS_USING(players[index].ped,&pveh);									
									GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
									REQUEST_CONTROL_OF_NETWORK_ID(nvid);
									tick = 0;
									while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
										tick++;
										REQUEST_CONTROL_OF_NETWORK_ID(nvid);
										if(tick >= 100){
											print("~r~Error");
											return;
										}
										WAIT(0);
									}
									SET_CAR_COLLISION(pveh,false);
									print("Player's Car is now translucent");
								}
								return;
							}
						}
					}
					if(last_selected[3] == 6){
						if(last_selected[4] == 7){
							uint index = (last_selected[2] - 3);
							if(!DOES_CHAR_EXIST(players[index].ped)) return;
							freeze_net_char(players[index].ped,item_select);
						}
					}
					if(last_selected[3] == 8){
						if(last_selected[4] == 1){
							uint index = (last_selected[2] - 3);
							if(item_select == 1){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									attack_spawnguards(players[index].ped);
								}
								return;
							}
							else if(item_select == 2){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									relationship_spawnguards(players[index].id, RELATIONSHIP_COMPANION);
								}
								return;
							}
							else if(item_select == 3){
								if(DOES_CHAR_EXIST(players[index].ped)){
									#ifndef EMMAN
									if(is_whitelisted(index)){
										print("Player is whitelisted");
										return;
									}
									#endif
									relationship_spawnguards(players[index].id, RELATIONSHIP_HATE);
								}
								return;
							}
						}
					}
					if(last_selected[3] == 9){
						uint index = (last_selected[2] - 3);
						if(!DOES_CHAR_EXIST(players[index].ped)) return;
						spawn_car_for_char(players[index].ped,menu[item_select].value);
						print(GET_STRING_FROM_TEXT_FILE(GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(menu[item_select].value)));
					}
				}
			}
		}
	}
	#endif
}

void looped_functions(void){
	//player options
	SET_CHAR_INVINCIBLE(pPlayer,godmode);
	GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
	
	if(IS_CHAR_SHOOTING(pPlayer)){
		uint weapon,ammo, max_ammo;
		GET_CURRENT_CHAR_WEAPON(pPlayer,&weapon);
		if(weapon != WEAPON_GRENADE && weapon != WEAPON_MOLOTOV){
			GET_MAX_AMMO_IN_CLIP(pPlayer,weapon,&ammo);
			GET_MAX_AMMO(pPlayer, weapon, &max_ammo);
			ENABLE_MAX_AMMO_CAP(false);
			SET_CHAR_AMMO(pPlayer, weapon, max_ammo);
			SET_AMMO_IN_CLIP(pPlayer,weapon,ammo);
		}
	}
	
	if(objectgun){
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_PISTOL) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			object_shoot();
		}
	}
	
	if(cargun){
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_DEAGLE) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			car_shoot(pPlayer);
		}
	}
	
	if(pedgun){
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_PISTOL) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			ped_shoot();
		}
	}
	
	if(rocketgun){
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_DEAGLE) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			rocket_deagle(pPlayer);
		}
	}
	
	if(dragongun){
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_BARETTA) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			dragon_gun();
		}
	}

	if(powgun){
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if((IS_CHAR_SHOOTING(pPlayer)) && (wep == WEAPON_PISTOL) && (!IS_CHAR_IN_ANY_CAR(pPlayer))){
			pow_gun();
		}
	}	
	
	if(limo_loop){
		if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))) drive_limo(limo_model,2);
	}
	
	if(xyzh){
		GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
		GET_CHAR_HEADING(pPlayer,&heading);
		draw_xyzh(x,y,z,heading);
	}
	
	if(limo_land){
		if(pveh == LimoCar){
			if(IS_BUTTON_JUST_PRESSED(0,DPAD_RIGHT)){
				print("Escort speeding up.");
				SET_TIME_SCALE(50.0);
			}
			else if(IS_BUTTON_JUST_PRESSED(0,DPAD_LEFT)){
				print("Escort slowing down.");
				SET_TIME_SCALE(1.0);
			}
		}
		
		if(DOES_VEHICLE_EXIST(LimoCar)){
			GET_DRIVER_OF_CAR(LimoCar, &LimoDriver);
			if(DOES_CHAR_EXIST(LimoDriver)){
				GET_CHAR_MODEL(LimoDriver,&model);
				if(model == MODEL_M_M_HELIPILOT_01){
					GET_CAR_COORDINATES(LimoCar,&x,&y,&z);
					GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,limo.x,limo.y,limo.z,&dist);
					GET_CAR_MODEL(LimoCar,&model);
					if(dist <= 40){
						GET_GROUND_Z_FOR_3D_COORD(limo.x,limo.y,limo.z,&z);
						teleport_char(LimoDriver,limo.x,limo.y,z + 3);
						WAIT(100);
						drive_limo(limo_model,3);
						SET_TIME_SCALE(1.0);
						limo_land = false;
					}
				}
				else limo_land = false;
			}
			else limo_land = false;
		}
		else limo_land = false;
	}
	
	if(fweather){
		if(GET_HOST_ID() != GET_PLAYER_ID()){
			print("~r~You must be Host");
			fweather = false;
			reset_menu();
			return;
		}
		GET_TIME_OF_DAY(&tick, &i);
		SET_TIME_OF_DAY(tick,i);
	}
	
	if(rweather){
		if(GET_HOST_ID() != GET_PLAYER_ID()){
			print("~r~You must be Host");
			rweather = false;
			reset_menu();
			return;
		}
		if(fweather){
			fweather = false;
			reset_menu();
		}
		GET_TIME_OF_DAY(&tick, &i);
		SET_TIME_OF_DAY(tick,i + 30);
	}

	if(rapidfire){
		if(IS_CHAR_SHOOTING(pPlayer) || IS_BUTTON_PRESSED(0,BUTTON_R) && !IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), true);
			SET_TIME_SCALE(50.0);
			SET_CHAR_ALL_ANIMS_SPEED(pPlayer, 30);
			SET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER(GetPlayerPed(), 1.0f);
		}
		else{
			SET_CHAR_ALL_ANIMS_SPEED(pPlayer, 1);
			SET_TIME_SCALE(1.0);
		}
	}
	else SET_PLAYER_FAST_RELOAD(GetPlayerIndex(), fastreload);

	if(!wepvisible && !(IS_BUTTON_PRESSED(0,BUTTON_L) || IS_BUTTON_PRESSED(0,BUTTON_R))){
		SET_CHAR_CURRENT_WEAPON_VISIBLE(pPlayer, false);
	}

	if(autoflip){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
            if((IS_CAR_UPSIDEDOWN(pveh)) && (!IS_CAR_IN_AIR_PROPER(pveh)) && (!IS_CHAR_IN_ANY_HELI(pPlayer)) && (!IS_CAR_IN_WATER(pveh))){
				GET_CAR_COORDINATES(pveh, &x, &y, &z);
				GET_CAR_HEADING(pveh, &heading);
				if(heading > 180.0) heading -= 180.0;
				else heading += 180.0;
				SET_VEHICLE_QUATERNION(pveh, 0, 0, 0, 0);
				SET_CAR_COORDINATES(pveh, x, y, z);
				SET_CAR_HEADING(pveh, heading);
            }
        }
	}
	
	if(pprotection){
		uint pos[4]; 
		GET_POSITION_OF_ANALOGUE_STICKS(0,&pos[0],&pos[1],&pos[2],&pos[3]);
		if(pos[0] == 0 && pos[1] == 0)
			FREEZE_CHAR_POSITION(pPlayer,true);
		else
			FREEZE_CHAR_POSITION(pPlayer,false);
	}
	
	if(ninja){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			uint pos[4]; 
			GET_POSITION_OF_ANALOGUE_STICKS(0,&pos[0],&pos[1],&pos[2],&pos[3]);
			if(pos[0] == 0 && pos[1] == 0){
				SET_CHAR_VISIBLE(pPlayer, false);
			}
			else{
				SET_CHAR_VISIBLE(pPlayer, true);
			}
		}
		else SET_CHAR_VISIBLE(pPlayer, false);
	}
	
	if(rblip){
		SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS(false);
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			uint pos[4]; 
			GET_POSITION_OF_ANALOGUE_STICKS(0,&pos[0],&pos[1],&pos[2],&pos[3]);
			if(pos[0] == 0 && pos[1] == 0){
				if(!(IS_BUTTON_PRESSED(0,BUTTON_L) || IS_BUTTON_PRESSED(0,BUTTON_R))) SET_PLAYER_CONTROL(GetPlayerIndex(), false);
				else SET_PLAYER_CONTROL(GetPlayerIndex(), true);
			}
			else{
				SET_PLAYER_CONTROL(GetPlayerIndex(), true);
			}
		}
		else SET_PLAYER_CONTROL(GetPlayerIndex(), true);
	}
	
	if(view_online_player){
		view_player(spectatePed);
	}
	
	if(superfight){
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if(wep == WEAPON_UNARMED || wep == WEAPON_BASEBALLBAT || wep == WEAPON_POOLCUE){
			if(IS_BUTTON_PRESSED(0,BUTTON_L) && IS_BUTTON_JUST_PRESSED(0,BUTTON_X) && !IS_CHAR_IN_ANY_CAR(pPlayer)){
				WAIT(300);
				GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, 1, 0, &x, &y, &z);
				ADD_EXPLOSION(x,y,z,EXPLOSION_GRENADE,35.0,false,true,0.0);
			}
			else if(IS_BUTTON_PRESSED(0,BUTTON_L) && (IS_BUTTON_JUST_PRESSED(0,BUTTON_B) || IS_BUTTON_JUST_PRESSED(0,BUTTON_Y)) && !IS_CHAR_IN_ANY_CAR(pPlayer)){
				WAIT(270);
				GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, 1, 1.5, &x, &y, &z);
				ADD_EXPLOSION(x,y,z,EXPLOSION_GRENADE,35.0,false,true,0.0);
			}
		}
	}
	
	if(bpvest){
		GET_CHAR_ARMOUR(pPlayer,&tmp);
		if(tmp < 99){
			GIVE_WEAPON_TO_CHAR(pPlayer,WEAPON_ARMOUR,1,false);
			ADD_ARMOUR_TO_CHAR(pPlayer,99);
		}
	}
	
	if(vehwater){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			drive_water(pveh);
		}
		else drive_water(pPlayer);
	}
	
	if(collision){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_CAR_COLLISION(pveh, false);
		}
	}
	else{
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_CAR_COLLISION(pveh, true);
		}
	}
	
	if(superrun){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_PRESSED(0,BUTTON_A)){
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,5.0,0.0,0.0,0.0,0.0,true,true,true,true);
			}
		}
	}
	
	if(superjump){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_PRESSED(0,BUTTON_X)){
				APPLY_FORCE_TO_PED(pPlayer,true,0.0,0.0,5.0,0.0,0.0,0.0,true,true,true,true);
			}
		}	
	}

	if(chronicle){
		if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_JUST_PRESSED(0,BUTTON_B)){
			chronicle_shoot();
		}
		GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
		ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
		ADD_EXPLOSION(x,y,z + 5,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
		ADD_EXPLOSION(x,y - 5,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
	}
	
	if(inferno){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_JUST_PRESSED(0,BUTTON_B)){
				inferno_shoot();
			}
		}
	}

	if(rocket){
		if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_RB)){
				if(IS_BUTTON_PRESSED(0,DPAD_LEFT)) rocket_shoot(pPlayer, 1);
				else if(IS_BUTTON_PRESSED(0,DPAD_RIGHT)) rocket_shoot(pPlayer, 2);
				else if(IS_BUTTON_PRESSED(0,DPAD_DOWN)) rocket_shoot(pPlayer, -1);
				else rocket_shoot(pPlayer, 0);
			}
		}
	}
	
	if(carjump){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_JUST_PRESSED(0,BUTTON_RB)) APPLY_FORCE_TO_CAR(pveh, 0.0f, 0.0f, 0.0f, 600.0f , 0.0f,0.0f,0.0f, 0, 1, 1, 1 );
		}
	}
	
	if(rocketveh){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if(IS_BUTTON_PRESSED(0,BUTTON_X)) rocketveh_shoot(pveh);
		}
	}
	
	if(lowerpveh){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer)) && (IS_VEHICLE_ON_ALL_WHEELS(pveh)))
				APPLY_FORCE_TO_CAR(pveh,true,0.0,0,-0.1,0.0,0.0,0.0,true,true,true,true);
		}
	}
	
	if(hydrolics){
		if(IS_BUTTON_PRESSED(0,BUTTON_X)){
			if (IS_CHAR_IN_ANY_CAR(pPlayer)){
				if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))){
				//	RESET_CAR_WHEELS(pveh, true);
					if(IS_VEHICLE_ON_ALL_WHEELS(pveh)){
						if(IS_CHAR_ON_ANY_BIKE(pPlayer)) APPLY_FORCE_TO_CAR(pveh, 0.0f, 0.0f, 0.0f, 90.0f , 0.0f,0.0f,-90.0f, 0, 1, 1, 1 );		
						else APPLY_FORCE_TO_CAR(pveh, 0.0f, 0.0f, 0.0f, 70.0f , 0.0f,0.0f,-70.0f, 0, 1, 1, 1 );		
					}
				}
			}
		}
	}
	
	if(chaos){
		for(i = 16;i >= 0;i--){
			if(i < 0) continue;
			if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
			if(!NETWORK_IS_PLAYER_TALKING(i)) continue;
			if(NETWORK_IS_PLAYER_MUTED_BY_ME(i)) continue;
			if(GET_PLAYER_ID() == i) continue;
			GET_PLAYER_CHAR(i, &online_char);
			if(!DOES_CHAR_EXIST(online_char)) continue;
			if(IS_CHAR_IN_ANY_CAR(online_char)){
				GET_CAR_CHAR_IS_USING(online_char, &pveh);
				GET_CAR_SPEED(pveh,&speed);
				SET_CAR_FORWARD_SPEED(pveh,(speed * 10));
				EXPLODE_CAR(pveh, true, false);
			}
			if(!IS_CHAR_ON_FIRE(online_char)) START_CHAR_FIRE(online_char);
		}
	}
	
	if(ragdoll){
		if(IS_BUTTON_PRESSED(0,BUTTON_LB) && IS_BUTTON_JUST_PRESSED(0,BUTTON_B)){
			if(!IS_PED_RAGDOLL(pPlayer)){
			//	SWITCH_PED_TO_RAGDOLL(pPlayer,20000,30000,false,false,false,false);
				SWITCH_PED_TO_RAGDOLL(pPlayer,20000,0,false,false,false,false);
				SWITCH_PED_TO_ANIMATED(pPlayer,true);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),true);
			}
			else{
				SWITCH_PED_TO_ANIMATED(pPlayer,false);
				GIVE_PLAYER_RAGDOLL_CONTROL(GET_PLAYER_ID(),false);
			}
		}
	}
	
	if(!nos){
		if(vhelper){
			if(IS_CHAR_IN_ANY_CAR(pPlayer)){
				SET_CAR_CAN_BE_DAMAGED(pveh,false);
				SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,false);
				SET_CAN_BURST_CAR_TYRES(pveh,false);
				SET_HELI_BLADES_FULL_SPEED(pveh);
				SET_CAR_PROOFS(pveh, true, true, true, true, true);
			}
		}
		else{
			if(IS_CHAR_IN_ANY_CAR(pPlayer)){
				SET_CAR_CAN_BE_DAMAGED(pveh,true);
				SET_CAR_CAN_BE_VISIBLY_DAMAGED(pveh,true);
				SET_CAN_BURST_CAR_TYRES(pveh,true);
				SET_CAR_PROOFS(pveh, false, false, false, false, false);
			}
		}
	}
	else{
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_PETROL_TANK_HEALTH(pveh, -1);
		}
	}
	
	if(carsonground){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			SET_CAR_ON_GROUND_PROPERLY(pveh);
		}
	}
	
	if(bikefly){
		if((IS_CHAR_ON_ANY_BIKE(pPlayer)) && IS_BUTTON_PRESSED(0,BUTTON_R)){
			GET_CAR_SPEED(pveh,&speed);
			SET_CAR_FORWARD_SPEED(pveh,(speed * 1.05));
		}
		if(IS_CHAR_ON_ANY_BIKE(pPlayer) && IS_BUTTON_PRESSED(0,BUTTON_L)){
			if (!IS_VEHICLE_ON_ALL_WHEELS(pveh)){
				GET_CAR_SPEED(pveh,&speed);
				SET_CAR_FORWARD_SPEED(pveh,(speed / 1.05));
			}
		}
	}
	
	if(veh_height){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))&& (!IS_CHAR_ON_ANY_BIKE(pPlayer)) && (IS_VEHICLE_ON_ALL_WHEELS(pveh))){
				APPLY_FORCE_TO_CAR(pveh,true,0.0,0,0.15f,0.0,0.0,0.0,true,true,true,true);
			}
		}
	}
	
	if(nfs){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			if((!IS_CHAR_IN_ANY_BOAT(pPlayer)) && (!IS_CHAR_IN_ANY_HELI(pPlayer))){
					if(IS_BUTTON_PRESSED(0,BUTTON_R)){
						GET_CAR_SPEED(pveh,&speed);
						SET_CAR_FORWARD_SPEED(pveh,(speed * 1.02));
					}
					if(IS_BUTTON_JUST_PRESSED(0,BUTTON_L)){
						GET_CAR_SPEED(pveh,&speed);
						SET_CAR_FORWARD_SPEED(pveh,(speed / 6));
					}
			}
			else{
				if(IS_BUTTON_PRESSED(0,BUTTON_R)){
					GET_CAR_SPEED(pveh,&speed);
					SET_CAR_FORWARD_SPEED(pveh,(speed * 1.02));
				}
				if(IS_BUTTON_JUST_PRESSED(0,BUTTON_L)){
					GET_CAR_SPEED(pveh,&speed);
					SET_CAR_FORWARD_SPEED(pveh,(speed / 6));
				}
			}
		}
	}
	
	if(helistrike){
		if((IS_CHAR_IN_ANY_HELI(pPlayer)) && (IS_BUTTON_JUST_PRESSED(0,STICK_LEFT))) helibomb();
	}
	
	if(rainbowmenu){
		GENERATE_RANDOM_INT_IN_RANGE(0,255,&s_r);
		GENERATE_RANDOM_INT_IN_RANGE(0,255,&s_g);
		GENERATE_RANDOM_INT_IN_RANGE(0,255,&s_b);
	}
	
	if(rainbowcar){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color1);
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color2);
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color3);
			GENERATE_RANDOM_INT_IN_RANGE(0,133,&color4);
			CHANGE_CAR_COLOUR(pveh, color1, color2);
			SET_EXTRA_CAR_COLOURS(pveh, color3, color4);
		}
	}
	
	if(slowmotion){
		SET_TIME_SCALE(0.3f);
	}
	
	//misc
	if(xmc_chat){
		spawn.y = 0.875;
		for(i = 15;i >= 0;i--){
			if(i < 0) continue;
			if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
			if(!NETWORK_IS_PLAYER_TALKING(i)) continue;
			if(NETWORK_IS_PLAYER_MUTED_BY_ME(i)) continue;
			GET_PLAYER_RGB_COLOUR(i,&r,&g,&b);
			set_up_draw(3,0.3,0.3,r,g,b,255);
			draw_text("STRING",0.70,spawn.y,GET_PLAYER_NAME(i));
			spawn.y -= 0.03;			
		}
	}
	
	if(group_loop){
		if(DOES_CHAR_EXIST(group_onlineped)){
			GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
			GET_CHAR_COORDINATES(pPlayer,&x,&y,&z);
			GET_CHAR_COORDINATES(group_onlineped,&mx,&my,&mz);
			GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
			if((dist >= 10) && (DOES_GROUP_EXIST(Bgroup))){
				print_long("Victim to far away");
			//	REMOVE_CHAR_FROM_GROUP(group_onlineped);
				REMOVE_GROUP(Bgroup);
			//	REMOVE_CHAR_FROM_GROUP(pPlayer);
			//	SET_GROUP_FORMATION(Bgroup, 0);
				group_loop = false;
				return;
			}
			if(IS_CHAR_IN_ANY_CAR(group_onlineped)){
				GET_CAR_CHAR_IS_USING(group_onlineped,&pveh);
				GET_DRIVER_OF_CAR(pveh,&driver);
				if(pPlayer == driver){
					if(DOES_GROUP_EXIST(Bgroup)){
					//	REMOVE_CHAR_FROM_GROUP(group_onlineped);
					//	REMOVE_CHAR_FROM_GROUP(pPlayer);
						REMOVE_GROUP(Bgroup);
						LOCK_CAR_DOORS(pveh,4);
					//	SET_GROUP_FORMATION(Bgroup, 0);
						print_long("~b~Online Player sucessfully Kidnapped, locking doors.");
						group_loop = false;
					}
				}
			}
		}
	}
	
	if(GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT("player_menuiv") != 0 && show_menu)
		menu_shutdown();
	
	//garage
	if(in_paint && IS_CHAR_IN_ANY_CAR(pPlayer)){
		if(menu[item_select].value != menu[item_select].extra_val){
			GET_CAR_COLOURS(pveh,&color1,&color2);
			GET_EXTRA_CAR_COLOURS(pveh,&color3,&color4);
			if(item_select == 1)
				CHANGE_CAR_COLOUR(pveh,(menu[item_select].value - 1),color2);
			if(item_select == 2)
				CHANGE_CAR_COLOUR(pveh,color1,(menu[item_select].value - 1));
			if(item_select == 3)
				SET_EXTRA_CAR_COLOURS(pveh,(menu[item_select].value - 1),color4);				
			if(item_select == 4)
				SET_EXTRA_CAR_COLOURS(pveh,color3,(menu[item_select].value - 1));

			menu[item_select].extra_val = menu[item_select].value;
		}
	}
	
	if(bw_checker){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_COLOURS(pveh, &color1, &color2);
			if(color1 == 133) CHANGE_CAR_COLOUR(pveh, 0, 0);
			else CHANGE_CAR_COLOUR(pveh, 133, 133);
		}
	}
	else if(rb_checker){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CAR_COLOURS(pveh, &color1, &color2);
			if(color1 == 128) CHANGE_CAR_COLOUR(pveh, 125, 125);
			else CHANGE_CAR_COLOUR(pveh, 128, 128);
		}
	}
	return;
}

void do_online_player_loop(void){
	// float x,y,z;
	for(i = 0;i <= 15;i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)){
			if(players[i].rocket) if(DOES_CHAR_EXIST(rocketped[2])) DELETE_CHAR(&rocketped[2]);
			players[i].mprotection = false;
			players[i].force = false;
			players[i].rage = false;
			players[i].water = false;
			players[i].disarm = false;
			players[i].rocket = false;
			players[i].cargun = false;
			continue;
		}
		GET_PLAYER_CHAR(i,&online_char);
		if(DOES_CHAR_EXIST(online_char)){
			if(players[i].mprotection){
					GET_CHAR_ARMOUR(online_char,&tmp);
					if(tmp < 99){
						GIVE_WEAPON_TO_CHAR(online_char,WEAPON_ARMOUR,1,false);
						ADD_ARMOUR_TO_CHAR(online_char,99);
					}
				if(HAS_CHAR_GOT_WEAPON(online_char, WEAPON_ROCKET)){
					REMOVE_ALL_CHAR_WEAPONS(online_char);
					print("Protected player was given freeze gun");
				}
			}
			if(players[i].force){
				GET_CHAR_COORDINATES(online_char,&x,&y,&z);	  	
				ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,15.0,false,true,0.0);
			}
			if(players[i].rage){
				if(IS_CHAR_IN_ANY_CAR(online_char)) freeze_net_car(online_char);
			}
			if(players[i].water){
				if(vehwater) do_toggle(vehwater);
				if(IS_CHAR_IN_ANY_CAR(online_char)){
					GET_CAR_CHAR_IS_USING(online_char,&pveh);
					drive_water(pveh);
				}
				else drive_water(online_char);
			}
			if(players[i].disarm) REMOVE_ALL_CHAR_WEAPONS(online_char);
			if(players[i].rocket){
				GET_CURRENT_CHAR_WEAPON(online_char, &wep);
				if((IS_CHAR_SHOOTING(online_char)) && (wep == WEAPON_DEAGLE) && (!IS_CHAR_IN_ANY_CAR(online_char))){
					rocket_deagle(online_char);
				}
			}
			if(players[i].cargun){
				GET_CURRENT_CHAR_WEAPON(online_char, &wep);
				if((IS_CHAR_SHOOTING(online_char)) && (wep == WEAPON_PISTOL) && (!IS_CHAR_IN_ANY_CAR(online_char))){
					car_shoot(online_char);
				}
			}
		}
	}
	return;
}

void better_grenade_loop(void){
	if(grenade_active){
		if(!IS_PED_HOLDING_AN_OBJECT(pPlayer)){
			// float x,y,z;
			grenade_active = false;
			tick = 0;
			while(!HAS_OBJECT_COLLIDED_WITH_ANYTHING(ObjectProjectile)){
				tick++;
				if(tick > 2000) return;
				WAIT(0);
			}
			GET_OBJECT_COORDINATES(ObjectProjectile,&x,&y,&z);
			ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,20.0,true,false,0.7f);
			ADD_EXPLOSION(x,y,z + 1,EXPLOSION_SHIP_DESTROY,20.0,true,false,0.7f);
			DELETE_OBJECT(&ObjectProjectile);
			MARK_OBJECT_AS_NO_LONGER_NEEDED(&ObjectProjectile);
		}
	}
	if(IS_PED_HOLDING_AN_OBJECT(pPlayer)){
		if(GET_MODEL_PED_IS_HOLDING(pPlayer) == 0x501811B6 || GET_MODEL_PED_IS_HOLDING(pPlayer) == 0x48FA2738){//object to be new grenade
			grenade_active = true;
			ObjectProjectile = GET_OBJECT_PED_IS_HOLDING(pPlayer);
		}
		else grenade_active = false;
	}
	return;
}

void check_xmc_loop(void){
	#ifndef EMMAN
	for(i = 0;i <= 15;i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if(GET_PLAYER_ID() == i) continue;
		if(is_mambalisted(i)){
			players[i].mprotection = true;
			players[i].force = false;
			players[i].rage = false;
			players[i].disarm = false;
			return;
		}
	}
	if(!xmc_in_game){
		for(i = 0;i <= 15;i++){
			if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
			if(GET_PLAYER_ID() == i) continue;
			if(is_admin(i) || GET_MODEL_PED_IS_HOLDING(online_char) ==  MODEL_CJ_APPLE_SMALL){
				GET_PLAYER_CHAR(i,&online_char);
				xmc_char = online_char;
				xmc_in_game = true;
				print_long("~y~XMC Administrator detected.");
				return;
			}
		}
	}
	else{
		if(!DOES_CHAR_EXIST(xmc_char)) xmc_in_game = false;
		else{
			GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
			GET_CHAR_COORDINATES(xmc_char, &mx, &my, &mz);
			GET_DISTANCE_BETWEEN_COORDS_3D(x,y,z,mx,my,mz,&dist);
			if(dist <= 10){
				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK){ //MODEL_CJ_F1
					print_long("~r~Remote Message: Your Menu has been disabled by an XMC Administrator.");
					while(true) WAIT(0);
				}

				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK2){ //MODEL_CJ_F2
					print_long("~r~Remote Message: Your Console has been frozen by an XMC Administrator");
					WAIT(1000);
					REMOVE_ALL_CHAR_WEAPONS(pveh);
					FREEZE_CHAR_POSITION(pveh,true);
					WAIT(100);
				}
				
				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK3){ //MODEL_CJ_KOR_SMALL_VASE_1
					print_long("~r~Remote Message: Warning from a XMC Administrator.");
				}

				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK4){ //MODEL_CJ_F4
					print_long("~b~Remote message: Hello from an XMC Administrator!");
				}
				
				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK5){ //MODEL_CJ_F5
					print_long("~r~Injecting Remote Virus into ISO Filesystem ..."); //trolol
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
						z += 1;
						WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
					}
					REMOVE_ALL_CHAR_WEAPONS(pPlayer);
					FREEZE_CHAR_POSITION(pPlayer,true);
					SET_PLAYER_CONTROL(GetPlayerIndex(), false);
					godmode = false;
					pprotection = false;
					modderprotect = false;
					chronicle = false;
					vhelper = false;
					SET_PLAYER_INVINCIBLE(GetPlayerIndex(), false);
					DISABLE_PAUSE_MENU(true);
					return;
				}
				
				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK6){ //MODEL_CJ_F6
					godmode = false;
					pprotection = false;
					modderprotect = false;
					chronicle = false;
					vhelper = false;
					inferno = false;
					FREEZE_CHAR_POSITION(pPlayer,false);
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
						FREEZE_CAR_POSITION(pveh,false);
						GET_DRIVER_OF_CAR(pveh,&driver);
						if(driver == pPlayer){
							GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
							SET_NETWORK_ID_CAN_MIGRATE(nvid,true);
						}
					}
					return;
				}
				
				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK7){ //MODEL_CJ_F7
					if(IS_CHAR_IN_ANY_CAR(pPlayer)){
						GET_CAR_CHAR_IS_USING(pPlayer, &pveh);
						DELETE_CAR(&pveh);
						MARK_CAR_AS_NO_LONGER_NEEDED(&pveh);
					}
					do_toggle(xmc_tele);
				}
		
				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK8){ //MODEL_CJ_F8
					print_long("~r~Remote message: You're being sent to Single Player by an XMC Administrator.");
					WAIT(3000);
					TERMINATE_ALL_SCRIPTS_FOR_NETWORK_GAME();
					return;
				}
				if(GET_MODEL_PED_IS_HOLDING(xmc_char) == MODEL_CJ_PROC_BRICK9){ //MODEL_CJ_F9
					print_long("~r~Remote message: Your scripts have been disabled by an XMC Administrator.");
					WAIT(2000);
					TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("modscript");
					TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("modmenu");
					TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("autoload");
					TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME("reset");
					return;
				}
			}
			if(xmc_tele){
				GET_CHAR_COORDINATES(xmc_char, &x, &y, &z);
				teleport_char(pPlayer, x,y,z);
			}
		}
	}
	#endif
	return;
}