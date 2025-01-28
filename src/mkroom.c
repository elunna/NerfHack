/* NetHack 3.7	mkroom.c	$NHDT-Date: 1613086701 2021/02/11 23:38:21 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.52 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Robert Patrick Rankin, 2011. */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * Entry points:
 *      do_mkroom() -- make and stock a room of a given type
 *      nexttodoor() -- return TRUE if adjacent to a door
 *      has_dnstairs() -- return TRUE if given room has a down staircase
 *      has_upstairs() -- return TRUE if given room has an up staircase
 *      courtmon() -- generate a court monster
 *      save_rooms() -- save rooms into file fd
 *      rest_rooms() -- restore rooms from file fd
 *      cmap_to_type() -- convert S_xxx symbol to XXX topology code
 */

#include "hack.h"

staticfn boolean isbig(struct mkroom *);
staticfn struct mkroom *pick_room(boolean);
staticfn void mkshop(void), mkzoo(int), mkswamp(void);
staticfn int mk_zoo_thronemon(coordxy, coordxy);
staticfn void mktemple(void);
staticfn coord *shrine_pos(int);
staticfn struct permonst *morguemon(void);
staticfn struct permonst *squadmon(void);
staticfn struct permonst *realzoomon(void);
staticfn void save_room(NHFILE *, struct mkroom *);
staticfn void rest_room(NHFILE *, struct mkroom *);
staticfn boolean invalid_shop_shape(struct mkroom *sroom);

#define sq(x) ((x) * (x))

extern const struct shclass shtypes[]; /* defined in shknam.c */

staticfn boolean
isbig(struct mkroom *sroom)
{
    int area = (sroom->hx - sroom->lx + 1)
                        * (sroom->hy - sroom->ly + 1);

    return (boolean) (area > 20);
}

/* Create, in one of the rooms on the level, a special room of a given type.
 * Assumes that rooms have already been created and placed on the level.
 * Which room is selected is generally random, but this function doesn't
 * determine that; it depends on the specific behavior of mkzoo/mkswamp/etc.
 */
void
do_mkroom(int roomtype)
{
    if (roomtype >= SHOPBASE) {
        mkshop(); /* someday, we should be able to specify shop type */
    } else {
        switch (roomtype) {
        case COURT:
            mkzoo(COURT);
            break;
        case GIANTCOURT:
            mkzoo(GIANTCOURT);
            break;
        case ZOO:
            mkzoo(ZOO);
            break;
        case REALZOO:
            mkzoo(REALZOO);
            break;
        case BEEHIVE:
            mkzoo(BEEHIVE);
            break;
        case MIGOHIVE:
            mkzoo(MIGOHIVE); 
            break;
        case FUNGUSFARM:
            mkzoo(FUNGUSFARM);
            break;
        case MORGUE:
            mkzoo(MORGUE);
            break;
        case BARRACKS:
            mkzoo(BARRACKS);
            break;
        case SWAMP:
            mkswamp();
            break;
        case TEMPLE:
            mktemple();
            break;
        case LEPREHALL:
            mkzoo(LEPREHALL);
            break;
        case COCKNEST:
            mkzoo(COCKNEST);
            break;
        case ANTHOLE:
            mkzoo(ANTHOLE);
            break;
        case DRAGONLAIR:
            mkzoo(DRAGONLAIR);
            break;
        default:
            impossible("Tried to make a room of type %d.", roomtype);
        }
    }
}

/* Create and stock a shop on a random room.
 *
 * In wizard mode, the SHOPTYPE environment variable can be used to force
 * creation of a certain special room type (not limited to shops; see below)
 * where a shop would have generated (in which case it will do that instead and
 * abort creating the shop). SHOPTYPE can also be used to specify a certain
 * sort of shop.
 *
 * Shops cannot be created in non-ordinary-type rooms, rooms containing
 * staircases, or rooms that don't have exactly one door. If no appropriate
 * room is found, this function will fail without further effect.
 *
 * Shops are always made lit. If a wand or a book shop whose area is larger than
 * 20 would have been created, it is instead replaced with a general store.
 */
