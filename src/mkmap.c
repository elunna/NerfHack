/* NetHack 3.7	mkmap.c	$NHDT-Date: 1717432093 2024/06/03 16:28:13 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.40 $ */
/* Copyright (c) J. C. Collet, M. Stephenson and D. Cohrs, 1992   */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include "sp_lev.h"

#define HEIGHT (ROWNO - 1)
#define WIDTH (COLNO - 2)

staticfn void init_map(schar);
staticfn void init_fill(schar, schar);
staticfn schar get_map(int, int, schar);
staticfn void pass_one(schar, schar);
staticfn void pass_two(schar, schar);
staticfn void pass_three(schar, schar);
staticfn void join_map_cleanup(void);
staticfn void join_map(schar, schar);
staticfn void finish_map(schar, schar, boolean, boolean, boolean);
staticfn void remove_room(unsigned);
staticfn void mkrivers(void);
staticfn void makeriver(int, int, int, int);
void mkmap(lev_init *);

staticfn void
init_map(schar bg_typ)
{
    int i, j;

    for (i = 1; i < COLNO; i++)
        for (j = 0; j < ROWNO; j++) {
            levl[i][j].roomno = NO_ROOM;
            levl[i][j].typ = bg_typ;
            levl[i][j].lit = FALSE;
        }
}

staticfn void
init_fill(schar bg_typ, schar fg_typ)
{
    int i, j;
    long limit, count;

    limit = (WIDTH * HEIGHT * 2) / 5;
    count = 0;
    while (count < limit) {
        i = rn1(WIDTH - 1, 2);
        j = rnd(HEIGHT - 1);
        if (levl[i][j].typ == bg_typ) {
            levl[i][j].typ = fg_typ;
            count++;
        }
    }
}

staticfn schar
get_map(int col, int row, schar bg_typ)
{
    if (col <= 0 || row < 0 || col > WIDTH || row >= HEIGHT)
        return bg_typ;
    return levl[col][row].typ;
}

staticfn const int dirs[16] = {
    -1, -1 /**/, -1,  0 /**/, -1, 1 /**/, 0, -1 /**/,
     0,  1 /**/,  1, -1 /**/,  1, 0 /**/, 1,  1
};

staticfn void
pass_one(schar bg_typ, schar fg_typ)
{
    int i, j;
    short count, dr;

    for (i = 2; i <= WIDTH; i++)
        for (j = 1; j < HEIGHT; j++) {
            for (count = 0, dr = 0; dr < 8; dr++)
                if (get_map(i + dirs[dr * 2], j + dirs[(dr * 2) + 1], bg_typ)
                    == fg_typ)
                    count++;

            switch (count) {
            case 0: /* death */
            case 1:
            case 2:
                levl[i][j].typ = bg_typ;
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                levl[i][j].typ = fg_typ;
                break;
            default:
                break;
            }
        }
}

#define new_loc(i, j) *(gn.new_locations + ((j) * (WIDTH + 1)) + (i))

staticfn void
pass_two(schar bg_typ, schar fg_typ)
{
    int i, j;
    short count, dr;

    for (i = 2; i <= WIDTH; i++)
        for (j = 1; j < HEIGHT; j++) {
            for (count = 0, dr = 0; dr < 8; dr++)
                if (get_map(i + dirs[dr * 2], j + dirs[(dr * 2) + 1], bg_typ)
                    == fg_typ)
                    count++;
            if (count == 5)
                new_loc(i, j) = bg_typ;
            else
                new_loc(i, j) = get_map(i, j, bg_typ);
        }

    for (i = 2; i <= WIDTH; i++)
        for (j = 1; j < HEIGHT; j++)
            levl[i][j].typ = new_loc(i, j);
}

staticfn void
pass_three(schar bg_typ, schar fg_typ)
{
    int i, j;
    short count, dr;

    for (i = 2; i <= WIDTH; i++)
        for (j = 1; j < HEIGHT; j++) {
            for (count = 0, dr = 0; dr < 8; dr++)
                if (get_map(i + dirs[dr * 2], j + dirs[(dr * 2) + 1], bg_typ)
                    == fg_typ)
                    count++;
            if (count < 3)
                new_loc(i, j) = bg_typ;
            else
                new_loc(i, j) = get_map(i, j, bg_typ);
        }

    for (i = 2; i <= WIDTH; i++)
        for (j = 1; j < HEIGHT; j++)
            levl[i][j].typ = new_loc(i, j);
}

