// header
#include "map.hpp"

// stlib
#include <cmath>
#include <iostream>

Texture Map::wall_texture;
Texture Map::corridor_texture;
Texture Map::wall_light_texture;

Texture Map::corridor_texture_red;
Texture Map::corridor_texture_blue;
Texture Map::corridor_texture_green;
Texture Map::corridor_texture_yellow;

Texture Map::trophy_texture;

// 800 * 1200 Map of Level 1
// 61 for the \n of all chars
// W = Wall, S = Wall_Shadow, R = Red Tile, G = Green tile, B = Blue Tile, Y = Yellow Tile, C = Plain_Corridor
char level_test[40][61] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WCCCCCGGGGGGGGGGGGGGGGGGGGYYYYYRRRRRRRRRRRCCCCCCCCCCCCCCCCCW",
	"WCCCCCGGGGGGGGGGGGGGGGGGGGYYYYYRRRRRRRRRRRCCCCCCCCCCCCCCCCCW",
	"WCCCCCGGGGGGGGGGGGGGGGGGGGYYYYYRRRRRRRRRRRCCCCCCCCCCCCCCCCCW",
	"WCCCCCGGGGGGGGGGGGGGGGGGGGYYYYYRRRRRRRRRRRCCCCCCCCCCCCCCCCCW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWCCCCCWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWCCCCCWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWCCZCCWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWCCCCCWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WCCCCCWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBWWWWWWWGGGGGW",
	"WYYYYYBBBBBBBBBBBBBBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCW",
	"WYYYYYBBBBBBBBBBBBBBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCW",
	"WYYYYYBBBBBBBBBBBBBBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCW",
	"WYYYYYWWWWWWWWWWWWWBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCW",
	"WYYYYYWWWWWWWWWWWWWBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCW",
	"WYYYYYWWWWWWWWWWWWWBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WYYYYYWWWWWWWWWWWWWBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WYYYYYWWWWWWWWWWWWWBBBWWWWWWWWWWWWWCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WYYYYYWWWWWWWWWWWWWBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WYYYYYWWWWWWWWWWWWWBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WYYYYYWWWWWWWWWWWWWBBBBBCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWCCCCCCCCCCCCCCCCCCCCCCCCCCCWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWGGGGGGGGGGGWWWWWWWWWWWWWWWWWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWGGGGGGGGGGGWWWWWWWWWWWWWWWWWWWRRRRRW",
	"WCCCCCWWWWWWWWWWWWWWWWWWGGGGGGGGGGGWWWWWWWWWWWWWWWWWWWRRRRRW",
	"WCCCCCRRRRRRRRRRRRRRRRRRCCCCCCCCCCCYYYYYYYYYYYYYYYYYYYCCCCCW",
	"WCCCCCRRRRRRRRRRRRRRRRRRCCCCCCCCCCCYYYYYYYYYYYYYYYYYYYCCCCCW",
	"WCCCCCRRRRRRRRRRRRRRRRRRCCCCCCCCCCCYYYYYYYYYYYYYYYYYYYCCCCCW",
	"WCCCCCRRRRRRRRRRRRRRRRRRCCCCCCCCCCCYYYYYYYYYYYYYYYYYYYCCCCCW",
	"WCCCCCRRRRRRRRRRRRRRRRRRCCCCCACCCCCYYYYYYYYYYYYYYYYYYYCCCCCW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};


char level_tutorial[40][61] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSW",
	"WCCCCCRRRRRRRRRRRRRRRRRRRRRRRRRRRCCBBBBBCCGGGGGCCYYYYYCCCCCW",
	"WCCCCCRRRRRRRRRRRRRRRRRRRRRRRRRRRCCBBBBBCCGGGGGCCYYYYYCCCCCW",
	"WCCZCCRRRRRRRRRRRRRRRRRRRRRRRRRRRCCBBBBBCCGGGGGCCYYYYYCCCACW",
	"WCCCCCRRRRRRRRRRRRRRRRRRRRRRRRRRRCCBBBBBCCGGGGGCCYYYYYCCCCCW",
	"WCCCCCRRRRRRRRRRRRRRRRRRRRRRRRRRRCCBBBBBCCGGGGGCCYYYYYCCCCCW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"};