staticfn void
mkshop(void)
{
    struct mkroom *sroom;
    int i = -1;
    char *ep = (char *) 0; /* (init == lint suppression) */

    /* first determine shoptype */
    if (wizard) {
        ep = nh_getenv("SHOPTYPE");
        if (ep) {
            if (*ep == 'z' || *ep == 'Z') {
                mkzoo(ZOO);
                return;
            }
            if (*ep == 'm' || *ep == 'M') {
                mkzoo(MORGUE);
                return;
            }
            if (*ep == 'b' || *ep == 'B') {
                mkzoo(BEEHIVE);
                return;
            }
            if (*ep == 'i' || *ep == 'I') {
                mkzoo(MIGOHIVE);
                return;
            }
            if (*ep == 'f' || *ep == 'F') {
                mkzoo(FUNGUSFARM);
                return;
            }
            if (*ep == 't' || *ep == 'T' || *ep == '\\') {
                mkzoo(COURT);
                return;
            }
            if (*ep == 's' || *ep == 'S') {
                mkzoo(BARRACKS);
                return;
            }
            if (*ep == 'a' || *ep == 'A') {
                mkzoo(ANTHOLE);
                return;
            }
            if (*ep == 'c' || *ep == 'C') {
                mkzoo(COCKNEST);
                return;
            }
            if (*ep == 'l' || *ep == 'L') {
                mkzoo(LEPREHALL);
                return;
            }
            if (*ep == '_') {
                mktemple();
                return;
            }
            if (*ep == '}') {
                mkswamp();
                return;
            }
            for (i = 0; shtypes[i].name; i++)
                if (*ep == def_oc_syms[(int) shtypes[i].symb].sym)
                    goto gottype;
            if (*ep == 'g' || *ep == 'G')
                i = 0;
            else if (*ep == 'v' || *ep == 'V')
                i = FODDERSHOP - SHOPBASE; /* veggy food */
            else
                i = -1;
        }
    }

 gottype:
    for (sroom = &svr.rooms[0];; sroom++) {
        /* return from this loop: cannot find any eligible room to be a shop
         * continue: sroom is ineligible
         * break: sroom is eligible
         */
        if (sroom->hx < 0)
            /* could not find any suitable rooms */
            return;
        if (sroom - svr.rooms >= svn.nroom) {
            impossible("rooms[] not closed by -1?");
            return;
        }
        if (sroom->rtype != OROOM)
            continue;
        if (has_dnstairs(sroom) || has_upstairs(sroom))
            continue;
        if (sroom->doorct == 1 || (wizard && ep && sroom->doorct != 0)) {
            if (invalid_shop_shape(sroom))
                continue;
            else
                break;
        }
    }
    if (!sroom->rlit) {
        coordxy x, y;

        for (x = sroom->lx - 1; x <= sroom->hx + 1; x++)
            for (y = sroom->ly - 1; y <= sroom->hy + 1; y++)
                levl[x][y].lit = 1;
        sroom->rlit = 1;
    }

    if (i < 0) { /* shoptype not yet determined */
        int j;

        /* pick a shop type at random */
        for (j = rnd(100), i = 0; (j -= shtypes[i].prob) > 0; i++)
            continue;

        /* big rooms cannot be wand or book shops,
         * - so make them general stores
         */
        if (isbig(sroom) && (shtypes[i].symb == WAND_CLASS
                             || shtypes[i].symb == SPBOOK_CLASS))
            i = 0;

        /* Let cartomancers have a few more card shops and prevent
         * other roles from seeing them. */
        else if (Role_if(PM_CARTOMANCER)) {
            /* 2% + 5% + 5% + 7% = 19% */
            if (shtypes[i].symb == WEAPON_CLASS
               || shtypes[i].symb == FOOD_CLASS)
            i = CARDSHOP - SHOPBASE;
        } else if (!strcmp(shtypes[i].name, "collectible card game company")) {
            i = 0;
        }
    }
    sroom->rtype = SHOPBASE + i;

    /* set room bits before stocking the shop */
#ifdef SPECIALIZATION
    topologize(sroom, FALSE); /* doesn't matter - this is a special room */
#else
    topologize(sroom);
#endif

    /* The shop used to be stocked here, but this no longer happens--all we do
       is set its rtype, and it gets stocked at the end of makelevel() along
       with other special rooms. */
    sroom->needfill = FILL_NORMAL;
}

/* Select a room on the level that is suitable to place a special room in.
 * The room must be of ordinary type, and cannot contain the upstairs.
 * It cannot contain the downstairs either, unless strict is FALSE, in which
 * case it may allow it with 1/3 chance.
 * Rooms with exactly one door are heavily preferred; there is only a 1/5
 * chance of selecting a room with more doors than that. */
staticfn struct mkroom *
pick_room(boolean strict)
{
    struct mkroom *sroom;
    int i = svn.nroom;

    for (sroom = &svr.rooms[rn2(svn.nroom)]; i--; sroom++) {
        if (sroom == &svr.rooms[svn.nroom])
            sroom = &svr.rooms[0];
        if (sroom->hx < 0)
            return (struct mkroom *) 0;
        if (sroom->rtype != OROOM)
            continue;
        if (!strict) {
            if (has_upstairs(sroom) || (has_dnstairs(sroom) && rn2(3)))
                continue;
        } else if (has_upstairs(sroom) || has_dnstairs(sroom))
            continue;
        if (sroom->doorct == 1 || !rn2(5) || wizard)
            return sroom;
    }
    return (struct mkroom *) 0;
}

/* Try to find a suitable room for a zoo of the given type and, if one can be
 * found, set its room type and call fill_zoo to stock it. */
staticfn void
mkzoo(int type)
{
    struct mkroom *sroom;

    if ((sroom = pick_room(FALSE)) != 0) {
        sroom->rtype = type;
        /* room does not get stocked at this time - it will get stocked at the
         * end of makelevel() */
        sroom->needfill = FILL_NORMAL;
    }
}

/* Create an appropriate "king" monster at the given location (assumed to be on
 * a throne). */
staticfn int
mk_zoo_thronemon(coordxy x, coordxy y)
{
    int i = rnd(level_difficulty());
    int pm = (i > 20) ? PM_VAMPIRE_LEADER
        : (i > 9) ? PM_OGRE_TYRANT
        : (i > 5) ? PM_ELVEN_MONARCH
        : (i > 2) ? PM_DWARF_RULER
        : PM_GNOME_RULER;
    struct monst *mon = makemon(&mons[pm], x, y, NO_MM_FLAGS);

    if (mon) {
        mon->msleeping = 1;
        mon->mpeaceful = 0;
        set_malign(mon);
        /* Give him a sceptre to pound in judgment */
        (void) mongets(mon, MACE);
    }
    return pm;
}

/* Populate one of the zoo-type rooms with monsters, objects, and possibly
 * dungeon features. Also set any appropriate level flags for level sound
 * purposes.
 * Currently, all of these involve placing a monster on every square of the
 * room, whereas objects may or may not be. */
