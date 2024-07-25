/* NetHack 3.7	mail.c	$NHDT-Date: 1596498174 2020/08/03 23:42:54 $  $NHDT-Branch: NetHack-3.7 $:$NHDT-Revision: 1.47 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/*-Copyright (c) Pasi Kallinen, 2018. */
/* NetHack may be freely redistributed.  See license for details. */

#include "hack.h"

#ifdef MAIL
#ifdef SIMPLE_MAIL
# include <fcntl.h>
# include <errno.h>
#endif /* SIMPLE_MAIL */
#endif /* MAIL */
#ifdef MAIL_STRUCTURES
#include "mail.h"
#endif

#ifdef MAIL
/*
 * Notify user when new mail has arrived.  Idea by Merlyn Leroy.
 *
 * The mail daemon can move with less than usual restraint.  It can:
 *      - move diagonally from a door
 *      - use secret and closed doors
 *      - run through a monster ("Gangway!", etc.)
 *      - run over pools & traps
 *
 * Possible extensions:
 *      - Open the file MAIL and do fstat instead of stat for efficiency.
 *        (But sh uses stat, so this cannot be too bad.)
 *      - Examine the mail and produce a scroll of mail named "From somebody".
 *      - Invoke MAILREADER in such a way that only this single mail is read.
 *      - Do something to the text when the scroll is enchanted or cancelled.
 *      - Make the daemon always appear at a stairwell, and have it find a
 *        path to the hero.
 *
 * Note by Olaf Seibert: On the Amiga, we usually don't get mail.  So we go
 *                       through most of the effects at 'random' moments.
 * Note by Paul Winner:  The MSDOS port also 'fakes' the mail daemon at
 *                       random intervals.
 */

staticfn boolean md_start(coord *);
staticfn boolean md_stop(coord *, coord *);
staticfn boolean md_rush(struct monst *, int, int);
staticfn void newmail(struct mail_info *);
#if defined(SIMPLE_MAIL) || defined(SERVER_ADMIN_MSG)
staticfn void read_simplemail(const char *mbox, boolean adminmsg);
#endif

#if !defined(UNIX) && !defined(VMS)
int mustgetmail = -1;
#endif

#ifdef UNIX
#include <sys/stat.h>
#include <pwd.h>
/* DON'T trust all Unices to declare getpwuid() in <pwd.h> */
#if !defined(_BULL_SOURCE) && !defined(__sgi) && !defined(_M_UNIX)
#if !defined(SUNOS4) && !(defined(ULTRIX) && defined(__GNUC__))
/* DO trust all SVR4 to typedef uid_t in <sys/types.h> (probably to a long) */
#if defined(POSIX_TYPES) || defined(SVR4) || defined(HPUX)
extern struct passwd *getpwuid(uid_t);
#else
extern struct passwd *getpwuid(int);
#endif
#endif
#endif
static struct stat omstat, nmstat;
static char *mailbox = (char *) 0;
static long laststattime;

#if !defined(MAILPATH) && defined(AMS) /* Just a placeholder for AMS */
#define MAILPATH "/dev/null"
#endif
#if !defined(MAILPATH) && (defined(LINUX) || defined(__osf__))
#define MAILPATH "/var/spool/mail/"
#endif
#if !defined(MAILPATH) && defined(__FreeBSD__)
#define MAILPATH "/var/mail/"
#endif
#if !defined(MAILPATH) && (defined(BSD) || defined(ULTRIX))
#define MAILPATH "/usr/spool/mail/"
#endif
#if !defined(MAILPATH) && (defined(SYSV) || defined(HPUX))
#define MAILPATH "/usr/mail/"
#endif

void
free_maildata(void)
{
    if (mailbox)
        free((genericptr_t) mailbox), mailbox = (char *) 0;
}