/*
 * use a flooding algorithm to find all locations that should
 * have the same rm number as the current location.
 * if anyroom is TRUE, use IS_ROOM to check room membership instead of
 * exactly matching levl[sx][sy].typ and walls are included as well.
 */
void
flood_fill_rm(
    int sx,
    int sy,
    int rmno,
    boolean lit,
    boolean anyroom)
{
    int i;
    int nx;
    schar fg_typ = levl[sx][sy].typ;

    /* back up to find leftmost uninitialized location */
    while (sx > 0 && (anyroom ? IS_ROOM(levl[sx][sy].typ)
                              : levl[sx][sy].typ == fg_typ)
           && (int) levl[sx][sy].roomno != rmno)
        sx--;
    sx++; /* compensate for extra decrement */

    /* assume sx,sy is valid */
    if (sx < gm.min_rx)
        gm.min_rx = sx;
    if (sy < gm.min_ry)
        gm.min_ry = sy;

    for (i = sx; i <= WIDTH && levl[i][sy].typ == fg_typ; i++) {
        levl[i][sy].roomno = rmno;
        levl[i][sy].lit = lit;
        if (anyroom) {
            /* add walls to room as well */
            int ii, jj;
            for (ii = (i == sx ? i - 1 : i); ii <= i + 1; ii++)
                for (jj = sy - 1; jj <= sy + 1; jj++)
                    if (isok(ii, jj) && (IS_WALL(levl[ii][jj].typ)
                                         || IS_DOOR(levl[ii][jj].typ)
                                         || levl[ii][jj].typ == SDOOR)) {
                        levl[ii][jj].edge = 1;
                        if (lit)
                            levl[ii][jj].lit = lit;

                        if (levl[ii][jj].roomno == NO_ROOM)
                            levl[ii][jj].roomno = rmno;
                        else if ((int) levl[ii][jj].roomno != rmno)
                            levl[ii][jj].roomno = SHARED;
                    }
        }
        gn.n_loc_filled++;
    }
    nx = i;

    if (isok(sx, sy - 1)) {
        for (i = sx; i < nx; i++)
            if (levl[i][sy - 1].typ == fg_typ) {
                if ((int) levl[i][sy - 1].roomno != rmno)
                    flood_fill_rm(i, sy - 1, rmno, lit, anyroom);
            } else {
                if ((i > sx || isok(i - 1, sy - 1))
                    && levl[i - 1][sy - 1].typ == fg_typ) {
                    if ((int) levl[i - 1][sy - 1].roomno != rmno)
                        flood_fill_rm(i - 1, sy - 1, rmno, lit, anyroom);
                }
                if ((i < nx - 1 || isok(i + 1, sy - 1))
                    && levl[i + 1][sy - 1].typ == fg_typ) {
                    if ((int) levl[i + 1][sy - 1].roomno != rmno)
                        flood_fill_rm(i + 1, sy - 1, rmno, lit, anyroom);
                }
            }
    }
    if (isok(sx, sy + 1)) {
        for (i = sx; i < nx; i++)
            if (levl[i][sy + 1].typ == fg_typ) {
                if ((int) levl[i][sy + 1].roomno != rmno)
                    flood_fill_rm(i, sy + 1, rmno, lit, anyroom);
            } else {
                if ((i > sx || isok(i - 1, sy + 1))
                    && levl[i - 1][sy + 1].typ == fg_typ) {
                    if ((int) levl[i - 1][sy + 1].roomno != rmno)
                        flood_fill_rm(i - 1, sy + 1, rmno, lit, anyroom);
                }
                if ((i < nx - 1 || isok(i + 1, sy + 1))
                    && levl[i + 1][sy + 1].typ == fg_typ) {
                    if ((int) levl[i + 1][sy + 1].roomno != rmno)
                        flood_fill_rm(i + 1, sy + 1, rmno, lit, anyroom);
                }
            }
    }

    if (nx > gm.max_rx)
        gm.max_rx = nx - 1; /* nx is just past valid region */
    if (sy > gm.max_ry)
        gm.max_ry = sy;
}

/* join_map uses temporary rooms; clean up after it */
staticfn void
join_map_cleanup(void)
{
    coordxy x, y;

    for (x = 1; x < COLNO; x++)
        for (y = 0; y < ROWNO; y++)
            levl[x][y].roomno = NO_ROOM;
    svn.nroom = gn.nsubroom = 0;
    svr.rooms[svn.nroom].hx = gs.subrooms[gn.nsubroom].hx = -1;
}