void
fill_zoo(struct mkroom *sroom)
{
    struct monst *mon;
    int sx, sy, i;
    int sh, goldlim = 0, type = sroom->rtype, ctype = NON_PM;
    coordxy tx = 0, ty = 0;
    int rmno = (int) ((sroom - svr.rooms) + ROOMOFFSET);
    coord mm;

    /* Note: This doesn't check needfill; it assumes the caller has already
       done that. */
    sh = sroom->fdoor;
    switch (type) {
    case COURT:
    case GIANTCOURT:
        if (svl.level.flags.is_maze_lev) {
            for (tx = sroom->lx; tx <= sroom->hx; tx++)
                for (ty = sroom->ly; ty <= sroom->hy; ty++)
                    if (IS_THRONE(levl[tx][ty].typ))
                        goto throne_placed;
        }
        /* If not, pick a random spot. */
        i = 100;
        do { /* don't place throne on top of stairs */
            (void) somexyspace(sroom, &mm);
            tx = mm.x;
            ty = mm.y;
        } while (occupied(tx, ty) && --i > 0);
 throne_placed:
        ctype = mk_zoo_thronemon(tx, ty);
        break;
    case ANTHOLE:
    case BEEHIVE:
    case MIGOHIVE:
        tx = sroom->lx + (sroom->hx - sroom->lx + 1) / 2;
        ty = sroom->ly + (sroom->hy - sroom->ly + 1) / 2;
        if (sroom->irregular) {
            /* center might not be valid, so put queen elsewhere */
            if ((int) levl[tx][ty].roomno != rmno || levl[tx][ty].edge) {
                (void) somexyspace(sroom, &mm);
                tx = mm.x;
                ty = mm.y;
            }
        }
        break;
    case ZOO:
    case LEPREHALL:
        goldlim = 500 * level_difficulty();
        break;
    case DRAGONLAIR:
        goldlim = 1500 * level_difficulty();
        break;
    }

    /* fill room with monsters */
    for (sx = sroom->lx; sx <= sroom->hx; sx++)
        for (sy = sroom->ly; sy <= sroom->hy; sy++) {
            /* Don't fill the square right next to the door, or any of the ones
             * along the same wall as the door if the room is rectangular. */
            if (sroom->irregular) {
                if ((int) levl[sx][sy].roomno != rmno || levl[sx][sy].edge
                    || (sroom->doorct
                        && (distmin(sx, sy, svd.doors[sh].x, svd.doors[sh].y)
                            <= 1)))
                    continue;
            } else if (!SPACE_POS(levl[sx][sy].typ)
                       || (sroom->doorct
                           && ((sx == sroom->lx && svd.doors[sh].x == sx - 1)
                               || (sx == sroom->hx && svd.doors[sh].x
                                   == sx + 1)
                               || (sy == sroom->ly && svd.doors[sh].y
                                   == sy - 1)
                               || (sy == sroom->hy
                                   && svd.doors[sh].y == sy + 1))))
                continue;
            /* don't place monster on explicitly placed throne */
            if ((type == COURT || type == GIANTCOURT)
                    && IS_THRONE(levl[sx][sy].typ))
                continue;
            /* create the appropriate room filler monster */
            mon = makemon((type == COURT) ? (ctype == PM_VAMPIRE_LEADER
                                          ? mkclass(S_VAMPIRE, 0) : courtmon()) :
                          (type == BARRACKS) ? squadmon() :
                          (type == MORGUE) ? morguemon() :
                          (type == FUNGUSFARM) ? fungusmon() :
                          (type == BEEHIVE) ? (sx == tx && sy == ty
                                                   ? &mons[PM_QUEEN_BEE]
                                                   : &mons[PM_KILLER_BEE]) :
                          (type == MIGOHIVE) ? (sx == tx && sy == ty
                                             ? &mons[PM_MIGO_QUEEN] : (rn2(2)
                                             ? &mons[PM_MIGO_DRONE]
                                             : &mons[PM_MIGO_WARRIOR])) :
                          (type == LEPREHALL) ? &mons[PM_LEPRECHAUN] :
                          (type == COCKNEST) ? (rn2(4)
                                                    ? &mons[PM_COCKATRICE]
                                                    : &mons[PM_CHICKATRICE]) :
                          (type == ANTHOLE) ? (sx == tx && sy == ty
                                                    ? &mons[PM_QUEEN_ANT]
                                                    : antholemon()) :
                          (type == REALZOO) ? realzoomon() :
                          (type == GIANTCOURT) ? mkclass(S_GIANT, 0) :
                          (type == DRAGONLAIR) ? mkclass(S_DRAGON, 0) :
                          (struct permonst *) 0, sx, sy, MM_ASLEEP | MM_NOGRP);
            if (mon) {
                mon->msleeping = 1;
                if ((type == COURT || type == GIANTCOURT || type == REALZOO)
                    && mon->mpeaceful) {
                    mon->mpeaceful = 0;
                    set_malign(mon);
                }
                /* Prevent rabid monsters from spawning in special rooms. */
                mon->mrabid = 0;
            }
            switch (type) {
            case DRAGONLAIR:
                if (!rn2(20))
                    (void) mksobj_at(
                        rnd_class(GRAY_DRAGON_SCALES, YELLOW_DRAGON_SCALES),
                        sx, sy, FALSE, FALSE);
                FALLTHROUGH;
                /*FALLTHRU*/
            case ZOO:
            case LEPREHALL:
                /* place floor gold */
                if (sroom->doorct) {
                    int distval = dist2(sx, sy,
                                        svd.doors[sh].x, svd.doors[sh].y);
                    i = sq(distval);
                } else
                    i = goldlim;
                if (i >= goldlim)
                    i = 5 * level_difficulty();
                goldlim -= i;
                (void) mkgold((long) rn1(i, 10), sx, sy);
                break;
            case GIANTCOURT:
                if (!rn2(111))
                    (void) mksobj_at(TINNING_KIT, sx, sy, TRUE, FALSE);
                break;
            case MORGUE:
                /* corpses and chests and headstones */
                if (!rn2(5))
                    (void) mk_tt_object(CORPSE, sx, sy);
                if (!rn2(10)) /* lots of treasure buried with dead */
                    (void) mksobj_at((rn2(3)) ? LARGE_BOX : CHEST, sx, sy,
                                     TRUE, FALSE);
                if (!rn2(5))
                    make_grave(sx, sy, (char *) 0);
                else if (!rn2(20)) {
                    maketrap(sx, sy, PIT);
                }
                break;
            case BEEHIVE:
                if (!rn2(3))
                    (void) mksobj_at(LUMP_OF_ROYAL_JELLY, sx, sy, TRUE,
                                     FALSE);
                break;
            case MIGOHIVE:
                switch (rn2(10)) {
                    case 9:
                        mksobj_at(DIAMOND, sx, sy, TRUE, FALSE);
                        break;
                    case 8:
                        mksobj_at(RUBY, sx, sy, TRUE, FALSE);
                        break;
                    case 7:
                    case 6:
                        mksobj_at(AGATE, sx, sy, TRUE, FALSE);
                        break;
                    case 5:
                    case 4:
                        mksobj_at(FLUORITE, sx, sy, TRUE, FALSE);
                        break;
                    default:
                        break;
                }
                break;
            case FUNGUSFARM:
                if (!rn2(3))
                    (void) mksobj_at(SLIME_MOLD, sx, sy, TRUE, FALSE);
                #if 0
                if (!rn2(5))
                    (void) mksobj_at(MUSHROOM, sx, sy, TRUE, FALSE);
                #endif
                break;
            case BARRACKS:
                if (!rn2(20)) /* the payroll and some loot */
                    (void) mksobj_at((rn2(3)) ? LARGE_BOX : CHEST, sx, sy,
                                     TRUE, FALSE);
                break;
            case COCKNEST:
                if (!rn2(3)) {
                    struct obj *sobj = mk_tt_object(STATUE, sx, sy);

                    if (sobj) {
                        for (i = rn2(5); i; i--)
                            (void) add_to_container(
                                sobj, mkobj(RANDOM_CLASS, FALSE));
                        sobj->owt = weight(sobj);
                    }
                }
                if (!rn2(5)) {
                    struct obj *egg = mksobj_at(EGG, sx, sy, FALSE, FALSE);
                    egg->owt = weight(egg);
                    set_corpsenm(egg, PM_COCKATRICE);
                }
                break;
            case ANTHOLE:
                if (!rn2(3))
                    (void) mkobj_at(FOOD_CLASS, sx, sy, FALSE);
                break;
            }
        }
    switch (type) {
    case GIANTCOURT:
    case COURT: {
        struct obj *chest, *gold;
        levl[tx][ty].typ = THRONE;
        (void) somexyspace(sroom, &mm);
        gold = mksobj(GOLD_PIECE, TRUE, FALSE);
        gold->quan = (long) rn1(50 * level_difficulty(), 10);
        gold->owt = weight(gold);
        /* the royal coffers */
        chest = mksobj_at(CHEST, mm.x, mm.y, TRUE, FALSE);
        add_to_container(chest, gold);
        chest->owt = weight(chest);
        chest->spe = 2; /* so it can be found later */
        svl.level.flags.has_court = 1;
        break;
    }
    case BARRACKS:
        svl.level.flags.has_barracks = 1;
        break;
    case ZOO:
    case REALZOO:
        svl.level.flags.has_zoo = 1;
        break;
    case MORGUE:
        svl.level.flags.has_morgue = 1;
        break;
    case SWAMP:
        svl.level.flags.has_swamp = 1;
        break;
    case BEEHIVE:
        svl.level.flags.has_beehive = 1;
        break;
    case MIGOHIVE:
        svl.level.flags.has_migohive = 1;
        break;
    case FUNGUSFARM:
        svl.level.flags.has_fungusfarm = 1;
        break;
    case DRAGONLAIR:
        svl.level.flags.has_lair = 1;
        break;
    }
}