void
getmailstatus(void)
{
    if (mailbox) {
        ; /* no need to repeat the setup */
    } else if ((mailbox = nh_getenv("MAIL")) != 0) {
        mailbox = dupstr(mailbox);
#ifdef MAILPATH
    } else  {
#ifdef AMS
        struct passwd ppasswd;

        (void) memcpy(&ppasswd, getpwuid(getuid()), sizeof (struct passwd));
        if (ppasswd.pw_dir) {
            /* note: 'sizeof "LITERAL"' includes +1 for terminating '\0' */
            mailbox = (char *) alloc((unsigned) (strlen(ppasswd.pw_dir)
                                                 + sizeof AMS_MAILBOX));
            Strcpy(mailbox, ppasswd.pw_dir);
            Strcat(mailbox, AMS_MAILBOX);
        }
#else
        const char *pw_name = getpwuid(getuid())->pw_name;

        /* note: 'sizeof "LITERAL"' includes +1 for terminating '\0' */
        mailbox = (char *) alloc((unsigned) (strlen(pw_name)
                                             + sizeof MAILPATH));
        Strcpy(mailbox, MAILPATH);
        Strcat(mailbox, pw_name);
#endif /* AMS */
#endif /* MAILPATH */
    }

    debugpline3("mailbox=%c%s%c",
                mailbox ? '\"' : '<',
                mailbox ? mailbox : "null",
                mailbox ? '\"' : '>');

    if (mailbox && stat(mailbox, &omstat)) {
#ifdef PERMANENT_MAILBOX
        pline("Cannot get status of MAIL=\"%s\".", mailbox);
        free_maildata(); /* set 'mailbox' to Null */
#else
        omstat.st_mtime = 0;
#endif
    }
}
#endif /* UNIX */

/*
 * Pick coordinates for a starting position for the mail daemon.  Called
 * from newmail() and newphone().
 */
staticfn boolean
md_start(coord *startp)
{
    coord testcc;     /* scratch coordinates */
    int row;          /* current row we are checking */
    int lax;          /* if TRUE, pick a position in sight. */
    int dd;           /* distance to current point */
    int max_distance; /* max distance found so far */
    stairway *stway = gs.stairs;

    /*
     * If blind and not telepathic, then it doesn't matter what we pick ---
     * the hero is not going to see it anyway.  So pick a nearby position.
     */
    if (Blind && !Blind_telepat) {
        if (!enexto(startp, u.ux, u.uy, (struct permonst *) 0))
            return FALSE; /* no good positions */
        return TRUE;
    }

    /*
     * Arrive at an up or down stairwell if it is in line of sight from the
     * hero.
     */
    while (stway) {
        if (stway->tolev.dnum == u.uz.dnum && couldsee(stway->sx, stway->sy)) {
            startp->x = stway->sx;
            startp->y = stway->sy;
            return TRUE;
        }
        stway = stway->next;
    }

    /*
     * Try to pick a location out of sight next to the farthest position away
     * from the hero.  If this fails, try again, just picking the farthest
     * position that could be seen.  What we really ought to be doing is
     * finding a path from a stairwell...
     *
     * The arrays gv.viz_rmin[] and gv.viz_rmax[] are set even when blind.  These
     * are the LOS limits for each row.
     */
    lax = 0; /* be picky */
    max_distance = -1;
 retry:
    for (row = 0; row < ROWNO; row++) {
        if (gv.viz_rmin[row] < gv.viz_rmax[row]) {
            /* There are valid positions on this row. */
            dd = distu(gv.viz_rmin[row], row);
            if (dd > max_distance) {
                if (lax) {
                    max_distance = dd;
                    startp->y = row;
                    startp->x = gv.viz_rmin[row];

                } else if (enexto(&testcc, (coordxy) gv.viz_rmin[row], row,
                                  (struct permonst *) 0)
                           && !cansee(testcc.x, testcc.y)
                           && couldsee(testcc.x, testcc.y)) {
                    max_distance = dd;
                    *startp = testcc;
                }
            }
            dd = distu(gv.viz_rmax[row], row);
            if (dd > max_distance) {
                if (lax) {
                    max_distance = dd;
                    startp->y = row;
                    startp->x = gv.viz_rmax[row];

                } else if (enexto(&testcc, (coordxy) gv.viz_rmax[row], row,
                                  (struct permonst *) 0)
                           && !cansee(testcc.x, testcc.y)
                           && couldsee(testcc.x, testcc.y)) {
                    max_distance = dd;
                    *startp = testcc;
                }
            }
        }
    }

    if (max_distance < 0) {
        if (!lax) {
            lax = 1; /* just find a position */
            goto retry;
        }
        return FALSE;
    }

    return TRUE;
}

/*
 * Try to choose a stopping point as near as possible to the starting
 * position while still adjacent to the hero.  If all else fails, try
 * enexto().  Use enexto() as a last resort because enexto() chooses
 * its point randomly, which is not what we want.
 */
staticfn boolean
md_stop(coord *stopp,  /* stopping position (we fill it in) */
        coord *startp) /* starting position (read only) */
{
    coordxy x, y, distance, min_distance = -1;

    for (x = u.ux - 1; x <= u.ux + 1; x++)
        for (y = u.uy - 1; y <= u.uy + 1; y++) {
            if (!isok(x, y) || u_at(x, y))
                continue;

            if (accessible(x, y) && !MON_AT(x, y)) {
                distance = dist2(x, y, startp->x, startp->y);
                if (min_distance < 0 || distance < min_distance
                    || (distance == min_distance && rn2(2))) {
                    stopp->x = x;
                    stopp->y = y;
                    min_distance = distance;
                }
            }
        }

    /* If we didn't find a good spot, try enexto(). */
    if (min_distance < 0 && !enexto(stopp, u.ux, u.uy, &mons[PM_MAIL_DAEMON]))
        return FALSE;

    return TRUE;
}

