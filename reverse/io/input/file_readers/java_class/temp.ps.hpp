%!PS-Adobe-3.0
%%BoundingBox: 24 24 571 818
%%Title: Enscript Output
%%For: 
%%Creator: GNU enscript 1.6.4
%%CreationDate: Mon Feb 19 13:31:00 2007
%%Orientation: Landscape
%%Pages: (atend)
%%DocumentMedia: A4 595 842 0 () ()
%%DocumentNeededResources: (atend)
%%EndComments
%%BeginProlog
%%BeginResource: procset Enscript-Prolog 1.6 4
%
% Procedures.
%

/_S {	% save current state
  /_s save def
} def
/_R {	% restore from saved state
  _s restore
} def

/S {	% showpage protecting gstate
  gsave
  showpage
  grestore
} bind def

/MF {	% fontname newfontname -> -	make a new encoded font
  /newfontname exch def
  /fontname exch def

  /fontdict fontname findfont def
  /newfont fontdict maxlength dict def

  fontdict {
    exch
    dup /FID eq {
      % skip FID pair
      pop pop
    } {
      % copy to the new font dictionary
      exch newfont 3 1 roll put
    } ifelse
  } forall

  newfont /FontName newfontname put

  % insert only valid encoding vectors
  encoding_vector length 256 eq {
    newfont /Encoding encoding_vector put
  } if

  newfontname newfont definefont pop
} def

/MF_PS { % fontname newfontname -> -	make a new font preserving its enc
  /newfontname exch def
  /fontname exch def

  /fontdict fontname findfont def
  /newfont fontdict maxlength dict def

  fontdict {
    exch
    dup /FID eq {
      % skip FID pair
      pop pop
    } {
      % copy to the new font dictionary
      exch newfont 3 1 roll put
    } ifelse
  } forall

  newfont /FontName newfontname put

  newfontname newfont definefont pop
} def

/SF { % fontname width height -> -	set a new font
  /height exch def
  /width exch def

  findfont
  [width 0 0 height 0 0] makefont setfont
} def

/SUF { % fontname width height -> -	set a new user font
  /height exch def
  /width exch def

  /F-gs-user-font MF
  /F-gs-user-font width height SF
} def

/SUF_PS { % fontname width height -> -	set a new user font preserving its enc
  /height exch def
  /width exch def

  /F-gs-user-font MF_PS
  /F-gs-user-font width height SF
} def

/M {moveto} bind def
/s {show} bind def

/Box {	% x y w h -> -			define box path
  /d_h exch def /d_w exch def /d_y exch def /d_x exch def
  d_x d_y  moveto
  d_w 0 rlineto
  0 d_h rlineto
  d_w neg 0 rlineto
  closepath
} def

/bgs {	% x y height blskip gray str -> -	show string with bg color
  /str exch def
  /gray exch def
  /blskip exch def
  /height exch def
  /y exch def
  /x exch def

  gsave
    x y blskip sub str stringwidth pop height Box
    gray setgray
    fill
  grestore
  x y M str s
} def

/bgcs { % x y height blskip red green blue str -> -  show string with bg color
  /str exch def
  /blue exch def
  /green exch def
  /red exch def
  /blskip exch def
  /height exch def
  /y exch def
  /x exch def

  gsave
    x y blskip sub str stringwidth pop height Box
    red green blue setrgbcolor
    fill
  grestore
  x y M str s
} def

% Highlight bars.
/highlight_bars {	% nlines lineheight output_y_margin gray -> -
  gsave
    setgray
    /ymarg exch def
    /lineheight exch def
    /nlines exch def

    % This 2 is just a magic number to sync highlight lines to text.
    0 d_header_y ymarg sub 2 sub translate

    /cw d_output_w cols div def
    /nrows d_output_h ymarg 2 mul sub lineheight div cvi def

    % for each column
    0 1 cols 1 sub {
      cw mul /xp exch def

      % for each rows
      0 1 nrows 1 sub {
        /rn exch def
        rn lineheight mul neg /yp exch def
        rn nlines idiv 2 mod 0 eq {
	  % Draw highlight bar.  4 is just a magic indentation.
	  xp 4 add yp cw 8 sub lineheight neg Box fill
	} if
      } for
    } for

  grestore
} def

