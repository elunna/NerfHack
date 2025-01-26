/* NetHack 3.7	mkmap.c	$NHDT-Date: 1717432093 2024/06/03 16:28:13 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.40 $ */
/* Copyright (c) J. C. Collet, M. Stephenson and D. Cohrs, 1992   */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"
#include "sp_lev.h"

#define HEIGHT (ROWNO - 1)
#define WIDTH (COLNO - 2)

staticfn void init_map(schar);
staticfn void init_fill(schar, schar);
staticfn schar get_map(coordxy, coordxy, schar);
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

/* Unconditionally sets the whole map's terrain to bg_typ. */
staticfn void
init_map(schar bg_typ)
{
    coordxy x, y;

    for (x = 1; x < COLNO; x++)
        for (y = 0; y < ROWNO; y++) {
            levl[x][y].roomno = NO_ROOM;
            levl[x][y].typ = bg_typ;
            levl[x][y].lit = FALSE;
        }
}

/* Randomly replaces 2/5 of squares on the level that have bg_typ terrain
 * with terrain of fg_typ.
 * Used to "seed" the random cavern-like generation. */
staticfn void
init_fill(schar bg_typ, schar fg_typ)
{
    coordxy x, y;
    long limit, count;

    limit = (WIDTH * HEIGHT * 2) / 5;
    count = 0;
    while (count < limit) {
        x = (coordxy) rn1(WIDTH - 1, 2);
        y = (coordxy) rnd(HEIGHT - 1);
        if (levl[x][y].typ == bg_typ) {
            levl[x][y].typ = fg_typ;
            count++;
        }
    }
}

/* Return the terrain type at the given location, or bg_typ if out of bounds.
 * Used in determining the count of "live" neighbors in cavernous generation
 * (outside the map all counts as dead). */
staticfn schar
get_map(coordxy col, coordxy row, schar bg_typ)
{
    if (col <= 0 || row < 0 || col > WIDTH || row >= HEIGHT)
        return bg_typ;
    return levl[col][row].typ;
}

staticfn const int dirs[16] = {
    -1, -1 /**/, -1,  0 /**/, -1, 1 /**/, 0, -1 /**/,
     0,  1 /**/,  1, -1 /**/,  1, 0 /**/, 1,  1
};

/* First pass of the cavernous generation: essentially one iteration of
 * Conway's Game of Life applied to levl.
 *
 * Evaluate each cell's neighbors to see if they are "alive" (fg_typ terrain)
 * or "dead" (bg_typ terrain), counting the edge of the map as dead.
 * If a dead cell has 5 or more alive neighbors it turns into fg_typ (becoming
 * alive). If an alive cell has 2 or fewer alive neighbors it turns into bg_typ
 * (becoming dead). Cells with 3 or 4 alive neighbors remain the way they are.
 *
 * Note that this is NOT storing the results in a backup buffer. It edits levl
 * as it goes, meaning that the results for some cells may be affected by the
 * previous results. Not sure why it doesn't use new_locations like the other
 * pass_* functions do.
 */
staticfn void
pass_one(schar bg_typ, schar fg_typ)
{
    coordxy x, y;
    short count, dr;

    for (x = 2; x <= WIDTH; x++)
        for (y = 1; y < HEIGHT; y++) {
            for (count = 0, dr = 0; dr < 8; dr++)
                if (get_map(x + dirs[dr * 2], y + dirs[(dr * 2) + 1], bg_typ)
                    == fg_typ)
                    count++;

            switch (count) {
            case 0: /* death */
            case 1:
            case 2:
                levl[x][y].typ = bg_typ;
                break;
            case 5:
            case 6:
            case 7:
            case 8:
                levl[x][y].typ = fg_typ;
                break;
            default:
                break;
            }
        }
}

#define new_loc(i, j) *(gn.new_locations + ((j) * (WIDTH + 1)) + (i))

/* Second pass at the game of life cellular automaton, except unlike the last
 * time, all it is doing is converting cells with exactly 5 neighbors into dead
 * cells.
 *
 * This time, it stores results in a temporary buffer, then copies them over
 * after it finishes. */
staticfn void
pass_two(schar bg_typ, schar fg_typ)
{
    coordxy x, y;
    short count, dr;

    for (x = 2; x <= WIDTH; x++)
        for (y = 1; y < HEIGHT; y++) {
            for (count = 0, dr = 0; dr < 8; dr++)
                if (get_map(x + dirs[dr * 2], y + dirs[(dr * 2) + 1], bg_typ)
                    == fg_typ)
                    count++;
            if (count == 5)
                new_loc(x, y) = bg_typ;
            else
                new_loc(x, y) = get_map(x, y, bg_typ);
        }

    for (x = 2; x <= WIDTH; x++)
        for (y = 1; y < HEIGHT; y++)
            levl[x][y].typ = new_loc(x, y);
}

/* Third pass at the cellular automaton: kill any live cells with fewer than 3
 * live neighbors.
 *
 * Like pass_two, it uses the new_locations temporary buffer and doesn't save
 * changes to levl until it's finished determining all the cell states.
 *
 * According to code below, this is used to tune map smoothing.*/