char level_1[40][61] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WSSSSSSWSSSSSSSSSWSSSWSSSSSSSSSSSSSSSSSSSSSSSSSSSSWSSSSSSSSW",
	"WBBBBBBWYYYYYYYYYWRRRWBBBBBBBBBBBBBBBBBBBBBBBBBBBBWCCCCCCCCW",
	"WBBBBBBSYYYYYYYYYSRRRSBBBBBBBBBBBBBBBBBBBBBBBBBBBBWCCCCCCZCW",
	"WBBBBBBBYYYYYYYYYRRRRRRRWWWWWWWWWWBWWWWWWWBBWWWWBBSWCCCCCCCW",
	"WBBBBBBBYYYYYYYYYRRRRRRRSSSSSSSWSSBSSWSSSSBBSSSWBBBWCCCCCCCW",
	"WBBBBBBWYYYYYYYYYWRRRRRRRRRRRRRWGGGGGWCCCCCCCCCSBBBSWCCCCCCW",
	"WWWBBWWWWWWWWWWYYWRRRWWWWWWWWRRWGGGGGWCCCCCCCCCCCCCCSCCCCCCW",
	"WSSBBSSSSSSSSSSYYWRRRWSSSSSSSRRWGGGGGWCCCCCCCCCCCCCCCCCCCCCW",
	"WRRRRRRRYYYYYYBBBWRRRWGGGGGGGGGWGGGGGWCCCCCCCCCCCCCCCCWCCCCW",
	"WRRRRRRWYYYYYYWBBWRRRWGGWWWWWWWWGGGGGWCCCCCCCCCCCCCCCCSWWCCW",
	"WRRRRRRWYYYYYYWBBWRRRSGGSSSSSSSSGGGGGSCCCCCCCCCCCCCCCCCSSWWW",
	"WRRWWWWWWWWWWWWWWWRRRBBBBBBBBBBBBBBBBBCCCCCCCCCCCCCCCCCCCSSW",
	"WRRSSSSSSSSSSSSSSWRRRWBBWWWWWWWWWWWBBWCCCCCCCCCCCCCCCCCCCCCW",
	"WGGGGGGGGGGGGGGGGWRRRWBBSSSWSSSSSSSBBWCCCCCCCCCCCCCCCCCCCCCW",
	"WWWWWWWWWWWGGWYYYWRRRWRRRRRSWYYYYYYYYSWCCCCCCCCCCCCCCCCCCCCW",
	"WSSSSSSSSSSGGWYYYWRRWWWWWRRRSWYYYYYYYYSWGGGWWWWWWWWWWWWRRRWW",
	"WBBBBBBBBBBBBWYYYSRRSSSSSWRRRSWYYYYYYYWSGGWSSSSSSSSSSWSRRRSW",
	"WBBBBBBBBBBBBWYYYYYYBBBBBSWRRRSWYYYYYWSGGWSRRGGGGGGGGWRRRRRW",
	"WWWWWWBBWWWWWWYYYYYYBBBBBBSWRRRSYYYYWSGGWSRRWGGGGGGGGWRRRRRW",
	"WSSSSSBBSSSSSWYYYWWWWWWWWBBSWRRRYYYWSGGWWRRWWGGWWWWGGWWWRWWW",
	"WCCCCCCCCCCCCWYYYWSSSSSSSWBBSWRRYYWSGGWSSRRSSGGSSSSGGSSSRSSW",
	"WCCCCCCCCCCCCWYYYWYYYYYYYSWBBSWWWWSGGWSRRRRRRGGGGGGGGBBBBBBW",
	"WCCCCCCCCCCCCWYYYWYYYYYYYYSWBBSSSSGGWSRRRWWWWGGWWWWGGWWWWWWW",
	"WCCCCCCCCCCCWSYYYSWYYYYYYYYSWBBBGGGWSRRRWSSSSGGSSSSGGSSSSSSW",
	"WCCCCCCCCCCWSCCCCCSWYYYYYYYYWBBBGGGWRRRWSYYYYYYYYYYYYYYYYYYW",
	"WCCCCCCCCCWSCCCCCCCSWYYYYYYYSWWBGWWSRRWSYYYYYYYYYYYYYYYYYYYW",
	"WCCCCCCCCCWCCCCCCCCCSYYYYYYYYSSBGSSRRRWYYYYYYYYYYYYYYYYYYYYW",
	"WCCCCCCCCWSCCCCCCCCCCWYYYYYYYYYYRRRRRWSYYYYYYYYYYYYYYYYYYYYW",
	"WCCCCCCCCWCCCCCCCCCCCWWWWWYYWWWWWWWWWWYYWWWWBBWWWWWGGWWWRRWW",
	"WCCCCCCCWSCCWWWWWWWCCSWSSSYYSSSWSSSSSWYYWSSSBBSSSWSGGSWSRRSW",
	"WCCCCCCCWCCCSSSSSSSCCCWBBBBBBBBWRRRRRWYYWBBBBBBBBWGGGGWRRRRW",
	"WCCCCCCCWCCCCCCCCCCCCCSBBBBBBBBSRRRRRSYYSBBBBBBBBSGGGGSRRRRW",
	"WCCCCCCCWCCCCCCCCCCCCCBBBBBBBBBBRRRRRRYYBBBBBBBBBBGGGGGRRRRW",
	"WCCCCCCCWCCCWWWWWWWCCCWBBBBBBBBWRRRRRWYYWBBBBBBBBWGGGGWRRRRW",
	"WCCCCCCCWCCCSSSSSSSCCCWWWWBBWWWWRRWWWWYYWWWWBBWWWWWGGWWWRRWW",
	"WCCCCCCCWCCCCCCCCCCCCCSSSSBBSSSSRRSSSSYYSSSSBBSSSSSGGSSSRRSW",
	"WCCCCCCWSCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCW",
	"WCCACCWSCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

