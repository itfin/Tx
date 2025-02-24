\l expat.q

Fix:([id:`symbol$()]major:`int$();minor:`int$();servicepack:`int$());
Fields:([id:`int$()]name:`symbol$();ftype:`symbol$());
Messages:([id:`symbol$()]name:`symbol$();cat:`symbol$());
Enums:([fid:`int$();val:`symbol$()]desp:`symbol$());
Components:([cid:`symbol$();parent:`symbol$();fname:`symbol$()]required:`boolean$();isgroup:`boolean$();iscomp:`boolean$());
RelationsX:([mtype:`symbol$();parent:`symbol$();fname:`symbol$()]required:`boolean$();isgroup:`boolean$();iscomp:`boolean$());
Relations:([mtype:`symbol$();parent:`symbol$();fname:`symbol$()]required:`boolean$();isgroup:`boolean$());
Header:([fname:`symbol$()]required:`boolean$());
Trailer:([fname:`symbol$()]required:`boolean$());

FastTemplate:([id:`int$()]name:`symbol$());
FastFields:([tid:`int$();slot:`int$()]id:`int$();name:`symbol$();ftype:`symbol$();presence:`symbol$();decimal:`int$();op:`symbol$();opval:`symbol$());
FastSequence:([tid:`int$();sid:`int$()]name:`symbol$());
FastSeqFields:([tid:`int$();sid:`int$();slot:`int$()]id:`int$();name:`symbol$();ftype:`symbol$();presence:`symbol$();decimal:`int$();op:`symbol$();opval:`symbol$());

cp:{[p;c;r]raze {[p;r;h]$[h`iscomp;cp[p^h`parent;h`fname;r&h`required];enlist (p^h`parent;h`fname;r&h`required;h`isgroup)]}[p;r] each delete cid from select from Components where cid=c}; /[parent;component;required] 

gp0:{[p;x]$[x[0]=`field;enlist p,("SB"$'value x[2]),00b;x[0]=`component;enlist p,("SB"$'value x[2]),01b;x[0]=`group;(enlist p,("SB"$'value x[2]),10b),raze gp0[`$x[2;`name]] each x[1];()]};
//gp:{[p;x]$[x[0]=`field;enlist ("SB"$'value x[2]),(0b;p);x[0]=`group;(enlist ("SB"$'value x[2]),(1b;p));()]};

gp:{[p;x]$[x[0]=`field;enlist p,("SB"$'value x[2]),0b;x[0]=`component;cp . p,"SB"$'value x[2];x[0]=`group;(enlist p,("SB"$'value x[2]),1b),raze gp[`$x[2;`name]] each x[1];()]};

importfixxml:{[f].temp.x:x:first xmlparse read0 f;
 Fix,:enlist (x[0]^`$x[2]`type),"I"$x[2] `major`minor`servicepack;y:(!/)flip x[1];
 if[0h=type z:y`header;Header,:flip "SB"$'value flip z[;2]];
 if[0h=type z:y`trailer;Trailer,:flip "SB"$'value flip z[;2]];
 if[0h=type z:y`messages;Messages,:flip `$value `msgtype`name`msgcat#flip z[;2];
 RelationsX,:raze {(`$x[2;`msgtype]),/:raze gp0[`] each x[1]} each z;
 Relations,:raze {(`$x[2;`msgtype]),/:raze gp[`] each x[1]} each z;
 ];
 if[0h=type z:y`fields;Fields,:flip "ISS"$'value flip `number`name`type#/:z[;2];
 Enums,:raze {$[10h=type x[1];();("I"$x[2;`number]),/: flip `$value flip `enum`description#/:x[1;;2]]} each z];
 if[0h=type z:y`components;Components,:raze {(`$x[2;`name]),/:raze gp0[`] each x[1]} each z];
 }; /importfixxml `:/q/xml/FIX44_HS.xml importfixxml each `:/q/xml/FIXT11_SP.xml`:/q/xml/FIX50SP2_SP.xml 

appverid:{[x;y;z]$[x<3;`0;x=3;`1;x=4;(0 1 2 3 4i!`2`3`4`5`6)y;x=5;(0N 0 1 2i!`7`7`8`9)z;`]};
savefixdb:{[d]FixOpt:`FixVersion`UseFast`FastField`UseFixT`AppVerID!(upper sv[`]`$string 3#value first 0!Fix;0b;0i;0<exec count i from Fix where id=`FIXT;appverid . value first select from Fix where id=`FIX);{[d;x]save ` sv d,x}[d] each `FixOpt`Fix`Header`Trailer`Messages`Fields`Enums`Components`RelationsX`Relations;}; /savefixdb `:/kdb/fix/HSFIX44 savefixdb `:/kdb/fix/SPFIX50sp2

\
{$[x[0]=`field;enlist ("SB"$'value x[2]),(0b;`);x[0]=`group;(enlist ("SB"$'value x[2]),(1b;`)),raze gp[`$x[2;`name]] each x[1];()]}

mf:{};
 Header,:flip "SB"$'value flip x[1;0;1;;2];
 Trailer,:flip "SB"$'value flip x[1;1;1;;2];
 Messages,:flip @[;1 0 2] `$value flip x[1;2;1;;2];
 Fields,:flip "ISS"$'value flip `name`number`type#/:x[1;4;1;;2];
 Enums,:raze {$[10h=type x[1];();("I"$x[2;`number]),/: flip `$value flip x[1;;2]]} each x[1;4;1];
 Components,:raze {(`$x[2;`name]),/:raze gp0[`] each x[1]} each x[1;3;1];
 RelationsX,:raze {(`$x[2;`msgtype]),/:raze gp0[`] each x[1]} each x[1;2;1];
 Relations,:raze {(`$x[2;`msgtype]),/:raze gp[`] each x[1]} each x[1;2;1];
 

Messages,:flip "SSS"$'flip d[3];
Relations,:flip ("S"$;"S"$;`boolean$;`boolean$;(enlist "S"$)') @' flip d[4];
Fields,:flip "ISS"$'flip d[5];
Enums,:flip "ISS"$'flip d[6];
{save ` sv `:/kdb/fix/HSFIX44,x} each `Fix`Header`Trailer`Messages`Relations`Fields`Enums;