/* Let the mail daemon have a larger vocabulary. */
staticfn NEARDATA const char *mail_text[] = { "Gangway!", "Look out!",
                                            "Pardon me!" };
#define md_exclamations() (mail_text[rn2(3)])

/*
 * Make the mail daemon run through the dungeon.  The daemon will run over
 * any monsters that are in its path, but will replace them later.  Return
 * FALSE if the md gets stuck in a position where there is a monster.  Return
 * TRUE otherwise.
 */
staticfn boolean
md_rush(struct monst *md,
        int tx, int ty) /* destination of mail daemon */
{
    struct monst *mon;            /* displaced monster */
    int dx, dy;          /* direction counters */
    int fx = md->mx, fy = md->my; /* current location */
    int nfx = fx, nfy = fy,       /* new location */
        d1, d2;                   /* shortest distances */

    /*
     * It is possible that the monster at (fx,fy) is not the md when:
     * the md rushed the hero and failed, and is now starting back.
     */
    if (m_at(fx, fy) == md) {
        remove_monster(fx, fy); /* pick up from orig position */
        newsym(fx, fy);
    }

    /*
     * At the beginning and exit of this loop, md is not placed in the
     * dungeon.
     */
    while (1) {
        /* Find a good location next to (fx,fy) closest to (tx,ty). */
        d1 = dist2(fx, fy, tx, ty);
        for (dx = -1; dx <= 1; dx++)
            for (dy = -1; dy <= 1; dy++)
                if ((dx || dy) && isok(fx + dx, fy + dy)
                    && !IS_STWALL(levl[fx + dx][fy + dy].typ)) {
                    d2 = dist2(fx + dx, fy + dy, tx, ty);
                    if (d2 < d1) {
                        d1 = d2;
                        nfx = fx + dx;
                        nfy = fy + dy;
                    }
                }

        /* Break if the md couldn't find a new position. */
        if (nfx == fx && nfy == fy)
            break;

        fx = nfx; /* this is our new position */
        fy = nfy;

        /* Break if the md reaches its destination. */
        if (fx == tx && fy == ty)
            break;

        SetVoice(md, 0, 80, 0);
        if ((mon = m_at(fx, fy)) != 0) /* save monster at this position */
            verbalize1(md_exclamations());
        else if (u_at(fx, fy))
            verbalize("Excuse me.");

        if (mon)
            remove_monster(fx, fy);
        place_monster(md, fx, fy); /* put md down */
        newsym(fx, fy);            /* see it */
        flush_screen(0);           /* make sure md shows up */
        nh_delay_output();            /* wait a little bit */

        /* Remove md from the dungeon.  Restore original mon, if necessary. */
        remove_monster(fx, fy);
        if (mon) {
            if ((mon->mx != fx) || (mon->my != fy))
                place_worm_seg(mon, fx, fy);
            else
                place_monster(mon, fx, fy);
        }
        newsym(fx, fy);
    }

    /*
     * Check for a monster at our stopping position (this is possible, but
     * very unlikely).  If one exists, then have the md leave in disgust.
     */
    if ((mon = m_at(fx, fy)) != 0) {
        remove_monster(fx, fy);
        place_monster(md, fx, fy); /* display md with text below */
        newsym(fx, fy);
        SetVoice(md, 0, 80, 0);
        verbalize("This place's too crowded.  I'm outta here.");
        remove_monster(fx, fy);

        if ((mon->mx != fx) || (mon->my != fy)) /* put mon back */
            place_worm_seg(mon, fx, fy);
        else
            place_monster(mon, fx, fy);

        newsym(fx, fy);
        return FALSE;
    }

    place_monster(md, fx, fy); /* place at final spot */
    newsym(fx, fy);
    flush_screen(0);
    nh_delay_output(); /* wait a little bit */

    return TRUE;
}