/* Make a swarm of undead around mm.
 * Why is this in mkroom.c? It's only used when using cursed invocation items.
 */
void
mkundead(
    coord *mm,
    boolean revive_corpses,
    int mm_flags)
{
    int cnt = (level_difficulty() + 1) / 10 + rnd(5);
    struct permonst *mdat;
    struct obj *otmp;
    coord cc;

    while (cnt--) {
        mdat = morguemon();
        if (mdat && enexto(&cc, mm->x, mm->y, mdat)
            && (!revive_corpses
                || !(otmp = sobj_at(CORPSE, cc.x, cc.y))
                || !revive(otmp, FALSE)))
            (void) makemon(mdat, cc.x, cc.y, mm_flags);
    }
    svl.level.flags.graveyard = TRUE; /* reduced chance for undead corpse */
}

/* Return an appropriate undead monster type for generating in graveyards or
 * when raising the dead. */
staticfn struct permonst *
morguemon(void)
{
    int i = rn2(100), hd = rn2(level_difficulty());

    if (hd > 10 && i < 10) {
        if (Inhell || In_endgame(&u.uz)) {
            return mkclass(S_DEMON, 0);
        } else {
            int ndemon_res = ndemon(A_NONE);
            if (ndemon_res != NON_PM)
                return &mons[ndemon_res];
            /* else do what? As is, it will drop to ghost/wraith/zombie */
        }
    }

    if (hd > 8 && i > 85) {
        if (!rn2(5))
            return &mons[PM_GRAVE_TROLL];
        else
            return mkclass(S_VAMPIRE, 0);
    }
    return ((i < 20) ? &mons[PM_GHOST]
                     : (i < 40) ? &mons[PM_WRAITH]
                                : mkclass(S_ZOMBIE, 0));
}

