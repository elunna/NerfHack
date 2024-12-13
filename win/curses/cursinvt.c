/* vim:set cin ft=c sw=4 sts=4 ts=8 et ai cino=Ls\:0t0(0 : -*- mode:c;fill-column:80;tab-width:8;c-basic-offset:4;indent-tabs-mode:nil;c-file-style:"k&r" -*-*/
/* NetHack 3.7 cursinvt.c */
/* Copyright (c) Fredrik Ljungdahl, 2017. */
/* NetHack may be freely redistributed.  See license for details. */

#include "curses.h"
#include "hack.h"
#include "wincurs.h"
#include "cursinvt.h"

static void curs_invt_updated(WINDOW *);
static unsigned pi_article_skip(const char *);
static int curs_scroll_invt(WINDOW *);
static void curs_show_invt(WINDOW *);

/*
 * Persistent inventory (perm_invent) for curses interface.
 * It resembles a menu but does not function like one.
 */

/* pseudo menu line data */
struct pi_line {
    char *invtxt;  /* class header or inventory item without letter prefix */
    attr_t c_attr; /* attribute for class headers */
    int color;
    char letter;   /* inventory letter; accelerator if this was really a menu;
                    * used to distinguish item lines from header lines and for
                    * display (no selection possible) */
};
static struct pi_line zero_pi_line;

/* full perm_invent data; added to array[] one line at a time */
struct pi_data {
    struct pi_line *array;         /* one element for each line of perminv */
    unsigned allocsize, inuseindx; /* num elements allocated and populated */
    unsigned rowoffset, coloffset; /* for displaying a subset due to space */
    unsigned widest;               /* longest array[].invtxt */
};
#define PERMINV_CHUNK 20 /* number of elements to grow array[] when needed */

/* current persistent inventory */
static struct pi_data pi = { (struct pi_line *) 0, 0, 0, 0, 0, 0 };

/* discard saved persistent inventory data */
void
curs_purge_perminv_data(boolean everything)
{
    if (pi.array) {
        unsigned idx;

        for (idx = 0; idx < pi.inuseindx; ++idx)
            free(pi.array[idx].invtxt), pi.array[idx].invtxt = 0;

        if (everything)
            free(pi.array), pi.array = 0, pi.allocsize = 0;
    }

    pi.inuseindx = 0;
    pi.rowoffset = pi.coloffset = 0;
    pi.widest = 0;
}

/* Runs when the game indicates that the inventory has been updated */
void
curs_update_invt(int arg)
{
    WINDOW *win = curses_get_nhwin(INV_WIN);

    /* Check if the inventory window is enabled in first place */
    if (!win) {
        /* It's not. Re-initialize the main windows if the
           option was enabled. */
        if (iflags.perm_invent) {
            /* [core_]status_initialize, curses_create_main_windows,
               curses_last_messages, [core_]doredraw; doredraw will
               call (*update_inventory) [curses_update_inventory] which
               will call us but 'win' should be defined that time */
            curs_reset_windows(TRUE, FALSE);
            /* TODO: guard against window creation failure [if that's
               possible] which would lead to uncontrolled recursion */
        }
        return;
    }

    /* clear anything displayed from previous update */
    werase(win);

    if (!arg) {
        /*
         * 'arg'==0 means basic inventory_update():  [re-]populate and
         * [re-]display the persistent inventory window.
         */
        if (pi.array) /* previous data is obsolete */
            curs_purge_perminv_data(FALSE);

        /* ask core to display full inventory in a PICK_NONE menu;
           instead of setting up an ordinary menu, it will indirectly
           call curs_add_invt() for each line (including class headers) */
        display_inventory(NULL, FALSE);
        curs_invt_updated(win);

    } else {
        /*
         * 'arg'!=0 means #perminv command is providing the player
         * with opportunity to scroll the already displayed persistent
         * inventory window.  Aside from being non-zero, the value of
         * 'arg' is ignored.
         */
        int scrollingdone;

        /* previous data is still valid; let player interactively scroll it */
        do {
            scrollingdone = curs_scroll_invt(win);
            curs_invt_updated(win);
        } while (!scrollingdone);

    }
    return;
}

