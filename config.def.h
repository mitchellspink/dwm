/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int gappx     			= 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Cascadia Code:size=10", "Cascadia Cove Nerd Font:size=10" };
static const char dmenufont[]       = "Cascadia Code:size=10";
static const char col_gray1[]       = "#1d2021";	/* Background Color  */
static const char col_gray2[]       = "#928374";	/* Inactive Window Border Color  */
static const char col_gray3[]       = "#fbf1c7";	/* Font Color  */
static const char col_gray4[]       = "#fbf1c7";	/* Current Tag and Current Window Font Color  */
static const char col_cyan[]        = "#fb4934";	/* Top Bar Second Color (Blue) And Active Window Border Color  */
static const unsigned int baralpha = 0.5;	/* Default - 0xd0 */
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

static const char *const autostart[] = {
	"picom", NULL,
	"hsetroot", "-cover", "/home/mitchell/.wallpapers/001.jpg", NULL,
	"slstatus", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { " WEB ", " CODE ", " DISCORD ", " SPOTIFY ", " ZOOM " };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class            instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    		NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Arandr",    		NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Pcmanfm",    	NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Lxappearance",   NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Pavucontrol",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Nitrogen",    	NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "zoom", 			NULL,     NULL,           1 << 4,    0,          0,          -1,        -1 },
	{ "discord", 		NULL,     NULL,           1 << 2,    0,          0,          -1,        -1 },
	{ "Spotify", 		NULL,     NULL,           1 << 3,    0,          0,          -1,        -1 },
	{ "Firefox", 		NULL,     NULL,           1 << 0,    0,          0,          -1,        -1 },
	{ "Brave", 			NULL,     NULL,           1 << 0,    0,          0,          -1,        -1 },
	{ "st-256color",    NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      		NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "[D]",      deck },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *slockcmd[]  				= { "slock", NULL };
static const char *browsercmd[]  			= { "brave", NULL };
static const char *pavucmd[]  				= { "pavucontrol", NULL };
static const char *upvol[]   				= { "pamixer", "--allow-boost", "-i", "5",     NULL };
static const char *downvol[] 				= { "pamixer", "--allow-boost", "-d", "5",     NULL };
static const char *mutevol[] 				= { "pamixer", "-t",  NULL };

#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_l,      spawn,          {.v = slockcmd } },
	{ MODKEY,                       XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_a,      spawn,          {.v = pavucmd } },

	/* Close Focused Window */
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },

	/* Toggle Bar */
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },

	/* Window Focus */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },

	/* Window Sizing */
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },

	/* Increase/Decrease Windows in Master */
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },

	/* Move Focused Window to Master */
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },

	/* Switch Between the Two Previous Tags */
	{ MODKEY,                       XK_Tab,    view,           {0} },

	/* Layouts */
	{ MODKEY|ControlMask,           XK_t,      setlayout,      {.v = &layouts[0]} },	/* Tile */
	{ MODKEY|ControlMask,           XK_f,      setlayout,      {.v = &layouts[1]} },	/* Floating */
	{ MODKEY|ControlMask,           XK_m,      setlayout,      {.v = &layouts[2]} },	/* Monocle */
	{ MODKEY|ControlMask,           XK_d,      setlayout,      {.v = &layouts[3]} },	/* Deck */

	/* Toggle Tile/Float Layout */
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	/* Toggle Focused Window Tile/Float Layout */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },

	/* View All Open Windows */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },

	/* Move Focused Window to All Tags */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	/* Multiple Monitors */
	{ MODKEY|ControlMask,           XK_comma,  focusmon,       {.i = -1 } },	/* focus previous */
	{ MODKEY|ControlMask,           XK_period, focusmon,       {.i = +1 } },	/* focus next */
	{ MODKEY|ControlMask|ShiftMask, XK_comma,  tagmon,         {.i = -1 } },	/* move window to previous */
	{ MODKEY|ControlMask|ShiftMask, XK_period, tagmon,         {.i = +1 } },	/* move window to next */

	/* PulseAudio */
	{ MODKEY,                       XK_F11,    spawn,          {.v = upvol   } },
	{ MODKEY,                       XK_F10,    spawn,          {.v = downvol } },
	{ MODKEY,                       XK_F9,     spawn,          {.v = mutevol } },

	/* Shiftview */
	{ MODKEY,                       XK_comma,  shiftview,      { .i = -1 } },
	{ MODKEY,                       XK_period, shiftview,      { .i = +1 } },

	/* Gaps */
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = 0  } },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	/* Quit DWM */
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