% Line highlight bar.
/line_highlight {	% x y width height gray -> -
  gsave
    /gray exch def
    Box gray setgray fill
  grestore
} def

% Column separator lines.
/column_lines {
  gsave
    .1 setlinewidth
    0 d_footer_h translate
    /cw d_output_w cols div def
    1 1 cols 1 sub {
      cw mul 0 moveto
      0 d_output_h rlineto stroke
    } for
  grestore
} def

% Column borders.
/column_borders {
  gsave
    .1 setlinewidth
    0 d_footer_h moveto
    0 d_output_h rlineto
    d_output_w 0 rlineto
    0 d_output_h neg rlineto
    closepath stroke
  grestore
} def

% Do the actual underlay drawing
/draw_underlay {
  ul_style 0 eq {
    ul_str true charpath stroke
  } {
    ul_str show
  } ifelse
} def

% Underlay
/underlay {	% - -> -
  gsave
    0 d_page_h translate
    d_page_h neg d_page_w atan rotate

    ul_gray setgray
    ul_font setfont
    /dw d_page_h dup mul d_page_w dup mul add sqrt def
    ul_str stringwidth pop dw exch sub 2 div ul_h_ptsize -2 div moveto
    draw_underlay
  grestore
} def

/user_underlay {	% - -> -
  gsave
    ul_x ul_y translate
    ul_angle rotate
    ul_gray setgray
    ul_font setfont
    0 0 ul_h_ptsize 2 div sub moveto
    draw_underlay
  grestore
} def

% Page prefeed
/page_prefeed {		% bool -> -
  statusdict /prefeed known {
    statusdict exch /prefeed exch put
  } {
    pop
  } ifelse
} def

% Wrapped line markers
/wrapped_line_mark {	% x y charwith charheight type -> -
  /type exch def
  /h exch def
  /w exch def
  /y exch def
  /x exch def

  type 2 eq {
    % Black boxes (like TeX does)
    gsave
      0 setlinewidth
      x w 4 div add y M
      0 h rlineto w 2 div 0 rlineto 0 h neg rlineto
      closepath fill
    grestore
  } {
    type 3 eq {
      % Small arrows
      gsave
        .2 setlinewidth
        x w 2 div add y h 2 div add M
        w 4 div 0 rlineto
        x w 4 div add y lineto stroke

        x w 4 div add w 8 div add y h 4 div add M
        x w 4 div add y lineto
	w 4 div h 8 div rlineto stroke
      grestore
    } {
      % do nothing
    } ifelse
  } ifelse
} def

% EPSF import.

/BeginEPSF {
  /b4_Inc_state save def    		% Save state for cleanup
  /dict_count countdictstack def	% Count objects on dict stack
  /op_count count 1 sub def		% Count objects on operand stack
  userdict begin
  /showpage { } def
  0 setgray 0 setlinecap
  1 setlinewidth 0 setlinejoin
  10 setmiterlimit [ ] 0 setdash newpath
  /languagelevel where {
    pop languagelevel
    1 ne {
      false setstrokeadjust false setoverprint
    } if
  } if
} bind def

/EndEPSF {
  count op_count sub { pos } repeat	% Clean up stacks
  countdictstack dict_count sub { end } repeat
  b4_Inc_state restore
} bind def

