void keyboard_actions(void){
	if(!xmc_keyboard) return;
	if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_G)){
		do_toggle(godmode);
		if(godmode) print("~g~KB: ~w~Godmode ~b~ON");
		else print("~g~KB: ~w~Godmode ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_I)){
		if(IS_CHAR_VISIBLE(pPlayer)){
			SET_CHAR_VISIBLE(pPlayer, false);
			print("~g~KB: ~w~Player is Invisible");
		}
		else{
			SET_CHAR_VISIBLE(pPlayer, true);
			print("~g~KB: ~w~Player is Visible");
		}
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_J)){
		do_toggle(superjump);
		if(superjump) print("~g~KB: ~w~SuperJump ~b~ON");
		else print("~g~KB: ~w~SuperJump ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_R)){
		do_toggle(superrun);
		if(superrun) print("~g~KB: ~w~SuperRun ~b~ON");
		else print("~g~KB: ~w~SuperRun ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_F)){
		if(IS_CHAR_ON_FIRE(pPlayer)){
			EXTINGUISH_CHAR_FIRE(pPlayer);
			print("~g~KB: ~w~Fire stopped");
		}
		else{
			START_CHAR_FIRE(pPlayer);
			print("~g~KB: ~w~Fire Started");
		}
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_E)){
		if(IS_CHAR_IN_ANY_CAR(pPlayer)){
			GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
			z += 1;
			WARP_CHAR_FROM_CAR_TO_COORD(pPlayer, x, y, z);
			APPLY_FORCE_TO_PED(pPlayer, 1 ,0.0f ,0.0f ,1000.0f ,0.0f ,0.0f ,0.0f ,1 ,1 ,1 ,1);
			print("~g~KB: ~w~Ejected");
			return;
		}
		else print("~g~KB: ~r~You must be in a car");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_K)){
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
			speed = true;
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
			print("~g~KB: ~w~Kicked players out of car");
			return;
		}
		else print("~g~KB: ~r~You must be in a car");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_H)){
		do_toggle(helistrike);
		if(helistrike) print("~g~KB: ~w~Helistrike ~b~ON");
		else print("~g~KB: ~w~Helistrike ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_S)){
		do_toggle(superfight);
		if(superfight) print("~g~KB: ~w~SuperPunch ~b~ON");
		else print("~g~KB: ~w~SuperPunch ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_W)){
		do_toggle(vehwater);
		if(vehwater) print("~g~KB: ~w~Drive/Walk on Water ~b~ON");
		else print("~g~KB: ~w~Drive/Walk on Water ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_P)){
		do_toggle(pprotection);
		FREEZE_CHAR_POSITION(pPlayer,false);
		if(pprotection) print("~g~KB: ~w~Smart Protection ~b~ON");
		else print("~g~KB: ~w~Smart Protection ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_N)){
		if(!inferno){
			if(godmode){
				print("~g~KB: ~w~Godmode must be disabled.");
				return;
			}
			START_CHAR_FIRE(pPlayer);
			WAIT(800);
			godmode = true;
		}
		do_toggle(inferno);
		if(inferno) print("~g~KB: ~w~Inferno ~b~ON");
		else print("~g~KB: ~w~Inferno ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_C)){
		do_toggle(chronicle);
		if(chronicle) print("~g~KB: ~w~Chronicle ~b~ON");
		else print("~g~KB: ~w~Chronicle ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_B)){
		do_toggle(bikefly);
		if(bikefly) print("~g~KB: ~w~Super Bike ~b~ON");
		else print("~g~KB: ~w~Super Bike ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_M)){
		do_toggle(modderprotect);
		if(modderprotect) print("~g~KB: ~w~Modder Protection ~b~ON");
		else print("~g~KB: ~w~Modder Protection ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_D)){
		if(!rocketgun) print("~g~Shoot the Deagle to fire rockets.");
		if(!rocketgun){
			GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_DEAGLE, AMMO_MAX, 0);
			SET_CURRENT_CHAR_WEAPON(pPlayer, WEAPON_DEAGLE, true);
		}
		else{
			for(i = 0;i <= 1;i++) if(DOES_CHAR_EXIST(rocketped[i])) DELETE_CHAR(&rocketped[i]);
		}
		do_toggle(rocketgun);
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_X)){
		do_toggle(rocket);
		if(rocket) print("~g~KB: ~w~RocketMan ~b~ON");
		else print("~g~KB: ~w~RocketMan ~r~OFF");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_T)){
		teleport_char(pPlayer,savex,savey,savez+1);
		print("~g~KB: ~w~Teleported to saved location");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_L)){
		if(!cargun){
			print("~g~KB: ~w~Car Launcher ~b~ON");
			GIVE_WEAPON_TO_CHAR(pPlayer, WEAPON_DEAGLE, AMMO_MAX, 0);
			SET_CURRENT_CHAR_WEAPON(pPlayer, WEAPON_DEAGLE, true);	
		}
		else print("~g~KB: ~w~Car Launcher ~r~OFF");
		do_toggle(cargun);
		return;
	}
	
	//teleports
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_1)){
		if(DOES_BLIP_EXIST(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT))){
			GET_BLIP_COORDS(GET_FIRST_BLIP_INFO_ID(BLIP_WAYPOINT),&spawn);
			GET_GROUND_Z_FOR_3D_COORD(spawn.x,spawn.y,spawn.z,&z);
			teleport_char(pPlayer,spawn.x,spawn.y,(z + 5.0));
			print("~g~KB: ~w~Teleported to Waypoint");
		}
		else print("~g~KB: ~w~You have to set a Waypoint");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_2)){
		teleport_char(pPlayer,2175.3516,761.2235,30.0);
		print("~g~KB: ~w~Teleported to the Airport");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_3)){
		teleport_char(pPlayer,-178.2,582.6,126.85);
		print("~g~KB: ~w~Teleported to the Majestic Hotel");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_4)){
		teleport_char(pPlayer,-415.17,1463.54,39.0);
		print("~g~KB: ~w~Teleported to the Playboy X Pad");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_5)){
		teleport_char(pPlayer,-279.77,-99.66,386.791);
		print("~g~KB: ~w~Teleported to the Empire State building");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_6)){
		teleport_char(pPlayer,-1079.8,-469.7,2.62);
		print("~g~KB: ~w~Teleported to the Prison");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_7)){
		teleport_char(pPlayer,-3.4734,270.6067,-2.9470);
		print("~g~KB: ~w~Teleported to the Subway");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_8)){
		teleport_char(pPlayer,-1539.8414,163.2967,9.9000);
		print("~g~KB: ~w~Teleported to the Sprunk Factory");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_9)){
		teleport_char(pPlayer,237.5457,-805.6555,13.7);
		print("~g~KB: ~w~Teleported to the Construction Yard");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_SPACE)){
		xmc_teleportinfront();
		print("~g~KB: ~w~Teleported in front");
		return;
	}
	else if(IS_GAME_KEYBOARD_KEY_JUST_PRESSED(KEY_0)){
		GET_CHAR_COORDINATES(pPlayer,&x, &y, &z);
		pveh = GET_CLOSEST_CAR(x,y,z, 50, false, 70);
		if(!DOES_VEHICLE_EXIST(pveh))
		pveh = GET_CLOSEST_CAR(x,y,z, 50, false, 71);
		if(!DOES_VEHICLE_EXIST(pveh))
		pveh = GET_CLOSEST_CAR(x,y,z, 50, false, 69);
		if(!DOES_VEHICLE_EXIST(pveh)){
			print("~g~KB: ~r~No Car found.");
			return;
		}
		GET_DRIVER_OF_CAR(pveh,&driver);
		if(!DOES_CHAR_EXIST(driver)){
			WARP_CHAR_INTO_CAR(pPlayer,pveh);
			print("~g~KB: ~w~Teleported into Nearest Car as Driver");
		}
		else{
			for(i = 0;i <= 2;i++){
				if(IS_CAR_PASSENGER_SEAT_FREE(pveh,i)){
					WARP_CHAR_INTO_CAR_AS_PASSENGER(pPlayer,pveh,i);
					print("~g~KB: ~w~Teleported into Nearest Car as Passenger");
				}
			}
		}
		return;
	}
	return;
}