/* Deliver a scroll of mail. */
/*ARGSUSED*/
staticfn void
newmail(struct mail_info *info)
{
    struct monst *md;
    coord start, stop;
    boolean message_seen = FALSE;

    /* Try to find good starting and stopping places. */
    if (!md_start(&start) || !md_stop(&stop, &start))
        goto give_up;

    /* Make the daemon.  Have it rush towards the hero. */
    if (!(md = makemon(&mons[PM_MAIL_DAEMON], start.x, start.y, NO_MM_FLAGS)))
        goto give_up;
    if (!md_rush(md, stop.x, stop.y))
        goto go_back;

    message_seen = TRUE;
    SetVoice(md, 0, 80, 0);
    verbalize("%s, %s!  %s.", Hello(md), svp.plname, info->display_txt);

    if (info->message_typ) {
        struct obj *obj = mksobj(SCR_MAIL, FALSE, FALSE);

        if (info->object_nam)
            obj = oname(obj, info->object_nam, ONAME_NO_FLAGS);
        if (info->response_cmd)
            new_omailcmd(obj, info->response_cmd);

        if (!m_next2u(md)) {
            SetVoice(md, 0, 80, 0);
            verbalize("Catch!");
        }
        display_nhwindow(WIN_MESSAGE, FALSE);
        obj = hold_another_object(obj, "Oops!", (const char *) 0,
                                  (const char *) 0);
        nhUse(obj);
    }

 go_back:
    /* zip back to starting location */
    if (!md_rush(md, start.x, start.y))
        md->mx = md->my = 0; /* for mongone, md is not on map */
    mongone(md);

 give_up:
    /* deliver some classes of messages even if no daemon ever shows up */
    if (!message_seen && info->message_typ == MSG_OTHER)
        pline("Hark!  \"%s.\"", info->display_txt);
}

#if !defined(UNIX) && !defined(VMS)

void
ckmailstatus(void)
{
    if (u.uswallow || !flags.biff)
        return;
    if (mustgetmail < 0) {
#if defined(AMIGA) || defined(MSDOS) || defined(TOS)
        mustgetmail = (svm.moves < 2000) ? (100 + rn2(2000)) : (2000 + rn2(3000));
#endif
        return;
    }
    if (--mustgetmail <= 0) {
        static struct mail_info deliver = {
            MSG_MAIL, "I have some mail for you", 0, 0
        };
        newmail(&deliver);
        mustgetmail = -1;
    }
}

DISABLE_WARNING_FORMAT_NONLITERAL

enum delivery_types { faulty_delivery, normal_delivery, subst_delivery };

/*ARGSUSED*/
void
readmail(struct obj *otmp UNUSED)
{
    int i;
    enum delivery_types delivery = normal_delivery;
    const char *recipient = 0;
    static const char *const junk_templates[] = {
        "%sReport bugs to <%s>.%s", /*** must be first entry ***/
        "Please disregard previous letter.",
        "Welcome to NerfHack.",
#ifdef AMIGA
        "Only Amiga makes it possible.",
        "CATS have all the answers.",
#endif
        "This mail complies with the Yendorian Anti-Spam Act (YASA)",
        "Please find enclosed a small token to represent your Owlbear",
        "**FR33 P0T10N 0F FULL H34L1NG**",
        "Please return to sender (Asmodeus)",
        /* when enclosed by "It reads:  \"...\"", this is too long
           for an ordinary 80-column display so wraps to a second line
           (suboptimal but works correctly);
           dollar sign and fractional zorkmids are inappropriate within
           nethack but are suitable for typical dysfunctional spam mail */
     "Buy a potion of gain level for only $19.99!  Guaranteed to be blessed!",
        /* DEVTEAM_URL will be substituted for 2nd "%s"; terminating punctuation
           (formerly "!") has deliberately been omitted so that it can't be
           mistaken for part of the URL (unfortunately that is still followed
           by a closing quote--in the pline below, not the data here) */
        "%sInvitation: Visit the NerfHack web site at %s%s"
    };
    const char *const it_reads = "It reads:  \"";

    i = rn2(SIZE(junk_templates));
    if (strchr(junk_templates[i], '%')) {
        if (i == 0) {
            recipient = DEVTEAM_EMAIL;
            delivery = subst_delivery;
        } else if (strstri(junk_templates[i], "web site")) {
            recipient = DEVTEAM_URL;
            delivery = subst_delivery;
        } else {
            impossible("fake mail #%d has undefined substitution", i);
            delivery = faulty_delivery;
        }
    }
    if (Blind) {
        pline("Unfortunately you cannot see what it says.");
    } else {
        if (delivery == subst_delivery)
            pline(junk_templates[i], it_reads, recipient, "\"");
        else if (delivery == normal_delivery)
            pline("%s%s\"", it_reads, junk_templates[i]);
    }
}

RESTORE_WARNING_FORMAT_NONLITERAL

#endif /* !UNIX && !VMS */

#ifdef UNIX