% Check PostScript language level.
/languagelevel where {
  pop /gs_languagelevel languagelevel def
} {
  /gs_languagelevel 1 def
} ifelse
%%EndResource
%%BeginResource: procset Enscript-Encoding-88591 1.6 4
/encoding_vector [
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/space        	/exclam       	/quotedbl     	/numbersign   	
/dollar       	/percent      	/ampersand    	/quoteright   	
/parenleft    	/parenright   	/asterisk     	/plus         	
/comma        	/hyphen       	/period       	/slash        	
/zero         	/one          	/two          	/three        	
/four         	/five         	/six          	/seven        	
/eight        	/nine         	/colon        	/semicolon    	
/less         	/equal        	/greater      	/question     	
/at           	/A            	/B            	/C            	
/D            	/E            	/F            	/G            	
/H            	/I            	/J            	/K            	
/L            	/M            	/N            	/O            	
/P            	/Q            	/R            	/S            	
/T            	/U            	/V            	/W            	
/X            	/Y            	/Z            	/bracketleft  	
/backslash    	/bracketright 	/asciicircum  	/underscore   	
/quoteleft    	/a            	/b            	/c            	
/d            	/e            	/f            	/g            	
/h            	/i            	/j            	/k            	
/l            	/m            	/n            	/o            	
/p            	/q            	/r            	/s            	
/t            	/u            	/v            	/w            	
/x            	/y            	/z            	/braceleft    	
/bar          	/braceright   	/tilde        	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/.notdef      	/.notdef      	/.notdef      	/.notdef      	
/space        	/exclamdown   	/cent         	/sterling     	
/currency     	/yen          	/brokenbar    	/section      	
/dieresis     	/copyright    	/ordfeminine  	/guillemotleft	
/logicalnot   	/hyphen       	/registered   	/macron       	
/degree       	/plusminus    	/twosuperior  	/threesuperior	
/acute        	/mu           	/paragraph    	/bullet       	
/cedilla      	/onesuperior  	/ordmasculine 	/guillemotright	
/onequarter   	/onehalf      	/threequarters	/questiondown 	
/Agrave       	/Aacute       	/Acircumflex  	/Atilde       	
/Adieresis    	/Aring        	/AE           	/Ccedilla     	
/Egrave       	/Eacute       	/Ecircumflex  	/Edieresis    	
/Igrave       	/Iacute       	/Icircumflex  	/Idieresis    	
/Eth          	/Ntilde       	/Ograve       	/Oacute       	
/Ocircumflex  	/Otilde       	/Odieresis    	/multiply     	
/Oslash       	/Ugrave       	/Uacute       	/Ucircumflex  	
/Udieresis    	/Yacute       	/Thorn        	/germandbls   	
/agrave       	/aacute       	/acircumflex  	/atilde       	
/adieresis    	/aring        	/ae           	/ccedilla     	
/egrave       	/eacute       	/ecircumflex  	/edieresis    	
/igrave       	/iacute       	/icircumflex  	/idieresis    	
/eth          	/ntilde       	/ograve       	/oacute       	
/ocircumflex  	/otilde       	/odieresis    	/divide       	
/oslash       	/ugrave       	/uacute       	/ucircumflex  	
/udieresis    	/yacute       	/thorn        	/ydieresis    	
] def
%%EndResource
%%EndProlog
%%BeginSetup
%%IncludeResource: font Courier-Bold
%%IncludeResource: font Courier
/HFpt_w 10 def
/HFpt_h 10 def
/Courier-Bold /HF-gs-font MF
/HF /HF-gs-font findfont [HFpt_w 0 0 HFpt_h 0 0] makefont def
/Courier /F-gs-font MF
/F-gs-font 7 7 SF
/#copies 1 def
% Pagedevice definitions:
gs_languagelevel 1 gt {
  <<
    /PageSize [595 842] 
  >> setpagedevice
} if
%%BeginResource: procset Enscript-Header-enscript 1.6 4
%%IncludeResource: font Times-Bold
%%IncludeResource: font Times-Roman

% Fonts.
/Times-Bold /HeaderFont-Bold MF
/HeaderDateF /HeaderFont-Bold findfont 12 scalefont def

/Times-Roman /HeaderFont-Times MF
/HeaderHDRF /HeaderFont-Times findfont 14 scalefont def

/HeaderPageNumF /Helvetica-Bold findfont 28.8 scalefont def

