\d .mma

mlopen:`:qmma 2:(`mlopen;1);mlclose:`:qmma 2:(`mlclose;1); mleval:`:qmma 2:(`mleval;3);
MLFUN:value "::";

mldo:mleval[;MLFUN;0];
mldocmd:{mldo[(MLFUN;`ToExpression;enlist x)];};
mlset:{mldo[(MLFUN;`Set;(x;y))];};

mlev:mleval[;MLFUN;1];
mlcmd:{mlev[(MLFUN;`ToExpression;enlist x)]}; 
mlcall:{mlev[(MLFUN;x;$[MLFUN~y;();0h=type y;y;enlist y])]};
mlev2str:{mlev[(MLFUN;`ToString;enlist x)]};
mlcmd2str:{mlev2str[(MLFUN;`ToExpression;enlist x)]};
mlcall2str:{mlev2str[(MLFUN;x;y)]};

mlevil:mleval[;MLFUN;2];
mlevfl:mleval[;MLFUN;3];
mlevia:mleval[;MLFUN;4];
mlevfa:mleval[;MLFUN;5];

mlcmd2il:{mlevil[(MLFUN;`ToExpression;enlist x)]};
mlcmd2fl:{mlevfl[(MLFUN;`ToExpression;enlist x)]};
mlcmd2ia:{mlevia[(MLFUN;`ToExpression;enlist x)]};
mlcmd2fa:{mlevfa[(MLFUN;`ToExpression;enlist x)]};

mlcall2il:{mlevil[(MLFUN;x;$[0h=type y;y;enlist y])]};
mlcall2fl:{mlevfl[(MLFUN;x;$[0h=type y;y;enlist y])]};
mlcall2ia:{mlevia[(MLFUN;x;$[0h=type y;y;enlist y])]};
mlcall2fa:{mlevfa[(MLFUN;x;$[0h=type y;y;enlist y])]};

mlstart:{[x]mlopen (`$"-linklaunch"),$[(10h=type x)&count x;(`$"-linkname"),(`$x);()]};
mlstop:{mlclose[1b];};
mlconnect:{[x;y]mlopen (`$"-linkconnect"),$[(10h=type x)&count x;(`$"-linkprotocol"),(`$x),$[(10h=type y)&count y;(`$"-linkname"),(`$y);()];()]};
mldisconn:{mlclose[0b];};

Sin:mlcall[`Sin];
D:mlcall[`D];
Integrate:mlcall[`Integrate];
FinancialData:mlcall[`FinancialData];
CountryData:mlcall[`CountryData];

\d .
mmastart:.mma.mlstart;
mmaset:.mma.mlset;
mmacmd:.mma.mlcmd;
mmastop:.mma.mlstop;
mmacall:.mma.mlcall;
/

s:.mma.mlstart["/pmma7/pmma.exe"]; s:.mma.mlstart["math -mathlink"];s:.mma.mlstart["Mathematica -mathlink"];
a:.mma.Sin 1.1+til 10;
b:.mma.mlcmd "x Sin[x]";
c:.mma.D (b;`x);
d:.mma.Integrate (b;`x);




//s:mlconnect["SharedMemory";"foo"];
//s:mlconnect["TCPIP";"8000"]; / LinkCreate["8000",LinkProtocol -> "TCPIP"]
//b:CountryData[("France";"Population")];
//a:mlcmd "1+1";
//mlset[`a;til 5];
//a:mlcmd "a";
//mlcall[`Sin;4.5]

mmacmd "PrependTo[$Path, \"/q/mma/lib\"]";

mmacall[`Needs] "ChineseCalendarV1`";


/Mathematica5 -> Q interface
1.download (http://kx.com/q/c/c.java),compile and jar the c.java in /q/java as c.jar:
2.In mma:Needs["JLink`"];InstallJava[CommandLine -> "javaw", ClassPath -> "/q/java/c.jar"];
3.In mma:c = JavaNew["c", "localhost", 5001];r = c@k["select from trade"];r@x;