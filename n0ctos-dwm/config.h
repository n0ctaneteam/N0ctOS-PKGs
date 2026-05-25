/* =========================================================
 * n0ctos — dwm config.h
 * live ISO build
 * ========================================================= */

/* ---------------------------------------------------------
 * APPEARANCE
 * --------------------------------------------------------- */

/* window border thickness in pixels */
static const unsigned int borderpx  = 2;

/* snap distance when moving windows near screen edge (px) */
static const unsigned int snap      = 16;

/* 1 = show bar, 0 = hide bar */
static const int showbar            = 1;

/* 1 = bar at top, 0 = bar at bottom */
static const int topbar             = 1;

/* fonts — change to any fc-list font name */
static const char *fonts[]    = { "JetBrainsMono Nerd Font Propo:size=13" };
static const char dmenufont[] = "JetBrainsMono Nerd Font Propo:size=13";

/* ---------------------------------------------------------
 * COLORS
 * change hex values to theme as you like
 * --------------------------------------------------------- */

static const char col_bg[]      = "#0a071f";  /* bar background            */
static const char col_fg[]      = "#dce6ff";  /* normal text               */
static const char col_border[]  = "#10021a";  /* inactive window border    */
static const char col_selbg[]   = "#13a5b0";  /* selected bg + border      */
static const char col_selborder[]   = "#13a5b0";  /* selected bg + border      */
static const char col_selfg[]   = "#11010f";  /* selected text             */

static const char *colors[][3] = {
    /*               fg          bg          border      */
    [SchemeNorm] = { col_fg,    col_bg,     col_border  },
    [SchemeSel]  = { col_selfg, col_selbg,  col_selborder  },
};

/* ---------------------------------------------------------
 * TAGS
 * rename these to anything you want e.g. "www" "term" etc
 * --------------------------------------------------------- */

static const char *tags[] = { "1", "2", "3", "4", "5" };

/* ---------------------------------------------------------
 * WINDOW RULES
 * force specific apps to a tag or floating mode
 * xprop | grep WM_CLASS  — to find class name of any app
 *
 * tags mask: 1<<0 = tag1, 1<<1 = tag2, 1<<2 = tag3 ...
 * isfloating: 1 = floating, 0 = tiled
 * monitor: -1 = current monitor
 * --------------------------------------------------------- */

static const Rule rules[] = {
    /* class          instance   title   tags mask   isfloating  monitor */
    { "calamares",    NULL,      NULL,   1 << 1,     0,          -1 },  /* installer on tag 2 */
    { "st",           NULL,      NULL,   1 << 0,     0,          -1 },  /* terminal on tag 1  */
};

/* ---------------------------------------------------------
 * LAYOUTS
 * --------------------------------------------------------- */

/* master area width ratio — 0.55 = master takes 55% of screen */
static const float mfact        = 0.55;

/* number of windows in master area */
static const int nmaster        = 1;

/* 0 = ignore app size hints (cleaner tiling, recommended) */
static const int resizehints    = 0;

/* 1 = keep fullscreen windows focused */
static const int lockfullscreen = 1;

static const Layout layouts[] = {
    /* symbol   function                                          */
    { "[]=",    tile    },   /* [0] default: master + stack tiling */
    { "[M]",    monocle },   /* [1] monocle: one window fullscreen  */
    { "><>",    NULL    },   /* [2] floating: free placement         */
};

/* ---------------------------------------------------------
 * KEYBINDINGS
 * MODKEY = Super (Win key)
 * --------------------------------------------------------- */

#define MODKEY Mod4Mask