staticfn void
join_map(schar bg_typ, schar fg_typ)
{
    struct mkroom *croom, *croom2;

    int i, j;
    int sx, sy;
    coord sm, em;

    /* first, use flood filling to find all of the regions that need joining
     */
    for (i = 2; i <= WIDTH; i++)
        for (j = 1; j < HEIGHT; j++) {
            if (levl[i][j].typ == fg_typ && levl[i][j].roomno == NO_ROOM) {
                gm.min_rx = gm.max_rx = i;
                gm.min_ry = gm.max_ry = j;
                gn.n_loc_filled = 0;
                flood_fill_rm(i, j, svn.nroom + ROOMOFFSET, FALSE, FALSE);
                if (gn.n_loc_filled > 3) {
                    add_room(gm.min_rx, gm.min_ry, gm.max_rx, gm.max_ry,
                             FALSE, OROOM, TRUE);
                    svr.rooms[svn.nroom - 1].irregular = TRUE;
                    if (svn.nroom >= (MAXNROFROOMS * 2))
                        goto joinm;
                } else {
                    /*
                     * it's a tiny hole; erase it from the map to avoid
                     * having the player end up here with no way out.
                     */
                    for (sx = gm.min_rx; sx <= gm.max_rx; sx++)
                        for (sy = gm.min_ry; sy <= gm.max_ry; sy++)
                            if ((int) levl[sx][sy].roomno
                                == svn.nroom + ROOMOFFSET) {
                                levl[sx][sy].typ = bg_typ;
                                levl[sx][sy].roomno = NO_ROOM;
                            }
                }
            }
        }

 joinm:
    /*
     * Ok, now we can actually join the regions with fg_typ's.
     * The rooms are already sorted due to the previous loop,
     * so don't call sort_rooms(), which can screw up the roomno's
     * validity in the levl structure.
     */
    for (croom = &svr.rooms[0], croom2 = croom + 1;
         croom2 < &svr.rooms[svn.nroom]; ) {
        /* pick random starting and end locations for "corridor" */
        if (!somexy(croom, &sm) || !somexy(croom2, &em)) {
            /* ack! -- the level is going to be busted */
            /* arbitrarily pick centers of both rooms and hope for the best */
            impossible("No start/end room loc in join_map.");
            sm.x = croom->lx + ((croom->hx - croom->lx) / 2);
            sm.y = croom->ly + ((croom->hy - croom->ly) / 2);
            em.x = croom2->lx + ((croom2->hx - croom2->lx) / 2);
            em.y = croom2->ly + ((croom2->hy - croom2->ly) / 2);
        }

        (void) dig_corridor(&sm, &em, FALSE, fg_typ, bg_typ);

        /* choose next region to join */
        /* only increment croom if croom and croom2 are non-overlapping */
        if (croom2->lx > croom->hx
            || ((croom2->ly > croom->hy || croom2->hy < croom->ly)
                && rn2(3))) {
            croom = croom2;
        }
        croom2++; /* always increment the next room */
    }
    join_map_cleanup();
}

staticfn void
finish_map(
    schar fg_typ,
    schar bg_typ,
    boolean lit,
    boolean walled,
    boolean icedpools)
{
    int i, j;

    if (walled)
        wallify_map(1, 0, COLNO-1, ROWNO-1);

    if (lit) {
        for (i = 1; i < COLNO; i++)
            for (j = 0; j < ROWNO; j++)
                if ((!IS_OBSTRUCTED(fg_typ) && levl[i][j].typ == fg_typ)
                    || (!IS_OBSTRUCTED(bg_typ) && levl[i][j].typ == bg_typ)
                    || (bg_typ == TREE && levl[i][j].typ == bg_typ)
                    || (walled && IS_WALL(levl[i][j].typ)))
                    levl[i][j].lit = TRUE;
        for (i = 0; i < svn.nroom; i++)
            svr.rooms[i].rlit = 1;
    }
    /* light lava even if everything's otherwise unlit;
       ice might be frozen pool rather than frozen moat */
    for (i = 1; i < COLNO; i++)
        for (j = 0; j < ROWNO; j++) {
            if (levl[i][j].typ == LAVAPOOL)
                levl[i][j].lit = TRUE;
            else if (levl[i][j].typ == ICE)
                levl[i][j].icedpool = icedpools ? ICED_POOL : ICED_MOAT;
        }
}

