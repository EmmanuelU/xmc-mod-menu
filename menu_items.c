/**
	Menu items config
	ENGLISH
	Orig. by: Herr Muskelprotze
	by: Emmanuel Utomi
	
**/

void add_item(char* item,bool act){
	item_count++;
	menu[item_count].item_name = item;
	menu[item_count].action = act;
}

void add_toggle(char* item,bool pointer){
	item_count++;
	menu[item_count].item_name = item;
	menu[item_count].action = true;
	menu[item_count].type = 1;
	menu[item_count].value = pointer;
}

void add_number(char* item,int maxvalue){
	item_count++;
	menu[item_count].item_name = item;
	menu[item_count].action = true;
	menu[item_count].type = 2;
	menu[item_count].value = 1;
	menu[item_count].maxval = maxvalue;
}

void add_gxt_hash(int model_hash){
	item_count++;
	menu[item_count].item_name = " ";
	menu[item_count].action = true;
	menu[item_count].type = 3;
	menu[item_count].value = model_hash;
}

void add_online_player(char* playername ,uint playerid,bool act)
{
	item_count++;
	menu[item_count].item_name = playername;
	menu[item_count].action = act;
	menu[item_count].type = 4;
	menu[item_count].value = playerid;
}

void add_online_player_admin(char* playername ,uint playerid)
{
	item_count++;
	menu[item_count].item_name = playername;
	menu[item_count].action = false;
	menu[item_count].type = 5;
	menu[item_count].value = playerid;
}