void
ckmailstatus(void)
{
    ck_server_admin_msg();

    if (!mailbox || u.uswallow || !flags.biff
#ifdef MAILCKFREQ
        || svm.moves < laststattime + MAILCKFREQ
#endif
        )
        return;

    laststattime = svm.moves;
    if (stat(mailbox, &nmstat)) {
#ifdef PERMANENT_MAILBOX
        pline("Cannot get status of MAIL=\"%s\" anymore.", mailbox);
        free_maildata();
#else
        nmstat.st_mtime = 0;
#endif
    } else if (nmstat.st_mtime > omstat.st_mtime) {
        if (nmstat.st_size) {
            static struct mail_info deliver = {
#ifndef NO_MAILREADER
                MSG_MAIL, "I have some mail for you",
#else
                /* suppress creation and delivery of scroll of mail */
                MSG_OTHER, "You have some mail in the outside world",
#endif
                0, 0
            };
            newmail(&deliver);
        }
        getmailstatus(); /* might be too late ... */
    }
}

#if defined(SIMPLE_MAIL) || defined(SERVER_ADMIN_MSG)

void
read_simplemail(const char *mbox, boolean adminmsg)
{
    FILE *mb = fopen(mbox, "r");
    char curline[128], *msg;
    boolean seen_one_already = FALSE;
#ifdef SIMPLE_MAIL
    struct flock fl = { 0 };
#endif

    if (!mb)
        goto bail;

#ifdef SIMPLE_MAIL
    fl.l_type = F_RDLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    errno = 0;
#endif

    /* Allow this call to block. */
    if (!adminmsg
#ifdef SIMPLE_MAIL
        && fcntl(fileno(mb), F_SETLKW, &fl) == -1
#endif
        )
        goto bail;

    while (fgets(curline, 128, mb) != NULL) {
        const char *endpunct;
        int msglen;

        if (!adminmsg) {
#ifdef SIMPLE_MAIL
            fl.l_type = F_UNLCK;
            fcntl(fileno(mb), F_UNLCK, &fl);
#endif
            There("is a%s message on this scroll.",
                  seen_one_already ? "nother" : "");
        }
        msg = strchr(curline, ':');

        /* if incorrectly formatted, or message is empty (':' and '\n' take
           up 2 chars, so must have at least 3 to be nonempty), give up */
        if (!msg || (msglen = (int) strlen(msg)) < 3)
            goto bail;

        *msg = '\0';
        msg++, msglen--;
        msg[msglen - 1] = '\0'; /* kill newline */

        /* supply ending punctuation only if the message doesn't have any */
        endpunct = "";
        if (!strchr(".!?", msg[msglen - 2]))
            endpunct = ".";

        if (adminmsg) {
            urgent_pline("The voice of %s booms through the caverns:",
                         curline);
        } else {
            pline("This message is from '%s'.", curline);
            pline("It reads:");
        }
        pline("\"%s\"%s", msg, endpunct);

        seen_one_already = TRUE;
#ifdef SIMPLE_MAIL
        errno = 0;
        if (!adminmsg) {
            fl.l_type = F_RDLCK;
            fcntl(fileno(mb), F_SETLKW, &fl);
        }
#endif
    }

#ifdef SIMPLE_MAIL
    if (!adminmsg) {
        fl.l_type = F_UNLCK;
        fcntl(fileno(mb), F_UNLCK, &fl);
    }
#endif
    fclose(mb);
    if (adminmsg)
        display_nhwindow(WIN_MESSAGE, TRUE);
    else
        unlink(mailbox);
    return;
 bail:
    /* bail out _professionally_ */
    if (!adminmsg)
        pline("It appears to be all gibberish.");
}

#endif /* SIMPLE_MAIL */

void
ck_server_admin_msg(void)
{
#ifdef SERVER_ADMIN_MSG
    static struct stat ost,nst;
    static long lastchk = 0;

    if (svm.moves < lastchk + SERVER_ADMIN_MSG_CKFREQ) return;
    lastchk = svm.moves;

    if (!stat(SERVER_ADMIN_MSG, &nst)) {
        if (nst.st_mtime > ost.st_mtime)
            read_simplemail(SERVER_ADMIN_MSG, TRUE);
        ost.st_mtime = nst.st_mtime;
    }
#endif /* SERVER_ADMIN_MSG */
}