/* persistent inventory has been updated or scrolled/panned; re-display it */
static void
curs_invt_updated(WINDOW *win)
{
    /* display collected inventory data, probably clipped */
    curs_show_invt(win);

    if (curses_window_has_border(INV_WIN))
        box(win, 0, 0);

    wnoutrefresh(win);
}

/* scroll persistent inventory window forwards or backwards or side-to-side */
static int
curs_scroll_invt(WINDOW *win UNUSED)
{
    char menukeys[QBUFSZ], qbuf[QBUFSZ];
    unsigned uheight, uwidth, uhalfwidth, scrlmask;
    int ch, menucmd, height, width;
    int res = 0;

    curses_get_window_size(INV_WIN, &height, &width);
    uheight    = (unsigned) height;
    uwidth     = (unsigned) width;
    uhalfwidth = uwidth / 2;

    menukeys[0] = '\0';
    scrlmask = 0U;
    if (pi.rowoffset > 0)
        scrlmask |= 1U; /* include scroll backwards: ^ and < */
    if (pi.rowoffset + uheight <= pi.inuseindx)
        scrlmask |= 2U; /* include scroll forwards: > and | */
    if (pi.coloffset > 0)
        scrlmask |= 4U; /* include scroll left: { */
    if (pi.widest > pi.coloffset + uwidth)
        scrlmask |= 8U; /* include scroll right: } */
    (void) collect_menu_keys(menukeys, scrlmask, TRUE);

    Snprintf(qbuf, sizeof qbuf, "Inventory scroll: [%s%s%s] ",
             menukeys, *menukeys ? " " : "", "Ret Esc");

    curses_count_window(qbuf);
    ch = getch();
    curses_count_window((char *) 0);
    curses_clear_unhighlight_message_window();

    menucmd = (ch <= 0 || ch >= 255) ? ch : (int) (uchar) map_menu_cmd(ch);
    switch (menucmd) {
    case KEY_ESC:
    case C('c'): /* ^C */
        /* for <escape>, leave window with scrolling as-is */
        res = -1;
        break;
    case '\n':
    case '\r':
    case '\b':
    case '\177':
        /* for <return>, or <space> when already on last page,
           restore window to unscrolled */
        pi.rowoffset = pi.coloffset = 0;
        res = 1;
        break;
    case ' ':
        if (pi.rowoffset + uheight <= pi.inuseindx) {
            pi.rowoffset = pi.coloffset = 0;
            res = 1;
            break;
        }
        FALLTHROUGH;
        /*FALLTHRU*/
    case KEY_RIGHT:
    case KEY_NPAGE:
    case MENU_NEXT_PAGE:
        if (pi.inuseindx <= uheight)
            pi.rowoffset = 0;
        else if (pi.rowoffset + 2 * uheight <= pi.inuseindx)
            pi.rowoffset += uheight;
        else
            pi.rowoffset = pi.inuseindx - (uheight - 1);
        break;
    case KEY_LEFT:
    case KEY_PPAGE:
    case MENU_PREVIOUS_PAGE:
        if (pi.rowoffset >= uheight)
            pi.rowoffset -= uheight;
        else
            pi.rowoffset = 0;
        break;

    case KEY_END:
    case MENU_LAST_PAGE:
        if (pi.inuseindx > uheight)
            pi.rowoffset = pi.inuseindx - (uheight - 1);
        else
            pi.rowoffset = 0;
        break;
    case KEY_HOME:
    case MENU_FIRST_PAGE:
        pi.rowoffset = 0;
        break;

    case KEY_DOWN:
        if (pi.rowoffset + uheight <= pi.inuseindx)
            pi.rowoffset += 1;
        break;
    case KEY_UP:
        if (pi.rowoffset > 0)
            pi.rowoffset -= 1;
        else
            pi.rowoffset = 0;
        break;

    case MENU_SHIFT_RIGHT:
        if (pi.widest <= uwidth) {
            pi.coloffset = 0;
        } else {
            pi.coloffset += uhalfwidth;
            if (pi.coloffset + uwidth > pi.widest)
                pi.coloffset = pi.widest - uwidth;
        }
        break;
    case MENU_SHIFT_LEFT:
        if (pi.coloffset >= uhalfwidth)
            pi.coloffset -= uhalfwidth;
        else
            pi.coloffset = 0;
        break;

#if 0
    case MENU_SEARCH:
        break;
#endif
    case '\0':
    default:
        curses_nhbell();
        break;
    }
    return res;
}