/* Return an appropriate ant monster type for an anthole.
 * This is deterministic, so that all ants on the same level (practically
 * speaking, in a single anthole) are the same type of ant.
 */
struct permonst *
antholemon(void)
{
    int mtyp, indx, trycnt = 0;

    /* casts are for dealing with time_t */
    indx = (int) ((long) ubirthday % 3L);
    indx += level_difficulty();
    /* Same monsters within a level, different ones between levels */
    do {
        switch ((indx + trycnt) % 3) {
        case 0:
            mtyp = PM_SOLDIER_ANT;
            break;
        case 1:
            mtyp = PM_FIRE_ANT;
            break;
        case 2:
            mtyp = PM_BULLET_ANT;
            break;
        default:
            mtyp = PM_GIANT_ANT;
            break;
        }
        /* try again if chosen type has been genocided or used up */
    } while (++trycnt < 3 && (svm.mvitals[mtyp].mvflags & G_GONE));

    return ((svm.mvitals[mtyp].mvflags & G_GONE) ? (struct permonst *) 0
                                             : &mons[mtyp]);
}

struct permonst *
fungusmon(void)
{
	int i, hd = level_difficulty(), mtyp = 0;

	i = rn2(hd > 20 ? 17 : hd > 12 ? 14 : 12);

	switch (i) {
	case 0:
	case 1:
        mtyp = PM_LICHEN;
        break;
	case 2: mtyp = PM_BROWN_MOLD;
        break;
	case 3: mtyp = PM_YELLOW_MOLD;
        break;
	case 4: mtyp = PM_GREEN_MOLD;
        break;
	case 5: mtyp = PM_RED_MOLD;
        break;
	case 6: mtyp = PM_SHRIEKER;
        break;
	case 7: mtyp = PM_VIOLET_FUNGUS;
        break;
	case 8: mtyp = PM_BLUE_JELLY;
        break;
	case 9:
	case 10: mtyp = PM_GRAY_FUNGUS;
        break;
	case 11: mtyp = PM_GRAY_OOZE;
        break;
	/* Following only after level 12... */
	case 12: mtyp = PM_SPOTTED_JELLY;
        break;
	case 13: mtyp = PM_BROWN_PUDDING;
        break;
	/* Following only after level 20... */
	case 14: mtyp = PM_GREEN_SLIME;
        break;
	case 15: mtyp = PM_BLACK_PUDDING;
        break;
	case 16: mtyp = PM_OCHRE_JELLY;
        break;
	}

	return ((svm.mvitals[mtyp].mvflags & G_GONE) ?
		(struct permonst *)0 : &mons[mtyp]);
}

/* Turn up to 5 ordinary rooms into swamp rooms.
 * Swamps contain a checkerboard pattern of pools (except next to doors),
 * F-class monsters, and possibly one sea monster, apiece.
 */
staticfn void
mkswamp(void) /* Michiel Huisjes & Fred de Wilde */
{
    struct mkroom *sroom;
    int i, eelct = 0;
    coordxy sx, sy;
    int rmno;

    for (i = 0; i < 5; i++) { /* turn up to 5 rooms swampy */
        sroom = &svr.rooms[rn2(svn.nroom)];
        if (sroom->hx < 0 || sroom->rtype != OROOM || has_upstairs(sroom)
            || has_dnstairs(sroom))
            continue;

        rmno = (int)(sroom - svr.rooms) + ROOMOFFSET;

        /* satisfied; make a swamp */
        sroom->rtype = SWAMP;
        for (sx = sroom->lx; sx <= sroom->hx; sx++)
            for (sy = sroom->ly; sy <= sroom->hy; sy++) {
                if (!IS_ROOM(levl[sx][sy].typ)
                    || (int) levl[sx][sy].roomno != rmno)
                    continue;
                if (!OBJ_AT(sx, sy) && !MON_AT(sx, sy) && !t_at(sx, sy)
                    && !nexttodoor(sx, sy)) {
                    if ((sx + sy) % 2) {
                        del_engr_at(sx, sy);
                        levl[sx][sy].typ = POOL;
                        if (!eelct || !rn2(4)) {
                            /* mkclass() won't do, as we might get kraken */
                            (void) makemon(rn2(5)
                                              ? &mons[PM_GIANT_EEL]
                                              : rn2(2)
                                                 ? &mons[PM_PIRANHA]
                                                 : &mons[PM_ELECTRIC_EEL],
                                           sx, sy, NO_MM_FLAGS);
                            if (!rn2(13))
                                (void) makemon(&mons[PM_WILL_O__THE_WISP],
                                               sx, sy, NO_MM_FLAGS);
                            eelct++;
                        }
                    } else if (!rn2(4)) { 
                        levl[sx][sy].typ = PUDDLE;
                        /* swamps tend to be moldy */
                        (void) makemon(mkclass(S_FUNGUS, 0), sx, sy,
                                       NO_MM_FLAGS);
                    }
                }
            }
        svl.level.flags.has_swamp = 1;
    }
}

/* Return the position within a room at which its altar should be placed, if it
 * is to be a temple. It will be the exact center of the room, unless the center
 * isn't actually a square, in which case it'll be offset one space to the side.
 */