/*ARGSUSED*/
void
readmail(struct obj *otmp UNUSED)
{
#ifdef DEF_MAILREADER /* This implies that UNIX is defined */
    const char *mr = 0;
#endif /* DEF_MAILREADER */
#ifdef SIMPLE_MAIL
    read_simplemail(mailbox, FALSE);
    return;
#endif /* SIMPLE_MAIL */
#ifdef DEF_MAILREADER /* This implies that UNIX is defined */
    if (iflags.debug_fuzzer)
        return;
    display_nhwindow(WIN_MESSAGE, FALSE);
    if (!(mr = nh_getenv("MAILREADER")))
        mr = DEF_MAILREADER;

    if (child(1)) {
        (void) execl(mr, mr, (char *) 0);
        nh_terminate(EXIT_FAILURE);
    }
#else
#ifndef AMS /* AMS mailboxes are directories */
    display_file(mailbox, TRUE);
#endif /* AMS */
#endif /* DEF_MAILREADER */

    /* get new stat; not entirely correct: there is a small time
       window where we do not see new mail */
    getmailstatus();
}

#endif /* UNIX */

#ifdef VMS

extern struct mail_info *parse_next_broadcast(void);

volatile int broadcasts = 0;

void
ckmailstatus(void)
{
    struct mail_info *brdcst;

    if (iflags.debug_fuzzer)
        return;
    if (u.uswallow || !flags.biff)
        return;

    while (broadcasts > 0) { /* process all trapped broadcasts [until] */
        broadcasts--;
        if ((brdcst = parse_next_broadcast()) != 0) {
            newmail(brdcst);
            break; /* only handle one real message at a time */
        }
    }
}

void
readmail(struct obj *otmp)
{
#ifdef SHELL /* can't access mail reader without spawning subprocess */
    const char *txt, *cmd;
    char *p, buf[BUFSZ] = DUMMY, qbuf[BUFSZ];
    int len;

    /* there should be a command in OMAILCMD */
    if (has_oname(otmp))
        txt = ONAME(otmp);
    else
        txt = "";
    len = strlen(txt);
    if (has_omailcmd(otmp))
        cmd = OMAILCMD(otmp);
    if (!cmd || !*cmd)
        cmd = "SPAWN";

    Sprintf(qbuf, "System command (%s)", cmd);
    getlin(qbuf, buf);
    if (*buf != '\033') {
        for (p = eos(buf); p > buf; *p = '\0')
            if (*--p != ' ')
                break; /* strip trailing spaces */
        if (*buf)
            cmd = buf; /* use user entered command */
        if (!strcmpi(cmd, "SPAWN") || !strcmp(cmd, "!"))
            cmd = (char *) 0; /* interactive escape */

        vms_doshell(cmd, TRUE);
        (void) sleep(1);
    }
#else
    nhUse(otmp);
#endif /* SHELL */
}

#endif /* VMS */
#endif /* MAIL */


