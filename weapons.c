void taser_gun(void){
	if(GET_PLAYER_ID() == GET_HOST_ID()){
		print("~r~You can't be Host");
	//	taser = false;
		reset_menu();
		return;
	}
	for(i = 0; i<16; i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if (i == GetPlayerIndex()) continue;
		GET_PLAYER_CHAR(i, &online_char);
		if(!DOES_CHAR_EXIST(online_char)) continue;
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if(wep == WEAPON_PISTOL){
			if(HAS_CHAR_BEEN_DAMAGED_BY_CHAR(online_char, pPlayer, false)){
				if(HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(online_char, WEAPON_PISTOL)){
					GET_CHAR_COORDINATES(online_char,&x,&y,&z);
					ADD_EXPLOSION(x,y,z,EXPLOSION_DIR_WATER_HYDRANT,35.0,false,true,0.0);
					GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(online_char,0,1,0,&x,&y,&z);
					ADD_EXPLOSION(x,y,z,EXPLOSION_DIR_WATER_HYDRANT,35.0,false,true,0.0);
				}
			}
		}
	}
}

void dragon_gun(void){
	for(i = 0; i<16; i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if (i == GetPlayerIndex()) continue;
		GET_PLAYER_CHAR(i, &online_char);
		if(!DOES_CHAR_EXIST(online_char)) continue;
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if(wep == WEAPON_BARETTA){
			if(HAS_CHAR_BEEN_DAMAGED_BY_CHAR(online_char, pPlayer, false)){
				if(HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(online_char, WEAPON_BARETTA)){
					GET_CHAR_COORDINATES(online_char,&x,&y,&z);
					ADD_EXPLOSION(x,y,z,EXPLOSION_MOLOTOV,35.0,false,false,0.0);
					START_CHAR_FIRE(online_char);
					CLEAR_CHAR_LAST_DAMAGE_ENTITY(online_char);
					CLEAR_CHAR_LAST_WEAPON_DAMAGE(pPlayer);
				}
			}
		}
	}
}

void pow_gun(void){
	for(i = 0; i<16; i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if (i == GetPlayerIndex()) continue;
		GET_PLAYER_CHAR(i, &online_char);
		if(!DOES_CHAR_EXIST(online_char)) continue;
		GET_CURRENT_CHAR_WEAPON(pPlayer, &wep);
		if(wep == WEAPON_PISTOL){
			if(HAS_CHAR_BEEN_DAMAGED_BY_CHAR(online_char, pPlayer, false)){
				if(HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(online_char, WEAPON_PISTOL)){
					GET_CHAR_COORDINATES(online_char,&x,&y,&z);
					ADD_EXPLOSION(x,y,z,EXPLOSION_GRENADE,35.0,false,false,0.0);
					CLEAR_CHAR_LAST_DAMAGE_ENTITY(online_char);
					CLEAR_CHAR_LAST_WEAPON_DAMAGE(pPlayer);
				}
			}
		}
	}
}

void freeze_gun(void){
	for(i = 0; i<16; i++){
		if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
		if (i == GetPlayerIndex()) continue;
		GET_PLAYER_CHAR(i, &online_char);
		if(!DOES_CHAR_EXIST(online_char)) continue;
		if(HAS_CHAR_BEEN_DAMAGED_BY_CHAR(online_char, pPlayer, false)){
			if(HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(online_char, WEAPON_DEAGLE)){
				GET_CHAR_COORDINATES(online_char,&x,&y,&z);
			//	GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(online_char,0,1,0,&x,&y,&z);
				REMOVE_ALL_CHAR_WEAPONS(online_char);
				WAIT(10);
				GIVE_WEAPON_TO_CHAR(online_char,WEAPON_ROCKET,AMMO_MAX,false);
			}
		}
	}
}