/* check 'str' for an article prefix and return length of that */
static unsigned
pi_article_skip(const char *str)
{
    unsigned skip = 0; /* number of chars to skip when displaying str */

    /*
     * if (!strncmp(str, "a ", 2))
     *     skip = 2;
     * else if (!strncmp(str, "an ", 3))
     *     skip = 3;
     * else if (!strncmp(str, "the ", 4))
     *     skip = 4;
     */
    if (str[0] == 'a') {
        if (str[1] == ' ')
            skip = 2;
        else if (str[1] == 'n' && str[2] == ' ')
            skip = 3;
    } else if (str[0] == 't') {
        if (str[1] == 'h' && str[2] == 'e' && str[3] == ' ')
            skip = 4;
    }

    return skip;
}

/* store an inventory item or class header but don't display anything yet */
void
curs_add_invt(
    int linenum,      /* line index; 1..n rather than 0..n-1 */
    char accelerator, /* selector letter for items, 0 for class headers */
    attr_t attr,      /* curses attribute for headers, 0 for items */
    int clr,          /* NetHack color for headers, NO_COLOR for items */
    const char *str)  /* formatted inventory item, without invlet prefix,
                       * or class header text */
{
    unsigned idx, len;
    struct pi_line newelement, *aptr = pi.array;

    if ((unsigned) linenum > pi.allocsize) {
        pi.allocsize += PERMINV_CHUNK;
        pi.array = (struct pi_line *) alloc(pi.allocsize * sizeof *aptr);
        for (idx = 0; idx < pi.allocsize; ++idx)
            pi.array[idx] = (idx < pi.inuseindx) ? aptr[idx] : zero_pi_line;
        if (aptr)
            free(aptr);
        aptr = pi.array;
    }

    newelement.invtxt = dupstr(str);
    newelement.c_attr = attr; /* note: caller has already converted 'attr'
                               * from tty-style attribute to curses one */
    newelement.color = clr;
    newelement.letter = accelerator;
    aptr[pi.inuseindx++] = newelement;

    len = strlen(str);
    if (accelerator) {
        /* +4: " )c " inventory letter will be inserted before invtxt;
           invtxt's "a "/"an "/"the " prefix, if any, will be skipped */
        len += 4;
        if (len > pi.widest)
            len -= pi_article_skip(str);
    }
    if (len > pi.widest)
        pi.widest = len;
}

