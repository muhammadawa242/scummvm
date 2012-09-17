/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef HOPKINS_GLOBALS_H
#define HOPKINS_GLOBALS_H

#include "common/scummsys.h"
#include "common/str.h"

namespace Hopkins {

struct TxtItem {
	int field0;
	int field12;
	int field3FC;
	int field3FE;
	int field400;
	int field404;
	int field406;
	int field408;
};

struct ListeTxtItem {
	int field0;
};

struct ZonePItem {
	int field0;
	int field2;
	int field4;
};

struct LigneItem {
	int field0;
	int field2;
	int field4;
	int field6;
	int field8;
	byte *field12;
};

struct LigneZoneItem {
	int field0;
	int field2;
	byte *field4;
};

struct CarreZoneItem {
	int field0;
};

struct BqeAnimItem {
	byte *data;
	int field4;
};

struct BankItem {
	byte *data;
	int8 field4;
	Common::String filename1;
	int fileHeader;
	int field1A;
	uint32 field1C;
	Common::String filename2;
};

struct BobItem {
	int fieldC;
	int field10;
	int field12;
	int field14;
	int field16;
};

struct BlAnimItem {
	uint32 v1;
	uint32 v2;
};

struct VBobItem {
	byte *field0;
	int field4;
	int field6;
	int field8;
	int fieldA;
	int fieldC;
	byte *field10;
	byte *field1C;
};

struct ObjetWItem {
	byte field0;
	byte field1;
	byte field2;
	byte field3;
	byte field4;
	byte field5;
	byte field6;
	byte field7;
};

/**
 * Engine Globals
 */
class Globals {
public:
	int FR;
	int SVGA;
	int internet;
	int PUBEXIT;
	bool XFULLSCREEN;
	int XSETMODE;
	int XZOOM;
	bool XFORCE16;
	bool XFORCE8;
	bool CARD_SB;
	int PERSO_TYPE;
	int vitesse;
	int INSTALL_TYPE;
	Common::String HOPIMAGE;
	Common::String HOPANIM;
	Common::String HOPLINK;
	Common::String HOPSAVE;
	Common::String HOPSOUND;
	Common::String HOPMUSIC;
	Common::String HOPVOICE;
	Common::String HOPANM;
	Common::String HOPSEQ;
	Common::String FICH_ZONE;
	Common::String FICH_TEXTE;
	Common::String NFICHIER;
	Common::String REP_SPR;
	int SOUNDVOL;
	int MUSICVOL;
	int VOICEVOL;
	bool SOUNDOFF;
	bool MUSICOFF;
	bool VOICEOFF;
	bool CENSURE;
	int min_x;
	int min_y;
	int max_x;
	int max_y;
	int lItCounter;
	int lOldItCounter;
	int g_old_anim;
	int g_old_sens;
	int HopkinsArr[140];
	void *police;
	int police_l;
	int police_h;
	byte *TETE;
	byte *ICONE;
	byte *BUF_ZONE;
	byte *CACHE_BANQUE[6];
	TxtItem Txt[11];
	ListeTxtItem ListeTxt[11];
	ZonePItem ZoneP[105];
	LigneItem Ligne[400];
	LigneZoneItem LigneZone[400];
	CarreZoneItem CarreZone[100];
	BqeAnimItem Bqe_Anim[35];
	BankItem Bank[8];
	BobItem Bob[36];
	BlAnimItem BL_ANIM[30];
	VBobItem VBob[35];
	ObjetWItem ObjetW[300];
	byte *Winventaire;
	byte *texte_tmp;
	int texte_long;
	int TEXTE_FORMATE;
	byte *SPRITE_ECRAN;
	byte *SAUVEGARDE;
	byte *BUFFERTAPE;
	byte *essai0;
	byte *essai1;
	byte *essai2;
	byte *Bufferobjet;
	int INVENTAIRE[36];
	byte *inventaire2;
	byte *GESTE;
	int OBJET_EN_COURS;
	int NUM_FICHIER_OBJ;
	int nbrligne;
	int largeur_boite;
	byte *INVENTAIRE_OBJET;
	int hauteur_boite;
	bool GESTE_FLAG;
	byte *FORETSPR;
	int FORET;
	byte *COUCOU;
	byte *chemin;
	byte *cache_souris;
	byte *BufLig;
	byte *Bufferdecor;
	byte *ADR_FICHIER_OBJ;
	byte *PERSO;
	bool redraw;
	int OBJL, OBJH;
	int Nouv_objet;
	int HELICO;
	uint32 CAT_POSI;
	uint32 CAT_TAILLE;
	int iRegul;
	bool BPP_NOAFF;
	int SORTIE;
	int PLANX, PLANY;
	int PASSWORD;
	int NOSPRECRAN;
	int ECRAN;
	int OLD_ECRAN;
	int Max_Propre;
	int Max_Propre_Gen;
	int Max_Ligne_Long;
	int Max_Perso_Y;
	bool DESACTIVE_INVENT;
	bool FLAG_VISIBLE;
	bool netscape;
	int btsouris;

	Globals();
	~Globals();

	void setConfig();
	void clearAll();
	void HOPKINS_DATA();
	void INIT_ANIM();
	void INIT_VBOB();
	void CHARGE_OBJET();
	byte *dos_malloc2(int count);
	byte *dos_free2(byte *p);
};

#define PTRNUL (byte *)NULL

} // End of namespace Hopkins

#endif /* HOPKINS_GLOBALS_H */