staticfn void
pass_three(schar bg_typ, schar fg_typ)
{
    coordxy x, y;
    short count, dr;

    for (x = 2; x <= WIDTH; x++)
        for (y = 1; y < HEIGHT; y++) {
            for (count = 0, dr = 0; dr < 8; dr++)
                if (get_map(x + dirs[dr * 2], y + dirs[(dr * 2) + 1], bg_typ)
                    == fg_typ)
                    count++;
            if (count < 3)
                new_loc(x, y) = bg_typ;
            else
                new_loc(x, y) = get_map(x, y, bg_typ);
        }

    for (x = 2; x <= WIDTH; x++)
        for (y = 1; y < HEIGHT; y++)
            levl[x][y].typ = new_loc(x, y);
}

/*
 * use a flooding algorithm to find all locations that should
 * have the same rm number as the current location.
 * if anyroom is TRUE, use IS_ROOM to check room membership instead of
 * exactly matching levl[sx][sy].typ and walls are included as well.
 */
void
flood_fill_rm(
    coordxy sx,
    coordxy sy,
    int rmno,
    boolean lit,
    boolean anyroom)
{
    coordxy i, nx;
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
            coordxy ii, jj;
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

/* Connects all the discrete blobs of fg_typ on the level with "corridors" made
 * of fg_typ.
 * Does this by finding the blobs via floodfill and labeling each as a separate
 * irregular room, then picking a random coordinate within the
 * already-connected rooms and some other room that isn't connected yet.
 * If any blob is of size 3 or less, it'll be removed instead of being
 * connected. */
staticfn void
join_map(schar bg_typ, schar fg_typ)
{
    struct mkroom *croom, *croom2;

    coordxy x, y, sx, sy;
    coord sm, em;

    /* first, use flood filling to find all of the regions that need joining
     */
    for (x = 2; x <= WIDTH; x++)
        for (y = 1; y < HEIGHT; y++) {
            if (levl[x][y].typ == fg_typ && levl[x][y].roomno == NO_ROOM) {
                gm.min_rx = gm.max_rx = x;
                gm.min_ry = gm.max_ry = y;
                gn.n_loc_filled = 0;
                flood_fill_rm(x, y, svn.nroom + ROOMOFFSET, FALSE, FALSE);
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

/* Post-processing of a level to set some final attributes which may be defined
 * in a special level or otherwise.
 * If lit is TRUE, the entire level will be lit, excluding rock terrain.
 * If walled is TRUE, the level will be wallified.
 * If icedpools is TRUE, any ice on the level will be treated as a pool rather
 * than a moat.
 * Also automatically sets any lava terrain to be lit.
 */
staticfn void
finish_map(
    schar fg_typ,
    schar bg_typ,
    boolean lit,
    boolean walled,
    boolean icedpools)
{
    coordxy x, y;

    if (walled)
        wallify_map(1, 0, COLNO-1, ROWNO-1);

    if (lit) {
        for (x = 1; x < COLNO; x++)
            for (y = 0; y < ROWNO; y++)
                if ((!IS_OBSTRUCTED(fg_typ) && levl[x][y].typ == fg_typ)
                    || (!IS_OBSTRUCTED(bg_typ) && levl[x][y].typ == bg_typ)
                    || (bg_typ == TREE && levl[x][y].typ == bg_typ)
                    || (walled && IS_WALL(levl[x][y].typ)))
                    levl[x][y].lit = TRUE;
        for (x = 0; x < svn.nroom; x++)
            svr.rooms[x].rlit = 1;
    }
    /* light lava even if everything's otherwise unlit;
       ice might be frozen pool rather than frozen moat */
    for (x = 1; x < COLNO; x++)
        for (y = 0; y < ROWNO; y++) {
            if (levl[x][y].typ == LAVAPOOL)
                levl[x][y].lit = TRUE;
            else if (levl[x][y].typ == ICE)
                levl[x][y].icedpool = icedpools ? ICED_POOL : ICED_MOAT;
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
remove_rooms(coordxy lx, coordxy ly, coordxy hx, coordxy hy)
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
    coordxy x, y;
    unsigned oroomno;

    if (croom != maxroom) {
        /* since the order in the array only matters for making corridors,
         * copy the last room over the one being removed on the assumption
         * that corridors have already been dug. */
        *croom = *maxroom;

        /* since maxroom moved, update affected level roomno values */
        oroomno = svn.nroom + ROOMOFFSET;
        roomno += ROOMOFFSET;
        for (x = croom->lx; x <= croom->hx; ++x)
            for (y = croom->ly; y <= croom->hy; ++y) {
                if (levl[x][y].roomno == oroomno)
                    levl[x][y].roomno = roomno;
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

/* Fully create a level with the cavernous generation filler algorithm.
 * Extracts its parameters from the fields of its init_lev argument, which
 * control smoothing, joining, wallification, and lighting.
 *
 * N_P1_ITER and friends control the number of times that each pass_* function
 * will be run. Note that pass_three is called only if init_lev->smoothed is
 * TRUE, regardless of what N_P3_ITER is.
 */
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
