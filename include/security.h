//Leave unchanged unless you know what your doing
#define PERSONAL
//#define EMMAN
#define PRIVATE 
//#define PREVIEW
#define RELEASE
#define GTCHECK
#define ENGLISH
//#define SPANISH
//#define FRENCH
//#define PC

#ifndef PERSONAL
#ifdef PRIVATE
#define MENU_TITLE "XMC ModMenu v6.0 Private"
#else
#define MENU_TITLE "XMC ModMenu v6.0 Public"
#endif
#else
#define MENU_TITLE "XMC ModMenu v6.0 Admin"
#endif

#define MENU_AUTHOR "Emmanuel Utomi - Emman V4"

bool GTcheck(char *GT, char *safeGT, int safelenght, uint charhash){
	int lenght;
	uint hash;
	lenght = GET_LENGTH_OF_LITERAL_STRING(GT);
	hash = GET_HASH_KEY(GT);
	return (COMPARE_STRING(GT, safeGT) && lenght == safelenght && hash == charhash);
}

bool is_admin(uint index){
	return false;
}

bool is_whitelisted(uint index){
	return false;
}

bool is_mambalisted(uint index){
	if (GTcheck(GET_PLAYER_NAME(index), "Emman V2", 8, 1828690324)) return true;
	if (GTcheck(GET_PLAYER_NAME(index), "KyranKool240", 12, 416359888)) return true;
	if (GTcheck(GET_PLAYER_NAME(index), "MalleikJhamal", 13, 1119530041)) return true;
	if (GTcheck(GET_PLAYER_NAME(index), "TimmyB099", 9, -1557747429)) return true;
	if (GTcheck(GET_PLAYER_NAME(index), "CRAZYTWINKLExX", 14, 2085509816)) return true;
	if (GTcheck(GET_PLAYER_NAME(index), "Th1sAZNGuy", 10, -2102623145)) return true;
	if (GTcheck(GET_PLAYER_NAME(index), "JMT x EXPLiCiT", 14, -1020681761)) return true;
	return false;
}

bool GTchecklist(char *GT){
	return false;
}