/do_header {	% print enscript header
  gsave
    d_header_x d_header_y translate

    % light bar
    0 0 d_header_w d_header_h 2 div Box
    .95 setgray fill

    % dark gray boxes
    /dbw d_header_h 2 mul def	% dark box width
    /dbc .7 def			% dark box color

    % left dark box.
    0 0 dbw d_header_h Box
    dbc setgray fill

    0 setgray 
    HeaderDateF setfont
    moddatestr dup stringwidth pop dbw exch sub 2 div 
    d_header_h 2 div 2 add moveto show
    modtimestr dup stringwidth pop dbw exch sub 2 div 
    d_header_h 5 div moveto show

    % right dark box
    d_header_w dbw sub 0 dbw d_header_h Box
    dbc setgray fill

    HeaderPageNumF setfont
    1 setgray
    pagenumstr dup
    stringwidth pop dbw exch sub 2 div d_header_w dbw sub add
    d_header_h .2 mul moveto show

    % filename
    0 setgray 
    HeaderHDRF setfont
    d_header_w fname stringwidth pop sub 2 div d_header_h 8 div moveto
    fname show

    % user supplied header string.
    user_header_p {
      /h d_header_h 8 div 5 mul def

      % Implement strict enscript compatibility.
      user_header_center_str () eq user_header_right_str () eq and {
        d_header_w user_header_left_str stringwidth pop sub 2 div 
        h moveto user_header_left_str show
      } {
        dbw 5 add h moveto user_header_left_str show

        d_header_w user_header_center_str stringwidth pop sub 2 div 
        h moveto user_header_center_str show

	d_header_w dbw sub 5 sub user_header_right_str stringwidth pop
	sub h moveto user_header_right_str show
      } ifelse
    } if

  grestore
} def
%%EndResource
/d_page_w 794 def
/d_page_h 547 def
/d_header_x 0 def
/d_header_y 511 def
/d_header_w 794 def
/d_header_h 36 def
/d_footer_x 0 def
/d_footer_y 0 def
/d_footer_w 794 def
/d_footer_h 0 def
/d_output_w 794 def
/d_output_h 511 def
/cols 2 def
%%EndSetup
%%Page: (1) 1
%%BeginPageSetup
_S
90 rotate
24 -571 translate
/pagenum 1 def
/fname (Class_Access_Flags.cpp) def
/fdir () def
/ftail (Class_Access_Flags.cpp) def
% User defined strings:
/pagenumstr (1) def
/moddatestr (02/19/07) def
/modtimestr (13:16:53) def
/user_header_p false def
/user_footer_p false def
%%EndPageSetup
column_lines
do_header
5 501 M
(#) s
/Courier-Bold 7 7 SUF
9.2 501 M
(include) s
/F-gs-font 7 7 SF
38.6 501 M
( ) s
/Courier-Bold 7 7 SUF
42.8 501 M
("Class_Access_Flags.h") s
/F-gs-font 7 7 SF
5 493 M
(#) s
/Courier-Bold 7 7 SUF
9.2 493 M
(include) s
/F-gs-font 7 7 SF
38.6 493 M
( ) s
/Courier-Bold 7 7 SUF
42.8 493 M
("Class_Access_Flags_Rules.h") s
/F-gs-font 7 7 SF
5 485 M
(#) s
/Courier-Bold 7 7 SUF
9.2 485 M
(include) s
/F-gs-font 7 7 SF
38.6 485 M
( ) s
/Courier-Bold 7 7 SUF
42.8 485 M
(<sstream>) s
/F-gs-font 7 7 SF
5 469 M
(namespace reverse { namespace java_module {) s
5 453 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 453 M
(boost) s
/F-gs-font 7 7 SF
42.8 453 M
(::uint16_t ) s
/Courier-Bold 7 7 SUF
89 453 M
(const) s
/F-gs-font 7 7 SF
110 453 M
( Class_Access_Flags::ACC_PUBLIC    = 0x0001;) s
5 445 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 445 M
(boost) s
/F-gs-font 7 7 SF
42.8 445 M
(::uint16_t ) s
/Courier-Bold 7 7 SUF
89 445 M
(const) s
/F-gs-font 7 7 SF
110 445 M
( Class_Access_Flags::ACC_FINAL     = 0x0010;) s
5 437 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 437 M
(boost) s
/F-gs-font 7 7 SF
42.8 437 M
(::uint16_t ) s
/Courier-Bold 7 7 SUF
89 437 M
(const) s
/F-gs-font 7 7 SF
110 437 M
( Class_Access_Flags::ACC_SUPER     = 0x0020;) s
5 429 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 429 M
(boost) s
/F-gs-font 7 7 SF
42.8 429 M
(::uint16_t ) s
/Courier-Bold 7 7 SUF
89 429 M
(const) s
/F-gs-font 7 7 SF
110 429 M
( Class_Access_Flags::ACC_INTERFACE = 0x0200;) s
5 421 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 421 M
(boost) s
/F-gs-font 7 7 SF
42.8 421 M
(::uint16_t ) s
/Courier-Bold 7 7 SUF
89 421 M
(const) s
/F-gs-font 7 7 SF
110 421 M
( Class_Access_Flags::ACC_ABSTRACT  = 0x0400;) s
5 413 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 413 M
(boost) s
/F-gs-font 7 7 SF
42.8 413 M
(::uint16_t ) s
/Courier-Bold 7 7 SUF
89 413 M
(const) s
/F-gs-font 7 7 SF
110 413 M
( Class_Access_Flags::ACC_RESERVED  = 0xF9CE;) s
5 397 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 397 M
(bool) s
/F-gs-font 7 7 SF
5 389 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 389 M
(Class_Access_Flags) s
/F-gs-font 7 7 SF
97.4 389 M
(::has_Valid_Flags \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
248.6 389 M
(const) s
/F-gs-font 7 7 SF
269.6 389 M
(& value \)) s
5 381 M
(    {) s
5 373 M
(        Class_Access_Flags_Rules afr_ref;) s
5 365 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 365 M
(bool) s
/F-gs-font 7 7 SF
55.4 365 M
( result = afr_ref.validate_Flags \( value \);) s
5 357 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 357 M
(return) s
/F-gs-font 7 7 SF
63.8 357 M
( result;) s
5 349 M
(    }) s
5 333 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 333 M
(std) s
/F-gs-font 7 7 SF
34.4 333 M
(::string) s
5 325 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 325 M
(Class_Access_Flags) s
/F-gs-font 7 7 SF
97.4 325 M
(::to_String \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
223.4 325 M
(const) s
/F-gs-font 7 7 SF
244.4 325 M
(& value \)) s
5 317 M
(    {) s
5 309 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 309 M
(std) s
/F-gs-font 7 7 SF
51.2 309 M
(::stringstream output;) s
5 301 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 301 M
(if) s
/F-gs-font 7 7 SF
47 301 M
( \( value & ACC_PUBLIC \)) s
5 293 M
(            {) s
5 285 M
(                output << ) s
/Courier-Bold 7 7 SUF
114.2 285 M
("  public") s
/F-gs-font 7 7 SF
156.2 285 M
(;) s
5 277 M
(            }) s
5 269 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 269 M
(if) s
/F-gs-font 7 7 SF
47 269 M
( \( value & ACC_FINAL \)) s
5 261 M
(            {) s
5 253 M
(                output << ) s
/Courier-Bold 7 7 SUF
114.2 253 M
("  final") s
/F-gs-font 7 7 SF
152 253 M
(;) s
5 245 M
(            }) s
5 237 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 237 M
(if) s
/F-gs-font 7 7 SF
47 237 M
( \( value & ACC_SUPER \)) s
5 229 M
(            {) s
5 221 M
(                output << ) s
/Courier-Bold 7 7 SUF
114.2 221 M
("  super") s
/F-gs-font 7 7 SF
152 221 M
(;) s
5 213 M
(            }) s
5 205 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 205 M
(if) s
/F-gs-font 7 7 SF
47 205 M
( \( value & ACC_INTERFACE \)) s
5 197 M
(            {) s
5 189 M
(                output << ) s
/Courier-Bold 7 7 SUF
114.2 189 M
("  interface") s
/F-gs-font 7 7 SF
168.8 189 M
(;) s
5 181 M
(            }) s
5 173 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 173 M
(if) s
/F-gs-font 7 7 SF
47 173 M
( \( value & ACC_ABSTRACT \)) s
5 165 M
(            {) s
5 157 M
(                output << ) s
/Courier-Bold 7 7 SUF
114.2 157 M
("  reserved") s
/F-gs-font 7 7 SF
164.6 157 M
(;) s
5 149 M
(            }) s
5 133 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 133 M
(return) s
/F-gs-font 7 7 SF
63.8 133 M
( output.str\(\);) s
5 117 M
(    }) s
5 109 M
(} ) s
/Courier-Oblique 7 7 SUF
13.4 109 M
(/* namespace java_module */) s
/F-gs-font 7 7 SF
5 101 M
(} ) s
/Courier-Oblique 7 7 SUF
13.4 101 M
(/* namespace reverse */) s
/F-gs-font 7 7 SF
_R
S
%%Page: (1) 2
%%BeginPageSetup
_S
90 rotate
24 -571 translate
/pagenum 1 def
/fname (Class_Access_Flags_Rules.cpp) def
/fdir () def
/ftail (Class_Access_Flags_Rules.cpp) def
% User defined strings:
/pagenumstr (1) def
/moddatestr (01/24/07) def
/modtimestr (14:13:33) def
/user_header_p false def
/user_footer_p false def
%%EndPageSetup
column_lines
do_header
5 501 M
(#) s
/Courier-Bold 7 7 SUF
9.2 501 M
(include) s
/F-gs-font 7 7 SF
38.6 501 M
( ) s
/Courier-Bold 7 7 SUF
42.8 501 M
("Class_Access_Flags_Rules.h") s
/F-gs-font 7 7 SF
5 493 M
(#) s
/Courier-Bold 7 7 SUF
9.2 493 M
(include) s
/F-gs-font 7 7 SF
38.6 493 M
( ) s
/Courier-Bold 7 7 SUF
42.8 493 M
("Class_Access_Flags.h") s
/F-gs-font 7 7 SF
5 477 M
(namespace reverse { namespace java_module {) s
5 461 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 461 M
(bool) s
/F-gs-font 7 7 SF
5 453 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 453 M
(Class_Access_Flags_Rules) s
/F-gs-font 7 7 SF
122.6 453 M
(::validate_Flags \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
269.6 453 M
(const) s
/F-gs-font 7 7 SF
290.6 453 M
(& value \)) s
5 445 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 445 M
(const) s
/F-gs-font 7 7 SF
5 437 M
(    {) s
5 429 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 429 M
(bool) s
/F-gs-font 7 7 SF
55.4 429 M
( result = true;) s
5 413 M
(        ) s
/Courier-Oblique 7 7 SUF
38.6 413 M
(// Is this class file an interface?) s
/F-gs-font 7 7 SF
5 405 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 405 M
(if) s
/F-gs-font 7 7 SF
47 405 M
( \( ! \( is_Interface \( value \) &&) s
5 397 M
(                 is_Abstract \( value \) &&) s
5 389 M
(                 ! is_Super \( value \) &&) s
5 381 M
(                 ! is_Final \( value \) &&) s
5 373 M
(                 are_Non_Assigned_Bits_Clear \( value \) \) \)) s
5 365 M
(            {) s
5 357 M
(                result = false;) s
5 349 M
(            }) s
5 341 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 341 M
(else) s
/F-gs-font 7 7 SF
55.4 341 M
( ) s
/Courier-Bold 7 7 SUF
59.6 341 M
(if) s
/F-gs-font 7 7 SF
68 341 M
( \(! \( is_Super \( value \) &&) s
5 333 M
(                     ! is_Interface \( value \) &&) s
5 325 M
(                     are_Non_Assigned_Bits_Clear \( value \) \) \)) s
5 317 M
(            {) s
5 309 M
(                result = false;) s
5 301 M
(            }) s
5 285 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 285 M
(return) s
/F-gs-font 7 7 SF
63.8 285 M
( result;) s
5 277 M
(    }) s
5 261 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 261 M
(bool) s
/F-gs-font 7 7 SF
5 253 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 253 M
(Class_Access_Flags_Rules) s
/F-gs-font 7 7 SF
122.6 253 M
(::is_Interface \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
261.2 253 M
(const) s
/F-gs-font 7 7 SF
282.2 253 M
(& value \)) s
5 245 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 245 M
(const) s
/F-gs-font 7 7 SF
5 237 M
(    {) s
5 229 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 229 M
(bool) s
/F-gs-font 7 7 SF
55.4 229 M
( result = false;) s
5 213 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 213 M
(boost) s
/F-gs-font 7 7 SF
59.6 213 M
(::uint16_t check_value = value &) s
5 205 M
(            ) s
/Courier-Bold 7 7 SUF
55.4 205 M
(Class_Access_Flags) s
/F-gs-font 7 7 SF
131 205 M
(::ACC_INTERFACE;) s
5 189 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 189 M
(if) s
/F-gs-font 7 7 SF
47 189 M
( \( check_value == Class_Access_Flags::ACC_INTERFACE \)) s
5 181 M
(            {) s
5 173 M
(                result = true;) s
5 165 M
(            }) s
5 157 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 157 M
(return) s
/F-gs-font 7 7 SF
63.8 157 M
( result;) s
5 149 M
(    }) s
5 133 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 133 M
(bool) s
/F-gs-font 7 7 SF
5 125 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 125 M
(Class_Access_Flags_Rules) s
/F-gs-font 7 7 SF
122.6 125 M
(::is_Abstract) s
5 117 M
(    \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
97.4 117 M
(const) s
/F-gs-font 7 7 SF
118.4 117 M
(& value \) ) s
/Courier-Bold 7 7 SUF
160.4 117 M
(const) s
/F-gs-font 7 7 SF
5 109 M
(    {) s
5 101 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 101 M
(bool) s
/F-gs-font 7 7 SF
55.4 101 M
( result = false;) s
5 93 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 93 M
(boost) s
/F-gs-font 7 7 SF
59.6 93 M
(::uint16_t check_value = value & Class_Access_Flags::ACC_ABSTRACT;) s
5 85 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 85 M
(if) s
/F-gs-font 7 7 SF
47 85 M
( \( check_value == Class_Access_Flags::ACC_ABSTRACT \)) s
5 77 M
(            {) s
5 69 M
(                result = true;) s
5 61 M
(            }) s
5 53 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 53 M
(return) s
/F-gs-font 7 7 SF
63.8 53 M
( result;) s
5 45 M
(    }) s
5 29 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 29 M
(bool) s
/F-gs-font 7 7 SF
5 21 M
(    ) s
/Courier-Bold 7 7 SUF
21.8 21 M
(Class_Access_Flags_Rules) s
/F-gs-font 7 7 SF
122.6 21 M
(::is_Public \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
248.6 21 M
(const) s
/F-gs-font 7 7 SF
269.6 21 M
(& value \) ) s
/Courier-Bold 7 7 SUF
311.6 21 M
(const) s
/F-gs-font 7 7 SF
5 13 M
(    {) s
5 5 M
(        ) s
/Courier-Bold 7 7 SUF
38.6 5 M
(bool) s
/F-gs-font 7 7 SF
55.4 5 M
( result = false;) s
402 501 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 501 M
(boost) s
/F-gs-font 7 7 SF
456.6 501 M
(::uint16_t check_value = value & Class_Access_Flags::ACC_PUBLIC;) s
402 493 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 493 M
(if) s
/F-gs-font 7 7 SF
444 493 M
( \( check_value == Class_Access_Flags::ACC_PUBLIC \)) s
402 485 M
(            {) s
402 477 M
(                result = true;) s
402 469 M
(            }) s
402 461 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 461 M
(return) s
/F-gs-font 7 7 SF
460.8 461 M
( result;) s
402 453 M
(    }) s
402 437 M
(    ) s
/Courier-Bold 7 7 SUF
418.8 437 M
(bool) s
/F-gs-font 7 7 SF
402 429 M
(    ) s
/Courier-Bold 7 7 SUF
418.8 429 M
(Class_Access_Flags_Rules) s
/F-gs-font 7 7 SF
519.6 429 M
(::is_Final \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
641.4 429 M
(const) s
/F-gs-font 7 7 SF
662.4 429 M
(& value \) ) s
/Courier-Bold 7 7 SUF
704.4 429 M
(const) s
/F-gs-font 7 7 SF
402 421 M
(    {) s
402 413 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 413 M
(bool) s
/F-gs-font 7 7 SF
452.4 413 M
( result = false;) s
402 405 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 405 M
(boost) s
/F-gs-font 7 7 SF
456.6 405 M
(::uint16_t check_value = value & Class_Access_Flags::ACC_FINAL;) s
402 397 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 397 M
(if) s
/F-gs-font 7 7 SF
444 397 M
( \( check_value == Class_Access_Flags::ACC_FINAL \)) s
402 389 M
(            {) s
402 381 M
(                result = true;) s
402 373 M
(            }) s
402 365 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 365 M
(return) s
/F-gs-font 7 7 SF
460.8 365 M
( result;) s
402 357 M
(    }) s
402 341 M
(    ) s
/Courier-Bold 7 7 SUF
418.8 341 M
(bool) s
/F-gs-font 7 7 SF
402 333 M
(    ) s
/Courier-Bold 7 7 SUF
418.8 333 M
(Class_Access_Flags_Rules) s
/F-gs-font 7 7 SF
519.6 333 M
(::is_Super \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
641.4 333 M
(const) s
/F-gs-font 7 7 SF
662.4 333 M
(& value \) ) s
/Courier-Bold 7 7 SUF
704.4 333 M
(const) s
/F-gs-font 7 7 SF
402 325 M
(    {) s
402 317 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 317 M
(bool) s
/F-gs-font 7 7 SF
452.4 317 M
( result = false;) s
402 309 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 309 M
(boost) s
/F-gs-font 7 7 SF
456.6 309 M
(::uint16_t check_value = value & Class_Access_Flags::ACC_SUPER;) s
402 301 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 301 M
(if) s
/F-gs-font 7 7 SF
444 301 M
( \( check_value == Class_Access_Flags::ACC_SUPER \)) s
402 293 M
(            {) s
402 285 M
(                result = true;) s
402 277 M
(            }) s
402 269 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 269 M
(return) s
/F-gs-font 7 7 SF
460.8 269 M
( result;) s
402 261 M
(    }) s
402 245 M
(    ) s
/Courier-Bold 7 7 SUF
418.8 245 M
(bool) s
/F-gs-font 7 7 SF
402 237 M
(    ) s
/Courier-Bold 7 7 SUF
418.8 237 M
(Class_Access_Flags_Rules) s
/F-gs-font 7 7 SF
519.6 237 M
(::are_Non_Assigned_Bits_Clear) s
402 229 M
(    \( boost::uint16_t ) s
/Courier-Bold 7 7 SUF
494.4 229 M
(const) s
/F-gs-font 7 7 SF
515.4 229 M
(& value \) ) s
/Courier-Bold 7 7 SUF
557.4 229 M
(const) s
/F-gs-font 7 7 SF
402 221 M
(    {) s
402 205 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 205 M
(bool) s
/F-gs-font 7 7 SF
452.4 205 M
( result = false;) s
402 197 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 197 M
(boost) s
/F-gs-font 7 7 SF
456.6 197 M
(::uint16_t check_value = value & Class_Access_Flags::ACC_RESERVED;) s
402 189 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 189 M
(if) s
/F-gs-font 7 7 SF
444 189 M
( \( check_value == 0 \)) s
402 181 M
(            {) s
402 173 M
(                result = true;) s
402 165 M
(            }) s
402 157 M
(        ) s
/Courier-Bold 7 7 SUF
435.6 157 M
(return) s
/F-gs-font 7 7 SF
460.8 157 M
( result;) s
402 149 M
(    }) s
402 133 M
(} ) s
/Courier-Oblique 7 7 SUF
410.4 133 M
(/* namespace java_module */) s
/F-gs-font 7 7 SF
402 125 M
(} ) s
/Courier-Oblique 7 7 SUF
410.4 125 M
(/* namespace reverse */) s
/F-gs-font 7 7 SF
_R
S
%%Trailer
%%Pages: 2
%%DocumentNeededResources: font Times-Roman Courier-Oblique Courier-Bold 
%%+ font Courier Times-Bold 
%%EOF
