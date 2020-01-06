/ use INSTEAD of an rdb to append data to disk partition during day and use that to build historical partition at day end 
/ q tick/w.q [tickerplanthost]:port[:usr:pwd] [hdbhost]:port[:usr:pwd] [-koe|keeponexit]
/ -keeponexit|koe - keep the (partial) contents of TMPSAVE directories on exit (default NO)
/ tmp storage in `:{pwd-after-logsync}/../tmp.pid.yyyy.mm.dd
/ 2009.09.04 add disksort, faster disk-table sort on slower drives
/ 2008.11.30 add .z.exit and -keeponexit

getTMPSAVE:{`$":../tmp.",(string .z.i),".",string x}  
TMPSAVE:getTMPSAVE .z.d
MAXROWS:100000
KEEPONEXIT:any`keeponexit`koe in key .Q.opt .z.x

append:{[t;data]
    t insert data;
    if[MAXROWS<count value t;
        / append enumerated buffer to disk
        .[` sv TMPSAVE,t,`;();,;.Q.en[`:.]`. t]; 
        / clear buffer
        @[`.;t;0#]; 
        ]}
upd:append

disksort:{[t;c;a] 
    if[not`s~attr(t:hsym t)c;
        if[count t;
            ii:iasc iasc flip c!t c,:();
            if[not$[(0,-1+count ii)~(first;last)@\:ii;@[{`s#x;1b};ii;0b];0b];
                {v:get y;if[not$[all(fv:first v)~/:256#v;all fv~/:v;0b];v[x]:v;y set v];}[ii]each` sv't,'get` sv t,`.d]];
        @[t;first c;a]];t}

/ get the ticker plant and history ports, defaults are 5010,5012
.u.x:.z.x,(count .z.x)_(":5010";":5012")

.u.end:{ / end of day: save, clear, sort on disk, move, hdb reload
    t:tables`.;t@:where 11h=type each t@\:`sym;
    / append enumerated buffer to disk
    {.[` sv TMPSAVE,x,`;();,;.Q.en[`:.]`. x]}each t;
    / clear buffer
    @[`.;t;0#];
    / sort on disk by sym and set `p#
    / {@[`sym xasc` sv TMPSAVE,x,`;`sym;`p#]}each t;
    {disksort[` sv TMPSAVE,x,`;`sym;`p#]}each t;
    / move the complete partition to final home, use <mv> instead of built-in <r> if filesystem whines
    system"r ",(1_string TMPSAVE)," ",-1_1_string .Q.par[`:.;x;`];
    / reset TMPSAVE for new day
    TMPSAVE::getTMPSAVE .z.d;	
    / and notify hdb to reload and pick up new partition
    if[h:@[hopen;`$":",.u.x 1;0];h"\\l .";hclose h];	
    }

.z.exit:{ / unexpected exit: clear, wipe TMPSAVE contents (doesn't rm the directory itself)
    if[not KEEPONEXIT;
        t:tables`.;t@:where 11h=type each t@\:`sym;
        / clear buffer                          
        @[`.;t;0#];
        / overwrite written-so-far-today data with empty
        {.[` sv TMPSAVE,x,`;();:;.Q.en[`:.]`. x]}each t;
        ]}

/ init schema and sync up from log file;cd to hdb (so client save can run)
.u.rep:{(.[;();:;].)each x;if[null first y;:()];system "cd ",1_-10_string first reverse y;-11!y;}
/ HARDCODE \cd if other than logdir/db

/ connect to ticker plant for (schema;(logcount;log))
.u.rep .(hopen `$":",.u.x 0)"(.u.sub[`;`];`.u `i`L)"