staticfn coord *
shrine_pos(int roomno)
{
    static coord buf;
    int delta;
    struct mkroom *troom = &svr.rooms[roomno - ROOMOFFSET];

    /* if width and height are odd, placement will be the exact center;
       if either or both are even, center point is a hypothetical spot
       between map locations and placement will be adjacent to that */
    delta = troom->hx - troom->lx;
    buf.x = troom->lx + delta / 2;
    if ((delta % 2) && rn2(2))
        buf.x++;
    delta = troom->hy - troom->ly;
    buf.y = troom->ly + delta / 2;
    if ((delta % 2) && rn2(2))
        buf.y++;
    return &buf;
}

/* Try and find a suitable room for a temple and if successful, create the
 * temple with its altar and attendant priest.
 */
staticfn void
mktemple(void)
{
    struct mkroom *sroom;
    coord *shrine_spot;
    struct rm *lev;

    if (!(sroom = pick_room(TRUE)))
        return;

    /* set up Priest and shrine */
    sroom->rtype = TEMPLE;
    /*
     * In temples, shrines are blessed altars
     * located in the center of the room
     */
    shrine_spot = shrine_pos((int) ((sroom - svr.rooms) + ROOMOFFSET));
    lev = &levl[shrine_spot->x][shrine_spot->y];
    lev->typ = ALTAR;
    set_levltyp(shrine_spot->x, shrine_spot->y, ALTAR);
    lev->altarmask = induced_align(80);
    priestini(&u.uz, sroom, shrine_spot->x, shrine_spot->y, FALSE);
    lev->altarmask |= AM_SHRINE;
    svl.level.flags.has_temple = 1;
}

/* Return TRUE if the given location is next to a door or a secret door in any
 * direction. */
boolean
nexttodoor(int sx, int sy)
{
    int dx, dy;
    struct rm *lev;

    for (dx = -1; dx <= 1; dx++)
        for (dy = -1; dy <= 1; dy++) {
            if (!isok(sx + dx, sy + dy))
                continue;
            lev = &levl[sx + dx][sy + dy];
            if (IS_DOOR(lev->typ) || lev->typ == SDOOR)
                return TRUE;
        }
    return FALSE;
}

/* Return TRUE if the given room contains stairs (regular or branch), in the
 * specified direction. */
boolean
has_dnstairs(struct mkroom *sroom)
{
    stairway *stway = gs.stairs;

    while (stway) {
        if (!stway->up && inside_room(sroom, stway->sx, stway->sy))
            return TRUE;
        stway = stway->next;
    }
    return FALSE;
}

boolean
has_upstairs(struct mkroom *sroom)
{
    stairway *stway = gs.stairs;

    while (stway) {
        if (stway->up && inside_room(sroom, stway->sx, stway->sy))
            return TRUE;
        stway = stway->next;
    }
    return FALSE;
}

/* Return a random x coordinate within the x limits of a room. */
int
somex(struct mkroom *croom)
{
    return rn1(croom->hx - croom->lx + 1, croom->lx);
}

/* Return a random y coordinate within the y limits of a room. */
int
somey(struct mkroom *croom)
{
    return rn1(croom->hy - croom->ly + 1, croom->ly);
}

/* Return TRUE if the given position falls within both the x and y limits
 * of a room.
 */
boolean
inside_room(struct mkroom *croom, coordxy x, coordxy y)
{
    if (croom->irregular) {
        int i = (int) ((croom - svr.rooms) + ROOMOFFSET);
        return (!levl[x][y].edge && (int) levl[x][y].roomno == i);
    }

    return (boolean) (x >= croom->lx - 1 && x <= croom->hx + 1
                      && y >= croom->ly - 1 && y <= croom->hy + 1);
}

/* return a coord c inside mkroom croom, but not in a subroom.
   returns TRUE if any such space found.
   can return a non-accessible location, eg. inside a wall
   if a themed room is not irregular, but has some non-room terrain */
boolean
somexy(struct mkroom *croom, coord *c)
{
    int try_cnt = 0;
    int i;

    if (croom->irregular) {
        i = (int) ((croom - svr.rooms) + ROOMOFFSET);

        while (try_cnt++ < 100) {
            c->x = somex(croom);
            c->y = somey(croom);
            if (!levl[c->x][c->y].edge && (int) levl[c->x][c->y].roomno == i)
                return TRUE;
        }
        /* try harder; exhaustively search until one is found */
        for (c->x = croom->lx; c->x <= croom->hx; c->x++)
            for (c->y = croom->ly; c->y <= croom->hy; c->y++)
                if (!levl[c->x][c->y].edge
                    && (int) levl[c->x][c->y].roomno == i)
                    return TRUE;
        return FALSE;
    }

    if (!croom->nsubrooms) {
        c->x = somex(croom);
        c->y = somey(croom);
        return TRUE;
    }

    /* Check that coords doesn't fall into a subroom or into a wall */

    while (try_cnt++ < 100) {
        c->x = somex(croom);
        c->y = somey(croom);
        if (IS_WALL(levl[c->x][c->y].typ))
            continue;
        for (i = 0; i < croom->nsubrooms; i++)
            if (inside_room(croom->sbrooms[i], c->x, c->y))
                goto you_lose;
        break;
 you_lose:
        ;
    }
    if (try_cnt >= 100)
        return FALSE;
    return TRUE;
}

/* like somexy(), but returns an accessible location */
boolean
somexyspace(struct mkroom* croom, coord *c)
{
    int trycnt = 0;
    boolean okay;

    do {
        okay = somexy(croom, c) && isok(c->x, c->y) && !occupied(c->x, c->y)
            && (levl[c->x][c->y].typ == ROOM
                || levl[c->x][c->y].typ == CORR
                || levl[c->x][c->y].typ == GRASS
                || levl[c->x][c->y].typ == ICE);
    } while (trycnt++ < 100 && !okay);
    return okay;
}

