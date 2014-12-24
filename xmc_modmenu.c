/*
 * Copyright (c) 2014, Emmanuel Utomi <emmanuelutomi@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <natives.h>
#include "include/vars.h"
#include <common.h>
#include "include/security.h"
#include <consts.h>
#include <types.h>
#include <strings.h>

#ifdef ENGLISH
#include "menu_items.c"
#elif FRENCH
#include "menu_items_french.c"
#elif SPANISH
#include "menu_items_spanish.c"
#endif

#include "weapons.c"
#include "menu_functions.c"
#include "keyboard.c"
#include "engine.c"

void main(void){
	THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME();
	show_menu = false;
	menu_setup();

#ifdef PRIVATE
	//gold
	s_r = 218;
	s_g = 165;
	s_b = 32;
#else
	//blue
	s_r = 0;
	s_g = 191;
	s_b = 255;
#endif
	
	if(drive_free){
		SWITCH_ROADS_OFF(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(false);
	}
	else{
		SWITCH_ROADS_ON(-2225.109,-1006.106,-10,2786.717,2126.596,1000);
		SWITCH_AMBIENT_PLANES(true);
	}
	
	if(neverwanted)
		SET_MAX_WANTED_LEVEL(0);

	#ifdef GTCHECK
		if(!GTchecklist(GET_PLAYER_NAME(GET_PLAYER_ID()))){
			SET_CAR_VISIBLE(pPlayer, 0);
			MARK_MODEL_AS_NO_LONGER_NEEDED(pPlayer);
			REMOVE_CHAR_FROM_GROUP(pveh);
			return;
		}
	#endif
	
	#ifndef PERSONAL
		#ifdef PRIVATE
		if(!(GTcheck(MENU_TITLE, "XMC ModMenu v6.0 Private", 24, 1979196251))){
			SET_CAR_VISIBLE(pPlayer, 0);
			MARK_MODEL_AS_NO_LONGER_NEEDED(pPlayer);
			REMOVE_CHAR_FROM_GROUP(pveh);
			return;
		}
		#else
		if(!(GTcheck(MENU_TITLE, "XMC ModMenu v6.0 Public", 23, -857715149))){
			SET_CAR_VISIBLE(pPlayer, 0);
			MARK_MODEL_AS_NO_LONGER_NEEDED(pPlayer);
			REMOVE_CHAR_FROM_GROUP(pveh);
			return;
		}
		#endif
		#else
		if(!(GTcheck(MENU_TITLE, "XMC ModMenu v6.0 Admin", 22, 1053136273))){
			SET_CAR_VISIBLE(pPlayer, 0);
			MARK_MODEL_AS_NO_LONGER_NEEDED(pPlayer);
			REMOVE_CHAR_FROM_GROUP(pveh);
			return;
		}
	#endif
	
	if(!(GTcheck(MENU_AUTHOR, "Emmanuel Utomi - Emman V4", 25, 1359987799))){
		SET_CAR_VISIBLE(pPlayer, 0);
		MARK_MODEL_AS_NO_LONGER_NEEDED(pPlayer);
		REMOVE_CHAR_FROM_GROUP(pveh);
		return;
	}
	
	#ifdef PERSONAL
		if(!is_admin(GET_PLAYER_ID())){
			SET_CAR_VISIBLE(pPlayer, 0);
			MARK_MODEL_AS_NO_LONGER_NEEDED(pPlayer);
			return;
		}
	#endif
	
	
	WAIT(200);

	print_long("~b~XMC Modmenu by Emmanuel Utomi ~PAD_LB~ + ~PAD_RB~");

	WAIT(100);
	do{
		WAIT(0);
		pPlayer = GetPlayerPed();
		
		check_xmc_loop();
		do_online_player_loop();
		keyboard_actions();
		do_menu();
		looped_functions();
		do_online_player_loop();
		better_grenade_loop();
		
		if(modderprotect){
			if(HAS_CHAR_GOT_WEAPON(pPlayer, WEAPON_ROCKET)){
				REMOVE_WEAPON_FROM_CHAR(pPlayer, WEAPON_ROCKET);
					print_long("Freeze Intercepted: ~r~Freeze gun.");
			}

			GET_PLAYER_GROUP(GetPlayerIndex(), &Bgroup);
			if(DOES_GROUP_EXIST(Bgroup)){
				GET_GROUP_LEADER(Bgroup, &online_char);
				if(online_char != pPlayer){
					REMOVE_CHAR_FROM_GROUP(pPlayer);
					CREATE_GROUP(0, Bgroup, true);
					SET_GROUP_LEADER(Bgroup, pPlayer);
					print_long("Freeze Intercepted: ~r~Ped Group Exploit.");
				}
			}

			for(i = 0;i < 16;i++){
				if(GET_PLAYER_ID() == i) continue;
				if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
				GET_PLAYER_CHAR(i,&online_char);
				if(!DOES_CHAR_EXIST(online_char)) continue;
				GET_CHAR_MODEL(online_char,&model);
				if(model == MODEL_PLAYER){
					SET_CHAR_VISIBLE(online_char,false);
					print_long("Freeze Intercepted: ~r~Model.");
				}
			}

			if(IS_CHAR_IN_ANY_CAR(pPlayer)){
				SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(pPlayer,false);
				GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
				GET_DRIVER_OF_CAR(pveh,&driver);
				if(driver == pPlayer){
					GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
					SET_NETWORK_ID_CAN_MIGRATE(nvid,false);
				}
			}
			else if(HAS_CONTROL_OF_NETWORK_ID(nvid))
				SET_NETWORK_ID_CAN_MIGRATE(nvid,true);
		}
		else{
			if(IS_CHAR_IN_ANY_CAR(pPlayer)){
				SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(pPlayer,true);
				GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
				GET_DRIVER_OF_CAR(pveh,&driver);
				if(driver == pPlayer){
					GET_NETWORK_ID_FROM_VEHICLE(pveh,&nvid);
					SET_NETWORK_ID_CAN_MIGRATE(nvid,true);
				}
			}
		}
		
	} while(true);
}