char level_2[40][61] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WSSSSSSSSSSWSSSSSSSSSSSWSSSSSSSSSSSSSWSSSSSSSSSWSSSSSSSSSSSW",
	"WGGGGGGGGGGWYYYYYYYYYYYWRRYYYYYYYYYYYWBBBBZBBBBWWBBBBBBBBBBW",
	"WGGGWWWWGGGSYYYYYYYYYYYWRRWWWWWWWWYYYWWWWWWWBBBSWWBBBBBBBBBW",
	"WGGGSSSSGGGYYYYYYYYYYYYWRWWSSSSSSSYYYWSSSSSWWBBBSWWWWWWWWBBW",
	"WGGGRRRRGGGWYYYYYYYYYYYWRWSYYYYYYYYYYWGGGGGSWBBBGSSSSSSSWBBW",
	"WWWWWRRWWWWWYYYYYYYYYYYWRWRRRRRRRRRYYWGGGGGGWWBBGGGGGGGBWWBW",
	"WSSSSRRSSSSWBWWWWWWWWWWWRWRRRRRRRRRYYWGGGGGGSWBBWGGGWWWBBWBW",
	"WCCCCRRCCCCWBSSSSSSSSSSWRWRRRRRRRRRRRWGYGWGGGWBBWWWGSSSBBWBW",
	"WWWWWRRWWWWWBBBBBBBBBBBWRWRRRWWWWWRRRWGYWWGGGWBBSSWGGBBBWSBW",
	"WSSSSRRSSSSWWWWWWWWWWWBWRWWRWSSSSSWRRWGYWSGRGWBBRBWRGBWWWBBW",
	"WCCCCRRCCCCWSSSSSSSSSSBWRSWRSBBBBBWWRWGYWGGRGWGGRBWRGBSSSBBW",
	"WWWWWRRWWWWWGGGGGGGGGGGWRRWRBBBBBBSWRWYYWGGRGWGGRBSWGGBBBBBW",
	"WSSSSRRSSSSWGWWWWWWWWWWWRRWBBBBBBBBSRWYYWWGRGWWGRRBWRRGGWWBW",
	"WCCCCRRCCCCWGSSSSSSSSSSWRRWBBBBBWBBBRWYYSWGRRSWGGRBWRRRRSWBW",
	"WWWWWRRWWWWWRRRRRRRRRRRWRRWBBBWWSWBBRWYYYWWRRRWGGRBWRRRRRWBW",
	"WSSSSRRSSSSWWWWWWWWWWWRWRRSBBBSSYWWBRWYYYSWRRRWWGRBSWWRRWWBW",
	"WCCCCRRCCCCWSSSSSSSSSSRWGGGGGGGGYSWWRSYYYYWWRRSWGGRBSWWWWSBW",
	"WWWWWRRWWWWWYYYYYYYYYYYWGGWWWWGGYYSWRRYYYYSWRRBWWGGBBSSWSGGW",
	"WSSSSRRSSSSWYWWWWWWWWWWWGGWSSWWGGYYWRRRYWBBWWRBSWWGBBBBSGGGW",
	"WCCCCRRCCCCWYSSSSSSSSSSWGWSBBSWGGYYSRRRWSGBSWBBRSWWBGGGGGGGW",
	"WWWWWRRWWWWWBBBBBBBBBBBWGWBBBBWWGYYRRRRWGGBGWWBRRSWBGWWGGGGW",
	"WSSSSRRSSSSWWWWWWWWWWWBWGSBBBBSSGYYRRRRWGGGBSWBRRRWWGSWWGGGW",
	"WCCCCRRCCCCWSSSSSSSSSSBWBBBBBBBGGYYRRRRWGGGBGWBRRRSWGRSWWGYW",
	"WWWWWRRWWWWWGGGGGGGGGGGWBBBBBBBGGYYRRWRWGGGBWWBRRRRWGRYSWYYW",
	"WSSSSRRSSSSWGWWWWWWWWWWWRRWWWBBGGYYRRWRWGGGBWSBRGGGWGRYYWWYW",
	"WCCCCRRCCCCWGSSSSSSSSSSWRWWSSBBGGYYYYWRWGGBBWBBRRRGWWRYYSWYW",
	"WWWWWRRWWWWWRRRRRRRRRRRWRWSGGBBWWWYYYWRWGBBWSBBWWWGSWRYYYWYW",
	"WSSSSRRSSSSWWWWWWWWWWWRWRWWGGBWWSSYYYWRWBBGWBBWWSSGGWRYYYWYW",
	"WCCCCRRCCCCWSSSSSSSSSSRWRSWWGBWSYYYWBWRWBGGWBBSWGGGGWRYYWWYW",
	"WWWWWRRWWWWWYYYYYYYYYYYWRRSWGBWYYYWWBWGWBGGWBBBWGGGGWRYWWSYW",
	"WSSSSRRSSSSWYWWWWWWWWWWWRRRWGBWYYWWSBWGWBGGWBBBSGGGGWRWWSYYW",
	"WCCCCRRCCCCWYSSSSSSSSSSWRRWWGWWYYWSBBWGWBGGWWBBBGGGGWRWSYYYW",
	"WWWWWRRWWWWWBBBBBBBBBBBWRWWSGWSYYWBBBWGSWBBSSWWWGGGGWRWYYYYW",
	"WSSSSRRSSSSWWWWWWWWWWWBWRWSGGWYYYWWBBWGGWWBBBSSSWWWWWRWWYYYW",
	"WCCCCRRCCCCWSSSSSSSSSSBSRWWGGWYYYSWBBWGGSWBBBYYYSSSSSRSWYYYW",
	"WWWWWRRWWWWWYYYYYYYYYYYYRSWGGSYYWWWBBWGGGWWWBBYYYYYRRRRWWWYW",
	"WSSSSRRSSSSWYYYYYYYYYYYYRRSGGGYYSSSBBWGGGSSSGRRRRRYYYYRSSSYW",
	"WCACCRRCCCCWYYYYYYYYYYYYGGGGGGBBBBBBBWGGGGGGGRRRRRRRRRYYYYYW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