/*
 * Search for a special room given its type (zoo, court, etc...)
 *      Special values :
 *              - ANY_SHOP
 *              - ANY_TYPE
 */
struct mkroom *
search_special(schar type)
{
    struct mkroom *croom;

    for (croom = &svr.rooms[0]; croom->hx >= 0; croom++)
        if ((type == ANY_TYPE && croom->rtype != OROOM)
            || (type == ANY_SHOP && croom->rtype >= SHOPBASE)
            || croom->rtype == type)
            return croom;
    for (croom = &gs.subrooms[0]; croom->hx >= 0; croom++)
        if ((type == ANY_TYPE && croom->rtype != OROOM)
            || (type == ANY_SHOP && croom->rtype >= SHOPBASE)
            || croom->rtype == type)
            return croom;
    return (struct mkroom *) 0;
}

/* Return an appropriate monster type for generating in throne rooms. */
struct permonst *
courtmon(void)
{
    int i = rn2(60) + rn2(3 * level_difficulty());

    if (i > 100)
        return mkclass(S_DRAGON, 0);
    else if (i > 95)
        return mkclass(S_GIANT, 0);
    else if (i > 85)
        return mkclass(S_TROLL, 0);
    else if (i > 75)
        return mkclass(S_CENTAUR, 0);
    else if (i > 60)
        return mkclass(S_ORC, 0);
    else if (i > 45)
        return &mons[PM_BUGBEAR];
    else if (i > 30)
        return &mons[PM_HOBGOBLIN];
    else if (i > 15)
        return mkclass(S_GNOME, 0);
    else
        return mkclass(S_KOBOLD, 0);
}

/* return real zoo monster types. */
staticfn struct permonst *
realzoomon(void)
{
    int i = rn2(60) + rn2(3 * level_difficulty());
#if 0 /* Removed, dungeon will never be deep enough to generate */
    if (i > 175)
        return (&mons[PM_JUMBO_THE_ELEPHANT]);
#endif
    if (i > 115)
        return (&mons[PM_MASTODON]);
    else if (i > 85)
        return (&mons[PM_PYTHON]);
    else if (i > 70)
        return (&mons[PM_MUMAK]);
    else if (i > 55)
        return (&mons[PM_TIGER]);
    else if (i > 45)
        return (&mons[PM_PANTHER]);
    else if (i > 25)
        return (&mons[PM_JAGUAR]);
    else if (i > 15)
        return (&mons[PM_APE]);
    else
        return (&mons[PM_MONKEY]);
}

static const struct {
    unsigned pm;
    unsigned prob;
} squadprob[] = { { PM_SOLDIER, 80 },
                  { PM_SERGEANT, 15 },
                  { PM_LIEUTENANT, 4 },
                  { PM_CAPTAIN, 1 } };

/* Return an appropriate Yendorian Army monster type for generating in
 * barracks. They will generate with the percentage odds given above. */
staticfn struct permonst *
squadmon(void)
{
    int sel_prob, i, cpro, mndx;

    sel_prob = rnd(80 + level_difficulty());

    cpro = 0;
    for (i = 0; i < SIZE(squadprob); i++) {
        cpro += squadprob[i].prob;
        if (cpro > sel_prob) {
            mndx = squadprob[i].pm;
            goto gotone;
        }
    }
    mndx = ROLL_FROM(squadprob).pm;
 gotone:
    if (!(svm.mvitals[mndx].mvflags & G_GONE))
        return &mons[mndx];
    else
        return (struct permonst *) 0;
}

/*
 * save_room : A recursive function that saves a room and its subrooms
 * (if any).
 */
staticfn void
save_room(NHFILE *nhfp, struct mkroom *r)
{
    short i;

    /*
     * Well, I really should write only useful information instead
     * of writing the whole structure. That is I should not write
     * the gs.subrooms pointers, but who cares ?
     */
    if (nhfp->structlevel)
        bwrite(nhfp->fd, (genericptr_t) r, sizeof (struct mkroom));
    for (i = 0; i < r->nsubrooms; i++) {
        save_room(nhfp, r->sbrooms[i]);
    }
}

/*
 * save_rooms : Save all the rooms on disk!
 */
void
save_rooms(NHFILE *nhfp)
{
    short i;

    /* First, write the number of rooms */
    if (nhfp->structlevel)
        bwrite(nhfp->fd, (genericptr_t) &svn.nroom, sizeof(svn.nroom));
    for (i = 0; i < svn.nroom; i++)
        save_room(nhfp, &svr.rooms[i]);
}

staticfn void
rest_room(NHFILE *nhfp, struct mkroom *r)
{
    short i;

    if (nhfp->structlevel)
        mread(nhfp->fd, (genericptr_t) r, sizeof(struct mkroom));

    for (i = 0; i < r->nsubrooms; i++) {
        r->sbrooms[i] = &gs.subrooms[gn.nsubroom];
        rest_room(nhfp, &gs.subrooms[gn.nsubroom]);
        gs.subrooms[gn.nsubroom++].resident = (struct monst *) 0;
    }
}

/*
 * rest_rooms : That's for restoring rooms. Read the rooms structure from
 * the disk.
 */
