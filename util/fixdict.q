\l expat.q

Fix:([id:`symbol$()]major:`int$();minor:`int$());
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

x:first xmlparse read0 `:/q/xml/FIX44_HS.xml;

Fix,:enlist x[0],"I"$value x[2];
Header,:flip "SB"$'value flip x[1;0;1;;2];
Trailer,:flip "SB"$'value flip x[1;1;1;;2];
Messages,:flip @[;1 0 2] `$value flip x[1;2;1;;2];
Fields,:flip "ISS"$'value flip x[1;4;1;;2];
Enums,:raze {$[10h=type x[1];();("I"$x[2;`number]),/: flip `$value flip x[1;;2]]} each x[1;4;1];

gp0:{[p;x]$[x[0]=`field;enlist p,("SB"$'value x[2]),00b;x[0]=`component;enlist p,("SB"$'value x[2]),01b;x[0]=`group;(enlist p,("SB"$'value x[2]),10b),raze gp0[`$x[2;`name]] each x[1];()]};
//gp:{[p;x]$[x[0]=`field;enlist ("SB"$'value x[2]),(0b;p);x[0]=`group;(enlist ("SB"$'value x[2]),(1b;p));()]};
Components,:raze {(`$x[2;`name]),/:raze gp0[`] each x[1]} each x[1;3;1];
RelationsX,:raze {(`$x[2;`msgtype]),/:raze gp0[`] each x[1]} each x[1;2;1];

cp:{[p;c;r]raze {[p;r;h]$[h`iscomp;cp[p^h`parent;h`fname;r&h`required];enlist (p^h`parent;h`fname;r&h`required;h`isgroup)]}[p;r] each delete cid from select from Components where cid=c}; /[parent;component;required] 

gp:{[p;x]$[x[0]=`field;enlist p,("SB"$'value x[2]),0b;x[0]=`component;cp . p,"SB"$'value x[2];x[0]=`group;(enlist p,("SB"$'value x[2]),1b),raze gp[`$x[2;`name]] each x[1];()]};
Relations,:raze {(`$x[2;`msgtype]),/:raze gp[`] each x[1]} each x[1;2;1];

//{save ` sv `:/kdb/fix/HSFIX44,x} each `Fix`Header`Trailer`Messages`Fields`Enums`Components`RelationsX`Relations;


\
{$[x[0]=`field;enlist ("SB"$'value x[2]),(0b;`);x[0]=`group;(enlist ("SB"$'value x[2]),(1b;`)),raze gp[`$x[2;`name]] each x[1];()]}

mf:{};


Messages,:flip "SSS"$'flip d[3];
Relations,:flip ("S"$;"S"$;`boolean$;`boolean$;(enlist "S"$)') @' flip d[4];
Fields,:flip "ISS"$'flip d[5];
Enums,:flip "ISS"$'flip d[6];
{save ` sv `:/kdb/fix/HSFIX44,x} each `Fix`Header`Trailer`Messages`Relations`Fields`Enums;