void car_shoot(Ped pPed){
	if(del_cargun){
		if(DOES_VEHICLE_EXIST(CarProjectile)){
			GET_NETWORK_ID_FROM_VEHICLE(CarProjectile, &nvid);
			SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			tick = 0;
			while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
				tick++;
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				if(tick >= 250){
					break;
				}
				WAIT(0);
			}
			GET_CHAR_COORDINATES(pPed, &x, &y, &z);
			SET_CAR_COORDINATES(CarProjectile, x,y,z);
			DELETE_CAR(&CarProjectile);
			MARK_CAR_AS_NO_LONGER_NEEDED(&CarProjectile);
		}
	}
	
	GET_PED_BONE_POSITION(pPed, BONE_RIGHT_HAND, 100, 0, 0, &aim);
	GET_PED_BONE_POSITION(pPed, BONE_RIGHT_HAND, 5, 0, 0, &spawn);
	force.x = (aim.x - spawn.x) / 95 * 2000;
	force.y = (aim.y - spawn.y) / 95 * 2000;
	force.z = (aim.z - spawn.z) / 95 * 2000;
		
	REQUEST_MODEL(car_launch);
	while(!HAS_MODEL_LOADED(car_launch)) WAIT(0);
	
	if(grond_cargun) CREATE_CAR(car_launch, spawn.x, spawn.y, spawn.z, &CarProjectile, 1);
	else CREATE_CAR(car_launch, spawn.x, spawn.y, spawn.z, &CarProjectile, 1);
	GET_NETWORK_ID_FROM_VEHICLE(CarProjectile, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, 0);
	SET_CAR_VISIBLE(CarProjectile, 0);
	MARK_MODEL_AS_NO_LONGER_NEEDED(car_launch);
	GET_CHAR_HEADING(pPed, &heading);
	if(DOES_VEHICLE_EXIST(CarProjectile)){
		if(strat_cargun){
			SET_CAR_HEADING(CarProjectile, heading);
		}
		else{
			if(heading > 180.0) heading -= 90.0;
			else heading += 90.0;
			SET_CAR_HEADING(CarProjectile, heading);
		}
		SET_CAR_PROOFS(CarProjectile, true, true, true, true, true);
		FREEZE_CAR_POSITION(CarProjectile,false);
		SET_CAR_COLLISION(CarProjectile, true);
		if(grond_cargun) SET_CAR_ON_GROUND_PROPERLY(CarProjectile);
		if(exp_cargun) SET_PETROL_TANK_HEALTH(CarProjectile, -1);
		WAIT(100);
		SET_CAR_VISIBLE(CarProjectile, 1);
	//	if(grond_cargun) APPLY_FORCE_TO_CAR(CarProjectile, 1, force.x, force.y, -100, 0.0, 0.0, 0.0, 1, 0, 1, 1);
		if(grond_cargun) APPLY_FORCE_TO_CAR(CarProjectile, 1, force.x, force.y, -1.0, 0.0, 0.0, 0.0, 1, 0, 1, 1);
		else APPLY_FORCE_TO_CAR(CarProjectile, 1, force.x, force.y, force.z, 0.0, 0.0, 0.0, 1, 0, 1, 1);
	//	APPLY_FORCE_TO_CAR(CarProjectile, 1, 0.0, 500.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1);
	}
}

void inferno_shoot(void){
	speed = 0;
	REQUEST_ANIMS("mini_bowling");
	while(!HAVE_ANIMS_LOADED("mini_bowling")) WAIT(0);
	TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"shot","mini_bowling",8.0,0,0);
	WAIT(700);
	for(i = 0;i <= 10;i++){
		speed += 2.0;
		GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, speed, 0, &x, &y, &z);
		ADD_EXPLOSION(x,y,z,EXPLOSION_MOLOTOV,35.0,false,false,0.0);
	}
	print("Fire field! (Fire textures may not load sometimes)");
	return;
}

void chronicle_shoot(void){
	speed = 0;
	if(!IS_CHAR_IN_ANY_CAR(pPlayer)){
		REQUEST_ANIMS("ped");
		while(!HAVE_ANIMS_LOADED("ped")) WAIT(0);
		TASK_PLAY_ANIM_WITH_FLAGS(pPlayer,"run_open_door_shove","ped",8.0,0,0);
		WAIT(500);
	}
	for(i = 0;i <= 25;i++){
		speed += 10.0;
		GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPlayer, 0, speed, 0, &x, &y, &z);
		ADD_EXPLOSION(x,y,z,EXPLOSION_SHIP_DESTROY,35.0,false,true,0.0);
	}
	print("Super blast!");
	return;
}