void
rest_rooms(NHFILE *nhfp)
{
    short i;

    if (nhfp->structlevel)
        mread(nhfp->fd, (genericptr_t) &svn.nroom, sizeof(svn.nroom));

    gn.nsubroom = 0;
    for (i = 0; i < svn.nroom; i++) {
        rest_room(nhfp, &svr.rooms[i]);
        svr.rooms[i].resident = (struct monst *) 0;
    }
    svr.rooms[svn.nroom].hx = -1; /* restore ending flags */
    gs.subrooms[gn.nsubroom].hx = -1;
}

/* convert a display symbol for terrain into topology type;
   used for remembered terrain when mimics pose as furniture */
int
cmap_to_type(int sym)
{
    int typ = STONE; /* catchall */

    switch (sym) {
    case S_stone:
        typ = STONE;
        break;
    case S_vwall:
        typ = VWALL;
        break;
    case S_hwall:
        typ = HWALL;
        break;
    case S_tlcorn:
        typ = TLCORNER;
        break;
    case S_trcorn:
        typ = TRCORNER;
        break;
    case S_blcorn:
        typ = BLCORNER;
        break;
    case S_brcorn:
        typ = BRCORNER;
        break;
    case S_crwall:
        typ = CROSSWALL;
        break;
    case S_tuwall:
        typ = TUWALL;
        break;
    case S_tdwall:
        typ = TDWALL;
        break;
    case S_tlwall:
        typ = TLWALL;
        break;
    case S_trwall:
        typ = TRWALL;
        break;
    case S_ndoor:  /* no door (empty doorway) */
    case S_vodoor: /* open door in vertical wall */
    case S_hodoor: /* open door in horizontal wall */
    case S_vcdoor: /* closed door in vertical wall */
    case S_hcdoor:
        typ = DOOR;
        break;
    case S_bars:
        typ = IRONBARS;
        break;
    case S_tree:
        typ = TREE;
        break;
    case S_room:
    case S_darkroom:
        typ = ROOM;
        break;
    case S_corr:
    case S_litcorr:
        typ = CORR;
        break;
    case S_upstair:
    case S_dnstair:
        typ = STAIRS;
        break;
    case S_upladder:
    case S_dnladder:
        typ = LADDER;
        break;
    case S_altar:
        typ = ALTAR;
        break;
    case S_grave:
        typ = GRAVE;
        break;
    case S_throne:
        typ = THRONE;
        break;
    case S_sink:
        typ = SINK;
        break;
    case S_toilet:
        typ = TOILET;
        break;
    case S_forge:
        typ = FORGE;
        break;
    case S_fountain:
        typ = FOUNTAIN;
        break;
    case S_pool:
        typ = POOL;
        break;
    case S_puddle:
        typ = PUDDLE;
        break;
    case S_ice:
        typ = ICE;
        break;
    case S_grass:
        typ = GRASS;
        break;
    case S_lava:
        typ = LAVAPOOL;
        break;
    case S_vodbridge: /* open drawbridge spanning north/south */
    case S_hodbridge:
        typ = DRAWBRIDGE_DOWN;
        break;        /* east/west */
    case S_vcdbridge: /* closed drawbridge in vertical wall */
    case S_hcdbridge:
        typ = DBWALL;
        break;
    case S_air:
        typ = AIR;
        break;
    case S_cloud:
        typ = CLOUD;
        break;
    case S_water:
        typ = WATER;
        break;
    case S_lavawall:
        typ = LAVAWALL;
        break;
    default:
        break; /* not a cmap symbol? */
    }
    return typ;
}

/* With the introduction of themed rooms, there are certain room shapes that
 * may generate a door, the square just inside the door, and only one other
 * ROOM square touching that one. E.g.
 *   ---
 * ---..
 * +....
 * ---..
 *   ---
 * This means that if the room becomes a shop, the shopkeeper will move
 * between those two squares nearest the door without ever allowing the
 * player to get past them.
 * Before approving sroom as a shop, check for this circumstance, and if it
 * exists, don't consider it as valid for a shop.
 *
 * Note that the invalidity of the shape derives from the position of its door
 * already being chosen. It's quite possible that if the door were somewhere
 * else on the perimeter of this room, it would work fine as a shop.*/
staticfn boolean
invalid_shop_shape(struct mkroom *sroom)
{
    coordxy x, y;
    coordxy doorx = svd.doors[sroom->fdoor].x;
    coordxy doory = svd.doors[sroom->fdoor].y;
    coordxy insidex = 0, insidey = 0, insidect = 0;

    /* First, identify squares inside the room and next to the door. */
    for (x = max(doorx - 1, sroom->lx);
         x <= min(doorx + 1, sroom->hx); x++) {
        for (y = max(doory - 1, sroom->ly);
             y <= min(doory + 1, sroom->hy); y++) {
            if (levl[x][y].typ == ROOM) {
                insidex = x;
                insidey = y;
                insidect++;
            }
        }
    }
    if (insidect < 1) {
        impossible("invalid_shop_shape: no squares inside door?");
        return TRUE;
    }
    /* if insidect > 1, then the shopkeeper already has alternate
     * squares to move to so we don't need to check further. */
    if (insidect == 1) {
        /* But if it is 1, scan all adjacent squares for other squares
         * that are part of this room. */
        insidect = 0;
        for (x = max(insidex - 1, sroom->lx);
             x <= min(insidex + 1, sroom->hx); x++) {
            for (y = max(insidey - 1, sroom->ly);
                 y <= min(insidey + 1, sroom->hy); y++) {
                if (x == insidex && y == insidey)
                    continue;
                if (levl[x][y].typ == ROOM)
                    insidect++;
            }
        }
        if (insidect == 1) {
            /* shopkeeper standing just inside the door can only move
             * to one other square; this cannot be a shop. */
            return TRUE;
        }
    }
    return FALSE;
}

/*mkroom.c*/