char level_3[40][61] = {
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW",
	"WSSSSSSSSSSSSWSSSSSWSSSSSSSSSWSSSSSSSSSSSSSSSSSSSSSSSSSSSSSW",
	"WBBBBBBBBBBBBWCCCCCWBBGGGGGGGWGGGGGGGGGGGGGGBBBBBBBBBBBBBYYW",
	"WBBBBBBBBBBBBWCCCCCWBBGGGGGGGWGGGGGGGGGGGGGGBBBBBBBBBBBBBYYW",
	"WBBWWWWWWWWWWWCCCCCWBBWWWWWWWWGGWWWWWWWWWWWWWWWWWWWWWWWWWYYW",
	"WBBSSSSSSSSSSSCCCCCWBBWSSSSSSSGGSSSSSSSWSSSSSSSSSSSSSSSSSYYW",
	"WRRRRRRRRRRRRCCCCCCWBBWCCCCCCCCCCCCCCCCWRRRRRRRRRRRRRRRRRRRW",
	"WRRRRRRRRRRRRCCCCCCWBBWCCCCCCCCCCCCCCCCWRRRRRRRRRRRRRRRRRRRW",
	"WRRWWWWWWWWWWCCCCCCSBBWCCCCCCCCCCCCCCCCWRRWWWWWWWWWWWWWWWYYW",
	"WRRSSSSSSSSSWCCCCCCBBBWCCCCCCCZCCCCCCCCWRRWSSSSSSSSSSSSSWYYW",
	"WGGGGGGGGGGGWCCCCCCBBBWCCCCCCCCCCCCCCCCWRRWCCCCCCCCCCCCCWYYW",
	"WGGGGGGGGGGGWWWWWWWWWWWWWWWWWWWWWWWWWWWWRRWCCCCCCCCCCCCCWYYW",
	"WWWWWWWWWWGGWSSSSSSSSSSSSSSSSSSSSSSSSSSWRRSWCCCCCCCCCCCCWYYW",
	"WSSSSSSSSSGGWBBBBBBBBBBBBBBBBBBBBBBBBBBWRRRSWWWWWWWCCWWWWWWW",
	"WBBBBBBBBBGGWBBBBBBBBBBBBBBBBBBBBBBBBBBWRRRRSSSSSSSCCSSSSSSW",
	"WBBBBBBBBBGGWRRWWWWWWWWWWWWWWWWWWWWWWWWWWWBBBBBBBBBBBBBBBYYW",
	"WWWWWWWBBWGGWRRWSSSSSSSSSSSSSSSSWSSWSSWSSWBBBBBBBBBBBBBBBYYW",
	"WSSSSSSBBWGGSRRWYYYYYYYYYYYYYYYYWGGWBBWRRWWWWWWWWWWWWWWWWYYW",
	"WCCCCCCCCWRRRRRWYYYYYYYYYYYYYYYYWGGWBBWRRWSSSSSSSSSSSSWSSYYW",
	"WCCCCCCCCWRRRRRWYYWWWWWWWWWYYWWWWGGWBBWRRWYYYYYYYYYYYYWCCCCW",
	"WCCCCCCCCWRRWWWWYYWSSSSSSSSYYSSSSGGWBBWRRSYYYYYYYYYYYYWCCCCW",
	"WCCCCCCCCWRRWSSWYYWGGGGGGGGGGGGGGGGWBBWRRRRRWWWWWWWWYYWCCCCW",
	"WCCCCCCCCWRRWBBWYYWGGGGGGGGGGGGGGGGWBBWRRRRRWSSSSSSSYYWCCCCW",
	"WCCCCCCCCWRRWBBWYYWGGWWWWWWWWWWWWWWWBBWRRWWWWBBBBBBBYYWCCCCW",
	"WRRWWWWWWWBBSBBSYYSGGSSWSSSSSSSSSSSSBBWRRWSSWBBBBBBBYYWCCCCW",
	"WRRSSSSSSWBBBBBCCCCCCCCWRRRRRRRRRRRRBBWRRWRRWWWWWWWWWWWCCCCW",
	"WRRRRRRRRWBBBBBCCCCCCCCWRRRRRRRRRRRRBBWRRWRRSSSSSSWSSSSCCCCW",
	"WRRRRRRRRWWWWWWCCCCCCCCWWWWWWWWWWWWWBBWRRWRRRRRRRRWGGYYCCCCW",
	"WWWWWWWRRWSSSSWCCCCCCCCWSSSSSSSSSSSSBBSRRSRRRRRRRRWGGYYCCCCW",
	"WSSSSSWRRWGGGGWCCCCCCCCWGGGGGGGGGGGGGGGGGGRRRRRRRRWGGWWWWWWW",
	"WYYYYYWRRWGGGGWWWWWWWBBWGGGGGGGGGGGGGGGGGGRRRRRRRRWGGSSSSSSW",
	"WYYYYYWRRWWWRRWSSSSSWBBWRRWWWWWWWWWWWWWBBWWWWWWWRRWGGGGGGGGW",
	"WCCWRRSRRSSSRRWGGGGGWBBSRRWSSSSSSSSSSSWBBWSSSSSWRRWGGGGGGGGW",
	"WCCWRRRRRRRRRRWGGGGGWBBBRRWBBBBBBBBBBBWBBWYYYYYWRRWWWWWWWGGW",
	"WCCWRRRRRRRRRRWGGWBBWBBBRRWBBBBBBBBBBBWBBWYYYYYWRRWSSSSSSBBW",
	"WCCWGGWWWWWWWWWGGWBBWWWWRRWBBWWWWWWWWWWBBWYYWBBWWWWBBBBBBBBW",
	"WCCWGGSSSSSSSSSGGWBBSSSWRRWBBSSSSSSSSSSBBSYYWBBSSSSBBBBBBBBW",
	"WCCWGGGGGGGGGGGGGWBBBBBWRRWGGGGGGGGGGGGGGGYYWBBBBBBBBBBBBBBW",
	"WACWGGGGGGGGGGGGGWBBBBBWRRWGGGGGGGGGGGGGGGYYWBBBBBBBBBBBBBBW",
	"WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW"
};

