/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int user_bh            = 5;        /* 0 means auto.*/
static const int und_bh             = 2;        /* underline height */
static const char *fonts[]          = { "SourceCodeVF:style=Semibold:size=10" };
static char normbgcolor[]           = "#222222";
static char normbordercolor[]       = "#444444";
static char normfgcolor[]           = "#bbbbbb";
static char selfgcolor[]            = "#eeeeee";
static char selbordercolor[]        = "#005577";
static char selbgcolor[]            = "#005577";
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const char *const autostart[] = {
	"startupscript", NULL,
	NULL /* terminate */
};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.5; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[ ]=",      tile },    /* first entry is default */
/*{ "><>",      NULL },    no layout function means floating behavior */
	{ "[M]=",      monocle },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* signal definitions */
static Signal signals[] = {
	/* signum       function        argument  */
	{ 1,            xrdb,      {.v = NULL} },
};

/* commands */
static const char *launcher[]  = { "launcher", NULL };
static const char *quickinfo[]  = { "quickinfo", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *filemanager[]  = { "st", "-e", "lf-ub", NULL };
static const char *powermenu[]  = { "powermenu", NULL };
static const char *screenshot[] = { "flameshot", "screen", NULL };
static const char *screenshotl[] = { "flameshot", "launcher", NULL };
static const char *upvol[]   = { "audioctrl", "ainc", NULL };
static const char *downvol[] = { "audioctrl", "adec", NULL };
static const char *toggvol[] = { "audioctrl", "atogg", NULL };
static const char *brightnessup[] = { "brightnessctrl", "binc", NULL };
static const char *brightnessdown[] = { "brightnessctrl", "bdec", NULL };

static const Key keys[] = {
	/* modifier                     key                        function        argument */
	{ MODKEY,                       XK_p,                      spawn,          {.v = launcher } },
	{ MODKEY|ShiftMask,             XK_Return,                 spawn,          {.v = termcmd } },
  { MODKEY,                       XK_Print,                  spawn,          {.v = screenshotl } },
  { MODKEY|ShiftMask,             XK_i,                      spawn,          {.v = quickinfo } },
  { MODKEY|ShiftMask,             XK_l,                      spawn,          {.v = filemanager } },
  { 0,                            XK_Print,                  spawn,          {.v = screenshot } },
  { 0,                            XF86XK_AudioLowerVolume,   spawn,          {.v = downvol } },
  { 0,                            XF86XK_AudioMute,          spawn,          {.v = toggvol } },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn,          {.v = upvol   } },
  { 0,                            XF86XK_MonBrightnessUp,    spawn,          {.v = brightnessup } },
  { 0,                            XF86XK_MonBrightnessDown,  spawn,          {.v = brightnessdown } },
  { MODKEY,                       XK_Up,                     viewnext,       {0} },
  { MODKEY,                       XK_Down,                   viewprev,       {0} },
  { MODKEY,                       XK_Right,                  viewnextnovacant,    {0} },
  { MODKEY,                       XK_Left,                   viewprevnovacant,    {0} },
	{ MODKEY,                       XK_b,                      togglebar,      {0} },
	{ MODKEY,                       XK_Tab,                    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,                      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,                      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,                      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,                      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,                      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,                      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,                 zoom,           {0} },
	{ MODKEY,                       XK_a,                      view,           {0} },
	{ MODKEY,                       XK_q,                      killclient,     {0} },
	{ MODKEY,		                    XK_space,                  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_space,                  cyclelayout,    {.i = -1 } },
	{ MODKEY,                       XK_f,                      togglefloating, {0} },
	{ MODKEY,                       XK_0,                      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,                      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,                 focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,                 tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,                      spawn,          {.v = powermenu} },
  { MODKEY,                       XK_Escape,                 quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
};
