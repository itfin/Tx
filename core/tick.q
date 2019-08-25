/ q tick.q sym . -p 5001 </dev/null >foo 2>&1 &

/2017.02.13 add chainsub to support tp cross sub
/2017.01.29 minor modified for Tx use.Change endofday[] to benginofday[x] to support skip weekends and holidays,change tick[] to load newest log file.Add .u.h(peertp's handle) and .u.ph(peer tp's sub handle),change .u.end to prevent send .u.end to chained tp.  

/2014.03.12 remove license check
/2013.09.05 warn on corrupt log
/2013.08.14 allow <endofday> when -u is set
/2012.11.09 use timestamp type rather than time. -19h/"t"/.z.Z -> -16h/"n"/.z.P
/2011.02.10 i->i,j to avoid duplicate data if subscription whilst data in buffer
/2009.07.30 ts day (and "d"$a instead of floor a)
/2008.09.09 .k -> .q, 2.4
/2008.02.03 tick/r.k allow no log
/2007.09.03 check one day flip
/2006.10.18 check type?
/2006.07.24 pub then log
/2006.02.09 fix(2005.11.28) .z.ts end-of-day
/2006.01.05 @[;`sym;`g#] in tick.k load
/2005.12.21 tick/r.k reset `g#sym
/2005.12.11 feed can send .u.endofday
/2005.11.28 zero-end-of-day
/2005.10.28 allow`time on incoming
/2005.10.10 zero latency
"kdb+tick 2.8 2014.03.12"

/q tick.q SRC [DST] [chaintp] [chainsub] [-p 5010] [-o h]
system"l tick/",(src:first .z.x,enlist"sym"),".q"

if[not system"p";system"p 5010"]

\l tick/u.q
\d .u
ph:-1;setph:{[]ph::.z.w;};end:{(neg (union/[w[;;0]]) except ph)@\:(`.u.end;x)};
ld:{if[not type key L::`$(-10_string L),string x;.[L;();:;()]];i::j::-11!(-2;L);if[0<=type i;-2 (string L)," is a corrupt log. Truncate to length ",(string last i)," and restart";exit 1];hopen L};

tick:{init[];if[not min(`time`sym~2#key flip value@)each t;'`timesym];@[;`sym;`g#]each t;d::.z.D;if[l::count y;L::`$":",y,"/",x,10#".";if[count fl:key `$":",y;if[d<dm:max "D"$(-10#) each string fl where fl like x,"[0-9]*";d::dm]];l::ld d]};

beginofday:{if[d>=x;:()];end d;d::x;if[l;hclose l;l::0(`.u.ld;d)]};            
ts:{if[d<x;if[d<x-1;system"t 0";'"more than one day?"];beginofday[x]]};       

x:.z.x[2];y:value .z.x[3];h:-1;s:0b;.z.pc:{del[;x]each t;if[.u.h=x;.u.h:-1;.u.s:0b];};
chainsub:{[]if[0=count .u.x;:()];if[0>.u.h;.u.h:@[hopen;(`$.u.x;500);-1]];if[(0>.u.h)|.u.s;:()];neg[h] (".u.setph";());{[h;x]neg[h] (".u.sub";x[0];x[1]);}[.u.h] each .u.y;.u.s:1b;};

if[system"t";
 .z.ts:{pub'[t;value each t];@[`.;t;@[;`sym;`g#]0#];i::j;ts .z.D;chainsub[];};
 upd:{[t;x]
 if[not -16=type first first x;if[d<"d"$a:.z.P;.z.ts[]];a:"n"$a;x:$[0>type first x;a,x;(enlist(count first x)#a),x]];
 t insert x;if[l;l enlist (`upd;t;x);j+:1];}];

if[not system"t";system"t 1000";
 .z.ts:{ts .z.D;chainsub[];};
 upd:{[t;x]ts"d"$a:.z.P;
 if[not -16=type first first x;a:"n"$a;x:$[0>type first x;a,x;(enlist(count first x)#a),x]];
 f:key flip value t;pub[t;$[0>type first x;enlist f!x;flip f!x]];if[l;l enlist (`upd;t;x);i+:1];}];

\d .
.u.tick[src;.z.x 1];
upd:{[t;x].u.upd[t;value flip x];};

\
 globals used
 .u.w - dictionary of tables->(handle;syms)
 .u.i - msg count in log file
 .u.j - total msg count (log file plus those held in buffer)
 .u.t - table names
 .u.L - tp log filename, e.g. `:./sym2008.09.11
 .u.l - handle to tp log file
 .u.d - date

/test
>q tick.q
>q tick/ssl.q

/run
>q tick.q sym  .  -p 5010	/tick
>q tick/r.q :5010 -p 5011	/rdb
>q sym            -p 5012	/hdb
>q tick/ssl.q sym :5010		/feed