bool Map::init()
{
	m_dead_time = -1;

	// load shared texture
	if (!wall_texture.is_valid())
	{
		if (!wall_texture.load_from_file(textures_path("wall_tile.png")))
		{
			fprintf(stderr, "Failed to load wall texture!");
			return false;
		}
	}

	if (!wall_light_texture.is_valid())
	{
		if (!wall_light_texture.load_from_file(textures_path("wall_tile_light.png")))
		{
			fprintf(stderr, "Failed to load wall texture!");
			return false;
		}
	}

	if (!corridor_texture.is_valid())
	{
		if (!corridor_texture.load_from_file(textures_path("corridor_tile.png")))
		{
			fprintf(stderr, "Failed to load corridor texture!");
			return false;
		}
	}

	if (!corridor_texture_red.is_valid())
	{
		if (!corridor_texture_red.load_from_file(textures_path("corridor_tile_red.png")))
		{
			fprintf(stderr, "Failed to load corridor texture!");
			return false;
		}
	}

	if (!corridor_texture_blue.is_valid())
	{
		if (!corridor_texture_blue.load_from_file(textures_path("corridor_tile_blue.png")))
		{
			fprintf(stderr, "Failed to load corridor texture!");
			return false;
		}
	}

	if (!corridor_texture_green.is_valid())
	{
		if (!corridor_texture_green.load_from_file(textures_path("corridor_tile_green.png")))
		{
			fprintf(stderr, "Failed to load corridor texture!");
			return false;
		}
	}

	if (!corridor_texture_yellow.is_valid())
	{
		if (!corridor_texture_yellow.load_from_file(textures_path("corridor_tile_yellow.png")))
		{
			fprintf(stderr, "Failed to load corridor texture!");
			return false;
		}
	}

	if (!trophy_texture.is_valid())
	{
		if (!trophy_texture.load_from_file(textures_path("trophy_texture.png")))
		{
			fprintf(stderr, "Failed to load trophy texture!");
			return false;
		}
	}

	// vertex buffer in local coordinates
	TexturedVertex vertices[4];
	vertices[0].position = {0.f, 20.f, 0.f}; // top left
	vertices[0].texcoord = {0.f, 1.f};
	vertices[1].position = {20.f, 20.f, 0.f}; // top right
	vertices[1].texcoord = {1.f, 1.f};
	vertices[2].position = {20.f, 0.f, 0.f}; // bottom right
	vertices[2].texcoord = {1.f, 0.f};
	vertices[3].position = {0.f, 0.f, 0.f}; // bottom left
	vertices[3].texcoord = {0.f, 0.f};

	// counterclockwise as it's the default opengl front winding direction
	uint16_t indices[] = {0, 3, 1, 1, 3, 2};

	// clea errors
	gl_flush_errors();

	// vertex buffer creation
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(TexturedVertex) * 4, vertices, GL_STATIC_DRAW);

	// index buffer creation
	glGenBuffers(1, &mesh.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * 6, indices, GL_STATIC_DRAW);

	// vertex array (Container for Vertex + Index buffer)
	glGenVertexArrays(1, &mesh.vao);

	// clear errors
	gl_flush_errors();

	if (gl_has_errors())
		return false;

	// load shaders
	if (!effect.load_from_file(shader_path("map.vs.glsl"), shader_path("map.fs.glsl")))
		return false;

	physics.scale = {1.0f, 1.0f};

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 61; j++)
		{
			current_level[i][j] = level_tutorial[i][j];
		}
	}

	return true;
}

// release all graphics resources
void Map::destroy()
{
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ibo);
	glDeleteVertexArrays(1, &mesh.vao);

	effect.release();
}


void Map::draw(const mat3 &projection)
{

	translation_tile = vec2({0.0, 0.0});

	for (int i = 0; i < 40; i++)
	{
		// Increment the row
		for (int j = 0; j < 61; j++)
		{
			if (current_level[i][j] == 'W')
			{
				// Draw a Wall
				draw_element(projection, wall_texture);
			}
			else if (current_level[i][j] == 'S')
			{
				// Draw a Shadow Wall
				draw_element(projection, wall_light_texture);
			}
			else if ((current_level[i][j] == 'C') || (current_level[i][j] == 'A'))
			{
				// Draw a Corridor
				draw_element(projection, corridor_texture);
			}
			else if ((current_level[i][j] == 'Z'))
			{
				// Draw a Corridor
				draw_element(projection, trophy_texture);
			}
			else if (current_level[i][j] == 'R')
			{
				// Draw a Corridor
				draw_element(projection, corridor_texture_red);
			}
			else if (current_level[i][j] == 'B')
			{
				// Draw a Corridor
				draw_element(projection, corridor_texture_blue);
			}
			else if (current_level[i][j] == 'G')
			{
				// Draw a Corridor
				draw_element(projection, corridor_texture_green);
			}
			else if (current_level[i][j] == 'Y')
			{
				// Draw a Corridor
				draw_element(projection, corridor_texture_yellow);
			}

			translation_tile.x += 20.0;
		}
		translation_tile.x = 0.0;
		translation_tile.y += 20.0;
	}
}