void object_shoot(void){
	float prjX, prjY, prjZ, prjT, gcX, gcY, gcZ, gcrotX, gcrotY, gcrotZ, objrotX, objrotZ;
	Camera game_cam;
	
	GET_GAME_CAM(&game_cam);
	if (IS_CAM_ACTIVE(game_cam)){
		GET_CAM_ROT(game_cam, &gcrotX, &gcrotY, &gcrotZ);// used for setting the object rotation and for some weird trig stuff below
		GET_CAM_POS(game_cam, &gcX, &gcY, &gcZ);// used for the spawn point of the object, because the player is offset while aiming
		if (gcrotX < 0.0)// the range for cam rot is -180 to 180, to set object rot we need 0 to 360
		{
			objrotX = gcrotX + 360.0;
		}
		else
		{
			objrotX = gcrotX;
		}
		if (gcrotZ < 0.0)
		{
			objrotZ = gcrotZ + 360.0;
		}
		else
		{
			objrotZ = gcrotZ;
		}
		/*  the trig stuff below could possibly be replaced with vectors, I have no idea how to do that though.  *
		*   I apologize if this is confusing, but if you want to change the distance from the game_cam that the  *
		*   object is spawned, adjust "3.0" to your preference on the first and fourth lines.  Also prjT is the  *
		*   adjacent side from the pitch calculation, its purpose is to be the tangent in the following 2 lines */
		prjT = (3.0 * COS(gcrotX));       // adj side calculation to be used as a tangent below
		prjX = gcX - (prjT * SIN(gcrotZ));// calculates how far to spawn the object from the game_cam on the X plane
		prjY = gcY + (prjT * COS(gcrotZ));// calculates how far to spawn the object from the game_cam on the Y plane
		prjZ = gcZ + (3.0 * SIN(gcrotX)); // calculates how far to spawn the object from the game_cam on the Z plane
	}
	if(del_objgun){
		if(DOES_OBJECT_EXIST(ObjectProjectile)){
			
			GET_NETWORK_ID_FROM_OBJECT(ObjectProjectile, &nvid);
			SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
			REQUEST_CONTROL_OF_NETWORK_ID(nvid);
			tick = 0;
			while(!HAS_CONTROL_OF_NETWORK_ID(nvid)){
				tick++;
				REQUEST_CONTROL_OF_NETWORK_ID(nvid);
				if(tick >= 250){
					break;
				}
				WAIT(0);
			}
			GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
			SET_OBJECT_COORDINATES(ObjectProjectile, x,y,z);
			DELETE_OBJECT(&ObjectProjectile);
		}
	}

	REQUEST_MODEL(object_launch);
	while(!HAS_MODEL_LOADED(object_launch)) WAIT(0);

	CREATE_OBJECT(object_launch, prjX, prjY, prjZ, &ObjectProjectile, 1);
	GET_NETWORK_ID_FROM_OBJECT(ObjectProjectile, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, 0);
	SET_OBJECT_VISIBLE(ObjectProjectile, 0);
	MARK_MODEL_AS_NO_LONGER_NEEDED(object_launch);
	if(DOES_OBJECT_EXIST(ObjectProjectile)){
		SET_OBJECT_QUATERNION(ObjectProjectile,0,0,0,0);
		SET_OBJECT_INVINCIBLE(ObjectProjectile,false);
		FREEZE_OBJECT_POSITION(ObjectProjectile,false);
		SET_OBJECT_DYNAMIC(ObjectProjectile,true);
		SET_OBJECT_AS_STEALABLE(ObjectProjectile,true);
		SET_OBJECT_ROTATION(ObjectProjectile, objrotX, 0.0, objrotZ);
		SET_OBJECT_COLLISION(ObjectProjectile, true);
		WAIT(100);
		SET_OBJECT_VISIBLE(ObjectProjectile, 1);
		APPLY_FORCE_TO_OBJECT(ObjectProjectile, 1, 0.0, 1000.0, 0.0, 0.0, 0.0, 0.0, 1, 1, 1, 1);
	}
}