/* display the inventory menu-like data collected in pi.array[] */
static void
curs_show_invt(WINDOW *win)
{
    const char *str;
    char accelerator, tmpbuf[BUFSZ];
    int attr, color;
    unsigned lineno, stroffset, widest, left_col, right_col,
        first_shown = 0, last_shown = 0, item_count = 0, xtra_line = 0;
    int x, y, width, height, available_width,
        border = curses_window_has_border(INV_WIN) ? 1 : 0,
        /* we actually care about the topmost of message, map, or status
           but either they all have borders or none do so just check map */
        otherborder = curses_window_has_border(MAP_WIN) ? 1 : 0;

    x = border; /* same for every line; 1 if border, 0 otherwise */

    curses_get_window_size(INV_WIN, &height, &width);
    widest = pi.widest;
    left_col = pi.coloffset + 1;
    right_col = left_col + (unsigned) width - 1;

    /*
     * If there will be any blank lines left at the bottom, sometimes
     * insert one blank line at the top.  If the first line is an item
     * (via !sortpack) which will be obscured by the column indicator,
     * or there is only one line (such as "not carrying anything") if
     * that line would be at the very top aligned with the top border
     * of another window (windowborders=3,4) because that looks odd.
     * This only handles the single page case [because scrolling always
     * fills pages beyond the first rather than just continuing from
     * last line of preceding page, hence no blank line(s) at bottom].
     */
    if ((pi.array[0].letter && pi.inuseindx < (unsigned) height
         && widest > (unsigned) width)
        || (pi.inuseindx == 1 && otherborder && !border)) {
        wmove(win, 1, x);
        wprintw(win, "%.*s", width - 2 * border, "");
        xtra_line = 1;
    }

    for (lineno = 0; lineno < pi.rowoffset; ++lineno)
        if (pi.array[lineno].letter)
            ++item_count;

    for (lineno = pi.rowoffset; lineno < pi.inuseindx; ++lineno) {
        str = pi.array[lineno].invtxt;
        accelerator = pi.array[lineno].letter;
        attr = pi.array[lineno].c_attr; /* already converted when stored */
        color = pi.array[lineno].color;
        if (color == NO_COLOR)
            color = NONE;

        if (accelerator)
            ++item_count;

        /* Figure out where to draw the line */
        y = (int) (lineno + xtra_line - pi.rowoffset) + border;
        if (y - border >= height) { /* height already -2 for Top+Btm border */
            /* 'y' has grown too big; there are too many lines to fit */
            continue; /* skip, but still loop to update 'item_count' */
        }
        available_width = width; /* width is already -2 for Lft+Rgt borders */

        wmove(win, y, x);

        stroffset = 0;
        if (accelerator) { /* inventory item line */
            if (!first_shown)
                first_shown = item_count;
            last_shown = item_count;
            /* despite being shown as a menu, nothing is selectable from the
               persistent inventory window so avoid the usual highlighting
               of inventory letters */
            wprintw(win, " %c) ", accelerator);
            available_width -= 4; /* space+letter+parenthesis+space */

            /*
             * Narrow the entries to fit more of the interesting text,
             * but defer the removal until after menu colors matching.
             * Do so unconditionally rather than trying to figure whether
             * it's needed.  When 'sortpack' is enabled we could also strip
             * out "<class> of" from "<prefix><class> of <item><suffix>"
             * but if that's to be done, the core ought to do it.
             */
            stroffset = pi_article_skip(str); /* to skip "a "/"an "/"the " */
            /* if/when scrolled right, invtxt for item lines gets shifted */
            stroffset += pi.coloffset;
        }

        if (stroffset < strlen(str)) {
            curses_menu_color_attr(win, color, attr, ON);
            wprintw(win, "%.*s", available_width, str + stroffset);
            curses_menu_color_attr(win, color, attr, OFF);
        }

        wclrtoeol(win);
    } /* lineno loop */

    if (pi.inuseindx > (unsigned) height) {
        /*
         * More lines than will fit at one time so some lines aren't shown.
         * Overwrite the rightmost portion of last line with something
         * like "[1-24 of 30>" or "<7-30 of 30]" if we've already scrolled
         * forward.  Right justified so that the line might still show
         * something useful. It could be on a line of its own, in which
         * case we need to erase that first.
         */
        y = height - (1 - border);
        if ((unsigned) y == pi.inuseindx - pi.rowoffset) {
            wmove(win, y, x);
            wclrtoeol(win);
        }
        Sprintf(tmpbuf, "%c%u-%u of %u%c",
                (first_shown > 1) ? '<' : '[',
                first_shown, last_shown, item_count,
                (last_shown < item_count) ? '>' : ']');
        mvwaddstr(win, y, x + (width - (int) strlen(tmpbuf)), tmpbuf);
    }
    if (widest > (unsigned) width) {
        /*
         * More columns than the persistent inventory window can fit so
         * some columns aren't shown.  Overwrite the rightmost portion of
         * first line with something like "[1-25 of 40}" or "{16-40 of 40]".
         * For the usual case, that line will be an object class header
         * so we won't be obscuring an item, but that might not be the
         * situation on page 2 and definitely won't be if 'sortpack' is Off.
         */
        Sprintf(tmpbuf, "%c%u-%u of %u%c",
                (left_col > 1) ? '{' : '[',
                left_col, right_col, widest,
                (right_col < widest) ? '}' : ']');
        mvwaddstr(win, border, x + (width - (int) strlen(tmpbuf)), tmpbuf);
    }
    return;
}