void Map::draw_element(const mat3 &projection, const Texture &texture)
{
	// transformation
	transform.begin();
	transform.translate(translation_tile);
	transform.scale(physics.scale);
	transform.end();

	// set shaders
	glUseProgram(effect.program);

	// enable alpha channel for textures
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// depth
	glEnable(GL_DEPTH_TEST);

	// get uniform locations for glUniform* calls
	GLint transform_uloc = glGetUniformLocation(effect.program, "transform");
	GLint color_uloc = glGetUniformLocation(effect.program, "fcolor");
	GLint projection_uloc = glGetUniformLocation(effect.program, "projection");
	GLint flash_map_uloc = glGetUniformLocation(effect.program, "flash_map");
	GLuint flash_timer_uloc = glGetUniformLocation(effect.program, "flash_timer");

	// set vertices and indices
	glBindVertexArray(mesh.vao);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ibo);

	// input data location as in the vertex buffer
	GLint in_position_loc = glGetAttribLocation(effect.program, "in_position");
	GLint in_texcoord_loc = glGetAttribLocation(effect.program, "in_texcoord");
	glEnableVertexAttribArray(in_position_loc);
	glEnableVertexAttribArray(in_texcoord_loc);
	glVertexAttribPointer(in_position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *)0);
	glVertexAttribPointer(in_texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(TexturedVertex), (void *)sizeof(vec3));

	// enable and binding texture to slot 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	// set uniform values to the currently bound program
	glUniformMatrix3fv(transform_uloc, 1, GL_FALSE, (float *)&transform.out);
	float color[] = {1.f, 1.f, 1.f};
	glUniform3fv(color_uloc, 1, color);
	glUniformMatrix3fv(projection_uloc, 1, GL_FALSE, (float *)&projection);
	glUniform1iv(flash_map_uloc, 1, &flash_map);
	glUniform1f(flash_timer_uloc, (m_flash_time > 0) ? (float)((glfwGetTime() - m_flash_time) * 20.0f) : -1);

	// draw
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

vec2 Map::get_position() const
{
	return motion.position;
}

void Map::set_position(vec2 position)
{
	motion.position = position;
}

