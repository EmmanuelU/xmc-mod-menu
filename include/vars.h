/**
	Settings, Keybinds, and Structure for core
	by: Herr Muskelprotze

**/

//Xbox 360 buttons
#define BUTTON_SELECT 0xD
#define BUTTON_START 0xC
#define BUTTON_X 0xE
#define BUTTON_Y 0xF
#define BUTTON_A 0x10
#define BUTTON_B 0x11
#define DPAD_UP 0x8
#define DPAD_DOWN 0x9
#define DPAD_LEFT 0xA
#define DPAD_RIGHT 0xB
#define BUTTON_L 0x5
#define BUTTON_R 0x7
#define BUTTON_LB 0x4
#define BUTTON_RB 0x6
#define STICK_LEFT 0x12
#define STICK_RIGHT 0x13

//PS3 Buttons
#define L3  0x12
#define L2  0x5
#define R2  0x7
#define L1  0x4
#define R1  0x6
#define START      0xC
#define SELECT     0xD
#define SQUARE     0xE
#define TRIANGLE   0xF
#define X          0x10
#define CIRCLE     0x11
#define STICK_L    0x12  //L3
#define STICK_R    0x13  //R3

int MENU_LENGHT,MENU_HASH;

typedef struct _menu_struct{
	char* item_name;
	bool action;
	int type;
	int value;
	int extra_val;
	int maxval;
} menu_struct;

menu_struct menu[20];

typedef struct _online_players{
	char* gamertag;
	Ped ped;
	int id;
	bool mprotection;
	bool force;
	bool rage;
	bool water;
	bool disarm;
	bool rocket;
	bool cargun;
	
} online_players;

online_players players[17];

int item_count = 0,
	item_select = 1,
	menu_level = 0,
	player_count = 0,
	last_selected[5];

uint r,g,b,a,s_r,s_g,s_b,s_a;
Ped pPlayer;

uint color1,color2,color3,color4;

uint model;
uint limo_model;
uint cubes[6];
uint test,guards;
Ped rocketped[3];
int tmp;
Object otmp;
Object tanker;
Blip XmcBlip;
uint object_launch = 0x3675A6C3;
uint car_launch = MODEL_SULTANRS;
Vector3 aim,spawn,force,limo;
Ped LimoDriver;
Vehicle LimoCar;
Ped online_char;
Camera XmcCam;
Camera gta2cam;
Camera spectateCam;
Ped spectatePed;
//uint rocket_ship_model = 0x19AF4794;
//uint inferno_fire_model = 0xF3C45209;
uint tick;
//Object Inferno_obj;
Ped driver, ClosestChar;
Vehicle pveh, paveh;
Group Bgroup, Pgroup;
float x, y, z, dist, heading, zoom = 1.0;
float mx,my,mz,savex,savey,savez;
float speed, angle, angle2;
int wep;
Ped gameped[7];
Ped CharProjectile;
Ped group_onlineped;
Ped shortcut_players[7];
char* footer;
Object admin_obj;
Vehicle CarProjectile;
Object ObjectProjectile;
bool grenade_active;
Vehicle superlock_veh;
float pos_y;
	
bool in_paint = false;	
bool xmc_in_game = false;
Ped xmc_char;

int i;
int nvid;

bool xmc1 = false,
	xmc2 = false,
	xmc3 = false,
	xmc4 = false,
	xmc5 = false,
	xmc6 = false,
	xmc7 = false,
	xmc8 = false,
	xmc9 = false,
	xmc10 = false,
	xmc11 = false,
	xmc12 = false,
	xmc13 = false,
	xmc14 = false,
	xmc15 = false,
	xmc16 = false,
	xmc17 = false,
	xmc18 = false;

bool show_menu = false,
	xmc_compact = false,
	xmc_chat = true,
	xmc_dim = false,
	xmc_online_col = true,
	xmc_keyboard = false,
	xmc_switch = false,
	xmc_tele = false,
	xmc_disable = false,
	godmode = true,
	veh_hazard = false,
	veh_indic = false,
	gravity = false,
	xyzh = false,
	group_loop = false,
	helistrike = false,
	bikefly = false,
	rocketgun = false,
	dragongun = false,
	collision = false,
	inferno = false,
	neverwanted = true,
	superfight = false,
	rb_checker = false,
	objectgun = false,
	exp_cargun = false,
	ninja = false,
	rblip = false,
	del_cargun = true,
	strat_cargun = false,
	grond_cargun = true,
	grav_cargun = false,
	cargun = false,
	pedgun = false,
	carjump = false,
	powgun = false,
	vehinvis = false,
	vehwater = false,
	rapidfire = false,
	slowmotion = false,
	freezecar = false,
	rainbowcar = false,
	bw_checker = false,
	autoflip = false,
	fastreload = true,
	lowerpveh = false,
	bpvest = false,
	autoaim = false,
	pprotection = false,
	fweather = false,
	rweather = false,
	superrun = false,
	rainbowmenu = false,
	nos = false,
	wepvisible = true,
	del_objgun = true,
	rocket = false,
	rocketveh = false,
	hydrolics = false,
	veh_height = false,
	superjump = false,
	view_online_player = false,
	limo_loop = false,
	limo_land = false,
	chronicle = false,
	chaos = false,
	vhelper = true,
	modderprotect = true,
	carsonground = false,
	nfs = false,
	drive_free = true,
	ragdoll = false;