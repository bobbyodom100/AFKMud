/****************************************************************************
 *                   ^     +----- |  / ^     ^ |     | +-\                  *
 *                  / \    |      | /  |\   /| |     | |  \                 *
 *                 /   \   +---   |<   | \ / | |     | |  |                 *
 *                /-----\  |      | \  |  v  | |     | |  /                 *
 *               /       \ |      |  \ |     | +-----+ +-/                  *
 ****************************************************************************
 * AFKMud Copyright 1997-2025 by Roger Libiez (Samson),                     *
 * Levi Beckerson (Whir), Michael Ward (Tarl), Erik Wolfe (Dwip),           *
 * Cameron Carroll (Cam), Cyberfox, Karangi, Rathian, Raine,                *
 * Xorith, and Adjani.                                                      *
 * All Rights Reserved.                                                     *
 *                                                                          *
 *                                                                          *
 * External contributions from Remcon, Quixadhal, Zarius, and many others.  *
 *                                                                          *
 * Original SMAUG 1.8b written by Thoric (Derek Snider) with Altrag,        *
 * Blodkai, Haus, Narn, Scryn, Swordbearer, Tricops, Gorog, Rennard,        *
 * Grishnakh, Fireblade, Edmond, Conran, and Nivek.                         *
 *                                                                          *
 * Original MERC 2.1 code by Hatchet, Furey, and Kahn.                      *
 *                                                                          *
 * Original DikuMUD code by: Hans Staerfeldt, Katja Nyboe, Tom Madsen,      *
 * Michael Seifert, and Sebastian Hammer.                                   *
 ****************************************************************************
 *                              Area Class Info                             *
 ****************************************************************************/

#ifndef __AREA_H__
#define __AREA_H__

/* Area flags - Narn Mar/96 */
/* Don't forget to update build.cpp!!! */
enum area_flags
{
   AFLAG_NOPKILL, AFLAG_NOCAMP, AFLAG_NOASTRAL, AFLAG_NOPORTAL, AFLAG_NORECALL,
   AFLAG_NOSUMMON, AFLAG_NOSCRY, AFLAG_NOTELEPORT, AFLAG_ARENA, AFLAG_NOBEACON,
   AFLAG_NOQUIT, AFLAG_PROTOTYPE, AFLAG_SILENCE, AFLAG_NOMAGIC, AFLAG_HIDDEN,
   AFLAG_NOWHERE, AFLAG_MAX
};

/*
 * Area definition.
 */
class area_data
{
 private:
   area_data( const area_data & a );
     area_data & operator=( const area_data & );

 public:
     area_data(  );
    ~area_data(  );

   void fix_exits(  );
   void sort_name(  );
   void sort_vnums(  );
   void reset(  );
   void fold( const char *, bool );
   void wipe_resets(  );

   list < room_index * >rooms;    // The list of room indexes for this area
   list < mob_index * >mobs;      // The list of mob indexes for this area
   list < obj_index * >objects;   // The list of object indexes for this area
   bitset < AFLAG_MAX > flags;

   class continent_data *continent; // Continent data structure this area is associated with.
   char *name;
   char *filename;
   char *author;                    /* Scryn */
   char *credits;
   char *resetmsg;                  /* Rennard */
   time_t creation_date;            // Timestamp for when this area was first created. Samson 1/20/07
   time_t install_date;             // Timestamp for when this area was "live" installed. Samson 1/20/07
   time_t last_resettime;           // Tracking for when the area was last reset. Debugging tool. Samson 3-6-04
   int low_vnum;
   int hi_vnum;
   int low_soft_range;
   int hi_soft_range;
   int low_hard_range;
   int hi_hard_range;
   short weatherx;                  // X Coordinate for this area's weather data.
   short weathery;                  // Y Coodrinate for this area'a weather data.
   short age;
   short nplayer;
   short reset_frequency;
   short map_x;                     // Coordinates of a zone on the overland, for recall/death purposes - Samson 12-25-00
   short map_y;
   unsigned short version;          // Replaces the file_ver method of tracking - Samson 12-23-02
   unsigned short tg_nothing;       // TG Values are for area-specific random treasure chances - Samson 11-25-04
   unsigned short tg_gold;
   unsigned short tg_item;
   unsigned short tg_gem;           // Runes come after gems and go up to 100%
   unsigned short tg_scroll;        // These are for specific chances of a particular item type - Samson 11-25-04
   unsigned short tg_potion;
   unsigned short tg_wand;
   unsigned short tg_armor;         // Weapons come after armors and go up to 100%
};

area_data *create_area(  );
void write_area_list(  );
area_data *get_area( const string & ); /* FB */
area_data *find_area( const string & );
void load_area_file( const string &, bool );
void boot_log( const char *, ... ) __attribute__ ( ( format( printf, 1, 2 ) ) );

extern list < area_data * >arealist;
extern list < area_data * >area_nsort;
extern list < area_data * >area_vsort;
extern int weath_unit;
extern int rand_factor;
extern int climate_factor;
extern int neigh_factor;
extern int max_vector;
#endif