void Map::check_wall(Char &ch, const float ms)
{
	if (!ch.is_moving())
	{
		ch.set_wall_collision('U', false);
		ch.set_wall_collision('D', false);
		ch.set_wall_collision('L', false);
		ch.set_wall_collision('R', false);
		return;
	}
	
	// ch info
	vec2 pos = ch.get_position();
	vec2 box = ch.get_bounding_box();
	vec2 dir = ch.get_velocity();
	float step = ch.is_dashing() ? 2 * ch.get_speed() * (ms / 1000) : ch.get_speed() * (ms / 1000);

	// get 4 corners of char
	vec2 pos_top_left = {pos.x - box.x, pos.y - box.y};
	vec2 pos_top_right = {pos.x + box.x, pos.y - box.y};
	vec2 pos_bottom_left = {pos.x - box.x, pos.y + box.y};
	vec2 pos_bottom_right = {pos.x + box.x, pos.y + box.y};
	
	// initialize
	int tile_x_top_left = 0;
	int tile_y_top_left = 0;
	int tile_x_top_right = 0;
	int tile_y_top_right = 0;
	int tile_x_bottom_left = 0;
	int tile_y_bottom_left = 0;
	int tile_x_bottom_right = 0;
	int tile_y_bottom_right = 0;

	// correction
	float d = 0.f;

	// blue color
	if (ch.get_color() == 3)
	{
		dir.x = -dir.x;
		dir.y = -dir.y;
	}

	// up
	if (dir.y < 0)
	{
		tile_x_top_left = (int)pos_top_left.x / 20;
		tile_y_top_left = (int)(pos_top_left.y - step) / 20;
		tile_x_top_right = (int)pos_top_right.x / 20;
		tile_y_top_right = (int)(pos_top_right.y - step) / 20;
		if (current_level[tile_y_top_left][tile_x_top_left] == 'W' || current_level[tile_y_top_left][tile_x_top_left] == 'S' ||
			current_level[tile_y_top_right][tile_x_top_right] == 'W' ||	current_level[tile_y_top_right][tile_x_top_right] == 'S')
		{
			d = 20 - (pos_top_left.y - (tile_y_top_left * 20));
			ch.change_position({0.f, d});
			ch.set_wall_collision('U', true);
		}
		else
		{
			ch.set_wall_collision('U', false);
		}
	}
	// down
	else if (dir.y > 0)
	{
		tile_x_bottom_left = (int)pos_bottom_left.x / 20;
		tile_y_bottom_left = (int)(pos_bottom_left.y + step) / 20;
		tile_x_bottom_right = (int)pos_bottom_right.x / 20;
		tile_y_bottom_right = (int)(pos_bottom_right.y + step) / 20;
		if (current_level[tile_y_bottom_left][tile_x_bottom_left] == 'W' || current_level[tile_y_bottom_left][tile_x_bottom_left] == 'S' ||
			current_level[tile_y_bottom_right][tile_x_bottom_right] == 'W' ||	current_level[tile_y_bottom_right][tile_x_bottom_right] == 'S')
		{
			d = (tile_y_bottom_left * 20) - pos_bottom_left.y - 0.001f;
			ch.change_position({0.f, d});
			ch.set_wall_collision('D', true);
		}
		else
		{
			ch.set_wall_collision('D', false);
		}
	}
	// left
	if (dir.x < 0)
	{
		tile_x_top_left = (int)(pos_top_left.x - step) / 20;
		tile_y_top_left = (int)pos_top_left.y / 20;
		tile_x_bottom_left = (int)(pos_bottom_left.x - step) / 20;
		tile_y_bottom_left = (int)pos_bottom_left.y / 20;
		if (current_level[tile_y_top_left][tile_x_top_left] == 'W' || current_level[tile_y_top_left][tile_x_top_left] == 'S' ||
			current_level[tile_y_bottom_left][tile_x_bottom_left] == 'W' ||	current_level[tile_y_bottom_left][tile_x_bottom_left] == 'S')
		{
			d = 20 - (pos_top_left.x - (tile_x_top_left * 20));
			ch.change_position({d, 0.f});
			ch.set_wall_collision('L', true);
		}
		else
		{
			ch.set_wall_collision('L', false);
		}
	}
	// right
	else if (dir.x > 0)
	{
		tile_x_top_right = (int)(pos_top_right.x + step) / 20;
		tile_y_top_right = (int)pos_top_right.y / 20;
		tile_x_bottom_right = (int)(pos_bottom_right.x + step) / 20;
		tile_y_bottom_right = (int)pos_bottom_right.y / 20;
		if (current_level[tile_y_top_right][tile_x_top_right] == 'W' || current_level[tile_y_top_right][tile_x_top_right] == 'S' ||
			current_level[tile_y_bottom_right][tile_x_bottom_right] == 'W' ||	current_level[tile_y_bottom_right][tile_x_bottom_right] == 'S')
		{
			d = (tile_x_top_right * 20) - pos_top_right.x - 0.001f;
			ch.change_position({d, 0.f});
			ch.set_wall_collision('R', true);
		}
		else
		{
			ch.set_wall_collision('R', false);
		}
	}
}

// TO REMOVE - placeholder for randomize path wall collision
void Map::is_wall_collision(Wanderer &wanderer)
{
	vec2 pos = wanderer.get_position();
	vec2 box = wanderer.get_bounding_box();

	// get 4 corners of wanderer: top left, top right, bottom left, bottom right
	vec2 pos_top_left = {pos.x - box.x, pos.y - box.y};
	vec2 pos_top_right = {pos.x + box.x, pos.y - box.y};
	vec2 pos_bottom_left = {pos.x - box.x, pos.y + box.y};
	vec2 pos_bottom_right = {pos.x + box.x, pos.y + box.y};

	int tile_x;
	int tile_y;

	// top left
	int tile_x_top_left = (int)pos_top_left.x / 20;
	int tile_y_top_left = (int)pos_top_left.y / 20;
	int tile_x_top_right = (int)pos_top_right.x / 20;
	int tile_y_top_right = (int)pos_top_right.y / 20;
	int tile_x_bottom_left = (int)pos_bottom_left.x / 20;
	int tile_y_bottom_left = (int)pos_bottom_left.y / 20;
	int tile_x_bottom_right = (int)pos_bottom_right.x / 20;
	int tile_y_bottom_right = (int)pos_bottom_right.y / 20;

	if (current_level[tile_y_top_left][tile_x_top_left] == 'W' && current_level[tile_y_top_right][tile_x_top_right] == 'W')
	{
		wanderer.set_wall_collision('U', true);
	}
	else
	{
		wanderer.set_wall_collision('U', false);
	}

	if (current_level[tile_y_top_right][tile_x_top_right] == 'W' && current_level[tile_y_bottom_right][tile_x_bottom_right] == 'W')
	{
		wanderer.set_wall_collision('R', true);
	}
	else
	{
		wanderer.set_wall_collision('R', false);
	}

	if (current_level[tile_y_bottom_right][tile_x_bottom_right] == 'W' && current_level[tile_y_bottom_left][tile_x_bottom_left] == 'W')
	{
		wanderer.set_wall_collision('D', true);
	}
	else
	{
		wanderer.set_wall_collision('D', false);
	}

	if (current_level[tile_y_bottom_left][tile_x_bottom_left] == 'W' && current_level[tile_y_top_left][tile_x_top_left] == 'W')
	{
		wanderer.set_wall_collision('L', true);
	}
	else
	{
		wanderer.set_wall_collision('L', false);
	}
}

int Map::get_tile(Char character)
{
	vec2 pos = character.get_position();
	int x = (int)pos.x / 20;
	int y = (int)pos.y / 20;

	if (current_level[y][x] == 'W')
		return 1;
	else if (current_level[y][x] == 'C')
		return 6;
	else if (current_level[y][x] == 'A')
		return 6;
	else if (current_level[y][x] == 'Z')
		return 100;
	else if (current_level[y][x] == 'R')
		return 2;
	else if (current_level[y][x] == 'G')
		return 3;
	else if (current_level[y][x] == 'B')
		return 4;
	else if (current_level[y][x] == 'Y')
		return 5;
	else
		return 0;
}