void ped_shoot(void){
	if(DOES_CHAR_EXIST(CharProjectile)){
		GET_NETWORK_ID_FROM_PED(CharProjectile, &nvid);
		SET_NETWORK_ID_CAN_MIGRATE(nvid, true);
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
		GET_CHAR_COORDINATES(pPlayer, &x, &y, &z);
		SET_CHAR_COORDINATES(CharProjectile, x,y,z);
		DELETE_CHAR(&CharProjectile);
	}
	
	GET_PED_BONE_POSITION(pPlayer, BONE_RIGHT_HAND, 100, 0, 0, &aim);
	GET_PED_BONE_POSITION(pPlayer, BONE_RIGHT_HAND, 5, 0, 0, &spawn);
	force.x = (aim.x - spawn.x) / 95 * 2000;
	force.y = (aim.y - spawn.y) / 95 * 2000;
	force.z = (aim.z - spawn.z) / 95 * 2000;
	
	CREATE_RANDOM_CHAR(spawn.x, spawn.y, spawn.z - 1, &CharProjectile);
	GET_NETWORK_ID_FROM_PED(CharProjectile, &nvid);
	SET_NETWORK_ID_CAN_MIGRATE(nvid, 0);
	SET_CHAR_VISIBLE(CharProjectile, 0);
	if(DOES_CHAR_EXIST(CharProjectile)){
		SET_CHAR_PROOFS(CharProjectile, true, true, true, true, true);
		FREEZE_CHAR_POSITION(CharProjectile,false);
		SET_CHAR_COLLISION(CharProjectile, true);
		WAIT(100);
		SET_CHAR_VISIBLE(CharProjectile, 1);
		APPLY_FORCE_TO_PED(CharProjectile, 1, force.x, force.y, force.z, 0.0, 0.0, 0.0, 1, 0, 1, 1);
	}
}

void rocket_deagle(Ped pPed){
	if(DOES_CHAR_EXIST(pPed)){
		i = 2;
		if(DOES_CHAR_EXIST(rocketped[i])) DELETE_CHAR(&rocketped[i]);
		WAIT(10);
		if(!(DOES_CHAR_EXIST(rocketped[i]))){
				GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 0, 2, 0, &x, &y, &z);
				CREATE_RANDOM_CHAR(x,y,z,&rocketped[i]);
				GET_NETWORK_ID_FROM_PED(rocketped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
				SET_CHAR_ACCURACY(rocketped[i], 100);
				SET_CHAR_VISIBLE(rocketped[i],false);
				SET_CHAR_COLLISION(rocketped[i],false);
				SET_CHAR_KEEP_TASK(rocketped[i], true);
				SET_SENSE_RANGE(rocketped[i], 200.0);
				SET_PED_GENERATES_DEAD_BODY_EVENTS(rocketped[i], true);
				//	SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(gameped[i], true);
				SET_CHAR_SHOOT_RATE(rocketped[i], 100);
				SET_CHAR_WILL_USE_COVER(rocketped[i], false);
				SET_CHAR_WILL_DO_DRIVEBYS(rocketped[i], false);
				SET_CHAR_SIGNAL_AFTER_KILL(rocketped[i], true);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(rocketped[i], false);
				SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(rocketped[i], false);
				SET_CHAR_INVINCIBLE(rocketped[i], true);
				SET_CHAR_PROOFS(rocketped[i], true, true, true, true, true);
				SET_CHAR_PROVIDE_COVERING_FIRE(rocketped[i], false);
				SET_CHAR_CANT_BE_DRAGGED_OUT(rocketped[i], true);
				SET_CHAR_STAY_IN_CAR_WHEN_JACKED(rocketped[i], true);
				SET_PED_DONT_DO_EVASIVE_DIVES(rocketped[i], true);
				SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT(rocketped[i], true);
				SET_PED_PATH_MAY_DROP_FROM_HEIGHT(rocketped[i], false);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(rocketped[i], false);
				SET_PED_PATH_MAY_USE_LADDERS(rocketped[i], false);
				WAIT(10);
		}
		if(DOES_CHAR_EXIST(rocketped[i])){
			UpdateWeaponOfPed(rocketped[i], WEAPON_RLAUNCHER);
			SET_CURRENT_CHAR_WEAPON(rocketped[i], WEAPON_RLAUNCHER, true);
			SET_CHAR_AMMO(rocketped[i], WEAPON_RLAUNCHER, 1);
			SET_AMMO_IN_CLIP(rocketped[i],WEAPON_RLAUNCHER,1);
		}
		GET_PED_BONE_POSITION(pPed, BONE_RIGHT_HAND, 100.0, 5.0, -20.0, &aim);
		if(DOES_CHAR_EXIST(rocketped[i])) FIRE_PED_WEAPON(rocketped[i],aim.x,aim.y,aim.z - 3.0);
		WAIT(100);
		if(DOES_CHAR_EXIST(rocketped[i])) DELETE_CHAR(&rocketped[i]);
	}
	return;
}