/*
 * TODO: If we really want to remove rooms after a map is plopped down
 * in a special level, this needs to be rewritten - the maps may have
 * holes in them ("x" mapchar), leaving parts of rooms still on the map.
 *
 * When level processed by join_map is overlaid by a MAP, some rooms may no
 * longer be valid.  All rooms in the region lx <= x < hx, ly <= y < hy are
 * removed.  Rooms partially in the region are truncated.  This function
 * must be called before the REGIONs or ROOMs of the map are processed, or
 * those rooms will be removed as well.  Assumes roomno fields in the
 * region are already cleared, and roomno and irregular fields outside the
 * region are all set.
 */
void
remove_rooms(int lx, int ly, int hx, int hy)
{
    int i;
    struct mkroom *croom;

    for (i = svn.nroom - 1; i >= 0; --i) {
        croom = &svr.rooms[i];
        if (croom->hx < lx || croom->lx >= hx || croom->hy < ly
            || croom->ly >= hy)
            continue; /* no overlap */

        if (croom->lx < lx || croom->hx >= hx || croom->ly < ly
            || croom->hy >= hy) { /* partial overlap */
            /* TODO: ensure remaining parts of room are still joined */

            if (!croom->irregular)
                impossible("regular room in joined map");
        } else {
            /* total overlap, remove the room */
            remove_room((unsigned) i);
        }
    }
}

/*
 * Remove roomno from the rooms array, decrementing nroom.
 * The last room is swapped with the being-removed room and locations
 * within it have their roomno field updated.  Other rooms are unaffected.
 * Assumes level structure contents corresponding to roomno have already
 * been reset.
 * Currently handles only the removal of rooms that have no subrooms.
 */
staticfn void
remove_room(unsigned int roomno)
{
    struct mkroom *croom = &svr.rooms[roomno];
    struct mkroom *maxroom = &svr.rooms[--svn.nroom];
    int i, j;
    unsigned oroomno;

    if (croom != maxroom) {
        /* since the order in the array only matters for making corridors,
         * copy the last room over the one being removed on the assumption
         * that corridors have already been dug. */
        *croom = *maxroom;

        /* since maxroom moved, update affected level roomno values */
        oroomno = svn.nroom + ROOMOFFSET;
        roomno += ROOMOFFSET;
        for (i = croom->lx; i <= croom->hx; ++i)
            for (j = croom->ly; j <= croom->hy; ++j) {
                if (levl[i][j].roomno == oroomno)
                    levl[i][j].roomno = roomno;
            }
    }

    maxroom->hx = -1; /* just like add_room */
}

#define N_P1_ITER 1 /* tune map generation via this value */
#define N_P2_ITER 1 /* tune map generation via this value */
#define N_P3_ITER 2 /* tune map smoothing via this value */

boolean
litstate_rnd(int litstate)
{
    if (litstate < 0)
        return (rnd(1 + abs(depth(&u.uz))) < 11 && rn2(77)) ? TRUE : FALSE;
    return (boolean) litstate;
}

void
mkmap(lev_init *init_lev)
{
    schar bg_typ = init_lev->bg, fg_typ = init_lev->fg;
    boolean smooth = init_lev->smoothed, join = init_lev->joined;
    xint16 lit = init_lev->lit, walled = init_lev->walled;
    int i;

    lit = litstate_rnd(lit);

    gn.new_locations = (char *) alloc((WIDTH + 1) * HEIGHT);

    init_map(bg_typ);
    init_fill(bg_typ, fg_typ);

    for (i = 0; i < N_P1_ITER; i++)
        pass_one(bg_typ, fg_typ);

    for (i = 0; i < N_P2_ITER; i++)
        pass_two(bg_typ, fg_typ);

    if (smooth)
        for (i = 0; i < N_P3_ITER; i++)
            pass_three(bg_typ, fg_typ);

    if (join)
        join_map(bg_typ, fg_typ);

    /* Apply rivers to certain quest fill levels */
    if (In_quest(&u.uz) && !Is_qstart(&u.uz) && !Is_nemesis(&u.uz)
        && (Role_if(PM_CAVE_DWELLER)
        || Role_if(PM_BARBARIAN)
        || Role_if(PM_RANGER)
        || Role_if(PM_TOURIST)
        /* Added a minefill map to monk quest */
        || Role_if(PM_MONK))) {
        mkrivers();
    }

    finish_map(fg_typ, bg_typ, (boolean) lit, (boolean) walled,
               init_lev->icedpools);
    /* a walled, joined level is cavernous, not mazelike -dlc */
    if (walled && join) {
        svl.level.flags.is_maze_lev = FALSE;
        svl.level.flags.is_cavernous_lev = TRUE;
    }
    free(gn.new_locations);
}