void Map::set_char_dead()
{
	m_dead_time = glfwGetTime();
}

void Map::reset_char_dead_time()
{
	m_dead_time = -1;
}

float Map::get_char_dead_time() const
{
	return glfwGetTime() - m_dead_time;
}

void Map::set_flash(int value)
{
	flash_map = value;
	m_flash_time = glfwGetTime();
}

int Map::get_flash()
{
	return flash_map;
}

void Map::reset_flash_time()
{
	m_flash_time = glfwGetTime();
}

float Map::get_flash_time() const
{
	return glfwGetTime() - m_flash_time;
}

vec2 Map::get_tile_center_coords(vec2 tile_indices)
{
	return vec2{ (tile_indices.x * 20) + 10, (tile_indices.y * 20) + 10 };
}

vec2 Map::get_grid_coords(vec2 position)
{
	int truncated_x = (int)position.x / 20;
	int truncated_y = (int)position.y / 20;
	return vec2{ (float)truncated_x, (float)truncated_y };
}

bool Map::is_wall(vec2 grid_coords)
{
	int x = grid_coords.x;
	int y = grid_coords.y;
	return current_level[y][x] == 'W' || current_level[y][x] == 'S';
}

vec2 Map::get_spawn() {

	vec2 res = vec2({ 0.f, 0.f });

	for (int i = 0; i < 40; i++)
	{
		for (int j = 0; j < 61; j++)
		{
			if (current_level[i][j] == 'A')
			{
				res.x = j * 20 + 10;
				res.y = i * 20 + 10;
				return res;
			}
		}
	}
}

void Map::set_current_map(int level)
{
	switch (level)
	{
	case 6000:
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 61; j++)
			{
				current_level[i][j] = level_tutorial[i][j];
			}
		}
		break;
	case 1000:
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 61; j++)
			{
				current_level[i][j] = level_1[i][j];
			}
		}
		break;
	case 2000:
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 61; j++)
			{
				current_level[i][j] = level_2[i][j];
			}
		}
		break;
	case 3000:
		for (int i = 0; i < 40; i++)
		{
			for (int j = 0; j < 61; j++)
			{
				current_level[i][j] = level_3[i][j];
			}
		}
		break;
	}
}

bool Map::check_wall(vec2 spotter_pos, vec2 char_pos)
{
	bool top_right = false;
	bool top_left = false;
	bool bottom_right = false;
	bool bottom_left = false;
	int sPosX = (int)spotter_pos.x / 20;
	int sPosY = (int)spotter_pos.y / 20;

	int cPosX = (int)char_pos.x / 20;
	int cPosY = (int)char_pos.y / 20;


	if ((sPosX < cPosX) && (sPosY < cPosY))
	{

		for (int posX = sPosX; posX <= cPosX; posX++)
		{
			for (int posY = sPosY; posY <= cPosY; posY++)
			{
				top_right = top_right || current_level[posY][posX] == 'W';
			}
		}
	}
	else if ((sPosX < cPosX) && (sPosY > cPosY))
	{
		for (int posX = sPosX; posX <= cPosX; posX++)
		{
			for (int posY = sPosY; posY >= cPosY; posY--)
			{
				bottom_left = bottom_left || current_level[posY][posX] == 'W';
			}
		}
	}
	else if ((sPosX > cPosX) && (sPosY > cPosY))
	{
		for (int posX = sPosX; posX >= cPosX; posX--)
		{
			for (int posY = sPosY; posY >= cPosY; posY--)
			{
				bottom_right = bottom_right || current_level[posY][posX] == 'W';
			}
		}
	}
	else if ((sPosX > cPosX) && (sPosY < cPosY))
	{
		for (int posX = sPosX; posX >= cPosX; posX--)
		{
			for (int posY = sPosY; posY <= cPosY; posY++)
			{
				top_left = top_left || current_level[posY][posX] == 'W';
			}
		}
	}
	else if ((sPosX == cPosX) && (sPosY < cPosY))
	{
		for (int posY = sPosY; posY <= cPosY; posY++)
		{
			top_left = top_left || current_level[posY][sPosX] == 'W';
		}
	}
	else if ((sPosX == cPosX) && (sPosY > cPosY))
	{
		for (int posY = sPosY; posY >= cPosY; posY--)
			{
				top_left = top_left || current_level[posY][sPosX] == 'W';
			}
	}
	else if ((sPosX < cPosX) && (sPosY == cPosY))
	{
		for (int posX = sPosX; posX <= cPosY; posX++)
		{
			top_left = top_left || current_level[sPosY][posX] == 'W';
		}
	}
	else if ((sPosX > cPosX) && (sPosY == cPosY))
	{
		for (int posX = sPosX; posX >= cPosX; posX--)
		{
			top_left = top_left || current_level[sPosY][posX] == 'W';
		}
	}


	/*if (is_wall)
		printf("wall collision works!\n");*/

	//printf("wall detection : %d\n", (top_right || top_left || bottom_right || bottom_left));
	return (top_right || top_left || bottom_right || bottom_left);
}