void rocket_shoot(Ped pPed, uint direction){
	if(DOES_CHAR_EXIST(pPed)){
		for(i = 0;i <= 1;i++) if(DOES_CHAR_EXIST(rocketped[i])) DELETE_CHAR(&rocketped[i]);
		if(DOES_OBJECT_EXIST(otmp)) DELETE_OBJECT(&otmp);
		WAIT(10);
		if(!(DOES_CHAR_EXIST(rocketped[0]) && DOES_CHAR_EXIST(rocketped[1]))){
			if(!DOES_OBJECT_EXIST(otmp)){
				CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&otmp,true);
				GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
				SET_OBJECT_VISIBLE(otmp, false);
				SET_OBJECT_COLLISION(otmp, false);
				ATTACH_OBJECT_TO_PED(otmp,pPed,0,0.0,0.0,0,0.0,0.0,0.0,false);
			}
			for(i = 0;i <= 1;i++){
				if(i == 0) GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 2.5, 0, 0, &x, &y, &z);
				else GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, -2.5, 0, 0, &x, &y, &z);
				CREATE_RANDOM_CHAR(x,y,z,&rocketped[i]);
				GET_NETWORK_ID_FROM_PED(rocketped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
				SET_CHAR_ACCURACY(rocketped[i], 100);
				SET_CHAR_VISIBLE(rocketped[i],false);
				SET_CHAR_COLLISION(rocketped[i],false);
				SET_CHAR_KEEP_TASK(rocketped[i], true);
				SET_SENSE_RANGE(rocketped[i], 200.0);
				SET_PED_GENERATES_DEAD_BODY_EVENTS(rocketped[i], true);
				//	SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(gameped[i], true);
				SET_CHAR_SHOOT_RATE(rocketped[i], 100);
				SET_CHAR_WILL_USE_COVER(rocketped[i], false);
				SET_CHAR_WILL_DO_DRIVEBYS(rocketped[i], false);
				SET_CHAR_SIGNAL_AFTER_KILL(rocketped[i], true);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(rocketped[i], false);
				SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(rocketped[i], false);
				SET_CHAR_INVINCIBLE(rocketped[i], true);
				SET_CHAR_PROOFS(rocketped[i], true, true, true, true, true);
				SET_CHAR_PROVIDE_COVERING_FIRE(rocketped[i], false);
				SET_CHAR_CANT_BE_DRAGGED_OUT(rocketped[i], true);
				SET_CHAR_STAY_IN_CAR_WHEN_JACKED(rocketped[i], true);
				SET_PED_DONT_DO_EVASIVE_DIVES(rocketped[i], true);
				SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT(rocketped[i], true);
				SET_PED_PATH_MAY_DROP_FROM_HEIGHT(rocketped[i], false);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(rocketped[i], false);
				SET_PED_PATH_MAY_USE_LADDERS(rocketped[i], false);
				WAIT(10);
				if(i == 0) ATTACH_PED_TO_OBJECT(rocketped[i],otmp,0,2.5,0.0,0,0,0,0,0);
				else ATTACH_PED_TO_OBJECT(rocketped[i],otmp,0,-2.5,0.0,0,0,0,0,0);
			}
		}
		for(i = 0;i <= 1;i++){
			if(DOES_CHAR_EXIST(rocketped[i])){
				UpdateWeaponOfPed(rocketped[i], WEAPON_RLAUNCHER);
				SET_CURRENT_CHAR_WEAPON(rocketped[i], WEAPON_RLAUNCHER, true);
				SET_CHAR_AMMO(rocketped[i], WEAPON_RLAUNCHER, 1);
				SET_AMMO_IN_CLIP(rocketped[i],WEAPON_RLAUNCHER,1);
			}
		}
		if(direction == -1) GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 0, -60, 0, &x, &y, &z);
		else if(direction == 0) GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 0, 60, 0, &x, &y, &z);
		else if(direction == 1) GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, -60, 30, 0, &x, &y, &z);
		else if(direction == 2) GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(pPed, 60, 30, 0, &x, &y, &z);
		for(i = 0;i <= 1;i++) if(DOES_CHAR_EXIST(rocketped[i])) FIRE_PED_WEAPON(rocketped[i],x,y,z);
		WAIT(50);
	}
	return;
}