void menu_setup(void){
	item_count = 0;
	footer = " ";
	if(menu_level == 0){
		footer = MENU_TITLE;
		add_item("Player Options",false);
		add_item("Vehicle Options",false);
		add_item("Weapon Options",false);
		add_item("Teleports",false);
		add_item("Misc",false);
		add_item("Mod Loader",false);
		add_item("Credits",false);
		return;
	}
	if(menu_level == 1){
		if(last_selected[0] == 1){
			footer = "Player Options";
			add_item("Online Players",false);
			add_item("Character",false);
			add_item("Give Health & Armor",true);
			add_toggle("God Mode",godmode);
			add_toggle("Never Wanted",neverwanted);
			add_toggle("Smart protection",pprotection);
			add_toggle("Super Run  ~PAD_LB~ + ~PAD_A~",superrun);
			add_toggle("Super Hops  ~PAD_LB~ + ~PAD_X~",superjump);
			add_toggle("Chronicle  ~PAD_LB~ + ~PAD_B~",chronicle);
			add_toggle("Visibility",IS_CHAR_VISIBLE(pPlayer));
			add_toggle("Burn",IS_CHAR_ON_FIRE(pPlayer));
			add_item("Bodyguards",false);
			add_toggle("Inferno  ~PAD_LB~ + ~PAD_B~",inferno);
			add_toggle("Walk/Drive on Water",vehwater);
			add_toggle("RocketMan  ~PAD_RB~ + ~PAD_DPAD_ALL~",rocket);
			add_item("Location",false);
			return;
		}
		if(last_selected[0] == 2){
			footer = "Vehicle Options";
			add_item("Car Garage",false);
			add_toggle("Vehicle Helper",vhelper);
			add_item("Slingshot",true);
			add_toggle("Super Glue",carsonground);
			add_toggle("Super Speed",nfs);
			add_toggle("Immobile Car",freezecar);
			add_toggle("Non-Collision",collision);
			add_toggle("Super Bike",bikefly);
			add_item("Kill Passengers",true);
			add_item("Delete Vehicle",true);
			add_item("Flip Vehicle",true);
			add_item("Eject from Vehicle",true);
			add_item("Kick Players out of Car",true);
			add_toggle("Heli Bomb  ~PAD_LSTICK_NONE~",helistrike);
			add_item("Shuffle Car seats",true);
			add_toggle("Invisibilty",vehinvis);
			add_item("Super Lock/Unlock Car",true);
			add_toggle("Auto Flip Car",autoflip);
			return;
		}
		if(last_selected[0] == 3){
			footer = "Weapon Options";
			add_item("Weapon Selector",false);
			add_toggle("Fast Reload",fastreload);
			add_toggle("Auto Aim",autoaim);
			add_item("Object Launcher",false);
			add_toggle("Rapid Fire",rapidfire);
			add_item("Car Launcher",false);
			add_toggle("Pow Glock",powgun);
			add_toggle("Ped Launcher",pedgun);
			add_toggle("Rocket Deagle",rocketgun);
			add_toggle("Weapon Visibilty",wepvisible);
			add_item("Give P90 (for in car use)",true);
			add_toggle("DragonsBreathe Berretta",dragongun);
			return;
		}
		if(last_selected[0] == 4){
			footer = "Teleports";
			add_item("Waypoint",true);
			add_item("Airport Helipads",true);
			add_item("Hove Beach",true);
			add_item("Majestic Hotel",true);
			add_item("Middle Park",true);
			add_item("Playboy X's Pad",true);
			add_item("Rotterdam Tower",true);
			add_item("Prison Cage",true);
			add_item("Crack House",true);
			add_item("Westminster Towers",true);
			add_item("Underground Garage",true);
			add_item("Algonquin Safe House",true);
			add_item("Scrapyard",true);
			add_item("Construction Site",true);
			add_item("Subway",true);
			add_item("Sprunk Factory",true);
			add_item("TBOGT Fight Cage",true);
			add_item("In front",true);
			add_item("In Nearest Car",true);
			return;
		}
		if(last_selected[0] == 5){
			footer = "Misc";
			add_item("Menu Options",false);
			add_item("Throwable Objects",false);
			add_item("Air Strikes",false);
			add_toggle("Drive Free",drive_free);
			add_item("Join New Freemode",true);
			add_item("Return to Single Player",true);
			add_item("Get name of host",true);
			add_toggle("Modder Protection",modderprotect);
			add_item("Unlock Achievements",true);
			add_toggle("Zero Gravity",gravity);
			add_item("Clear Nearby Cars",true);
			add_item("Clear Nearby Peds",true);
			add_item("Radio Anywhere",false);
			add_toggle("Slow Motion",slowmotion);
			add_item("Weather",false);
			add_item("Concrete Barricade",true);
			add_item("Camera",false);
			add_item("Clear Nearby Objects",true);
			add_item("Escorts",false);
			return;
		}
		if(last_selected[0] == 6){
			footer = "Mod Loader";
			add_toggle("Mod Slot 1  - xmc1.sco",xmc1);
			add_toggle("Mod Slot 2  - xmc2.sco",xmc2);
			add_toggle("Mod Slot 3  - xmc3.sco",xmc3);
			add_toggle("Mod Slot 4  - xmc4.sco",xmc4);
			add_toggle("Mod Slot 5  - xmc5.sco",xmc5);
			add_toggle("Mod Slot 6  - xmc6.sco",xmc6);
			add_toggle("Mod Slot 7  - xmc7.sco",xmc7);
			add_toggle("Mod Slot 8  - xmc8.sco",xmc8);
			add_toggle("Mod Slot 9  - xmc9.sco",xmc9);
			add_toggle("Mod Slot 10 - xmc10.sco",xmc10);
			add_toggle("Mod Slot 11 - xmc11.sco",xmc11);
			add_toggle("Mod Slot 12 - xmc12.sco",xmc12);
			add_toggle("Mod Slot 13 - xmc13.sco",xmc13);
			add_toggle("Mod Slot 14 - xmc14.sco",xmc14);
			add_toggle("Mod Slot 15 - xmc15.sco",xmc15);
			add_toggle("Mod Slot 16 - xmc16.sco",xmc16);
			add_toggle("Mod Slot 17 - xmc17.sco",xmc17);
			add_toggle("Mod Slot 18 - xmc18.sco",xmc18);
			return;
		}
		if(last_selected[0] == 7){
			footer = "Credits: Devs & Testers";
			add_item("^^^ Emmanuel Utomi ^^^",true);
			add_item("Muskelprotze",true);
			add_item("PSX Developer Team",true);
			add_item("Keredor",true);
			add_item("Buffeting",true);
			add_item("Chr0m3 x Modz & NayJames123",true);
			add_item("Evade & Lavaman",true);
			add_item("Eaqz & BoubouVirus",true);
			add_item("Duck/Rockstar London",true);
			add_item("Despo/Soft Dusty",true);
			add_item("Big Fish 500 & The Producer",true);
			add_item("L33t Hax/Stuart",true);
			add_item("Goddess & o M A F I A o",true);
			add_item("iM Jack v & Pmaster10",true);
			add_item("GTA JORDOSKY1 & xI iTz TOAST Ix",true);
			add_item("CR4ZYCOOKIE & Lil Deadman V2",true);
			return;
		}
	}
	if(menu_level == 2){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				footer = "Online Players";
				player_count = 0;
				for(i = 0;i < 16;i++){
					if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
					if(GET_PLAYER_ID() == i) continue;
					GET_PLAYER_CHAR(i,&online_char);
					players[player_count].ped = online_char;
					players[player_count].gamertag = GET_PLAYER_NAME(i);
					players[player_count].id = i;
					player_count++;
				}
				
				if(player_count > 0){
					add_item("All Players",false);
					add_item("Shortcut Players",false);
					for(i = 0;i <= player_count;i++){
						if(IS_NETWORK_PLAYER_ACTIVE(players[i].id)){
							if(GET_PLAYER_ID() == players[i].id) continue;
							if(is_admin(players[i].id)) add_online_player_admin(players[i].gamertag,players[i].id);
							else if(xmc_online_col) add_online_player(players[i].gamertag,players[i].id,false);
							else add_item(players[i].gamertag,false);
						}
					}
				}
				else add_item("Game is empty",true);
				return;
			}
			if(last_selected[1] == 2){
				footer = "Character";
				add_item("Anims",false);
				add_item("Speeches",false);
				add_item("Stop All Tasks/Attachments",true);
				add_toggle("Ragdoll  ~PAD_LB~ + ~PAD_B~",ragdoll);
				add_item("Give Money",true);
				add_item("Add HeadGear",true);
				add_item("Change Clothes",true);
				add_item("Attach Objects",false);
				add_toggle("Ninja",ninja);
				add_toggle("Super Punch/Kick  ~PAD_LT~ + ~PAD_B~ / ~PAD_X~",superfight);
				add_toggle("Remove Blip",rblip);
				add_item("Evil B's Model Changer",true);
				add_item("Buffeting's Model Changer",true);
				add_item("Strides",false);
				add_toggle("BulletProof Vest",bpvest);
				return;
			}
			if(last_selected[1] == 12){
				print_long("~y~Disable Group Protection if using Evades premium V3");
				footer = "Bodyguards";
				add_item("Options",false);
				add_item("Jew",true);
				add_item("Lil Jacob",true);
				add_item("Brucie",true);
				add_item("Nigga",true);
				add_item("FBI",true);
				add_item("Cop",true);
				add_item("Fat Cop",true);
				add_item("Multiplayer Male",true);
				add_item("Multiplayer Female",true);
				add_item("Army Guy",true);
				add_item("Club",true);
				add_item("Stripper",true);
				add_item("Noose Guard",true);
				add_item("Suited",true);
				add_item("Thief",true);
				add_item("Noose Sniper",true);
				add_item("Loony Black",true);
				add_item("Air Worker",true);
				return;
			}
			if(last_selected[1] == 16){
				footer = "Location";
				add_item("Teleport to Saved Location",true);
				add_item("Save Current Location",true);
				add_toggle("XYZH Coords",xyzh);
				return;
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				footer = "Car Garage";
				in_paint = false;
				add_item("Vehicle Spawner",false);
				add_item("Upgrades",false);
				add_item("Paint",false);
				add_item("Neons",false);
				add_item("Funny Cars",false);
				add_item("Fix & Wash Vehicle",true);
				add_toggle("Hydraulics  ~PAD_X~",hydrolics);
				add_toggle("Lower Suspension",lowerpveh);
				add_item("Lock/Unlock Doors",true);
				add_toggle("Rainbow Car",rainbowcar);
				add_toggle("Ignite Engine (NOS Effect)",nos);
				add_toggle("Raise Suspension",veh_height);
				add_item("Doors",false);
				add_item("Lights",false);
				add_item("Spawn 5 Cars",false);
				add_toggle("RocketCar  ~PAD_X~",rocketveh);
				add_toggle("Car Jump  ~PAD_RB~",carjump);
				add_toggle("CheckerBoard: Black/White",bw_checker);
				add_toggle("CheckerBoard: Red/Blue",rb_checker);
				return;
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				footer = "Weapon Selector";
				add_number("Weapons Pack",3);
				add_item("TBOGT Weapon Selector",false);
				add_item("Grenades",true);
				add_item("Glock 17",true);
				add_item("Desert Eagle",true);
				add_item("Pump Shotgun",true);
				add_item("Beretta Shotgun",true);
				add_item("Micro Uzi",true);
				add_item("MP5",true);
				add_item("AK-47",true);
				add_item("AR-15",true);
				add_item("M40-A5",true);
				add_item("Advance Sniper",true);
				add_item("Rocket Launcher",true);
				add_item("Baseball Bat",true);
				add_item("Pool Stick",true);
				add_item("Knife",true);
				add_item("Molotovs",true);
				return;
			}
			if(last_selected[1] == 4){
				footer = "Object launcher";
				add_toggle("Launcher - Glock",objectgun);
				add_toggle("Clear last object",del_objgun);
				add_item("Shoot Dildos",true);
				add_item("Shoot Red Cubes",true);
				add_item("Shoot Blue Cubes",true);
				add_item("Shoot Green Cubes",true);
				add_item("Shoot Bowling Balls",true);
				add_item("Shoot Donuts",true);
				add_item("Shoot Bricks",true);
				add_item("Shoot Bins",true);
				add_item("Shoot Dumpsters",true);
				add_item("Shoot Candy Machines",true);
				add_item("Shoot Bowling Pins",true);
				add_item("Shoot Sprunk Box",true);	
				add_item("Shoot TVs",true);	
				return;
			}
			if(last_selected[1] == 6){
				footer = "Car launcher";
				add_toggle("Launcher - Deagle",cargun);
				add_toggle("Clear last car",del_cargun);
				add_toggle("Explosive Rounds",exp_cargun);
				add_toggle("Shoot Cars Vertically",strat_cargun);
				add_toggle("Ground Cars",grond_cargun);
				add_item("Shoot Sultan RS's",true);
				add_item("Shoot Airtug's",true);
				add_item("Shoot Ambulance's",true);
				add_item("Shoot Phantom's",true);
				add_item("Shoot Bus's",true);
				add_item("Shoot Tugboat's",true);
				add_item("Shoot Trashmaster's",true);
				add_item("Shoot Trains's",true);
				add_item("Shoot Ripley's",true);
				add_item("Shoot Admiral's",true);
				add_item("Shoot Cavalcade's",true);
				add_item("Shoot Futo's",true);
				add_item("Shoot Noose Cruiser's",true);
				return;
			}
		}
		if(last_selected[0] == 5){
			if(last_selected[1] == 1){
				footer = "Menu Options";
				add_item("Colors",false);
				add_toggle("Compact",xmc_compact);
				add_toggle("Screen Chat Names",xmc_chat);
				add_toggle("Dim Background",xmc_dim);
				add_toggle("Player menu Colors",xmc_online_col);
				add_toggle("Keyboard Shortcuts",xmc_keyboard);
				add_toggle("Open Menu with  ~PAD_RB~ + ~PAD_LB~",xmc_switch);
				return;
			}
			if(last_selected[1] == 2){
				footer = "Throwable Objects";
				add_item("Big Ol' Pile of Dildos",true);
				add_item("Gumball Machine",true);
				add_item("Cubes",true);
				add_item("Throwing Knives",true);
				add_item("Grenades - that explode",true);
				add_item("Rockets - that explode",true);
				add_item("AK47",true);
				add_item("Axe",true);
				add_item("Bowling Pin",true);
				add_item("Sprunk Box",true);	
				add_item("TV",true);	
				add_item("Bowling Ball",true);
				return;
			}
			if(last_selected[1] == 3){
				footer = "Air Strikes";
				add_item("Airport Helipads",true);
				add_item("Airport Control Tower",true);
				add_item("Airport Parking Lot",true);
				add_item("Waypoint",true);
				add_item("Your Location",true);
				return;
			}
			if(last_selected[1] == 13){
				footer = "Radio Anywhere";
				add_item("Radio On",true);
				add_item("Radio Off",true);
				add_item("Tune Station Up",true);
				add_item("Tune Station Down",true);
				return;
			}
			if(last_selected[1] == 15){
				footer = "Weather";
				add_item("Sunny",true);
				add_item("Extra Sunny",true);
				add_item("Extra Sunny (2)",true);
				add_item("Sunny & Windy",true);
				add_item("Sunny & Windy (2)",true);
				add_item("Drizzle",true);
				add_item("Fog",true);
				add_item("Rain",true);
				add_item("Thunder Storm",true);
				add_item("Cloudy",true);
				add_item("Skip ahead 1 hour",true);
				add_toggle("Freeze Weather",fweather);
				add_toggle("Rapid Weather",rweather);
				return;
			}
			if(last_selected[1] == 17){
				footer = "Camera";
				add_toggle("Overhead Cam",DOES_CAM_EXIST(gta2cam));
				add_item("Drunk Cam",true);
				return;
			}
			if(last_selected[1] == 19){
				footer = "Escorts ~PAD_DPAD_LEFTRIGHT~";
				add_item("End all Escorts",true);
				add_item("Limo",true);
				add_item("Maverick",true);
				add_item("Cavalcade",true);
				add_item("Bus",true);
				add_item("Police Cruiser",true);
				add_item("Ambulance",true);
				add_item("FBI",true);
				add_item("Taxi",true);
				add_item("Police Stockade",true);
				add_item("Oracle",true);
				add_item("Current Car",true);
				return;
			}
		}
	}
	
	if(menu_level == 3){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					footer = "All Players";
					add_item("Give Weapons & Armor",true);
					add_item("Remove Weapons",true);
					add_toggle("Talking Chaos",chaos);
					add_item("Vehicle Train",true);
					add_item("Attach a Hippo",true);
					add_item("Delete Cars",true);
					add_item("Teleport to You",true);
					add_item("Teleport to Prison",true);
					add_item("Teleport to Airport",true);
					add_item("Slingshot Cars",true);
					add_item("Attach a Cube",true);
					add_item("Attach a Dick",true);
					add_item("Screw up all cars",true);
					add_item("Burn all Players",true);
					add_item("Chronicle all Players",true);
					add_item("Attach a Cone",true);
					add_item("Attach a Tire",true);
					add_item("Attach a Bowling Ball",true);
					return;
				}
				if(last_selected[2] == 2){
					footer = "Shortcut Players";
					add_item("Give Weapons & Armor",true);
					add_item("Remove Weapons",true);
					add_item("Teleport to You",true);
					add_item("Delete Vehicles",true);
					add_item("Vehicle Spawner",false);
					add_item("Display Shortcut Players",false);
					add_item("Clear Shortcut List",true);
					return;
				}
				else{
					admin_obj = GET_OBJECT_PED_IS_HOLDING(pPlayer);
					WAIT(1);
					if(DOES_OBJECT_EXIST(admin_obj)) DELETE_OBJECT(&admin_obj);
					footer = players[(last_selected[2] - 3)].gamertag;
					add_item("Weapon Selector",false);
					add_item("Add to Shortcut",true);
					add_item("Loops",false);
					add_item("Teleports",false);
					add_item("Vehicles",false);
					add_item("Main",false);
					add_item("Objects",false);
					add_item("Bodyguards",false);
					add_item("Vehicle Spawner",false);
					add_item("Administrator",false);
					add_item("Attaches",false);
					add_item("Ram with Car",false);
					return;
				}
			}
			if(last_selected[1] == 2){
				if(last_selected[2] == 1){
					footer = "Animations";
					add_number("Taichi",2);
					add_number("Male Dance",4);
					add_number("Female Dance",3);
					add_item("Pole Dance",true);
					add_item("Zohan",true);
					add_item("Busted",true);
					add_item("Smoking",true);	
					add_number("Drunk",2);
					add_item("Execute",true);
					add_item("Knock On Door",true);
					add_item("Smoking #2",true);
					add_number("Roll",2);
					add_number("Bouncer",2);
					add_item("Wave",true);
					add_number("Hooker",3);
					add_item("Fuck Off!",true);
					add_item("Hail Taxi",true);
					add_item("Celebrate",true);
					add_number("Car Kiss",2);
					return;
				}
				if(last_selected[2] == 2){
					print("~y~Experimental, some may not work with your player model.");
					footer = "Speeches";
					add_item("Thanks",true);
					add_item("Scream",true);
					add_item("Get Out",true);
					add_item("Hello",true);
					add_item("Hooker Sex",true);
					add_item("Fuck off!",true);
					add_item("Conversation",true);
					add_item("Bye",true);
					add_item("I was shot!",true);
					add_item("Lets Fight!",true);
					return;
				}
				if(last_selected[2] == 8){
					footer = "Attach Objects";
					add_item("Hippo",true);
					add_item("Cube",true);
					add_item("Dick",true);
					add_item("Dumpster",true);
					add_item("TV",true);
					add_item("Cone",true);
					add_item("Tire",true);
					add_item("Bowling Ball",true);
					return;
				}
				if(last_selected[2] == 14){
					footer = "Strides";
					add_item("Normal",true);
					add_item("Hurt",true);
					add_item("Gangster",true);
					add_item("Fat",true);
					add_item("Coward",true);
					add_item("Girl",true);
					add_item("Gangster 2",true);
					return;
				}
			}
			if(last_selected[1] == 12){
				if(last_selected[2] == 1){
					footer = "Bodyguard Options";
					add_item("Delete One Guard",true);
					add_item("Delete All Guards",true);
					add_item("Teleport guards to you",true);
					add_item("Give Weapon to all guards",false);
					add_item("Take Away All Godmode",true);
					add_item("Guards Dances",false);
					add_item("Disband All Guards",true);
					add_item("Clear All Guard's Tasks",true);
					add_item("Create a Human Tower",true);
					add_item("Attach a Dick to all guards",true);
					add_item("Teleport guards into car",true);
					add_item("Guard Strides",false);
					return;
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					footer = "Vehicle Spawner";
					add_item("Sports",false);
					add_item("Muscle",false);
					add_item("Two Door",false);
					add_item("Four Door",false);
					add_item("Four Door (2)",false);
					add_item("Junkers",false);
					add_item("SUVs, Vans & Trucks",false);
					add_item("Commercial",false);
					add_item("Commercial (2)",false);
					add_item("Emergency",false);
					add_item("Service",false);
					add_item("Bikes",false);
					add_item("Boats",false);
					add_item("Helicopters",false);
					return;
				}
				if(last_selected[2] == 2){
					footer = "Upgrades";
					char* upgrade[10];
					upgrade[0] = "Upgrade 1";
					upgrade[1] = "Upgrade 2";
					upgrade[2] = "Upgrade 3";
					upgrade[3] = "Upgrade 4";
					upgrade[4] = "Upgrade 5";
					upgrade[5] = "Upgrade 6";
					upgrade[6] = "Upgrade 7";
					upgrade[7] = "Upgrade 8";
					upgrade[8] = "Upgrade 9";
					upgrade[9] = "Upgrade 10";
					
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					if(DOES_VEHICLE_EXIST(pveh)){
						for(i = 0;i < 10;i++) add_toggle(upgrade[i],IS_VEHICLE_EXTRA_TURNED_ON(pveh,(i + 1)));
					}
					return;
				}
				if(last_selected[2] == 3){
					footer = "Paint";
					add_number("Color 1",134);
					add_number("Color 2",134);
					add_number("Color 3",134);
					add_number("Color 4",134);
					
					in_paint = true;
					GET_CAR_CHAR_IS_USING(pPlayer,&pveh);
					if(DOES_VEHICLE_EXIST(pveh)){
						GET_CAR_COLOURS(pveh,&color1,&color2);
						GET_EXTRA_CAR_COLOURS(pveh,&color3,&color4);
						menu[1].value = color1 + 1;
						menu[2].value = color2 + 1;
						menu[3].value = color3 + 1;
						menu[4].value = color4 + 1;
						
						menu[1].extra_val = menu[1].value;
						menu[2].extra_val = menu[2].value;
						menu[3].extra_val = menu[3].value;
						menu[4].extra_val = menu[4].value;
					}
					return;
				}
				if(last_selected[2] == 4){
					footer = "Neons";
					add_item("Blue",true);
					add_item("Yellow",true);
					add_item("Green",true);
					add_item("Red",true);
					add_item("Pink",true);
					add_item("Orange",true);
					return;
				}
				if(last_selected[2] == 5){
					print("~g~I didn't make any cars here, only tweaked some slightly");
					footer = "Funny Cars";
					add_item("BMX Sanchez",true);
					add_item("Monster Truck",true);
					add_item("Big PCJ",true);
					add_item("Private Jet",true);
					add_item("WheelBarrow",true);
					add_item("Rocket Boat",true);
					add_item("Rusty Back to the Future",true);
					return;
				}
				if(last_selected[2] == 13){
					footer = "Car Doors";
					add_item("All Doors",true);
					add_item("Hood",true);
					add_item("Trunk",true);
					add_item("Front Left",true);
					add_item("Front Right",true);
					add_item("Rear Left",true);
					add_item("Rear Right",true);
					return;
				}
				if(last_selected[2] == 14){
					footer = "Vehicle Lights";
					add_toggle("Hazard Lights",veh_hazard);
					add_toggle("Indicator Lights",veh_indic);
					return;
				}
				if(last_selected[2] == 15){
					footer = "Spawn 5 Cars";
					add_item("Infernus",true);
					add_item("Sultan RS",true);
					add_item("Banshee",true);
					add_item("Comet",true);
					add_item("Dinghy",true);
					add_item("Annihilator",true);
					if(GET_CURRENT_EPISODE() == 2){
						add_item("Bullet GT",true);
						add_item("APC Tank",true);
						add_item("Buzzard",true);
					}
					return;
				}
			}
		}
		if(last_selected[0] == 3){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					footer = "TBOGT Weapons";
					if(GET_CURRENT_EPISODE() == 2){
						add_item(".44 Pistol",true);
						add_item("Explosive AA12",true);
						add_item("AA12",true);
						add_item("P-90",true);
						add_item("Golden Uzi",true);
						add_item("M249",true);
						add_item("Explosive Sniper",true);
						add_item("Grenade Launcher",true);
						add_item("Sticky Bombs",true);
						return;
					}
					else{
						add_item("You must be on TBOGT to use this",true);
						return;
					}
				}
			}
		}
		if(last_selected[0] == 5){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					footer = "Menu Colors";
					add_item("Purple",true);
					add_item("Red",true);
					add_item("Light Blue",true);
					add_item("Green",true);
					add_item("Pink",true);
					add_item("Gold",true);
					add_item("Gray",true);
					add_item("Dark Blue",true);
					add_toggle("Flashing Colors",rainbowmenu);
					return;
				}
			}
		}
	}
	if(menu_level == 4){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					if(last_selected[3] == 5){
						footer = "Vehicle Spawner";
						add_item("Sports",false);
						add_item("Muscle",false);
						add_item("Two Door",false);
						add_item("Four Door",false);
						add_item("Four Door (2)",false);
						add_item("Junkers",false);
						add_item("SUVs, Vans & Trucks",false);
						add_item("Commercial",false);
						add_item("Commercial (2)",false);
						add_item("Emergency",false);
						add_item("Service",false);
						add_item("Bikes",false);
						add_item("Boats",false);
						add_item("Helicopters",false);
						return;
					}
					if(last_selected[3] == 6){
						footer = "Shortcut Players";
						player_count = 0;
						for(i = 0;i <= 15;i++){
						//	players[player_count].connected = false;
							if(!IS_NETWORK_PLAYER_ACTIVE(i)) continue;
							if(GET_PLAYER_ID() == i) continue;
							GET_PLAYER_CHAR(i,&online_char);
							players[player_count].ped = online_char;
							players[player_count].gamertag = GET_PLAYER_NAME(i);
							players[player_count].id = i;
						//	players[player_count].connected = true;
							player_count++;
						}
						if(player_count > 0){
							for(i = 0;i <= 6;i++){
								if(DOES_CHAR_EXIST(shortcut_players[i])){
									if(IS_NETWORK_PLAYER_ACTIVE(GetPlayerFromPed(shortcut_players[i]))){
										if(xmc_online_col) add_online_player(GET_PLAYER_NAME(GetPlayerFromPed(shortcut_players[i])),GetPlayerFromPed(shortcut_players[i]),true);
										else add_item(GET_PLAYER_NAME(GetPlayerFromPed(shortcut_players[i])),true);
									}
								}
							}
						}
						else add_item("Game empty",true);
						return;
					}
				}
				if(last_selected[2] > 2){
					if(last_selected[3] == 1){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_number("Weapons Pack",3);
						add_item("Remove All Weapons",true);
						add_item("Give a RPG",true);
						add_item("Give a Pool Stick",true);
						add_item("Give a M4",true);
						add_item("Give a Desert Eagle",true);
						add_item("Give a Baseball Bat",true);
						add_item("Give Grenades",true);
						add_item("Give an AK47",true);
						add_item("Give a Pump Shotgun",true);
						add_item("Give a Sniper Rifle",true);
						add_item("Give a MP5",true);
						add_item("Give Molotovs",true);
						if(GET_CURRENT_EPISODE() == 2){
							add_item("Give an Explosive AA12",true);
							add_item("Give a P90",true);
							add_item("Give a Golden UZI",true);
							add_item("Give a M249",true);
							add_item("Give an Explosive Sniper",true);
							add_item("Give Sticky Bombs",true);
						}
						return;
					}
					if(last_selected[3] == 3){
						tmp = players[(last_selected[2] - 3)].id;
						footer = players[(last_selected[2] - 3)].gamertag;
						add_toggle("Modder Protection",players[tmp].mprotection);
						add_toggle("Chronicle",players[tmp].force);
						add_toggle("Rage Mode",players[tmp].rage);
						add_toggle("Walk/Drive on Water",players[tmp].water);
						add_toggle("Disarm",players[tmp].disarm);
						add_toggle("View Player",view_online_player);
						add_toggle("Rocket Deagle",players[tmp].rocket);
						add_toggle("Car Launcher (Glock)",players[tmp].cargun);
						return;
					}
					if(last_selected[3] == 4){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Teleport to Them",true);
						add_item("Teleport in Car",true);
						add_item("Teleport to You",true);
						add_item("Teleport to Waypoint",true);
						add_item("Teleport to Prison",true);
						add_item("Teleport to Airport",true);
						add_item("Teleport to Playboy X House",true);
						add_item("Teleport to Killzone",true);
						add_item("Teleport to Water",true);
						add_item("Teleport to Fight Cage (TBOGT)",true);
						add_item("Send Player Skydiving",true);
						add_item("Teleport to a Random Location",true);
						return;
					}
					if(last_selected[3] == 5){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Main",false);
						add_item("Control",false);
						add_item("Vehicle Helper",true);
						add_item("Lock/Unlock Doors",true);
						add_item("Flip Vehicle",true);
						add_item("Flip Vehicle 180",true);
						add_item("Visibility",false);
						add_item("Colors",false);
						add_item("Neons",false);
						add_item("Collision",false);
						return;
					}
					if(last_selected[3] == 6){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Give Money",true);
						add_item("Nuke",true);
						add_item("Taser",true);
						add_item("Kick",true);
						add_item("Burn",true);
						add_item("Kidnap",true);
						add_item("Freeze",false);
						add_item("Glitch",true);
						return;
					}
					if(last_selected[3] == 7){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Attach a Hippo",true);
						add_item("Attach a Cube",true);
						add_item("Attach a Dick",true);
						add_item("Attach a Dumpster",true);
						add_item("Attach a TV",true);
						add_item("Attach a Troll Box",true);
						add_item("Attach a Sultan",true);
						add_item("Attach a Cone",true);
						add_item("Attach a Tire",true);
						add_item("Attach a Bowling Ball",true);
						add_item("Attach a Bus",true);
						add_item("Attach an Ice Cream Truck",true);
						return;
					}
					if(last_selected[3] == 8){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Actions",false);
						add_item("Human Tower",true);
						add_item("Teleport Guards to Player",true);
						return;
					}
					if(last_selected[3] == 9){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Sports",false);
						add_item("Muscle",false);
						add_item("Two Door",false);
						add_item("Four Door",false);
						add_item("Four Door (2)",false);
						add_item("Junkers",false);
						add_item("SUVs, Vans & Trucks",false);
						add_item("Commercial",false);
						add_item("Commercial (2)",false);
						add_item("Emergency",false);
						add_item("Service",false);
						add_item("Bikes",false);
						add_item("Boats",false);
						add_item("Helicopters",false);
						return;
					}
					if(last_selected[3] == 10){
						#ifndef PERSONAL
						print("~r~Personal Version only");
						return;
						#else
						REQUEST_MODEL(MODEL_CJ_APPLE_SMALL);    
						while(!HAS_MODEL_LOADED(MODEL_CJ_APPLE_SMALL)) WAIT(0);
						CREATE_OBJECT(MODEL_CJ_APPLE_SMALL, x, y, z, &admin_obj, 1);
						while(!DOES_OBJECT_EXIST(admin_obj)) WAIT(0);
						SET_OBJECT_INVINCIBLE(admin_obj,0);
						SET_CHAR_VISIBLE(pPlayer, true);
						FREEZE_OBJECT_POSITION(admin_obj,0);
						SET_OBJECT_DYNAMIC(admin_obj,1);
						SET_OBJECT_AS_STEALABLE(admin_obj,1);
						SET_OBJECT_COLLISION(admin_obj,1);
						GIVE_PED_PICKUP_OBJECT(pPlayer, admin_obj, true);
						print_long("Make sure user must be running ~g~Xmc Modmenu v4.0 ~w~or later.");
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("--- XMC v4.0+ ---",true);
						add_item("Send a Greeting message",true);
						add_item("Send a Warning message",true);
						add_item("Send Menu Disable (loop toggle)",true);
						add_item("Send a Freeze",true);
						add_item("Send a Troll Virus",true);
						add_item("Send a Feature & Protection Disable",true);
						add_item("Send a Teleport to you (loop toggle)",true);
						add_item("--- XMC v5.5+ ---",true);
						add_item("Send a back to Singleplayer",true);
						add_item("Send a Script Segfault",true);
						#endif
						return;
					}
					if(last_selected[3] == 11){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Attach to Their Car",true);
						add_item("Attach to Their Head",true);
						add_item("Attach Your Car to Their Head",true);
						add_item("Attach Their Car to Your Head",true);
						add_item("Attach a Random Ped",true);
						return;
					}
					if(last_selected[3] == 12){
						footer = players[(last_selected[2] - 3)].gamertag;
						add_item("Ram with Bus",true);
						add_item("Ram with Infernus",true);
						add_item("Ram with Banshee",true);
						add_item("Ram with Dinghy",true);
						add_item("Ram with Cavalcade",true);
						add_item("Ram with Ambulance",true);
						add_item("Ram with Trashmaster",true);
						add_item("Ram with Vigero",true);
						add_item("Ram with Phantom",true);
						add_item("Ram with Ice Cream Truck",true);
						return;
					}
				}
			}
			if(last_selected[1] == 12){
				if(last_selected[2] == 1){
					if(last_selected[3] == 4){
						footer = "Bodyguard Weapons";
						add_item("RPG",true);
						add_item("Pool Stick",true);
						add_item("M4",true);
						add_item("Desert Eagle",true);
						add_item("Baseball Bat",true);
						add_item("Knife",true);
						add_item("AK47",true);
						add_item("Pump Shotgun",true);
						add_item("Sniper Rifle",true);
						add_item("MP5",true);
						add_item("Molotovs",true);
						return;
					}
					if(last_selected[3] == 6){
						footer = "Bodyguard Dances";
						add_number("Taichi",2);
						add_number("Male Dance",4);
						add_number("Female Dance",3);
						add_item("Pole Dance",true);
						add_item("Busted",true);
						return;
					}
					if(last_selected[3] == 12){
						footer = "Bodyguard Strides";
						add_item("Normal",true);
						add_item("Hurt",true);
						add_item("Gangster",true);
						add_item("Fat",true);
						add_item("Coward",true);
						add_item("Girl",true);
						add_item("Gangster 2",true);
						return;
					}
				}
			}
		}
		if(last_selected[0] == 2){
			if(last_selected[1] == 1){
				if(last_selected[2] == 1){
					 i = GET_CURRENT_EPISODE();
					if(last_selected[3] == 1){
						footer = "Sports";
						add_gxt_hash(MODEL_BANSHEE);
						add_gxt_hash(MODEL_COMET);
						add_gxt_hash(MODEL_COQUETTE);
						add_gxt_hash(MODEL_FELTZER);
						add_gxt_hash(MODEL_INFERNUS);
						add_gxt_hash(MODEL_SULTAN);
						add_gxt_hash(MODEL_SULTANRS);
						add_gxt_hash(MODEL_SUPERGT);
						add_gxt_hash(MODEL_TURISMO);
						if(i == 2){
							add_gxt_hash(MODEL_BUFFALO);
							add_gxt_hash(MODEL_BULLET);
							add_gxt_hash(MODEL_F620);
						}
						return;
					}
					if(last_selected[3] == 2){
						footer = "Muscle";
						add_gxt_hash(MODEL_BUCCANEER);
						add_gxt_hash(MODEL_DUKES);
						add_gxt_hash(MODEL_FACTION);
						add_gxt_hash(MODEL_MANANA);
						add_gxt_hash(MODEL_PEYOTE);
						add_gxt_hash(MODEL_RUINER);
						add_gxt_hash(MODEL_SABRE);
						add_gxt_hash(MODEL_SABREGT);
						add_gxt_hash(MODEL_STALION);
						add_gxt_hash(MODEL_VIGERO);
						add_gxt_hash(MODEL_VIRGO);
						add_gxt_hash(MODEL_VOODOO);
						if(i == 2)
							add_gxt_hash(MODEL_TAMPA);
						return;
					}
					if(last_selected[3] == 3){
						footer = "Two Doors";
						add_gxt_hash(MODEL_BLISTA);
						add_gxt_hash(MODEL_FORTUNE);
						add_gxt_hash(MODEL_FUTO);
						add_gxt_hash(MODEL_SENTINEL);
						add_gxt_hash(MODEL_URANUS);
						if(i == 2){
							add_gxt_hash(MODEL_SUPERD2);
						}
						return;
					}
					if(last_selected[3] == 4){
						footer = "Four Doors";
						add_gxt_hash(MODEL_ADMIRAL);
						add_gxt_hash(MODEL_CHAVOS);
						add_gxt_hash(MODEL_COGNOSCENTI);
						add_gxt_hash(MODEL_DF8);
						add_gxt_hash(MODEL_DILETTANTE);
						add_gxt_hash(MODEL_EMPEROR);
						add_gxt_hash(MODEL_ESPERANTO);
						add_gxt_hash(MODEL_FEROCI);
						add_gxt_hash(MODEL_HAKUMAI);
						add_gxt_hash(MODEL_INGOT);
						add_gxt_hash(MODEL_INTRUDER);
						add_gxt_hash(MODEL_LOKUS);
						add_gxt_hash(MODEL_MARBELLA);
						add_gxt_hash(MODEL_MERIT);
						return;
					}
					if(last_selected[3] == 5){
						footer = "Four Doors (2)";
						add_gxt_hash(MODEL_ORACLE);
						add_gxt_hash(MODEL_PINNACLE);
						add_gxt_hash(MODEL_PMP600);
						add_gxt_hash(MODEL_PREMIER);
						add_gxt_hash(MODEL_PRES);
						add_gxt_hash(MODEL_PRIMO);
						add_gxt_hash(MODEL_ROM);
						add_gxt_hash(MODEL_SCHAFTER);
						add_gxt_hash(MODEL_SOLAIR);
						add_gxt_hash(MODEL_STRATUM);
						add_gxt_hash(MODEL_VINCENT);
						add_gxt_hash(MODEL_WASHINGTON);
						add_gxt_hash(MODEL_WILLARD);
						if(i == 2){
							add_gxt_hash(MODEL_SCHAFTER2);
							add_gxt_hash(MODEL_SCHAFTER3);
							add_gxt_hash(MODEL_SUPERD);
						}
						return;
					}
					if(last_selected[3] == 6){
						footer = "Junkers";
						add_gxt_hash(MODEL_EMPEROR2);
						add_gxt_hash(MODEL_SABRE2);
						add_gxt_hash(MODEL_VIGERO2);
						return;
					}
					if(last_selected[3] == 7){
						footer = "SUVs, Vans & Trucks";
						add_gxt_hash(MODEL_BOBCAT);
						add_gxt_hash(MODEL_CAVALCADE);
						add_gxt_hash(MODEL_FXT);
						add_gxt_hash(MODEL_E109);
						add_gxt_hash(MODEL_HABANERO);
						add_gxt_hash(MODEL_HUNTLEY);
						add_gxt_hash(MODEL_LANDSTALKER);
						add_gxt_hash(MODEL_MINIVAN);
						add_gxt_hash(MODEL_MOONBEAM);
						add_gxt_hash(MODEL_PATRIOT);
						add_gxt_hash(MODEL_PERENNIAL);
						add_gxt_hash(MODEL_RANCHER);
						add_gxt_hash(MODEL_REBLA);
						if(i == 2){
							add_gxt_hash(MODEL_SERRANO);
							add_gxt_hash(MODEL_SERRANO2);
							add_gxt_hash(MODEL_CAVALCADE2);
							add_gxt_hash(MODEL_SLAMVAN);
						}
						return;
					}
					if(last_selected[3] == 8){
						footer = "Commercial";
						add_gxt_hash(MODEL_AIRTUG);
						add_gxt_hash(MODEL_BENSON);
						add_gxt_hash(MODEL_BIFF);
						add_gxt_hash(MODEL_BOXVILLE);
						add_gxt_hash(MODEL_BURRITO);
						add_gxt_hash(MODEL_FLATBED);
						add_gxt_hash(MODEL_FEROCI2);
						add_gxt_hash(MODEL_PERENNIAL2);
						add_gxt_hash(MODEL_FORKLIFT);
						add_gxt_hash(MODEL_BURRITO2);
						add_gxt_hash(MODEL_MRTASTY);
						add_gxt_hash(MODEL_MULE);
						add_gxt_hash(MODEL_PACKER);
						add_gxt_hash(MODEL_PHANTOM);	
						return;
					}
					if(last_selected[3] == 9){
						footer = "Commercial (2)";
						add_gxt_hash(MODEL_PONY);
						add_gxt_hash(MODEL_RIPLEY);
						add_gxt_hash(MODEL_STOCKADE);
						add_gxt_hash(MODEL_SPEEDO);
						add_gxt_hash(MODEL_STEED);
						add_gxt_hash(MODEL_YANKEE);
						if(i == 2)
							add_gxt_hash(MODEL_CADDY);
							add_gxt_hash(MODEL_AVAN);
						return;
					}
					if(last_selected[3] == 10){
						footer = "Emergency";
						add_gxt_hash(MODEL_AMBULANCE);
						add_gxt_hash(MODEL_NSTOCKADE);
						add_gxt_hash(MODEL_FBI);
						add_gxt_hash(MODEL_FIRETRUK);
						add_gxt_hash(MODEL_NOOSE);
						add_gxt_hash(MODEL_POLPATRIOT);
						add_gxt_hash(MODEL_POLICE);
						add_gxt_hash(MODEL_POLICE2);
						add_gxt_hash(MODEL_PSTOCKADE);
						if(i == 2){
							add_gxt_hash(MODEL_APC);
							add_gxt_hash(MODEL_POLICE3);
							add_gxt_hash(MODEL_POLICEW);
							add_gxt_hash(MODEL_POLICE4);
							add_gxt_hash(MODEL_POLICEB);						
						}
						return;
					}
					if(last_selected[3] == 11){
						footer = "Service";
						add_gxt_hash(MODEL_BUS);
						add_gxt_hash(MODEL_CABBY);
						add_gxt_hash(MODEL_ROMERO);
						add_gxt_hash(MODEL_TAXI);
						add_gxt_hash(MODEL_TAXI2);
						add_gxt_hash(MODEL_TRASH);
						add_gxt_hash(MODEL_STRETCH);
						if(i == 2){
							add_gxt_hash(MODEL_LIMO2);
						}
						return;
					}
					if(last_selected[3] == 12){
						footer = "Bikes";
						add_gxt_hash(MODEL_FAGGIO);
						add_gxt_hash(MODEL_BOBBER);
						add_gxt_hash(MODEL_HELLFURY);
						add_gxt_hash(MODEL_NRG900);
						add_gxt_hash(MODEL_PCJ);
						add_gxt_hash(MODEL_SANCHEZ);
						add_gxt_hash(MODEL_ZOMBIEB);
						if(i == 2){
							add_gxt_hash(MODEL_HEXER);
							add_gxt_hash(MODEL_FAGGIO2);
							add_gxt_hash(MODEL_BATI2);
							add_gxt_hash(MODEL_VADER);
							add_gxt_hash(MODEL_AKUMA);
							add_gxt_hash(MODEL_HAKUCHOU);
							add_gxt_hash(MODEL_DOUBLE);
						}
						return;
					}
					if(last_selected[3] == 13){
						footer = "Boats";
						add_gxt_hash(MODEL_DINGHY);
						add_gxt_hash(MODEL_JETMAX);
						add_gxt_hash(MODEL_MARQUIS);
						add_gxt_hash(MODEL_PREDATOR);
						add_gxt_hash(MODEL_REEFER);
						add_gxt_hash(MODEL_SQUALO);
						add_gxt_hash(MODEL_TROPIC);
						add_gxt_hash(MODEL_TUGA);
						if(i == 2){
							add_gxt_hash(MODEL_SMUGGLER);
							add_gxt_hash(MODEL_FLOATER);
							add_gxt_hash(MODEL_BLADE);
						}
						return;
					}
					if(last_selected[3] == 14){
						footer = "Helicopters";
						add_gxt_hash(MODEL_ANNIHILATOR);
						add_gxt_hash(MODEL_TOURMAV);
						add_gxt_hash(MODEL_MAVERICK);
						add_gxt_hash(MODEL_POLMAV);
						if(i == 2){
							add_gxt_hash(MODEL_BUZZARD);
							add_gxt_hash(MODEL_SWIFT);
							add_gxt_hash(MODEL_SKYLIFT);
						}
						return;
					}
				}
			}
		}
	}
	if(menu_level == 5){
		if(last_selected[0] == 1){
			if(last_selected[1] == 1){
				if(last_selected[2] == 2){
					if(last_selected[3] == 5){
						 i = GET_CURRENT_EPISODE();
						footer = "Vehicle Spawner";
						if(last_selected[4] == 1){
							add_gxt_hash(MODEL_BANSHEE);
							add_gxt_hash(MODEL_COMET);
							add_gxt_hash(MODEL_COQUETTE);
							add_gxt_hash(MODEL_FELTZER);
							add_gxt_hash(MODEL_INFERNUS);
							add_gxt_hash(MODEL_SULTAN);
							add_gxt_hash(MODEL_SULTANRS);
							add_gxt_hash(MODEL_SUPERGT);
							add_gxt_hash(MODEL_TURISMO);
							if(i == 2){
								add_gxt_hash(MODEL_BUFFALO);
								add_gxt_hash(MODEL_BULLET);
								add_gxt_hash(MODEL_F620);
							}
							return;
						}
						if(last_selected[4] == 2){
							add_gxt_hash(MODEL_BUCCANEER);
							add_gxt_hash(MODEL_DUKES);
							add_gxt_hash(MODEL_FACTION);
							add_gxt_hash(MODEL_MANANA);
							add_gxt_hash(MODEL_PEYOTE);
							add_gxt_hash(MODEL_RUINER);
							add_gxt_hash(MODEL_SABRE);
							add_gxt_hash(MODEL_SABREGT);
							add_gxt_hash(MODEL_STALION);
							add_gxt_hash(MODEL_VIGERO);
							add_gxt_hash(MODEL_VIRGO);
							add_gxt_hash(MODEL_VOODOO);
							if(i == 2)
								add_gxt_hash(MODEL_TAMPA);
							return;
						}
						if(last_selected[4] == 3){
							add_gxt_hash(MODEL_BLISTA);
							add_gxt_hash(MODEL_FORTUNE);
							add_gxt_hash(MODEL_FUTO);
							add_gxt_hash(MODEL_SENTINEL);
							add_gxt_hash(MODEL_URANUS);
							if(i == 2){
								add_gxt_hash(MODEL_SUPERD2);
							}
							return;
						}
						if(last_selected[4] == 4){
							add_gxt_hash(MODEL_ADMIRAL);
							add_gxt_hash(MODEL_CHAVOS);
							add_gxt_hash(MODEL_COGNOSCENTI);
							add_gxt_hash(MODEL_DF8);
							add_gxt_hash(MODEL_DILETTANTE);
							add_gxt_hash(MODEL_EMPEROR);
							add_gxt_hash(MODEL_ESPERANTO);
							add_gxt_hash(MODEL_FEROCI);
							add_gxt_hash(MODEL_HAKUMAI);
							add_gxt_hash(MODEL_INGOT);
							add_gxt_hash(MODEL_INTRUDER);
							add_gxt_hash(MODEL_LOKUS);
							add_gxt_hash(MODEL_MARBELLA);
							add_gxt_hash(MODEL_MERIT);
							return;
						}
						if(last_selected[4] == 5){
							add_gxt_hash(MODEL_ORACLE);
							add_gxt_hash(MODEL_PINNACLE);
							add_gxt_hash(MODEL_PMP600);
							add_gxt_hash(MODEL_PREMIER);
							add_gxt_hash(MODEL_PRES);
							add_gxt_hash(MODEL_PRIMO);
							add_gxt_hash(MODEL_ROM);
							add_gxt_hash(MODEL_SCHAFTER);
							add_gxt_hash(MODEL_SOLAIR);
							add_gxt_hash(MODEL_STRATUM);
							add_gxt_hash(MODEL_VINCENT);
							add_gxt_hash(MODEL_WASHINGTON);
							add_gxt_hash(MODEL_WILLARD);
							if(i == 2){
								add_gxt_hash(MODEL_SCHAFTER2);
								add_gxt_hash(MODEL_SCHAFTER3);
								add_gxt_hash(MODEL_SUPERD);
							}
							return;
						}
						if(last_selected[4] == 6){
							add_gxt_hash(MODEL_EMPEROR2);
							add_gxt_hash(MODEL_SABRE2);
							add_gxt_hash(MODEL_VIGERO2);
							return;
						}
						if(last_selected[4] == 7){
							add_gxt_hash(MODEL_BOBCAT);
							add_gxt_hash(MODEL_CAVALCADE);
							add_gxt_hash(MODEL_FXT);
							add_gxt_hash(MODEL_E109);
							add_gxt_hash(MODEL_HABANERO);
							add_gxt_hash(MODEL_HUNTLEY);
							add_gxt_hash(MODEL_LANDSTALKER);
							add_gxt_hash(MODEL_MINIVAN);
							add_gxt_hash(MODEL_MOONBEAM);
							add_gxt_hash(MODEL_PATRIOT);
							add_gxt_hash(MODEL_PERENNIAL);
							add_gxt_hash(MODEL_RANCHER);
							add_gxt_hash(MODEL_REBLA);
							if(i == 2){
								add_gxt_hash(MODEL_SERRANO);
								add_gxt_hash(MODEL_SERRANO2);
								add_gxt_hash(MODEL_CAVALCADE2);
								add_gxt_hash(MODEL_SLAMVAN);
							}
							return;
						}
						if(last_selected[4] == 8){
							add_gxt_hash(MODEL_AIRTUG);
							add_gxt_hash(MODEL_BENSON);
							add_gxt_hash(MODEL_BIFF);
							add_gxt_hash(MODEL_BOXVILLE);
							add_gxt_hash(MODEL_BURRITO);
							add_gxt_hash(MODEL_FLATBED);
							add_gxt_hash(MODEL_FEROCI2);
							add_gxt_hash(MODEL_PERENNIAL2);
							add_gxt_hash(MODEL_FORKLIFT);
							add_gxt_hash(MODEL_BURRITO2);
							add_gxt_hash(MODEL_MRTASTY);
							add_gxt_hash(MODEL_MULE);
							add_gxt_hash(MODEL_PACKER);
							add_gxt_hash(MODEL_PHANTOM);	
							return;
						}
						if(last_selected[4] == 9){
							add_gxt_hash(MODEL_PONY);
							add_gxt_hash(MODEL_RIPLEY);
							add_gxt_hash(MODEL_STOCKADE);
							add_gxt_hash(MODEL_SPEEDO);
							add_gxt_hash(MODEL_STEED);
							add_gxt_hash(MODEL_YANKEE);
							if(i == 2)
								add_gxt_hash(MODEL_CADDY);
								add_gxt_hash(MODEL_AVAN);
							return;
						}
						if(last_selected[4] == 10){
							add_gxt_hash(MODEL_AMBULANCE);
							add_gxt_hash(MODEL_NSTOCKADE);
							add_gxt_hash(MODEL_FBI);
							add_gxt_hash(MODEL_FIRETRUK);
							add_gxt_hash(MODEL_NOOSE);
							add_gxt_hash(MODEL_POLPATRIOT);
							add_gxt_hash(MODEL_POLICE);
							add_gxt_hash(MODEL_POLICE2);
							add_gxt_hash(MODEL_PSTOCKADE);
							if(i == 2){
								add_gxt_hash(MODEL_APC);
								add_gxt_hash(MODEL_POLICE3);
								add_gxt_hash(MODEL_POLICEW);
								add_gxt_hash(MODEL_POLICE4);
								add_gxt_hash(MODEL_POLICEB);						
							}
							return;
						}
						if(last_selected[4] == 11){
							add_gxt_hash(MODEL_BUS);
							add_gxt_hash(MODEL_CABBY);
							add_gxt_hash(MODEL_ROMERO);
							add_gxt_hash(MODEL_TAXI);
							add_gxt_hash(MODEL_TAXI2);
							add_gxt_hash(MODEL_TRASH);
							add_gxt_hash(MODEL_STRETCH);
							if(i == 2){
								add_gxt_hash(MODEL_LIMO2);
							}
							return;
						}
						if(last_selected[4] == 12){
							add_gxt_hash(MODEL_FAGGIO);
							add_gxt_hash(MODEL_BOBBER);
							add_gxt_hash(MODEL_HELLFURY);
							add_gxt_hash(MODEL_NRG900);
							add_gxt_hash(MODEL_PCJ);
							add_gxt_hash(MODEL_SANCHEZ);
							add_gxt_hash(MODEL_ZOMBIEB);
							if(i == 2){
								add_gxt_hash(MODEL_HEXER);
								add_gxt_hash(MODEL_FAGGIO2);
								add_gxt_hash(MODEL_BATI2);
								add_gxt_hash(MODEL_VADER);
								add_gxt_hash(MODEL_AKUMA);
								add_gxt_hash(MODEL_HAKUCHOU);
								add_gxt_hash(MODEL_DOUBLE);
							}
							return;
						}
						if(last_selected[4] == 13){
							add_gxt_hash(MODEL_DINGHY);
							add_gxt_hash(MODEL_JETMAX);
							add_gxt_hash(MODEL_MARQUIS);
							add_gxt_hash(MODEL_PREDATOR);
							add_gxt_hash(MODEL_REEFER);
							add_gxt_hash(MODEL_SQUALO);
							add_gxt_hash(MODEL_TROPIC);
							add_gxt_hash(MODEL_TUGA);
							if(i == 2){
								add_gxt_hash(MODEL_SMUGGLER);
								add_gxt_hash(MODEL_FLOATER);
								add_gxt_hash(MODEL_BLADE);
							}
							return;
						}
						if(last_selected[4] == 14){
							add_gxt_hash(MODEL_ANNIHILATOR);
							add_gxt_hash(MODEL_TOURMAV);
							add_gxt_hash(MODEL_MAVERICK);
							add_gxt_hash(MODEL_POLMAV);
							if(i == 2){
								add_gxt_hash(MODEL_BUZZARD);
								add_gxt_hash(MODEL_SWIFT);
								add_gxt_hash(MODEL_SKYLIFT);
							}
							return;
						}
					}
				}
				if(last_selected[2] > 2){
					if(last_selected[3] == 5){
						if(last_selected[4] == 1){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Troll Vehicle",true);
							add_item("Delete Vehicle",true);
							add_item("Slingshot Vehicle",true);
							add_item("Screw Up Vehicle",true);
							add_item("Shut Down Vehicle",true);
							add_item("Freeze Vehicle",true);
							add_item("Steal Vehicle",true);
							add_item("Glitch Vehicle",true);
							add_item("Road Block",true);
							return;
						}
						if(last_selected[4] == 2){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Speed Boost",true);
							add_item("Speed Brake",true);
							add_item("Remote Control",true);
							add_item("Heli Pickup",true);
							add_item("Tow Truck",true);
							return;
						}
						if(last_selected[4] == 7){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Set Car Invisible",true);
							add_item("Set Car Visible",true);
							return;
						}
						if(last_selected[4] == 8){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Black",true);
							add_item("White",true);
							add_item("Blue",true);
							add_item("Red",true);
							add_item("Purple",true);
							add_item("Pink",true);
							add_item("Yellow",true);
							add_item("Orange",true);
							add_item("Green",true);
							return;
						}
						if(last_selected[4] == 9){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Blue",true);
							add_item("Yellow",true);
							add_item("Green",true);
							add_item("Red",true);
							add_item("Pink",true);
							add_item("Orange",true);
							return;
						}
						if(last_selected[4] == 10){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Collision: On",true);
							add_item("Collision: Off",true);
							return;
						}
					}
					if(last_selected[3] == 6){
						if(last_selected[4] == 7){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Freeze Gun",true);
							add_item("Group Hack",true);
							add_item("All",true);
							return;
						}
					}
					if(last_selected[3] == 8){
						if(last_selected[4] == 1){
							footer = players[(last_selected[2] - 3)].gamertag;
							add_item("Order to Kill",true);
							add_item("Relationship: Friendly",true);
							add_item("Relationship: Enemy",true);
							return;
						}
					}
					if(last_selected[3] == 9){
						i = GET_CURRENT_EPISODE();
						footer = players[(last_selected[2] - 3)].gamertag;
						if(last_selected[4] == 1){
							add_gxt_hash(MODEL_BANSHEE);
							add_gxt_hash(MODEL_COMET);
							add_gxt_hash(MODEL_COQUETTE);
							add_gxt_hash(MODEL_FELTZER);
							add_gxt_hash(MODEL_INFERNUS);
							add_gxt_hash(MODEL_SULTAN);
							add_gxt_hash(MODEL_SULTANRS);
							add_gxt_hash(MODEL_SUPERGT);
							add_gxt_hash(MODEL_TURISMO);
							if(i == 2){
								add_gxt_hash(MODEL_BUFFALO);
								add_gxt_hash(MODEL_BULLET);
								add_gxt_hash(MODEL_F620);
							}
							return;
						}
						if(last_selected[4] == 2){
							add_gxt_hash(MODEL_BUCCANEER);
							add_gxt_hash(MODEL_DUKES);
							add_gxt_hash(MODEL_FACTION);
							add_gxt_hash(MODEL_MANANA);
							add_gxt_hash(MODEL_PEYOTE);
							add_gxt_hash(MODEL_RUINER);
							add_gxt_hash(MODEL_SABRE);
							add_gxt_hash(MODEL_SABREGT);
							add_gxt_hash(MODEL_STALION);
							add_gxt_hash(MODEL_VIGERO);
							add_gxt_hash(MODEL_VIRGO);
							add_gxt_hash(MODEL_VOODOO);
							if(i == 2)
								add_gxt_hash(MODEL_TAMPA);
							return;
						}
						if(last_selected[4] == 3){
							add_gxt_hash(MODEL_BLISTA);
							add_gxt_hash(MODEL_FORTUNE);
							add_gxt_hash(MODEL_FUTO);
							add_gxt_hash(MODEL_SENTINEL);
							add_gxt_hash(MODEL_URANUS);
							if(i == 2){
								add_gxt_hash(MODEL_SUPERD2);
							}
							return;
						}
						if(last_selected[4] == 4){
							add_gxt_hash(MODEL_ADMIRAL);
							add_gxt_hash(MODEL_CHAVOS);
							add_gxt_hash(MODEL_COGNOSCENTI);
							add_gxt_hash(MODEL_DF8);
							add_gxt_hash(MODEL_DILETTANTE);
							add_gxt_hash(MODEL_EMPEROR);
							add_gxt_hash(MODEL_ESPERANTO);
							add_gxt_hash(MODEL_FEROCI);
							add_gxt_hash(MODEL_HAKUMAI);
							add_gxt_hash(MODEL_INGOT);
							add_gxt_hash(MODEL_INTRUDER);
							add_gxt_hash(MODEL_LOKUS);
							add_gxt_hash(MODEL_MARBELLA);
							add_gxt_hash(MODEL_MERIT);
							return;
						}
						if(last_selected[4] == 5){
							add_gxt_hash(MODEL_ORACLE);
							add_gxt_hash(MODEL_PINNACLE);
							add_gxt_hash(MODEL_PMP600);
							add_gxt_hash(MODEL_PREMIER);
							add_gxt_hash(MODEL_PRES);
							add_gxt_hash(MODEL_PRIMO);
							add_gxt_hash(MODEL_ROM);
							add_gxt_hash(MODEL_SCHAFTER);
							add_gxt_hash(MODEL_SOLAIR);
							add_gxt_hash(MODEL_STRATUM);
							add_gxt_hash(MODEL_VINCENT);
							add_gxt_hash(MODEL_WASHINGTON);
							add_gxt_hash(MODEL_WILLARD);
							if(i == 2){
								add_gxt_hash(MODEL_SCHAFTER2);
								add_gxt_hash(MODEL_SCHAFTER3);
								add_gxt_hash(MODEL_SUPERD);
							}
							return;
						}
						if(last_selected[4] == 6){
							add_gxt_hash(MODEL_EMPEROR2);
							add_gxt_hash(MODEL_SABRE2);
							add_gxt_hash(MODEL_VIGERO2);
							return;
						}
						if(last_selected[4] == 7){
							add_gxt_hash(MODEL_BOBCAT);
							add_gxt_hash(MODEL_CAVALCADE);
							add_gxt_hash(MODEL_FXT);
							add_gxt_hash(MODEL_E109);
							add_gxt_hash(MODEL_HABANERO);
							add_gxt_hash(MODEL_HUNTLEY);
							add_gxt_hash(MODEL_LANDSTALKER);
							add_gxt_hash(MODEL_MINIVAN);
							add_gxt_hash(MODEL_MOONBEAM);
							add_gxt_hash(MODEL_PATRIOT);
							add_gxt_hash(MODEL_PERENNIAL);
							add_gxt_hash(MODEL_RANCHER);
							add_gxt_hash(MODEL_REBLA);
							if(i == 2){
								add_gxt_hash(MODEL_SERRANO);
								add_gxt_hash(MODEL_SERRANO2);
								add_gxt_hash(MODEL_CAVALCADE2);
								add_gxt_hash(MODEL_SLAMVAN);
							}
							return;
						}
						if(last_selected[4] == 8){
							add_gxt_hash(MODEL_AIRTUG);
							add_gxt_hash(MODEL_BENSON);
							add_gxt_hash(MODEL_BIFF);
							add_gxt_hash(MODEL_BOXVILLE);
							add_gxt_hash(MODEL_BURRITO);
							add_gxt_hash(MODEL_FLATBED);
							add_gxt_hash(MODEL_FEROCI2);
							add_gxt_hash(MODEL_PERENNIAL2);
							add_gxt_hash(MODEL_FORKLIFT);
							add_gxt_hash(MODEL_BURRITO2);
							add_gxt_hash(MODEL_MRTASTY);
							add_gxt_hash(MODEL_MULE);
							add_gxt_hash(MODEL_PACKER);
							add_gxt_hash(MODEL_PHANTOM);	
							return;
						}
						if(last_selected[4] == 9){
							add_gxt_hash(MODEL_PONY);
							add_gxt_hash(MODEL_RIPLEY);
							add_gxt_hash(MODEL_STOCKADE);
							add_gxt_hash(MODEL_SPEEDO);
							add_gxt_hash(MODEL_STEED);
							add_gxt_hash(MODEL_YANKEE);
							if(i == 2)
								add_gxt_hash(MODEL_CADDY);
								add_gxt_hash(MODEL_AVAN);
							return;
						}
						if(last_selected[4] == 10){
							add_gxt_hash(MODEL_AMBULANCE);
							add_gxt_hash(MODEL_NSTOCKADE);
							add_gxt_hash(MODEL_FBI);
							add_gxt_hash(MODEL_FIRETRUK);
							add_gxt_hash(MODEL_NOOSE);
							add_gxt_hash(MODEL_POLPATRIOT);
							add_gxt_hash(MODEL_POLICE);
							add_gxt_hash(MODEL_POLICE2);
							add_gxt_hash(MODEL_PSTOCKADE);
							if(i == 2){
								add_gxt_hash(MODEL_APC);
								add_gxt_hash(MODEL_POLICE3);
								add_gxt_hash(MODEL_POLICEW);
								add_gxt_hash(MODEL_POLICE4);
								add_gxt_hash(MODEL_POLICEB);						
							}
							return;
						}
						if(last_selected[4] == 11){
							add_gxt_hash(MODEL_BUS);
							add_gxt_hash(MODEL_CABBY);
							add_gxt_hash(MODEL_ROMERO);
							add_gxt_hash(MODEL_TAXI);
							add_gxt_hash(MODEL_TAXI2);
							add_gxt_hash(MODEL_TRASH);
							add_gxt_hash(MODEL_STRETCH);
							if(i == 2){
								add_gxt_hash(MODEL_LIMO2);
							}
							return;
						}
						if(last_selected[4] == 12){
							add_gxt_hash(MODEL_FAGGIO);
							add_gxt_hash(MODEL_BOBBER);
							add_gxt_hash(MODEL_HELLFURY);
							add_gxt_hash(MODEL_NRG900);
							add_gxt_hash(MODEL_PCJ);
							add_gxt_hash(MODEL_SANCHEZ);
							add_gxt_hash(MODEL_ZOMBIEB);
							if(i == 2){
								add_gxt_hash(MODEL_HEXER);
								add_gxt_hash(MODEL_FAGGIO2);
								add_gxt_hash(MODEL_BATI2);
								add_gxt_hash(MODEL_VADER);
								add_gxt_hash(MODEL_AKUMA);
								add_gxt_hash(MODEL_HAKUCHOU);
								add_gxt_hash(MODEL_DOUBLE);
							}
							return;
						}
						if(last_selected[4] == 13){
							add_gxt_hash(MODEL_DINGHY);
							add_gxt_hash(MODEL_JETMAX);
							add_gxt_hash(MODEL_MARQUIS);
							add_gxt_hash(MODEL_PREDATOR);
							add_gxt_hash(MODEL_REEFER);
							add_gxt_hash(MODEL_SQUALO);
							add_gxt_hash(MODEL_TROPIC);
							add_gxt_hash(MODEL_TUGA);
							if(i == 2){
								add_gxt_hash(MODEL_SMUGGLER);
								add_gxt_hash(MODEL_FLOATER);
								add_gxt_hash(MODEL_BLADE);
							}
							return;
						}
						if(last_selected[4] == 14){
							add_gxt_hash(MODEL_ANNIHILATOR);
							add_gxt_hash(MODEL_TOURMAV);
							add_gxt_hash(MODEL_MAVERICK);
							add_gxt_hash(MODEL_POLMAV);
							if(i == 2){
								add_gxt_hash(MODEL_BUZZARD);
								add_gxt_hash(MODEL_SWIFT);
								add_gxt_hash(MODEL_SKYLIFT);
							}
							return;
						}
					}
				}
			}
		}
	}
}

void reset_menu(void){
	for(i = 1;i <= item_count;i++){
		menu[i].action = false;
		menu[i].type = 0;
	}
	menu_setup();
}