staticfn void
mkrivers(void)
{
    int nriv = rn2(3) + 1;
    while (nriv--) {
        if (rn2(2))
            makeriver(0, rn2(ROWNO), COLNO - 1, rn2(ROWNO));
        else
            makeriver(rn2(COLNO), 0, rn2(COLNO), ROWNO - 1);
    }
}

staticfn void
makeriver(int x1, int y1, int x2, int y2)
{
    int cx, cy, dx, dy, chance, count = 0, monstcount = rnd(4);
    cx = x1;
    cy = y1;

    while (count++ < 2000) {
      	int rnum = levl[cx][cy].roomno - ROOMOFFSET;
      	chance = 0;
        if (rnum >= 0 && svr.rooms[rnum].rtype != OROOM)
            chance = 0;
        else if (levl[cx][cy].typ == STAIRS)
            chance = 0;
        /* damp terrain replacing stairs currently isn't
           possible as makeriver() is only called during
           mines creation, but good to guard against should
           makeriver() ever be called after mkstairs() */
        else if (levl[cx][cy].typ == STAIRS)
            chance = 0;
        else if (levl[cx][cy].typ == CORR)
            chance = 15;
        else if (levl[cx][cy].typ == ROOM)
            chance = 30;
        else if (IS_OBSTRUCTED(levl[cx][cy].typ))
            chance = 100;

        if (rn2(100) < chance && !t_at(cx, cy)) {
            levl[cx][cy].typ = rn2(3) ? PUDDLE : POOL;
            levl[cx][cy].lit = 1;
      	}

        if (cx == x2 && cy == y2)
            break;

        if (cx < x2 && !rn2(3))
            dx = 1;
        else if (cx > x2 && !rn2(3))
            dx = -1;
        else
            dx = 0;

        if (cy < y2 && !rn2(3))
            dy = 1;
        else if (cy > y2 && !rn2(3))
            dy = -1;
        else
            dy = 0;

        switch (rn2(16)) {
            default: break;
            case 1: dx--; dy--;
                break;
            case 2: dx++; dy--;
                break;
            case 3: dx--; dy++;
                break;
            case 4: dx++; dy++;
                break;
            case 5: dy--;
                break;
            case 6: dy++;
                break;
            case 7: dx--;
                break;
            case 8: dx++;
                break;
      	}

        if (dx < -1)
            dx = -1;
        else if (dx > 1)
            dx = 1;

        if (dy < -1)
            dy = -1;
        else if (dy > 1)
            dy = 1;

        cx += dx;
        cy += dy;

        if (cx < 0)
            cx = 0;
        else if (cx >= COLNO)
            cx = COLNO - 1;

        if (cy < 0)
            cy = 0;
        else if (cy >= ROWNO)
            cy = ROWNO - 1;
    }
    /* Loop through and spawn some monsters. Since rivers are
       currently only made in the gnomish mines, no need to
       specify In_mines(&u.uz) */
    count = 0;
    while (count++ < 2000 && monstcount > 0) {
        cx = 1 + rn2(COLNO - 2);
        cy = 1 + rn2(ROWNO - 2);
        if (levl[cx][cy].typ == POOL || levl[cx][cy].typ == PUDDLE) {
            if (u.uz.dlevel >= 5) {
                (void) makemon(rn2(20) ? &mons[PM_JELLYFISH +
                                               rn2(PM_ELECTRIC_EEL - PM_JELLYFISH)]
                                       : rn2(8) ? &mons[PM_WATER_MOCCASIN]
                                                : &mons[PM_WATER_TROLL],
                                                cx, cy, NO_MM_FLAGS);
            } else {
                (void) makemon(&mons[PM_JELLYFISH +
                               rn2(PM_ELECTRIC_EEL - PM_JELLYFISH)],
                               cx, cy, NO_MM_FLAGS);
            }
            monstcount--;
        }
    }
    if (!(levl[cx][cy].typ == POOL || levl[cx][cy].typ == PUDDLE))
        maybe_unhide_at(cx, cy);
}

/*mkmap.c*/