/* helper macro for tag keybinds */
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY, view,       {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY, toggleview, {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY, tag,        {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY, toggletag,  {.ui = 1 << TAG} },

/* run shell commands */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

/* ---------------------------------------------------------
 * COMMANDS
 * change terminal, launcher, scripts here
 * --------------------------------------------------------- */

static char dmenumon[2]           = "0";

/* dmenu launch command */
static const char *dmenucmd[]     = {
    "dmenu_run",
    "-m",  dmenumon,
    "-fn", dmenufont,
    "-nb", col_bg,    "-nf", col_fg,
    "-sb", col_selbg, "-sf", col_selfg,
    NULL
};

/* terminal — st with zsh */
static const char *termcmd[]      = { "st", "-e", "zsh", NULL };

/* calamares installer */
static const char *calamarescmd[] = { "calamares", NULL };

/* welcome TUI script */
static const char *welcomecmd[]   = { "st", "-e", "/usr/local/bin/welcome.sh", NULL };

/* ---------------------------------------------------------
 * KEY BINDINGS TABLE
 * --------------------------------------------------------- */

static const Key keys[] = {
    /* modifier              key            function         argument */

    /* ── launchers ──────────────────────────────────────── */
    { MODKEY,                XK_Return,     spawn,           {.v = termcmd}      },  /* open terminal        */
    { MODKEY,                XK_d,          spawn,           {.v = dmenucmd}     },  /* dmenu launcher       */
    { MODKEY,                XK_w,          spawn,           {.v = welcomecmd}   },  /* welcome TUI          */
    { MODKEY,                XK_i,          spawn,           {.v = calamarescmd} },  /* calamares installer  */

    /* ── bar ────────────────────────────────────────────── */
    { MODKEY,                XK_b,          togglebar,       {0}                 },  /* toggle bar           */

    /* ── focus navigation — vim ─────────────────────────── */
    { MODKEY,                XK_j,          focusstack,      {.i = +1}           },  /* focus next window    */
    { MODKEY,                XK_k,          focusstack,      {.i = -1}           },  /* focus prev window    */

    /* ── focus navigation — arrow keys ──────────────────── */
    { MODKEY,                XK_Down,       focusstack,      {.i = +1}           },  /* focus next window    */
    { MODKEY,                XK_Up,         focusstack,      {.i = -1}           },  /* focus prev window    */

    /* ── master resize — vim ────────────────────────────── */
    { MODKEY,                XK_h,          setmfact,        {.f = -0.05}        },  /* shrink master        */
    { MODKEY,                XK_l,          setmfact,        {.f = +0.05}        },  /* grow master          */

    /* ── master resize — arrow keys ─────────────────────── */
    { MODKEY,                XK_Left,       setmfact,        {.f = -0.05}        },  /* shrink master        */
    { MODKEY,                XK_Right,      setmfact,        {.f = +0.05}        },  /* grow master          */

    /* ── master area ────────────────────────────────────── */
    { MODKEY,                XK_equal,      incnmaster,      {.i = +1}           },  /* add window to master */
    { MODKEY,                XK_minus,      incnmaster,      {.i = -1}           },  /* remove from master   */
    { MODKEY|ShiftMask,      XK_Return,     zoom,            {0}                 },  /* swap to master       */

    /* ── close window ───────────────────────────────────── */
    { MODKEY|ShiftMask,      XK_c,          killclient,      {0}                 },  /* close focused window */

    /* ── layouts ────────────────────────────────────────── */
    { MODKEY,                XK_t,          setlayout,       {.v = &layouts[0]}  },  /* tiling               */
    { MODKEY,                XK_m,          setlayout,       {.v = &layouts[1]}  },  /* monocle              */
    { MODKEY,                XK_f,          setlayout,       {.v = &layouts[2]}  },  /* floating             */
    { MODKEY|ShiftMask,      XK_space,      togglefloating,  {0}                 },  /* toggle float focused */

    /* ── tags 1–5 ───────────────────────────────────────── */
    TAGKEYS(XK_1, 0)
    TAGKEYS(XK_2, 1)
    TAGKEYS(XK_3, 2)
    TAGKEYS(XK_4, 3)
    TAGKEYS(XK_5, 4)

    /* ── quit ───────────────────────────────────────────── */
    { MODKEY|ShiftMask,      XK_q,          quit,            {0}                 },  /* quit dwm             */
};

/* ---------------------------------------------------------
 * MOUSE BINDINGS
 * --------------------------------------------------------- */

static const Button buttons[] = {
    /* click          event mask   button    function         argument           */
    { ClkLtSymbol,    0,           Button1,  setlayout,       {0}                },  /* cycle layout         */
    { ClkLtSymbol,    0,           Button3,  setlayout,       {.v = &layouts[2]} },  /* set float layout     */
    { ClkWinTitle,    0,           Button2,  zoom,            {0}                },  /* middle click = master*/
    { ClkClientWin,   MODKEY,      Button1,  movemouse,       {0}                },  /* super+drag = move    */
    { ClkClientWin,   MODKEY,      Button2,  togglefloating,  {0}                },  /* super+mid = float    */
    { ClkClientWin,   MODKEY,      Button3,  resizemouse,     {0}                },  /* super+rclick = resize*/
    { ClkTagBar,      0,           Button1,  view,            {0}                },  /* click tag            */
    { ClkTagBar,      0,           Button3,  toggleview,      {0}                },  /* right click tag      */
    { ClkTagBar,      MODKEY,      Button1,  tag,             {0}                },  /* move win to tag      */
    { ClkTagBar,      MODKEY,      Button3,  toggletag,       {0}                },  /* toggle win on tag    */
};