const char *
get_hint(void)
{
    static const char *hint[] = {
            /* miscellaneous hints */
            "If your have good luck, your stealth will much more effective.",
            "Branchport always brings you to the bottom of the branch.",
            "You can enter the quest at experience level 10 - use discretion!",
            "Chaotics do not get alignment penalties for angering peacefuls.",
            "Swapping weapons take 0 turns.",
            "It's almost impossible to put an identified wand of cancellation into a bag of holding.",
            "Guess what - you already know potions of water, blank scrolls, and scrolls of identify!",
            "If you wield your weapon long enough, it will identify itself.",
            "Peaceful monsters are underlined.",
            "Skill caps and percentage towards next level is available in #enhance.",
            "Show available skill slots in #enhance menu.",
            "> or < can be used to autotravel to stairs with the autostairtravel option.",
            "The showdamage option lets you see damage dealt and flanking bonuses.",
            "The invweight option shows the weight of each item in inventory.",
            "You can #loot your pets to manage their inventory.",
            "Prayer statistics can be viewed in the attributes menu (via Ctrl-X).",
            "Warning shows low level monsters as orange 0's.",
            "Farlook monsters to see if they are sleeping, fleeing, or berserking.",
            "Beware - Conflict negates Elbereth and scare monster protection.",
            "Invisibility and see invisible cannot be permanently gained intrinsically.",
            "Telepathy cannot be permanently gained intrinsically.",
            "Teleportitis cannot be permanently gained intrinsically.",
            "Half-physical and half-spell damage only provide quarter reduction in NerfHack!",
            "Even with a luckstone, your luck will eventually run out.",
            "Don't try to identify the riders, they reveal themselves only when close.",
            "Don't rely on Astral Rain on the Astral Plane.",
            "While you are carrying the Amulet of Yendor, monsters will flood in from the stairs.",
            "When donating, don't be surprised if the gold slips though the priests fingers.",
            "After two gifts have been granted, an altar can crack from additional gifts.",
            "If you receive a gift on a cracked altar, it will crumble and be gone forever.",
            "If you are crowned on a cracked altar, the altar will be destroyed.",
            "Once you are crowned, altars always have a chance to crack when you receive a gift.",
            "Don't try to use your pet to steal from shops - the shopkeepers strictly forbid it.",
            "Don't try to wish for quest artifacts in NerfHack, it's förbjuden.",
            "Thrones no longer grant any wishes, but they might identify all your possessions...",
            "Non-magical items are much less likely to polymorph into magical items.",
            "Don't be surprised if you see more golems when polypiling...",
            "Polypiling is quite draining on items...",
            "Crowning only grants up to 3 abilities in NerfHack.",
            "You may be able to get acid, disintegration, or even petrification resistance from crowning.",
            "Avoid being burdened or worse, it severely affects your AC now!",
            "Dexterity can affect your AC - for better or worse.",
            "Wounded legs can severely affect your AC - try jungle boots to prevent it!",
            "If you wear your armor, it weighs 25% less.",
            "Caution! Only elves can safely enchant elven armor over +3.",
            "Dwarves get a 1AC bonus for each piece of dwarven armor they wear.",
            "Elves get a 1AC bonus for each piece of elven armor they wear.",
            "Gnomes get a 2AC bonus for each piece of gnomish armor they wear.",
            "Orcs get a 1AC bonus for each piece of orcish armor they wear.",
            "Elves, dwarves, orcs, and gnomes strongly prefer their racial armor to others.",
            "Dragon scales and armor provide much less AC in NerfHack.",
            "Dragon scale mail cannot be wished for - but the scales can.",
            "Most resistances are now partial and range from 0%-100%, start building them up!",
            "Reflection doesn't reflect 100% of the damage anymore - your resistances matter more!",
            "Displacement provides fairly reliable protection from gaze attacks.",
            "Invisibility provides quite reliable protection from gaze attacks.",
            "The base memory retention for spells is now 10000 turns.",
            "Primary spellcasters get a memory boost of 500 turns when they cast spells.",
            "Casting your special spell also grants a retention bonus of 500 turns no matter your role.",
            "Wielding a quarterstaff provides a small bonus to spellcasting.",
            "When casting a SKILLED attack spell, you can choose the basic or skilled effect.",
            "You get a 100 turn reminder for spells that are close to fading away.",
            "Objects can be completely destroyed via rusting/rotting/corroding.",
            "In NerfHack - amulets, rings, wands, and tools are now erodeable.",
            "In NerfHack, even silver items can corrode.",
            "Poison gas clouds can rot organic armor.",
            "Item erosion can be repaired by dipping into a potion of restore ability.",
            "Scrolls may disintegrate when dipped into water.",
            "Greased items can't be disarmed with a bullwhip and they are harder to steal.",
            "Towels can be (a)pplied to remove grease from specific objects.",
            "With Glib hands, you'll drop any item you try to apply (except a towel).",
            "Grease can be washed off towels by wetting them.",
            "Greased towels now operate the same way that cursed towels do.",
            "All piercers can actually pierce metal helmets now!" ,
            "Baby dragons have dangerous bites now.",
            "Make sure monsters don't sandwich and flank you, they get a large advantage if they do.",
            "You can use your pets to flank monsters, gaining a significant advantage to-hit.",
            "Some monsters can turn berserk in NerfHack, if they do watch out...",
            "When a monster goes berserk it can instantly regenerate a large portion of HP.",
            "When berserking, monsters can't be scared, won't flee, and will always come for you.",
            "Watch out - A berserking monster deals double damage rolls when attacking!",
            "Cave dwellers cannot have skills in edged or pointy weapons unrestricted.",
            "Cavepersons' gods sometimes don't respond to prayer.",
            "Cavepeople can lash flint to arrows, making them more dangerous ([a]pply them).",
            "Cavepeople are quite bad at learning spells - they don't even have a special spell!",
            "Illiterate cavedwellers get an HP boost for each level they gain.",
            "Disclaimer: Only lawful knights can dip for Excalibur.",
            "Priests cannot have edged weapon skills unrestricted.",
            "Priests always receive Mjollnir as their crowning gift.",
            "Priests reduce the chance of zombie revival by 50%.",
            "Rogues can inflict backstab damage for the first thrown weapon.",
            "Rogues get bonus backstab damage when using stilettos.",
            "Rogues also get a multishot bonus for knives.",
            "Rogues can get counterattacks in while wielding knives or daggers.",
            "Rangers get auto-id for launchers when they reach XP level 7.",
            "Rangers get auto-id for ammo enchantment when they reach XP level 10.",
            "Rangers are not stunned from using portals (they are used to quick travel).",
            "Samurai get to-hit and damage bonuses for twoweaponing a katana with a wakizashi.",
            "Tourists get automatic type identification for shop items.",
            "No player-race starts with infravision anymore.",
            "Elves get see invisible at level 8.",
            "Gnomes start with an expanded nightvision radius.",
            "Gnomes get stealth at level 5.",
            "Rocks can be broken (a)pplied to produce flint stones.",
            "Flint stones can be applied to iron objects, producing frightening sparks.",
            "Scrolls of light are much more effective at lighting.",
            "Mud boots provide protection from wrapping attacks.",
            "Hiking boots let you avoid pit traps.",
            "Hiking boots provide extra carrying capacity.",
            "Fencing gloves grant a to-hit bonus when attacking with a free off-hand.",
            "Old gloves don't take erosion damage.",
            "Padded gloves provide an extra point of AC.",
            "Combat boots provide extra AC and a to-hit bonus.",
            "Jungle boots provide protection from wounded legs.",
            "Gauntlets of dexterity grant a to-hit bonus while using bows.",
            "Any slashing or piercing weapons can now be poisoned.",
            "Wielded polearms grant a 2AC bonus.",
            "Spears at expert skill can skewer through enemies.",
            "Spetums can skewer up to 3 monsters in melee while riding a steed.",
            "Ranseurs can disarm monsters or the player in melee while riding a steed or pounding.",
            "Bardiches have a 1 in 100 chance of beheading monsters (or the player).",
            "+4 to-hit bonus for attacking with a scimitar on a steed.",
            "Wielding and unwielding curved swords takes 0 turns.",
            "Morning stars and flails can stun monsters when you are skilled or better.",
            "Rocks and flint receive a powerful strength bonus when using slings.",
            "Gem class projectiles do minimal damage vs thick-skinned monsters.",
            "Slings have the potential to insta-kill giants.",
            "Know this! Wands of wishing always generate pre-charged.",
            "Unicorn horn success depends on it's enchantment, unicorn horn skill helps too!",
            "war hammers have been changed into a stronger two-handed weapon.",
            "Blessed scrolls of genocide only clear a single monster species in the dungeon.",
            "Uncursed scrolls of genocide only clear a single monster species on the level.",
            "Monsters cannot be fully genocided after entering the planes.",
            "Disclaimer: Confused scrolls of gold detection no longer detect magic portals.",
            "Confused scroll of identify grant enlightenment.",
            "Cursed wands have a much higher chance of exploding.",
            "Beware! Cursed wands have a very high chance of backfiring.",
            "Blessed wands wrest much faster than uncursed wands, which wrest faster than cursed wands.",
            "Stomping boots instakill any tiny monsters you run into.",
            "Levitation boots have been replaced with flying boots.",
            "Gauntlets of force act like rings of increase damage.",
            "Gauntlets of force let you #force things easily.",
            "Gauntlets of force can bust through iron bars and boulders.",
            "A scythe is the only polearm that can be used in melee (without riding).",
            "The Tsurugi of Muramasa has a 10% chance of bisection.",
            "Magicbane is now a quarterstaff.",
            "Fire Brand instakills highly flammable monsters and green slimes.",
            "Frost Brand instakills water elementals.",
            "Vorpal blade grants see invisible while wielded.",
            "Vorpal blade gets a 10% chance of beheading.",
            "The Heart of Ahriman now grants slotless flying and displacement instead of stealth.",
            "Trollsbane grants regeneration while wielded.",
            "Giantslayer conveys max strength while wielded.",
            "Werebane provides protection from shapechangers when wielded.",
            "The Sceptre of Might gets a flat +3 damage buff.",
            "The Longbow of Diana confers reduced damage when wielded.",
            "Mjollnir can be invoked for a lightning bolt.",
            "All artifact banes provide warning vs their bane monster type when wielded.",
            "All artifact banes can instakill their associated monster types.",
            "The drawbridge passtune range has been expanded by one square.",
            "The drawbridge does not always close with the passtune.",
            "Player can't regenerate hit points while in the Valley of the Dead.",
            "Monsters are never generated peaceful in Sokoban.",
            "Cursed gain level can be used in Sokoban to bypass a floor.",
            "You can dip metallic items into forges to repair them.",
            "You can remove punishment at a forge if you have a hammer...",
            "You can dispose of zombie corpses in a forge.",
            "You can bless metallic items in a forge if you have high luck.",
            "You get a one-time erodeproofing from forges.",
            "Door traps can actually explode in a ball of fire.",
            "Beware: Randomly found tins are capable of being booby trapped.",
            "Crowning gifts will never be granted from regular #offers - only from crowning."
    };

    return hint[rn2(SIZE(hint))];
}

/*mail.c*/