void rocketveh_shoot(Vehicle vehicle){
	if(DOES_VEHICLE_EXIST(vehicle)){
		for(i = 0;i <= 1;i++) if(DOES_CHAR_EXIST(rocketped[i])) DELETE_CHAR(&rocketped[i]);
		if(DOES_OBJECT_EXIST(otmp)) DELETE_OBJECT(&otmp);
		WAIT(10);
		if(!(DOES_CHAR_EXIST(rocketped[0]) && DOES_CHAR_EXIST(rocketped[1]))){
			if(!DOES_OBJECT_EXIST(otmp)){
				CREATE_OBJECT(MODEL_CJ_GOLF_BALL,0.0,0.0,0.0,&otmp,true);
				GET_NETWORK_ID_FROM_OBJECT(otmp, &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
				SET_OBJECT_VISIBLE(otmp, false);
				SET_OBJECT_COLLISION(otmp, false);
				ATTACH_OBJECT_TO_CAR(otmp,vehicle,0.0,0.0,0,0.0,0.0,0.0,false);
			}
			for(i = 0;i <= 1;i++){
				if(i == 0) GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(vehicle, 3.0, 0, 0, &x, &y, &z);
				else GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(vehicle, -3.0, 0, 0, &x, &y, &z);
				CREATE_RANDOM_CHAR(x,y,z,&rocketped[i]);
				GET_NETWORK_ID_FROM_PED(rocketped[i], &nvid);
				SET_NETWORK_ID_CAN_MIGRATE(nvid, false);
				SET_CHAR_ACCURACY(rocketped[i], 100);
				SET_CHAR_COLLISION(rocketped[i],false);
				SET_CHAR_VISIBLE(rocketped[i],false);
				SET_CHAR_KEEP_TASK(rocketped[i], true);
				SET_SENSE_RANGE(rocketped[i], 200.0);
				SET_PED_GENERATES_DEAD_BODY_EVENTS(rocketped[i], true);
				//	SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(gameped[i], true);
				SET_CHAR_SHOOT_RATE(rocketped[i], 100);
				SET_CHAR_WILL_USE_COVER(rocketped[i], false);
				SET_CHAR_WILL_DO_DRIVEBYS(rocketped[i], false);
				SET_CHAR_SIGNAL_AFTER_KILL(rocketped[i], true);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(rocketped[i], false);
				SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(rocketped[i], false);
				SET_CHAR_INVINCIBLE(rocketped[i], true);
				SET_CHAR_PROOFS(rocketped[i], true, true, true, true, true);
				SET_CHAR_PROVIDE_COVERING_FIRE(rocketped[i], false);
				SET_CHAR_CANT_BE_DRAGGED_OUT(rocketped[i], true);
				SET_CHAR_STAY_IN_CAR_WHEN_JACKED(rocketped[i], true);
				SET_PED_DONT_DO_EVASIVE_DIVES(rocketped[i], true);
				SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT(rocketped[i], true);
				SET_PED_PATH_MAY_DROP_FROM_HEIGHT(rocketped[i], false);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(rocketped[i], false);
				SET_PED_PATH_MAY_USE_LADDERS(rocketped[i], false);
				WAIT(10);
				if(i == 0) ATTACH_PED_TO_OBJECT(rocketped[i],otmp,0,2.5,0.0,0,0,0,0,0);
				else ATTACH_PED_TO_OBJECT(rocketped[i],otmp,0,-2.5,0.0,0,0,0,0,0);
			}
		}
		for(i = 0;i <= 1;i++){
			if(DOES_CHAR_EXIST(rocketped[i])){
				UpdateWeaponOfPed(rocketped[i], WEAPON_RLAUNCHER);
				SET_CURRENT_CHAR_WEAPON(rocketped[i], WEAPON_RLAUNCHER, true);
				SET_CHAR_AMMO(rocketped[i], WEAPON_RLAUNCHER, 1);
				SET_AMMO_IN_CLIP(rocketped[i],WEAPON_RLAUNCHER,1);
			}
		}
		GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(vehicle, 0, 60, 0, &x, &y, &z);
		for(i = 0;i <= 1;i++) if(DOES_CHAR_EXIST(rocketped[i])) FIRE_PED_WEAPON(rocketped[i],x,y,z);
		WAIT(50);
	}
	return;
}